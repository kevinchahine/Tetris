#pragma once

#include "core.h"

#include "TetrominoBase.h"
#include "Move.h"

#include <boost/container_hash/hash.hpp>

namespace tetris
{
	namespace core
	{
		class CORE_API MoveStatePair
		{
		public:
			MoveStatePair() = default;
			MoveStatePair(const MoveStatePair&) = default;
			MoveStatePair(MoveStatePair&&) noexcept = default;
			~MoveStatePair() noexcept = default;
			MoveStatePair& operator=(const MoveStatePair&) = default;
			MoveStatePair& operator=(MoveStatePair&& pair) noexcept = default;
			//{
			//	this->move = pair.move;
			//	this->state = std::move(pair.state);
			//	return *this;
			//}
			
			MoveStatePair(Move move, const TetrominoBase & tetromino) :
				move(move),
				state(tetromino) {}

		public:
			Move move;

			// Destination of falling piece after making move
			TetrominoBase state;

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
	template<> struct hash<tetris::core::MoveStatePair>
	{
		size_t operator()(tetris::core::MoveStatePair const& p) const noexcept
		{
			/* This only will work for 64-bit */
			// --- Calculate hash of tetromino matrix ---
			// 16-bits for the tetromino 
			register size_t tetromino_hash = 0;
			const tetris::core::TetrominoBase& tetromino = p.state;
			
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
			
			//// --- Calculate hash of tetromino position ---
			//// 16-bits for the position of the tetromino (8-bit for x and 8-bit for y)
			//// [ x (8-bits) ][ y (8-bits) ]
			//register size_t position_hash = (tetromino.position().x << 8) | (tetromino.position().y);
			//
			//// --- Calculate hash of move ---
			//// 8-bits for the move
			//register size_t move_hash = p.move.getMove();
			//
			//// Full hash: MSB to LSB
			//// [ reserved (24-bits) ][ move_hash (8-bits) ][ tetromino_hash (16-bits) ][ x_hash (8-bits) ][ y_hash (8-bits) ]
			//register size_t hash = 
			//	(move_hash << 32) | 
			//	(tetromino_hash << 16) | 
			//	(position_hash << 0);
			//
			//return hash;

			size_t hash = 0;

			boost::hash_combine(hash, tetromino_hash);
			boost::hash_combine(hash, tetromino.position().x);
			boost::hash_combine(hash, tetromino.position().y);
			boost::hash_combine(hash, p.move.getMove());

			return hash;
		}
	};
}