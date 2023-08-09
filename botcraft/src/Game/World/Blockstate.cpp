#include <sstream>
#include <fstream>
#include <random>
#include <chrono>
#include <deque>

#include "botcraft/Game/World/Blockstate.hpp"
#include "botcraft/Utilities/Logger.hpp"
#include "botcraft/Utilities/StringUtilities.hpp"

#if USE_GUI
#include "botcraft/Renderer/Atlas.hpp"
#endif

using namespace ProtocolCraft;

namespace Botcraft
{
    // Utilities functions

    Model ModelModificationFromJson(const Model &model, const Json::Value &json)
    {
        Model output = model;

        bool uv_lock = false;
        if (json.contains("uvlock"))
        {
            uv_lock = json["uvlock"].get<bool>();
        }

        int rotation_x = 0;
        if (json.contains("x"))
        {
            rotation_x = json["x"].get_number<int>();
        }

        int rotation_y = 0;
        if (json.contains("y"))
        {
            rotation_y = json["y"].get_number<int>();
        }

        //Rotate colliders

        if (rotation_x != 0)
        {
            std::vector<AABB> &colliders = output.GetColliders();

            for (int i = 0; i < colliders.size(); ++i)
            {
                Vector3<double> new_center;
                switch (rotation_x / 90)
                {
                case 0:
                    break;
                case 1:
                    new_center = colliders[i].GetCenter() - 0.5;
                    new_center = Vector3<double>(new_center.x, new_center.z, -new_center.y);
                    new_center = new_center + 0.5;
                    colliders[i] = AABB(new_center, Vector3<double>(colliders[i].GetHalfSize().x, colliders[i].GetHalfSize().z, colliders[i].GetHalfSize().y));
                    break;
                case 2:
                    new_center = colliders[i].GetCenter() - 0.5;
                    new_center = Vector3<double>(new_center.x, -new_center.y, -new_center.z);
                    new_center = new_center + 0.5;
                    colliders[i] = AABB(new_center, Vector3<double>(colliders[i].GetHalfSize().x, colliders[i].GetHalfSize().y, colliders[i].GetHalfSize().z));
                    break;
                case 3:
                    new_center = colliders[i].GetCenter() - 0.5;
                    new_center = Vector3<double>(new_center.x, -new_center.z, new_center.y);
                    new_center = new_center + 0.5;
                    colliders[i] = AABB(new_center, Vector3<double>(colliders[i].GetHalfSize().x, colliders[i].GetHalfSize().z, colliders[i].GetHalfSize().y));
                    break;
                default:
                    LOG_ERROR("Blockstate X rotation should be in 90 degrees steps");
                    break;
                }
            }
        }

        if (rotation_y != 0)
        {
            std::vector<AABB> &colliders = output.GetColliders();

            for (int i = 0; i < colliders.size(); ++i)
            {
                Vector3<double> new_center;
                switch (rotation_y / 90)
                {
                case 0:
                    break;
                case 1:
                    new_center = colliders[i].GetCenter() - 0.5;
                    new_center = Vector3<double>(-new_center.z, new_center.y, new_center.x);
                    new_center = new_center + 0.5;
                    colliders[i] = AABB(new_center, Vector3<double>(colliders[i].GetHalfSize().z, colliders[i].GetHalfSize().y, colliders[i].GetHalfSize().x));
                    break;
                case 2:
                    new_center = colliders[i].GetCenter() - 0.5;
                    new_center = Vector3<double>(-new_center.x, new_center.y, -new_center.z);
                    new_center = new_center + 0.5;
                    colliders[i] = AABB(new_center, Vector3<double>(colliders[i].GetHalfSize().x, colliders[i].GetHalfSize().y, colliders[i].GetHalfSize().z));
                    break;
                case 3:
                    new_center = colliders[i].GetCenter() - 0.5;
                    new_center = Vector3<double>(new_center.z, new_center.y, -new_center.x);
                    new_center = new_center + 0.5;
                    colliders[i] = AABB(new_center, Vector3<double>(colliders[i].GetHalfSize().z, colliders[i].GetHalfSize().y, colliders[i].GetHalfSize().x));
                    break;
                default:
                    LOG_ERROR("Blockstate Y rotation should be in 90 degrees steps");
                    break;
                }
            }
        }

#ifdef USE_GUI
        //Rotate faces

        if (rotation_x != 0)
        {
            std::vector<FaceDescriptor> &faces = output.GetFaces();

            std::vector<Orientation> rotated_orientations = { Orientation::Top, Orientation::North, Orientation::Bottom, Orientation::South };

            for (int f = 0; f < faces.size(); ++f)
            {
                //We want to add this transformation after the local translations,
                //Just before the global translation to final position
                faces[f].transformations.translations.insert(faces[f].transformations.translations.begin(), Renderer::TransformationPtr(new Renderer::Rotation(1.0f, 0.0f, 0.0f, -static_cast<float>(rotation_x))));

                const auto it_cullface = std::find(rotated_orientations.begin(), rotated_orientations.end(), faces[f].cullface_direction);

                if (it_cullface != rotated_orientations.end())
                {
                    faces[f].cullface_direction = rotated_orientations[((it_cullface - rotated_orientations.begin()) + rotation_x / 90) % rotated_orientations.size()];
                }

                if (uv_lock)
                {
                    const auto it_orientation = std::find(rotated_orientations.begin(), rotated_orientations.end(), faces[f].orientation);
                    if (it_orientation == rotated_orientations.end())
                    {
                        faces[f].transformations.rotation -= rotation_x / 90;
                    }
                }
                faces[f].face = Renderer::Face(faces[f].transformations, faces[f].orientation);
            }
        }

        if (rotation_y != 0)
        {
            std::vector<FaceDescriptor> &faces = output.GetFaces();

            std::vector<Orientation> rotated_orientations = { Orientation::South, Orientation::West, Orientation::North, Orientation::East };

            for (int f = 0; f < faces.size(); ++f)
            {
                //We want to add this transformation after the local translations,
                //Just before the global translation to final position
                faces[f].transformations.translations.insert(faces[f].transformations.translations.begin(), Renderer::TransformationPtr(new Renderer::Rotation(0.0f, 1.0f, 0.0f, -static_cast<float>(rotation_y))));

                const auto it_cullface = std::find(rotated_orientations.begin(), rotated_orientations.end(), faces[f].cullface_direction);

                if (it_cullface != rotated_orientations.end())
                {
                    faces[f].cullface_direction = rotated_orientations[((it_cullface - rotated_orientations.begin()) + rotation_y / 90) % rotated_orientations.size()];
                }

                if (uv_lock)
                {
                    const auto it_orientation = std::find(rotated_orientations.begin(), rotated_orientations.end(), faces[f].orientation);
                    if (it_orientation == rotated_orientations.end())
                    {
                        // Not sure why it's always 2 here...
                        faces[f].transformations.rotation += 2;
                    }
                }
                faces[f].face = Renderer::Face(faces[f].transformations, faces[f].orientation);
            }
        }
#endif

        return output;
    }

