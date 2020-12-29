#include "pch.h"
#include "PineappleSlushy.h"

namespace tetris
{
	namespace ai
	{
		float tetris::ai::PineappleSlushy::calc(const tetris::core::Board & board) const
		{
			int nHoles = 0;
			int sittingCells;
			int sumOfAllHeights;
			int bumpyness;
			int clearableLines;
			int wells;

			return
				nHoles * m_weights.at(0) +
				sittingCells * m_weights.at(1) +
				sumOfAllHeights * m_weights.at(2) +
				bumpyness * m_weights.at(3) +
				clearableLines * m_weights.at(4) +
				wells * m_weights.at(5);
		}
	}
}