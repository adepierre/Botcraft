#include <fstream>
#include <sstream>
#include <filesystem>
#include <set>

#include "botcraft/Game/AssetsManager.hpp"
#include "botcraft/Game/World/Biome.hpp"
#include "botcraft/Utilities/Logger.hpp"

#if USE_GUI
#include "botcraft/Renderer/Atlas.hpp"
#endif

#include "protocolCraft/Utilities/Json.hpp"

using namespace ProtocolCraft;

namespace Botcraft
{
    AssetsManager& AssetsManager::getInstance()
    {
        static AssetsManager instance;

        return instance;
    }

    AssetsManager::AssetsManager()
    {
        std::filesystem::path expected_mc_path = ASSETS_PATH + std::string("/minecraft");
        if (!std::filesystem::is_directory(expected_mc_path))
        {
            LOG_FATAL("Minecraft assets folder expected at " << std::filesystem::absolute(expected_mc_path) << " but not found");
            throw std::runtime_error("Minecraft assets not found");
        }
        LOG_INFO("Loading blocks from file...");
        LoadBlocksFile();
        LOG_INFO("Done!");
        LOG_INFO("Loading biomes from file...");
        LoadBiomesFile();
        LOG_INFO("Done!");
        LOG_INFO("Loading items from file...");
        LoadItemsFile();
        LOG_INFO("Done!");
#if USE_GUI
        LOG_INFO("Loading textures...");
        atlas = std::make_unique<Renderer::Atlas>();
        LoadTextures();
        LOG_INFO("Done!");
        LOG_INFO("Updating models with Atlas data...");
        UpdateModelsWithAtlasData();
        LOG_INFO("Done!");
#endif
        LOG_INFO("Clearing cache from memory...");
        ClearCaches();
        LOG_INFO("Done!");
    }

#if PROTOCOL_VERSION < 347 /* < 1.13 */
    const std::unordered_map<int, std::unordered_map<unsigned char, std::unique_ptr<Blockstate> > >& AssetsManager::Blockstates() const
#else
    const std::unordered_map<int, std::unique_ptr<Blockstate> >& AssetsManager::Blockstates() const
#endif
    {
        return blockstates;
    }

    const Blockstate* AssetsManager::GetBlockstate(const BlockstateId id) const
    {
#if PROTOCOL_VERSION < 347 /* < 1.13 */
        auto it = blockstates.find(id.first);
        if (it != blockstates.end())
        {
            auto it2 = it->second.find(id.second);
            if (it2 != it->second.end())
            {
                return it2->second.get();
            }
            else
            {
                return it->second.at(0).get();
            }
        }
        else
        {
            return blockstates.at(-1).at(0).get();
        }
#else
        if (id < flattened_blockstates_size)
        {
            const Blockstate* block = flattened_blockstates[id];
            if (block != nullptr)
            {
                return block;
            }
        }
        auto it = blockstates.find(id);
        if (it != blockstates.end())
        {
            return it->second.get();
        }
        else
        {
            return blockstates.at(-1).get();
        }
#endif
        return nullptr;
    }

#if PROTOCOL_VERSION < 358 /* < 1.13 */
    const std::unordered_map<unsigned char, std::unique_ptr<Biome> >& AssetsManager::Biomes() const
#else
    const std::unordered_map<int, std::unique_ptr<Biome> >& AssetsManager::Biomes() const
#endif
    {
        return biomes;
    }

#if PROTOCOL_VERSION < 358 /* < 1.13 */
    const Biome* AssetsManager::GetBiome(const unsigned char id) const
#else
    const Biome* AssetsManager::GetBiome(const int id) const
#endif
    {
        auto it = biomes.find(id);
        if (it != biomes.end())
        {
            return it->second.get();
        }
        else
        {
            return nullptr;
        }
    }

    const std::unordered_map<ItemId, std::unique_ptr<Item> >& AssetsManager::Items() const
    {
        return items;
    }

    const Item* AssetsManager::GetItem(const ItemId id) const
    {
        auto it = items.find(id);
        if (it != items.end())
        {
            return it->second.get();
        }
        else
        {
#if PROTOCOL_VERSION < 347 /* < 1.13 */
            it = items.find({ id.first, 0 });
            if (it != items.end())
            {
                return it->second.get();
            }
#endif
            return nullptr;
        }
    }

