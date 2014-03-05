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
			Assert::AreEqual("SUCCESS", feedback.c_str());
			TaskList& taskList = logic.getTaskList();
			int length = taskList.size();
			std::string taskDescription = (taskList.getTask(0)).getDescription();
			Assert::AreEqual("testing only", taskDescription.c_str());
		}

		TEST_METHOD(TaskTest)
		{
			Task newTask;
			newTask.setDescription("hello");
			newTask.setCategory("testing");
			newTask.setPriority(HIGH);
			Date startDate(28,2,2014);
			Date endDate(4,3,2014);
			newTask.setStartDate(startDate);
			newTask.setEndDate(endDate);
			ClockTime newTime(1200);
			newTask.setEndTime(newTime);
		}

		TEST_METHOD(AddCommandTest)
		{
			TaskList _taskList;
			Parser _parser;
			std::string commandLine = "add testing";
			Command* command;
			command = _parser.interpretCommand(commandLine);
			command->execute(_taskList);
			std::string taskDescription = (_taskList.getTask(0)).getDescription();
			Assert::AreEqual("testing", taskDescription.c_str());
			
		}

		TEST_METHOD(EditCommandTest) {
		}

	};
}