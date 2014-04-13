#include "stdafx.h"
#include "CppUnitTest.h"

#define combineVectorString(target, source) for(unsigned int i=0;i<source.size();target+=source[i++]) { if(i) target += " "; }

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TimeWiseUnitTest {		
	TEST_CLASS(UnitTest1) {
	public:
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

		TEST_METHOD(CommandClearTest) {
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
		}

		TEST_METHOD(CommandEditTest) {
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

		TEST_METHOD(CommandSearchKeywordTest) {
			
		}
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
			std::string expectedCase5 = "1";
			std::string validInput6 = _parser.removeFirstWord("add   hello kitty");
			std::string expectedCase6 = "hello kitty";
			std::string validInput7 = _parser.removeFirstWord("  add   do homework");
			std::string expectedCase7 = "do homework";
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

		TEST_METHOD(ParserTest_SplitBySpace) {
			//vector to be converted to string for comparison
			std:: string word = "add";
			Parser _parser;

			std::vector<string> validInput1 = _parser.splitBySpace("go to the zoo on 21/05/2014 at 7pm !H #leisure");
			std::string expectedCase1 = "go to the zoo on 21/05/2014 at 7pm !H #leisure";
			std::string convertedCase1 = "";
			combineVectorString(convertedCase1, validInput1);

			std::vector<string> validInput2 = _parser.splitBySpace("  go to the zoo on 21/05/2014 at 7pm !H #leisure  ");
			std::string expectedCase2 = "go to the zoo on 21/05/2014 at 7pm !H #leisure";
			std::string convertedCase2 = "";
			combineVectorString(convertedCase2, validInput2);

			std::vector<string> validInput3= _parser.splitBySpace("go to the zoo          on 21/05/2014 at 7pm !H #leisure");
			std::string expectedCase3 = "go to the zoo on 21/05/2014 at 7pm !H #leisure";
			std::string convertedCase3 = "";
			combineVectorString(convertedCase3, validInput3);

			std::vector<string> invalidInput4 = _parser.splitBySpace("");
			std::string expectedCase4 = "";
			std::string convertedCase4 = "";
			combineVectorString(convertedCase4, invalidInput4);

			std::vector<string> validInput5 = _parser.splitBySpace("go to the zoo on 21 May 2014 at 7pm !H #leisure");
			std::string expectedCase5 = "go to the zoo on 21 May 2014 at 7pm !H #leisure";
			std::string convertedCase5 = "";
			combineVectorString(convertedCase5, validInput5);

			std::vector<string> validInput6 = _parser.splitBySpace("go to the zoo on 21 May at 7pm !H #leisure");
			std::string expectedCase6 = "go to the zoo on 21 May at 7pm !H #leisure";
			std::string convertedCase6 = "";
			combineVectorString(convertedCase6, validInput6);
			
			Assert::AreEqual(convertedCase1, expectedCase1);
			Assert::AreEqual(convertedCase2, expectedCase2);
			Assert::AreEqual(convertedCase3, expectedCase3);
			Assert::AreEqual(convertedCase4, expectedCase4);
			Assert::AreEqual(convertedCase5, expectedCase5);
			Assert::AreEqual(convertedCase6, expectedCase6);
		}
		
		TEST_METHOD (ParserTest_StrReplace) {
			string validInput1 = Parser::strReplace("!", "", "!low");
			string expectedCase1 = "low";
			string validInput2= Parser::strReplace("!", "", "#personal");
			string expectedCase2 = "personal";
			Assert::AreEqual(expectedCase1, validInput1);
			Assert::AreNotEqual(expectedCase2, validInput2);
		}

		TEST_METHOD(ParserTest_IsTimeFormat) {
			bool validInput1 = Parser::isTimeFormat("8pm");
			bool expectedCase1 = true;
			bool validInput2= Parser::isTimeFormat("16:00");
			bool expectedCase2 = true;
			bool validInput3= Parser::isTimeFormat("1630");
			bool expectedCase3 = true;
			bool validInput4= Parser::isTimeFormat("8.30am");
			bool expectedCase4 = true;
			bool validInput5= Parser::isTimeFormat("0000");
			bool expectedCase5 = true;
			bool invalidInput6= Parser::isTimeFormat("am");
			bool expectedCase6 = false;
			bool invalidInput7= Parser::isTimeFormat("2400");
			bool expectedCase7 = false;
			bool invalidInput8= Parser::isTimeFormat("4/03");
			bool expectedCase8 = false;
			bool invalidInput9= Parser::isTimeFormat("430");
			bool expectedCase9 = false;
			bool invalidInput10 = Parser::isTimeFormat("hello");
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
			bool validInput1 = Parser::isDateFormat("22/12/2013");
			bool expectedCase1 = true;
			bool validInput2= Parser::isDateFormat("22/12");
			bool expectedCase2 = true;
			//bool validInput3= Parser::isDateFormat("22-07-2013");
			bool expectedCase3 = true;
			//bool validInput4= Parser::isDateFormat("22-12");
			bool expectedCase4 = true;
			//bool validInput5= Parser::isDateFormat("22.12.2013");
			bool expectedCase5 = true;
			//bool validInput6= Parser::isDateFormat("22.12");
			bool expectedCase6 = true;
			bool validInput7= Parser::isDateFormat("tomorrow");
			bool expectedCase7 = true;
			bool validInput8= Parser::isDateFormat("today");
			bool expectedCase8 = true;
			bool validInput9= Parser::isDateFormat("tmr");
			bool expectedCase9 = true;
			//bool invalidInput10 = Parser::isDateFormat("tonight");
			bool expectedCase10 = true;
			//bool invalidInput11 = Parser::isDateFormat("2day");
			bool expectedCase11 = true;
			bool invalidInput12 = Parser::isDateFormat("22,12,2013");
			bool expectedCase12 = false;
			bool invalidInput13 = Parser::isDateFormat("22,12");
			bool expectedCase13 = false;
			bool invalidInput14 = Parser::isDateFormat("45/07/2013");
			bool expectedCase14 = false;
			bool invalidInput15 = Parser::isDateFormat("15/15/2013");
			bool expectedCase15 = false;
			//bool invalidInput16 = Parser::isDateFormat("15/07/403");
			bool expectedCase16 = false;
			bool invalidInput17 = Parser::isDateFormat("15/07/13");
			bool expectedCase17 = true;
			bool invalidInput18 = Parser::isDateFormat("hello/hello/2013");
			bool expectedCase18 = false;
			bool invalidInput19 = Parser::isDateFormat("hello");
			bool expectedCase19 = false;
			bool validInput20 = Parser::isDateFormat("22 March 2013");
			bool expectedCase20 = true;
			bool validInput21= Parser::isDateFormat("22 March");
			bool expectedCase21 = true;
			

			Assert::AreEqual(expectedCase1, validInput1);
			Assert::AreEqual(expectedCase2, validInput2);
			//Assert::AreEqual(expectedCase3, validInput3);
			//Assert::AreEqual(expectedCase4, validInput4);
			//Assert::AreEqual(expectedCase5, validInput5);
			//Assert::AreEqual(expectedCase6, validInput6);
			Assert::AreEqual(expectedCase7, validInput7);
			Assert::AreEqual(expectedCase8, validInput8);
			Assert::AreEqual(expectedCase9, validInput9);
			//Assert::AreEqual(expectedCase10, invalidInput10);
			//Assert::AreEqual(expectedCase11, invalidInput11);
			Assert::AreEqual(expectedCase12, invalidInput12);
			Assert::AreEqual(expectedCase13, invalidInput13);
			Assert::AreEqual(expectedCase14, invalidInput14);
			Assert::AreEqual(expectedCase15, invalidInput15);
			//sAssert::AreEqual(expectedCase16, invalidInput16);
			Assert::AreEqual(expectedCase17, invalidInput17);
			Assert::AreEqual(expectedCase18, invalidInput18);
			Assert::AreEqual(expectedCase19, invalidInput19);
			Assert::AreEqual(expectedCase20, validInput20);
			Assert::AreEqual(expectedCase21, validInput21);
		}

		TEST_METHOD(ParserTest_CreateDate) {
			Date* validInput1 = Parser::createDate("21/03/2013");
			int  expectedCase1[3] = {21,3,2013};
			int  outputCase1[3] = {validInput1->getDay(), validInput1->getMonth(), validInput1->getYear()};
			for (int i = 0; i <3; i++) {
				Assert::AreEqual(expectedCase1[i], outputCase1[i]);
			}

			Date* validInput2 = Parser::createDate("21/03");
			int  expectedCase2[3] = {21,3,2014};
			int  outputCase2[3] = {validInput2->getDay(), validInput2->getMonth(), validInput2->getYear()};
			for (int i = 0; i <3; i++) {
				Assert::AreEqual(expectedCase2[i], outputCase2[i]);
			}

			Date* validInput3 = Parser::createDate("21/03/13");
			int  expectedCase3[3] = {21,3,2013};
			int  outputCase3[3] = {validInput3->getDay(), validInput3->getMonth(), validInput3->getYear()};
			for (int i = 0; i <3; i++) {
				Assert::AreEqual(expectedCase3[i], outputCase3[i]);
			}

			/* Date* validInput4 = Parser::createDate("21-03-2013");
			int  expectedCase4[3] = {21,3,2013};
			int  outputCase4[3] = {validInput4->getDay(), validInput4->getMonth(), validInput4->getYear()};
			for (int i = 0; i <3; i++) {
				Assert::AreEqual(expectedCase4[i], outputCase4[i]);
			}
			Date* validInput5 = Parser::createDate("21-03");
			int  expectedCase5[3] = {21,3,2014};
			int  outputCase5[3] = {validInput5->getDay(), validInput5->getMonth(), validInput5->getYear()};
			for (int i = 0; i <3; i++) {
				Assert::AreEqual(expectedCase5[i], outputCase5[i]);
			}
			Date* validInput6 = Parser::createDate("21-03-13");
			int  expectedCase6[3] = {21,3,2013};
			int  outputCase6[3] = {validInput6->getDay(), validInput6->getMonth(), validInput6->getYear()};
			for (int i = 0; i <3; i++) {
				Assert::AreEqual(expectedCase6[i], outputCase6[i]);
			}
			Date* invalidInput7 = Parser::createDate("21*03*13");
			int  expectedCase7[3] = {NULL,NULL,NULL};
			int  outputCase7[3] = {invalidInput7->getDay(), invalidInput7->getMonth(), invalidInput7->getYear()};
			for (int i = 0; i <3; i++) {
				Assert::AreEqual(expectedCase7[i], outputCase7[i]);
			}
			Date* invalidInput8 = _parser.createDate("21/03*13");
			int  expectedCase8[3] = {21,NULL,2013};
			int  outputCase8[3] = {invalidInput8->getDay(), invalidInput8->getMonth(), invalidInput8->getYear()};
			for (int i = 0; i <3; i++) {
				Assert::AreEqual(expectedCase8[i], outputCase8[i]);
			}*/
		}
		
		TEST_METHOD(ParserTest_ExtractDate) {
			Parser parser;
			vector<int> dateData;

			dateData = parser.extractDate("15/3", 0);
			Assert::AreEqual(1,dateData[3]);
			Assert::AreEqual(2014,dateData[0]);
			Assert::AreEqual(3,dateData[1]);
			Assert::AreEqual(15,dateData[2]);

			dateData = parser.extractDate("15/3/2014", 0);
			Assert::AreEqual(1,dateData[3]);
			Assert::AreEqual(2014,dateData[0]);
			Assert::AreEqual(3,dateData[1]);
			Assert::AreEqual(15,dateData[2]);

			dateData = parser.extractDate("15 mar", 1);
			Assert::AreEqual(2,dateData[3]);
			Assert::AreEqual(2014,dateData[0]);
			Assert::AreEqual(3,dateData[1]);
			Assert::AreEqual(15,dateData[2]);

			dateData = parser.extractDate("15 Mar", 1);
			Assert::AreEqual(2,dateData[3]);
			Assert::AreEqual(2014,dateData[0]);
			Assert::AreEqual(3,dateData[1]);
			Assert::AreEqual(15,dateData[2]);

			dateData = parser.extractDate("15 MAR", 1);
			Assert::AreEqual(2,dateData[3]);
			Assert::AreEqual(2014,dateData[0]);
			Assert::AreEqual(3,dateData[1]);
			Assert::AreEqual(15,dateData[2]);

			dateData = parser.extractDate("15 mar 2014", 2);
			Assert::AreEqual(3,dateData[3]);
			Assert::AreEqual(2014,dateData[0]);
			Assert::AreEqual(3,dateData[1]);
			Assert::AreEqual(15,dateData[2]);

			dateData = parser.extractDate("15 Mar 2014", 2);
			Assert::AreEqual(3,dateData[3]);
			Assert::AreEqual(2014,dateData[0]);
			Assert::AreEqual(3,dateData[1]);
			Assert::AreEqual(15,dateData[2]);

			dateData = parser.extractDate("15 MAR 2014", 2);
			Assert::AreEqual(3,dateData[3]);
			Assert::AreEqual(2014,dateData[0]);
			Assert::AreEqual(3,dateData[1]);
			Assert::AreEqual(15,dateData[2]);
		}

		TEST_METHOD(ParserTest_ExtractTime) {
			Parser parser;
			vector<int> timeData;

			timeData = parser.extractTime("15:30", 0);
			Assert::AreEqual(1, timeData[1]);
			Assert::AreEqual(1530, timeData[0]);

			timeData = parser.extractTime("330pm", 0);
			Assert::AreEqual(1, timeData[1]);
			Assert::AreEqual(1530, timeData[0]);

			timeData = parser.extractTime("15:00", 0);
			Assert::AreEqual(1, timeData[1]);
			Assert::AreEqual(1500, timeData[0]);

			timeData = parser.extractTime("3pm", 0);
			Assert::AreEqual(1, timeData[1]);
			Assert::AreEqual(1500, timeData[0]);

			timeData = parser.extractTime("00:30", 0);
			Assert::AreEqual(1, timeData[1]);
			Assert::AreEqual(30, timeData[0]);

			timeData = parser.extractTime("1230am", 0);
			Assert::AreEqual(1, timeData[1]);
			Assert::AreEqual(30, timeData[0]);

			timeData = parser.extractTime("12:30", 0);
			Assert::AreEqual(1, timeData[1]);
			Assert::AreEqual(1230, timeData[0]);

			timeData = parser.extractTime("1230pm", 0);
			Assert::AreEqual(1, timeData[1]);
			Assert::AreEqual(1230, timeData[0]);
		}

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

		TEST_METHOD(DateTest_Opeartors2) {
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

		TEST_METHOD(System_Test1) {
			// test for command add (float, deadline, timed tasks) and the feedback that the system is going to return to the users
			TimeWiseLogic _logic;
			std::string feedback1 = _logic.processCommand("add do laundry");
			std::string expected1 = "Task: 'do laundry !low' has been successfully added to your schedule.";
			Assert::AreEqual(feedback1,expected1);
			/*whether this test case passes or not depends on the current day.
			before testing, we need to change the current day in the expected output string to make it pass
			std::string feedback2 = _logic.processCommand("add do laundry from 9am to 10am");
			std::string expected2 = "Task: 'do laundry on 5/4/2014 from 0900 to 1000 !low' has been successfully added to your schedule.";
			Assert::AreEqual(feedback2,expected2);*/
			std::string feedback3 = _logic.processCommand("add do laundry by 21/05");
			std::string expected3 = "Task: 'do laundry on 21/5/2014 !low' has been successfully added to your schedule.";
			Assert::AreEqual(feedback3,expected3);
			/*Whether this test case passes depend on what date tomorrow would be
			We have to change the tomorrow date for it to pass
			std::string feedback4 = _logic.processCommand("add do laundry tomorrow at 9pm");
			std::string expected4 = "Task: 'do laundry on 5/4/2014 at 2100 !low' has been successfully added to your schedule.";
			Assert::AreEqual(feedback4,expected4);*/
			std::string feedback5 = _logic.processCommand("add do laundry from 21/5 to 22/5");
			std::string expected5 = "Task: 'do laundry on 21/5/2014 to 22/5/2014 !low' has been successfully added to your schedule.";
			Assert::AreEqual(feedback5,expected5);
			std::string feedback6 = _logic.processCommand("add do laundry from 21/5 to 22/5 from 9pm to 10pm");
			std::string expected6 = "Task: 'do laundry on 21/5/2014 to 22/5/2014 from 2100 to 2200 !low' has been successfully added to your schedule.";
			Assert::AreEqual(feedback6,expected6);
			std::string feedback7 = _logic.processCommand("add do laundry !high #household");
			std::string expected7 = "Task: 'do laundry !high #household' has been successfully added to your schedule.";
			Assert::AreEqual(feedback7,expected7);
			std::string feedback8 = _logic.processCommand("do laundry !high #household");
			std::string expected8 = "Task: 'do laundry !high #household' has been successfully added to your schedule.";
			Assert::AreEqual(feedback8,expected8);
			std::string feedback9 = _logic.processCommand("add");
			std::string expected9 = "Error! No input detected";
			Assert::AreEqual(feedback9,expected9);
			/*std::string feedback10 = _logic.processCommand("");
			std::string expected10 = "cannot enter empty input!";
			Assert::AreEqual(feedback10,expected10);*/
		}

		TEST_METHOD(System_Test2) {
			TimeWiseLogic _logic;
			//Test for command delete and the feedback that the system return to user
			std::string cmd1 = _logic.processCommand("add do laundry");
			std::string cmd2 = _logic.processCommand("add do laundry by 21/05");
			std::string cmd3 = _logic.processCommand("add do laundry from 21/5 to 22/5");
			std::string cmd4 = _logic.processCommand("add do laundry from 21/5 to 22/5 from 9pm to 10pm");
			std::string cmd5 = _logic.processCommand("add do laundry #chores");
			//std::string cmd6 = _logic.processCommand("add do laundry tomorrow at 9pm");
			//std::string cmd7 = _logic.processCommand("add do laundry from 9 am to 10 am");
			std::string cmd8 = _logic.processCommand("delete 1");
			std::string expected8 = "Task: 'do laundry !low #chores' has been successfully removed from your schedule.";
			Assert::AreEqual(cmd8,expected8);
			std::string cmd9 = _logic.processCommand("delete");
			std::string expected9 = "Error! No input detected";
			/*Assert::AreEqual(cmd9,expected9);
			std::string cmd10 = _logic.processCommand("delete 56");
			std::string expected10 = "Error! The task index that you entered is out of range.";
			Assert::AreEqual(cmd10,expected10);*/
			std::string cmd11 = _logic.processCommand("delete -3");
			std::string expected12 = "Error! The task index that you entered is not a number.";
			Assert::AreEqual(cmd9,expected9);
		    /*int _size = _logic.getTaskList().undoneSize();
			int expectedSize = -1;
			Assert::AreEqual(_size, expectedSize);*/

		}
		TEST_METHOD(System_Test3) {
			//test for command done/undone and the feedback that the system is going to return
			TimeWiseLogic _logic;
			std::string cmd1 = _logic.processCommand("add do laundry");
			//std::string cmd7 = _logic.processCommand("add do laundry from 9 am to 10 am");
			std::string cmd2 = _logic.processCommand("add do laundry by 21/05");
			//std::string cmd8 = _logic.processCommand("add do laundry tomorrow at 9pm");
			std::string cmd3 = _logic.processCommand("add do laundry from 21/5 to 22/5");
			std::string cmd4 = _logic.processCommand("add do laundry from 21/5 to 22/5 from 9pm to 10pm");
			std::string cmd5 = _logic.processCommand("add do laundry #chores");
			std::string cmd6 = _logic.processCommand("done 1");
			std::string expected6 = "Task: 'do laundry !low #chores' has been successfully marked as completed.";
			Assert::AreEqual(cmd6, expected6);
			/*int _undoneSize = _logic.getTaskList().doneSize();
			int expectedUndoneSize = 1;
			Assert::AreEqual(_undoneSize, expectedUndoneSize);
			int _doneSize = _logic.getTaskList().doneSize();
			int expectedDoneSize = 1;
			Assert::AreEqual(_doneSize, expectedDoneSize);*/
			std::string cmd9 = _logic.processCommand("done");
			std::string expected9 = "Error! No input detected";
			Assert::AreEqual(cmd9,expected9);
			std::string cmd10 = _logic.processCommand("done 12");
			std::string expected10 = "Error! The task index that you entered is out of range.";
			Assert::AreEqual(cmd10,expected10);
			std::string cmd11 = _logic.processCommand("done -3");
			std::string expected11 = "Error! The task index that you entered is not a number.";
			Assert::AreEqual(cmd11,expected11);
			std::string cmd12 = _logic.processCommand("undone 1");
			std::string expected12 = "Task: 'do laudry on 21/4/2014 to 22/4/2014 !low' has been successfully marked as uncompleted.";
			Assert::AreEqual(cmd12,expected12);

		}
		TEST_METHOD(System_Test4) {
			TimeWiseLogic _logic;
		    //test for command clear and the feedback that the system is going to return to user
			std::string cmd1 = _logic.processCommand("add do laudry");
			std::string cmd2 = _logic.processCommand("add do laudry from 9 am to 10 am");
			std::string cmd3 = _logic.processCommand("add do laudry by 21/05");
			std::string cmd4 = _logic.processCommand("add do laudry tomorrow at 9pm");
			std::string cmd5 = _logic.processCommand("add do laudry from 21/4 to 22/4");
			std::string cmd6 = _logic.processCommand("add do laudry from 21/4 to 22/4 9pm to 10 pm");
			std::string cmd7 = _logic.processCommand("add do laudry !high #household");
			std::string cmd8 = _logic.processCommand("done 5");
			std::string cmd9 = _logic.processCommand("done 6");
			
			int _undoneSize1 = _logic.getTaskList().undoneSize();
			int expectedUndoneSize1 = 5;
			Assert::AreEqual(_undoneSize1,expectedUndoneSize1);
			std::string cmd10 = _logic.processCommand("clear undone");
			std::string expected10 = "All uncompleted tasks are removed from your schedule!";
			Assert::AreEqual(cmd10,expected10);
			int _undoneSize2 = _logic.getTaskList().undoneSize();
			int expectedUndoneSize2 = 0;
			Assert::AreEqual(_undoneSize2,expectedUndoneSize2);

			int _doneSize1 = _logic.getTaskList().doneSize();
			int expectedDoneSize1 = 2;
			Assert::AreEqual(_doneSize1, expectedDoneSize1);
			std::string cmd11 = _logic.processCommand("clear done");
			std::string expected11 = "All completed tasks are removed from your schedule!";
			Assert::AreEqual(cmd11,expected11);
			int _doneSize2 = _logic.getTaskList().doneSize();
			int expectedDoneSize2 = 0;
			Assert::AreEqual(_doneSize2, expectedDoneSize2);
			std::string cmd12 = _logic.processCommand("add do laudry");
			std::string cmd13 = _logic.processCommand("add do laudry from 9 am to 10 am");
			std::string cmd14 = _logic.processCommand("add do laudry by 21/05");
			std::string cmd15 = _logic.processCommand("add do laudry tomorrow at 9pm");
			std::string cmd16 = _logic.processCommand("add do laudry from 21/4 to 22/4");
			std::string cmd17 = _logic.processCommand("add do laudry from 21/4 to 22/4 9pm to 10 pm");
			std::string cmd18 = _logic.processCommand("add do laudry !high #household");
			std::string cmd19 = _logic.processCommand("done 5");
			std::string cmd20 = _logic.processCommand("done 6");
			std::string cmd21 = _logic.processCommand("clear all");
			std::string expected21 = "All tasks are removed from your schedule!";
			Assert::AreEqual(cmd21, expected21);
			int overallSize = _logic.getTaskList().doneSize() + _logic.getTaskList().undoneSize();
			Assert::AreEqual(0, overallSize);
			

		}

};
}