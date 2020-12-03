#include "pch.h"
#include "TetrominoBase.h"

#pragma warning( push, 3)
#include<opencv2/core.hpp>
#pragma warning( pop )

using namespace std;

namespace tetris
{
	namespace core
	{
		TetrominoBase::TetrominoBase() :
			Matrix{ cv::Mat::zeros(cv::Size(4, 4), CV_8UC1) }
		{
		}

		TetrominoBase::TetrominoBase(int nRows, int nCols) :
			Matrix{ cv::Mat::zeros(cv::Size{nCols, nRows}, CV_8UC1) }
		{
		}

		void TetrominoBase::spin()
		{
			cv::rotate(*this, *this, cv::ROTATE_90_COUNTERCLOCKWISE);
		}

		void TetrominoBase::unSpin()
		{
			cv::rotate(*this, *this, cv::ROTATE_90_CLOCKWISE);
		}
	}
}