    std::string ModelNameFromJson(const Json::Value& json)
    {
        const std::string& model_path = json["model"].get_string();
#if PROTOCOL_VERSION < 347
        return "block/" + model_path;
#elif PROTOCOL_VERSION > 578 //> 1.15.2
        // Remove the minecraft: prefix from the model path
        return model_path.substr(10);
#else
        return model_path;
#endif
    }

    int WeightFromJson(const Json::Value& json)
    {
        int output = 1;

        if (json.contains("weight"))
        {
            output = json["weight"].get_number<int>();
        }

        return output;
    }

    const bool CheckCondition(const std::string &name, const std::string &value, const std::vector<std::string> &variables)
    {
        const std::vector<std::string> possible_values = Utilities::SplitString(value, '|');

        bool output = false;

        for (int i = 0; i < variables.size(); ++i)
        {
            if (Utilities::StartsWith(variables[i], name))
            {
                for (int j = 0; j < possible_values.size(); ++j)
                {
                    if (Utilities::EndsWith(variables[i], possible_values[j]))
                    {
                        output = true;
                        break;
                    }
                }
                if (output)
                {
                    break;
                }
            }
        }

        return output;
    }

    // Blockstate implementation starts here
    std::map<std::string, Json::Value> Blockstate::cached_jsons;

