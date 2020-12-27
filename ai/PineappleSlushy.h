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
		// weights = { w1, w2, w3, v4 }
		class AI_API PineappleSlushy : public HeuristicBase
		{
		public:
			PineappleSlushy(int nWeights = 0) :
				HeuristicBase({ -1.0f, -1.0f, -1.0f, -1.0f }) {}
			PineappleSlushy(const PineappleSlushy&) = default;
			PineappleSlushy(PineappleSlushy&&) noexcept = default;
			virtual ~PineappleSlushy() noexcept = default;
			PineappleSlushy& operator=(const PineappleSlushy&) = default;
			PineappleSlushy& operator=(PineappleSlushy&&) noexcept = default;

			virtual float calc(const tetris::core::Board& board) const = 0;


		};
	}
}

