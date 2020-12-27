#pragma once

#include <vector>
#include <tuple>

namespace tetris
{
	namespace ai
	{
		namespace optimizers
		{
			class Individual : public std::pair<int, std::vector<float>>
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

				friend std::ostream & operator<<(std::ostream & os, const Individual & individual);
			};
		}
	}
}

