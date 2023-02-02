#include "botcraft/Game/Model.hpp"
#include "botcraft/Utilities/StringUtilities.hpp"
#include "botcraft/Utilities/Logger.hpp"

#include "protocolCraft/Utilities/Json.hpp"

#include <sstream>
#include <fstream>

using namespace ProtocolCraft;

namespace Botcraft
{
    std::unordered_map<std::string, Model> Model::cached_models;

    Model::Model()
    {
        ambient_occlusion = false;
    }

    const Model& Model::GetModel(const std::string& filepath, const bool custom)
    {
        auto cached = cached_models.find(filepath);
        if (cached != cached_models.end())
        {
            return cached->second;
        }
        cached_models[filepath] = Model(filepath, custom);
        return cached_models[filepath];
    }

    const Model Model::GetModel(const unsigned char height, const std::string& texture)
    {
        return Model(height, texture);
    }

    Model::Model(const std::string &filepath, const bool custom)
    {
        std::string full_filepath;
        
        if (custom)
        {
            full_filepath = ASSETS_PATH + std::string("/custom/models/") + filepath + ".json";
        }
        else
        {
            full_filepath = ASSETS_PATH + std::string("/minecraft/models/") + filepath + ".json";
        }

        bool error = filepath == "";
        Json::Value obj;
        
        if (!error)
        {
            try
            {
                std::ifstream file(full_filepath);
                file >> obj;
                file.close();
            }
            catch (const std::runtime_error& e)
            {
                LOG_ERROR("Error reading model file  " << full_filepath << '\n' << e.what());
                error = true;
            }
        }

        //Create default model (Full solid cube)
        if (error)
        {
            ambient_occlusion = false;
            colliders.push_back(AABB(Vector3<double>(0.5, 0.5, 0.5), Vector3<double>(0.5, 0.5, 0.5)));
#ifdef USE_GUI
            faces = std::vector<FaceDescriptor>();
            for (int i = 0; i < 6; ++i)
            {
                FaceDescriptor current_face;
                current_face.cullface_direction = (Orientation)i;
                current_face.orientation = (Orientation)i;
                current_face.transformations.scales.push_back(Renderer::ScalePtr(new Renderer::Scale(0.5f, 0.5f, 0.5f)));
                current_face.face = Renderer::Face(current_face.transformations, current_face.orientation);
                faces.push_back(current_face);
            }
#endif
            return;
        }

        //Default values
        ambient_occlusion = true;

        if (obj.contains("parent"))
        {
#if PROTOCOL_VERSION > 578 // > 1.15.2
            // Remove the minecraft: in front of the parent model name
            std::string model_name = obj["parent"].get_string();
            if (StartsWith(model_name, "minecraft:"))
            {
                model_name = model_name.substr(10);
            }
            const Model& parent_model = GetModel(model_name, custom);
#else
            const Model& parent_model = GetModel(obj["parent"].get_string(), custom);
#endif
            colliders = parent_model.colliders;
#if USE_GUI
            textures_variables = parent_model.textures_variables;
            textures_base_size = parent_model.textures_base_size;
            faces = parent_model.faces;
            ambient_occlusion = parent_model.ambient_occlusion;
#endif
        }

        if (obj.contains("ambientocclusion"))
        {
            ambient_occlusion = obj["ambientocclusion"].get<bool>();
        }

        if (obj.contains("display"))
        {
            //TODO do something with display information?
        }

#if USE_GUI
        if (obj.contains("textures_base_size"))
        {
            for (const auto& [key, val] : obj["textures_base_size"].get_object())
            {
                textures_base_size[key] = std::pair<int, int>(val[0].get_number<int>(), val[1].get_number<int>());
            }
        }

        if (obj.contains("textures"))
        {
            for (const auto& [key, val] : obj["textures"].get_object())
            {
#if PROTOCOL_VERSION > 578 // > 1.15.2
                // Remove leading minecraft: from the path of the textures
                std::string texture_name = val.get_string();
                if (StartsWith(texture_name, "minecraft:"))
                {
                     texture_name = texture_name.substr(10);
                }
#else
                const std::string& texture_name = val.get_string();
#endif
                textures_variables["#" + key] = texture_name;
                if (val.get_string().rfind("#", 0) == 0)
                {
                    textures_variables[val.get_string()] = val.get_string();
                }
            }
        }
#endif

        if (obj.contains("elements"))
        {
#if USE_GUI
            //Override any elements from the parent
            faces.clear();
#endif

            for (const auto& element : obj["elements"].get_array())
            {
#if USE_GUI
                std::vector<FaceDescriptor> current_element;
                Renderer::FaceTransformation element_global_transformations;
#endif
                int start_x, start_y, start_z;
                int end_x, end_y, end_z;

                if (element.contains("from"))
                {
                    start_x = element["from"][0].get_number<int>();
                    start_y = element["from"][1].get_number<int>();
                    start_z = element["from"][2].get_number<int>();
                }

                if (element.contains("to"))
                {
                    end_x = element["to"][0].get_number<int>();
                    end_y = element["to"][1].get_number<int>();
                    end_z = element["to"][2].get_number<int>();
                }

                colliders.push_back(AABB(Vector3<double>(start_x + end_x, start_y + end_y, start_z + end_z) / 2.0 / 16.0, Vector3<double>(std::abs(end_x - start_x), std::abs(end_y - start_y), std::abs(end_z - start_z)) / 2.0 / 16.0));

#if USE_GUI
                if (element.contains("rotation"))
                {
                    float origin_x, origin_y, origin_z;
                    origin_x = element["rotation"]["origin"][0].get_number<float>();
                    origin_y = element["rotation"]["origin"][1].get_number<float>();
                    origin_z = element["rotation"]["origin"][2].get_number<float>();

                    //Add the rotation to global transformations

                    const float angle = element["rotation"]["angle"].get_number<float>();
                    element_global_transformations.rotations.push_back(Renderer::TransformationPtr(new Renderer::Translation(-((start_x + end_x) / 2.0f - origin_x) / 16.0f, -((start_y + end_y) / 2.0f - origin_y) / 16.0f, -((start_z + end_z) / 2.0f - origin_z) / 16.0f)));
                    if (element["rotation"]["axis"].get_string() == "x")
                    {
                        element_global_transformations.rotations.push_back(Renderer::TransformationPtr(new Renderer::Rotation(1.0f, 0.0f, 0.0f, angle)));
                    }
                    else if (element["rotation"]["axis"].get_string() == "y")
                    {
                        element_global_transformations.rotations.push_back(Renderer::TransformationPtr(new Renderer::Rotation(0.0f, 1.0f, 0.0f, angle)));
                    }
                    else if (element["rotation"]["axis"].get_string() == "z")
                    {
                        element_global_transformations.rotations.push_back(Renderer::TransformationPtr(new Renderer::Rotation(0.0f, 0.0f, 1.0f, angle)));
                    }
                    element_global_transformations.rotations.push_back(Renderer::TransformationPtr(new Renderer::Translation(((start_x + end_x) / 2.0f - origin_x) / 16.0f, ((start_y + end_y) / 2.0f - origin_y) / 16.0f, ((start_z + end_z) / 2.0f - origin_z) / 16.0f)));

                    bool rescale = false;
                    if (element["rotation"].contains("rescale"))
                    {
                        rescale = element["rotation"]["rescale"].get<bool>();
                    }

                    if (rescale)
                    {
                        float scale_factor = std::abs(1.0f / (std::cos(angle * 3.14159f / 180.0f)));
                        if (element["rotation"]["axis"].get_string() == "x")
                        {
                            element_global_transformations.scales.push_back(Renderer::ScalePtr(new Renderer::Scale(1.0f, scale_factor, scale_factor)));
                        }
                        else if (element["rotation"]["axis"].get_string() == "y")
                        {
                            element_global_transformations.scales.push_back(Renderer::ScalePtr(new Renderer::Scale(scale_factor, 1.0f, scale_factor)));
                        }
                        else if (element["rotation"]["axis"].get_string() == "z")
                        {
                            element_global_transformations.scales.push_back(Renderer::ScalePtr(new Renderer::Scale(scale_factor, scale_factor, 1.0f)));
                        }
                    }
                }

                if (element.contains("shade"))
                {
                    //TODO do something with shade value
                }

                if (element.contains("faces"))
                {
                    for (const auto& [key, face_params] : element["faces"].get_object())
                    {
                        FaceDescriptor current_face;
                        if (key == "down")
                        {
                            current_face.orientation = Orientation::Bottom;
                        }
                        else if (key == "up")
                        {
                            current_face.orientation = Orientation::Top;
                        }
                        else if (key == "north")
                        {
                            current_face.orientation = Orientation::North;
                        }
                        else if (key == "south")
                        {
                            current_face.orientation = Orientation::South;
                        }
                        else if (key == "east")
                        {
                            current_face.orientation = Orientation::East;
                        }
                        else if (key == "west")
                        {
                            current_face.orientation = Orientation::West;
                        }
                                                
                        if (face_params.contains("uv"))
                        {
                            current_face.transformations.offset_x1 = face_params["uv"][0].get_number<float>();
                            current_face.transformations.offset_y1 = face_params["uv"][1].get_number<float>();
                            current_face.transformations.offset_x2 = face_params["uv"][2].get_number<float>();
                            current_face.transformations.offset_y2 = face_params["uv"][3].get_number<float>();
                        }
                        //If UV are not specified, we have to get them from [x,y,z] coordinates
                        else
                        {
                            switch (current_face.orientation)
                            {
                            case Orientation::Bottom:
                                current_face.transformations.offset_x1 = static_cast<float>(start_x);
                                current_face.transformations.offset_y1 = static_cast<float>(start_z);
                                current_face.transformations.offset_x2 = static_cast<float>(end_x);
                                current_face.transformations.offset_y2 = static_cast<float>(end_z);
                                break;
                            case Orientation::Top:
                                current_face.transformations.offset_x1 = static_cast<float>(start_x);
                                current_face.transformations.offset_y1 = static_cast<float>(start_z);
                                current_face.transformations.offset_x2 = static_cast<float>(end_x);
                                current_face.transformations.offset_y2 = static_cast<float>(end_z);
                                break;
                            case Orientation::East:
                                current_face.transformations.offset_x1 = static_cast<float>(start_z);
                                current_face.transformations.offset_y1 = static_cast<float>(16 - end_y);
                                current_face.transformations.offset_x2 = static_cast<float>(end_z);
                                current_face.transformations.offset_y2 = static_cast<float>(16 - start_y);
                                break;
                            case Orientation::West:
                                current_face.transformations.offset_x1 = static_cast<float>(start_z);
                                current_face.transformations.offset_y1 = static_cast<float>(16 - end_y);
                                current_face.transformations.offset_x2 = static_cast<float>(end_z);
                                current_face.transformations.offset_y2 = static_cast<float>(16 - start_y);
                                break;
                            case Orientation::South:
                                current_face.transformations.offset_x1 = static_cast<float>(start_x);
                                current_face.transformations.offset_y1 = static_cast<float>(16 - end_y);
                                current_face.transformations.offset_x2 = static_cast<float>(end_x);
                                current_face.transformations.offset_y2 = static_cast<float>(16 - start_y);
                                break;
                            case Orientation::North:
                                current_face.transformations.offset_x1 = static_cast<float>(start_x);
                                current_face.transformations.offset_y1 = static_cast<float>(16 - end_y);
                                current_face.transformations.offset_x2 = static_cast<float>(end_x);
                                current_face.transformations.offset_y2 = static_cast<float>(16 - start_y);
                                break;
                            default:
                                break;
                            }
                        }

                        if (face_params.contains("texture"))
                        {
                            const std::string& texture_name = face_params["texture"].get_string();
                            current_face.texture_names[0] = texture_name;
                            if (textures_variables.find(texture_name) == textures_variables.end())
                            {
                                textures_variables[texture_name] = texture_name;
                            }
                        }

                        if (face_params.contains("cullface"))
                        {
                            const std::string& value = face_params["cullface"].get_string();
                            if (value == "down")
                            {
                                current_face.cullface_direction = Orientation::Bottom;
                            }
                            else if (value == "up")
                            {
                                current_face.cullface_direction = Orientation::Top;
                            }
                            else if (value == "north")
                            {
                                current_face.cullface_direction = Orientation::North;
                            }
                            else if (value == "south")
                            {
                                current_face.cullface_direction = Orientation::South;
                            }
                            else if (value == "west")
                            {
                                current_face.cullface_direction = Orientation::West;
                            }
                            else if (value == "east")
                            {
                                current_face.cullface_direction = Orientation::East;
                            }
                            else
                            {
                                current_face.cullface_direction = Orientation::None;
                            }
                        }
                        else
                        {
                            current_face.cullface_direction = Orientation::None;
                        }

                        if (face_params.contains("rotation"))
                        {
                            current_face.transformations.rotation = face_params["rotation"].get_number<int>() / 90;
                        }

                        if (face_params.contains("tintindex"))
                        {
                            current_face.use_tintindexes[0] = true;
                        }
                        else
                        {
                            current_face.use_tintindexes[0] = false;
                        }
                        current_face.face = Renderer::Face(current_face.transformations, current_face.orientation);
                        current_element.push_back(current_face);
                    }
                }

                //Add the scaling and translation of this element (based on from to)
                float center_x = (end_x + start_x) / 2.0f;
                float center_y = (end_y + start_y) / 2.0f;
                float center_z = (end_z + start_z) / 2.0f;

                if (center_x != 8.0f || center_y != 8.0f || center_z != 8.0f)
                {
                    element_global_transformations.translations.push_back(Renderer::TransformationPtr(new Renderer::Translation((center_x - 8) / 16.0f, (center_y - 8) / 16.0f, (center_z - 8) / 16.0f)));
                }

                //We divide by 32 because the base face size is 2 and a block size is 1
                element_global_transformations.scales.push_back(Renderer::ScalePtr(new Renderer::Scale((end_x - start_x) / 32.0f, (end_y - start_y) / 32.0f, (end_z - start_z) / 32.0f)));

                //Add the global transformations of this element to all the faces
                for (int m = 0; m < current_element.size(); ++m)
                {
                    for (int n = 0; n < element_global_transformations.scales.size(); ++n)
                    {
                        current_element[m].transformations.scales.push_back(element_global_transformations.scales[n]);
                    }
                    for (int n = 0; n < element_global_transformations.rotations.size(); ++n)
                    {
                        current_element[m].transformations.rotations.push_back(element_global_transformations.rotations[n]);
                    }
                    for (int n = 0; n < element_global_transformations.translations.size(); ++n)
                    {
                        current_element[m].transformations.translations.push_back(element_global_transformations.translations[n]);
                    }
                    current_element[m].face = Renderer::Face(current_element[m].transformations, current_element[m].orientation);
                }

                //Add the faces of the current element to the global faces
                faces.insert(faces.end(), current_element.begin(), current_element.end());
#endif
            }
        }

#if USE_GUI
        bool has_changed = true;
        while (has_changed)
        {
            has_changed = false;
            // Replace all the textures variables with their identifiers
            for (int i = static_cast<int>(faces.size()) - 1; i > -1; --i)
            {
                // Treat #overlay as special cases
                if (faces[i].texture_names[0].rfind("#overlay", 0) == 0)
                {
                    int matching_index = -1;
                    for (int j = 0; j < faces.size(); ++j)
                    {
                        if (i != j && faces[i].face == faces[j].face)
                        {
                            matching_index = j;
                            break;
                        }
                    }

                    // We found the same face
                    if (matching_index != -1)
                    {
                        faces[matching_index].texture_names.push_back(faces[i].texture_names[0]);
                        faces[matching_index].use_tintindexes.push_back(faces[i].use_tintindexes[0]);
                    }
                    faces.erase(faces.begin() + i);
                    has_changed = true;
                    continue;
                }
                for (int s = 0; s < faces[i].texture_names.size(); ++s)
                {
                    std::string variable_name = faces[i].texture_names[s];
                    while (variable_name.rfind("#", 0) == 0 && variable_name != textures_variables[variable_name])
                    {
                        variable_name = textures_variables[variable_name];
                        has_changed = true;
                    }
                    faces[i].texture_names[s] = variable_name;
                }
            }
        }

        // Once all the texture names have been replaced
        // by their identifiers, multiply uv by texture
        // sizes for special cases with non 64x64 default
        // sizes
        for (size_t i = 0; i < faces.size(); ++i)
        {
            if (faces[i].texture_names.size() == 0)
            {
                continue;
            }

            auto it = textures_base_size.find(faces[i].texture_names[0]);
            if (it != textures_base_size.end())
            {
                faces[i].transformations.offset_x1 *= 16.0f / it->second.first;
                faces[i].transformations.offset_y1 *= 16.0f / it->second.second;
                faces[i].transformations.offset_x2 *= 16.0f / it->second.first;
                faces[i].transformations.offset_y2 *= 16.0f / it->second.second;

                faces[i].face = Renderer::Face(faces[i].transformations, faces[i].orientation);
            }
        }
#endif
    }

