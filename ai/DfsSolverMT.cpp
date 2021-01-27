#include "pch.h"
#include "DfsSolverMT.h"

#include <Tetris/core/MoveGenerator.h>

#include <iomanip>	// for setprecision(). can be removed
#include <math.h>

using namespace std;
using namespace tetris::core;

namespace tetris
{
	namespace ai
	{
		DfsSolverMT::DfsSolverMT(const DfsSolverMT & rhs)
		{
			try {
				{
					unique_lock<mutex> rhs_lk(rhs.frontierMutex);
					this->frontier = rhs.frontier;
				}

				{
					unique_lock<mutex> rhs_lk(rhs.exploredMutex);
					this->explored = rhs.explored;
				}

				{
					unique_lock<mutex> rhs_lk(rhs.bestSolMutex);
					this->bestSol = rhs.bestSol;
					this->bestHeur = rhs.bestHeur;
				}
			}
			catch (exception & e) {
				cout << "Exception caught: " << e.what() << '\n'
					<< '\t' << __FUNCTION__ << '\n';
			}
		}

		DfsSolverMT::DfsSolverMT(DfsSolverMT && rhs) noexcept
		{
			try {
				{
					unique_lock<mutex> rhs_lk(rhs.frontierMutex);
					this->frontier = move(rhs.frontier);
				}

				{
					unique_lock<mutex> rhs_lk(rhs.exploredMutex);
					this->explored = move(rhs.explored);
				}

				{
					unique_lock<mutex> rhs_lk(rhs.bestSolMutex);
					this->bestSol = move(rhs.bestSol);
					this->bestHeur = move(rhs.bestHeur);
				}
			}
			catch (exception & e) {
				cout << "Exception caught: " << e.what() << '\n'
					<< '\t' << __FUNCTION__ << '\n';
			}
		}

		DfsSolverMT & DfsSolverMT::operator=(const DfsSolverMT & rhs)
		{
			if (this != &rhs)
			{
				{
					unique_lock<mutex> lhs_lk(this->frontierMutex, defer_lock);
					unique_lock<mutex> rhs_lk(rhs.frontierMutex, defer_lock);
					lock(lhs_lk, rhs_lk);
					this->frontier = rhs.frontier;
				}

				{
					unique_lock<mutex> lhs_lk(this->exploredMutex, defer_lock);
					unique_lock<mutex> rhs_lk(rhs.exploredMutex, defer_lock);
					lock(lhs_lk, rhs_lk);
					this->explored = rhs.explored;
				}

				{
					unique_lock<mutex> lhs_lk(this->bestSolMutex, defer_lock);
					unique_lock<mutex> rhs_lk(rhs.bestSolMutex, defer_lock);
					lock(lhs_lk, rhs_lk);
					this->bestSol = rhs.bestSol;
					this->bestHeur = rhs.bestHeur;
				}
			}

			return *this;
		}

		DfsSolverMT & DfsSolverMT::operator=(DfsSolverMT && rhs) noexcept
		{
			if (this != &rhs)
			{
				{
					unique_lock<mutex> lhs_lk(this->frontierMutex);
					unique_lock<mutex> rhs_lk(rhs.frontierMutex);
					lock(lhs_lk, rhs_lk);
					this->frontier = move(rhs.frontier);
				}

				{
					unique_lock<mutex> lhs_lk(this->exploredMutex);
					unique_lock<mutex> rhs_lk(rhs.exploredMutex);
					lock(lhs_lk, rhs_lk);
					this->explored = move(rhs.explored);
				}

				{
					unique_lock<mutex> lhs_lk(this->bestSolMutex);
					unique_lock<mutex> rhs_lk(rhs.bestSolMutex);
					lock(lhs_lk, rhs_lk);
					this->bestSol = move(rhs.bestSol);
					this->bestHeur = move(rhs.bestHeur);
				}
			}

			return *this;
		}

		void DfsSolverMT::reset()
		{
			m_moveSequence.clear();

			frontier.clear();
			explored.clear();
			bestSol.clear();
			bestHeur = numeric_limits<float>::lowest();
			noMoreWorkFlags.reset();	// set all bits to 0
		}

		Move DfsSolverMT::getInput(const core::Game & game)
		{
			if (m_moveSequence.empty()) {
				m_moveSequence = solve(game).sequence();

				if (m_moveSequence.empty()) {
					throw std::exception("No solution was found\n");
				}
			}
			else {
			}

			Move selection = m_moveSequence.front();

			m_moveSequence.pop_front();

			return selection;
		}

