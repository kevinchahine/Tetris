#include "pch.h"
#include "Individual.h"

#include <iomanip>

using namespace std;

namespace tetris
{
	namespace ai
	{
		namespace optimizers
		{
			Individual::Individual(size_t count, float value) :
				std::pair<int, std::vector<float>>{ 0, std::vector<float>( count, value ) } {}

			bool Individual::operator<(const Individual & right)
			{
				return this->score() < right.score();
			}

			bool Individual::operator>(const Individual & right)
			{
				return this->score() > right.score();
			}

			bool Individual::operator<=(const Individual & right)
			{
				return this->score() <= right.score();
			}

			bool Individual::operator>=(const Individual & right)
			{
				return this->score() >= right.score();
			}

			bool Individual::operator==(const Individual & right)
			{
				return this->score() == right.score();
			}

			bool Individual::operator!=(const Individual & right)
			{
				return this->score() != right.score();
			}

		}
	}
}
