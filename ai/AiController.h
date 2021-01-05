#pragma once

#include "ai.h"
#include "HeuristicBase.h"

#include <Tetris/core/Game.h>
#include <Tetris/core/ControllerBase.h>

#include <memory>
#include <queue>

#include <iocolor/iocolor.h>

namespace tetris
{
	namespace ai
	{
		class AI_API AiController : public core::ControllerBase
		{
		public:
			AiController() = default;
			AiController(const AiController & aiController);
			AiController(AiController &&) noexcept = default;
			virtual ~AiController() noexcept = default;
			AiController & operator=(const AiController &);
			AiController & operator=(AiController &&) noexcept = default;

			std::unique_ptr<HeuristicBase>& heuristicPtr() { return m_heuristicPtr; }
			const std::unique_ptr<HeuristicBase>& heuristicPtr() const { return m_heuristicPtr; }

		protected:
			float calcHeuristic(const core::Board& board, const core::TetrominoBase& falling) const;

		protected:
			std::unique_ptr<HeuristicBase> m_heuristicPtr;

			std::deque<core::Move> m_moveSequence;
		};
	}
}

