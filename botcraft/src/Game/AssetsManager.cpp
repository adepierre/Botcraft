#include <fstream>
#include <sstream>
#include <iostream>

#include "botcraft/Game/AssetsManager.hpp"
#include "botcraft/Game/World/Block.hpp"
#include "botcraft/Game/World/Biome.hpp"

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
        std::cout << "Loading blocks from file..." << std::endl;
        LoadBlocksFile();
        std::cout << "Done!" << std::endl;
        std::cout << "Loading biomes from file..." << std::endl;
        LoadBiomesFile();
        std::cout << "Done!" << std::endl;
        std::cout << "Loading items from file..." << std::endl;
        LoadItemsFile();
        std::cout << "Done!" << std::endl;
#if USE_GUI
        std::cout << "Loading textures..." << std::endl;
        atlas = std::make_unique<Renderer::Atlas>();
        LoadTextures();
        std::cout << "Done!" << std::endl;
        std::cout << "Updating models with Atlas data..." << std::endl;
        UpdateModelsWithAtlasData();
        std::cout << "Done!" << std::endl;
#endif
        std::cout << "Clearing cache from memory..." << std::endl;
        ClearCaches();
        std::cout << "Done!" << std::endl;
    }

#if PROTOCOL_VERSION < 347
    const std::unordered_map<int, std::unordered_map<unsigned char, std::shared_ptr<Blockstate> > >& AssetsManager::Blockstates() const
#else
    const std::unordered_map<int, std::shared_ptr<Blockstate> >& AssetsManager::Blockstates() const
#endif
    {
        return blockstates;
    }

#if PROTOCOL_VERSION < 358
    const std::unordered_map<unsigned char, std::shared_ptr<Biome> >& AssetsManager::Biomes() const
#else
    const std::unordered_map<int, std::shared_ptr<Biome> >& AssetsManager::Biomes() const
#endif
    {
        return biomes;
    }

#if PROTOCOL_VERSION < 358
    const std::shared_ptr<Biome> AssetsManager::GetBiome(const unsigned char id)
#else
    const std::shared_ptr<Biome> AssetsManager::GetBiome(const int id)
#endif
    {
        auto it = biomes.find(id);
        if (it != biomes.end())
        {
            return biomes[id];
        }
        else
        {
            return nullptr;
        }
    }

#if PROTOCOL_VERSION < 347
    const std::unordered_map<int, std::unordered_map<unsigned char, std::shared_ptr<Item> > >& AssetsManager::Items() const
#else
    const std::unordered_map<int, std::shared_ptr<Item>>& AssetsManager::Items() const
#endif
    {
        return items;
    }

#if USE_GUI
    const Renderer::Atlas* AssetsManager::GetAtlas() const
    {
        return atlas.get();
    }
