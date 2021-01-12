#pragma once
#include "ai.h"
#include "Individual.h"
#include "AiController.h"
#include "Session.h"

#include <limits>		// for numeric<T>::max()
#include <chrono>
#include <vector>
#include <memory>		// for unique_ptr<T>

/*
	will involve:
		multithreading
		filesystems
		random number distributions
		boost::serializer
		chrono
		multiwindow stuff (try to show all games on the same window)
			Make a new Display class for it that shows multiple games

	Optimizer op;

	op.setOutPutDir(filesystem::directory);				// <--- defaults to '.'

	*/

/*
	/////////////////////////////////////////////////////////////////

	// *** Consider using a map<int, weights> for population that way the weights
	// will always be sorted
	vector<Weights> population;
	vector<int>	 scores;
	vector<pair<weights, int>> populationScorePairs;		// use this instead
	pair<weights, int> allTimeBest;

	chrono::time_point startTime = now();

	for (int gen = 0; gen < generationLimit; gen++) {
		chrono::time_point currTime = now();
		chrono::duration trainingDuration = currTime - startTime;
		if (trainingDuration > timeLimit) {
			break;
		}

		for each person in population:
			Game g;
			g.controller() = person
			g.setWeights(person);
			g.setControlelr();
			int scores.push_back() = g.run();

			vector<Weights> newPop;
			sort population according to score

			// Save results in a file
			//	- gen and generationLimit
			//	- time_elapsed and timeLimit
			//	- generationnumber
			//	- population - vector<pair<weights, int>>
			//	- allTimeBest - pair<weights, int>

			// Breeding phase
				
				// Calculate favorability of each person 
				{
				vector<Weights> newPopulation = breed(population, scores);
				population = move(newPopulation;
				}

			// Challenge the all time best
			pair<weights, int> & best = max(population.begin(), end(), [](const auto & left, const auto & right){ return left.second < right.second; });
			if (best.second > allTimeBest.second) {
				allTimeBest = best;
				cout << "Found a new all time best: " << allTimeBest << '\n';
			}
		}

		return allTimeBest;
	}

	*/

/*
	/////////////////////////////////////////////////////
	vector<float> breed(vector<pair<weights, int>> & population)
	{
		sort(
		population, 
		[](const pair<weights, int> & left, const pair<weights, int> & right>) 
			{ return left.second < right.second; }
		);

		int scoreSum = accumulate(population.begin(), end(), [](const auto & elem) { return elem.second; });

		// make sure population is sorted in assending order
		pickOne(int scoreSum, population) {
			uniform_int_distribution<int> dist(0, scoreSum);
			int num = dist(generator);

			//                                                         *** Might not be > ***
			return find_last_of(population.begin, end, [num](const auto & person) { return num > person.second; }
		}

		for (int i = 0; i < population.size(); i++) {
			const pair<weights, int> & mom = pickOne(scoreSum, population);
			const pair<weights, int> & dad = pickOne(scoreSum, population);

			pair<weights, int> child = makeBaby(mom, dad);
			newPopulation.push_back(move(child));
		}

		return newPopulation;
	}

	*/

/*
	////////////////////////////////////////////////////////////////////////////
	void saveProgress(const boost::filesystem::directory & outDir, Everything else) {
		// 1.) Make sure directory can be accessed

		// 2.) Determine what to name the file (we want to becareful not to overwrite any existing files)
		
		// 3.) Create directory named after date (use boost::posix::date_time)
		//	 ex: /Trining_24_12_2020_time/ 
		//	It would be nice if the name is in both lexicological and chronological order

		// 4.) Create a file (if it doesn't already exist) named after the generation number
		//	ex: /Training_24_12_2020_time/generation_005.txt
		// It is unlikely that file already exists in normal operations but if it does then 
		// overrite it I guess

		// 5.) Serialize the current generation

		// 6.) Write current generation to file

		// 7.) Close file
	}

	*/

/*
	Everything else & void recoverProgress(const boost::filesystem::directory & outDir)
	{
		// 1.) Find the most recent file
		// Iterate files in outDir and find the one with the latest date

		// 2.) read and parse that file

		// 3.) return
	}
*/

namespace tetris
{
	namespace ai
	{
		namespace optimizers
		{
			class AI_API Optimizer
			{
			public:	// -------------------- PUBLIC METHODS ------------------------

				void reset();

				Session train(std::unique_ptr<AiController> && controller, int popSize, int generationsLimit);
					
				Session train();

				void resumeTraining(Session & trainingSession);

				Session resumeTrainingFromFile();

				// Make sure the AiController has been assigned a heuristic
				void setAiController(std::unique_ptr<ai::AiController> && controller) { m_aiController = std::move(controller); }
				const std::unique_ptr<ai::AiController> & getAiController() const { return m_aiController; }
				
				// Use std::numeric_limits<int>::max() for "endless" generations
				void setGenerationsLimit(int nGenerations) { m_generationsLimit = nGenerations; }
				// If returned value equals std::numeric_limits<int>::max(), 
				// then optimizer will run for an "endless" number of generations
				int getGenerationsLimit() const { return m_generationsLimit; }
				
				void setTimeLimit(std::chrono::seconds timeLimit) { m_timeLimit = timeLimit; }
				std::chrono::steady_clock::duration getTimeLimit() const { return m_timeLimit; }
				
				void setPopulationSize(int populationSize) { m_populationSize = populationSize; }
				int getPopulationSize() const { return m_populationSize; }

			private:	// ---------------- PRIVATE METHODS -----------------------

				std::vector<Individual> makeInitialPopulation();

				// Assumes mom.weights().size() == dad.weights().size() and both are > 0
				Individual makeBaby(const Individual & mom, const Individual & dad);

				// Make sure population is sorted from least to greatest score
				std::vector<Individual> breed(const std::vector<Individual> & population);

				int eval(std::unique_ptr<AiController> & controllerPtr, int randomSeed);

				void eval(std::unique_ptr<AiController> & controllerPtr, Individual & individual, int randomSeed);

				void evalPopulation(std::unique_ptr<AiController> & controllerPtr, std::vector<Individual> & population, int randomSeed);

				void saveProgress(const Session & session);
				
				Session restoreProgress();

			private:	// ---------------- PRIVATE FIELDS ------------------------

				std::unique_ptr<tetris::ai::AiController> m_aiController;

				int m_generationsLimit = INT_MAX; // std::numeric_limits<int>::max();

				std::chrono::seconds m_timeLimit;

				int m_populationSize = 10;
			};
		}
	}
}