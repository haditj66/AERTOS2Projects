//############################################### 
//this is an autogenerated file using cgen's macro2 command. Dont modify this file here unless it is in user sections 
//###############################################

#pragma once 

 

#if BUILD_TESTS__TRUE
//** <h4>integration test enders: will end the test in various ways</h4>*// 
//** the following will end the test after a certain time in milli has passed*// 
#define AEITEST_END_TestsAfterTimer_commonHalAOs(timeInMilliBeforeEnd) _AEITEST_END_TestsAfterTimer(timeInMilliBeforeEnd)
#define AEITEST_commonHalAOs(testName, thingToAssert, AssertionMessage) _AEITEST(testName, thingToAssert, AssertionMessage,0,1) 
#define AEITEST_commonHalAOs_MUST_PASS_THIS_MANY(testName, thingToAssert, AssertionMessage, passedOnlyAfterThisManyPasses) _AEITEST(testName, thingToAssert, AssertionMessage, 0,passedOnlyAfterThisManyPasses) 
#define AEITEST_commonHalAOs_IgnoreFirstTests(testName, thingToAssert, AssertionMessage, ignoreFirstRunsNum) _AEITEST(testName, thingToAssert, AssertionMessage, ignoreFirstRunsNum,1) 
#define AEITEST_EndTestsIfFalseAssertion_commonHalAOs(testName, thingToAssert, AssertionMessage) _AEITEST_EndTestsIfFalseAssertion(testName, thingToAssert, AssertionMessage) 
#define AEITEST_END_commonHalAOs _AEITEST_END
#define AEITEST_EXPECT_TEST_TO_RUN_commonHalAOs(testName) _AEITEST_EXPECT_TEST_TO_RUN(testName)
 
#else
#define AEITEST_END_TestsAfterTimer_commonHalAOs(timeInMilliBeforeEnd) 
#define AEITEST_commonHalAOs(testName, thingToAssert, AssertionMessage) 
#define AEITEST_commonHalAOs_MUST_PASS_THIS_MANY(testName, thingToAssert, AssertionMessage, passedOnlyAfterThisManyPasses) 
#define AEITEST_commonHalAOs_IgnoreFirstTests(testName, thingToAssert, AssertionMessage, ignoreFirstRunsNum) 
#define AEITEST_EndTestsIfFalseAssertion_commonHalAOs(testName, thingToAssert, AssertionMessage) 
#define AEITEST_END_commonHalAOs 
#define AEITEST_EXPECT_TEST_TO_RUN_commonHalAOs(testName) 
 
#endif