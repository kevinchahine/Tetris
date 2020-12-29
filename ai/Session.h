#pragma once

#include "ai.h"

#include <Tetris/ai/Individual.h>

#include <iostream>
#include <chrono>
#include <vector>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>

namespace tetris
{
	namespace ai
	{
		class AI_API Session
		{
		public:

			//template<typename Archive>
			//void serialize(Archive & ar, unsigned int version);

			template<typename Archive>
			void save(Archive & ar, const unsigned int version) const;

			template<typename Archive>
			void load(Archive & ar, const unsigned int version);

			friend std::ostream & operator<<(std::ostream & os, const Session & session)
			{
				os << "Gen: " << session.generationNumber << "/" << session.generationNumber << ' '
					<< "Time Elapsed: " << session.timeElapsed.count() << "/" << session.timeLimit.count() << ' '
					<< "Random Seed: " << session.randomSeed << ' '
					<< "All Time Best: " << session.allTimeBest << '\n'
					<< "population:\n";

				for (const optimizers::Individual & i : session.population) {
					os << i << '\n';
				}

				return os;
			}

		public:
			//boost::serialization::access;

			int generationNumber = 0;
			int generationLimit = 0;

			std::chrono::seconds timeLimit = std::chrono::seconds(0);
			std::chrono::seconds timeElapsed = std::chrono::seconds(0);

			std::vector<tetris::ai::optimizers::Individual> population;
			tetris::ai::optimizers::Individual allTimeBest;

			int randomSeed = 0;
		};

// ------------------------------------ TEMPLATE DEFINITIONS ------------------

		//template<typename Archive>
		//void Session::serialize(Archive & ar, unsigned int version)
		//{
		//	ar & generationNumber;
		//	ar & generationLimit;
		//
		//	//ar & timeLimit;
		//	//ar & timeElapsed;
		//
		//	ar & population;
		//	ar & allTimeBest;
		//}

		template<typename Archive>
		void Session::save(Archive & ar, const unsigned int version) const
		{
			ar << generationNumber;
			ar << generationLimit;

			ar << timeLimit.count();
			ar << timeElapsed.count();

			ar << population;
			ar << allTimeBest;

			ar << randomSeed;
		}

		template<typename Archive>
		void Session::load(Archive & ar, const unsigned int version)
		{
			ar >> generationNumber;
			ar >> generationLimit;
			   
			const long long timeLimitCount;
			const long long timeElapsedCount;

			ar >> timeLimitCount;
			ar >> timeElapsedCount;

			timeLimit = chrono::seconds(timeLimitCount);
			timeElapsed = chrono::seconds(timeElapsedCount);
			   
			ar >> population;
			ar >> allTimeBest;

			ar >> randomSeed;
		}
	}
}

