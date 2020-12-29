#pragma once

#include "ai.h"
#include "HeuristicBase.h"

namespace tetris
{
	namespace ai
	{
		// Heuristic that only counts holes 
		// weights = { nHoles }
		class AI_API HolyHeuristic : public HeuristicBase
		{
		public:
			HolyHeuristic() :
				HeuristicBase(1) {}
			GrapeJuiceHeuristic(float nHoles) :
				HeuristicBase({ nHoles }) {}
			HolyHeuristic(const HolyHeuristic&) = default;
			HolyHeuristic(HolyHeuristic&&) noexcept = default;
			virtual ~HolyHeuristic() noexcept = default;
			HolyHeuristic& operator=(const HolyHeuristic&) = default;
			HolyHeuristic& operator=(HolyHeuristic&&) noexcept = default;

			virtual float calc(const core::Board& board) const override;

		private:
		};
	}
}
