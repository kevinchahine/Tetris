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

<<<<<<< HEAD
=======
			void setCallback(std::function<void(const Move & move)>&& callback) { m_callback = std::move(callback); }

			virtual std::unique_ptr<ControllerBase> clone() = 0;

		protected:
			std::function<void(const Move& move)> m_callback;

>>>>>>> 8dcf789 (index on develop: bf3e42d Added method to resume from saved training state)
		};
	}
}
