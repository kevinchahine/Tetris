#include "pch.h"
#include "Optimizer.h"

#include <Tetris/core/GamePlayer.h>
#include <Tetris/core/DisplayBase.h>

#include <iocolor/iocolor.h>

#include <fstream>
#include <algorithm>
#include <random>
#include <thread>

using namespace std;

// --- Externs ---
extern default_random_engine generator;

namespace tetris
{
	namespace ai
	{
		namespace optimizers
		{
			// ------------------------ PUBLIC METHODS ------------------------

			void Optimizer::reset()
			{

			}

			vector<float> Optimizer::train()
			{
				Individual allTimeBest;

				// Create the first generation
				vector<Individual> population = makeInitialPopulation();

				// Keep training 
				resumeTraining(population, allTimeBest);

				return allTimeBest.weights();
			}

			void Optimizer::resumeTraining(const vector<Individual> & inputPopulation,	Individual & allTimeBest)
			{
				// Do some safty checks
				if (m_aiController == nullptr) 
					throw exception("AiController was not set. Did someone forget to call Optimizer::setAiController()");
				if (m_aiController->heuristicPtr() == nullptr)
					throw exception("AiController was not attached to a HeuristicBase object");
				if (inputPopulation.empty()) 
					throw exception("inputPopulation is empty.");
				// *** Still need to make sure each Inidividual has the same number of heuristic elements as does the AiControllers heuristic

				chrono::steady_clock::time_point startTime = chrono::steady_clock::now();

				// Create a copy of the input population
				vector<Individual> population = inputPopulation;

				// Be fruitfull and multiply 
				// (but don't actually multiply. This algorithm only works with population control)
				for (int genNum = 0; genNum < m_generationsLimit; genNum++) {
					// Check time limit
					chrono::steady_clock::time_point currTime = chrono::steady_clock::now();
					chrono::seconds dur = chrono::duration_cast<chrono::seconds>(currTime - startTime);

					cout << "Generation " << genNum << '\t' << "training time: " << dur.count() << " seconds" << '\n';

					//if (dur > m_timeLimit) {
					//	cout << "Time out at " << dur.count() << '\n';
					//	break;
					//}

					// Evaluate Each individual and save their scores in population
					evalPopulation(m_aiController, population);

					// Challenge allTimeBest
					auto maxIt = max_element(population.begin(), population.end());
					if (maxIt->score() > allTimeBest.score()) {
						allTimeBest = *maxIt;

						cout << iocolor::push()
							<< iocolor::setfg(iocolor::GREEN)
							<< "Found a better all time best: " << allTimeBest << '\n'
							<< iocolor::pop();
					}

					// Breed population to create the next generation
					// population must be sorted based on score before calling breed
					vector<Individual> nextGeneration = breed(move(population));

					population = move(nextGeneration);

					chrono::steady_clock::time_point endGenTime = chrono::steady_clock::now();
					chrono::seconds generationDuration = chrono::duration_cast<chrono::seconds>(endGenTime - currTime);
					cout << "Generation Time Elapsed: " << generationDuration.count() << " seconds\n";

					// --- Save Progress (incase errors occur) ---
					saveProgress(genNum, allTimeBest, population);
				}

				chrono::steady_clock::time_point endTime = chrono::steady_clock::now();
			}

			void Optimizer::resumeTrainingFromFile()
			{
				Individual allTimeBest;

				// Create the first generation
				vector<Individual> population;

				int genNumber = 0;

				restoreProgress(genNumber, allTimeBest, population);

				// Keep training 
				resumeTraining(population, allTimeBest);
			}

			// ------------------------ PRIVATE METHODS -----------------------

			vector<Individual> Optimizer::makeInitialPopulation()
			{
				// Make our randomizer
				uniform_real_distribution<float> uniDist(-1.0f, 1.0f);

				// How many weights do we have?
				const size_t N_WEIGHTS = m_aiController->heuristicPtr()->weights().size();

				// --- Create Population ---
				// Create a population of <m_populationSize> individuals 
				// each with <N_WEIGHTS> weights
				vector<Individual> population;
				population.reserve(m_populationSize);

				// --- Assign each Individual random weights ---
				default_random_engine * gPtr = &generator;
				generate_n(back_inserter(population), m_populationSize, [&]() {
					Individual someone{ N_WEIGHTS };
					auto & weights = someone.weights();

					transform(weights.begin(), weights.end(), weights.begin(), [&](float value) {
						return uniDist(generator);
					});

					return someone;
				});

				return population;
			}

