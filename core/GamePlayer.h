#pragma once

#include "core.h"

#include <memory>

namespace tetris
{
	namespace core
	{
		// Forward Declarations
		class Game;
		class ControllerBase;
		class DisplayBase;

		class CORE_API GamePlayer
		{
		public:

			int play(
				tetris::core::Game & game, 
				std::unique_ptr<ControllerBase> & controllerPtr, 
				const std::unique_ptr<DisplayBase> & displayPtr);


		};
	}
}
