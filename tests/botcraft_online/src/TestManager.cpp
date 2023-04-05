#include "TestManager.hpp"
#include "MinecraftServer.hpp"

#include <catch2/catch_test_case_info.hpp>

#include <protocolCraft/Types/NBT/NBT.hpp>

#include <botcraft/Network/NetworkManager.hpp>

#include <fstream>
#include <sstream>
#include <regex>

std::string ReplaceCharacters(const std::string& in, const std::vector<std::pair<char, std::string>>& replacements = { {'"', "\\\""}, {'\n', "\\n"} });

TestManager::TestManager()
{
	current_offset = {spacing_x, 2, 2 * spacing_z };
	current_test_index = 0;
	bot_index = 0;
	chunk_loader_id = -1;
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

#if PROTOCOL_VERSION > 340
void TestManager::SetBlock(const std::string& name, const Botcraft::Position& pos, const std::map<std::string, std::string>& blockstates, const std::map<std::string, std::string>& metadata) const
#else
void TestManager::SetBlock(const std::string& name, const Botcraft::Position& pos, const int block_variant, const std::map<std::string, std::string>& metadata) const
#endif
{
	MakeSureLoaded(pos);
	std::stringstream command;
	command
		<< "setblock" << " "
		<< pos.x << " "
		<< pos.y << " "
		<< pos.z << " "
		<< ((name.size() > 10 && name.substr(0, 10) == "minecraft:") ? "" : "minecraft:") << name;
#if PROTOCOL_VERSION > 340
	if (!blockstates.empty())
	{
		command << "[";
		int index = 0;
		for (const auto& [k, v] : blockstates)
		{
			command << k << "=";
			if (v.find(' ') != std::string::npos ||
				v.find(',') != std::string::npos ||
				v.find(':') != std::string::npos)
			{
				// Make sure the whole string is between quotes and all internal quotes are escaped
				command << "\"" << ReplaceCharacters(v) << "\"";
			}
			else
			{
				command << v;
			}
			command << (index == blockstates.size() - 1 ? "" : ",");
			index += 1;
		}
		command << "]";
	}
#else
	command << " "
		<< block_variant << " "
		<< "replace" << " ";
#endif
	if (!metadata.empty())
	{
		command << "{";
		int index = 0;
		for (const auto& [k, v] : metadata)
		{
			command << k << ":";
			if (v.find(' ') != std::string::npos ||
				v.find(',') != std::string::npos ||
				v.find(':') != std::string::npos)
			{
				// Make sure the whole string is between quotes and all internal quotes are escaped
				command << "\"" << ReplaceCharacters(v) << "\"";
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
#if PROTOCOL_VERSION > 340
	command << " replace";
#endif
	MinecraftServer::GetInstance().SendLine(command.str());
#if PROTOCOL_VERSION > 340
	MinecraftServer::GetInstance().WaitLine(
		".*: Changed the block at "
		+ std::to_string(pos.x) + ", "
		+ std::to_string(pos.y) + ", "
		+ std::to_string(pos.z) + ".*", 2000);
#else
	MinecraftServer::GetInstance().WaitLine(".*: Block placed.*", 2000);
#endif
}

void TestManager::CreateBook(const Botcraft::Position& pos, const std::vector<std::string>& pages, const std::string& facing, const std::string& title, const std::string& author, const std::vector<std::string>& description)
{
	int facing_id = 0;
	if (facing == "south")
	{
		facing_id = 0;
	}
	else if (facing == "west")
	{
		facing_id = 1;
	}
	else if (facing == "north")
	{
		facing_id = 2;
	}
	else if (facing == "east")
	{
		facing_id = 3;
	}

	std::stringstream command;

	command
#if PROTOCOL_VERSION < 477
		<< "summon" << " "
		<< "minecraft:item_frame" << " "
#else
		<< "setblock" << " "
#endif
		<< pos.x << " "
		<< pos.y << " "
		<< pos.z << " "
#if PROTOCOL_VERSION < 477
		<< "{Facing:" << facing_id << ","
		<< "Item:{"
#else
		<< "minecraft:lectern"
		<< "[facing=" << facing << ",has_book=true]"
		<< "{"
		<< "Book:{"
#endif
			<< "id:\"written_book\"" << ","
			<< "Count:1" << ","
			<< "tag:{"
				<< "pages:[";
	for (size_t i = 0; i < pages.size(); ++i)
	{
		command
			<< "\"{"
			<< "\\\"text\\\"" << ":" << "\\\"" << ReplaceCharacters(pages[i], { {'\n', "\\\\n"}, {'"', "\\\\\\\""} }) << "\\\""
			<< "}\"" << ((i < pages.size() - 1) ? "," : "");
	}
	command << "]";
	if (!title.empty())
	{
		command << ","
			<< "title" << ":" << "\"" << ReplaceCharacters(title) << "\"";
	}
	if (!author.empty())
	{
		command << ","
			<< "author" << ":" << "\"" << ReplaceCharacters(author) << "\"";
	}
	if (!description.empty())
	{
		command << "," << "display" << ":"
			<< "{Lore:[";
		for (size_t i = 0; i < description.size(); ++i)
		{
			command
				<< "\""
#if PROTOCOL_VERSION < 735
				// Just a list of strings is working before 1.16(?)
				<< ReplaceCharacters(description[i])
#else
				// After, a JSON text element is required
				<< "{" << "\\\"text\\\"" << ":" << "\\\"" << ReplaceCharacters(description[i], { { '\n', "\\\\n"}, { '"', "\\\\\\\"" } }) << "\\\"" << "}"
#endif
				<< "\"" << ((i < description.size() - 1) ? "," : "");
		}
		command << "]}";
	}
	command
		<< "}" // tag
		<< "}" // Item
		<< "}"; // Main

	MinecraftServer::GetInstance().SendLine(command.str());
#if PROTOCOL_VERSION > 340 && PROTOCOL_VERSION < 477
	MinecraftServer::GetInstance().WaitLine(".*?: Summoned new Item Frame.*", 2000);
#elif PROTOCOL_VERSION == 340
	MinecraftServer::GetInstance().WaitLine(".*?: Object successfully summoned.*", 2000);
#else
	MinecraftServer::GetInstance().WaitLine(
		".*: Changed the block at "
		+ std::to_string(pos.x) + ", "
		+ std::to_string(pos.y) + ", "
		+ std::to_string(pos.z) + ".*", 2000);
#endif
}

void TestManager::Teleport(const std::string& name, const Botcraft::Vector3<double>& pos) const
{
	std::stringstream command;
	command
		<< "teleport" << " "
		<< name << " "
		<< pos.x << " "
		<< pos.y << " "
		<< pos.z;
	MinecraftServer::GetInstance().SendLine(command.str());
	MinecraftServer::GetInstance().WaitLine(".*?Teleported " + name + " to.*", 2000);
}

Botcraft::Position TestManager::GetStructureSize(const std::string& filename) const
{
	const std::string no_space_filename = ReplaceCharacters(filename, { {' ', "_"} });
	const std::filesystem::path filepath = MinecraftServer::GetInstance().GetStructurePath() / (no_space_filename + ".nbt");

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

void TestManager::CreateTPSign(const Botcraft::Position& src, const Botcraft::Vector3<double>& dst, const std::vector<std::string>& texts, const std::string& facing, const TestSucess success) const
{
	Botcraft::Position offset_target;
	int block_rotation = 0;
	if (facing == "north")
	{
		block_rotation = 0;
		offset_target = dst + Botcraft::Position(0, 0, -1);
	}
	else if (facing == "south")
	{
		block_rotation = 8;
		offset_target = dst + Botcraft::Position(0, 0, 1);
	}
	else if (facing == "east")
	{
		block_rotation = 12;
		offset_target = dst + Botcraft::Position(-1, 0, 0);
	}
	else if (facing == "west")
	{
		block_rotation = 4;
		offset_target = dst + Botcraft::Position(1, 0, 0);
	}
	std::string text_color;
	switch (success)
	{
	case TestSucess::None:
		text_color = "black";
		break;
	case TestSucess::Success:
		text_color = "dark_green";
		break;
	case TestSucess::Failure:
		text_color = "red";
		break;
	case TestSucess::ExpectedFailure:
		text_color = "gold";
		break;
	}
	std::map<std::string, std::string> lines;
	for (size_t i = 0; i < std::min(texts.size(), static_cast<size_t>(4)); ++i)
	{
		std::stringstream line;
		line
			<< "{"
			<< "\"text\":\"" << texts[i] << "\"" << ",";
		if (i == 0)
		{
			line
				<< "\"underlined\"" << ":" << "false" << ","
				<< "\"color\"" << ":" << "\"" << "black" << "\"" << ","
				<< "\"clickEvent\"" << ":" << "{"
					<< "\"action\"" << ":" << "\"run_command\"" << ","
					<< "\"value\"" << ":" << "\""
#if PROTOCOL_VERSION > 340
					<< "teleport @s" << " " << offset_target.x << " " << offset_target.y << " " << offset_target.z
					<< " " << "facing" << " " << dst.x << " " << dst.y << " " << dst.z
#else
					<< "teleport @s" << " " << dst.x << " " << dst.y << " " << dst.z
#endif
					<< "\""
				<< "}";
		}
		else
		{
			line
				<< "\"underlined\"" << ":" << "true" << ","
				<< "\"color\"" << ":" << "\"" << text_color << "\"";
		}
		line << "}";
		lines.insert({ "Text" + std::to_string(i + 1), line.str() });
	}
	// There is a bug in version 1.14 (and prereleases) that requires all 4 lines
	// to be specified or the server can't read the text. See: https://bugs.mojang.com/browse/MC-144316
#if PROTOCOL_VERSION > 459 && PROTOCOL_VERSION < 478
	for (size_t i = texts.size(); i < 4ULL; ++i)
	{
		lines.insert({ "Text" + std::to_string(i + 1), "{\"text\":\"\"}" });
	}
#endif

	SetBlock(
#if PROTOCOL_VERSION < 393
		"standing_sign",
#elif PROTOCOL_VERSION < 477
		"sign",
#else
		"oak_sign",
#endif
		src,
#if PROTOCOL_VERSION > 340
		{
			{ "rotation", std::to_string(block_rotation) }
		},
#else
		block_rotation,
#endif
		lines
	);
}

void TestManager::LoadStructure(const std::string& filename, const Botcraft::Position& pos, const Botcraft::Position& load_offset) const
{
	const std::string no_space_filename = ReplaceCharacters(filename, { {' ', "_"} });
	const std::string& loaded = std::filesystem::exists(MinecraftServer::GetInstance().GetStructurePath() / (no_space_filename + ".nbt")) ?
		no_space_filename :
		"_default";

	SetBlock(
		"structure_block",
		pos,
#if PROTOCOL_VERSION > 340
		{},
#else
		0,
#endif
		{
			{"mode", "LOAD"},
			{"name", loaded},
			{"posX", std::to_string(load_offset.x)},
			{"posY", std::to_string(load_offset.y)},
			{"posZ", std::to_string(load_offset.z)},
			{"showboundingbox", "1"}
		}
	);
	SetBlock("redstone_block", pos + Botcraft::Position(0, 1, 0));
}

void TestManager::MakeSureLoaded(const Botcraft::Position& pos) const
{
	// Don't teleport if we're close enough
	const double threshold_dist = Botcraft::CHUNK_WIDTH * (MinecraftServer::options.view_distance - 3);
	if (pos.SqrDist(chunk_loader_position) < threshold_dist * threshold_dist)
	{
		return;
	}
	Teleport(chunk_loader_name, pos);
	chunk_loader_position = pos;
}

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


void TestManager::testRunStarting(Catch::TestRunInfo const& test_run_info)
{
	// Make sure the server is running and ready before the first test run
	MinecraftServer::GetInstance().Initialize();
	// Retrieve header size
	header_size = GetStructureSize("_header_running");
	chunk_loader = GetBot<Botcraft::ConnectionClient>(chunk_loader_name, chunk_loader_id, chunk_loader_position, Botcraft::GameType::Spectator);
}

void TestManager::testCaseStarting(Catch::TestCaseInfo const& test_info)
{
	// Retrieve test structure size
	current_test_size = GetStructureSize(test_info.name);
	LoadStructure("_header_running", Botcraft::Position(current_offset.x, 0, spacing_z - header_size.z));
	current_offset.z = 2 * spacing_z;
}

void TestManager::testCasePartialStarting(Catch::TestCaseInfo const& test_info, uint64_t part_number)
{
	// Load header
	current_header_position = current_offset - Botcraft::Position(0, 2, 0);
	LoadStructure("_header_running", current_header_position);
	current_offset.z += header_size.z;
	// Load test structure
	LoadStructure(test_info.name, current_offset + Botcraft::Position(0, -1, 0), Botcraft::Position(0, 1, 0));
	current_test_case_failures.clear();
	section_stack = { std::filesystem::path(test_info.lineInfo.file).stem().string() };
}

void TestManager::sectionStarting(Catch::SectionInfo const& section_info)
{
	section_stack.push_back(section_info.name);
}

void TestManager::assertionEnded(Catch::AssertionStats const& assertion_stats)
{
	if (!assertion_stats.assertionResult.succeeded())
	{
		const std::filesystem::path file_path = std::filesystem::relative(assertion_stats.assertionResult.getSourceInfo().file, BASE_SOURCE_DIR);
		current_test_case_failures.push_back(
			ReplaceCharacters(file_path.string(), {{'\\', "/"}}) + ":" +
			std::to_string(assertion_stats.assertionResult.getSourceInfo().line) + "\n\n" +
			assertion_stats.assertionResult.getExpressionInMacro() + "\n\n"
			"with expansion:" + "\n" +
			assertion_stats.assertionResult.getExpandedExpression()
		);
	}
}

void TestManager::testCasePartialEnded(Catch::TestCaseStats const& test_case_stats, uint64_t part_number)
{
	const bool passed = test_case_stats.totals.assertions.allPassed();
	// Replace header with proper test result
	LoadStructure(passed ? "_header_success" : (test_case_stats.testInfo->okToFail() ? "_header_expected_fail" : "_header_fail"), current_header_position);
	// Create TP sign for the partial that just ended
	CreateTPSign(
		Botcraft::Position(-2 * (current_test_index + 1), 2, -2 * part_number - 5),
		Botcraft::Vector3(current_offset.x, 2, current_offset.z - 1),
		section_stack, "north", passed ? TestSucess::Success : (test_case_stats.testInfo->okToFail() ? TestSucess::ExpectedFailure : TestSucess::Failure)
	);
	// Create back to spawn sign for the section that just ended
	CreateTPSign(
		Botcraft::Position(current_offset.x, 2, current_offset.z - 1),
		Botcraft::Vector3(-2 * (current_test_index + 1), 2, -2 * static_cast<int>(part_number) - 5),
		section_stack, "south", passed ? TestSucess::Success : (test_case_stats.testInfo->okToFail() ? TestSucess::ExpectedFailure : TestSucess::Failure)
	);
	if (!passed)
	{
		CreateBook(
			Botcraft::Position(current_offset.x + 1, 2, current_offset.z - header_size.z),
			current_test_case_failures,
			"north",
			test_case_stats.testInfo->name + "#" + std::to_string(part_number),
			"Botcraft Test Framework",
			section_stack
		);
	}
	current_offset.z += current_test_size.z + spacing_z;
	
	// Kill all items that could exist on the floor
	MinecraftServer::GetInstance().SendLine("kill @e[type=item]");
#if PROTOCOL_VERSION > 340
	// In 1.12.2 server sends one line per entity killed so we can't wait without knowing
	// how many there were. Just assume the command worked
	MinecraftServer::GetInstance().WaitLine(".*?: (?:Killed|No entity was found).*", 2000);
#endif
}

void TestManager::testCaseEnded(Catch::TestCaseStats const& test_case_stats)
{
	const bool passed = test_case_stats.totals.assertions.allPassed();
	LoadStructure(passed ? "_header_success" : (test_case_stats.testInfo->okToFail() ? "_header_expected_fail" : "_header_fail"), Botcraft::Position(current_offset.x, 0, spacing_z - header_size.z));
	// Create Sign to TP to current test
	CreateTPSign(
		Botcraft::Position(-2 * (current_test_index + 1), 2, -2),
		Botcraft::Vector3(current_offset.x, 2, spacing_z - 1),
		{ std::filesystem::path(test_case_stats.testInfo->lineInfo.file).stem().string(), test_case_stats.testInfo->name },
		"north", passed ? TestSucess::Success : (test_case_stats.testInfo->okToFail() ? TestSucess::ExpectedFailure : TestSucess::Failure)
	);
	// Create sign to TP to TP back to spawn
	CreateTPSign(
		Botcraft::Position(current_offset.x, 2, spacing_z - 1),
		Botcraft::Vector3(-2 * (current_test_index + 1), 2, -2),
		{ std::filesystem::path(test_case_stats.testInfo->lineInfo.file).stem().string(), test_case_stats.testInfo->name },
		"south", passed ? TestSucess::Success : (test_case_stats.testInfo->okToFail() ? TestSucess::ExpectedFailure : TestSucess::Failure)
	);
	current_test_index += 1;
	current_offset.x += std::max(current_test_size.x, header_size.x) + spacing_x;
}

void TestManager::testRunEnded(Catch::TestRunStats const& test_run_info)
{
	if (chunk_loader)
	{
		chunk_loader->Disconnect();
	}
}




void TestManagerListener::testRunStarting(Catch::TestRunInfo const& test_run_info)
{
	TestManager::GetInstance().testRunStarting(test_run_info);
}

void TestManagerListener::testCaseStarting(Catch::TestCaseInfo const& test_info)
{
	TestManager::GetInstance().testCaseStarting(test_info);
}

void TestManagerListener::testCasePartialStarting(Catch::TestCaseInfo const& test_info, uint64_t part_number)
{
	TestManager::GetInstance().testCasePartialStarting(test_info, part_number);
}

void TestManagerListener::sectionStarting(Catch::SectionInfo const& section_info)
{
	TestManager::GetInstance().sectionStarting(section_info);
}

void TestManagerListener::assertionEnded(Catch::AssertionStats const& assertion_stats)
{
	TestManager::GetInstance().assertionEnded(assertion_stats);
}

void TestManagerListener::testCasePartialEnded(Catch::TestCaseStats const& test_case_stats, uint64_t part_number)
{
	TestManager::GetInstance().testCasePartialEnded(test_case_stats, part_number);
}

void TestManagerListener::testCaseEnded(Catch::TestCaseStats const& test_case_stats)
{
	TestManager::GetInstance().testCaseEnded(test_case_stats);
}

void TestManagerListener::testRunEnded(Catch::TestRunStats const& test_run_info)
{
	TestManager::GetInstance().testRunEnded(test_run_info);
}
CATCH_REGISTER_LISTENER(TestManagerListener)

std::string ReplaceCharacters(const std::string& in, const std::vector<std::pair<char, std::string>>& replacements)
{
	std::string output;
	output.reserve(in.size());

	for (size_t i = 0; i < in.size(); ++i)
	{
		bool found = false;
		for (size_t j = 0; j < replacements.size(); ++j)
		{
			if (replacements[j].first == in[i])
			{
				output += replacements[j].second;
				found = true;
				break;
			}
		}
		if (!found)
		{
			output += in[i];
		}
	}

	return output;
}
