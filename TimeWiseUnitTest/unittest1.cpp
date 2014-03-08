#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TimeWiseUnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(CommandAddTest) {
			TaskList _taskList;
			std::vector<Command_Add*> commandToBeExecuted;
			ClockTime startTime(1200);
			ClockTime endTime(1600);
			Date startDate(10,3,2014);
			Date endDate(12,3,2014);
			commandToBeExecuted.push_back(new Command_Add);
			commandToBeExecuted[0]->setDescription("check for floating task without priority and cat");

			commandToBeExecuted.push_back(new Command_Add);
			commandToBeExecuted[1]->setDescription("check floating task with priority and cat");
			commandToBeExecuted[1]->setPriority(HIGH);
			commandToBeExecuted[1]->setCategory("test");

			commandToBeExecuted.push_back(new Command_Add);
			commandToBeExecuted[2]->setDescription("check deadline task without priority and cat");
			commandToBeExecuted[2]->setEndDate(endDate);
			commandToBeExecuted[2]->setEndTime(endTime);

			commandToBeExecuted.push_back(new Command_Add);
			commandToBeExecuted[3]->setDescription("check timed task without priority and cat");
			commandToBeExecuted[3]->setStartDate(startDate);
			commandToBeExecuted[3]->setStartTime(startTime);
			commandToBeExecuted[3]->setEndDate(endDate);
			commandToBeExecuted[3]->setEndTime(endTime);
			
			commandToBeExecuted[0]->execute(_taskList);
			Assert::AreEqual("check for floating task without priority and cat",_taskList.getTask(0)->getDescription().c_str());

			commandToBeExecuted[1]->execute(_taskList);
			Assert::AreEqual("check floating task with priority and cat",_taskList.getTask(1)->getDescription().c_str());
			Assert::AreEqual(static_cast<int>(HIGH),static_cast<int>(_taskList.getTask(1)->getPriority()));
			Assert::AreEqual("test",_taskList.getTask(1)->getTaskCategory().c_str());

			commandToBeExecuted[2]->execute(_taskList);
			Assert::AreEqual("check deadline task without priority and cat",_taskList.getTask(2)->getDescription().c_str());
			Assert::AreEqual("1600",_taskList.getTask(2)->getEndTime().toString().c_str());
			Assert::AreEqual("12 Mar 14",_taskList.getTask(2)->getEndDate().toString().c_str());

			commandToBeExecuted[3]->execute(_taskList);
			Assert::AreEqual("check timed task without priority and cat",_taskList.getTask(3)->getDescription().c_str());
			Assert::AreEqual("1600",_taskList.getTask(3)->getEndTime().toString().c_str());
			Assert::AreEqual("12 Mar 14",_taskList.getTask(3)->getEndDate().toString().c_str());
			Assert::AreEqual("1200",_taskList.getTask(3)->getStartTime().toString().c_str());
			Assert::AreEqual("10 Mar 14",_taskList.getTask(3)->getStartDate().toString().c_str());

		}

		TEST_METHOD(CommandDeleteTest) {
			TaskList _taskList;
			std::vector<Command_Add*> commandToBeExecuted;
			std::vector<Command_Delete*> commandToBeDeleted;
			ClockTime startTime(1200);
			ClockTime endTime(1600);
			Date startDate(10,3,2014);
			Date endDate(12,3,2014);
			commandToBeExecuted.push_back(new Command_Add);
			commandToBeExecuted[0]->setDescription("check for floating task without priority and cat");

			commandToBeExecuted.push_back(new Command_Add);
			commandToBeExecuted[1]->setDescription("check floating task with priority and cat");
			commandToBeExecuted[1]->setPriority(HIGH);
			commandToBeExecuted[1]->setCategory("test");

			commandToBeExecuted.push_back(new Command_Add);
			commandToBeExecuted[2]->setDescription("check deadline task without priority and cat");
			commandToBeExecuted[2]->setEndDate(endDate);
			commandToBeExecuted[2]->setEndTime(endTime);

			commandToBeExecuted.push_back(new Command_Add);
			commandToBeExecuted[3]->setDescription("check timed task without priority and cat");
			commandToBeExecuted[3]->setStartDate(startDate);
			commandToBeExecuted[3]->setStartTime(startTime);
			commandToBeExecuted[3]->setEndDate(endDate);
			commandToBeExecuted[3]->setEndTime(endTime);

			commandToBeDeleted.push_back(new Command_Delete);
			commandToBeDeleted[0]->setDeletionIndex(1);
			commandToBeDeleted.push_back(new Command_Delete);
			commandToBeDeleted[1]->setDeletionIndex(2);
			commandToBeDeleted.push_back(new Command_Delete);
			commandToBeDeleted[2]->setDeletionIndex(2);
			commandToBeDeleted.push_back(new Command_Delete);
			commandToBeDeleted[3]->setDeletionIndex(1);

			commandToBeExecuted[0]->execute(_taskList);
			commandToBeExecuted[1]->execute(_taskList);
			commandToBeExecuted[2]->execute(_taskList);
			commandToBeExecuted[3]->execute(_taskList);
			commandToBeDeleted[0]->execute(_taskList);
			Assert::AreEqual("check floating task with priority and cat",_taskList.getTask(0)->getDescription().c_str());
			Assert::AreEqual("check deadline task without priority and cat",_taskList.getTask(1)->getDescription().c_str());
			Assert::AreEqual("check timed task without priority and cat",_taskList.getTask(2)->getDescription().c_str());
			commandToBeDeleted[1]->execute(_taskList);
			Assert::AreEqual("check floating task with priority and cat",_taskList.getTask(0)->getDescription().c_str());
			Assert::AreEqual("check timed task without priority and cat",_taskList.getTask(1)->getDescription().c_str());
			commandToBeDeleted[2]->execute(_taskList);
			Assert::AreEqual("check floating task with priority and cat",_taskList.getTask(0)->getDescription().c_str());
			commandToBeDeleted[3]->execute(_taskList);
			Assert::AreEqual(0,_taskList.size());
		}

		TEST_METHOD(CommandClearTest) {
			TaskList _taskList;
			std::vector<Command_Add*> commandToBeExecuted;
			ClockTime startTime(1200);
			ClockTime endTime(1600);
			Date startDate(10,3,2014);
			Date endDate(12,3,2014);
			commandToBeExecuted.push_back(new Command_Add);
			commandToBeExecuted[0]->setDescription("check for floating task without priority and cat");

			commandToBeExecuted.push_back(new Command_Add);
			commandToBeExecuted[1]->setDescription("check floating task with priority and cat");
			commandToBeExecuted[1]->setPriority(HIGH);
			commandToBeExecuted[1]->setCategory("test");

			commandToBeExecuted.push_back(new Command_Add);
			commandToBeExecuted[2]->setDescription("check deadline task without priority and cat");
			commandToBeExecuted[2]->setEndDate(endDate);
			commandToBeExecuted[2]->setEndTime(endTime);

			commandToBeExecuted.push_back(new Command_Add);
			commandToBeExecuted[3]->setDescription("check timed task without priority and cat");
			commandToBeExecuted[3]->setStartDate(startDate);
			commandToBeExecuted[3]->setStartTime(startTime);
			commandToBeExecuted[3]->setEndDate(endDate);
			commandToBeExecuted[3]->setEndTime(endTime);

			Command_Clear* clear = new Command_Clear;
			clear->execute(_taskList);
			Assert::AreEqual(0,_taskList.size());

		}

		TEST_METHOD(CommandEditTest) {
			TaskList _taskList;
			std::vector<Command_Add*> commandToBeExecuted;
			ClockTime startTime(1200);
			ClockTime endTime(1600);
			Date startDate(10,3,2014);
			Date endDate(12,3,2014);
			commandToBeExecuted.push_back(new Command_Add);
			commandToBeExecuted[0]->setDescription("check for floating task without priority and cat");

			commandToBeExecuted.push_back(new Command_Add);
			commandToBeExecuted[1]->setDescription("check floating task with priority and cat");
			commandToBeExecuted[1]->setPriority(HIGH);
			commandToBeExecuted[1]->setCategory("test");

			commandToBeExecuted.push_back(new Command_Add);
			commandToBeExecuted[2]->setDescription("check deadline task without priority and cat");
			commandToBeExecuted[2]->setEndDate(endDate);
			commandToBeExecuted[2]->setEndTime(endTime);

			commandToBeExecuted.push_back(new Command_Add);
			commandToBeExecuted[3]->setDescription("check timed task without priority and cat");
			commandToBeExecuted[3]->setStartDate(startDate);
			commandToBeExecuted[3]->setStartTime(startTime);
			commandToBeExecuted[3]->setEndDate(endDate);
			commandToBeExecuted[3]->setEndTime(endTime);

			Command_Edit* edit = new Command_Edit;
			edit->setIndex(1);
			edit->setHeader("description");
			edit->setDescription("new description");
			edit->execute(_taskList);
			Assert::AreEqual("new description",_taskList.getTask(0)->getDescription().c_str());
			edit->setHeader("start time");
			edit->setIndex(2);
			edit->setStartTime(*(new ClockTime(0300)));
			edit->execute(_taskList);
			Assert::AreEqual("0300",_taskList.getTask(1)->getStartTime().toString().c_str());
		}
	};
}