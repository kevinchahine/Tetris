#pragma once

#include "ai.h"
#include "HeuristicBase.h"

#include <Tetris/core/Game.h>
#include <Tetris/core/ControllerBase.h>

#include <memory>
#include <queue>

namespace tetris
{
	namespace ai
	{
		class AI_API AiController : public core::ControllerBase
		{
		public:
			std::unique_ptr<HeuristicBase>& heuristicPtr() { return m_heuristicPtr; }
			const std::unique_ptr<HeuristicBase>& heuristicPtr() const { return m_heuristicPtr; }

		protected:
			std::unique_ptr<HeuristicBase> m_heuristicPtr;

			std::queue<core::Move> m_moveSequence;
		};
	}
}

