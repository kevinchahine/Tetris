#pragma once

#include "core.h"
#include "Game.h"

namespace tetris
{
	namespace core
	{
		class CORE_API DisplayBase
		{
		public:

			virtual void rasterize(const Game& game) = 0;

			virtual void show() = 0;

		};
	}
}