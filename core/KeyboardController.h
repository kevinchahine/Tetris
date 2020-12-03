#pragma once

#include "ControllerBase.h"

#include <thread>

namespace tetris
{
	namespace core
	{
		class KeyboardController : public ControllerBase
		{
		public:
			KeyboardController();
			virtual ~KeyboardController() noexcept;

			virtual void reset() override;

			virtual Move getInput() override;

		private:
			// Stops ongoing thread
			void stopAsyncOp();

			void initAsyncOp();

		private:
			std::thread myThread;
			bool isMessageIn = false;
			Move input;
			bool stopFlag = false;
		};
	}
}
