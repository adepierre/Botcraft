#include "TestManager.hpp"
#include "MinecraftServer.hpp"

#include <catch2/catch_test_case_info.hpp>

#include <protocolCraft/Types/NBT/NBT.hpp>

#include <botcraft/Network/NetworkManager.hpp>

#include <fstream>
#include <sstream>
#include <regex>

TestManager::TestManager()
{
	current_offset = {spacing_x, 2, 2 * spacing_z };
	current_test_success = false;
	current_test_index = 0;
	current_section_index = 0;
	current_section_stack_depth = 0;
	bot_index = 0;
}

TestManager::~TestManager()
{

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


#if PROTOCOL_VERSION == 340
void TestManager::SetBlock(const std::string& name, const Botcraft::Position& pos, const int block_variant, const std::map<std::string, std::string>& metadata) const
{
	MakeSureLoaded(pos);
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
			command << k << ":";
			if (v.find(' ') != std::string::npos ||
				v.find(',') != std::string::npos ||
				v.find(':') != std::string::npos)
			{
				// Make sure the whole string is between quotes and all internal quotes are escaped
				command << "\"" << std::regex_replace(v, std::regex("\\\\?\""), "\\\"") << "\"";
			}
			else
			{
				command << v;
			}
			command << (index == metadata.size() - 1 ? "" : ",");
			index += 1;
		}
		command << "}";
	}
	MinecraftServer::GetInstance().SendLine(command.str());
	MinecraftServer::GetInstance().WaitLine(".*: Block placed.*", 2000);
}
#endif

void TestManager::SetGameMode(const std::string& name, const Botcraft::GameType gamemode) const
{
	std::string gamemode_string;
	switch (gamemode)
	{
	case Botcraft::GameType::Survival:
		gamemode_string = "survival";
		break;
	case Botcraft::GameType::Creative:
		gamemode_string = "creative";
		break;
	case Botcraft::GameType::Adventure:
		gamemode_string = "adventure";
		break;
	case Botcraft::GameType::Spectator:
		gamemode_string = "spectator";
		break;
	default:
		return;
	}
	std::stringstream command;
	command
		<< "gamemode" << " "
		<< gamemode_string << " "
		<< name;
	MinecraftServer::GetInstance().SendLine(command.str());
	MinecraftServer::GetInstance().WaitLine(".*? Set " + name + "'s game mode to.*", 2000);
}

