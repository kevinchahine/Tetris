#include "pch.h"
#include "GamePlayer.h"

// Include game classes (Model)
#include "Game.h"

// Include display classes (View)
#include "DisplayBase.h"

// Include controller and solver classes (Controller)
#include "ControllerBase.h"

// Include heuristics for ai controllers
#include <iostream>
#include <string>
#include <chrono>
#include <memory>

#include <iocolor/iocolor.h>

#pragma warning ( push, 3 )
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#pragma warning ( pop )

using namespace std;

namespace tetris
{
	namespace core
	{
		int GamePlayer::play(
			tetris::core::Game & game, 
			std::unique_ptr<ControllerBase>& controllerPtr, 
			const std::unique_ptr<DisplayBase>& displayPtr)
		{
			// Make sure we have a controller. We can't play without one
			if (controllerPtr == nullptr) {
				string message = "controllerPtr " + string(__FUNCTION__) + " is nullptr";
				throw std::exception(message.c_str());
			}

			// --- Set up Game (MODEL) ---
			game.awake();

			// --- Game Loop ---
			while (game.isGameOver() == false)
			{
				// Show board but only if we have a display
				if (displayPtr != nullptr) {
					displayPtr->rasterize(game);
					displayPtr->show();
					this_thread::sleep_for(chrono::milliseconds(33));
				}

				tetris::core::Move m = controllerPtr->getInput(game);
				game.update(m);
			}

			cout << iocolor::push()
				<< iocolor::setfg(iocolor::RED)
				<< "!!!Game Over!!!\n"
				<< iocolor::pop();

			if (displayPtr != nullptr) {
				displayPtr->rasterize(game);
				displayPtr->show();
				this_thread::sleep_for(chrono::milliseconds(33));
			}

			return game.scoreKeeper().getScore();
		}

	}
}