			Individual Optimizer::makeBaby(const Individual & mom, const Individual & dad)
			{
				// All weight vectors must be the same size
				const size_t N_WEIGHTS = mom.weights().size();

				// --- Create child ---
				Individual child;

				child.weights().resize(N_WEIGHTS);

				// pick a random number between 0 and weights.size();
				uniform_int_distribution<size_t> uniDist(0, N_WEIGHTS - 1);
				normal_distribution<float> normDist(-0.2f, 0.2f);

				// --- cross-breed ---
				size_t splitPoint = uniDist(generator);
				copy(mom.weights().data(), mom.weights().data() + splitPoint, child.weights().data());
				copy(dad.weights().data() + splitPoint, dad.weights().data() + N_WEIGHTS, child.weights().data() + splitPoint);

				// --- add a small variance to a randomly selected weight ---
				int weightIndex = uniDist(generator);
				child.weights().at(weightIndex) += normDist(generator);

				// --- Return
				return child;
			}

			vector<Individual> Optimizer::breed(const vector<Individual> & population)
			{
				vector<Individual> newPopulation;
				newPopulation.reserve(population.size());

				vector<int> scores;
				scores.reserve(population.size());
				transform(
					population.begin(), population.end(),
					back_inserter(scores), 
					[](const Individual & individual) {	return individual.score(); });

				// Randomly select 2 parents (Give a higher chance to Individuals with a higher score)
				discrete_distribution<size_t> dist(scores.begin(), scores.end());	// O(n)

				generate_n(back_inserter(newPopulation), population.size(), [&]() {
					const Individual & mom = population.at(dist(generator));		// O(1)
					const Individual & dad = population.at(dist(generator));		// O(1)
				
					return makeBaby(mom, dad);
				});

				return newPopulation;
			}

			int Optimizer::eval(unique_ptr<AiController>& controllerPtr)
			{
				// --- Set up Game (MODEL) ---
				core::Game game;
				game.awake();

				controllerPtr->reset();

				// --- Game Loop ---
				while (game.isGameOver() == false)
				{
					tetris::core::Move m = controllerPtr->getInput(game);
					game.update(m);
				}

				return game.scoreKeeper().getScore();
			}

			void Optimizer::evalPopulation(unique_ptr<AiController>& controllerPtr, vector<Individual>& population)
			{
				//vector<thread> threadPool{ thread::hardware_concurrency() };	// Just a start

				for (Individual & individual : population) {
					// Play a game

					std::function<void(const Individual &)> evaluate =
						[](const Individual & individual) {

					};

					// Set weights of ai controller
					m_aiController->heuristicPtr()->weights() = individual.weights();

					// Play a game using the individuals weights heuristic
					int score = eval(m_aiController);

					individual.score() = score;

					cout << iocolor::push()
						<< iocolor::setfg(iocolor::YELLOW)
						<< individual
						<< iocolor::pop() << '\n';
				}
			}

			void Optimizer::saveProgress(int genNumber, const Individual & allTimeBest, const std::vector<Individual> & population)
			{
				// 1.) --- Create file and archiver ---1
				ofstream outFile;
				string fileName = "Generation_" + to_string(genNumber) + ".txt";
				outFile.open(fileName);
				boost::archive::text_oarchive outAr{ outFile };

				cout << iocolor::push()
					<< iocolor::setfg(iocolor::LIGHTMAGENTA)
					<< "Saving progress to " << fileName << "...";

				// 2.) --- Archive progress to file ---
				outAr << genNumber;
				outAr << allTimeBest;
				outAr << population;

				// 3.) --- Close file ---
				outFile.close();

				cout << "done\n"
					<< iocolor::pop();
			}

			void Optimizer::restoreProgress(int & genNumber, Individual & allTimeBest, std::vector<Individual> & population)
			{
				// 1.) --- Open file and create Archiver ---
				ifstream inFile;
				string fileName = "Generation_" + to_string(10) + ".txt";
				inFile.open(fileName);
				boost::archive::text_iarchive inAr{ inFile };

				cout << iocolor::push()
					<< iocolor::setfg(iocolor::CYAN)
					<< "Saving progress to " << fileName << "...";

				// 2.) --- Restore progress from archive ---
				inAr >> genNumber;
				inAr >> allTimeBest;
				inAr >> population;

				// 3.) --- Close file ---
				inFile.close();

				cout << "done\n"
					<< iocolor::pop();
			}
		}
	}
}