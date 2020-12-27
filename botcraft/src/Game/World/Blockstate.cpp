#include <sstream>
#include <fstream>
#include <iostream>
#include <random>
#include <chrono>

#include <picojson/picojson.h>

#include "botcraft/Game/World/Blockstate.hpp"
#include "botcraft/Utilities/StringUtilities.hpp"

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
                    std::cerr << "Error, blockstate X rotation should be in 90° steps" << std::endl;
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

            std::vector<Orientation> rotated_orientations = { Orientation::Top, Orientation::North, Orientation::Bottom, Orientation::South };

            for (int f = 0; f < faces.size(); ++f)
            {
                //We want to add this transformation after the local translations,
                //Just before the global translation to final position
                faces[f].transformations.translations.insert(faces[f].transformations.translations.begin(), Renderer::TransformationPtr(new Renderer::Rotation(1.0f, 0.0f, 0.0f, -rotation_x)));

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
                faces[f].transformations.translations.insert(faces[f].transformations.translations.begin(), Renderer::TransformationPtr(new Renderer::Rotation(0.0f, 1.0f, 0.0f, -rotation_y)));

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

    std::string ModelNameFromJson(const std::string &s)
    {
        picojson::value json_value;
        picojson::parse(json_value, s);

        const picojson::object &json = json_value.get<picojson::object>();

        auto it = json.find("model");
        std::string model_path = it->second.get<std::string>();
#if PROTOCOL_VERSION < 347
        return "block/" + model_path;
#elif PROTOCOL_VERSION > 578 //> 1.15.2
        // Remove the minecraft: prefix from the model path
        return model_path.substr(10);
#else
        return model_path;
#endif
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
                    if (EndsWith(variables[i], possible_values[j]))
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
    std::map<std::string, picojson::value> Blockstate::cached_jsons;

#if PROTOCOL_VERSION < 347
    Blockstate::Blockstate(const int id_, const unsigned char metadata_, 
                           const bool transparent_, const bool solid_, const bool fluid_,
                           const float hardness_, const TintType tint_type_, const std::string &name_,
                           const std::string &path, const std::vector<std::string> &variables) :
                           id(id_), metadata(metadata_), transparent(transparent_), solid(solid_), fluid(fluid_),
                           hardness(hardness_), tint_type(tint_type_), m_name(name_)
#else
    Blockstate::Blockstate(const int id_,
                           const bool transparent_, const bool solid_, const bool fluid_, const bool custom,
                           const float hardness_, const TintType tint_type_, const std::string &name_,
                           const std::string &path, const std::vector<std::string> &variables) :
                           id(id_), transparent(transparent_), solid(solid_), fluid(fluid_),
                           hardness(hardness_), tint_type(tint_type_), m_name(name_)
#endif
    {
        weights_sum = 0;
        random_generator = std::mt19937(std::chrono::system_clock::now().time_since_epoch().count());

        if (path == "none")
        {
            models.push_back(Model());
            models_weights.push_back(1);
            weights_sum += 1;
            return;
        }

        std::string full_filepath;
        
        if (custom)
        {
            full_filepath = ASSETS_PATH + std::string("/custom/blockstates/") + path + ".json";
        }
        else
        {
            full_filepath = ASSETS_PATH + std::string("/minecraft/blockstates/") + path + ".json";
        }

        std::stringstream ss;
        std::ifstream file;

        bool error = path == "";
        picojson::value json;

        if (!error)
        {
            auto cached = cached_jsons.find(path);
            if (cached != cached_jsons.end())
            {
                json = cached->second;
            }
            else
            {
                file.open(full_filepath);
                if (!file.is_open())
                {
                    if (custom)
                    {
                        std::cout << "Missing custom definition for " << full_filepath << std::endl;
                    }
                    else
                    {
                        std::cerr << "Error reading blockstate file at " << full_filepath << std::endl;
                    }

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
                        else
                        {
                            cached_jsons[path] = json;
                        }
                    }
                }
            }
        }

        if (error)
        {
            models.push_back(Model::GetModel("", false));
            models_weights.push_back(1);
            weights_sum += 1;
            return;
        }

        const picojson::object& base_object = json.get<picojson::object>();

        // We store the models in a deque for efficiency
        std::deque<Model> models_deque;

        //If it's a "normal" blockstate
        auto it = base_object.find("variants");
        if (it != base_object.end())
        {
            const picojson::object& variants = it->second.get<picojson::object>();
            picojson::value null_value = picojson::value();
            picojson::value &variant_value = null_value;

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
                        const int weight = WeightFromJson(serialized);
                        models_deque.push_back(ModelModificationFromJson(Model::GetModel(model_name, custom), serialized));
                        models_weights.push_back(weight);
                        weights_sum += weight;
                    }
                }
                else
                {
                    const std::string serialized = variant_value.serialize();
                    const std::string model_name = ModelNameFromJson(serialized);
                    const int weight = WeightFromJson(serialized);
                    models_deque.push_back(ModelModificationFromJson(Model::GetModel(model_name, custom), serialized));
                    models_weights.push_back(weight);
                    weights_sum += weight;
                }
            }
            else
            {
                std::cerr << "Error reading " << full_filepath << std::endl;
                models_deque.push_back(Model::GetModel("", false));
                models_weights.push_back(1);
                weights_sum += 1;
            }
        }

        //If it's a multipart blockstate
        it = base_object.find("multipart");
        if (it != base_object.end())
        {
            //Start with an empty model
            models_deque.push_back(Model());
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
                        size_t num_models = models_deque.size();
                        const picojson::array &models_array = it3->second.get<picojson::array>();
                        for (int j = 0; j < models_array.size(); ++j)
                        {
                            const std::string serialized = models_array[j].serialize();
                            const std::string model_name = ModelNameFromJson(serialized);
                            for (int k = 0; k < num_models; ++k)
                            {
                                models_deque.push_back(models_deque[k] + ModelModificationFromJson(Model::GetModel(model_name, custom), serialized));
                                models_weights.push_back(models_weights[k] * WeightFromJson(serialized));
                            }
                        }
                        models_deque.erase(models_deque.begin(), models_deque.begin() + num_models);
                        models_weights.erase(models_weights.begin(), models_weights.begin() + num_models);
                    }
                    else
                    {
                        const std::string serialized = it3->second.serialize();
                        const std::string model_name = ModelNameFromJson(serialized);
                        for (int k = 0; k < models_deque.size(); ++k)
                        {
                            models_deque[k] += ModelModificationFromJson(Model::GetModel(model_name, custom), serialized);
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
                            size_t num_models = models_deque.size();
                            const picojson::array &models_array = it3->second.get<picojson::array>();
                            for (int j = 0; j < models_array.size(); ++j)
                            {
                                const std::string serialized = models_array[j].serialize();
                                const std::string model_name = ModelNameFromJson(serialized);
                                for (int k = 0; k < num_models; ++k)
                                {
                                    Model new_model = models_deque[k] + ModelModificationFromJson(Model::GetModel(model_name, custom), serialized);
                                    models_deque.push_back(new_model);
                                    models_weights.push_back(models_weights[k] * WeightFromJson(serialized));
                                }
                            }
                            models_deque.erase(models_deque.begin(), models_deque.begin() + num_models);
                            models_weights.erase(models_weights.begin(), models_weights.begin() + num_models);
                        }
                        else
                        {
                            const std::string serialized = it3->second.serialize();
                            const std::string model_name = ModelNameFromJson(serialized);
                            for (int k = 0; k < models_deque.size(); ++k)
                            {
                                models_deque[k] += ModelModificationFromJson(Model::GetModel(model_name, custom), serialized);
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
        models = std::vector<Model>(std::make_move_iterator(models_deque.begin()), std::make_move_iterator(models_deque.end()));
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

    void Blockstate::ClearCache()
    {
        cached_jsons.clear();
    }

    const int Blockstate::GetNumModels() const
    {
        return models.size();
    }
} //Botcraft