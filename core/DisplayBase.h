#pragma once

#include "Game.h"

namespace tetris
{
	namespace core
	{
		class DisplayBase
		{
		public:

			virtual void rasterize(const Game& game) = 0;

			virtual void show() = 0;

		};
	}
}