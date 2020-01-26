#include <fstream>
#include <sstream>

#include "botcraft/Game/AssetsManager.hpp"
#include "botcraft/Game/World/Block.hpp"
#include "botcraft/Game/World/Biome.hpp"

#include <picojson/picojson.h>

#include "botcraft/Version.hpp"

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
    }

#if PROTOCOL_VERSION < 347
    const std::map<int, std::map<unsigned char, std::shared_ptr<Blockstate> > >& AssetsManager::Blockstates() const
#else
    const std::map<int, std::shared_ptr<Blockstate> >& AssetsManager::Blockstates() const
#endif
    {
        return blockstates;
    }

#if PROTOCOL_VERSION < 358
    const std::map<unsigned char, std::shared_ptr<Biome> >& AssetsManager::Biomes() const
#else
    const std::map<int, std::shared_ptr<Biome> >& AssetsManager::Biomes() const
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

#ifdef USE_GUI
    const std::vector<std::pair<std::string, std::string> > AssetsManager::GetTexturesPathsNames() const
    {
        std::set<std::string> unique_names;

        for (auto it = blockstates.begin(); it != blockstates.end(); ++it)
        {
#if PROTOCOL_VERSION < 347
            for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            {
                for (int n = 0; n < it2->second->GetNumModels(); ++n)
                {
                    const auto &faces = it2->second->GetModel(n).GetFaces();

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
                const auto &faces = it->second->GetModel(n).GetFaces();

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

        std::vector<std::pair<std::string, std::string> > output;
        output.reserve(unique_names.size());
        for (auto it = unique_names.begin(); it != unique_names.end(); ++it)
        {
            if ((*it).empty())
            {
                continue;
            }
            output.push_back({ (ASSETS_PATH + std::string("/minecraft/textures/") + *it + ".png") , *it});
        }

        return output;
    }
#endif

    void AssetsManager::LoadBlocksFile()
    {
        std::stringstream ss;
        std::ifstream file;

        std::map<std::string, bool> solidity;
        std::map<std::string, bool> transparency;
        std::map<std::string, float> hardness;
        std::map<std::string, std::string> textures;
        std::map<std::string, std::string> rendering;
#if PROTOCOL_VERSION < 347
        std::map<std::string, std::map<int, TintType> > tint_types;
#else
        std::map<std::string, TintType> tint_types;
#endif
        const std::string info_file_path = ASSETS_PATH + std::string("/custom/Blocks_info.json");

        file.open(info_file_path);
        if (!file.is_open())
        {
            std::cerr << "Error reading info block file at " << info_file_path << std::endl;
            return;
        }

        ss << file.rdbuf();
        file.close();

        picojson::value json;
        ss >> json;
        std::string err = picojson::get_last_error();

        if (!err.empty())
        {
            std::cerr << "Error parsing info block file at " << info_file_path << "\n";
            std::cerr << err << std::endl;
            return;
        }

        if (!json.is<picojson::array>())
        {
            std::cerr << "Error parsing info block file at " << info_file_path << std::endl;
            return;
        }


        //Load all the info
        const picojson::value::array &blockstates_info = json.get<picojson::array>();

        for (int i = 0; i < blockstates_info.size(); ++i)
        {
            std::string name = "";
            const picojson::value &info = blockstates_info[i];

            if (!info.is<picojson::object>())
            {
                std::cerr << "Error with the " << i << "th element of blockstates info" << std::endl;
                continue;
            }

            if (!info.contains("name") || !info.get("name").is<std::string>())
            {
                std::cerr << "Error with the name of the " << i << "th element of blockstates info" << std::endl;
                continue;
            }
            else
            {
                name = info.get("name").get<std::string>();
            }

            if (!info.contains("transparent") || !info.get("transparent").is<bool>())
            {
                transparency[name] = false;
            }
            else
            {
                transparency[name] = info.get("transparent").get<bool>();
            }

            if (!info.contains("solid") || !info.get("solid").is<bool>())
            {
                solidity[name] = false;
            }
            else
            {
                solidity[name] = info.get("solid").get<bool>();
            }

            if (!info.contains("hardness") || !info.get("hardness").is<double>())
            {
                hardness[name] = -2.0f;
            }
            else
            {
                hardness[name] = info.get("hardness").get<double>();
            }

            if (!info.contains("render") || !info.get("render").is<std::string>())
            {
                rendering[name] = "block";
            }
            else
            {
                rendering[name] = info.get("render").get<std::string>();
            }

            // Get texture info (used for fluids)
            if (info.contains("texture") && info.get("texture").is<std::string>())
            {
                textures[name] = info.get("texture").get<std::string>();
            }

            // Get the tint type info (for grass/leaves/water ...)
            if (info.contains("tintType") && info.get("tintType").is<std::string>())
            {
                std::string tint_type_string;
                TintType tint_type = TintType::None;
                tint_type_string = info.get("tintType").get<std::string>();
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
                tint_types[name] = std::map<int, TintType>({ { -1, tint_type } });
#else
                tint_types[name] = tint_type;
#endif
            }
#if PROTOCOL_VERSION < 347
            // Before the flattening, we could have different tints for different metadata
            else if (info.contains("tintTypes") && info.get("tintType").is<picojson::object>())
            {
                tint_types[name] = std::map<int, TintType>({});
                const picojson::object& tints = info.get("tintType").get<picojson::object>();
                for (auto it = tints.begin(); it != tints.end(); ++it)
                {
                    TintType tint_type = TintType::None;
                    std::string tint_type_string = it->second.get<std::string>();
                    
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

                    tint_types[name][std::stoi(it->first)] = tint_type;
                }
            }
#endif
            else
            {
#if PROTOCOL_VERSION < 347
                tint_types[name] = std::map<int, TintType>({ { -1, TintType::None } });
#else
                tint_types[name] = TintType::None;
#endif
            }
        }

        // Add a default block
#if PROTOCOL_VERSION < 347
        blockstates[-1] = std::map<unsigned char, std::shared_ptr<Blockstate> >({ { 0, std::shared_ptr<Blockstate>(new Blockstate(-1, 0, false, true, false, -2.0f, TintType::None, "default", "")) } });
#else
        blockstates[-1] = std::shared_ptr<Blockstate>(new Blockstate(-1, false, true, false, -2.0f, TintType::None, "default", ""));
#endif

        const std::string file_path = ASSETS_PATH + std::string("/custom/Blocks.json");

        file.open(file_path);
        if (!file.is_open())
        {
            std::cerr << "Error reading block file at " << file_path << std::endl;
            return;
        }

        ss << file.rdbuf();
        file.close();

        ss >> json;

        if (!err.empty())
        {
            std::cerr << "Error parsing block file at " << file_path << "\n";
            std::cerr << err << std::endl;
            return;
        }
#if PROTOCOL_VERSION < 347

        if (!json.is<picojson::array>())
        {
            std::cerr << "Error parsing block file at " << file_path << std::endl;
            return;
        }

        //Load all the blockstates from JSON file
        const picojson::value::array &json_blockstates = json.get<picojson::array>();

        for (int i = 0; i < json_blockstates.size(); ++i)
        {
            int id = -1;
            std::string blockstate_display_name = "";
            std::string blockstate_name = "";

            const picojson::object element = json_blockstates[i].get<picojson::object>();

            auto it = element.find("id");
            if (it != element.end())
            {
                id = (int)it->second.get<double>();
            }

            it = element.find("display_name");
            if (it != element.end())
            {
                blockstate_display_name = it->second.get<std::string>();
            }

            it = element.find("name");
            if (it != element.end())
            {
                blockstate_name = it->second.get<std::string>();
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
                blockstates[id][0] = std::shared_ptr<Blockstate>(new Blockstate(id, 0, true, false, false, -2.0f, TintType::None, blockstate_name, "none"));
            }
            else if (render == "block" || render == "fluid" || render == "other")
            {
                if(render == "fluid" && textures.find(blockstate_name) == textures.end())
                {
                    std::cerr << "Error, blockstate " << blockstate_name << " is a fluid, but it does not have a texture file specified in Blocks_info.json" << std::endl;
                }
                it = element.find("metadata");
                if (it != element.end())
                {
                    const picojson::array metadatas = it->second.get<picojson::array>();
                    for (int j = 0; j < metadatas.size(); ++j)
                    {
                        unsigned char metadata;
                        std::vector<std::string> variables;
                        std::string blockstate;

                        const picojson::object current = metadatas[j].get<picojson::object>();
                        auto it2 = current.find("value");
                        metadata = (unsigned char)it2->second.get<double>();

                        it2 = current.find("variables");
                        if (it2 != current.end())
                        {
                            for (int k = 0; k < it2->second.get<picojson::array>().size(); ++k)
                            {
                                variables.push_back(it2->second.get<picojson::array>()[k].get<std::string>());
                            }
                        }

                        it2 = current.find("blockstate");
                        blockstate = it2->second.get<std::string>();
                        
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
                                blockstates[id][metadata] = std::shared_ptr<Blockstate>(new Blockstate(id, metadata, transparency[blockstate_name], solidity[blockstate_name], false, hardness[blockstate_name], tint_type, blockstate_name, blockstate, variables));
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
                                std::shared_ptr<Blockstate> b = std::shared_ptr<Blockstate>(new Blockstate(id, metadata, transparency[blockstate_name], solidity[blockstate_name], false, hardness[blockstate_name], tint_type, blockstate_name, blockstate, variables));
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
                        blockstates[id][0] = std::shared_ptr<Blockstate>(new Blockstate(id, 0, false, true, false, -2.0f, TintType::None, "", ""));
                    }
                }
            }
        }
#else

        if (!json.is<picojson::object>())
        {
            std::cerr << "Error parsing block file at " << file_path << std::endl;
            return;
        }

        //Load all the blockstates from JSON file
        const picojson::value::object& obj = json.get<picojson::object>();

        for (picojson::value::object::const_iterator blockstates_it = obj.begin(); blockstates_it != obj.end(); ++blockstates_it)
        {
            int id = -1;
            std::string blockstate_name = blockstates_it->first;

            const picojson::object element = blockstates_it->second.get<picojson::object>();

            auto it = element.find("states");

            if (it == element.end() || !it->second.is<picojson::array>())
            {
                continue;
            }

            const picojson::value::array &json_blockstates = it->second.get<picojson::array>();

            for (int i = 0; i < json_blockstates.size(); ++i)
            {
                int id = -1;
                std::vector<std::string> variables;

                if (json_blockstates[i].contains("id") && json_blockstates[i].get("id").is<double>())
                {
                    id = json_blockstates[i].get("id").get<double>();
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
                if (json_blockstates[i].contains("properties") && json_blockstates[i].get("properties").is<picojson::object>())
                {
                    const picojson::object &properties = json_blockstates[i].get("properties").get<picojson::object>();

                    for (auto it2 = properties.begin(); it2 != properties.end(); ++it2)
                    {
                        variables.push_back(it2->first + "=" + it2->second.get<std::string>());
                        if (render == "fluid" && it2->first == "level")
                        {
                            fluid_level = std::stoi(it2->second.get<std::string>());
                        }
                    }
                }

                if (render == "none")
                {
                    blockstates[id] = std::shared_ptr<Blockstate>(new Blockstate(id, true, false, false, -2, TintType::None, blockstate_name, "none"));
                }
                else if (render == "block" || render == "fluid" || render == "other")
                {
                    if (render == "fluid" && textures.find(blockstate_name) == textures.end())
                    {
                        std::cerr << "Error, blockstate " << blockstate_name << " is a fluid, but it does not have a texture file specified in Blocks_info.json" << std::endl;
                    }

                    if (render == "fluid")
                    {
                        blockstates[id] = std::shared_ptr<Blockstate>(new Blockstate(id, transparency[blockstate_name], solidity[blockstate_name], true, hardness[blockstate_name], tint_types[blockstate_name], blockstate_name, Model::GetModel(15 - fluid_level, textures[blockstate_name])));
                    }
                    else
                    {
                        // Remove the minecraft: prefix to get the blockstate name
                        std::string blockstate = blockstate_name.substr(10);
                        blockstates[id] = std::shared_ptr<Blockstate>(new Blockstate(id, transparency[blockstate_name], solidity[blockstate_name], false, hardness[blockstate_name], tint_types[blockstate_name], blockstate_name, blockstate, variables));
                    }
                }
            }
        }
#endif
    }

    void AssetsManager::LoadBiomesFile()
    {
        std::string file_path = ASSETS_PATH + std::string("/custom/Biomes.json");

        std::stringstream ss;
        std::ifstream file;

        file.open(file_path);
        if (!file.is_open())
        {
            std::cerr << "Error reading biome file at " << file_path << std::endl;
            return;
        }

        ss << file.rdbuf();
        file.close();

        picojson::value json;
        ss >> json;
        std::string err = picojson::get_last_error();

        if (!err.empty())
        {
            std::cerr << "Error parsing biome file at " << file_path << "\n";
            std::cerr << err << std::endl;
            return;
        }

        if (!json.is<picojson::array>())
        {
            std::cerr << "Error parsing biome file at " << file_path << std::endl;
            return;
        }

        //Load all the biomes from JSON file
        const picojson::value::array &all_biomes = json.get<picojson::array>();

        for (int i = 0; i < all_biomes.size(); ++i)
        {
            unsigned char id = 0;
            std::string name = "";
            float rainfall = 0.0f;
            float temperature = 0.0f;
            BiomeType biome_type = BiomeType::Classic;

            const picojson::object element = all_biomes[i].get<picojson::object>();

            auto it = element.find("id");
            if (it != element.end())
            {
                id = (int)it->second.get<double>();
            }

            it = element.find("name");
            if (it != element.end())
            {
                name = it->second.get<std::string>();
            }

            it = element.find("rainfall");
            if (it != element.end())
            {
                rainfall = it->second.get<double>();
            }
            
            it = element.find("temperature");
            if (it != element.end())
            {
                temperature = it->second.get<double>();
            }

            it = element.find("biomeType");
            if (it != element.end())
            {
                std::string string_biome_type = it->second.get<std::string>();
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
} //Botcraft