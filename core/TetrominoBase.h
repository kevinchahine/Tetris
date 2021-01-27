#pragma once

#include "core.h"
#include "Matrix.h"
#include "Move.h"

#include <stdint.h>

#include <boost/container_hash/hash.hpp>

namespace tetris
{
	namespace core
	{	
		// --- Forward Declarations ---
		class Board;

		// --- Constants ---
		const cv::Scalar RED{ 0, 0, 255 };
		const cv::Scalar PURPLE{ 255, 0, 255 };
		const cv::Scalar BLUE{ 255, 0, 0 };
		const cv::Scalar CYAN{ 255, 255, 128 };
		const cv::Scalar GREEN{ 0, 255, 0 };
		const cv::Scalar YELLOW{ 0, 255, 255 };
		const cv::Scalar ORANGE{ 64, 128, 255 };
		const cv::Scalar GRAY{ 128, 128, 128 };
		const cv::Scalar WHITE{ 255, 255, 255 };
		const cv::Scalar BLACK{ 0, 0, 0 };

		const cv::Scalar shades[] = {
			BLACK,
			CYAN,
			RED,
			PURPLE,
			BLUE,
			GREEN,
			YELLOW,
			ORANGE,
			GRAY,
			WHITE
		};

		// 4x4 cv::Mat 
		// element values:
		//	0 - empty cell
		//	x - shape identifier as a uint8_t (where x is non zero)
		//	See tetris::core::Matrix for possible values
		class CORE_API TetrominoBase : public Matrix
		{
		public:
			TetrominoBase();
			TetrominoBase(int nRows, int nCols);
			TetrominoBase(const TetrominoBase&) = default;
			TetrominoBase(TetrominoBase&&) noexcept = default;
			virtual ~TetrominoBase() noexcept = default;
			TetrominoBase& operator=(const TetrominoBase&) = default;
			TetrominoBase& operator=(TetrominoBase&&) noexcept = default;

			void spin();

			// A more accurate spin method that pushes tetromino away from walls 
			// if part of it ends up out of bounds
			void spin(const Board& board);

			void unSpin();

			void moveDown();

			void moveLeft();

			void moveRight();

			void moveUp();

			void move(Move m);

			void move(Move m, const Board& board);

			void show(const std::string& windowName = "Tetromino") const;

			cv::Point& position() { return m_position; }
			const cv::Point& position() const { return m_position; }

			bool operator==(const TetrominoBase & rhs) const
			{
				return *this != rhs;
			}

			bool operator!=(const TetrominoBase & rhs) const
			{
				if (m_position == rhs.m_position)							return true;
				if (static_cast<Matrix>(*this) == static_cast<Matrix>(rhs))	return true;

				return false;
			}

		protected:
			cv::Point m_position;
		};
	}
}

// custom specialization of std::hash injected in namespace std
namespace std
{
	// Only works if:
	//	- Tetromino is stored in some kind of 4x4 array
	//	- x and y coordinates of the Tetrominos postition are in the range [0, 255]
	template<> struct hash<tetris::core::TetrominoBase>
	{
		size_t operator()(tetris::core::TetrominoBase const& tetromino) const noexcept
		{
			register size_t tetromino_hash = 0;

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

			return hash;
		}
	};
}
