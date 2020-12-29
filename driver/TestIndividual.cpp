#include "TestIndividual.h"

#include <Tetris/ai/Individual.h>

#include <iostream>
#include <sstream>
#include <string>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

using namespace std;

void tetris::driver::testIndividualSerialize()
{
	tetris::ai::optimizers::Individual individual;
	individual.score() = 555;
	individual.weights() = { 2, 3, 4, 5, 6 };

	stringstream ss;
	boost::archive::text_oarchive outAr{ ss };

	outAr << individual;

	cout << "Individual: " << ss.str() << '\n';

	tetris::ai::optimizers::Individual parsed;
	boost::archive::text_iarchive inAr{ ss };

	inAr >> parsed;

	cout << "Parsed: " << parsed.score() << " weights: ";
	for (auto w : parsed.weights()) {
		cout << w << ' ';
	}
	cout << "\n";

}
