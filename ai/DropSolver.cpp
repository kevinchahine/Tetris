#include "pch.h"
#include "DropSolver.h"
#include "SolutionSequence.h"

// Remove VVV
#include <Tetris/core/GraphicalDisplay.h>
#include <opencv2/highgui.hpp>
// Remove ^^^

#include <algorithm>
#include <list>
#include <vector>
#include <iterator>
#include <limits>

#include <iocolor/iocolor.h>

using namespace std;
using namespace tetris::core;

namespace tetris
{
	namespace ai
	{
		void DropSolver::reset()
		{
			// Clear queue
			m_moveSequence.clear();
		}

		Move DropSolver::getInput(const Game & game)
		{
			Move selection;
			
			if (m_moveSequence.empty()) {
				solve(game);
				if (m_moveSequence.empty()) {
					throw std::exception("No solution was found");
				}
			}

			selection = m_moveSequence.front();
			m_moveSequence.pop_front();

			// --- Return the selected move ---
			return selection;
		}

		void DropSolver::solve(const Game & inputGame)
		{
			GraphicalDisplay disp;
			SolutionSequence sol;

			// --- Create a copy the current game ---
			Game game = inputGame;

			// --- Stores the selected move ---
			Move selection = Move::DOWN;

			// --- Create a list of all possible drop states ---
			list<TetrominoBase> endStates;

			// 1.) --- Move falling piece all the way to the left ---
			TetrominoBase falling = game.fallingPiece();
			while (game.board().isInBounds(falling)) {
				falling.moveLeft();
			}

			falling.moveRight();

			// 2.) --- For each position, see where the falling piece ends up 
			while (game.board().isInBounds(falling)) {
				// Do each rotation
				for (int orientation = 0; orientation < 4; orientation++) {
					// Make another copy and drop it down as far as it goes.
					TetrominoBase fallingCopy = falling;

					for (int i = 0; i < orientation; i++) {
						fallingCopy.spin(game.board());
					}

					// Push it down
					while (game.board().overlaps(fallingCopy) == false) {
						fallingCopy.moveDown();
					}
					fallingCopy.moveUp();

					// Save this state so that we can analyze it later.
					endStates.push_back(std::move(fallingCopy));
				}

				// --- Move top piece one space to the RIGHT and repeat ---
				falling.moveRight();
			}

			// 3.) --- Make sure we have atleast one end state to analyze ---
			if (endStates.empty()) {
				throw std::exception("No end states were found");
			}

			// 4.) --- Analyze each end state ---
			// --- Now that we have all the end states, analyze each of them ---
			float bestHeuristic = numeric_limits<float>::lowest();
			const TetrominoBase * bestPtr = &endStates.front();

			cout << "Showing end states...";

			for (const TetrominoBase& endState : endStates) {
				// 4-1.) --- Place endState on board ---
				game.board().pasteAt(endState);

				// 4-2.) --- Calculate heuristic ---
				float favorability = m_heuristicPtr->calc(game.board());
				cout << '\t' << "heuristic = " << favorability << '\n';

				disp.rasterize(game);
				disp.show();
				cv::waitKey(0);

				// 4-3.) --- Is this end state better than the best? ---
				if (favorability > bestHeuristic) {
					bestPtr = &endState;
					bestHeuristic = favorability;
				}

				// 4-4.) --- Remove endState from board ---
				game.board().removeFrom(endState);
			}

			// *** Now bestPtr points to the best end state ***
			const TetrominoBase& bestRef = *bestPtr;

			// 5.) --- Find sequence of moves that lead us to the end state ---
			// Clear queue
			m_moveSequence.clear();

			// 5-1.) --- Calculate horizontal shift ---
			int xShift = bestRef.position().x - game.fallingPiece().position().x;
			core::Move move = (xShift < 0 ? Move::LEFT : Move::RIGHT);
			
			for (int i = 0; i < abs(xShift); i++) {
				m_moveSequence.push_back(move);
			}

			// 5-2.) --- Calculate vertical shift ---
			int yShift = bestRef.position().y - game.fallingPiece().position().y;
			move = Move::DOWN;
			
			for (int i = 0; i < abs(yShift); i++) {
				m_moveSequence.push_back(move);
			}

			m_moveSequence.push_back(Move::DOWN);	// Last move to place piece
		}
	}
}