    ItemId AssetsManager::GetItemID(const std::string& item_name) const
    {
        for (const auto& p : items)
        {
            if (p.second->GetName() == item_name)
            {
                return p.first;
            }
        }

#if PROTOCOL_VERSION < 347 /* < 1.13 */
        return { -1, 0 };
#else
        return -1;
#endif
    }

#if USE_GUI
    const Renderer::Atlas* AssetsManager::GetAtlas() const
    {
        return atlas.get();
    }
#endif

    ToolMaterial GetToolMaterialFromString(const std::string& s)
    {
        if (s == "wood")
        {
            return ToolMaterial::Wood;
        }
        else if (s == "gold")
        {
            return ToolMaterial::Gold;
        }
        else if (s == "stone")
        {
            return ToolMaterial::Stone;
        }
        else if (s == "iron")
        {
            return ToolMaterial::Iron;
        }
        else if (s == "diamond")
        {
            return ToolMaterial::Diamond;
        }
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        else if (s == "netherite")
        {
            return ToolMaterial::Netherite;
        }
#endif
        return ToolMaterial::None;
    }

    ToolType GetToolTypeFromString(const std::string& s)
    {
        if (s == "axe")
        {
            return ToolType::Axe;
        }
        else if (s == "hoe")
        {
            return ToolType::Hoe;
        }
        else if (s == "pickaxe")
        {
            return ToolType::Pickaxe;
        }
        else if (s == "shears")
        {
            return ToolType::Shears;
        }
        else if (s == "shovel")
        {
            return ToolType::Shovel;
        }
        else if (s == "sword")
        {
            return ToolType::Sword;
        }
        return ToolType::None;
    }

