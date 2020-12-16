#include "pch.h"
#include "DropSolver.h"

#include <list>
#include <vector>

using namespace std;
using namespace tetris::core;

namespace tetris
{
	namespace ai
	{
		void DropSolver::reset()
		{

		}

		core::Move DropSolver::getInput()
		{
			Move selection = solve();

			// --- Call the callback if it has been set
			if (m_callback != nullptr) {
				m_callback(selection);
			}

			// --- Return the selected move ---
			return selection;
		}

		core::Move DropSolver::solve()
		{
			// --- Create a copy the game ---
			Game game = this->game();

			// --- Stores the selected move ---
			Move selection = Move::DOWN;

			// --- Create a list of all possible drop states ---
			list<TetrominoBase> endStates;

			// 1.) --- Move falling piece all the way to the left ---
			TetrominoBase& fallingRef = game.fallingPiece();
			while (game.board().isInBounds(fallingRef)) {
				fallingRef.moveLeft();
			}
			fallingRef.moveRight();

			// 2.) --- For each position, see where the falling piece ends up 
			while (game.board().isInBounds(fallingRef)) {
				// Make another copy and drop it down as far as it goes.
				TetrominoBase fallingCopy = fallingRef;

				// Push it down
				while (game.board().overlaps(fallingCopy) == false) {
					fallingCopy.moveDown();
				}

				// Save this state so that we can analyze it later.
				endStates.push_back(move(fallingCopy));

				// --- Move top piece one space to the RIGHT and repeat ---
				fallingRef.moveRight();
			}

			// 3.) --- Analyze each end state ---
			// --- Now that we have all the end states, analyze each of them ---
			for (const TetrominoBase& endState : endStates) {
				// 3-1.) --- Place endState on board ---

				// 3-2.) --- Calculate heuristic ---

				// 3-3.) --- Remove endState from board ---
			}

			return selection;
		}

	}
}