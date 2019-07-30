#include <sstream>
#include <fstream>
#include <iostream>
#include <random>
#include <chrono>

#include <picojson/picojson.h>

#include "botcraft/Game/World/Blockstate.hpp"
#include "botcraft/Version.hpp"

namespace Botcraft
{
    // Utilities functions

    Model ModelModificationFromJson(const Model &model, const std::string &s)
    {
        picojson::value json_value;
        picojson::parse(json_value, s);

        const picojson::object &json = json_value.get<picojson::object>();

        Model output = model;

        bool uv_lock = false;
        auto it = json.find("uvlock");
        if (it != json.end())
        {
            uv_lock = it->second.get<bool>();
        }

        int rotation_x = 0;
        it = json.find("x");
        if (it != json.end())
        {
            rotation_x = (int)it->second.get<double>();
        }

        int rotation_y = 0;
        it = json.find("y");
        if (it != json.end())
        {
            rotation_y = (int)it->second.get<double>();
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
                    new_center = Vector3<double>(new_center.x, -new_center.z, new_center.y);
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
                    new_center = Vector3<double>(new_center.x, new_center.z, -new_center.y);
                    new_center = new_center + 0.5;
                    colliders[i] = AABB(new_center, Vector3<double>(colliders[i].GetHalfSize().x, colliders[i].GetHalfSize().z, colliders[i].GetHalfSize().y));
                    break;
                default:
                    std::cerr << "Error, blockstate X rotation should be in 90° steps" << std::endl;
                    break;
                }
            }
        }

        if (rotation_y != 0)
        {
            // Not sure why I need this
            rotation_y = 360 - rotation_y;

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
                    new_center = Vector3<double>(new_center.z, new_center.y, -new_center.x);
                    new_center = new_center + 0.5;
                    colliders[i] = AABB(new_center, Vector3<double>(colliders[i].GetHalfSize().z, colliders[i].GetHalfSize().z, colliders[i].GetHalfSize().x));
                    break;
                case 2:
                    new_center = colliders[i].GetCenter() - 0.5;
                    new_center = Vector3<double>(-new_center.x, new_center.y, -new_center.z);
                    new_center = new_center + 0.5;
                    colliders[i] = AABB(new_center, Vector3<double>(colliders[i].GetHalfSize().x, colliders[i].GetHalfSize().y, colliders[i].GetHalfSize().z));
                    break;
                case 3:
                    new_center = colliders[i].GetCenter() - 0.5;
                    new_center = Vector3<double>(-new_center.z, new_center.y, new_center.x);
                    new_center = new_center + 0.5;
                    colliders[i] = AABB(new_center, Vector3<double>(colliders[i].GetHalfSize().z, colliders[i].GetHalfSize().y, colliders[i].GetHalfSize().x));
                    break;
                default:
                    std::cerr << "Error, blockstate Y rotation should be in 90° steps" << std::endl;
                    break;
                }
            }
        }

#ifdef USE_GUI
        //Rotate faces

        if (rotation_x != 0)
        {
            std::vector<FaceDescriptor> &faces = output.GetFaces();

            std::vector<Orientation> rotated_orientations = { Orientation::Top, Orientation::South, Orientation::Bottom, Orientation::North };

            for (int f = 0; f < faces.size(); ++f)
            {
                //We want to add this transformation after the local translations,
                //Just before the global translation to final position
                faces[f].transformations.translations.insert(faces[f].transformations.translations.begin(), Renderer::TransformationPtr(new Renderer::Rotation(1.0f, 0.0f, 0.0f, rotation_x)));

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

            std::vector<Orientation> rotated_orientations = { Orientation::South, Orientation::East, Orientation::North, Orientation::West };

            for (int f = 0; f < faces.size(); ++f)
            {
                //We want to add this transformation after the local translations,
                //Just before the global translation to final position
                faces[f].transformations.translations.insert(faces[f].transformations.translations.begin(), Renderer::TransformationPtr(new Renderer::Rotation(0.0f, 1.0f, 0.0f, rotation_y)));

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
                        faces[f].transformations.rotation -= rotation_y / 90;
                    }
                }
                faces[f].face = Renderer::Face(faces[f].transformations, faces[f].orientation);
            }
        }
