#pragma once

#include "core.h"
#include "ControllerBase.h"
#include "Game.h"

namespace tetris
{
	namespace core
	{
		class CORE_API AiController : public ControllerBase
		{
		public:

			const Game*& gamePtr() { return m_gamePtr; }
			const Game* gamePtr() const { return m_gamePtr; }

		protected:
			// Non-owning
			// Does not need to be dereferenced
			const Game * m_gamePtr = nullptr;
		};
	}
}

