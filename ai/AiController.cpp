#include "pch.h"
#include "AiController.h"

using namespace std;
using namespace tetris::core;

namespace tetris
{
	namespace ai
	{
		AiController::AiController(const AiController & aiController) : 
			ControllerBase(aiController),
			m_heuristicPtr(aiController.m_heuristicPtr->clone()),
			m_moveSequence(aiController.m_moveSequence)
		{} 

		AiController & AiController::operator=(const AiController & aiController)
		{
			static_cast<ControllerBase&>(*this) = static_cast<const ControllerBase&>(aiController);
			m_heuristicPtr = aiController.m_heuristicPtr->clone();
			m_moveSequence = aiController.m_moveSequence;

			return *this;
		}

		float AiController::calcHeuristic(const core::Board& board, const TetrominoBase& falling) const
		{
			const_cast<Board&>(board).pasteAt(falling);

			float heur = m_heuristicPtr->calc(board);

			const_cast<Board&>(board).removeFrom(falling);

			return heur;
		}
	}
}