#include "pch.h"
#include "DfsSolver2.h"

using namespace tetris::core;
using namespace std;

namespace tetris
{
	namespace ai
	{
		void DfsSolver2::reset()
		{
			m_moveSequence.clear();
		}

		Move DfsSolver2::getInput(const Game & game)
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

		std::unique_ptr<ControllerBase> DfsSolver2::clone()
		{
			return make_unique<DfsSolver2>(*this);
		}

		SolutionSequence DfsSolver2::solve(const Game & game)
		{
			Game gameCopy = game;

			// --- Find best solution for FALLING piece ---
			SolutionSequence fallingSeq = DfsSolver::solve(gameCopy);
			float fallingHeur = calcHeuristic(gameCopy.board(), fallingSeq.falling());

			// --- Find best solution for HELD piece ---
			Game copy2 = game;
			copy2.swapPieces();
			SolutionSequence heldSeq = DfsSolver::solve(copy2);
			float heldHeur = calcHeuristic(copy2.board(), heldSeq.falling());

			cout << iocolor::push()
				<< iocolor::cyan() << "Held: " << heldHeur << '\n'
				<< "Falling: " << fallingHeur << '\n'
				<< iocolor::pop();

			// --- Determine which is better ---
			if (fallingHeur > heldHeur) {
				cout << iocolor::push()
					<< iocolor::lightgreen() << "Falling is better\n"
					<< iocolor::pop();

				return fallingSeq;
			}
			else {
				heldSeq.prependSwap();
				
				cout << iocolor::push()
					<< iocolor::lightgreen() << "Held is better\n"
					<< iocolor::pop();

				return heldSeq;
			}
		}
	}
}