#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TimeWiseUnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(ProcessCommandTest)
		{
			TimeWiseLogic logic;
			std::string feedback;
			feedback= logic.processCommand("add testing only");
			Assert::AreEqual("SUCCESSFUL", feedback.c_str());
			TaskList taskList = logic.getTaskList();
			std::string taskDescription = (taskList.getTask(0)).getDescription();
			Assert::AreEqual("testing only", taskDescription.c_str());
		}

	};
}