void TestManager::Teleport(const std::string& name, const Botcraft::Vector3<double>& pos) const
{
	std::stringstream command;
	command
		<< "teleport" << " "
		<< name << " "
		<< pos.x << " "
		<< pos.y << " "
		<< pos.z << " ";
	MinecraftServer::GetInstance().SendLine(command.str());
	MinecraftServer::GetInstance().WaitLine(".*?Teleported " + name + " to.*", 2000);
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

void TestManager::CreateTPSign(const Botcraft::Position& src, const Botcraft::Vector3<double>& dst, const std::vector<std::string>& texts, const std::string& facing) const
{
	std::map<std::string, std::string> lines;
	for (size_t i = 0; i < std::min(texts.size(), 4ULL); ++i)
	{
		std::stringstream line;
		line
			<< "{"
			<< "\"text\":\"" << texts[i] << "\"";
		if (i == 0)
		{
			line << ","
				<< "\"underlined\"" << ":" << "true" << ","
				<< "\"clickEvent\"" << ":" << "{"
					<< "\"action\"" << ":" << "\"run_command\"" << ","
					// TODO: add "facing" args on /teleport for 1.13+
					<< "\"value\"" << ":" << "\"teleport @s " << dst.x << " " << dst.y << " " << dst.z << "\""
				<< "}";
		}
		line << "}";
		lines.insert({ "Text" + std::to_string(i + 1), line.str() });
	}

	int block_variant = 0;
	if (facing == "north")
	{
		block_variant = 0;
	}
	else if (facing == "south")
	{
		block_variant = 8;
	}
	else if (facing == "east")
	{
		block_variant = 12;
	}
	else if (facing == "west")
	{
		block_variant = 4;
	}

	SetBlock("standing_sign", src, block_variant, lines);
}

void TestManager::LoadStructure(const std::string& filename, const Botcraft::Position& pos, const Botcraft::Position& load_offset) const
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

void TestManager::MakeSureLoaded(const Botcraft::Position& pos) const
{
	Teleport(chunk_loader_name, pos);
}

void TestManager::testRunStarting(Catch::TestRunInfo const& test_run_info)
{
	// Make sure the server is running and ready before the first test run
	MinecraftServer::GetInstance().Initialize();
	// Retrieve header size
	header_size = GetStructureSize("_header_running");
	chunk_loader = GetBot();
	chunk_loader_name = chunk_loader->GetNetworkManager()->GetMyName();
	SetGameMode(chunk_loader_name, Botcraft::GameType::Spectator);
}

void TestManager::testRunEnded(Catch::TestRunStats const& test_run_info)
{
	if (chunk_loader)
	{
		chunk_loader->Disconnect();
	}
}

void TestManager::testCaseStarting(Catch::TestCaseInfo const& test_info)
{
	// Retrieve test structure size
	current_test_size = GetStructureSize(test_info.name);
	LoadStructure("_header_running", Botcraft::Position(current_offset.x, 0, spacing_z - header_size.z));current_test_name = test_info.name;
	current_test_success = true;
	current_offset.z = 2 * spacing_z;
	current_section_index = 0;
}

void TestManager::testCaseEnded(Catch::TestCaseStats const& test_case_stats)
{
	LoadStructure(current_test_success ? "_header_success" : "_header_fail", Botcraft::Position(current_offset.x, 0, spacing_z - header_size.z));
	// Create Sign to TP to current test
	CreateTPSign(Botcraft::Position(-2 * (current_test_index + 1), 2, -2), Botcraft::Vector3(current_offset.x, 2, spacing_z - 1), { current_test_name }, "north");
	// Create sign to TP to TP back to spawn
	CreateTPSign(Botcraft::Position(current_offset.x, 2, spacing_z - 1), Botcraft::Vector3(-2 * (current_test_index + 1), 2, -2), { current_test_name }, "south");
	current_test_index += 1;
	current_offset.x += std::max(current_test_size.x, header_size.x) + spacing_x;
}

void TestManager::sectionStarting(Catch::SectionInfo const& section_info)
{
	if (current_section_stack_depth == 0)
	{
		// Load header
		current_header_position = current_offset - Botcraft::Position(0, 2, 0);
		LoadStructure("_header_running", current_header_position);
		current_offset.z += header_size.z;
		// Load test structure
		LoadStructure(current_test_name, current_offset + Botcraft::Position(0, -1, 0), Botcraft::Position(0, 1, 0));
	}
	section_stack.push_back(section_info.name);
	current_section_stack_depth += 1;
}

void TestManager::sectionEnded(Catch::SectionStats const& section_stats)
{
	current_section_stack_depth -= 1;
	if (current_section_stack_depth == 0)
	{
		// Replace header with proper test result
		LoadStructure(section_stats.assertions.allOk() ? "_header_success" : "_header_fail", current_header_position);
		// Create TP sign for the section that just ended
		CreateTPSign(Botcraft::Position(-2 * (current_test_index + 1), 2, -2 * (current_section_index + 2)), Botcraft::Vector3(current_offset.x, 2, current_offset.z - 1), section_stack, "north");
		// Create back to spawn sign for the section that just ended
		CreateTPSign(Botcraft::Position(current_offset.x, 2, current_offset.z - 1), Botcraft::Vector3(-2 * (current_test_index + 1), 2, -2 * (current_section_index + 2)), section_stack, "south");
		current_test_success &= section_stats.assertions.allOk();
		current_offset.z += current_test_size.z + spacing_z;
		current_section_index += 1;
		section_stack.clear();
	}
}





void TestManagerListener::testRunStarting(Catch::TestRunInfo const& test_run_info)
{
	TestManager::GetInstance().testRunStarting(test_run_info);
}

void TestManagerListener::testRunEnded(Catch::TestRunStats const& test_run_info)
{
	TestManager::GetInstance().testRunEnded(test_run_info);
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
