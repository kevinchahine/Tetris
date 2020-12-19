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

			return -nHoles;
		}
	}
}