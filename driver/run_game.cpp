#include "run_game.h"

#include <iostream>
#include <string>
#include <chrono>
#include <memory>

#include <iocolor/iocolor.h>

#pragma warning ( push, 3 )
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#pragma warning ( pop )

// Include game classes (Model)
#include <Tetris/core/Game.h>
#include <Tetris/core/Tetrominos.hpp>

// Include display classes (View)
#include <Tetris/core/DisplayBase.h>
#include <Tetris/core/ColoredConsoleDisplay.h>
#include <Tetris/core/GraphicalDisplay.h>

// Include controller and solver classes (Controller)
#include <Tetris/core/Controllers.hpp>
#include <Tetris/ai/AiController.h>
#include <Tetris/ai/Solvers.hpp>

// Include heuristics for ai controllers
#include <Tetris/ai/Heuristics.hpp>

#include <Tetris/core/GamePlayer.h>

using namespace std;

void tetris::driver::runGame()
{
	tetris::core::Game game;
	game.awake();

	// --- Set up Display (VIEW) ---
	unique_ptr<tetris::core::DisplayBase> displayPtr =
		//make_unique<tetris::core::ColoredConsoleDisplay>();
		make_unique<tetris::core::GraphicalDisplay>();
		//nullptr;

	// --- Set up controller (CONTROLLER) ---
	unique_ptr<tetris::core::ControllerBase> controllerPtr =
		//make_unique<tetris::core::KeyboardController>();
		make_unique<tetris::ai::DfsSolver>();
		//make_unique<tetris::ai::RandomSolver>();
		//make_unique<tetris::ai::DropSolver>();

	{
		tetris::ai::AiController * ptr = dynamic_cast<tetris::ai::AiController*>(controllerPtr.get());

		if (ptr != nullptr) {
			ptr->heuristicPtr() =
				//make_unique<tetris::ai::HolyHeuristic>();
				//make_unique<tetris::ai::OrangeJuiceHeuristic>();
				//make_unique<tetris::ai::GrapeJuiceHeuristic>();
				make_unique<tetris::ai::AppleCiderHeuristic>();
				//make_unique<tetris::ai::PineappleSlushy>();

			ptr->heuristicPtr()->weights() =
				//{ -2.5, -0.815, -1.5, -0.558 };
				//{ -0.551, -0.0705, -0.149, -0.72 };	// score: 41400 (AppleCider)
				//{ -1.64, -0.136, -0.465, -1.83 };		// score: 27160 (AppleCider)
				//{ -1.64, -0.136, -0.465, -1.83 };		// score: 27160 (AppleCider)
				{ -1.73, -0.112, -1.3, 0.933 };			// score: 12520 (AppleCider)
		}
	}

	controllerPtr->reset();

	// --- Play the game ---
	tetris::core::GamePlayer gamePlayer;

	cout << "Playing game...";
	int score = gamePlayer.play(game, controllerPtr, displayPtr);
	cout << "Score: " << score << '\n';
}
