#pragma once

#include "ai.h"
#include <Tetris/ai/AiController.h>

namespace tetris
{
	namespace ai
	{
		class AI_API RandomSolver : public ai::AiController
		{
		public:
			RandomSolver() = default;
			RandomSolver(const RandomSolver &);
			RandomSolver(RandomSolver &&) noexcept = default;
			virtual ~RandomSolver() noexcept = default;
			RandomSolver & operator=(const RandomSolver &);
			RandomSolver & operator=(RandomSolver &&) noexcept = default;

			virtual void reset() override;

			virtual core::Move getInput(const core::Game & game) override;

			virtual std::unique_ptr<ControllerBase> clone() override;

		protected:

		};
	}
}

