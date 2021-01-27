#include "pch.h"
#include "HolyHeuristic.h"
#include "HeuristicHelpers.h"

using namespace std;

namespace tetris
{
	namespace ai
	{
		float HolyHeuristic::calc(const core::Board& board) const
		{
			// --- Count the number of holes in board ---
			int nHoles = countHoles(board);

			return static_cast<float>(-nHoles);
		}

		std::unique_ptr<HeuristicBase> HolyHeuristic::clone() const
		{
			return make_unique<HolyHeuristic>(*this);
		}
		std::string HolyHeuristic::name()
		{
			return "Holy";
		}
	}
}