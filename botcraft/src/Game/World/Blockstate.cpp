#include <deque>
#include <fstream>
#include <set>

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

    Model ModelModificationFromJson(const Model& model, const Json::Value& json)
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
            const std::set<AABB>& colliders = output.GetColliders();
            std::set<AABB> new_colliders;
            for (const auto& collider : colliders)
            {
                Vector3<double> new_center;
                switch (rotation_x / 90)
                {
                case 0:
                    new_colliders.insert(collider);
                    break;
                case 1:
                    new_center = collider.GetCenter() - 0.5;
                    new_center = Vector3<double>(new_center.x, new_center.z, -new_center.y);
                    new_center = new_center + 0.5;
                    new_colliders.insert(AABB(new_center, Vector3<double>(collider.GetHalfSize().x, collider.GetHalfSize().z, collider.GetHalfSize().y)));
                    break;
                case 2:
                    new_center = collider.GetCenter() - 0.5;
                    new_center = Vector3<double>(new_center.x, -new_center.y, -new_center.z);
                    new_center = new_center + 0.5;
                    new_colliders.insert(AABB(new_center, Vector3<double>(collider.GetHalfSize().x, collider.GetHalfSize().y, collider.GetHalfSize().z)));
                    break;
                case 3:
                    new_center = collider.GetCenter() - 0.5;
                    new_center = Vector3<double>(new_center.x, -new_center.z, new_center.y);
                    new_center = new_center + 0.5;
                    new_colliders.insert(AABB(new_center, Vector3<double>(collider.GetHalfSize().x, collider.GetHalfSize().z, collider.GetHalfSize().y)));
                    break;
                default:
                    LOG_ERROR("Blockstate X rotation should be in 90 degrees steps");
                    break;
                }
            }
            output.SetColliders(new_colliders);
        }

        if (rotation_y != 0)
        {
            const std::set<AABB>& colliders = output.GetColliders();
            std::set<AABB> new_colliders;
            for (const auto& collider : colliders)
            {
                Vector3<double> new_center;
                switch (rotation_y / 90)
                {
                case 0:
                    new_colliders.insert(collider);
                    break;
                case 1:
                    new_center = collider.GetCenter() - 0.5;
                    new_center = Vector3<double>(-new_center.z, new_center.y, new_center.x);
                    new_center = new_center + 0.5;
                    new_colliders.insert(AABB(new_center, Vector3<double>(collider.GetHalfSize().z, collider.GetHalfSize().y, collider.GetHalfSize().x)));
                    break;
                case 2:
                    new_center = collider.GetCenter() - 0.5;
                    new_center = Vector3<double>(-new_center.x, new_center.y, -new_center.z);
                    new_center = new_center + 0.5;
                    new_colliders.insert(AABB(new_center, Vector3<double>(collider.GetHalfSize().x, collider.GetHalfSize().y, collider.GetHalfSize().z)));
                    break;
                case 3:
                    new_center = collider.GetCenter() - 0.5;
                    new_center = Vector3<double>(new_center.z, new_center.y, -new_center.x);
                    new_center = new_center + 0.5;
                    new_colliders.insert(AABB(new_center, Vector3<double>(collider.GetHalfSize().z, collider.GetHalfSize().y, collider.GetHalfSize().x)));
                    break;
                default:
                    LOG_ERROR("Blockstate Y rotation should be in 90 degrees steps");
                    break;
                }
            }
            output.SetColliders(new_colliders);
        }

