#pragma once

#include "ai.h"

#include "HeuristicBase.h"

namespace tetris
{
	namespace ai
	{
		// Heuristic that counts:
		//	- holes 
		//	- occupied cells above the holes
		//	- sum of all height
		//	- bumpyness
		//	- clearable lines
		//	- wells	(3+ cells deep)
		// weights = { w1, w2, w3, w4, w5, w6 }
		class AI_API PineappleSlushy : public HeuristicBase
		{
		public:
			PineappleSlushy(int nWeights = 0) :
				HeuristicBase({ -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f }) {}
			PineappleSlushy(float nHoles, float sittingCells, float sumOfAllHeights, float bumpyness, float clearableLines, float wells) :
				HeuristicBase({ nHoles, sittingCells, sumOfAllHeights, bumpyness, clearableLines, wells }) {}
			PineappleSlushy(const PineappleSlushy&) = default;
			PineappleSlushy(PineappleSlushy&&) noexcept = default;
			virtual ~PineappleSlushy() noexcept = default;
			PineappleSlushy& operator=(const PineappleSlushy&) = default;
			PineappleSlushy& operator=(PineappleSlushy&&) noexcept = default;

			virtual float calc(const tetris::core::Board& board) const;

			virtual std::unique_ptr<HeuristicBase> clone() const override;

			virtual std::string name() override;

		};
	}
}