		unique_ptr<ControllerBase> DfsSolverMT::clone()
		{
			return make_unique<DfsSolverMT>(*this);
		}

		string DfsSolverMT::name()
		{
			return "DFS1-MT";
		}

		void DfsSolverMT::branchValidMoves(
			const core::Board & board, 
			const SolutionSequence & baseSequence)
		{
			vector<Move> validMoves;
			generateMoves(validMoves, board, baseSequence.falling());

			// Copy moves in reverse order
			for (auto it = validMoves.rbegin(); it != validMoves.rend(); it++)
			{
				Move m = *it;

				// Make a copy of the sequence
				SolutionSequence seqCopy = baseSequence;

				// Apply move to sequence
				seqCopy.move(m, board);

				// Calc hash of new sequence
				size_t hashValue = hash<SolutionSequence>{}(seqCopy);

				// Only add new sequence if this state has not already been analyzed
				exploredMutex.lock();
				frontierMutex.lock();
				if (explored.count(hashValue) == 0) {
					frontier.push(move(seqCopy));	// move sequence to frontier
				}
				frontierMutex.unlock();
				exploredMutex.unlock();
			}
		}

		SolutionSequence DfsSolverMT::solve(const core::Game & game)
		{
			reset();

			// 1.) Generate starting moves and push them into the frontier
			branchValidMoves(game.board(), game.fallingPiece());

			// 2.) Create threads that run solveImpl
			vector<thread> pool;
			//pool.reserve(1);
			pool.reserve(thread::hardware_concurrency());	// !!! This should be set from CL

			for (size_t t = 0; t < pool.capacity(); t++) {
				pool.push_back(thread(&DfsSolverMT::solveImpl, this, game, noMoreWorkFlags[t]));
			}

			// 3.) Wait for threads to complete
			for_each(pool.begin(), pool.end(), [](auto & t) { t.join(); });

			// 3.) --- Append a final move to solution to place piece ---
			bestSol.placePiece();

			// 4.) Return the best solution
			return bestSol;
		}

		void DfsSolverMT::solveImpl(const core::Game & game, std::bitset<64>::reference && noMoreWorkBit)
		{
			// 2.) --- Keep repeating as long as there are moves to try in the frontier ---
			while (true) {
				// 2-1.) --- Grab the next state from the frontier ---
				// --- Don't forget to pop it off when we're done with it ---
				frontierMutex.lock();								// vvvvv
				if (frontier.empty())								// O(1)
				{
					frontierMutex.unlock();							// ^^^^^
				
					// Tell other threads that we don't have anywork to do.
					noMoreWorkBit = 0;	

					// Do any other threads have work to do?
					if (noMoreWorkFlags.none()) {
						// Nope, all threads are workless and 
						// will no longer push work to frontier anymore.
						break;	// We done here dog
					}
					else {
						// Skip and repeat and recheck to see if 
						// another thread has pushed more work to frontier.
						continue;
					}
				}

				// Tell other threads that we are still working and will soon push stuff 
				// to frontier. In otherwords, other threads should not return if frontier is empty yet.
				noMoreWorkBit = 1;	

				SolutionSequence seq = move(frontier.top());		// O(1)
				frontier.pop();										// O(n + log(n))
				frontierMutex.unlock();								// ^^^^^

				// 2-2.) --- Put sequence in explored list ---
				// so that we don't analyze it again
				auto h = hash<SolutionSequence>{}(seq);				// O(n)
				exploredMutex.lock();								// vvvvv
				explored.insert(h);									// O(log(n))
				exploredMutex.unlock();								// ^^^^^

				// 2-3.) --- Is this a goal state? --- 
				// It is a goal state if the falling piece is laying on something
				if (game.board().isLaying(seq.falling())) {
					float heur = calcHeuristic(game.board(), seq.falling());

					bestSolMutex.lock();							// vvvvv
					
					if (
						(heur > bestHeur)/* || */
					//	(fabs(heur - bestHeur) <= 0.2f * fabs(heur) && seq.sequence().size() < bestSol.sequence().size())
					) 			
					{
						bestHeur = heur;							// O(1)
						bestSol = seq;								// O(n)	!!! This should be optimized with move if possible
					}
					bestSolMutex.unlock();							// ^^^^^
				}

				// 2-4.) See if there are any moves we can do from here
				// This method is thread safe and contains mutex locks on the inside 
				// that are used in a way optimized for multi threading
				branchValidMoves(game.board(), seq);	
			}
		}
	}
}
