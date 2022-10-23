#include <fstream>
#include <sstream>
#include <filesystem>

#include "botcraft/Game/AssetsManager.hpp"
#include "botcraft/Game/World/Block.hpp"
#include "botcraft/Game/World/Biome.hpp"
#include "botcraft/Utilities/Logger.hpp"

#if USE_GUI
#include "botcraft/Renderer/Atlas.hpp"
#endif

#include <nlohmann/json.hpp>

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

#if PROTOCOL_VERSION < 347
    const std::unordered_map<int, std::unordered_map<unsigned char, std::unique_ptr<Blockstate> > >& AssetsManager::Blockstates() const
#else
    const std::unordered_map<int, std::unique_ptr<Blockstate> >& AssetsManager::Blockstates() const
#endif
    {
        return blockstates;
    }

#if PROTOCOL_VERSION < 358
    const std::unordered_map<unsigned char, std::unique_ptr<Biome> >& AssetsManager::Biomes() const
#else
    const std::unordered_map<int, std::unique_ptr<Biome> >& AssetsManager::Biomes() const
#endif
    {
        return biomes;
    }

#if PROTOCOL_VERSION < 358
    const Biome* AssetsManager::GetBiome(const unsigned char id)
#else
    const Biome* AssetsManager::GetBiome(const int id)
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

#if PROTOCOL_VERSION < 347
    const std::unordered_map<int, std::unordered_map<unsigned char, std::unique_ptr<Item> > >& AssetsManager::Items() const
#else
    const std::unordered_map<int, std::unique_ptr<Item>>& AssetsManager::Items() const
#endif
    {
        return items;
    }

#if PROTOCOL_VERSION < 347
    const std::pair<int, unsigned char> AssetsManager::GetItemID(const std::string& item_name) const
    {
        for (const auto& p : items)
        {
            for (const auto& p2 : p.second)
            {
                if (p2.second->GetName() == item_name)
                {
                    return { p.first, p2.first };
                }
            }
        }
        return { -1, 0 };
    }
#else
    const int AssetsManager::GetItemID(const std::string& item_name) const
    {
        for (const auto& p : items)
        {
            if (p.second->GetName() == item_name)
            {
                return p.first;
            }
        }
        return -1;
    }
#endif

#if USE_GUI
    const Renderer::Atlas* AssetsManager::GetAtlas() const
    {
        return atlas.get();
    }
