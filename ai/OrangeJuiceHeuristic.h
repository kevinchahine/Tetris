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
		//	- maximum height
		// weights = { w1, w2, w3 }
		class AI_API OrangeJuiceHeuristic : public HeuristicBase
		{
		public:
			OrangeJuiceHeuristic() :
				HeuristicBase({ -1.0f, -1.0f, -1.0f }) {}
			OrangeJuiceHeuristic(const OrangeJuiceHeuristic&) = default;
			OrangeJuiceHeuristic(OrangeJuiceHeuristic&&) noexcept = default;
			virtual ~OrangeJuiceHeuristic() noexcept = default;
			OrangeJuiceHeuristic& operator=(const OrangeJuiceHeuristic&) = default;
			OrangeJuiceHeuristic& operator=(OrangeJuiceHeuristic&&) noexcept = default;

			virtual float calc(const core::Board& board) const override;

		private:
		};
	}
}