#ifdef USE_GUI
        //Rotate faces

        if (rotation_x != 0)
        {
            std::vector<FaceDescriptor>& faces = output.GetFaces();

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
            std::vector<FaceDescriptor>& faces = output.GetFaces();

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
#if PROTOCOL_VERSION < 347 /* < 1.13 */
        return "block/" + model_path;
#elif PROTOCOL_VERSION > 578 /* > 1.15.2 */
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

    bool CheckCondition(const std::string& name, const std::string& value, const std::vector<std::string>& variables)
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
    std::set<std::string> Blockstate::unique_strings;
    std::deque<Model> Blockstate::unique_models;

    Blockstate::Blockstate(const BlockstateProperties& properties)
    {
        LoadProperties(properties);

        weights_sum = 0;

        if (properties.path == "none")
        {
            LoadWeightedModels({ {Model(), 1} });
            return;
        }

        if (properties.path.empty())
        {
            LoadWeightedModels({ {Model::GetModel("", false), 1} });
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

            LoadWeightedModels({ {Model::GetModel("", false), 1} });
            return;
        }

        const Json::Value& json = cached_jsons[full_filepath];

        // We store the models in a deque for efficiency
        std::deque<std::pair<Model, int>> weighted_models;

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
                        weighted_models.push_back({ ModelModificationFromJson(Model::GetModel(ModelNameFromJson(model), properties.custom), model), WeightFromJson(model) });
                    }
                }
                else
                {
                    weighted_models.push_back({ ModelModificationFromJson(Model::GetModel(ModelNameFromJson(variant_value), properties.custom), variant_value), WeightFromJson(variant_value) });
                }
            }
            else
            {
                LOG_ERROR("Error reading " << full_filepath);
                weighted_models.push_back({ Model::GetModel("", false), 1 });
            }
        }

        //If it's a multipart blockstate
        if (json.contains("multipart"))
        {
            //Start with an empty model
            weighted_models.push_back({ Model(), 1 });

            for (const auto& part : json["multipart"].get_array())
            {
                //If no condition
                if (!part.contains("when"))
                {
                    //If there are several models
                    if (part["apply"].is_array())
                    {
                        size_t num_models = weighted_models.size();
                        for (const auto& m : part["apply"].get_array())
                        {
                            const std::string model_name = ModelNameFromJson(m);
                            for (int k = 0; k < num_models; ++k)
                            {
                                weighted_models.push_back({ weighted_models[k].first + ModelModificationFromJson(Model::GetModel(model_name, properties.custom), m), weighted_models[k].second * WeightFromJson(m) });
                            }
                        }
                        weighted_models.erase(weighted_models.begin(), weighted_models.begin() + num_models);
                    }
                    else
                    {
                        const std::string model_name = ModelNameFromJson(part["apply"]);
                        for (int k = 0; k < weighted_models.size(); ++k)
                        {
                            weighted_models[k].first += ModelModificationFromJson(Model::GetModel(model_name, properties.custom), part["apply"]);
                            weighted_models[k].second *= WeightFromJson(part["apply"]);
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
                            size_t num_models = weighted_models.size();
                            for (const auto& m : part["apply"].get_array())
                            {
                                const std::string model_name = ModelNameFromJson(m);
                                const int model_weight = WeightFromJson(m);
                                for (int k = 0; k < num_models; ++k)
                                {
                                    weighted_models.push_back({ weighted_models[k].first + ModelModificationFromJson(Model::GetModel(model_name, properties.custom), m), weighted_models[k].second * model_weight });
                                }
                            }
                            weighted_models.erase(weighted_models.begin(), weighted_models.begin() + num_models);
                        }
                        else
                        {
                            const std::string model_name = ModelNameFromJson(part["apply"]);
                            const int model_weight = WeightFromJson(part["apply"]);
                            for (int k = 0; k < weighted_models.size(); ++k)
                            {
                                weighted_models[k].first += ModelModificationFromJson(Model::GetModel(model_name, properties.custom), part["apply"]);
                                weighted_models[k].second *= model_weight;
                            }
                        }
                    }
                }
            }
        }

        // If this block has colliders different from rendered model
        if (!properties.colliders.is_null())
        {
            std::set<AABB> colliders;
            if (properties.colliders.is_array())
            {
                for (const auto& c : properties.colliders.get_array())
                {
                    Vector3<double> from(
                        c["from"][0].get_number(),
                        c["from"][1].get_number(),
                        c["from"][2].get_number()
                    );
                    Vector3<double> to(
                        c["to"][0].get_number(),
                        c["to"][1].get_number(),
                        c["to"][2].get_number()
                    );
                    colliders.insert(AABB((from + to) / 2.0 / 16.0, (to - from) / 2.0 / 16.0));
                }
            }
            else if (properties.colliders.is_object())
            {
                for (const auto& [k, v] : properties.colliders.get_object())
                {
                    if (MatchCondition(k))
                    {
                        for (const auto& c : v.get_array())
                        {
                            Vector3<double> from(
                                c["from"][0].get_number(),
                                c["from"][1].get_number(),
                                c["from"][2].get_number()
                            );
                            Vector3<double> to(
                                c["to"][0].get_number(),
                                c["to"][1].get_number(),
                                c["to"][2].get_number()
                            );
                            colliders.insert(AABB((from + to) / 2.0 / 16.0, (to - from) / 2.0 / 16.0));
                        }
                        break;
                    }
                }
            }
            if (!colliders.empty())
            {
                for (auto& [m, i] : weighted_models)
                {
                    m.SetColliders(colliders);
                }
            }
        }

        LoadWeightedModels(weighted_models);
    }

    Blockstate::Blockstate(const BlockstateProperties& properties, const Model& model_)
    {
        LoadProperties(properties);

        LoadWeightedModels({ {model_, 1} });
    }

    BlockstateId Blockstate::GetId() const
    {
        return blockstate_id;
    }

    const Model& Blockstate::GetModel(const unsigned short index) const
    {
        return unique_models.at(models_indices[index]);
    }

    unsigned char Blockstate::GetModelId(const Position& pos) const
    {
        const size_t num_models = models_weights.size();

        // If there is only one model, don't bother computing hash
        if (num_models == 1)
        {
            return 0;
        }

        size_t random_value = std::hash<Position>{}(pos) % weights_sum;
        for (int i = 0; i < num_models; ++i)
        {
            if (random_value < models_weights[i])
            {
                return static_cast<unsigned char>(i);
            }
            random_value -= models_weights[i];
        }
        // Should never be here
        return 0;
    }

    const std::string& Blockstate::GetName() const
    {
        return *m_name;
    }

    const std::string& Blockstate::GetVariableValue(const std::string& variable) const
    {
        return *variables.at(&variable);
    }

    Vector3<double> Blockstate::GetHorizontalOffsetAtPos(const Position& pos) const
    {
        const double max_horizontal_offset =
            0.125f * flags[static_cast<size_t>(BlockstateFlags::HorizontalOffset0_125)] +
            0.25f * flags[static_cast<size_t>(BlockstateFlags::HorizontalOffset0_25)];
        if (max_horizontal_offset == 0.0)
        {
            return Vector3<double>(pos.x, pos.y, pos.z);
        }

        // We need to offset the colliders based on position-based pseudo randomness
        long long int pos_seed = static_cast<long long int>(pos.x * 3129871) ^ static_cast<long long int>(pos.z) * 116129781LL ^ 0LL;
        pos_seed = pos_seed * pos_seed * 42317861LL + pos_seed * 11LL;
        pos_seed = pos_seed >> 16;
        return Vector3<double>(
            std::clamp((static_cast<double>(static_cast<float>(pos_seed & 0xFLL) / 15.0f) - 0.5) * 0.5, -max_horizontal_offset, max_horizontal_offset) + pos.x,
            0.0 + pos.y,
            std::clamp((static_cast<double>(static_cast<float>(pos_seed >> 8 & 0xFLL) / 15.0f) - 0.5) * 0.5, -max_horizontal_offset, max_horizontal_offset) + pos.z
        );
    }

    std::set<AABB> Blockstate::GetCollidersAtPos(const Position& pos) const
    {
        std::set<AABB> output;

        const Model& model = GetModel(GetModelId(pos));

        const std::set<AABB>& colliders = model.GetColliders();
        const Vector3<double> offset = GetHorizontalOffsetAtPos(pos);
        for (const auto& c : colliders)
        {
            output.insert(c + offset);
        }
        return output;
    }

    bool Blockstate::IsAir() const
    {
        return flags[static_cast<size_t>(BlockstateFlags::Air)];
    }

    bool Blockstate::IsSolid() const
    {
        return flags[static_cast<size_t>(BlockstateFlags::Solid)];
    }

    bool Blockstate::IsTransparent() const
    {
        return flags[static_cast<size_t>(BlockstateFlags::Transparent)];
    }

    bool Blockstate::IsFluid() const
    {
        return flags[static_cast<size_t>(BlockstateFlags::Water)] ||
            flags[static_cast<size_t>(BlockstateFlags::Lava)];
    }

    bool Blockstate::IsFluidOrWaterlogged() const
    {
        return IsFluid() || flags[static_cast<size_t>(BlockstateFlags::WaterLogged)];
    }

    bool Blockstate::IsLava() const
    {
        return flags[static_cast<size_t>(BlockstateFlags::Lava)];
    }

    bool Blockstate::IsFluidFalling() const
    {
        return flags[static_cast<size_t>(BlockstateFlags::FluidFalling)];
    }

    bool Blockstate::IsWater() const
    {
        return flags[static_cast<size_t>(BlockstateFlags::Water)];
    }

    bool Blockstate::IsWaterlogged() const
    {
#if PROTOCOL_VERSION < 347 /* < 1.13 */
        // No waterlogging before 1.13
        return false;
#else
        return flags[static_cast<size_t>(BlockstateFlags::WaterLogged)];
#endif
    }

    bool Blockstate::IsWaterOrWaterlogged() const
    {
        return IsWater() || IsWaterlogged();
    }

    bool Blockstate::IsClimbable() const
    {
        return flags[static_cast<size_t>(BlockstateFlags::Climbable)];
    }

    bool Blockstate::IsHazardous() const
    {
        return flags[static_cast<size_t>(BlockstateFlags::Hazardous)];
    }

    bool Blockstate::IsSlime() const
    {
        return flags[static_cast<size_t>(BlockstateFlags::Slime)];
    }

    bool Blockstate::IsBed() const
    {
        return flags[static_cast<size_t>(BlockstateFlags::Bed)];
    }

    bool Blockstate::IsSoulSand() const
    {
        return flags[static_cast<size_t>(BlockstateFlags::SoulSand)];
    }

    bool Blockstate::IsHoney() const
    {
#if PROTOCOL_VERSION < 573 /* < 1.15 */
        return false;
#else
        return flags[static_cast<size_t>(BlockstateFlags::Honey)];
#endif
    }

    bool Blockstate::IsScaffolding() const
    {
#if PROTOCOL_VERSION < 477 /* < 1.14 */
        return false;
#else
        return flags[static_cast<size_t>(BlockstateFlags::Scaffolding)];
#endif
    }

    bool Blockstate::IsBubbleColumn() const
    {
        return IsDownBubbleColumn() || IsUpBubbleColumn();
    }

    bool Blockstate::IsUpBubbleColumn() const
    {
#if PROTOCOL_VERSION < 347 /* < 1.13 */
        // No bubble column before 1.13
        return false;
#else
        return flags[static_cast<size_t>(BlockstateFlags::UpBubbleColumn)];
#endif
    }

    bool Blockstate::IsDownBubbleColumn() const
    {
#if PROTOCOL_VERSION < 347 /* < 1.13 */
        // No bubble column before 1.13
        return false;
#else
        return flags[static_cast<size_t>(BlockstateFlags::DownBubbleColumn)];
#endif
    }

    bool Blockstate::IsCobweb() const
    {
        return flags[static_cast<size_t>(BlockstateFlags::Cobweb)];
    }

    bool Blockstate::IsBerryBush() const
    {
#if PROTOCOL_VERSION < 477 /* < 1.14 */
        return false;
#else
        return flags[static_cast<size_t>(BlockstateFlags::BerryBush)];
#endif
    }

    bool Blockstate::IsPowderSnow() const
    {
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        return false;
#else
        return flags[static_cast<size_t>(BlockstateFlags::PowderSnow)];
#endif
    }

    float Blockstate::GetHardness() const
    {
        return hardness;
    }

    float Blockstate::GetFriction() const
    {
        return friction;
    }

    TintType Blockstate::GetTintType() const
    {
        return tint_type;
    }

    float Blockstate::GetFluidHeight() const
    {
        if (!IsFluidOrWaterlogged())
        {
            return 0.0f;
        }
        if (flags[static_cast<size_t>(BlockstateFlags::FluidFalling)])
        {
            return 1.0f;
        }
        if (IsWaterlogged())
        {
            return 8.0f / 9.0f;
        }

        const char level = static_cast<char>(flags[static_cast<size_t>(BlockstateFlags::FluidLevelBit_0)]) |
            static_cast<char>(flags[static_cast<size_t>(BlockstateFlags::FluidLevelBit_1)] << 1) |
            static_cast<char>(flags[static_cast<size_t>(BlockstateFlags::FluidLevelBit_2)] << 2);

        return 1.0f - static_cast<float>(level + 1) / 9.0f;
    }

    float Blockstate::GetMiningTimeSeconds(const ToolType tool_type, const ToolMaterial tool_material,
        const unsigned char tool_efficiency, const unsigned char haste, const unsigned char fatigue,
        const bool on_ground, const bool head_in_fluid_wo_aqua_affinity, const float speed_factor) const
    {
        if (hardness < 0.0f || IsWater() || IsLava())
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
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
                9.0f,
#endif
        } };

        float speed_multiplier = 1.0f;
        bool can_harvest = flags[static_cast<size_t>(BlockstateFlags::AnyToolHarvest)];

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
        speed_multiplier *= speed_factor;
        speed_multiplier *= head_in_fluid_wo_aqua_affinity ? 0.2f : 1.0f;
        speed_multiplier *= on_ground ? 1.0f : 0.2f;

        const float damage_per_ticks = speed_multiplier / std::max(hardness, 0.0000001f) / (can_harvest ? 30.0f : 100.0f);

        if (damage_per_ticks > 1.0f)
        {
            return 0.0f;
        }

        return std::ceil(1.0f / damage_per_ticks) / 20.0f;
    }

