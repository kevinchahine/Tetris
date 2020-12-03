#pragma once

#include "DisplayBase.h"

namespace tetris
{
	namespace core
	{
		class ColoredConsoleDisplay : public DisplayBase
		{
		public:

			virtual void rasterize(const Game& game) override;

			virtual void show() override;

		};
	}
}
