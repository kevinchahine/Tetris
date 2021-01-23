#include "ClParser.h"

#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>		// for strlen()
#include <numeric>

#include <boost/program_options.hpp>	// Break this down into only the headers we need

#include <iocolor/iocolor.h>

#include <Tetris/core/GamePlayer.h>
#include <Tetris/ai/Heuristics.hpp>

using namespace std;
namespace po = boost::program_options;

namespace tetris
{
	namespace driver
	{
		ClParser::ClParser() :
			m_displayPtr(make_unique<tetris::core::ColoredConsoleDisplay>()),
			m_controllerPtr(make_unique<tetris::ai::DfsSolver>()),
			m_heuristicPtr(make_unique<tetris::ai::AppleCiderHeuristic>())
		{
			dynamic_cast<tetris::ai::AiController*>(m_controllerPtr.get())->heuristicPtr() =
				m_heuristicPtr->clone();

			switchesDesc.add_options()
				("help,h", "Show help")
				//("r,record", "Record video output (only works with displays that support this feature")
				("cl,c", "use command line display")
				("gui,g", "use a build-in graphical display")
				("train,t", "run training algorithm instead of playing a game")
				("play,p", "run game instead of training algorithm")
				("list,l", "List controllers and heuristics")
				;
			
			optionsDesc.add_options()
				("controller", po::value<string>()->default_value("dfs"), "Determines what controller to use. Use --list to see options")
				("heuristic", po::value<string>()->default_value("applecider"), "Determines what heuristic to use. Only applies to AiControllers. Use --list to see options.")
				("display", po::value<string>()->default_value("gui"), "Determines what display to use. Use --list to see options.")
				("generations", po::value<int>()->implicit_value(100), "Sets generations limit. Only applies to training.")
				("population", po::value<int>()->implicit_value(10), "Sets population size of each generation. Only applies to training.")
				("time-limit", po::value<int>()->implicit_value(10'000), "Time limit in seconds, Sets time limit for training. Only applies to training.")
				("out-dir", po::value<string>()->default_value("."), "Sets out directory for training progess backups. Only applies to training")
				("continue", po::value<string>()->default_value("."), "Specifies which directory training progress was saved in. Only applies to training.")
				("seed", po::value<int>(), "Sets random seed for more controlled games.")
				;

			// Add positional parameters that allow specifying heuristic weights to the heuristic option

			// Combine all descriptions into 1
			desc.add(switchesDesc);
			desc.add(optionsDesc);
		}

		void ClParser::handle(int argc, char ** argv)
		{
			// 1.) --- Set options style ---
			namespace style = boost::program_options::command_line_style;

			cout << iocolor::push();

			int git_style =
				style::unix_style |
				style::allow_guessing |			// allows abbreviated spelling for long options
				style::allow_dash_for_short |	// 
				style::allow_long |
				style::short_allow_next |		// allows separation
				//style::case_insensitive
				0;

			po::variables_map vm;

			try {
				// 1.) --- Start by making arguments lowercase ---
				for (int i = 1; i < argc; i++) {	// (skip 1st argument: the path)
					char * arg = argv[i];

					transform(arg, arg + strlen(arg), arg, tolower);
				}

				po::store(
					po::command_line_parser(argc, argv)
					.options(desc)
					.style(git_style)
					.run(),
					vm);

				cout << "Print arguments: "
					<< vm.size() << ":\n";
				for (const auto v : vm) {
					cout << '\t' << v.first << " | " << v.second.as<string>() << '\n';
				}

				handleSwitches(vm);
				handleOptions(vm);

				// After switches and options have been handled, execute 
				// the game mode. ** See .setGameMode()
				if (m_gameMode != nullptr) {
					cout << iocolor::setfg(iocolor::LIGHTBLUE)
						<< "lets play!!!\n";
					m_gameMode();
				}
			}
			catch (po::error & poe) {
				cout << iocolor::setfg(iocolor::RED)
					<< "Caught exception: " << poe.what() << '\n'
					<< "USAGE: " << argv[0] << '\n'
					<< desc << '\n';
			}

			cout << iocolor::pop();
		}

		// ------------------------ SWITCHES ------------------------------

		void ClParser::handleSwitches(const boost::program_options::variables_map & vm)
		{
			if (vm.count("help"))	showHelp();
			if (vm.count("cl"))		setDisplay("cl");
			if (vm.count("gui"))	setDisplay("gui");
			if (vm.count("train"))	setGameMode("train");
			if (vm.count("play"))	setGameMode("play");
			if (vm.count("list"))	listOptions();

			//if (m_gameMode == nullptr) {
			//	setGameMode("play");
			//}
		}

		void ClParser::showHelp() const
		{
			cout << desc << '\n';	// Simple
		}

		void ClParser::listOptions() const
		{
			cout << iocolor::push();

			cout << iocolor::setfg(iocolor::YELLOW)
				<< "Controllers:\n"
				<< iocolor::setfg(iocolor::LIGHTGREEN)
				<< "\tKeyboard      Uses keyboard as controller.\n"
				<< "\tDFS           Ai Solver using a depth-first search. (Same as DFS1)\n"
				<< "\tDFS1          Depth-First Search involving only the falling piece. (same as DFS) (smart)\n"
				<< "\tDFS2          Depth-First Search involving falling piece and held piece. (More smart)\n"
				<< "\tDFS3          Depth-First Search involving falling, held and next piece. (Even more smart)\n"
				<< "\tDrop          Ai Solver using a simpler search algorithm involving spins\n"
				<< "\t              followed by lateral moves and ending with straight drops. (okay)\n"
				<< "\tRandom        Ai Solver that makes random moves (dumb).\n"
				<< '\n';

			cout << iocolor::setfg(iocolor::YELLOW)
				<< "Displays:\n"
				<< iocolor::setfg(iocolor::GREEN)
				<< "\tGUI           Show display on a graphical window. Needs opencv support.\n"
				<< "\tCL            Show display on command line.\n"
				<< '\n';

			cout << iocolor::setfg(iocolor::YELLOW)
				<< "Heuristics: (only applies to AI based controllers)\n"
				<< iocolor::setfg(iocolor::GREEN)
				<< "\tAppleCider (AC)\n"
				<< "\tGrapeJuice (GJ)\n"
				<< "\tHoly\n"
				<< "\tOrangeJuice (OJ)\n"
				<< "\tPineAppleSlushy (PA)"
				<< '\n';

			cout << iocolor::pop();
		}

		// ------------------------ OPTIONS -------------------------------

		void ClParser::handleOptions(const boost::program_options::variables_map & vm)
		{
			if (vm.count("controller"))		setController(vm["controller"].as<string>());
			if (vm.count("heuristic"))		setHeuristic(vm["heuristic"].as<string>());
			if (vm.count("display"))		setDisplay(vm["display"].as<string>());
			if (vm.count("generations"))	setGenerationLimit(vm["generations"].as<int>());
			if (vm.count("population"))		setPopulationSize(vm["population"].as<int>());
			if (vm.count("time-limit"))		setTimeLimit(vm["time-limit"].as<int>());
			if (vm.count("out-dir"))		setOutputDir(vm["out-dir"].as<string>());
			if (vm.count("continue"));
			if (vm.count("seed"));
		}

		void ClParser::setController(const string & controller)
		{
			// Shorten name
			const string & c = controller;

			if (c == "keyboard") {
				m_controllerPtr = make_unique<tetris::core::KeyboardController>();
			}
			else if (c == "dfs" || c == "dfs1") {
				m_controllerPtr = make_unique<tetris::ai::DfsSolver>();
			}
			else if (c == "dfs2") {
				m_controllerPtr = make_unique<tetris::ai::DfsSolver2>();
			}
			else if (c == "dfs3") {
				m_controllerPtr = make_unique<tetris::ai::DfsSolver3>();
			}
			else if (c == "drop") {
				m_controllerPtr = make_unique<tetris::ai::DropSolver>();
			}
			else if (c == "random") {
				m_controllerPtr = make_unique<tetris::ai::RandomSolver>();
			}
			else {
				printWarning("No controller was found that matches " + c);
			}
		}

		void ClParser::setHeuristic(const std::string & heuristic)
		{
			using namespace tetris::ai;

			// Shorten names
			const string & h = heuristic;
			auto & p = m_heuristicPtr;

			if (h == "applecider" || h == "apple" || h == "ac") {
				p = make_unique<AppleCiderHeuristic>();
			}
			else if (h == "grapejuice" || h == "grape" || h == "gj") {
				p = make_unique<GrapeJuiceHeuristic>();
			}
			else if (h == "holy") {
				p = make_unique<HolyHeuristic>();
			}
			else if (h == "orangejuice" || h == "orange" || h == "oj") {
				p = make_unique<OrangeJuiceHeuristic>();
			}
			else if (h == "pineappleslushy" || h == "pineapple" || h == "pa") {
				p = make_unique<PineappleSlushy>();
			}
			else {
				printWarning("No Heuristic was found that matches " + h);
			}
		}

		void ClParser::setDisplay(const string & display)
		{
			// Shorten name
			const string & d = display;

			if (d == "gui") {
				cout << "GUI\n";
				m_displayPtr = make_unique<tetris::core::GraphicalDisplay>();
			}
			else if (d == "cl") {
				cout << "CL\n";
				m_displayPtr = make_unique<tetris::core::ColoredConsoleDisplay>();
			}
			else {
				printWarning("No display was found that matches " + d);
			}
		}

		void ClParser::setGameMode(const std::string & mode)
		{
			// Shorten name
			const string & m = mode;

			if (m == "play") {
				m_gameMode = [&]() {
					this->playGame();
				};
			}
			else if (m == "train") {
				m_gameMode = [&]() {
					this->train();
				};
			}
			else {
				printWarning("No game mode was found that matches " + m);
			}
		}

		void ClParser::playGame()
		{
			// --- Model ---
			tetris::core::Game game;

			// --- View ---	
			// Nothing to do here

			// --- Controller ---
			// Make sure we have a controller
			if (m_controllerPtr == nullptr) {
				setController("dfs");	// Default to dfs
			}

			// Set heuristic but only if our controller is an AiController
			{
				// Down cast to AiController if possible
				tetris::ai::AiController * cPtr = dynamic_cast<tetris::ai::AiController*>(m_controllerPtr.get());

				// If cast was sucessfull, set its heuristic 
				if (cPtr != nullptr) {
					// (now we know that our controller is infact an AiController)

					// Make sure we have a heuristic
					if (m_heuristicPtr == nullptr) {
						throw std::exception("Heuristic was not specified. Ai controllers need to have a heuristic to work");
					}

					// Next set the controllers hueristic
					cPtr->heuristicPtr() = m_heuristicPtr->clone();
				}
			}

			// --- Play ---
			tetris::core::GamePlayer player;
			player.play(game, m_controllerPtr, m_displayPtr);
		}

		void ClParser::setGenerationLimit(int generationLimit)
		{
			if (m_trainingSessionPtr == nullptr) {
				m_trainingSessionPtr = make_unique<tetris::ai::Session>();
			}

			m_trainingSessionPtr->generationLimit = generationLimit;
		}

		void ClParser::setPopulationSize(int populationSize)
		{
			if (m_trainingSessionPtr == nullptr) {
				m_trainingSessionPtr = make_unique<tetris::ai::Session>();
			}

			m_trainingSessionPtr->population.resize(populationSize);
		}

		void ClParser::setTimeLimit(int timeLimit)
		{
			cout << __FUNCTION__ << " not implemented. Also figure out how to "
				<< "abstractify time into chrono durations\n";
		}

		void ClParser::setOutputDir(const string & outDir)
		{
			cout << __FUNCTION__ << " not implemented.\n";
		}

		void ClParser::setTrainingParams(const boost::program_options::variables_map & vm)
		{
			cout << __FUNCTION__ << " not implemented.\n";
		}

		void ClParser::train()
		{
			// --- Model ---
			tetris::ai::optimizers::Optimizer opt;

			// --- View --- (No view)

			// --- Controller ---
			// Make sure we have a controller
			if (m_controllerPtr == nullptr) {
				throw std::exception("AI Controller not set");
			}

			// Set heuristic but only if our controller is an AiController
			{
				// Down cast to AiController if possible
				tetris::ai::AiController * cPtr = dynamic_cast<tetris::ai::AiController*>(m_controllerPtr.get());

				// If cast was sucessfull, set its heuristic 
				if (cPtr == nullptr) {
					throw std::exception("Controller needs to be an Ai Controller.");
				}
				else {
					// *** Now we know our controller is infact an AiController ***

					// Make sure we have a heuristic
					if (m_heuristicPtr == nullptr) {
						throw std::exception("Heuristic was not specified. Ai controllers need to have a heuristic to work");
					}

					// Next set copy the controllers hueristic
					cPtr->heuristicPtr() = m_heuristicPtr->clone();

					// Set Ai Controller to Optimizer
					auto d = static_cast<ai::AiController*>(m_controllerPtr.release());
					unique_ptr<ai::AiController> aiPtr(d);
					opt.setAiController(move(aiPtr));
				}
			}

			// --- Train ---

			if (m_trainingSessionPtr == nullptr) {
				m_trainingSessionPtr = make_unique<ai::Session>();
			}

			//opt.resumeTraining(*m_trainingSessionPtr);
			opt.train();
		}

		void ClParser::printWarning(const std::string & message, std::ostream & os) const
		{
			cout << iocolor::push()
				<< iocolor::setfg(iocolor::RED)
				<< message << '\n'
				<< iocolor::pop();
		}
	}
}