    Model::Model(const unsigned char height, const std::string &texture)
    {
        ambient_occlusion = false;
        colliders = std::vector<AABB>({ AABB(Vector3<double>(0.5, (height + 1.0) / 2.0 / 16.0, 0.5), Vector3<double>(0.5, (height + 1.0) / 2.0 / 16.0, 0.5)) });

#ifdef USE_GUI
        faces = std::vector<FaceDescriptor>(6);
        for (int i = 0; i < 6; ++i)
        {
            faces[i].orientation = (Orientation)i;
            faces[i].texture_names = { texture };
            faces[i].cullface_direction = (Orientation)i;
            faces[i].use_tintindexes = { false };

            faces[i].transformations.scales.push_back(Renderer::ScalePtr(new Renderer::Scale(0.5f, (height + 1.0f) / 32.0f, 0.5f)));
            faces[i].transformations.translations.push_back(Renderer::TransformationPtr(new Renderer::Translation(0.0f, ((height + 1) / 2.0f - 8) / 16.0f, 0.0f)));

            faces[i].transformations.rotation = 0;

            switch (faces[i].orientation)
            {
            case Orientation::Bottom:
                faces[i].transformations.offset_x1 = 0.0f;
                faces[i].transformations.offset_y1 = 0.0f;
                faces[i].transformations.offset_x2 = 16.0f;
                faces[i].transformations.offset_y2 = 16.0f;
                break;
            case Orientation::Top:
                faces[i].transformations.offset_x1 = 0.0f;
                faces[i].transformations.offset_y1 = 0.0f;
                faces[i].transformations.offset_x2 = 16.0f;
                faces[i].transformations.offset_y2 = 16.0f;
                break;
            case Orientation::East:
                faces[i].transformations.offset_x1 = 0.0f;
                faces[i].transformations.offset_y1 = 16.0f - height - 1.0f;
                faces[i].transformations.offset_x2 = 16.0f;
                faces[i].transformations.offset_y2 = 16.0f;
                break;
            case Orientation::West:
                faces[i].transformations.offset_x1 = 0.0f;
                faces[i].transformations.offset_y1 = 16.0f - height - 1.0f;
                faces[i].transformations.offset_x2 = 16.0f;
                faces[i].transformations.offset_y2 = 16.0f;
                break;
            case Orientation::South:
                faces[i].transformations.offset_x1 = 0.0f;
                faces[i].transformations.offset_y1 = 16.0f - height - 1.0f;
                faces[i].transformations.offset_x2 = 16.0f;
                faces[i].transformations.offset_y2 = 16.0f;
                break;
            case Orientation::North:
                faces[i].transformations.offset_x1 = 0.0f;
                faces[i].transformations.offset_y1 = 16.0f - height - 1.0f;
                faces[i].transformations.offset_x2 = 16.0f;
                faces[i].transformations.offset_y2 = 16.0f;
                break;
            default:
                break;
            }
            faces[i].face = Renderer::Face(faces[i].transformations, faces[i].orientation);
        }
#endif
    }

    Model &Model::operator+=(const Model &m)
    {
        this->ambient_occlusion = this->ambient_occlusion || m.ambient_occlusion;
        this->colliders.insert(this->colliders.end(), m.colliders.begin(), m.colliders.end());
#ifdef USE_GUI
        this->faces.insert(this->faces.end(), m.faces.begin(), m.faces.end());
#endif
        return *this;
    }

    const std::vector<AABB> &Model::GetColliders() const
    {
        return colliders;
    }

    std::vector<AABB> &Model::GetColliders()
    {
        return colliders;
    }

    void Model::ClearCache()
    {
        cached_models.clear();
    }

#ifdef USE_GUI
    const std::vector<FaceDescriptor> &Model::GetFaces() const
    {
        return faces;
    }

    std::vector<FaceDescriptor> &Model::GetFaces()
    {
        return faces;
    }
#endif
} //Botcraft
