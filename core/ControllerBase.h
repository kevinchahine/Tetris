#pragma once

#include "core.h"

#include "Move.h"

namespace tetris
{
	namespace core
	{
		class CORE_API ControllerBase
		{
		public:
			virtual void reset() = 0;

			virtual Move getInput() = 0;
		};
	}
}
