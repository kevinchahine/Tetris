#include "pch.h"
#include "TetrominoZ.h"

namespace tetris
{
	namespace core
	{
		TetrominoZ::TetrominoZ() :
			TetrominoBase(3, 3)
		{
			at(0, 0) = Z;
			at(0, 1) = Z;
			at(1, 1) = Z;
			at(1, 2) = Z;
		}
	}
}