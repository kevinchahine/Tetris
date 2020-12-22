#pragma once

#include "core.h"
#include "Matrix.h"
#include "Move.h"

#include <stdint.h>

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

		protected:
			cv::Point m_position;
		};
	}
}