    Blockstate::Blockstate(const BlockstateProperties& properties)
    {
        id = properties.id;
#if PROTOCOL_VERSION < 347
        metadata = properties.metadata;
#endif
        air = properties.air;
        transparent = properties.transparent;
        solid = properties.solid;
        fluid = properties.fluid;
        climbable = properties.climbable;
        hazardous = properties.hazardous;
        hardness = properties.hardness;
        tint_type = properties.tint_type;
        m_name = properties.name;
        any_tool_harvest = properties.any_tool_harvest;
        best_tools = properties.best_tools;

        weights_sum = 0;
        random_generator = std::mt19937(static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()));

        if (properties.path == "none")
        {
            models.push_back(Model());
            models_weights.push_back(1);
            weights_sum += 1;
            return;
        }

        if (properties.path.empty())
        {
            models.push_back(Model::GetModel("", false));
            models_weights.push_back(1);
            weights_sum += 1;

            return;
        }

        std::string full_filepath;
        
        if (properties.custom)
        {
            full_filepath = ASSETS_PATH + std::string("/custom/blockstates/") + properties.path + ".json";
        }
        else
        {
            full_filepath = ASSETS_PATH + std::string("/minecraft/blockstates/") + properties.path + ".json";
        }

        try
        {
            auto it = cached_jsons.find(full_filepath);
            if (it == cached_jsons.end())
            {
                std::ifstream file(full_filepath);
                file >> cached_jsons[full_filepath];
                file.close();
            }
        }
        catch (const std::runtime_error& e)
        {
            if (properties.custom)
            {
                LOG_ERROR("Missing custom definition for " << full_filepath << '\n' << e.what());
            }
            else
            {
                LOG_ERROR("Error reading blockstate file at " << full_filepath << '\n' << e.what());
            }
            
            models.push_back(Model::GetModel("", false));
            models_weights.push_back(1);
            weights_sum += 1;

            return;
        }

        const Json::Value& json = cached_jsons[full_filepath];

        // We store the models in a deque for efficiency
        std::deque<Model> models_deque;

        for (int i = 0; i < properties.variables.size(); ++i)
        {
            std::vector<std::string> splitted = Utilities::SplitString(properties.variables[i], '=');
            variables[splitted[0]] = splitted[1];
        }

        //If it's a "normal" blockstate
        if (json.contains("variants"))
        {
            Json::Value null_value;
            Json::Value& variant_value = null_value;

            if (json["variants"].contains(""))
            {
                variant_value = json["variants"][""];
            }

            if (json["variants"].contains("normal"))
            {
                variant_value = json["variants"]["normal"];
            }

            //This case means we have to check the variables to find
            //the right variant
            if (properties.variables.size() > 0 && variant_value.is_null())
            {
                int max_match = 0;

                for (const auto& [key, val] : json["variants"].get_object())
                {
                    const std::vector<std::string> variables_values = Utilities::SplitString(key, ',');
                    
                    int num_match = 0;
                    for (int i = 0; i < properties.variables.size(); ++i)
                    {
                        for (int j = 0; j < variables_values.size(); ++j)
                        {
                            if (properties.variables[i] == variables_values[j])
                            {
                                num_match++;
                            }
                        }
                    }
                    if (num_match > max_match)
                    {
                        variant_value = val;
                        max_match = num_match;
                    }
                }
            }

            //If we have found a correct value
            if (!variant_value.is_null())
            {
                if (variant_value.is_array())
                {
                    for (const auto& model : variant_value.get_array())
                    {
                        const int weight = WeightFromJson(model);
                        models_deque.push_back(ModelModificationFromJson(Model::GetModel(ModelNameFromJson(model), properties.custom), model));
                        models_weights.push_back(weight);
                        weights_sum += weight;
                    }
                }
                else
                {
                    const int weight = WeightFromJson(variant_value);
                    models_deque.push_back(ModelModificationFromJson(Model::GetModel(ModelNameFromJson(variant_value), properties.custom), variant_value));
                    models_weights.push_back(weight);
                    weights_sum += weight;
                }
            }
            else
            {
                LOG_ERROR("Error reading " << full_filepath);
                models_deque.push_back(Model::GetModel("", false));
                models_weights.push_back(1);
                weights_sum += 1;
            }
        }

