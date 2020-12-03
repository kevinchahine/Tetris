#pragma once

#include "core.h"

#pragma warning (push, 3)
#include <boost/container/static_vector.hpp>
#pragma warning (pop)

#include "TetrominoBase.h"

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

			// Indicies of tetrominoes
			boost::container::static_vector<int, 7> indicies;
		};
	}
}