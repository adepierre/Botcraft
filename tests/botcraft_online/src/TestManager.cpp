#include "TestManager.hpp"
#include "MinecraftServer.hpp"

#include <catch2/catch_test_case_info.hpp>

#include <protocolCraft/Types/NBT/NBT.hpp>

#include <fstream>
#include <sstream>

TestManager::TestManager()
{
	current_offset = {spacing_x, 2, 0};
	current_test_success = false;
}

TestManager::~TestManager()
{

}

Botcraft::Position TestManager::GetStructureSize(const std::string& filename) const
{
	const std::filesystem::path filepath = MinecraftServer::GetInstance().GetServerPath() / "world" / "structures" / (filename + ".nbt");
	if (!std::filesystem::exists(filepath))
	{
		return GetStructureSize("_default");
	}
	std::ifstream file(filepath.string(), std::ios::in | std::ios::binary);
	file.unsetf(std::ios::skipws);

	ProtocolCraft::NBT::Value nbt;
	file >> nbt;
	file.close();

	// TODO: deal with recursive structures (structures containing structure blocks) ?
	return nbt["size"].as_list_of<int>();
}

TestManager& TestManager::GetInstance()
{
	static TestManager instance;
	return instance;
}

const Botcraft::Position& TestManager::GetCurrentOffset() const
{
	return current_offset;
}

void TestManager::testRunStarting(Catch::TestRunInfo const& test_run_info)
{
	// Make sure the server is running and ready before the first test run
	MinecraftServer::GetInstance().Initialize();
	// Retrieve header size
	header_size = GetStructureSize("_header_running");
}

void TestManager::testCaseStarting(Catch::TestCaseInfo const& test_info)
{
	// Retrieve test structure size
	current_test_size = GetStructureSize(test_info.name);
	current_test_name = test_info.name;
	current_test_success = true;
}

void TestManager::testCaseEnded(Catch::TestCaseStats const& test_case_stats)
{
	LoadStructure(current_test_success ? "_header_success" : "_header_fail", Botcraft::Position(current_offset.x, 0, -header_size.z - spacing_z));
	current_offset.x += std::max(current_test_size.x, header_size.x) + spacing_x;
	current_offset.z = 0;
}

void TestManager::sectionStarting(Catch::SectionInfo const& section_info)
{
	if (section_stack.empty())
	{
		// Load header
		current_header_position = current_offset - Botcraft::Position(0, 2, 0);
		LoadStructure("_header_running", current_header_position);
		current_offset.z += header_size.z;
		// Load test structure
		LoadStructure(current_test_name, current_offset + Botcraft::Position(0, -1, 0), Botcraft::Position(0, 1, 0));
	}
	section_stack.push(section_info.name);
}

void TestManager::sectionEnded(Catch::SectionStats const& section_stats)
{
	section_stack.pop();
	if (section_stack.empty())
	{
		// Replace header with proper test result one
		LoadStructure(section_stats.assertions.allOk() ? "_header_success" : "_header_fail", current_header_position);
		current_test_success &= section_stats.assertions.allOk();
		current_offset.z += current_test_size.z + spacing_z;
	}
}

void TestManager::LoadStructure(const std::string& filename, const Botcraft::Position& pos, const Botcraft::Position& load_offset)
{
	const std::string& loaded = std::filesystem::exists(MinecraftServer::GetInstance().GetServerPath() / "world" / "structures" / (filename + ".nbt")) ?
		filename :
		"_default";
	SetBlock("structure_block", pos, 0, {
		{"mode", "LOAD"},
		{"name", loaded},
		{"posX", std::to_string(load_offset.x)},
		{"posY", std::to_string(load_offset.y)},
		{"posZ", std::to_string(load_offset.z)},
		{"showboundingbox", "1"}
	});
	SetBlock("redstone_block", pos + Botcraft::Position(0, 1, 0));
}

#if PROTOCOL_VERSION == 340
void TestManager::SetBlock(const std::string& name, const Botcraft::Position& pos, const int block_variant, const std::map<std::string, std::string>& metadata)
{
	std::stringstream command;
	command
		<< "setblock" << " "
		<< pos.x << " "
		<< pos.y << " "
		<< pos.z << " "
		<< ((name.size() > 10 && name.substr(0, 10) == "minecraft:") ? "" : "minecraft:") << name << " "
		<< block_variant << " "
		<< "replace";
	if (!metadata.empty())
	{
		command << " {";
		int index = 0;
		for (const auto& [k, v] : metadata)
		{
			command << k << ":" << v << (index == metadata.size() - 1 ? "" : ",");
			index += 1;
		}
		command << "}";
	}
	MinecraftServer::GetInstance().SendLine(command.str());
	MinecraftServer::GetInstance().WaitLine(".*: Block placed.*", 2000);
}
#endif

void TestManagerListener::testRunStarting(Catch::TestRunInfo const& test_run_info)
{
	TestManager::GetInstance().testRunStarting(test_run_info);
}

void TestManagerListener::testCaseStarting(Catch::TestCaseInfo const& test_info)
{
	TestManager::GetInstance().testCaseStarting(test_info);
}

void TestManagerListener::testCaseEnded(Catch::TestCaseStats const& test_case_stats)
{
	TestManager::GetInstance().testCaseEnded(test_case_stats);
}

void TestManagerListener::sectionStarting(Catch::SectionInfo const& section_info)
{
	TestManager::GetInstance().sectionStarting(section_info);
}

void TestManagerListener::sectionEnded(Catch::SectionStats const& section_stats)
{
	TestManager::GetInstance().sectionEnded(section_stats);
}
CATCH_REGISTER_LISTENER(TestManagerListener)
