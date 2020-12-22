#include "pch.h"
#include "CppUnitTest.h"

#include <Tetris/core/Game.h>
#include <Tetris/core/Tetrominos.hpp>

#include <Tetris/ai/FrontierStack.h>
#include <Tetris/ai/SolutionSequence.h>

#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace tetris::core;
using namespace tetris::ai;
using namespace std;

namespace tetris
{
	namespace unit_tests
	{
		TEST_CLASS(TestFrontierStack)
		{
		public:

			TEST_METHOD(empty)
			{
				FrontierStack<string> frontier;

				Assert::IsTrue(frontier.empty());
				
				frontier.push("%");

				Assert::IsFalse(frontier.empty());

				frontier.push("#$");

				Assert::IsFalse(frontier.empty());

				frontier.pop();

				Assert::IsFalse(frontier.empty());

				frontier.pop();

				Assert::IsTrue(frontier.empty());
			}
			TEST_METHOD(size)
			{
				FrontierStack<string> frontier;

				Assert::AreEqual<size_t>(frontier.size(), 0);

				frontier.push("asdf");

				Assert::AreEqual<size_t>(frontier.size(), 1);

				frontier.push("asdf");	// size should stay the same

				Assert::AreEqual<size_t>(frontier.size(), 1);

				frontier.push("ASDF");

				Assert::AreEqual<size_t>(frontier.size(), 2);

				frontier.pop();

				Assert::AreEqual<size_t>(frontier.size(), 1);

				frontier.pop();

				Assert::AreEqual<size_t>(frontier.size(), 0);
			}

			TEST_METHOD(top)
			{
				FrontierStack<string> frontier;

				frontier.push("asdf");

				Assert::AreEqual<string>(frontier.top(), "asdf");

				frontier.push("fff");

				Assert::AreEqual<string>(frontier.top(), "fff");
			}

			TEST_METHOD(contains)
			{
				FrontierStack<string> frontier;

				Assert::IsFalse(frontier.contains("asdf"));

				frontier.push("asdf");

				Assert::IsTrue(frontier.contains("asdf"));
				Assert::IsFalse(frontier.contains("fff"));

				frontier.push("apple");

				Assert::IsTrue(frontier.contains("asdf"));
				Assert::IsTrue(frontier.contains("apple"));
				Assert::IsFalse(frontier.contains("fff"));

				frontier.pop();

				Assert::IsTrue(frontier.contains("asdf"));
				Assert::IsFalse(frontier.contains("apple"));
				Assert::IsFalse(frontier.contains("fff"));

				frontier.pop();

				Assert::IsFalse(frontier.contains("asdf"));
				Assert::IsFalse(frontier.contains("apple"));
				Assert::IsFalse(frontier.contains("fff"));

			}

			TEST_METHOD(usingSolutionSequence)
			{
				FrontierStack<SolutionSequence> frontier;

				TetrominoI t;
				t.position() = cv::Point(4, 4);

				SolutionSequence seq(t);

				seq.moveDown();
				seq.moveDown();
				seq.moveLeft();
				seq.moveRight();

				Assert::IsFalse(frontier.contains(seq));

				frontier.push(seq);

				Assert::IsTrue(frontier.contains(seq));

				seq.moveDown();

				Assert::IsFalse(frontier.contains(seq));

				frontier.push(seq);

				Assert::IsTrue(frontier.contains(seq));


			}
		};
	}
}