#endif

    void AssetsManager::LoadBlocksFile()
    {
        std::unordered_map<std::string, bool> solidity;
        std::unordered_map<std::string, bool> transparency;
        std::unordered_map<std::string, float> hardness;
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
            std::cerr << "Error reading info block file at " << info_file_path << std::endl;
            std::cerr << e.what() << std::endl;
            return;
        }

        //Load all the info
        for (auto& info : json)
        {
            std::string name = "";

            if (!info.contains("name") || !info["name"].is_string())
            {
                std::cerr << "Error with an element of blockstates info: " << std::endl;
                std::cerr << info << std::endl;
                continue;
            }
            else
            {
                name = info["name"];
            }

            if (!info.contains("transparent") || !info["transparent"].is_boolean())
            {
                transparency[name] = false;
            }
            else
            {
                transparency[name] = info["transparent"];
            }

            if (!info.contains("solid") || !info["solid"].is_boolean())
            {
                solidity[name] = false;
            }
            else
            {
                solidity[name] = info["solid"];
            }

            if (!info.contains("hardness") || !info["hardness"].is_number())
            {
                hardness[name] = -2.0f;
            }
            else
            {
                hardness[name] = info["hardness"];
            }

            if (!info.contains("render") || !info["render"].is_string())
            {
                rendering[name] = "block";
            }
            else
            {
                rendering[name] = info["render"];
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
        blockstates[-1] = std::unordered_map<unsigned char, std::shared_ptr<Blockstate> >({ { 0, std::shared_ptr<Blockstate>(new Blockstate(-1, 0, false, true, false, false, -2.0f, TintType::None, "default", "")) } });
#else
        blockstates[-1] = std::shared_ptr<Blockstate>(new Blockstate(-1, false, true, false, false, -2.0f, TintType::None, "default", ""));
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
            std::cerr << "Error reading block file at " << file_path << std::endl;
            std::cerr << e.what() << std::endl;
            return;
        }

#if PROTOCOL_VERSION < 347

        if (!json.is_array())
        {
            std::cerr << "Error block file at " << file_path << " is not a json array as expected" << std::endl;
            return;
        }

        //Load all the blockstates from JSON file
        for (auto& element : json)
        {
            int id = -1;
            std::string blockstate_display_name = "";
            std::string blockstate_name = "";

            if (element.contains("id"))
            {
                id = element["id"];
            }

            if (element.contains("display_name"))
            {
                blockstate_display_name = element["display_name"];
            }

            if (element.contains("name"))
            {
                blockstate_name = element["name"];
            }

            std::string render = "block";
            if (rendering.find(blockstate_name) == rendering.end())
            {
                std::cerr << "Error trying to get rendering information for blockstate " << blockstate_name << std::endl;
                continue;
            }
            else
            {
                render = rendering[blockstate_name];
            }

            if (render == "none")
            {
                blockstates[id][0] = std::shared_ptr<Blockstate>(new Blockstate(id, 0, true, false, false, false, -2.0f, TintType::None, blockstate_name, "none"));
            }
            else if (render == "block" || render == "fluid" || render == "other")
            {
                if(render == "fluid" && textures.find(blockstate_name) == textures.end())
                {
                    std::cerr << "Error, blockstate " << blockstate_name << " is a fluid, but it does not have a texture file specified in Blocks_info.json" << std::endl;
                }
                if (element.contains("metadata"))
                {
                    for (auto& metadata_obj : element["metadata"])
                    {
                        unsigned char metadata;
                        std::vector<std::string> variables;
                        std::string blockstate;

                        metadata = metadata_obj["value"];

                        if (metadata_obj.contains("variables"))
                        {
                            for (auto& s : metadata_obj["variables"])
                            {
                                variables.push_back(s);
                            }
                        }

                        blockstate = metadata_obj["blockstate"];
                        
                        TintType tint_type = TintType::None;

                        if (tint_types.find(blockstate_name) != tint_types.end())
                        {
                            if (tint_types[blockstate_name].find(-1) != tint_types[blockstate_name].end())
                            {
                                tint_type = tint_types[blockstate_name][-1];
                            }
                            else if (tint_types[blockstate_name].find(metadata) != tint_types[blockstate_name].end())
                            {
                                tint_type = tint_types[blockstate_name][metadata];
                            }
                        }

                        auto check_it = blockstates.find(id);
                        if (check_it != blockstates.end())
                        {
                            if (render == "fluid")
                            {
                                blockstates[id][metadata] = std::shared_ptr<Blockstate>(new Blockstate(id, metadata, transparency[blockstate_name], solidity[blockstate_name], true, hardness[blockstate_name], tint_type, blockstate_name, Model::GetModel(15 - metadata, textures[blockstate_name])));
                            }
                            else
                            {
                                blockstates[id][metadata] = std::shared_ptr<Blockstate>(new Blockstate(id, metadata, transparency[blockstate_name], solidity[blockstate_name], false, render == "other", hardness[blockstate_name], tint_type, blockstate_name, blockstate, variables));
                            }
                        }
                        else
                        {
                            // We want to be sure that blockstates[id][0] exists    
                            if (render == "fluid")
                            {
                                std::shared_ptr<Blockstate> b = std::shared_ptr<Blockstate>(new Blockstate(id, metadata, transparency[blockstate_name], solidity[blockstate_name], true, hardness[blockstate_name], tint_type, blockstate_name, Model::GetModel(15 - metadata, textures[blockstate_name])));
                                blockstates[id];
                                blockstates[id][0] = b;
                                blockstates[id][metadata] = b;
                            }
                            else
                            {
                                std::shared_ptr<Blockstate> b = std::shared_ptr<Blockstate>(new Blockstate(id, metadata, transparency[blockstate_name], solidity[blockstate_name], false, render == "other", hardness[blockstate_name], tint_type, blockstate_name, blockstate, variables));
                                blockstates[id];
                                blockstates[id][0] = b;
                                blockstates[id][metadata] = b;
                            }
                        }
                    }
                }
                else
                {
                    //If no metadata, set to default block
                    if (render == "fluid")
                    {
                        blockstates[id][0] = std::shared_ptr<Blockstate>(new Blockstate(id, 0, false, true, true, -2.0f, TintType::None, "", Model::GetModel(15, "")));
                    }
                    else
                    {
                        blockstates[id][0] = std::shared_ptr<Blockstate>(new Blockstate(id, 0, false, true, false, false, -2.0f, TintType::None, "", ""));
                    }
                }
            }
        }
#else
        if (!json.is_object())
        {
            std::cerr << "Error block file at " << file_path << " is not a json object as expected" << std::endl;
            return;
        }

        for (nlohmann::json::const_iterator blockstates_it = json.begin(); blockstates_it != json.end(); ++blockstates_it)
        {
            int id = -1;
            std::string blockstate_name = blockstates_it.key();

            const nlohmann::json& element = blockstates_it.value();

            if (!element.contains("states") || !element["states"].is_array())
            {
                continue;
            }

            for (auto& blockstate : element["states"])
            {
                int id = -1;
                std::vector<std::string> variables;

                if (blockstate.contains("id") && blockstate["id"].is_number())
                {
                    id = blockstate["id"];
                }
                else
                {
                    std::cerr << "Error trying to read the id of block " << blockstate_name << std::endl;
                    continue;
                }

                if (rendering.find(blockstate_name) == rendering.end() ||
                    solidity.find(blockstate_name) == solidity.end() ||
                    transparency.find(blockstate_name) == transparency.end() ||
                    tint_types.find(blockstate_name) == tint_types.end())
                {
                    std::cerr << "Error trying to get information for blockstate " << blockstate_name << std::endl;
                    continue;
                }

                const std::string render = rendering[blockstate_name];

                // Read the properties (if any)
                int fluid_level = 0;
                if (blockstate.contains("properties") && blockstate["properties"].is_object())
                {
                    for (nlohmann::json::const_iterator prop = blockstate["properties"].begin(); prop != blockstate["properties"].end(); ++prop)
                    {
                        variables.push_back(prop.key() + "=" + prop.value().get<std::string>());
                        if (render == "fluid" && prop.key() == "level")
                        {
                            fluid_level = std::stoi(prop.value().get<std::string>());
                        }
                    }
                }

                if (render == "none")
                {
                    blockstates[id] = std::shared_ptr<Blockstate>(new Blockstate(id, true, false, false, false, -2, TintType::None, blockstate_name, "none"));
                }
                else if (render == "fluid")
                {
                    if (textures.find(blockstate_name) == textures.end())
                    {
                        std::cerr << "Error, blockstate " << blockstate_name << " is a fluid, but it does not have a texture file specified in Blocks_info.json" << std::endl;
                    }
                    else
                    {
                        blockstates[id] = std::shared_ptr<Blockstate>(new Blockstate(id, transparency[blockstate_name], solidity[blockstate_name], true, hardness[blockstate_name], tint_types[blockstate_name], blockstate_name, Model::GetModel(15 - fluid_level, textures[blockstate_name])));
                    }
                }
                else if (render == "block")
                {
                    // Remove the minecraft: prefix to get the blockstate name
                    std::string blockstate = blockstate_name.substr(10);
                    blockstates[id] = std::make_shared<Blockstate>(id, transparency[blockstate_name], solidity[blockstate_name], false, false, hardness[blockstate_name], tint_types[blockstate_name], blockstate_name, blockstate, variables);
                }
                else if (render == "other")
                {
                    // Remove the minecraft: prefix to get the blockstate name
                    std::string blockstate = blockstate_name.substr(10);
                    blockstates[id] = std::make_shared<Blockstate>(id, transparency[blockstate_name], solidity[blockstate_name], false, true, hardness[blockstate_name], tint_types[blockstate_name], blockstate_name, blockstate, variables);
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
            std::cerr << "Error reading biome file at " << file_path << std::endl;
            std::cerr << e.what() << std::endl;
            return;
        }

        if (!json.is_array())
        {
            std::cerr << "Error biome file at " << file_path << " is not a json object as expected" << std::endl;
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

            biomes[id] = std::shared_ptr<Biome>(new Biome(name, temperature, rainfall, biome_type));
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
            std::cerr << "Error reading item file at " << file_path << std::endl;
            std::cerr << e.what() << std::endl;
            return;
        }

        // Add a default item
#if PROTOCOL_VERSION < 347
        items[-1] = { { 0, std::shared_ptr<Item>(new Item(-1, 0, "default")) } };
#else
        items[-1] = std::shared_ptr<Item>(new Item(-1, "default"));
#endif

        //Load all the items from JSON file
        for (nlohmann::json::const_iterator items_it = json.begin(); items_it != json.end(); ++items_it)
        {
            int id = -1;
            std::string item_name = items_it.key();

            const nlohmann::json& properties = items_it.value();

            if (!properties.contains("id") || !properties["id"].is_number())
            {
                continue;
            }
            id = properties["id"];
#if PROTOCOL_VERSION < 347
            if (!properties.contains("damage_id") || !properties["damage_id"].is_number())
            {
                continue;
            }
            unsigned char damage_id = properties["damage_id"];
            if (items.find(id) == items.end())
            {
                items[id] = std::unordered_map<unsigned char, std::shared_ptr<Item> >();
            }
            items[id][damage_id] = std::shared_ptr<Item>(new Item(id, damage_id, item_name));
#else
            items[id] = std::shared_ptr<Item>(new Item(id, item_name));
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