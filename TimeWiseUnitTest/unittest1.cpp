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
			commandToBeExecuted[1]->execute(_taskList);
			commandToBeExecuted[2]->execute(_taskList);
			commandToBeExecuted[3]->execute(_taskList);

			Command_Delete* commandToBeDeleted = new Command_Delete;
			commandToBeDeleted->setDeletionIndex(0);
			commandToBeDeleted->execute(_taskList);
			Assert::AreEqual("check floating task with priority and cat",_taskList.getTask(0)->getDescription().c_str());
			Assert::AreEqual("check deadline task without priority and cat",_taskList.getTask(1)->getDescription().c_str());
			Assert::AreEqual("check timed task without priority and cat",_taskList.getTask(2)->getDescription().c_str());
			commandToBeDeleted->setDeletionIndex(1);
			commandToBeDeleted->execute(_taskList);
			Assert::AreEqual("check floating task with priority and cat",_taskList.getTask(0)->getDescription().c_str());
			Assert::AreEqual("check timed task without priority and cat",_taskList.getTask(1)->getDescription().c_str());
			commandToBeDeleted->setDeletionIndex(1);
			commandToBeDeleted->execute(_taskList);
			Assert::AreEqual("check floating task with priority and cat",_taskList.getTask(0)->getDescription().c_str());
			commandToBeDeleted->setDeletionIndex(0);
			commandToBeDeleted->execute(_taskList);
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

			commandToBeExecuted[0]->execute(_taskList);
			commandToBeExecuted[1]->execute(_taskList);
			commandToBeExecuted[2]->execute(_taskList);
			commandToBeExecuted[3]->execute(_taskList);

			Command_Edit* edit = new Command_Edit;
			edit->setIndex(0);
			edit->setHeader("description");
			edit->setDescription("new description");
			edit->execute(_taskList);
			Assert::AreEqual("new description",_taskList.getTask(0)->getDescription().c_str());
			Command_Edit* edit1 = new Command_Edit;
			edit1->setIndex(2);
			edit1->setHeader("end time");
			ClockTime* time = new ClockTime(2359);
			edit1->setEndTime(*time);
			edit1->execute(_taskList);
			Assert::AreEqual("2359",(_taskList.getTask(2)->getEndTime().toString()).c_str());


		}

		TEST_METHOD(CommandDoneUndoneTest) {
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
			commandToBeExecuted[1]->execute(_taskList);
			commandToBeExecuted[2]->execute(_taskList);
			commandToBeExecuted[3]->execute(_taskList);

			Command_Done* newDone= new Command_Done;
			newDone->setCompletedIndex(0);
			newDone->execute(_taskList);
			Assert::AreEqual(static_cast<int>(COMPLETED),static_cast<int>(_taskList.getTask(0)->getTaskStatus()));
			newDone->setCompletedIndex(1);
			newDone->execute(_taskList);
			Assert::AreEqual(static_cast<int>(COMPLETED),static_cast<int>(_taskList.getTask(1)->getTaskStatus()));
			newDone->setCompletedIndex(2);
			newDone->execute(_taskList);
			Assert::AreEqual(static_cast<int>(COMPLETED),static_cast<int>(_taskList.getTask(2)->getTaskStatus()));
			newDone->setCompletedIndex(3);
			newDone->execute(_taskList);
			Assert::AreEqual(static_cast<int>(COMPLETED),static_cast<int>(_taskList.getTask(3)->getTaskStatus()));

			Command_Undone* newUndone= new Command_Undone;
			newUndone->setUncompletedIndex(0);
			newUndone->execute(_taskList);
			Assert::AreEqual(static_cast<int>(UNCOMPLETED),static_cast<int>(_taskList.getTask(0)->getTaskStatus()));
			newUndone->setUncompletedIndex(1);
			newUndone->execute(_taskList);
			Assert::AreEqual(static_cast<int>(UNCOMPLETED),static_cast<int>(_taskList.getTask(1)->getTaskStatus()));
			newUndone->setUncompletedIndex(2);
			newUndone->execute(_taskList);
			Assert::AreEqual(static_cast<int>(UNCOMPLETED),static_cast<int>(_taskList.getTask(2)->getTaskStatus()));
			newUndone->setUncompletedIndex(3);
			newUndone->execute(_taskList);
			Assert::AreEqual(static_cast<int>(UNCOMPLETED),static_cast<int>(_taskList.getTask(3)->getTaskStatus()));
		}
	};
}