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
		//	- wells	(3+ cells deep)
		// weights = { w1, w2, w3, v4 }
		class AI_API AppleCiderHeuristic : public HeuristicBase
		{
		public:
			AppleCiderHeuristic() :
				HeuristicBase({ -1.0f, -1.0f, -1.0f, -1.0f }) {}
			AppleCiderHeuristic(float nHoles, float sittingCells, float sumOfAllHeights, float nWells) :
				HeuristicBase({ nHoles, sittingCells, sumOfAllHeights, nWells }) {}
			AppleCiderHeuristic(const AppleCiderHeuristic&) = default;
			AppleCiderHeuristic(AppleCiderHeuristic&&) noexcept = default;
			virtual ~AppleCiderHeuristic() noexcept = default;
			AppleCiderHeuristic& operator=(const AppleCiderHeuristic&) = default;
			AppleCiderHeuristic& operator=(AppleCiderHeuristic&&) noexcept = default;

			virtual float calc(const core::Board& board) const override;

			virtual std::unique_ptr<HeuristicBase> clone() const override;

			virtual std::string name() override;

		};
	}
}
