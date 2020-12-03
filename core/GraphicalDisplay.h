#pragma once

#include <iostream>

#include "core.h"
#include "DisplayBase.h"

#pragma warning ( push, 3 )
#include <opencv2/core/mat.hpp>
#pragma warning ( pop )

namespace tetris
{
	namespace core
	{
		class CORE_API GraphicalDisplay : public DisplayBase
		{
		public:

			virtual void rasterize(const Game& game) override;

			virtual void show() override;

		protected:

			// Size of cell in pixels (length and width)
			cv::Size cellSize = cv::Size{ 30, 30 };

			cv::Mat m_base = cv::Mat::zeros(512, 512, CV_8UC3);

			cv::Mat m_heldPiece = cv::Mat::zeros(cellSize * 4, CV_8UC3);

			cv::Mat m_nextPiece = cv::Mat::zeros(cellSize * 4, CV_8UC3);

			cv::Mat m_image = cv::Mat::zeros(512, 512, CV_8UC3);
		};
	}
}