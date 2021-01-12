#include "pch.h"
#include "RandomSolver.h"

#include <chrono>
#include <random>
#include <vector>

using namespace std;
using namespace tetris::core;

namespace tetris
{
	namespace ai
	{
		default_random_engine engine(chrono::system_clock::now().time_since_epoch().count());

		RandomSolver::RandomSolver(const RandomSolver & solver) :
			AiController(solver)
		{
		}

		RandomSolver & RandomSolver::operator=(const RandomSolver & solver)
		{
			static_cast<AiController &>(*this) = solver;

			return *this;
		}

		void RandomSolver::reset()
		{

		}

		core::Move RandomSolver::getInput(const core::Game & game)
		{
			// --- Get all valid moves ---
			vector<tetris::core::MoveStatePair> validMoves;
			game.generateMoveStatePairs(validMoves);	// leaves out the swap move

			core::Move selection = core::Move::DOWN;

			if (!validMoves.empty()) {
				// --- Randomly select one of them ---
				uniform_int_distribution<int> dist(0, (validMoves.empty() ? 0 : validMoves.size() - 1));
				int randomIndex = dist(engine);

				selection = validMoves.at(randomIndex).move;
			}

			// --- Return the selected move ---
			return selection;
		}

		std::unique_ptr<ControllerBase> RandomSolver::clone()
		{
			return make_unique<RandomSolver>(*this);
		}
		std::string RandomSolver::name()
		{
			return "Random";
		}
	}
}