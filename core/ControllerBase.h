#pragma once

#include "core.h"

#include "Move.h"

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

			virtual Move getInput() = 0;

			void setCallback(std::function<void(const Move & move)>&& callback) { m_callback = std::move(callback); }

			const Game*& gamePtr() { return m_gamePtr; }
			const Game* gamePtr() const { return m_gamePtr; }

			const Game & game() const {
				if (m_gamePtr == nullptr) 
					throw std::exception("m_game was nullptr");

				return *m_gamePtr;
			}

		protected:
			std::function<void(const Move& move)> m_callback;

		private:
			// Non-owning
			// Does not need to be dereferenced
			const Game* m_gamePtr = nullptr;
		};
	}
}