        //If it's a multipart blockstate
        if (json.contains("multipart"))
        {
            //Start with an empty model
            models_deque.push_back(Model());
            models_weights.push_back(1);
            weights_sum = 0;

            for (const auto& part : json["multipart"].get_array())
            {
                //If no condition
                if (!part.contains("when"))
                {
                    //If there are several models
                    if (part["apply"].is_array())
                    {
                        size_t num_models = models_deque.size();
                        for (const auto& m : part["apply"].get_array())
                        {
                            const std::string model_name = ModelNameFromJson(m);
                            for (int k = 0; k < num_models; ++k)
                            {
                                models_deque.push_back(models_deque[k] + ModelModificationFromJson(Model::GetModel(model_name, properties.custom), m));
                                models_weights.push_back(models_weights[k] * WeightFromJson(m));
                            }
                        }
                        models_deque.erase(models_deque.begin(), models_deque.begin() + num_models);
                        models_weights.erase(models_weights.begin(), models_weights.begin() + num_models);
                    }
                    else
                    {
                        const std::string model_name = ModelNameFromJson(part["apply"]);
                        for (int k = 0; k < models_deque.size(); ++k)
                        {
                            models_deque[k] += ModelModificationFromJson(Model::GetModel(model_name, properties.custom), part["apply"]);
                            models_weights[k] *= WeightFromJson(part["apply"]);
                        }
                    }
                }
                //There is a condition !
                //We check if there is a match with the variables
                else
                {
                    bool condition = false;
                    //If it's a OR condition
                    if (part["when"].contains("OR"))
                    {
                        for (const auto& current_condition : part["when"]["OR"].get_array())
                        {
                            for (const auto& [key, val] : current_condition.get_object())
                            {
                                const std::string condition_name = key;
                                std::string condition_value = "";

                                if (val.is_string())
                                {
                                    condition_value = val.get_string();
                                }
                                else if (val.is_bool())
                                {
                                    condition_value = val.get<bool>() ? "true" : "false";
                                }
                                else if (val.is_number())
                                {
                                    condition_value = std::to_string(val.get_number<double>());
                                }

                                condition = CheckCondition(condition_name, condition_value, properties.variables);
                                //If one condition in the list is not verified,
                                //the whole condition is not
                                if (!condition)
                                {
                                    break;
                                }
                            }

                            if (condition)
                            {
                                break;
                            }
                        }
                    }
                    else
                    {
                        for (const auto& [key, val] : part["when"].get_object())
                        {
                            std::string condition_value = "";

                            if (val.is_string())
                            {
                                condition_value = val.get_string();
                            }
                            else if (val.is_bool())
                            {
                                condition_value = val.get<bool>() ? "true" : "false";
                            }
                            else if (val.is_number())
                            {
                                condition_value = std::to_string(val.get<double>());
                            }

                            condition = CheckCondition(key, condition_value, properties.variables);
                            //If one condition in the list is not verified,
                            //the whole condition is not
                            if (!condition)
                            {
                                break;
                            }
                        }
                    }

                    //If the condition is verified, add the model
                    if (condition)
                    {
                        //If there are several models
                        if (part["apply"].is_array())
                        {
                            size_t num_models = models_deque.size();
                            for (const auto& m : part["apply"].get_array())
                            {
                                const std::string model_name = ModelNameFromJson(m);
                                const int model_weight = WeightFromJson(m);
                                for (int k = 0; k < num_models; ++k)
                                {
                                    models_deque.push_back(models_deque[k] + ModelModificationFromJson(Model::GetModel(model_name, properties.custom), m));
                                    models_weights.push_back(models_weights[k] * model_weight);
                                }
                            }
                            models_deque.erase(models_deque.begin(), models_deque.begin() + num_models);
                            models_weights.erase(models_weights.begin(), models_weights.begin() + num_models);
                        }
                        else
                        {
                            const std::string model_name = ModelNameFromJson(part["apply"]);
                            const int model_weight = WeightFromJson(part["apply"]);
                            for (int k = 0; k < models_deque.size(); ++k)
                            {
                                models_deque[k] += ModelModificationFromJson(Model::GetModel(model_name, properties.custom), part["apply"]);
                                models_weights[k] *= model_weight;
                            }
                        }
                    }
                }
            }

            for (int i = 0; i < models_weights.size(); ++i)
            {
                weights_sum += models_weights[i];
            }
        }
        models = std::vector<Model>(std::make_move_iterator(models_deque.begin()), std::make_move_iterator(models_deque.end()));
    }

    Blockstate::Blockstate(const BlockstateProperties& properties, const Model &model_)
    {
        id = properties.id;
#if PROTOCOL_VERSION < 347
        metadata = properties.metadata;
#endif
        air = properties.air;
        transparent = properties.transparent;
        solid = properties.solid;
        climbable = properties.climbable;
        hazardous = properties.hazardous;
        hardness = properties.hardness;
        fluid = properties.fluid;
        tint_type = properties.tint_type;
        m_name = properties.name;
        any_tool_harvest = properties.any_tool_harvest;
        best_tools = properties.best_tools;
        for (int i = 0; i < properties.variables.size(); ++i)
        {
            std::vector<std::string> splitted = Utilities::SplitString(properties.variables[i], '=');
            variables[splitted[0]] = splitted[1];
        }

        weights_sum = 1;
        random_generator = std::mt19937(static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()));

        models_weights = { 1 };
        models = { model_ };
    }

    const unsigned int Blockstate::GetId() const
    {
        return id;
    }