#endif

    void AssetsManager::LoadBlocksFile()
    {
        std::unordered_map<std::string, BlockstateProperties> blockstate_properties;
        std::unordered_map<std::string, std::string> textures;
        std::unordered_map<std::string, std::string> rendering;
#if PROTOCOL_VERSION < 347
        std::unordered_map<std::string, std::unordered_map<int, TintType> > tint_types;
#else
        std::unordered_map<std::string, TintType> tint_types;
#endif
        const std::string info_file_path = ASSETS_PATH + std::string("/custom/Blocks_info.json");

        nlohmann::json json;
        try
        {
            std::ifstream file(info_file_path);
            file >> json;
            file.close();
        }
        catch (const nlohmann::json::exception& e)
        {
            LOG_ERROR("Error reading info block file at " << info_file_path << '\n' << e.what());
            return;
        }

        //Load all the info
        for (auto& info : json)
        {
            std::string name = "";

            if (!info.contains("name") || !info["name"].is_string())
            {
                LOG_ERROR("Error with an element of blockstates info: \n" << info);
                continue;
            }
            else
            {
                name = info["name"];
                blockstate_properties[name].name = name;
            }

            if (info.contains("transparent") && info["transparent"].is_boolean())
            {
                blockstate_properties[name].transparent = info["transparent"];
            }

            if (info.contains("solid") && info["solid"].is_boolean())
            {
                blockstate_properties[name].solid = info["solid"];
            }

            if (info.contains("hardness") && info["hardness"].is_number())
            {
                blockstate_properties[name].hardness = info["hardness"];
            }

            if (!info.contains("render") || !info["render"].is_string())
            {
                rendering[name] = "block";
            }
            else
            {
                rendering[name] = info["render"];
            }

            if (info.contains("climbable") && info["climbable"].is_boolean())
            {
                blockstate_properties[name].climbable = info["climbable"];
            }

            // Get texture info (used for fluids)
            if (info.contains("texture") && info["texture"].is_string())
            {
                textures[name] = info["texture"];
            }

            // Get the tint type info (for grass/leaves/water ...)
            if (info.contains("tintType") && info["tintType"].is_string())
            {
                std::string tint_type_string;
                TintType tint_type = TintType::None;
                tint_type_string = info["tintType"];
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

#if PROTOCOL_VERSION < 347
                tint_types[name] = std::unordered_map<int, TintType>({ { -1, tint_type } });
#else
                tint_types[name] = tint_type;
#endif
            }
#if PROTOCOL_VERSION < 347
            // Before the flattening, we could have different tints for different metadata
            else if (info.contains("tintTypes") && info["tintType"].is_object())
            {
                tint_types[name] = std::unordered_map<int, TintType>({});
                for (auto it = info["tintType"].begin(); it != info["tintType"].end(); ++it)
                {
                    TintType tint_type = TintType::None;
                    std::string tint_type_string = it.value().get<std::string>();
                    
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

                    tint_types[name][std::stoi(it.key())] = tint_type;
                }
            }
#endif
            else
            {
#if PROTOCOL_VERSION < 347
                tint_types[name] = std::unordered_map<int, TintType>({ { -1, TintType::None } });
#else
                tint_types[name] = TintType::None;
#endif
            }
        }

        // Add a default block
#if PROTOCOL_VERSION < 347
        blockstates[-1];
        blockstates[-1][0] = std::make_unique<Blockstate>(
            BlockstateProperties{
                -1, //id
                0, //metadata
                false, //transparent
                true, //solid
                false, //fluid
                false, //climbable
                false, //custom
                -2.0f, //hardness
                TintType::None, //tint_type
                "default", //name
            }
        );
#else
        blockstates[-1] = std::make_unique<Blockstate>(
            BlockstateProperties{
                -1, //id
                false, //transparent
                true, //solid
                false, //fluid
                false, //climbable
                false, //custom
                -2.0f, //hardness
                TintType::None, //tint_type
                "default", //name
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
        catch (const nlohmann::json::exception& e)
        {
            LOG_ERROR("Error reading block file at " << file_path << '\n' << e.what());
            return;
        }

#if PROTOCOL_VERSION < 347

        if (!json.is_array())
        {
            LOG_ERROR("Error block file at " << file_path << " is not a json array as expected");
            return;
        }

        //Load all the blockstates from JSON file
        for (auto& element : json)
        {
            const std::string& blockstate_name = element["name"].get<std::string>();

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
                props.id = element["id"];
            }

            const std::string render = rendering[blockstate_name];

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

                for (auto& metadata_obj : element["metadata"])
                {
                    props.metadata = metadata_obj["value"];
                    props.path = metadata_obj["blockstate"];
                    props.variables = std::vector<std::string>();
                    if (metadata_obj.contains("variables"))
                    {
                        for (auto& s : metadata_obj["variables"])
                        {
                            props.variables.push_back(s);
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

        for (nlohmann::json::const_iterator blockstates_it = json.begin(); blockstates_it != json.end(); ++blockstates_it)
        {
            std::string blockstate_name = blockstates_it.key();

            const nlohmann::json& element = blockstates_it.value();

            if (!element.contains("states") || !element["states"].is_array())
            {
                continue;
            }

            for (auto& blockstate : element["states"])
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
                    props.id = blockstate["id"];
                }
                else
                {
                    LOG_ERROR("Error trying to read the id of block " << blockstate_name);
                    continue;
                }

                const std::string render = rendering[blockstate_name];

                // Read the properties (if any)
                int fluid_level = 0;
                if (blockstate.contains("properties") && blockstate["properties"].is_object())
                {
                    for (nlohmann::json::const_iterator prop = blockstate["properties"].begin(); prop != blockstate["properties"].end(); ++prop)
                    {
                        props.variables.push_back(prop.key() + "=" + prop.value().get<std::string>());
                        if (render == "fluid" && prop.key() == "level")
                        {
                            fluid_level = std::stoi(prop.value().get<std::string>());
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
#endif
    }

    void AssetsManager::LoadBiomesFile()
    {
        std::string file_path = ASSETS_PATH + std::string("/custom/Biomes.json");

        nlohmann::json json;
        try
        {
            std::ifstream file(file_path);
            file >> json;
            file.close();
        }
        catch (const nlohmann::json::exception& e)
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
        for (auto& element : json)
        {
            unsigned char id = 0;
            std::string name = "";
            float rainfall = 0.0f;
            float temperature = 0.0f;
            BiomeType biome_type = BiomeType::Classic;

            if (element.contains("id"))
            {
                id = element["id"];
            }

            if (element.contains("name"))
            {
                name = element["name"];
            }

            if (element.contains("rainfall"))
            {
                rainfall = element["rainfall"];
            }
            
            if (element.contains("temperature"))
            {
                temperature = element["temperature"];
            }

            if (element.contains("biomeType"))
            {
                std::string string_biome_type = element["biomeType"];
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
#if PROTOCOL_VERSION >= 393
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

        nlohmann::json json;
        try
        {
            std::ifstream file(file_path);
            file >> json;
            file.close();
        }
        catch (const nlohmann::json::exception& e)
        {
            LOG_ERROR("Error reading item file at " << file_path << '\n' << e.what());
            return;
        }

        // Add a default item
#if PROTOCOL_VERSION < 347
        items[-1];
        items[-1][0] = std::make_unique<Item>(-1, 0, "default", 64);
#else
        items[-1] = std::make_unique<Item>(-1, "default", 64);
#endif

        //Load all the items from JSON file
        for (nlohmann::json::const_iterator items_it = json.begin(); items_it != json.end(); ++items_it)
        {
            int id = -1;
            unsigned char stack_size = 64;
            std::string item_name = items_it.key();

            const nlohmann::json& properties = items_it.value();

            if (!properties.contains("id") || !properties["id"].is_number())
            {
                continue;
            }
            id = properties["id"];
            if (properties.contains("stack_size"))
            {
                stack_size = properties["stack_size"];
            }
#if PROTOCOL_VERSION < 347
            if (!properties.contains("damage_id") || !properties["damage_id"].is_number())
            {
                continue;
            }
            unsigned char damage_id = properties["damage_id"];
            if (items.find(id) == items.end())
            {
                items[id] = std::unordered_map<unsigned char, std::unique_ptr<Item> >();
            }
            items[id][damage_id] = std::make_unique<Item>(id, damage_id, item_name, stack_size);
#else
            items[id] = std::make_unique<Item>(id, item_name, stack_size);
#endif
        }
    }

#if USE_GUI
    void AssetsManager::LoadTextures()
    {
        std::set<std::string> unique_names;

        for (auto it = blockstates.begin(); it != blockstates.end(); ++it)
        {
#if PROTOCOL_VERSION < 347
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
        for (auto it = blockstates.begin(); it != blockstates.end(); ++it)
        {
#if PROTOCOL_VERSION < 347
            for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            {
                it2->second->UpdateModelsWithAtlasData(atlas.get());
            }
#else
            it->second->UpdateModelsWithAtlasData(atlas.get());
#endif
        }
    }
#endif

} //Botcraft
