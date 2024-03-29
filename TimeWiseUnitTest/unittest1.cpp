#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TimeWiseUnitTest {		
	TEST_CLASS(UnitTest1) {
	public:
		//@author A0097277M
		TEST_METHOD(CommandAddTest) {
			//equivalence partition: floating task, timed task, deadline task
			TaskList _taskList;
			std::vector<Command_Add*> commandToBeExecuted;
			ClockTime startTime(1200);
			ClockTime endTime(1600);
			Date startDate(10,3,2014);
			Date endDate(12,3,2014);
			std::string feedback;
			DISPLAY_TYPE displayScreen = MAIN;
			commandToBeExecuted.push_back(new Command_Add);
			commandToBeExecuted[0]->setDescription("check for floating task without category");
			commandToBeExecuted[0]->setPreviousScreen(&displayScreen);

			commandToBeExecuted.push_back(new Command_Add);
			commandToBeExecuted[1]->setDescription("check for floating task with category");
			commandToBeExecuted[1]->setCategory("test");
			commandToBeExecuted[1]->setPreviousScreen(&displayScreen);


			commandToBeExecuted.push_back(new Command_Add);
			commandToBeExecuted[2]->setDescription("check for deadline task with category");
			commandToBeExecuted[2]->setEndDate(endDate);
			commandToBeExecuted[2]->setEndTime(endTime);
			commandToBeExecuted[2]->setCategory("test");
			commandToBeExecuted[2]->setPreviousScreen(&displayScreen);


			commandToBeExecuted.push_back(new Command_Add);
			commandToBeExecuted[3]->setDescription("check for timed task with category");
			commandToBeExecuted[3]->setStartDate(startDate);
			commandToBeExecuted[3]->setStartTime(startTime);
			commandToBeExecuted[3]->setEndDate(endDate);
			commandToBeExecuted[3]->setEndTime(endTime);
			commandToBeExecuted[3]->setCategory("test");
			commandToBeExecuted[3]->setPreviousScreen(&displayScreen);

			
			commandToBeExecuted[0]->execute(_taskList,feedback);
			Assert::AreEqual("check for floating task without category",_taskList.getTask(0)->getDescription().c_str());

			commandToBeExecuted[1]->execute(_taskList, feedback);
			Assert::AreEqual("check for floating task with category",_taskList.getTask(0)->getDescription().c_str());
			Assert::AreEqual("test",_taskList.getTask(0)->getTaskCategory().c_str());

			commandToBeExecuted[2]->execute(_taskList, feedback);
			Assert::AreEqual("check for deadline task with category",_taskList.getTask(2)->getDescription().c_str());
			Assert::AreEqual("1600",_taskList.getTask(2)->getEndTime()->toString().c_str());
			Assert::AreEqual("12 Mar",_taskList.getTask(2)->getEndDate()->toString().c_str());

			commandToBeExecuted[3]->execute(_taskList,feedback);
			Assert::AreEqual("check for timed task with category",_taskList.getTask(3)->getDescription().c_str());
			Assert::AreEqual("1600",_taskList.getTask(3)->getEndTime()->toString().c_str());
			Assert::AreEqual("12 Mar",_taskList.getTask(3)->getEndDate()->toString().c_str());
			Assert::AreEqual("1200",_taskList.getTask(3)->getStartTime()->toString().c_str());
			Assert::AreEqual("10 Mar",_taskList.getTask(3)->getStartDate()->toString().c_str());
			
		}
		//@author A0097277M
		TEST_METHOD(CommandDeleteTest) {
			
			TaskList _taskList;
			std::string feedback;
			for(int i=0;i<10;i++){
				Task* task = new Task();
				task->setDescription("a"+i);
				_taskList.addTask(*task);
			}
			Command_Delete* _cmd = new Command_Delete;
			_cmd->addDeletionIndex(0);
			_cmd->setDisplayScreen(MAIN);
			_cmd->execute(_taskList,feedback);
			Assert::AreEqual(9,static_cast<int>(_taskList.undoneSize()));
			delete _cmd;
			_cmd=NULL;
			_cmd = new Command_Delete;
			for(int i=0;i<3;i++){
				_cmd->addDeletionIndex(0+i);
				_cmd->setDisplayScreen(MAIN);
			}
			_cmd->execute(_taskList,feedback);
			Assert::AreEqual(6,static_cast<int>(_taskList.undoneSize()));
			
		}
		//@author A0097277M
		TEST_METHOD(CommandClearTest) {
			//Equivalence partitioning: Clear from Screen, Clear from Main, Clear from Completed, Clear All
			TaskList _taskList;
			std::string feedback;
			for(int i=0;i<10;i++){
				Task* task = new Task();
				task->setDescription("a"+i);
				_taskList.addTask(*task);
			}
			Command_Clear* clear = new Command_Clear(ALL);
			clear->execute(_taskList, feedback);
			Assert::AreEqual(0,static_cast<int>(_taskList.undoneSize()));
			clear->undo(_taskList,feedback);
			Assert::AreEqual(10,static_cast<int>(_taskList.undoneSize()));
			Command_Clear* clear1 = new Command_Clear(UNCOMPLETED_TASKS);
			clear1->execute(_taskList,feedback);
			Assert::AreEqual(0,static_cast<int>(_taskList.undoneSize()));
			clear1->undo(_taskList,feedback);
			Command_Clear* clear2 = new Command_Clear(SCREEN);
			clear2->setDisplayScreen(MAIN);
			clear->execute(_taskList,feedback);
			Assert::AreEqual(0,static_cast<int>(_taskList.undoneSize()));
		}
		//@author A0097277M
		TEST_METHOD(CommandEditTest) {
			//Equivalence Partition: Edit Description, Edit Schedule
			TaskList _taskList;
			std::string feedback;
			Task* task=new Task;
			task->setDescription("test");
			_taskList.addTask(*task);
			Command_Edit* cmd = new Command_Edit;
			cmd->setDescription("test success");
			cmd->setIndex(0);
			cmd->setDisplayScreen(MAIN);
			cmd->execute(_taskList,feedback);
			Assert::AreEqual("test success",_taskList.getTask(0)->getDescription().c_str());
			Command_Edit* cmd1 = new Command_Edit;
			cmd1->setDescription("test for date and time");
			cmd1->setEndDate(new Date(12,12,2014));
			cmd1->setStartDate(new Date(11,12,2014));
			cmd1->setStartTime(new ClockTime(1200));
			cmd1->setEndTime(new ClockTime(1300));
			cmd1->setIndex(0);
			cmd1->setDisplayScreen(MAIN);
			cmd1->execute(_taskList,feedback);
			Assert::AreEqual("test for date and time",_taskList.getTask(0)->getDescription().c_str());
			Assert::AreEqual("12 Dec",_taskList.getTask(0)->getEndDate()->toString().c_str());
			Assert::AreEqual("11 Dec",_taskList.getTask(0)->getStartDate()->toString().c_str());
			Assert::AreEqual("1200",_taskList.getTask(0)->getStartTime()->toString().c_str());
			Assert::AreEqual("1300",_taskList.getTask(0)->getEndTime()->toString().c_str());
		}
		//@author A0097277M
		TEST_METHOD(CommandDoneUndoneTest) {
			TaskList _taskList;
			std::string feedback;
			DISPLAY_TYPE type = MAIN;
			for(int i=0;i<10;i++){
				Task* task = new Task();
				task->setDescription("a"+i);
				_taskList.addTask(*task);
			}
			Command_Done* cmd = new Command_Done;
			for(int i=0;i<3;i++){
				cmd->addDoneIndex(i);
			}
			cmd->setPreviousScreen(&type);
			cmd->execute(_taskList,feedback);
			Assert::AreEqual(7,static_cast<int>(_taskList.undoneSize()));
			Assert::AreEqual(3,static_cast<int>(_taskList.doneSize()));
			type = COMPLETE;
			Command_Undone* cmd1 = new Command_Undone;
			for(int i=0;i<3;i++){
				cmd1->addUndoneIndex(i);
			}
			cmd1->setPreviousScreen(&type);
			cmd1->execute(_taskList,feedback);
			Assert::AreEqual(10,static_cast<int>(_taskList.undoneSize()));
			Assert::AreEqual(0,static_cast<int>(_taskList.doneSize()));

		}
		//@author A0097277M
		TEST_METHOD(CommandSearchKeywordTest) {
			TaskList _taskList;
			std::string feedback;
			DISPLAY_TYPE type = MAIN;
			for(int i=0;i<5;i++){
				Task* task = new Task();
				task->setDescription("Hello");
				_taskList.addTask(*task);
			}
			for(int i=0;i<5;i++){
				Task* task = new Task();
				task->setDescription("Bingo");
				_taskList.addTask(*task);
			}
			Command_Search* cmd = new Command_Search;
			cmd->setKeyword("hel");
			cmd->setPreviousScreen(&type);
			cmd->execute(_taskList,feedback);
			Assert::AreEqual(5,static_cast<int>(_taskList.searchedSize()));
			for(int i=0;i<5;i++){
				Assert::AreEqual("Hello",_taskList.getSearchedTask(i)->getDescription().c_str());
			}
		}
		//@author A0097277M
		TEST_METHOD(ClockTimeTest) {
			//equivalence partition: set time as negative, set time as positive and below 2359, set time above 2359
			//Boundary Value analysis: set time as -1, set time as 0000, set time as 2400,set time as 2359, set time as 2360
			ClockTime* newTime = new ClockTime(2359);
			ClockTime* otherTime = new ClockTime(0000);
			Assert::AreEqual(2359, newTime->getTime());
			Assert::AreEqual("2359",newTime->toString().c_str());
			Assert::AreEqual(static_cast<int>(LATER),static_cast<int>(newTime->isLater(otherTime)));
			try{
				newTime->setTime(-1);
			}catch(InvalidDateTimeFormatException& e){
				Assert::AreEqual(INVALID_USER_INPUT_DATE_TIME,e.what());
			}
			try{
				newTime->setTime(2360);
			}catch(InvalidDateTimeFormatException& e){
				Assert::AreEqual(INVALID_USER_INPUT_DATE_TIME,e.what());
			}
			try{
				newTime->setTime(2400);
			}catch(InvalidDateTimeFormatException& e){
				Assert::AreEqual(INVALID_USER_INPUT_DATE_TIME,e.what());
			}
			delete newTime;
			delete otherTime;
		}
		//@author A0097277M
		TEST_METHOD(DateTest) {
			//equivalence partition: negative day month year, positive day month year=> leapYear, nonleapYEar=>validDayMonthYear InvalidDayMonthYear
			//Boundary Value analysis: set day month year as negative or zero, set month above 12, set day above valid day
			Date* newDate = new Date(31,12,2014);
			Date* otherDate = new Date(1,1,2014);
			Assert::AreEqual(2014, newDate->getYear());
			Assert::AreEqual(12, newDate->getMonth());
			Assert::AreEqual(31, newDate->getDay());
			Assert::AreEqual(static_cast<int>(LATER),static_cast<int>(newDate->isLater(otherDate)));
			try {
				newDate->setDate(0,0,0);
			} catch(InvalidDateTimeFormatException& e) {
				Assert::AreEqual(INVALID_USER_INPUT_DATE_TIME,e.what());
			}
			try {
				newDate->setDate(31,2,2014);
			} catch(InvalidDateTimeFormatException& e) {
				Assert::AreEqual(INVALID_USER_INPUT_DATE_TIME,e.what());
			}
			try {
				newDate->setDate(31,13,2014);
			} catch(InvalidDateTimeFormatException& e){
				Assert::AreEqual(INVALID_USER_INPUT_DATE_TIME,e.what());
			}
			try {
				newDate->setDate(29,2,2014);
			} catch(InvalidDateTimeFormatException& e){
				Assert::AreEqual(INVALID_USER_INPUT_DATE_TIME,e.what());
			}
			Assert::AreEqual(true, Date::isLeapYear(2016));
			newDate->setDate(29,2,2016);

			delete newDate;
			delete otherDate;
		}

		//@author A0121023H
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
		//@author A0121023H
		TEST_METHOD(ParserTest_RemoveFirstWord) {
			Parser _parser;
			std::string validInput1 = _parser.removeFirstWord("edit 1");
			std::string expectedCase1 = " 1";
			std::string validInput2= _parser.removeFirstWord("clear");
			std::string expectedCase2 = "";
			std::string validInput3 = _parser.removeFirstWord(" add do homework");
			std::string expectedCase3 = " do homework";
			std::string validInput4= _parser.removeFirstWord("       add do homework");
			std::string expectedCase4 = " do homework";
			std::string validInput5 = _parser.removeFirstWord("undone 1   ");
			std::string expectedCase5 = " 1";
			std::string validInput6 = _parser.removeFirstWord("add   hello kitty");
			std::string expectedCase6 = "   hello kitty";
			std::string validInput7 = _parser.removeFirstWord("  add   do homework");
			std::string expectedCase7 = "   do homework";
			std::string invalidInput8 = _parser.removeFirstWord("");
			std::string expectedCase8 = "";
			Assert::AreEqual(expectedCase1, validInput1);
			Assert::AreEqual(expectedCase2, validInput2);
			Assert::AreEqual(expectedCase3, validInput3);
			Assert::AreEqual(expectedCase4, validInput4);
			Assert::AreEqual(expectedCase5, validInput5);
			Assert::AreEqual(expectedCase6, validInput6);
			Assert::AreEqual(expectedCase7, validInput7);
			Assert::AreEqual(expectedCase8, invalidInput8);
		}
		//@author A0121023H
		TEST_METHOD(ParserTest_SplitBySpace) {
			//vector to be converted to string for comparison
			std:: string word = "add";

			std::vector<string> validInput1 = Parser::splitBySpace("go to the zoo on 21/05/2014 at 7pm !H #leisure");
			std::string expectedCase1 = "go to the zoo on 21/05/2014 at 7pm !H #leisure";
			std::string convertedCase1 = Parser::strConcat(validInput1);

			std::vector<string> validInput2 = Parser::splitBySpace("  go to the zoo on 21/05/2014 at 7pm !H #leisure  ");
			std::string expectedCase2 = "go to the zoo on 21/05/2014 at 7pm !H #leisure";
			std::string convertedCase2 = Parser::strConcat(validInput2);

			std::vector<string> validInput3= Parser::splitBySpace("go to the zoo          on 21/05/2014 at 7pm !H #leisure");
			std::string expectedCase3 = "go to the zoo on 21/05/2014 at 7pm !H #leisure";
			std::string convertedCase3 = Parser::strConcat(validInput3);

			std::vector<string> invalidInput4 = Parser::splitBySpace("");
			std::string expectedCase4 = "";
			std::string convertedCase4 = Parser::strConcat(invalidInput4);

			std::vector<string> validInput5 = Parser::splitBySpace("go to the zoo on 21 May 2014 at 7pm !H #leisure");
			std::string expectedCase5 = "go to the zoo on 21 May 2014 at 7pm !H #leisure";
			std::string convertedCase5 = Parser::strConcat(validInput5);

			std::vector<string> validInput6 = Parser::splitBySpace("go to the zoo on 21 May at 7pm !H #leisure");
			std::string expectedCase6 = "go to the zoo on 21 May at 7pm !H #leisure";
			std::string convertedCase6 = Parser::strConcat(validInput6);
			
			Assert::AreEqual(convertedCase1, expectedCase1);
			Assert::AreEqual(convertedCase2, expectedCase2);
			Assert::AreEqual(convertedCase3, expectedCase3);
			Assert::AreEqual(convertedCase4, expectedCase4);
			Assert::AreEqual(convertedCase5, expectedCase5);
			Assert::AreEqual(convertedCase6, expectedCase6);
		}
		//@author A0121023H
		TEST_METHOD (ParserTest_StrReplace) {
			string validInput1 = Parser::strReplace("!", "", "!low");
			string expectedCase1 = "low";
			string validInput2= Parser::strReplace("!", "", "#personal");
			string expectedCase2 = "personal";
			Assert::AreEqual(expectedCase1, validInput1);
			Assert::AreNotEqual(expectedCase2, validInput2);
		}
		//@author A0121023H
		TEST_METHOD(ParserTest_IsTime) {
			bool validInput1 = Parser::isTime("8pm");
			bool expectedCase1 = true;
			bool validInput2= Parser::isTime("16:00");
			bool expectedCase2 = true;
			bool validInput3= Parser::isTime("1630");
			bool expectedCase3 = false;
			bool validInput4= Parser::isTime("8.30am");
			bool expectedCase4 = true;
			bool validInput5= Parser::isTime("0000");
			bool expectedCase5 = false;
			bool invalidInput6= Parser::isTime("am");
			bool expectedCase6 = false;
			bool invalidInput7= Parser::isTime("2400");
			bool expectedCase7 = false;
			bool invalidInput8= Parser::isTime("4/03");
			bool expectedCase8 = false;
			bool invalidInput9= Parser::isTime("430");
			bool expectedCase9 = false;
			bool invalidInput10 = Parser::isTime("hello");
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

		//@author A0121023H
		TEST_METHOD(ParserTest_IsPreposition) {
			bool validInput1 = Parser::isPreposition("on");
			bool expectedCase1 = true;
			bool invalidInput2 = Parser::isPreposition("");
			bool expectedCase2 = false;
			bool invalidInput3 = Parser::isPreposition("onn");
			bool expectedCase3 = false;
			bool invalidInput4 = Parser::isPreposition("10");
			bool expectedCase4 = false;

			Assert::AreEqual(expectedCase1, validInput1);
			Assert::AreEqual(expectedCase2, invalidInput2);
			Assert::AreEqual(expectedCase3, invalidInput3);
			Assert::AreEqual(expectedCase3, invalidInput4);
		}
		//@author A0121023H
	    TEST_METHOD(ParserTest_IsDate) {
			bool input1 = Parser::isDate("22/12/2013");
			bool expectedCase1 = true;
			bool input2 = Parser::isDate("22/12");
			bool expectedCase2 = true;
			bool input3 = Parser::isDate("22-07-2013");
			bool expectedCase3 = true;
			bool input4 = Parser::isDate("22-12");
			bool expectedCase4 = false;
			bool input5 = Parser::isDate("22.12.2013");
			bool expectedCase5 = true;
			bool input6 = Parser::isDate("22.12");
			bool expectedCase6 = false;
			bool input7 = Parser::isDate("tomorrow");
			bool expectedCase7 = true;
			bool input8 = Parser::isDate("today");
			bool expectedCase8 = true;
			bool input9 = Parser::isDate("tmr");
			bool expectedCase9 = true;
			bool input10 = Parser::isDate("tmrw");
			bool expectedCase10 = true;
			bool input11 = Parser::isDate("today2");
			bool expectedCase11 = false;
			bool input12 = Parser::isDate("22,12,2013");
			bool expectedCase12 = false;
			bool input13 = Parser::isDate("22,12");
			bool expectedCase13 = false;
			bool input14 = Parser::isDate("45/07/2013");
			bool expectedCase14 = false;
			bool input15 = Parser::isDate("15/15/2013");
			bool expectedCase15 = false;
			bool input16 = Parser::isDate("15/07/403");
			bool expectedCase16 = false;
			bool input17 = Parser::isDate("15/07/13");
			bool expectedCase17 = true;
			bool input18 = Parser::isDate("hello/hello/2013");
			bool expectedCase18 = false;
			bool input19 = Parser::isDate("hello");
			bool expectedCase19 = false;
			bool input20 = Parser::isDate("22 March 2013");
			bool expectedCase20 = true;
			bool input21= Parser::isDate("22 March");
			bool expectedCase21 = true;
			bool input22 = Parser::isDate("22 Mar");
			bool expectedCase22 = true;
			bool input23 = Parser::isDate("22 March, 2013");
			bool expectedCase23 = true;
			bool input24 = Parser::isDate("Mar 22");
			bool expectedCase24 = true;
			bool input25 = Parser::isDate("Mar 22 2013");
			bool expectedCase25 = true;
			bool input26 = Parser::isDate("March 22 2013");
			bool expectedCase26 = true;
			bool input27 = Parser::isDate("Mar 22, 2013");
			bool expectedCase27 = true;
			bool input28 = Parser::isDate("March 22, 2013");
			bool expectedCase28 = true;
			bool input29 = Parser::isDate("22nd Mar");
			bool expectedCase29 = true;
			bool input30 = Parser::isDate("22nd March");
			bool expectedCase30 = true;
			bool input31 = Parser::isDate("22nd Mar 2013");
			bool expectedCase31 = true;
			bool input32 = Parser::isDate("22nd March 2013");
			bool expectedCase32 = true;
			bool input33 = Parser::isDate("22nd Mar, 2013");
			bool expectedCase33 = true;
			bool input34 = Parser::isDate("22nd March, 2013");
			bool expectedCase34 = true;
			

			Assert::AreEqual(expectedCase1, input1);
			Assert::AreEqual(expectedCase2, input2);
			Assert::AreEqual(expectedCase3, input3);
			Assert::AreEqual(expectedCase4, input4);
			Assert::AreEqual(expectedCase5, input5);
			Assert::AreEqual(expectedCase6, input6);
			Assert::AreEqual(expectedCase7, input7);
			Assert::AreEqual(expectedCase8, input8);
			Assert::AreEqual(expectedCase9, input9);
			Assert::AreEqual(expectedCase10, input10);
			Assert::AreEqual(expectedCase11, input11);
			Assert::AreEqual(expectedCase12, input12);
			Assert::AreEqual(expectedCase13, input13);
			Assert::AreEqual(expectedCase14, input14);
			Assert::AreEqual(expectedCase15, input15);
			Assert::AreEqual(expectedCase16, input16);
			Assert::AreEqual(expectedCase17, input17);
			Assert::AreEqual(expectedCase18, input18);
			Assert::AreEqual(expectedCase19, input19);
			Assert::AreEqual(expectedCase20, input20);
			Assert::AreEqual(expectedCase21, input21);
			Assert::AreEqual(expectedCase22, input22);
			Assert::AreEqual(expectedCase23, input23);
			Assert::AreEqual(expectedCase24, input24);
			Assert::AreEqual(expectedCase25, input25);
			Assert::AreEqual(expectedCase26, input26);
			Assert::AreEqual(expectedCase27, input27);
			Assert::AreEqual(expectedCase28, input28);
			Assert::AreEqual(expectedCase29, input29);
			Assert::AreEqual(expectedCase30, input30);
			Assert::AreEqual(expectedCase31, input31);
			Assert::AreEqual(expectedCase32, input32);
			Assert::AreEqual(expectedCase33, input33);
			Assert::AreEqual(expectedCase34, input34);
		}
		//@author A0121023H
		TEST_METHOD(DateTest_Operators1) {
			// operator==(Date)
			Assert::AreEqual(true,  Date(12,12,1908) == Date(12,12,1908));	// All same
			Assert::AreEqual(false, Date(12,12,1908) == Date(12,12,1909));	// Different year
			Assert::AreEqual(false, Date(12,12,1908) == Date(12,11,1908));	// Different month
			Assert::AreEqual(false, Date(12,12,1908) == Date(11,12,1908));	// Different day

			// operator>(Date)
			Assert::AreEqual(false, Date(12,12,1908) > Date(12,12,1908));	// All same
			Assert::AreEqual(false, Date(12,12,1908) > Date(12,12,1909));	// Different year 1
			Assert::AreEqual(true,  Date(12,12,1909) > Date(12,12,1908));	// Different year 2
			Assert::AreEqual(true,  Date(12,12,1908) > Date(12,11,1908));	// Different month 1
			Assert::AreEqual(false, Date(12,11,1908) > Date(12,12,1908));	// Different month 2
			Assert::AreEqual(false, Date(11,12,1908) > Date(12,12,1908));	// Different day 1
			Assert::AreEqual(true,  Date(12,12,1908) > Date(12,11,1908));	// Different day 2

			// operator<(Date)
			Assert::AreEqual(false, Date(12,12,1908) < Date(12,12,1908));	// All same
			Assert::AreEqual(true,  Date(12,12,1908) < Date(12,12,1909));	// Different year 1
			Assert::AreEqual(false, Date(12,12,1909) < Date(12,12,1908));	// Different year 2
			Assert::AreEqual(false, Date(12,12,1908) < Date(12,11,1908));	// Different month 1
			Assert::AreEqual(true,  Date(12,11,1908) < Date(12,12,1908));	// Different month 2
			Assert::AreEqual(true,  Date(11,12,1908) < Date(12,12,1908));	// Different day 1
			Assert::AreEqual(false, Date(12,12,1908) < Date(12,11,1908));	// Different day 2
		}
		//@author A0121023H
		TEST_METHOD(DateTest_Operators2) {
			// operator>=(Date)
			Assert::AreEqual(true,  Date(12,12,1908) >= Date(12,12,1908));	// All same
			Assert::AreEqual(false, Date(12,12,1908) >= Date(12,12,1909));	// Different year 1
			Assert::AreEqual(true,  Date(12,12,1909) >= Date(12,12,1908));	// Different year 2
			Assert::AreEqual(true,  Date(12,12,1908) >= Date(12,11,1908));	// Different month 1
			Assert::AreEqual(false, Date(12,11,1908) >= Date(12,12,1908));	// Different month 2
			Assert::AreEqual(false, Date(11,12,1908) >= Date(12,12,1908));	// Different day 1
			Assert::AreEqual(true,  Date(12,12,1908) >= Date(12,11,1908));	// Different day 2

			// operator<=(Date)
			Assert::AreEqual(true,  Date(12,12,1908) <= Date(12,12,1908));	// All same
			Assert::AreEqual(true,  Date(12,12,1908) <= Date(12,12,1909));	// Different year 1
			Assert::AreEqual(false, Date(12,12,1909) <= Date(12,12,1908));	// Different year 2
			Assert::AreEqual(false, Date(12,12,1908) <= Date(12,11,1908));	// Different month 1
			Assert::AreEqual(true,  Date(12,11,1908) <= Date(12,12,1908));	// Different month 2
			Assert::AreEqual(true,  Date(11,12,1908) <= Date(12,12,1908));	// Different day 1
			Assert::AreEqual(false, Date(12,12,1908) <= Date(11,12,1908));	// Different day 2
		}
		//@author A0099938B
		// test for command add (float, deadline, timed tasks) and the feedback that the system is going to return to the users
		TEST_METHOD(System_Test_Float_Task) {
		// Test for float task
			TimeWiseLogic _logic;
			std::string feedback1 = _logic.processCommand("add do laundry");
			std::string expected1 = ADD_SUCCESS;
			Assert::AreEqual(feedback1,expected1);
		}
		//@author A0099938B
		TEST_METHOD(System_Test_Timed_Task){
		// Test for timed task
			TimeWiseLogic _logic;
			std::string feedback2 = _logic.processCommand("add do laundry from 9am to 10am");
			std::string expected2 = ADD_SUCCESS;
			Assert::AreEqual(feedback2,expected2);
		}
		//@author A0099938B
		TEST_METHOD(System_Test_Deadline_Task) {
		// Test for deadline task
			TimeWiseLogic _logic;
			std::string feedback3 = _logic.processCommand("add do laundry by 21/05");
			std::string expected3 = ADD_SUCCESS;
			Assert::AreEqual(feedback3,expected3);
		}

		//@author A0099938B
		TEST_METHOD(System_Test_No_Argument) {
			TimeWiseLogic _logic;
			std::string feedback9 = _logic.processCommand("add");
			std::string expected9 = NO_ARGUMENT_EXCEPTION;
			Assert::AreEqual(feedback9,expected9);
		}
		//@author A0099938B
		TEST_METHOD(System_Test_Empty_Input) {
			TimeWiseLogic _logic;
			std::string feedback10 = _logic.processCommand("");
			std::string expected10 = NO_COMMAND_LINE;
			Assert::AreEqual(feedback10,expected10);
		}
		//@author A0099938B
		TEST_METHOD(System_Test_Delete_Command) {
			TimeWiseLogic _logic;
			//Test for command delete and the feedback that the system return to user
			std::string cmd1 = _logic.processCommand("add do laundry");
			std::string cmd2 = _logic.processCommand("add do laundry by 21/05");
			std::string cmd3 = _logic.processCommand("add do laundry from 21/5 to 22/5");
			std::string cmd4 = _logic.processCommand("add do laundry from 21/5 to 22/5 from 9pm to 10pm");
			std::string cmd5 = _logic.processCommand("add do laundry #chores");
			std::string cmd6 = _logic.processCommand("add do laundry tomorrow at 9pm");
			std::string cmd7 = _logic.processCommand("add do laundry from 9 am to 10 am");
			std::string cmd8 = _logic.processCommand("delete 1");
			std::string expected8 = DELETE_SUCCESS;
			Assert::AreEqual(cmd8,expected8);
			std::string cmd9 = _logic.processCommand("delete");
			std::string expected9 = NO_ARGUMENT_EXCEPTION;// Test for input without any index.
			Assert::AreEqual(cmd9,expected9);
		}
		//@author A0099938B
		TEST_METHOD(System_Test_Delete_Negative_Index) {
			TimeWiseLogic _logic;
			//Test for command delete and the feedback that the system return to user when the index is out of range.
			std::string cmd1  = _logic.processCommand("add do laundry");
			std::string cmd2  = _logic.processCommand("add do laundry by 21/05");
			std::string cmd3  = _logic.processCommand("add do laundry from 21/5 to 22/5");
			std::string cmd4  = _logic.processCommand("add do laundry from 21/5 to 22/5 from 9pm to 10pm");
			std::string cmd5  = _logic.processCommand("add do laundry #chores");
			std::string cmd6  = _logic.processCommand("add do laundry tomorrow at 9pm");
			std::string cmd7  = _logic.processCommand("add do laundry from 9am to 10am");
			std::string cmd9 = _logic.processCommand("delete -3");
			std::string expected9 = USER_INPUT_NOT_A_NUMBER;
			Assert::AreEqual(expected9, cmd9);

		}
		//@author A0099938B
		TEST_METHOD(System_Test_Done_Command) {
			//test for command done/undone and the feedback that the system is going to return
			TimeWiseLogic _logic;
			std::string cmd1 = _logic.processCommand("add do laundry");
			std::string cmd7 = _logic.processCommand("add do laundry from 9am to 10am");
			std::string cmd2 = _logic.processCommand("add do laundry by 21/05");
			std::string cmd8 = _logic.processCommand("add do laundry tomorrow at 9pm");
			std::string cmd3 = _logic.processCommand("add do laundry from 21/5 to 22/5");
			std::string cmd4 = _logic.processCommand("add do laundry from 21/5 to 22/5 from 9pm to 10pm");
			std::string cmd5 = _logic.processCommand("add do laundry #chores");
			std::string cmd6 = _logic.processCommand("done 1");
			std::string expected6 = DONE_SUCCESS;
			Assert::AreEqual(cmd6, expected6);
		}
		//@author A0099938B
		TEST_METHOD(System_Test_Undone_Command) {
			//test for command undone command and the feedback that the system is going to return
			TimeWiseLogic _logic;
			std::string cmd1 = _logic.processCommand("add do laundry");
			std::string cmd7 = _logic.processCommand("add do laundry from 9 am to 10 am");
			std::string cmd2 = _logic.processCommand("add do laundry by 21/05");
			std::string cmd8 = _logic.processCommand("add do laundry tomorrow at 9pm");
			std::string cmd3 = _logic.processCommand("add do laundry from 21/5 to 22/5");
			std::string cmd4 = _logic.processCommand("add do laundry from 21/5 to 22/5 from 9pm to 10pm");
			std::string cmd5 = _logic.processCommand("add do laundry #chores");
			std::string cmd6 = _logic.processCommand("undone 1");
			std::string expected6 = TASK_NOT_COMPLETED_YET;
			Assert::AreEqual(expected6, cmd6);
		}
		//@author A0099938B
		TEST_METHOD(System_Test_Clear_All) {
			TimeWiseLogic _logic;
		    //test for command clear and the feedback that the system is going to return to user
			std::string cmd1 = _logic.processCommand("add do laundry");
			std::string cmd2 = _logic.processCommand("add do laundry from 9 am to 10 am");
			std::string cmd3 = _logic.processCommand("add do laundry by 21/05");
			std::string cmd4 = _logic.processCommand("add do laundry tomorrow at 9pm");
			std::string cmd5 = _logic.processCommand("add do laundry from 21/4 to 22/4");
			std::string cmd6 = _logic.processCommand("add do laundry from 21/4 to 22/4 9pm to 10 pm");
			std::string cmd7 = _logic.processCommand("add do laundry !high #household");
			std::string cmd8 = _logic.processCommand("clear all");
			std::string expected8 = CLEAR_ALL_SUCCESS;
			Assert::AreEqual(expected8, cmd8);
		}

};
}