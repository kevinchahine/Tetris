#pragma once

#include "ai.h"

#include <Tetris/core/Move.h>
#include <Tetris/core/TetrominoBase.h>

#include <algorithm>
#include <iterator>
#include <memory>
#include <queue>

#include <boost/container_hash/hash.hpp>

// --- Forward Declarations ---
class tetris::core::Board;

namespace tetris
{
	namespace ai
	{
		class AI_API SolutionSequence
		{
		public:
			SolutionSequence() = default;
			SolutionSequence(const core::TetrominoBase& falling);
			SolutionSequence(core::TetrominoBase && falling);
			SolutionSequence(const SolutionSequence&) = default;
			SolutionSequence(SolutionSequence&&) noexcept = default;
			~SolutionSequence() noexcept = default;
			SolutionSequence& operator=(const SolutionSequence&) = default;
			SolutionSequence& operator=(SolutionSequence&&) noexcept = default;

			friend std::ostream& operator<<(std::ostream& os, const SolutionSequence& seq)
			{
				for (core::Move m : seq.sequence()) {
					os << m << '\t';
				}
				//std::ostream_iterator<core::Move> osIter(os, "\t");
				//
				//std::copy(seq.sequence().begin(), seq.sequence().end(), osIter);
			
				return os;
			}

			void moveDown();

			void moveLeft();

			void moveRight();

			void moveSpin(const core::Board & board);

			void move(core::Move move, const core::Board& board);

			const std::deque<core::Move>& sequence() const { return m_sequence; }
			const core::TetrominoBase& falling() const { return m_falling; }

		protected:
			std::deque<core::Move> m_sequence;

			core::TetrominoBase m_falling;
		};
	}
}

// custom specialization of std::hash injected in namespace std
namespace std
{
	// Only works if:
	//	- Tetromino is stored in some kind of 4x4 array
	//	- x and y coordinates of the Tetrominos postition are in the range [0, 255]
	//	- Move is stored as a single character (or a class containing a single character)
	//	- No other values contribute to the uniqueness of the MoveStatePair
	template<> struct hash<tetris::ai::SolutionSequence>
	{
		size_t operator()(tetris::ai::SolutionSequence const& s) const noexcept
		{
			register size_t tetromino_hash = 0;
			const tetris::core::TetrominoBase& tetromino = s.falling();

			int bitPos = 0;
			for (int row = 0; row < tetromino.rows; row++) {
				for (int col = 0; col < tetromino.cols; col++) {
					// Assign a 1 to the bit if cell is occupied
					// Assign a 0 to the bit if cell is unoccupied
					tetromino_hash |= (tetromino.at(row, col) != tetris::core::Matrix::EMPTY) << bitPos;

					// Increment bitPos 
					bitPos++;
				}
			}

			size_t hash = 0;

			boost::hash_combine(hash, tetromino_hash);
			boost::hash_combine(hash, tetromino.position().x);
			boost::hash_combine(hash, tetromino.position().y);
			//boost::hash_range(hash, s.sequence().begin(), s.sequence().end());

			return hash;
		}
	};
}

