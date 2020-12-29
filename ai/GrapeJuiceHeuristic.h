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
		// weights = { w1, w2, w3 }
		class AI_API GrapeJuiceHeuristic : public HeuristicBase
		{
		public:
			GrapeJuiceHeuristic() :
				HeuristicBase({ -1.0f, -1.0f, -1.0f, -1.0f }) {}
			GrapeJuiceHeuristic(float nHoles, float sittingCells, float sumOfHeights) :
				HeuristicBase({ nHoles, sittingCells, sumOfHeights }) {}
			GrapeJuiceHeuristic(const GrapeJuiceHeuristic&) = default;
			GrapeJuiceHeuristic(GrapeJuiceHeuristic&&) noexcept = default;
			virtual ~GrapeJuiceHeuristic() noexcept = default;
			GrapeJuiceHeuristic& operator=(const GrapeJuiceHeuristic&) = default;
			GrapeJuiceHeuristic& operator=(GrapeJuiceHeuristic&&) noexcept = default;

			virtual float calc(const core::Board & board) const override;

			virtual std::unique_ptr<HeuristicBase> clone() override;

		};
	}
}
