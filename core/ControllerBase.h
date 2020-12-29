#pragma once

#include "core.h"

#include "Move.h"
#include "Game.h"

#include <functional>

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

		};
	}
}
