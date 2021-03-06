#include "pch.h"
#include "OrangeJuiceHeuristic.h"
#include "HeuristicHelpers.h"

using namespace std;

namespace tetris
{
	namespace ai
	{
		float OrangeJuiceHeuristic::calc(const core::Board& board) const
		{
			// --- Count the number of holes in board ---
			int nHoles = countHoles(board);

			// --- Count the number of cells above each hole ---
			// Cells that sit above multiple holes count that many times more ---
			int nSitting = countSittingCells(board);

			// --- Find altitude of the highest cell ---
			int height = maxHeight(board);

			// --- Calculate linear combination ---
			return 
				nHoles * m_weights.at(0) +
				nSitting * m_weights.at(1) +
				height * m_weights.at(2);
		}
	}
}