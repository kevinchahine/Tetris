#pragma once
#include "ai.h"

/*
	will involve:
		multithreading
		filesystems
		random number distributions
		boost::serializer
		chrono

	Optimizer op;

	if (true)		op.setGenerationLimit(100);
	else			op.setTimeLimit(chrono::hours(4));

	op.setOutPutDir(filesystem::directory);

	if (sync) {
		op.run();					// blocking
	}
	else {
		op.async_run(callback);		// non-blocking

		while (isStillTraining) {
			
		}
	}

	/////////////////////////////////////////////////////////////////

	// *** Consider using a map<int, weights> for population that way the weights
	// will always be sorted
	vector<Weights> population;
	vector<int>	 scores;
	vector<pair<weights, int>> populationScorePairs;		// use this instead
	pair<weights, int> allTimeBest;

	for (int gen = 0; gen < generationLimit; gen++) {
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

	// Assumes mom.first.size() == dad.first.size() and both are > 0
	pair<weights, int> makeBaby(const pair<weights, int> & mom, const pair<weights, int> & dad) {
		pair<weights, int> child;
		child.weights.resize(mom.weights.size());

		// pick a random number between 0 and weights.size();
		uniform_int_distribution<int> uniDist(0, weights.size();
		int splitPoint = uniDist(generator);

		// --- cross-breed ---
		copy(mom.weights.begin(), mom.weights.begin() + splitPoint, child.begin());
		copy(dad.weights.begin() + splitPoint, dad.weights.end(), child.begin() + splitPoint);

		// --- add a small variance to a randomly selected weight ---
		normal_distribution<> normDist(0, 0.1);

		int weightIndex = uniDist(generator);

		child.weights.at(weightIndex) += normDist(generator);

	}

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
		class Optimizer
		{
		public:

		};
	}
}