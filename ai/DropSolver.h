#pragma once

#include "ai.h"
#include <Tetris/core/AiController.h>

namespace tetris
{
	namespace ai
	{
		/*
		Solves by moving the falling piece left or right to its desired spot then dropping it 
		all the way down. Does use swaps and spins 
		*/
		class AI_API DropSolver : public core::AiController
		{
		public:
			virtual void reset() override;

			virtual core::Move getInput() override;

		protected:
			core::Move solve();

		};
	}
}
