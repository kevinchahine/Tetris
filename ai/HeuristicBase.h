#pragma once

#include "ai.h"

#include <Tetris/core/Board.h>

#include <stdint.h>
#include <vector>

namespace tetris
{
	namespace ai
	{
		class AI_API HeuristicBase
		{
		public:
			HeuristicBase(int nWeights = 0) :
				m_weights(nWeights, 1.0f) {}
			HeuristicBase(std::initializer_list<float> initList) :
				m_weights(initList) {}
			HeuristicBase(const HeuristicBase&) = default;
			HeuristicBase(HeuristicBase&&) noexcept = default;
			virtual ~HeuristicBase() noexcept = default;
			HeuristicBase& operator=(const HeuristicBase&) = default;
			HeuristicBase& operator=(HeuristicBase&&) noexcept = default;

			virtual float calc(const tetris::core::Board& board) const = 0;

			std::vector<float>& weights() { return m_weights; }
			const std::vector<float>& weights() const { return m_weights; }

			virtual std::unique_ptr<HeuristicBase> clone() = 0;

		protected:
			std::vector<float> m_weights;
		};
	}
}
