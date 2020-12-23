#include "pch.h"
#include "AiController.h"

using namespace std;
using namespace tetris::core;

namespace tetris
{
	namespace ai
	{
		float AiController::calcHeuristic(const core::Board& board, const TetrominoBase& falling) const
		{
			const_cast<Board&>(board).pasteAt(falling);

			float heur = m_heuristicPtr->calc(board);

			const_cast<Board&>(board).removeFrom(falling);

			return heur;
		}
	}
}