#endif

        return output;
    }

    std::string ModelNameFromJson(const std::string &s)
    {
        picojson::value json_value;
        picojson::parse(json_value, s);

        const picojson::object &json = json_value.get<picojson::object>();

        auto it = json.find("model");
        std::string model_path = it->second.get<std::string>();

        return model_path;
    }

    int WeightFromJson(const std::string &s)
    {
        picojson::value json_value;
        picojson::parse(json_value, s);

        const picojson::object &json = json_value.get<picojson::object>();

        int output = 1;

        auto it = json.find("weight");
        if (it != json.end())
        {
            output = (int)it->second.get<double>();
        }

        return output;
    }

    const bool StartsWith(const std::string &mainStr, const std::string &toMatch)
    {
        return mainStr.find(toMatch) == 0;
    }

    const std::vector<std::string> SplitString(const std::string& s, const char delimiter)
    {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter))
        {
            tokens.push_back(token);
        }
        return tokens;
    }

    const bool CheckCondition(const std::string &name, const std::string &value, const std::vector<std::string> &variables)
    {
        const std::vector<std::string> possible_values = SplitString(value, '|');

        bool output = false;

        for (int i = 0; i < variables.size(); ++i)
        {
            if (StartsWith(variables[i], name))
            {
                for (int j = 0; j < possible_values.size(); ++j)
                {
                    if (StartsWith(variables[i], possible_values[j]))
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
#if PROTOCOL_VERSION < 347
    Blockstate::Blockstate(const int id_, const unsigned char metadata_, 
                           const bool transparent_, const bool solid_, const bool fluid_,
                           const float hardness_, const TintType tint_type_, const std::string &name_,
                           const std::string &path, const std::vector<std::string> &variables) :
                           id(id_), metadata(metadata_), transparent(transparent_), solid(solid_), fluid(fluid_),
                           hardness(hardness_), tint_type(tint_type_), m_name(name_)
#else
    Blockstate::Blockstate(const int id_,
                           const bool transparent_, const bool solid_, const bool fluid_,
                           const float hardness_, const TintType tint_type_, const std::string &name_,
                           const std::string &path, const std::vector<std::string> &variables) :
                           id(id_), transparent(transparent_), solid(solid_), fluid(fluid_),
                           hardness(hardness_), tint_type(tint_type_), m_name(name_)
#endif
    {
        weights_sum = 0;
        random_generator = std::mt19937(std::chrono::system_clock::now().time_since_epoch().count());
        std::map<std::string, Model> models_cache;

        if (path == "none")
        {
            models.push_back(Model());
            models_weights.push_back(1);
            weights_sum += 1;
            return;
        }

        std::string full_filepath = ASSETS_PATH + std::string("/minecraft/blockstates/") + path + ".json";

        std::stringstream ss;
        std::ifstream file;

        bool error = path == "";
        picojson::value json;

        if (!error)
        {
            file.open(full_filepath);
            if (!file.is_open())
            {
                std::cerr << "Error reading blockstate file at " << full_filepath << std::endl;
                error = true;
            }
            if (!error)
            {
                ss << file.rdbuf();
                file.close();

                ss >> json;
                std::string err = picojson::get_last_error();

                if (!err.empty())
                {
                    std::cerr << "Error parsing blockstate file at " << full_filepath << "\n";
                    std::cerr << err << std::endl;
                    error = true;
                }
                if (!error)
                {

                    if (!json.is<picojson::object>())
                    {
                        std::cerr << "Error parsing blockstate file at " << full_filepath << std::endl;
                        error = true;
                    }
                }
            }
        }

        if (error)
        {
            models.push_back(Model(""));
            models_weights.push_back(1);
            weights_sum += 1;
            return;
        }

        const picojson::object& base_object = json.get<picojson::object>();

        //If it's a "normal" blockstate
        auto it = base_object.find("variants");
        if (it != base_object.end())
        {
            const picojson::object& variants = it->second.get<picojson::object>();
            picojson::value &variant_value = picojson::value();

            auto it2 = variants.find("");
            if (it2 != variants.end())
            {
                variant_value = it2->second;
            }

            it2 = variants.find("normal");
            if (it2 != variants.end())
            {
                variant_value = it2->second;
            }

            //This case means we have to check the variables to find
            //the right variant
            if (variables.size() > 0 && variant_value.is<picojson::null>())
            {
                int max_match = 0;

                for (it2 = variants.begin(); it2 != variants.end(); ++it2)
                {
                    const std::vector<std::string> variables_values = SplitString(it2->first, ',');
                    
                    int num_match = 0;
                    for (int i = 0; i < variables.size(); ++i)
                    {
                        for (int j = 0; j < variables_values.size(); ++j)
                        {
                            if (variables[i] == variables_values[j])
                            {
                                num_match++;
                            }
                        }
                    }
                    if (num_match > max_match)
                    {
                        variant_value = it2->second;
                        max_match = num_match;
                    }
                }
            }

            //If we have found a correct value
            if (!variant_value.is<picojson::null>())
            {
                if (variant_value.is<picojson::array>())
                {
                    picojson::array &models_array = variant_value.get<picojson::array>();
                    for (int i = 0; i < models_array.size(); ++i)
                    {
                        const std::string serialized = models_array[i].serialize();
                        const std::string model_name = ModelNameFromJson(serialized);
                        auto cache_it = models_cache.find(model_name);
                        if (cache_it == models_cache.end())
                        {
#if PROTOCOL_VERSION < 347
                            models_cache[model_name] = Model("block/" + model_name);
#else
                            models_cache[model_name] = Model(model_name);
#endif
                        }
                        const int weight = WeightFromJson(serialized);
                        models.push_back(ModelModificationFromJson(models_cache[model_name], serialized));
                        models_weights.push_back(weight);
                        weights_sum += weight;
                    }
                }
                else
                {
                    const std::string serialized = variant_value.serialize();
                    const std::string model_name = ModelNameFromJson(serialized);
                    auto cache_it = models_cache.find(model_name);
                    if (cache_it == models_cache.end())
                    {
#if PROTOCOL_VERSION < 347
                        models_cache[model_name] = Model("block/" + model_name);
#else
                        models_cache[model_name] = Model(model_name);
#endif
                    }
                    const int weight = WeightFromJson(serialized);
                    models.push_back(ModelModificationFromJson(models_cache[model_name], serialized));
                    models_weights.push_back(weight);
                    weights_sum += weight;
                }
            }
            else
            {
                std::cerr << "Error reading " << full_filepath << std::endl;
                models.push_back(Model(""));
                models_weights.push_back(1);
                weights_sum += 1;
            }
        }

        //If it's a multipart blockstate
        it = base_object.find("multipart");
        if (it != base_object.end())
        {
            //Start with an empty model
            models.push_back(Model());
            models_weights.push_back(1);
            weights_sum = 0;

            const picojson::array& parts = it->second.get<picojson::array>();

            for (int i = 0; i < parts.size(); ++i)
            {
                const picojson::object &current_case = parts[i].get<picojson::object>();

                auto it2 = current_case.find("when");
                //If no condition
                if (it2 == current_case.end())
                {
                    auto it3 = current_case.find("apply");

                    //If there are several models
                    if (it3->second.is<picojson::array>())
                    {
                        size_t num_models = models.size();
                        const picojson::array &models_array = it3->second.get<picojson::array>();
                        for (int j = 0; j < models_array.size(); ++j)
                        {
                            const std::string serialized = models_array[i].serialize();
                            const std::string model_name = ModelNameFromJson(serialized);
                            auto cache_it = models_cache.find(model_name);
                            if (cache_it == models_cache.end())
                            {
#if PROTOCOL_VERSION < 347
                                models_cache[model_name] = Model("block/" + model_name);
#else
                                models_cache[model_name] = Model(model_name);
#endif
                            }
                            for (int k = 0; k < num_models; ++k)
                            {
                                models.push_back(models[k] + ModelModificationFromJson(models_cache[model_name], serialized));
                                models_weights.push_back(models_weights[k] * WeightFromJson(serialized));
                            }
                        }
                        models.erase(models.begin(), models.begin() + num_models);
                        models_weights.erase(models_weights.begin(), models_weights.begin() + num_models);
                    }
                    else
                    {
                        const std::string serialized = it3->second.serialize();
                        const std::string model_name = ModelNameFromJson(serialized);
                        auto cache_it = models_cache.find(model_name);
                        if (cache_it == models_cache.end())
                        {
#if PROTOCOL_VERSION < 347
                            models_cache[model_name] = Model("block/" + model_name);
#else
                            models_cache[model_name] = Model(model_name);
#endif
                        }
                        for (int k = 0; k < models.size(); ++k)
                        {
                            models[k] += ModelModificationFromJson(models_cache[model_name], serialized);
                            models_weights[k] *= WeightFromJson(serialized);
                        }
                    }
                }
                //There is a condition !
                //We check if there is a match with the variables
                else
                {
                    bool condition = false;

                    const picojson::object &when = it2->second.get<picojson::object>();

                    auto it_or = when.find("OR");

                    //If it's a OR condition
                    if (it_or != when.end())
                    {
                        const picojson::array &conditions = it_or->second.get<picojson::array>();

                        for (int c = 0; c < conditions.size(); ++c)
                        {
                            const picojson::object &current_condition = conditions[c].get<picojson::object>();

                            for (auto condition_it = current_condition.begin(); condition_it != current_condition.end(); ++condition_it)
                            {
                                const std::string condition_name = condition_it->first;
                                std::string condition_value = "";

                                if (condition_it->second.is<std::string>())
                                {
                                    condition_value = condition_it->second.get<std::string>();
                                }
                                else if (condition_it->second.is<bool>())
                                {
                                    condition_value = condition_it->second.get<bool>() ? "true" : "false";
                                }
                                else if (condition_it->second.is<double>())
                                {
                                    condition_value = std::to_string(condition_it->second.get<double>());
                                }

                                condition = CheckCondition(condition_name, condition_value, variables);
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
                        for (auto condition_it = when.begin(); condition_it != when.end(); ++condition_it)
                        {
                            const std::string condition_name = condition_it->first;
                            std::string condition_value = "";

                            if (condition_it->second.is<std::string>())
                            {
                                condition_value = condition_it->second.get<std::string>();
                            }
                            else if (condition_it->second.is<bool>())
                            {
                                condition_value = condition_it->second.get<bool>() ? "true" : "false";
                            }
                            else if (condition_it->second.is<double>())
                            {
                                condition_value = std::to_string(condition_it->second.get<double>());
                            }

                            condition = CheckCondition(condition_name, condition_value, variables);
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
                        auto it3 = current_case.find("apply");

                        //If there are several models
                        if (it3->second.is<picojson::array>())
                        {
                            size_t num_models = models.size();
                            const picojson::array &models_array = it3->second.get<picojson::array>();
                            for (int j = 0; j < models_array.size(); ++j)
                            {
                                const std::string serialized = models_array[j].serialize();
                                const std::string model_name = ModelNameFromJson(serialized);
                                auto cache_it = models_cache.find(model_name);
                                if (cache_it == models_cache.end())
                                {
#if PROTOCOL_VERSION < 347
                                    models_cache[model_name] = Model("block/" + model_name);
#else
                                    models_cache[model_name] = Model(model_name);
#endif
                                }
                                for (int k = 0; k < num_models; ++k)
                                {
                                    models.push_back(models[k] + ModelModificationFromJson(models_cache[model_name], serialized));
                                    models_weights.push_back(models_weights[k] * WeightFromJson(serialized));
                                }
                            }
                            models.erase(models.begin(), models.begin() + num_models);
                            models_weights.erase(models_weights.begin(), models_weights.begin() + num_models);
                        }
                        else
                        {
                            const std::string serialized = it3->second.serialize();
                            const std::string model_name = ModelNameFromJson(serialized);
                            auto cache_it = models_cache.find(model_name);
                            if (cache_it == models_cache.end())
                            {
#if PROTOCOL_VERSION < 347
                                models_cache[model_name] = Model("block/" + model_name);
#else
                                models_cache[model_name] = Model(model_name);
#endif
                            }
                            for (int k = 0; k < models.size(); ++k)
                            {
                                models[k] += ModelModificationFromJson(models_cache[model_name], serialized);
                                models_weights[k] *= WeightFromJson(serialized);
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
    }
    
#if PROTOCOL_VERSION < 347
    Blockstate::Blockstate(const int id_, const unsigned char metadata_,
                           const bool transparent_, const bool solid_, const bool fluid_,
                           const float hardness_, const TintType tint_type_, const std::string &name_,
                           const Model &model_) :
                           id(id_), metadata(metadata_), transparent(transparent_),solid(solid_),
                           hardness(hardness_), fluid(fluid_), tint_type(tint_type_), m_name(name_)
#else
    Blockstate::Blockstate(const int id_,
                           const bool transparent_, const bool solid_, const bool fluid_,
                           const float hardness_, const TintType tint_type_, const std::string &name_,
                           const Model &model_) :
                           id(id_), transparent(transparent_), solid(solid_), 
                           hardness(hardness_), fluid(fluid_), tint_type(tint_type_), m_name(name_)
#endif
    {
        weights_sum = 1;
        random_generator = std::mt19937(std::chrono::system_clock::now().time_since_epoch().count());

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

    const Model &Blockstate::GetModel(const unsigned char index) const
    {
        return models[index];
    }

    const unsigned char Blockstate::GetRandomModelId()
    {
        int random_value = std::uniform_int_distribution<int>(0, weights_sum - 1)(random_generator);
        for (int i = 0; i < models_weights.size(); ++i)
        {
            if (random_value < models_weights[i])
            {
                return (unsigned char)i;
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

    const bool Blockstate::IsAir() const
    {
        return id == 0;
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

    const float Blockstate::GetHardness() const
    {
        return hardness;
    }

    const TintType Blockstate::GetTintType() const
    {
        return tint_type;
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

    const int Blockstate::GetNumModels() const
    {
        return models.size();
    }
} //Botcraft