#pragma once

#include "ai.h"

#include <iostream>
#include <vector>
#include <tuple>
#include <iomanip>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

namespace tetris
{
	namespace ai
	{
		namespace optimizers
		{
			class AI_API Individual : public std::pair<int, std::vector<float>>
			{
			public:
				Individual() = default;
				Individual(size_t count, float value = 0.0f);
				Individual(const Individual&) = default;
				Individual(Individual&&) noexcept = default;
				~Individual() noexcept = default;
				Individual& operator=(const Individual&) = default;
				Individual& operator=(Individual&&) noexcept = default;

				bool operator<(const Individual & right);
				bool operator>(const Individual & right);
				bool operator<=(const Individual & right);
				bool operator>=(const Individual & right);
				bool operator==(const Individual & right);
				bool operator!=(const Individual & right);

				const int & score() const { return this->first; }
				int & score() { return this->first; }

				const std::vector<float> & weights() const { return this->second; };
				std::vector<float> & weights() { return this->second; };

				friend std::ostream & operator<<(std::ostream & os, const Individual & individual) {
					auto osflags = os.flags();

					os << "score: " << std::setw(6) << individual.score()
						<< " weights: ";

					os << std::setprecision(3);
					for (float w : individual.weights()) {
						os << std::setw(8) << w;
					}

					os.flags(osflags);

					return os;
				}

			private:
				friend class boost::serialization::access;

				template<typename Archive>
				void serialize(Archive & ar, const unsigned int version);
			};

			template<typename Archive>
			void Individual::serialize(Archive & ar, unsigned int version)
			{
				///auto & super = static_cast<std::pair<int, std::vector<float>>>(*this);
				///ar & super;

				ar & this->score();
				ar & this->weights();
			}
		}
	}
}

