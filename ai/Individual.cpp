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

			std::ostream & operator<<(std::ostream & os, const Individual & individual)
			{
				auto osflags = os.flags();

				os << "score: " << setw(6) << individual.score()
					<< " weights: ";

				os << setprecision(3);
				for (float w : individual.weights()) {
					os << setw(8) << w;
				}

				os.flags(osflags);

				return os;
			}
		}
	}
}