    void AssetsManager::LoadBlocksFile()
    {
        std::unordered_map<std::string, BlockstateProperties> blockstate_properties;
        std::unordered_map<std::string, std::string> textures;
        std::unordered_map<std::string, std::string> rendering;
#if PROTOCOL_VERSION < 347 /* < 1.13 */
        std::unordered_map<std::string, std::unordered_map<int, TintType> > tint_types;
#else
        std::unordered_map<std::string, TintType> tint_types;
#endif
        const std::string info_file_path = ASSETS_PATH + std::string("/custom/Blocks_info.json");

        Json::Value json;
        try
        {
            std::ifstream file(info_file_path);
            file >> json;
            file.close();
        }
        catch (const std::runtime_error& e)
        {
            LOG_ERROR("Error reading info block file at " << info_file_path << '\n' << e.what());
            return;
        }

        //Load all the info
        for (auto& info : json.get_array())
        {
            std::string name = "";

            if (!info.contains("name") || !info["name"].is_string())
            {
                LOG_ERROR("Error with an element of blockstates info: \n" << info.Dump());
                continue;
            }
            else
            {
                name = info["name"].get_string();
                blockstate_properties[name].name = name;
            }

            if (info.contains("air") && info["air"].is_bool())
            {
                blockstate_properties[name].air = info["air"].get<bool>();
            }

            if (info.contains("transparent") && info["transparent"].is_bool())
            {
                blockstate_properties[name].transparent = info["transparent"].get<bool>();
            }

            if (info.contains("solid") && info["solid"].is_bool())
            {
                blockstate_properties[name].solid = info["solid"].get<bool>();
            }

            if (info.contains("hardness") && info["hardness"].is_number())
            {
                blockstate_properties[name].hardness = info["hardness"].get_number<float>();
            }

            if (info.contains("friction") && info["friction"].is_number())
            {
                blockstate_properties[name].friction = info["friction"].get_number<float>();
            }

            if (!info.contains("render") || !info["render"].is_string())
            {
                rendering[name] = "block";
            }
            else
            {
                rendering[name] = info["render"].get_string();
            }

            if (info.contains("climbable") && info["climbable"].is_bool())
            {
                blockstate_properties[name].climbable = info["climbable"].get<bool>();
            }

            if (info.contains("hazardous") && info["hazardous"].is_bool())
            {
                blockstate_properties[name].hazardous = info["hazardous"].get<bool>();
            }

            // Get breaking tools info
            if (info.contains("tools") && info["tools"].is_array())
            {
                for (const auto& tool : info["tools"].get_array())
                {
                    if (tool.is_string())
                    {
                        const std::string tool_name = tool.get_string();
                        if (tool_name == "any")
                        {
                            blockstate_properties[name].any_tool_harvest = true;
                        }
                        else
                        {
                            ToolType tool_type = GetToolTypeFromString(tool_name);
                            ToolMaterial min_material = (tool_type == ToolType::Shears || tool_type == ToolType::Sword) ? ToolMaterial::None : ToolMaterial::Wood;
                            blockstate_properties[name].best_tools.push_back(
                                BestTool{
                                    tool_type,
                                    min_material,
                                    1.0f
                                });
                        }
                    }
                    else if (tool.is_object())
                    {
                        if (tool.contains("tool") && tool["tool"].is_string())
                        {
                            BestTool best_tool;
                            best_tool.tool_type = GetToolTypeFromString(tool["tool"].get_string());
                            
                            if (tool.contains("min_material") && tool["min_material"].is_string())
                            {
                                best_tool.min_material = GetToolMaterialFromString(tool["min_material"].get_string());
                            }
                            else
                            {
                                // Default min material
                                best_tool.min_material = (best_tool.tool_type == ToolType::Shears || best_tool.tool_type == ToolType::Sword) ? ToolMaterial::None : ToolMaterial::Wood;
                            }

                            if (tool.contains("multiplier") && tool["multiplier"].is_number())
                            {
                                best_tool.multiplier = tool["multiplier"].get<float>();
                            }
                            else
                            {
                                // Default multiplier
                                best_tool.multiplier = 1.0f;
                            }
                            blockstate_properties[name].best_tools.push_back(best_tool);
                        }
                    }
                }
            }

            // Get texture info (used for fluids)
            if (info.contains("texture") && info["texture"].is_string())
            {
                textures[name] = info["texture"].get_string();
            }

            // Get the tint type info (for grass/leaves/water ...)
            if (info.contains("tintType") && info["tintType"].is_string())
            {
                std::string tint_type_string;
                TintType tint_type = TintType::None;
                tint_type_string = info["tintType"].get_string();
                if (tint_type_string == "grass")
                {
                    tint_type = TintType::Grass;
                }
                else if (tint_type_string == "leaves")
                {
                    tint_type = TintType::Leaves;
                }
                else if (tint_type_string == "water")
                {
                    tint_type = TintType::Water;
                }
                else if (tint_type_string == "redstone")
                {
                    tint_type = TintType::Redstone;
                }

#if PROTOCOL_VERSION < 347 /* < 1.13 */
                tint_types[name] = std::unordered_map<int, TintType>({ { -1, tint_type } });
#else
                tint_types[name] = tint_type;
#endif
            }
#if PROTOCOL_VERSION < 347 /* < 1.13 */
            // Before the flattening, we could have different tints for different metadata
            else if (info.contains("tintTypes") && info["tintType"].is_object())
            {
                tint_types[name] = std::unordered_map<int, TintType>({});
                for (const auto& [key, val]: info["tintType"].get_object())
                {
                    TintType tint_type = TintType::None;
                    std::string tint_type_string = val.get_string();
                    
                    if (tint_type_string == "grass")
                    {
                        tint_type = TintType::Grass;
                    }
                    else if (tint_type_string == "leaves")
                    {
                        tint_type = TintType::Leaves;
                    }
                    else if (tint_type_string == "water")
                    {
                        tint_type = TintType::Water;
                    }
                    else if (tint_type_string == "redstone")
                    {
                        tint_type = TintType::Redstone;
                    }

                    tint_types[name][std::stoi(key)] = tint_type;
                }
            }
#endif
            else
            {
#if PROTOCOL_VERSION < 347 /* < 1.13 */
                tint_types[name] = std::unordered_map<int, TintType>({ { -1, TintType::None } });
#else
                tint_types[name] = TintType::None;
#endif
            }
        }

        // Add a default block
#if PROTOCOL_VERSION < 347 /* < 1.13 */
        blockstates[-1];
        blockstates[-1][0] = std::make_unique<Blockstate>(
            BlockstateProperties{
                -1,             //id
                0,              //metadata
                false,          //air
                false,          //transparent
                true,           //solid
                false,          //fluid
                false,          //climbable
                false,          //custom
                false,          //hazardous
                -2.0f,          //hardness
                0.6f,           //friction
                TintType::None, //tint_type
                "default",      //name
            }
        );
#else
        blockstates[-1] = std::make_unique<Blockstate>(
            BlockstateProperties{
                -1,             //id
                false,          //air
                false,          //transparent
                true,           //solid
                false,          //fluid
                false,          //climbable
                false,          //custom
                false,          //hazardous
                -2.0f,          //hardness
                0.6f ,          //friction
                TintType::None, //tint_type
                "default",      //name
            }
        );
#endif

        const std::string file_path = ASSETS_PATH + std::string("/custom/Blocks.json");

        try
        {
            std::ifstream file(file_path);
            file >> json;
            file.close();
        }
        catch (const std::runtime_error& e)
        {
            LOG_ERROR("Error reading block file at " << file_path << '\n' << e.what());
            return;
        }

#if PROTOCOL_VERSION < 347 /* < 1.13 */

        if (!json.is_array())
        {
            LOG_ERROR("Error block file at " << file_path << " is not a json array as expected");
            return;
        }

        //Load all the blockstates from JSON file
        for (const auto& element : json.get_array())
        {
            const std::string& blockstate_name = element["name"].get_string();

            if (rendering.find(blockstate_name) == rendering.end() ||
                blockstate_properties.find(blockstate_name) == blockstate_properties.end() ||
                tint_types.find(blockstate_name) == tint_types.end())
            {
                LOG_ERROR("Error trying to get information for blockstate " << blockstate_name);
                continue;
            }

            BlockstateProperties& props = blockstate_properties[blockstate_name];
            props.id = -1;
            props.metadata = 0;
            props.variables = std::vector<std::string>();

            if (element.contains("id") && element["id"].is_number())
            {
                props.id = element["id"].get_number<int>();
            }

            const std::string& render = rendering[blockstate_name];

            if (render == "none")
            {
                props.fluid = false;
                props.tint_type = TintType::None;
                props.custom = false;
                props.path = "none";
                blockstates[props.id][0] = std::make_unique<Blockstate>(props);
            }
            else if (render == "block" || render == "fluid" || render == "other")
            {
                if (render == "fluid" && textures.find(blockstate_name) == textures.end())
                {
                    LOG_ERROR("Error, blockstate " << blockstate_name << " is a fluid, but it does not have a texture file specified in Blocks_info.json");
                }

                if (!element.contains("metadata"))
                {
                    LOG_ERROR("Error, no metadata found for block " << blockstate_name);
                }

                for (const auto& metadata_obj : element["metadata"].get_array())
                {
                    props.metadata = metadata_obj["value"].get_number<int>();
                    props.path = metadata_obj["blockstate"].get_string();
                    props.variables = std::vector<std::string>();
                    if (metadata_obj.contains("variables"))
                    {
                        for (const auto& s : metadata_obj["variables"].get_array())
                        {
                            props.variables.push_back(s.get_string());
                        }
                    }

                    props.tint_type = TintType::None;
                    if (tint_types.find(blockstate_name) != tint_types.end())
                    {
                        if (tint_types[blockstate_name].find(-1) != tint_types[blockstate_name].end())
                        {
                            props.tint_type = tint_types[blockstate_name][-1];
                        }
                        else if (tint_types[blockstate_name].find(props.metadata) != tint_types[blockstate_name].end())
                        {
                            props.tint_type = tint_types[blockstate_name][props.metadata];
                        }
                    }

                    auto check_it = blockstates.find(props.id);
                    if (check_it != blockstates.end())
                    {
                        if (render == "fluid")
                        {
                            props.fluid = true;
                            props.custom = false;
                            blockstates[props.id][props.metadata] = std::make_unique<Blockstate>(props, Model::GetModel(15 - props.metadata, textures[blockstate_name]));
                        }
                        else
                        {
                            props.fluid = false;
                            props.custom = render == "other";
                            blockstates[props.id][props.metadata] = std::make_unique<Blockstate>(props);
                        }
                    }
                    else
                    {
                        // We want to be sure that blockstates[id][0] exists    
                        if (render == "fluid")
                        {
                            props.fluid = true;
                            blockstates[props.id];
                            blockstates[props.id][0] = std::make_unique<Blockstate>(props, Model::GetModel(15 - props.metadata, textures[blockstate_name]));
                            blockstates[props.id][props.metadata] = std::make_unique<Blockstate>(props, Model::GetModel(15 - props.metadata, textures[blockstate_name]));
                        }
                        else
                        {
                            props.fluid = false;
                            props.custom = render == "other";
                            blockstates[props.id];
                            blockstates[props.id][0] = std::make_unique<Blockstate>(props);
                            blockstates[props.id][props.metadata] = std::make_unique<Blockstate>(props);
                        }
                    }
                }
            }
        }
#else
        if (!json.is_object())
        {
            LOG_ERROR("Error block file at " << file_path << " is not a json object as expected");
            return;
        }

        for (const auto& [blockstate_name, element]: json.get_object())
        {
            if (!element.contains("states") || !element["states"].is_array())
            {
                continue;
            }

            for (const auto& blockstate : element["states"].get_array())
            {
                if (rendering.find(blockstate_name) == rendering.end() ||
                    blockstate_properties.find(blockstate_name) == blockstate_properties.end() ||
                    tint_types.find(blockstate_name) == tint_types.end())
                {
                    LOG_ERROR("Error trying to get information for blockstate " << blockstate_name);
                    continue;
                }

                BlockstateProperties& props = blockstate_properties[blockstate_name];
                props.id = -1;
                props.variables = std::vector<std::string>();

                if (blockstate.contains("id") && blockstate["id"].is_number())
                {
                    props.id = blockstate["id"].get_number<int>();
                }
                else
                {
                    LOG_ERROR("Error trying to read the id of block " << blockstate_name);
                    continue;
                }

                const std::string& render = rendering[blockstate_name];

                // Read the properties (if any)
                int fluid_level = 0;
                if (blockstate.contains("properties") && blockstate["properties"].is_object())
                {
                    for (const auto& [key, val]: blockstate["properties"].get_object())
                    {
                        props.variables.push_back(key + "=" + val.get_string());
                        if (render == "fluid" && key == "level")
                        {
                            fluid_level = std::stoi(val.get_string());
                        }
                    }
                }

                if (render == "none")
                {
                    props.fluid = false;
                    props.tint_type = TintType::None;
                    props.custom = false;
                    props.path = "none";
                    blockstates[props.id] = std::make_unique<Blockstate>(props);
                }
                else if (render == "fluid")
                {
                    if (textures.find(blockstate_name) == textures.end())
                    {
                        LOG_ERROR("Error, blockstate " << blockstate_name << " is a fluid, but it does not have a texture file specified in Blocks_info.json");
                    }
                    else
                    {
                        props.fluid = true;
                        props.tint_type = tint_types[blockstate_name];
                        blockstates[props.id] = std::make_unique<Blockstate>(props, Model::GetModel(15 - fluid_level, textures[blockstate_name]));
                    }
                }
                else if (render == "block" || render == "other")
                {
                    props.fluid = false;
                    props.custom = render == "other";
                    props.tint_type = tint_types[blockstate_name];
                    props.path = blockstate_name.substr(10);
                    blockstates[props.id] = std::make_unique<Blockstate>(props);
                }
            }
        }
        FlattenBlocks();
#endif
    }

#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
    void AssetsManager::FlattenBlocks()
    {
        int max_id = -1;
        for (const auto& [id, block] : blockstates)
        {
            max_id = std::max(id, max_id);
        }
        if (max_id > std::numeric_limits<unsigned short>::max())
        {
            LOG_ERROR("Too many blockstates, compact chunk representation will be broken");
        }
        flattened_blockstates = std::vector<const Blockstate*>(max_id + 1, nullptr);
        flattened_blockstates_size = flattened_blockstates.size();
        for (const auto& [id, block] : blockstates)
        {
            if (id >= 0)
            {
                flattened_blockstates[id] = block.get();
            }
        }
    }
#endif

