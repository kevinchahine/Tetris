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

			void setCallback(std::function<void(const Move & move)>&& callback) { m_callback = std::move(callback); }

		protected:
			std::function<void(const Move& move)> m_callback;

		};
	}
}
