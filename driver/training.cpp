#include "training.h"

#include <Tetris/ai/Optimizer.h>
#include <Tetris/ai/Solvers.hpp>
#include <Tetris/ai/Heuristics.hpp>
#include <Tetris/ai/Individual.h>

#include <chrono>

using namespace std;

namespace tetris
{
	namespace driver
	{
		void train1()
		{
			tetris::ai::optimizers::Optimizer op;

			// Set Optimizer parameters
			{
				unique_ptr<tetris::ai::DfsSolver> solverPtr = make_unique<tetris::ai::DfsSolver>();
				solverPtr->heuristicPtr() = make_unique<tetris::ai::AppleCiderHeuristic>();
				op.setAiController(move(solverPtr));
				
				op.setGenerationsLimit(std::numeric_limits<int>::max());
				
				op.setTimeLimit(chrono::seconds::max());
				
				op.setPopulationSize(8);
			}

			cout << "Starting training\n";
			tetris::ai::Session session = 
				op.train();
				//op.resumeTrainingFromFile();

			cout << "Training complete\n";

			cout << "All Time Best: " << session.allTimeBest << '\n';
			cout << "Population:\n";
			for (const tetris::ai::optimizers::Individual i : session.population) {
				cout << "\t" << i << "\n";
			}
		}
	}
}