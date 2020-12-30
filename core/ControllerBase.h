#pragma once

#include "core.h"

#include "Move.h"
#include "Game.h"

#include <functional>
#include <memory>

namespace tetris
{
	namespace core
	{
		// --- Forward Declarations ---
		class Game;
		
		class CORE_API ControllerBase
		{
		public:
			virtual void reset() = 0;

			virtual Move getInput(const Game & game) = 0;

			virtual std::unique_ptr<ControllerBase> clone() = 0;
		};
	}
}
