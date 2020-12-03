#pragma once

#include "core.h"
#include "DisplayBase.h"

namespace tetris
{
	namespace core
	{
		class CORE_API ColoredConsoleDisplay : public DisplayBase
		{
		public:

			virtual void rasterize(const Game& game) override;

			virtual void show() override;

		};
	}
}
