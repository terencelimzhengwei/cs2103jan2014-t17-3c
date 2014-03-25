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
			Assert::AreEqual("check floating task with priority and cat",_taskList.getTask(0)->getDescription().c_str());
			Assert::AreEqual(static_cast<int>(HIGH),static_cast<int>(_taskList.getTask(0)->getPriority()));
			Assert::AreEqual("test",_taskList.getTask(0)->getTaskCategory().c_str());

			commandToBeExecuted[2]->execute(_taskList);
			Assert::AreEqual("check deadline task without priority and cat",_taskList.getTask(2)->getDescription().c_str());
			Assert::AreEqual("1600",_taskList.getTask(2)->getEndTime()->toString().c_str());
			Assert::AreEqual("12 Mar 14",_taskList.getTask(2)->getEndDate()->toString().c_str());

			commandToBeExecuted[3]->execute(_taskList);
			Assert::AreEqual("check timed task without priority and cat",_taskList.getTask(3)->getDescription().c_str());
			Assert::AreEqual("1600",_taskList.getTask(3)->getEndTime()->toString().c_str());
			Assert::AreEqual("12 Mar 14",_taskList.getTask(3)->getEndDate()->toString().c_str());
			Assert::AreEqual("1200",_taskList.getTask(3)->getStartTime()->toString().c_str());
			Assert::AreEqual("10 Mar 14",_taskList.getTask(3)->getStartDate()->toString().c_str());

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
			Assert::AreEqual("check for floating task without priority and cat",_taskList.getTask(0)->getDescription().c_str());
			Assert::AreEqual("check deadline task without priority and cat",_taskList.getTask(1)->getDescription().c_str());
			Assert::AreEqual("check timed task without priority and cat",_taskList.getTask(2)->getDescription().c_str());
			commandToBeDeleted->setDeletionIndex(1);
			commandToBeDeleted->execute(_taskList);
			Assert::AreEqual("check for floating task without priority and cat",_taskList.getTask(0)->getDescription().c_str());
			Assert::AreEqual("check timed task without priority and cat",_taskList.getTask(1)->getDescription().c_str());
			commandToBeDeleted->setDeletionIndex(1);
			commandToBeDeleted->execute(_taskList);
			Assert::AreEqual("check for floating task without priority and cat",_taskList.getTask(0)->getDescription().c_str());
			commandToBeDeleted->setDeletionIndex(0);
			commandToBeDeleted->execute(_taskList);
			Assert::AreEqual(0,_taskList.undoneSize());
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
			Assert::AreEqual(0,_taskList.undoneSize());

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
			Assert::AreEqual("2359",(_taskList.getTask(2)->getEndTime()->toString()).c_str());


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

		TEST_METHOD(CommandSearchKeywordTest) {
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

		/*	Command_Search* search = new Command_Search();
			search->setKeyword("task");
			search->execute(_taskList);
			std::vector<Task*> searchedtask= _taskList.getSearchResults();
			Assert::AreEqual(_taskList.getTask(0)->getDescription().c_str(),searchedtask[0]->getDescription().c_str());
			Assert::AreEqual(_taskList.getTask(1)->getDescription().c_str(),searchedtask[1]->getDescription().c_str());
			Assert::AreEqual(_taskList.getTask(2)->getDescription().c_str(),searchedtask[2]->getDescription().c_str());
			Assert::AreEqual(_taskList.getTask(3)->getDescription().c_str(),searchedtask[3]->getDescription().c_str());
			search->setKeyword("check timed task without priority and cat");
			search->execute(_taskList);
			std::vector<Task*> searchedtask1= _taskList.getSearchResults();
			Assert::AreEqual("check timed task without priority and cat",searchedtask1[0]->getDescription().c_str());
			search->setCategory("test");
			search->execute(_taskList);
			std::vector<Task*> searchedtask2= _taskList.getSearchResults();
			Assert::AreEqual(1,static_cast<int>(searchedtask2.size()));
			Assert::AreEqual("test",searchedtask2[0]->getTaskCategory().c_str());
			search->setDate(&endDate);
			search->execute(_taskList);
			std::vector<Task*> searchedtask3= _taskList.getSearchResults();
			Assert::AreEqual(2,static_cast<int>(searchedtask3.size()));
			Assert::AreEqual(endDate.toString(),(searchedtask3[0]->getEndDate()->toString()));
			Assert::AreEqual(endDate.toString(),searchedtask3[1]->getEndDate()->toString());*/

		}
		TEST_METHOD(ClockTimeTest) {
			ClockTime* newTime = new ClockTime(1200);
			ClockTime* otherTime = new ClockTime(1230);
			Assert::AreEqual(1200, newTime->getTime());
			Assert::AreEqual("1200",newTime->toString().c_str());
			//Assert::IsTrue(newTime->checkOverdueTime());
			Assert::AreEqual(static_cast<int>(EARLIER),static_cast<int>(newTime->isLater(otherTime)));
		}
		TEST_METHOD(DateTest) {
			Date* newDate = new Date(12,2,2014);
			Date* otherDate = new Date(15,2,2014);
			Assert::AreEqual(12,newDate->getDayNumber());
			Assert::AreEqual(2,newDate->getMonth());
			Assert::AreEqual(2014,newDate->getYear());
			Assert::AreEqual(static_cast<int>(EARLIER),static_cast<int>(newDate->isLater(otherDate)));
			Assert::AreEqual(static_cast<int>(LATER),static_cast<int>(newDate->checkOverdue()));
		}

		TEST_METHOD(updateOverdueTaskTest) {
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

			_taskList.updateOverdueTaskList();
			std::vector<Task*> overdueTask = _taskList.getOverdueTaskList();
			Assert::AreEqual(2,static_cast<int>(overdueTask.size()));
		}

		TEST_METHOD(checkClashTest) {
			TaskList _taskList;
			std::vector<Command_Add*> commandToBeExecuted;
			ClockTime startTime(1200);
			ClockTime endTime(1600);
			Date startDate(10,3,2014);
			Date endDate(12,3,2014);
			commandToBeExecuted.push_back(new Command_Add);
			commandToBeExecuted[0]->setDescription("check for floating task without priority and cat");
			commandToBeExecuted[2]->setEndDate(endDate);
			commandToBeExecuted[2]->setEndTime(endTime);

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
		}

		TEST_METHOD(ParserTest_GetFirstWord) {
			Parser _parser;
			std::string expectedCase1 = "add";
			std::string validInput1 = _parser.getFirstWord("add dinner with Mai");
			std::string expectedCase2 = "";
			std::string invalidInput2 = _parser.getFirstWord("");
			std::string validInput3 = _parser.getFirstWord("  add do homework");
			std::string expectedCase3 = "add";
			Assert::AreEqual(expectedCase1, validInput1);
			Assert::AreEqual(expectedCase2, invalidInput2);
			Assert::AreEqual(expectedCase3, validInput3);
		}

		TEST_METHOD(ParserTest_RemoveFirstWord) {
			Parser _parser;
			std::string validInput1 = _parser.removeFirstWord("edit 1");
			std::string expectedCase1 = "1";
			std::string validInput2= _parser.removeFirstWord("clear");
			std::string expectedCase2 = "";
			std::string validInput3 = _parser.removeFirstWord(" add do homework");
			std::string expectedCase3 = "do homework";
			std::string validInput4= _parser.removeFirstWord("       add do homework");
			std::string expectedCase4 = "do homework";
			std::string validInput5 = _parser.removeFirstWord("undone 1   ");
			std::string expectedCase5 = "1   ";
			std::string validInput6 = _parser.removeFirstWord("add   hello kitty");
			std::string expectedCase6 = "   hello kitty";
			std::string validInput7 = _parser.removeFirstWord("  add   do homework");
			std::string expectedCase7 = "   do homework";
			std::string invalidInput8 = _parser.removeFirstWord("");
			std::string expectedCase8 = NULL;
			Assert::AreEqual(expectedCase1, validInput1);
			Assert::AreEqual(expectedCase2, validInput2);
			Assert::AreEqual(expectedCase3, validInput3);
			Assert::AreEqual(expectedCase4, validInput4);
			Assert::AreEqual(expectedCase5, validInput5);
			Assert::AreEqual(expectedCase6, validInput6);
			Assert::AreEqual(expectedCase7, validInput7);
			Assert::AreEqual(expectedCase8, invalidInput8);
		}

		TEST_METHOD(ParserTest_SplitBySpace) {
			//vector to be converted to string for comparison
			std:: string word = "add";
			Parser _parser;

			std::vector<string> validInput1 = _parser.splitBySpace("go to the zoo on 21/05/2014 at 7pm !H #leisure");
			std::string expectedCase1 = "go to the zoo on 21/05/2014 at 7pm !H #leisure";
			std::string convertedCase1 = "";
			for (int i = 0; i < 10; i ++) {
				convertedCase1 += validInput1[i];
			}
			std::vector<string> validInput2 = _parser.splitBySpace("  go to the zoo on 21/05/2014 at 7pm !H #leisure  ");
			std::string expectedCase2 = "go to the zoo on 21/05/2014 at 7pm !H #leisure";
			std::string convertedCase2 = "";
			for (int i = 0; i < 10; i ++) {
				convertedCase2 += validInput2[i];
			}
			std::vector<string> validInput3= _parser.splitBySpace("go to the zoo          on 21/05/2014 at 7pm !H #leisure");
			std::string expectedCase3 = "go to the zoo on 21/05/2014 at 7pm !H #leisure";
			std::string convertedCase3 = "";
			for (int i = 0; i < 10; i ++) {
				convertedCase3 += validInput3[i];
			}
			std::vector<string> invalidInput4 = _parser.splitBySpace("");
			std::string expectedCase4 = "";
			std::string convertedCase4 = "";
			for (int i = 0; i < 1; i ++) {
				convertedCase4 += invalidInput4[i];
			}

			std::vector<string> validInput5 = _parser.splitBySpace("go to the zoo on 21 May 2014 at 7pm !H #leisure");
			std::string expectedCase5 = "go to the zoo on 21 May 2014 at 7pm !H #leisure";
			std::string convertedCase5 = "";
			for (int i = 0; i < 12; i ++) {
				convertedCase3 += validInput5[i];
			}

			std::vector<string> validInput6 = _parser.splitBySpace("go to the zoo on 21 May at 7pm !H #leisure");
			std::string expectedCase6 = "go to the zoo on 21 May at 7pm !H #leisure";
			std::string convertedCase6 = "";
			for (int i = 0; i < 11; i ++) {
				convertedCase6 += validInput6[i];
			}
			
			Assert::AreEqual(convertedCase1, expectedCase1);
			Assert::AreEqual(convertedCase2, expectedCase2);
			Assert::AreEqual(convertedCase3, expectedCase3);
			Assert::AreEqual(convertedCase4, expectedCase4);
			Assert::AreEqual(convertedCase5, expectedCase5);
			Assert::AreEqual(convertedCase6, expectedCase6);
		}
		
		TEST_METHOD (ParserTest_ReplaceWord) {
			Parser _parser;
			std::string validInput1 = _parser.replaceWord("!", "", "!low");
			std::string expectedCase1 = "low";
			std::string validInput2= _parser.replaceWord("!", "", "#personal");
			std::string expectedCase2 = "personal";
			Assert::AreEqual(expectedCase1, validInput1);
			Assert::AreEqual(expectedCase2, validInput2);
		}

		TEST_METHOD(ParserTest_IsTimeFormat) {
			Parser _parser;
			bool validInput1 = _parser.isTimeFormat("8pm");
			bool expectedCase1 = true;
			bool validInput2= _parser.isTimeFormat("16:00");
			bool expectedCase2 = true;
			bool validInput3= _parser.isTimeFormat("1630");
			bool expectedCase3 = true;
			bool validInput4= _parser.isTimeFormat("8.30am");
			bool expectedCase4 = true;
			bool validInput5= _parser.isTimeFormat("0000");
			bool expectedCase5 = true;
			bool invalidInput6= _parser.isTimeFormat("am");
			bool expectedCase6 = false;
			bool invalidInput7= _parser.isTimeFormat("2400");
			bool expectedCase7 = false;
			bool invalidInput8= _parser.isTimeFormat("4/03");
			bool expectedCase8 = false;
			bool invalidInput9= _parser.isTimeFormat("430");
			bool expectedCase9 = false;
			bool invalidInput10 = _parser.isTimeFormat("hello");
			bool expectedCase10 = false;

			Assert::AreEqual(expectedCase1, validInput1);
			Assert::AreEqual(expectedCase2, validInput2);
			Assert::AreEqual(expectedCase3, validInput3);
			Assert::AreEqual(expectedCase4, validInput4);
			Assert::AreEqual(expectedCase5, validInput5);
			Assert::AreEqual(expectedCase6, invalidInput6);
			Assert::AreEqual(expectedCase7, invalidInput7);
			Assert::AreEqual(expectedCase8, invalidInput8);
			Assert::AreEqual(expectedCase9, invalidInput9);
			Assert::AreEqual(expectedCase10, invalidInput10);
		}

		TEST_METHOD(ParserTest_IsPreposition) {
			Parser _parser;
			bool validInput1 = _parser.isPreposition("on");
			bool expectedCase1 = true;
			bool invalidInput2 = _parser.isPreposition("");
			bool expectedCase2 = false;
			bool invalidInput3 = _parser.isPreposition("10");
			bool expectedCase3 = false;

			Assert::AreEqual(expectedCase1, validInput1);
			Assert::AreEqual(expectedCase2, invalidInput2);
			Assert::AreEqual(expectedCase3,invalidInput3);


		}

		TEST_METHOD(ParserTest_IsDateFormat) {
			Parser _parser;
			bool validInput1 = _parser.isDateFormat("22/12/2013");
			bool expectedCase1 = true;
			bool validInput2= _parser.isDateFormat("22/12");
			bool expectedCase2 = true;
			bool validInput3= _parser.isDateFormat("22-07-2013");
			bool expectedCase3 = true;
			bool validInput4= _parser.isDateFormat("22-12");
			bool expectedCase4 = true;
			bool validInput5= _parser.isDateFormat("22.12.2013");
			bool expectedCase5 = true;
			bool validInput6= _parser.isDateFormat("22.12");
			bool expectedCase6 = true;
			bool validInput7= _parser.isDateFormat("tomorrow");
			bool expectedCase7 = true;
			bool validInput8= _parser.isDateFormat("today");
			bool expectedCase8 = true;
			bool validInput9= _parser.isDateFormat("tmr");
			bool expectedCase9 = true;
			bool invalidInput10 = _parser.isDateFormat("tonight");
			bool expectedCase10 = true;
			bool invalidInput11 = _parser.isDateFormat("2day");
			bool expectedCase11 = true;
			bool invalidInput12 = _parser.isDateFormat("22,12,2013");
			bool expectedCase12 = false;
			bool invalidInput13 = _parser.isDateFormat("22,12");
			bool expectedCase13 = false;
			bool invalidInput14 = _parser.isDateFormat("45/07/2013");
			bool expectedCase14 = false;
			bool invalidInput15 = _parser.isDateFormat("15/15/2013");
			bool expectedCase15 = false;
			bool invalidInput16 = _parser.isDateFormat("15/07/403");
			bool expectedCase16 = false;
			bool invalidInput17 = _parser.isDateFormat("15/07/13");
			bool expectedCase17 = false;
			bool invalidInput18 = _parser.isDateFormat("hello/hello/2013");
			bool expectedCase18 = false;
			bool invalidInput19 = _parser.isDateFormat("hello");
			bool expectedCase19 = false;
			bool validInput20 = _parser.isDateFormat("22 March 2013");
			bool expectedCase20 = true;
			bool validInput21= _parser.isDateFormat("22 March");
			bool expectedCase21 = true;
			

			Assert::AreEqual(expectedCase1, validInput1);
			Assert::AreEqual(expectedCase2, validInput2);
			Assert::AreEqual(expectedCase3, validInput3);
			Assert::AreEqual(expectedCase4, validInput4);
			Assert::AreEqual(expectedCase5, validInput5);
			Assert::AreEqual(expectedCase6, validInput6);
			Assert::AreEqual(expectedCase7, validInput7);
			Assert::AreEqual(expectedCase8, validInput8);
			Assert::AreEqual(expectedCase9, validInput9);
			Assert::AreEqual(expectedCase10, invalidInput10);
			Assert::AreEqual(expectedCase11, invalidInput11);
			Assert::AreEqual(expectedCase12, invalidInput12);
			Assert::AreEqual(expectedCase13, invalidInput13);
			Assert::AreEqual(expectedCase14, invalidInput14);
			Assert::AreEqual(expectedCase15, invalidInput15);
			Assert::AreEqual(expectedCase16, invalidInput16);
			Assert::AreEqual(expectedCase17, invalidInput17);
			Assert::AreEqual(expectedCase18, invalidInput18);
			Assert::AreEqual(expectedCase19, invalidInput19);
			Assert::AreEqual(expectedCase20, validInput20);
			Assert::AreEqual(expectedCase21, validInput21);
		}

		TEST_METHOD (ParserTest_CreatDate) {
			Parser _parser;
			Date* validInput1 = _parser.createDate("21/03/2013");
			int  expectedCase1[3] = {21,3,2013};
			int  outputCase1[3] = {validInput1->getDayNumber(), validInput1->getMonth(), validInput1->getYear()};
			for (int i = 0; i <3; i++) {
				Assert::AreEqual(expectedCase1[i], outputCase1[i]);
			}
			Date* validInput2 = _parser.createDate("21/03");
			int  expectedCase2[3] = {21,3,2013};
			int  outputCase2[3] = {validInput2->getDayNumber(), validInput2->getMonth(), validInput2->getYear()};
			for (int i = 0; i <3; i++) {
				Assert::AreEqual(expectedCase2[i], outputCase2[i]);
			}
			Date* validInput3 = _parser.createDate("21/03/13");
			int  expectedCase3[3] = {21,3,2013};
			int  outputCase3[3] = {validInput3->getDayNumber(), validInput3->getMonth(), validInput3->getYear()};
			for (int i = 0; i <3; i++) {
				Assert::AreEqual(expectedCase3[i], outputCase3[i]);
			}
			Date* validInput4 = _parser.createDate("21-03-2013");
			int  expectedCase4[3] = {21,3,2013};
			int  outputCase4[3] = {validInput4->getDayNumber(), validInput4->getMonth(), validInput4->getYear()};
			for (int i = 0; i <3; i++) {
				Assert::AreEqual(expectedCase4[i], outputCase4[i]);
			}
			Date* validInput5 = _parser.createDate("21-03");
			int  expectedCase5[3] = {21,3,2013};
			int  outputCase5[3] = {validInput5->getDayNumber(), validInput5->getMonth(), validInput5->getYear()};
			for (int i = 0; i <3; i++) {
				Assert::AreEqual(expectedCase5[i], outputCase5[i]);
			}
			Date* validInput6 = _parser.createDate("21-03-13");
			int  expectedCase6[3] = {21,3,2013};
			int  outputCase6[3] = {validInput6->getDayNumber(), validInput6->getMonth(), validInput6->getYear()};
			for (int i = 0; i <3; i++) {
				Assert::AreEqual(expectedCase6[i], outputCase6[i]);
			}
			Date* invalidInput7 = _parser.createDate("21*03*13");
			int  expectedCase7[3] = {NULL,NULL,NULL};
			int  outputCase7[3] = {invalidInput7->getDayNumber(), invalidInput7->getMonth(), invalidInput7->getYear()};
			for (int i = 0; i <3; i++) {
				Assert::AreEqual(expectedCase7[i], outputCase7[i]);
			}
			Date* invalidInput8 = _parser.createDate("21/03*13");
			int  expectedCase8[3] = {21,NULL,2013};
			int  outputCase8[3] = {invalidInput8->getDayNumber(), invalidInput8->getMonth(), invalidInput8->getYear()};
			for (int i = 0; i <3; i++) {
				Assert::AreEqual(expectedCase8[i], outputCase8[i]);
			}
		}

		

		
		

};
}
