#include "pch.h"
#include "TetrominoO.h"

namespace tetris
{
	namespace core
	{
		TetrominoO::TetrominoO() :
			TetrominoBase(2, 2)
		{
			at(0, 0) = O;
			at(0, 1) = O;
			at(1, 0) = O;
			at(1, 1) = O;
		}
	}
}