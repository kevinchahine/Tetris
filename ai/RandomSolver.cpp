#include "pch.h"
#include "RandomSolver.h"

#include <chrono>
#include <random>
#include <vector>

using namespace std;

namespace tetris
{
	namespace ai
	{
		default_random_engine engine(chrono::system_clock::now().time_since_epoch().count());

		void RandomSolver::reset()
		{

		}

		core::Move RandomSolver::getInput()
		{
			// --- Alias the game reference ---
			const tetris::core::Game& game = this->game();

			// --- Get all valid moves ---
			vector<tetris::core::MoveStatePair> validMoves;
			game.generateMoves(validMoves);	// leaves out the swap move

			core::Move selection = core::Move::DOWN;

			if (!validMoves.empty()) {
				// --- Randomly select one of them ---
				uniform_int_distribution<int> dist(0, (validMoves.empty() ? 0 : validMoves.size() - 1));
				int randomIndex = dist(engine);

				selection = validMoves.at(randomIndex).move;
			}

			// --- Call the callback if it has been set
			if (m_callback != nullptr) {
				m_callback(selection);
			}

			// --- Return the selected move ---
			return selection;
		}
	}
}