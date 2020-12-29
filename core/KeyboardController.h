#pragma once

#include "core.h"
#include "ControllerBase.h"

#include <thread>

namespace tetris
{
	namespace core
	{
		class CORE_API KeyboardController : public ControllerBase
		{
		public:
			KeyboardController();
			virtual ~KeyboardController() noexcept;
			
			virtual void reset() override;

			virtual Move getInput(const Game & game) override;

			virtual std::unique_ptr<ControllerBase> clone() override;

		private:
			// Stops ongoing thread
			void stopAsyncOp();

			void startAsyncOp();

		private:
			std::thread myThread;
			bool isMessageIn = false;
			Move input;
			bool stopFlag = false;
		};
	}
}
