#pragma once

#include "Move.h"

namespace tetris
{
	namespace core
	{
		class ControllerBase
		{
		public:
			virtual void reset() = 0;

			virtual Move getInput() = 0;
		};
	}
}
