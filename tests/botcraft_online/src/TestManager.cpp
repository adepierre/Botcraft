#include "TestManager.hpp"
#include "MinecraftServer.hpp"


TestManager::TestManager()
{

}

TestManager::~TestManager()
{

}

TestManager& TestManager::GetInstance()
{
	static TestManager instance;
	return instance;
}

void TestManagerListener::testRunStarting(Catch::TestRunInfo const& test_run_info)
{
	// Make sure the server is running and ready before the first test run
	MinecraftServer::GetInstance().Initialize();
}

void TestManagerListener::testCaseStarting(Catch::TestCaseInfo const& test_info)
{

}

void TestManagerListener::testCaseEnded(Catch::TestCaseStats const& test_case_stats)
{

}

void TestManagerListener::sectionStarting(Catch::SectionInfo const& section_info)
{

}

void TestManagerListener::sectionEnded(Catch::SectionStats const& section_stats)
{

}
