#include "training.h"

#include <Tetris/ai/Optimizer.h>
#include <Tetris/ai/Solvers.hpp>
#include <Tetris/ai/Heuristics.hpp>
#include <Tetris/ai/Individual.h>

#include <chrono>
#include <numeric>

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
				unique_ptr<tetris::ai::DfsSolver3> solverPtr = make_unique<tetris::ai::DfsSolver3>();
				solverPtr->heuristicPtr() = make_unique<tetris::ai::AppleCiderHeuristic>();
				op.setAiController(move(solverPtr));
				
				op.setGenerationsLimit(INT_MAX);// numeric_limits<int>::max());
				
				op.setTimeLimit(chrono::hours(1000));// chrono::seconds::max());
				
				op.setPopulationSize(10);
			}

			chrono::steady_clock::time_point startTime = chrono::steady_clock::now();

			cout << "Starting training at "
				<< startTime.time_since_epoch().count()
				<< "\n";

			tetris::ai::Session session = 
				op.train();
				//op.resumeTrainingFromFile();

			chrono::steady_clock::time_point finishTime = chrono::steady_clock::now();

			cout << "Training complete at " << finishTime.time_since_epoch().count() << "\n";
			cout << "duration = "
				<< chrono::duration_cast<chrono::minutes>(finishTime - startTime).count()
				<< " minutes\n";

			cout << "All Time Best: " << session.allTimeBest << '\n';
			cout << "Population:\n";
			for (const tetris::ai::optimizers::Individual i : session.population) {
				cout << "\t" << i << "\n";
			}
		}
	}
}