#if PROTOCOL_VERSION < 347 /* < 1.13 */
    unsigned int Blockstate::IdMetadataToId(const int id_, const unsigned char metadata_)
    {
        return id_ << 4 | metadata_;
    }

    void Blockstate::IdToIdMetadata(const unsigned int input_id, int& output_id, unsigned char& output_metadata)
    {
        output_id = input_id >> 4;
        output_metadata = input_id & 0x0F;
    }
#endif

    void Blockstate::ClearCache()
    {
        cached_jsons.clear();
        unique_models.shrink_to_fit();
    }

#if USE_GUI
    void Blockstate::UpdateModelsWithAtlasData(const Renderer::Atlas* atlas)
    {
        for (auto& m : unique_models)
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

    size_t Blockstate::GetNumModels() const
    {
        return models_indices.size();
    }

    void Blockstate::LoadProperties(const BlockstateProperties& properties)
    {
        m_name = GetUniqueStringPtr(properties.name);
        hardness = properties.hardness;
        friction = properties.friction;
        tint_type = properties.tint_type;
        best_tools = properties.best_tools;

        for (int i = 0; i < properties.variables.size(); ++i)
        {
            std::vector<std::string> splitted = Utilities::SplitString(properties.variables[i], '=');
            variables[GetUniqueStringPtr(splitted[0])] = GetUniqueStringPtr(splitted[1]);

            // Special case for fluids
            if ((properties.lava || properties.water) && splitted[0] == "level")
            {
                const int level = std::stoi(splitted[1]);
                flags[static_cast<size_t>(BlockstateFlags::FluidFalling)] = (level >> 3) & 0x01;
                flags[static_cast<size_t>(BlockstateFlags::FluidLevelBit_0)] = (level >> 0) & 0x01;
                flags[static_cast<size_t>(BlockstateFlags::FluidLevelBit_1)] = (level >> 1) & 0x01;
                flags[static_cast<size_t>(BlockstateFlags::FluidLevelBit_2)] = (level >> 2) & 0x01;
            }
        }
#if PROTOCOL_VERSION < 347 /* < 1.13 */
        blockstate_id = { properties.id, properties.metadata };
#else
        blockstate_id = properties.id;
#endif

        flags[static_cast<size_t>(BlockstateFlags::Air)] = properties.air;
        flags[static_cast<size_t>(BlockstateFlags::Solid)] = GetBoolFromCondition(properties.solid);
        flags[static_cast<size_t>(BlockstateFlags::Transparent)] = properties.transparent;
        flags[static_cast<size_t>(BlockstateFlags::Lava)] = properties.lava;
        flags[static_cast<size_t>(BlockstateFlags::Water)] = properties.water;
        flags[static_cast<size_t>(BlockstateFlags::WaterLogged)] = GetBoolFromCondition(properties.waterlogged);
        // FluidFalling and FluidLevelBit_N are already set when loading variables
        flags[static_cast<size_t>(BlockstateFlags::Climbable)] = properties.climbable;
        flags[static_cast<size_t>(BlockstateFlags::Hazardous)] = properties.hazardous;
        flags[static_cast<size_t>(BlockstateFlags::AnyToolHarvest)] = properties.any_tool_harvest;
        flags[static_cast<size_t>(BlockstateFlags::Slime)] = properties.slime;
        flags[static_cast<size_t>(BlockstateFlags::Bed)] = properties.bed;
        flags[static_cast<size_t>(BlockstateFlags::SoulSand)] = properties.soul_sand;
        flags[static_cast<size_t>(BlockstateFlags::Honey)] = properties.honey;
        flags[static_cast<size_t>(BlockstateFlags::Scaffolding)] = properties.scaffolding;
        flags[static_cast<size_t>(BlockstateFlags::Cobweb)] = properties.cobweb;
        flags[static_cast<size_t>(BlockstateFlags::DownBubbleColumn)] = GetBoolFromCondition(properties.down_bubble_column);
        flags[static_cast<size_t>(BlockstateFlags::UpBubbleColumn)] = GetBoolFromCondition(properties.up_bubble_column);
        flags[static_cast<size_t>(BlockstateFlags::BerryBush)] = properties.berry_bush;
        flags[static_cast<size_t>(BlockstateFlags::PowderSnow)] = properties.powder_snow;
        flags[static_cast<size_t>(BlockstateFlags::HorizontalOffset0_25)] = std::abs(properties.horizontal_offset - 0.25f) < 0.01f;
        flags[static_cast<size_t>(BlockstateFlags::HorizontalOffset0_125)] = std::abs(properties.horizontal_offset - 0.125f) < 0.01f;
    }

    void Blockstate::LoadWeightedModels(const std::deque<std::pair<Model, int>>& models_to_load)
    {
        models_indices.clear();
        models_indices.reserve(models_to_load.size());
        models_weights.clear();
        models_weights.reserve(models_to_load.size());
        weights_sum = 0;

        for (const auto& [m, w] : models_to_load)
        {
            bool already_present = false;
            for (size_t i = 0; i < models_indices.size(); ++i)
            {
                if (unique_models[models_indices[i]].IsSame(m))
                {
                    already_present = true;
                    models_weights[i] += w;
                    weights_sum += w;
                    break;
                }
            }
            if (already_present)
            {
                continue;
            }

            models_indices.push_back(GetUniqueModelIndex(m));
            models_weights.push_back(w);
            weights_sum += w;
        }

        models_indices.shrink_to_fit();
        models_weights.shrink_to_fit();
    }

    bool Blockstate::GetBoolFromCondition(const Json::Value& condition) const
    {
        if (condition.is_bool())
        {
            return condition.get<bool>();
        }
        else if (condition.is_string())
        {
            return MatchCondition(condition.get_string());
        }
        throw std::runtime_error("Unknown JSON type in GetBoolFromCondition for block " + GetName());
    }

    bool Blockstate::MatchCondition(const std::string& condition) const
    {
        const std::vector<std::string> and_conditions = Utilities::SplitString(condition, ',');
        for (const std::string& c : and_conditions)
        {
            bool current_result = false;
            const bool is_negative = Utilities::Contains(c, "!=");
            const std::vector<std::string> splitted = is_negative ? Utilities::SplitString(c, "!=") : Utilities::SplitString(c, '=');
            const std::string& variable = splitted[0];
            const std::string& value = splitted[1];
            for (const auto [k, v] : variables)
            {
                if (*k == variable)
                {
                    current_result = is_negative ? *v != value : *v == value;
                    break;
                }
            }
            if (!current_result)
            {
                return false;
            }
        }
        return true;
    }

    const std::string* Blockstate::GetUniqueStringPtr(const std::string& s)
    {
        return &*unique_strings.insert(s).first;
    }

    size_t Blockstate::GetUniqueModelIndex(const Model& model)
    {
        // Don't bother searching for a preexisting model if USE_GUI
        // as IsSame always returns false anyway
#if !USE_GUI
        for (size_t i = 0; i < unique_models.size(); ++i)
        {
            if (model.IsSame(unique_models[i]))
            {
                return i;
            }
        }
#endif
        unique_models.push_back(model);
        return unique_models.size() - 1;
    }
} //Botcraft
