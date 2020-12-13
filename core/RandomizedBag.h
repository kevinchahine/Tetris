#pragma once

#pragma warning (disable: 4251)

#include "core.h"
#include "TetrominoBase.h"

#include <iostream>
#include <random>
#include <chrono>

#pragma warning (push, 3)
#include <boost/container/static_vector.hpp>
#pragma warning (pop)

namespace tetris
{
	namespace core
	{
		class CORE_API RandomizedBag
		{
		public:
			const TetrominoBase& nextTetromino();

		private:
			void fillAndShuffle();

			void clear();

			bool empty();

			void pop();

		private:

			// Indicies of tetrominoes in our bag
			boost::container::static_vector<int, 7> indicies;
		};
	}
}