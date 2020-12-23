#include "pch.h"
#include "DfsSolver.h"

#include "SolutionSequence.h"
#include "FrontierStack.h"

#include <Tetris/core/MoveStatePair.h>
#include <Tetris/core/MoveGenerator.h>
#include <Tetris/core/GraphicalDisplay.h>	// Remove
#include <opencv2/highgui.hpp>				// remove

#include <iocolor/iocolor.h>

#include <thread>		// for sleep
#include <chrono>		// for sleep
#include <algorithm>
#include <iterator>
#include <queue>
#include <stack>
#include <set>
#include <limits>

using namespace tetris::core;
using namespace std;

namespace tetris
{
	namespace ai
	{
		void DfsSolver::reset()
		{

		}

		core::Move DfsSolver::getInput()
		{
			//m_moveSequence.clear();

			if (m_moveSequence.empty()) {
				solve();
			
				if (m_moveSequence.empty()) {
					throw std::exception("No solution was found\n");
				}
			}
			else {
			}

			Move selection = m_moveSequence.front();

			m_moveSequence.pop_front();

			// --- Call the callback if it has been set
			if (m_callback != nullptr) {
				m_callback(selection);
			}

			return selection;
		}

		core::Move DfsSolver::solve()
		{
			core::GraphicalDisplay disp;	// remove

			// Create a copy of the current game 
			core::Game game = this->game();
			core::Game gameDisp = game;		// remove

			// Contains states that we want to try next.
			// Make sure that states added to frontier are not found in explored
			// to prevent infinite loops
			FrontierStack<SolutionSequence> frontier;

			// Explored list containing hash values of states that we have analyzed
			// *** "states" should move from the frontier, get analyzed and pushed to explored
			set<size_t> explored;

			SolutionSequence bestSol;							// Best solution found so far
			float bestHeur = numeric_limits<float>::lowest();	// Heuristic of the best solution

			// 1.) Generate starting moves and push them into the frontier
			copyValidMoves(frontier, explored, game.board(), game.fallingPiece());

			// 2.) --- Keep repeating as long has there are moves to try in the frontier ---
			while (!frontier.empty())
			{
				// 2-1.) --- Grab the next state from the frontier ---
				// --- Don't forget to pop it off when we're done with it ---
				SolutionSequence seq = move(frontier.top());
				frontier.pop();

				// 2-1.) --- Put sequence in explored list ---
				// so that we don't analyze it again 
				explored.insert(hash<SolutionSequence>{}(seq));

				// 2-2.) --- Is this a goal state? ---
				// It is a goal state if the falling piece is laying on something
				if (game.board().isLaying(seq.falling())) {
					float heur = calcHeuristic(game.board(), seq.falling());
					cout << "\tHeuristic: " << heur;

					if (heur > bestHeur) {
						bestHeur = heur; 
						bestSol = seq;

						cout << iocolor::push()
							<< iocolor::setfg(iocolor::GREEN)
							<< " best :)\n" 
							<< iocolor::setfg(iocolor::RED) << heur 
							<< iocolor::pop();
					}
					else {
						cout << iocolor::push()
							<< iocolor::setfg(iocolor::RED)
							<< "NOT good enough :(\n"
							<< iocolor::pop();
					}

					gameDisp.fallingPiece() = seq.falling();
					disp.rasterize(gameDisp);
					disp.show();
					cv::waitKey(1);
				}

				// 2-3.) See if there are any moves we can do from here
				copyValidMoves(frontier, explored, game.board(), seq);
			}
			
			if (m_callback != nullptr) {
				m_callback(core::Move::DOWN);
			}
			
			// Copy best solution
			m_moveSequence = std::move(bestSol.sequence());
			m_moveSequence.push_back(Move::DOWN);

			cout << "Solution found: "
				<< iocolor::push()
				<< iocolor::setfg(iocolor::BLUE)
				<< "size = " << m_moveSequence.size() << ' '
				<< iocolor::setfg(iocolor::YELLOW)
				<< bestHeur << '\n'
				<< iocolor::setfg(iocolor::MAGENTA)
				<< bestSol << '\n'
				<< iocolor::pop();
			//this_thread::sleep_for(chrono::milliseconds(500));
			//cin.get();

			return Move::SPIN;// m_moveSequence.front();	// change this please its not correct
		}

		void DfsSolver::copyValidMoves(
			FrontierStack<SolutionSequence>& frontier, 
			const std::set<size_t>& explored, 
			const core::Board& board,
			const SolutionSequence& baseSequence) const
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
				if (explored.count(hashValue) == 0) {
					frontier.push(move(seqCopy));	// move sequence to frontier
				}
			}
		}
	}
}