#if PROTOCOL_VERSION < 347
    const unsigned char Blockstate::GetMetadata() const
    {
        return metadata;
    }
#endif

    const Model &Blockstate::GetModel(const unsigned short index) const
    {
        return models[index];
    }

    const unsigned char Blockstate::GetRandomModelId(const Position* pos) const
    {
        int random_value = 0;
        if (!pos)
        {
            random_value = std::uniform_int_distribution<int>(0, weights_sum - 1)(random_generator);
        }
        else
        {
            // Faster pseudo random choice
            random_value = (pos->x + pos->y + pos->z) % weights_sum;
        }
        
        const size_t num_models = models_weights.size();
        for (int i = 0; i < num_models; ++i)
        {
            if (random_value < models_weights[i])
            {
                return static_cast<unsigned char>(i);
            }
            random_value -= models_weights[i];
        }
        //Should never be here
        return 0;
    }

    const std::string& Blockstate::GetName() const
    {
        return m_name;
    }

    const std::string& Blockstate::GetVariableValue(const std::string& variable) const
    {
        return variables.at(variable);
    }

    const bool Blockstate::IsAir() const
    {
        return air;
    }

    const bool Blockstate::IsSolid() const
    {
        return solid;
    }

    const bool Blockstate::IsTransparent() const
    {
        return transparent;
    }

    const bool Blockstate::IsFluid() const
    {
        return fluid;
    }

    const bool Blockstate::IsClimbable() const
    {
        return climbable;
    }

    const bool Blockstate::IsHazardous() const
    {
        return hazardous;
    }

    bool Blockstate::IsWaterlogged() const
    {
        const auto it = variables.find("waterlogged");
        return it != variables.cend() && it->second == "true";
    }

    const float Blockstate::GetHardness() const
    {
        return hardness;
    }

    const TintType Blockstate::GetTintType() const
    {
        return tint_type;
    }

    float Blockstate::GetMiningTimeSeconds(const ToolType tool_type, const ToolMaterial tool_material,
        const unsigned char tool_efficiency, const unsigned char haste, const unsigned char fatigue,
        const bool on_ground, const bool head_in_fluid_wo_aqua_affinity) const
    {
        if (hardness < 0.0f || fluid)
        {
            return -1.0f;
        }

        static const std::array<float, static_cast<int>(ToolMaterial::NUM_TOOL_MATERIAL)> material_multipliers{ {
                1.0f,
                2.0f,
                12.0f,
                4.0f,
                6.0f,
                8.0f,
#if PROTOCOL_VERSION > 578 // > 1.15.2
                9.0f,
#endif
        } };

        float speed_multiplier = 1.0f;
        bool can_harvest = any_tool_harvest;

        for (const auto& t : best_tools)
        {
            // If this is not the tool we use, just skip to next one
            if (t.tool_type != tool_type)
            {
                continue;
            }

            switch (tool_type)
            {
            case ToolType::Shears:
            case ToolType::Sword:
                speed_multiplier = t.multiplier;
                can_harvest = true;
                break;
            case ToolType::Axe:
            case ToolType::Hoe:
            case ToolType::Pickaxe:
            case ToolType::Shovel:
                speed_multiplier = t.multiplier * material_multipliers[static_cast<int>(tool_material)];
                can_harvest |= tool_material >= t.min_material;
                break;
            default:
                LOG_WARNING("Unknown tool type: " << static_cast<int>(tool_type));
                break;
            }
            // If we are here we already found and processed the current tool
            break;
        }

        speed_multiplier += (tool_efficiency > 0) * 1.0f + tool_efficiency * tool_efficiency;
        speed_multiplier *= 1.0f + 0.2f * haste;
        speed_multiplier *= static_cast<float>(std::pow(0.3f, std::min(static_cast<int>(fatigue), 4)));
        speed_multiplier *= head_in_fluid_wo_aqua_affinity ? 0.2f : 1.0f;
        speed_multiplier *= on_ground ? 1.0f : 0.2f;

        const float damage_per_ticks = speed_multiplier / std::max(hardness, 0.0000001f) / (can_harvest ? 30.0f : 100.0f);

        if (damage_per_ticks > 1.0f)
        {
            return 0.0f;
        }

        return std::ceil(1.0f / damage_per_ticks) / 20.0f;
    }

