#include "pch.h"
#include "DfsSolver3.h"

#include <Tetris/core/GraphicalDisplay.h>	// Remove <---
#include <opencv2/opencv.hpp>				// Remove <---

using namespace tetris::core;
using namespace std;

namespace tetris
{
	namespace ai
	{
		void DfsSolver3::reset()
		{
			m_moveSequence.clear();
		}

		core::Move DfsSolver3::getInput(const core::Game & game)
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

		std::unique_ptr<ControllerBase> DfsSolver3::clone()
		{
			return std::unique_ptr<DfsSolver3>();
		}

		SolutionSequence DfsSolver3::solve(const core::Game & inputGame)
		{
			GraphicalDisplay disp;
			cout << iocolor::push();

			Game game = inputGame;

			// --- Find best solution for FALLING piece ---

			SolutionSequence fallingSeq = DfsSolver::solve(game);

			float fallingHeur = 0.0f;

			{
				TetrominoBase fallenPiece = fallingSeq.falling();
				fallenPiece.moveUp();
				game.fallingPiece() = move(fallenPiece);
				game.placeFallingPiece();
				game.loadNextPiece();
				SolutionSequence fallingNextSeq = DfsSolver::solve(game);
				
				fallingHeur = calcHeuristic(game.board(), fallingNextSeq.falling());
			}

			// --- Find best solution for HELD piece ---
			game = inputGame;
			game.swapPieces();
			SolutionSequence heldSeq = DfsSolver::solve(game);

			float heldHeur = 0.0f;

			{
				TetrominoBase fallenPiece = heldSeq.falling();
				fallenPiece.moveUp();
				game.fallingPiece() = move(fallenPiece);
				game.placeFallingPiece();
				game.loadNextPiece();
				SolutionSequence heldNextSeq = DfsSolver::solve(game);

				heldHeur = calcHeuristic(game.board(), heldNextSeq.falling());
			}

			cout << iocolor::cyan() << "Held: " << heldHeur << '\n'
				<< "Falling: " << fallingHeur << '\n';

			// --- Determine which is better ---
			SolutionSequence bestSeq;
			if (true/*fallingHeur > heldHeur*/) {
				cout << iocolor::lightgreen() << "Falling is better\n";

				bestSeq = move(fallingSeq);
			}
			else {
				cout << iocolor::lightgreen() << "Held is better\n";

				//heldSeq.prependSwap();

				//bestSeq = move(heldSeq);
			}

			cout << iocolor::pop();

			return bestSeq;
		}
	}
}
