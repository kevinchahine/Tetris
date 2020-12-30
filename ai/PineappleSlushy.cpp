#include "pch.h"
#include "PineappleSlushy.h"

using namespace std;

namespace tetris
{
	namespace ai
	{
		float tetris::ai::PineappleSlushy::calc(const tetris::core::Board & board) const
		{
			int nHoles = 0;
			int sittingCells = 0;
			int sumOfAllHeights = 0;
			int bumpyness = 0;
			int clearableLines = 0;
			int wells = 0;

			return
				nHoles * m_weights.at(0) +
				sittingCells * m_weights.at(1) +
				sumOfAllHeights * m_weights.at(2) +
				bumpyness * m_weights.at(3) +
				clearableLines * m_weights.at(4) +
				wells * m_weights.at(5);
		}

		unique_ptr<HeuristicBase> PineappleSlushy::clone() const
		{
			return make_unique<PineappleSlushy>(*this);
		}
	}
}