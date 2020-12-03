#pragma once

#include "core.h"

#include <iostream>

#include <iocolor/iocolor.h>

namespace tetris
{
	namespace core
	{
		class CORE_API ScoreKeeper
		{
		public:
			void add(int points);

			friend std::ostream& operator<<(std::ostream& os, const ScoreKeeper& scoreKeeper);

		private:
			int score = 0;

			int turnNumber = 0;
		};
	}
}