    void AssetsManager::LoadBiomesFile()
    {
        std::string file_path = ASSETS_PATH + std::string("/custom/Biomes.json");

        Json::Value json;
        try
        {
            std::ifstream file(file_path);
            file >> json;
            file.close();
        }
        catch (const std::runtime_error& e)
        {
            LOG_ERROR("Error reading biome file at " << file_path << '\n' << e.what());
            return;
        }

        if (!json.is_array())
        {
            LOG_ERROR("Error biome file at " << file_path << " is not a json object as expected");
            return;
        }

        //Load all the biomes from JSON file
        int max_biome_id = 0;
        for (const auto& element : json.get_array())
        {
            unsigned char id = 0;
            std::string name = "";
            float rainfall = 0.0f;
            float temperature = 0.0f;
            BiomeType biome_type = BiomeType::Classic;

            if (element.contains("id"))
            {
                id = element["id"].get_number<unsigned char>();
            }

            if (element.contains("name"))
            {
                name = element["name"].get_string();
            }

            if (element.contains("rainfall"))
            {
                rainfall = element["rainfall"].get_number<float>();
            }
            
            if (element.contains("temperature"))
            {
                temperature = element["temperature"].get_number<float>();
            }

            if (element.contains("biomeType"))
            {
                const std::string& string_biome_type = element["biomeType"].get_string();
                if (string_biome_type == "Swamp")
                {
                    biome_type = BiomeType::Swamp;
                }
                else if (string_biome_type == "Badlands")
                {
                    biome_type = BiomeType::Badlands;
                }
                else if (string_biome_type == "DarkForest")
                {
                    biome_type = BiomeType::DarkForest;
                }
#if PROTOCOL_VERSION >= 393 /* >= 1.13 */
                else if (string_biome_type == "WarmOcean")
                {
                    biome_type = BiomeType::WarmOcean;
                }
                else if (string_biome_type == "LukewarmOcean")
                {
                    biome_type = BiomeType::LukewarmOcean;
                }
                else if (string_biome_type == "ColdOcean")
                {
                    biome_type = BiomeType::ColdOcean;
                }
                else if (string_biome_type == "FrozenOcean")
                {
                    biome_type = BiomeType::FrozenOcean;
                }
#endif
            }

            biomes[id] = std::make_unique<Biome>(name, temperature, rainfall, biome_type);
        }
    }

