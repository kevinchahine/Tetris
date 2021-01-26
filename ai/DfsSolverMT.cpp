#include "pch.h"
#include "DfsSolverMT.h"

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
		}

		Move DfsSolverMT::getInput(const core::Game & game)
		{
			if (m_moveSequence.empty()) {

				cout << "Solving...";
				m_moveSequence = solve(game).sequence();

				cout << "Solution: ";
				for (const auto & a : m_moveSequence)
					cout << a << '\n';

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

		SolutionSequence DfsSolverMT::solve(const core::Game & game)
		{
			// 1.) Generate starting moves and push them into the frontier
			branchValidMoves(frontier, explored, game.board(), game.fallingPiece());

			// 2.) Create threads that run solveImpl
			vector<thread> pool;
			pool.reserve(thread::hardware_concurrency());

			for (size_t t = 0; t < pool.capacity(); t++) {
				pool.push_back(thread(&DfsSolverMT::solveImpl, this, game));
			}

			// 3.) Wait for threads to complete
			for_each(pool.begin(), pool.end(), [](auto & t) { t.join(); });

			// 4.) Return the best solution
			return bestSol;
		}

		SolutionSequence DfsSolverMT::solveImpl(const core::Game & game)
		{
			return SolutionSequence();
		}
	}
}
