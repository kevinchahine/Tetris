#pragma once

#include "ai.h"

#include <Tetris/core/AiController.h>

namespace tetris
{
	namespace ai
	{
		class AI_API DfsSolver : public core::AiController
		{
		public:
			virtual void reset() override;

			virtual core::Move getInput() override;

		protected:

			core::Move solve();

		};
	}
}
