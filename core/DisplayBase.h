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
			// Sets board size in units of cells (not pixels)
			void setBoardSize(const cv::Size& boardSize) { m_boardSize = boardSize; }

			virtual void rasterize(const Game& game) = 0;

			virtual void show() = 0;

		protected:
			// Size of tetris board in units of cells (not pixels)
			cv::Size m_boardSize;
		};
	}
}