    void AssetsManager::LoadItemsFile()
    {
        std::string file_path = ASSETS_PATH + std::string("/custom/Items.json");

        Json::Value json;
        try
        {
            std::ifstream file(file_path);
            file >> json;
            file.close();
        }
        catch (const std::runtime_error& e)
        {
            LOG_ERROR("Error reading item file at " << file_path << '\n' << e.what());
            return;
        }

        // Add a default item
        ItemProperties props{
#if PROTOCOL_VERSION < 347 /* < 1.13 */
                {-1, 0}, //id
#else
                -1, //id
#endif
                "default", //name
                64, //stack_size
        };
#if PROTOCOL_VERSION < 347 /* < 1.13 */
        items[{-1, 0}] = std::make_unique<Item>(props);
#else
        items[-1] = std::make_unique<Item>(props);
#endif

        //Load all the items from JSON file
        for (const auto& [key, properties]:  json.get_object())
        {
            // Read name
            props.name = key;

            if (!properties.contains("id") || !properties["id"].is_number())
            {
                continue;
            }
#if PROTOCOL_VERSION < 347 /* < 1.13 */
            props.id.first = properties["id"].get_number<int>();
#else
            props.id = properties["id"].get_number<int>();
#endif

            if (properties.contains("stack_size") && properties["stack_size"].is_number())
            {
                props.stack_size = properties["stack_size"].get_number<unsigned char>();
            }
            // Default value
            else
            {
                props.stack_size = 64;
            }

#if PROTOCOL_VERSION < 347 /* < 1.13 */
            if (!properties.contains("damage_id") || !properties["damage_id"].is_number())
            {
                continue;
            }
            props.id.second = properties["damage_id"].get_number<unsigned char>();
#endif
            items[props.id] = std::make_unique<Item>(props);
        }
    }

#if USE_GUI
    void AssetsManager::LoadTextures()
    {
        std::set<std::string> unique_names;

        for (auto it = blockstates.begin(); it != blockstates.end(); ++it)
        {
#if PROTOCOL_VERSION < 347 /* < 1.13 */
            for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            {
                for (int n = 0; n < it2->second->GetNumModels(); ++n)
                {
                    const auto& faces = it2->second->GetModel(n).GetFaces();

                    for (int i = 0; i < faces.size(); ++i)
                    {
                        for (int s = 0; s < faces[i].texture_names.size(); ++s)
                        {
                            unique_names.insert(faces[i].texture_names[s]);
                        }
                    }
                }
            }
#else
            for (int n = 0; n < it->second->GetNumModels(); ++n)
            {
                const auto& faces = it->second->GetModel(n).GetFaces();

                for (int i = 0; i < faces.size(); ++i)
                {
                    for (int s = 0; s < faces[i].texture_names.size(); ++s)
                    {
                        unique_names.insert(faces[i].texture_names[s]);
                    }
                }
            }
#endif
        }

        std::vector<std::pair<std::string, std::string> > paths;
        paths.reserve(unique_names.size());
        for (auto it = unique_names.begin(); it != unique_names.end(); ++it)
        {
            if ((*it).empty())
            {
                continue;
            }
            paths.push_back({ (ASSETS_PATH + std::string("/minecraft/textures/") + *it + ".png") , *it });
        }

        atlas->LoadData(paths);
    }
#endif

    void AssetsManager::ClearCaches()
    {
        Blockstate::ClearCache();
        Model::ClearCache();
    }

#if USE_GUI
    void AssetsManager::UpdateModelsWithAtlasData()
    {
        Blockstate::UpdateModelsWithAtlasData(atlas.get());
    }
#endif

} //Botcraft