#if PROTOCOL_VERSION < 347
    const unsigned int Blockstate::IdMetadataToId(const unsigned int id_, const unsigned char metadata_)
    {
        return id_ << 4 | metadata_;
    }

    void Blockstate::IdToIdMetadata(const unsigned int input_id, unsigned int &output_id, unsigned char &output_metadata)
    {
        output_id = input_id >> 4;
        output_metadata = input_id & 0x0F;
    }
#endif

    void Blockstate::ClearCache()
    {
        cached_jsons.clear();
    }

#if USE_GUI
    void Blockstate::UpdateModelsWithAtlasData(const Renderer::Atlas* atlas)
    {
        for (auto& m : models)
        {
            for (auto& f : m.GetFaces())
            {
                // Extract texture info in the atlas
                std::array<unsigned short, 4> texture_pos = { 0, 0, 0, 0 };
                std::array<unsigned short, 4> texture_size = { 0, 0, 0, 0 };
                std::array<Renderer::Transparency, 2> transparencies = { Renderer::Transparency::Opaque, Renderer::Transparency::Opaque };
                std::array<Renderer::Animation, 2> animated = { Renderer::Animation::Static, Renderer::Animation::Static };

                for (int i = 0; i < std::min(2, static_cast<int>(f.texture_names.size())); ++i)
                {
                    const Renderer::TextureData& texture_data = atlas->GetData(f.texture_names[i]);
                    std::tie(texture_pos[2 * i + 0], texture_pos[2 * i + 1]) = texture_data.position;
                    std::tie(texture_size[2 * i + 0], texture_size[2 * i + 1]) = texture_data.size;
                    transparencies[i] = texture_data.transparency;
                    animated[i] = texture_data.animation;
                }

                // Main texture coords in the atlas
                std::array<float, 4> coords = f.face.GetTextureCoords(false);
                unsigned short height_normalizer = animated[0] == Renderer::Animation::Animated ? texture_size[0] : texture_size[1];
                coords[0] = (texture_pos[0] + coords[0] / 16.0f * texture_size[0]) / atlas->GetWidth();
                coords[1] = (texture_pos[1] + coords[1] / 16.0f * height_normalizer) / atlas->GetHeight();
                coords[2] = (texture_pos[0] + coords[2] / 16.0f * texture_size[0]) / atlas->GetWidth();
                coords[3] = (texture_pos[1] + coords[3] / 16.0f * height_normalizer) / atlas->GetHeight();
                f.face.SetTextureCoords(coords, false);

                // Overlay texture coords in the atlas if existing
                if (f.texture_names.size() > 1)
                {
                    coords = f.face.GetTextureCoords(true);
                    height_normalizer = animated[1] == Renderer::Animation::Animated ? texture_size[2] : texture_size[3];
                    coords[0] = (texture_pos[2] + coords[0] / 16.0f * texture_size[2]) / atlas->GetWidth();
                    coords[1] = (texture_pos[3] + coords[1] / 16.0f * height_normalizer) / atlas->GetHeight();
                    coords[2] = (texture_pos[2] + coords[2] / 16.0f * texture_size[2]) / atlas->GetWidth();
                    coords[3] = (texture_pos[3] + coords[3] / 16.0f * height_normalizer) / atlas->GetHeight();
                    f.face.SetTextureCoords(coords, true);
                }
            
                f.face.SetTransparencyData(transparencies[0]);
            }
        }
    }
#endif

    const int Blockstate::GetNumModels() const
    {
        return static_cast<int>(models.size());
    }
} //Botcraft
