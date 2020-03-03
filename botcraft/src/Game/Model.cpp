#include "botcraft/Game/Model.hpp"

#include <picojson/picojson.h>

#include <sstream>
#include <fstream>

namespace Botcraft
{
    std::unordered_map<std::string, Model> Model::cached_models;

    Model::Model()
    {
        ambient_occlusion = false;
    }

    const Model& Model::GetModel(const std::string& filepath)
    {
        auto cached = cached_models.find(filepath);
        if (cached != cached_models.end())
        {
            return cached->second;
        }
        cached_models[filepath] = Model(filepath);
        return cached_models[filepath];
    }

    const Model Model::GetModel(const unsigned char height, const std::string& texture)
    {
        return Model(height, texture);
    }

    Model::Model(const std::string &filepath)
    {
        std::string full_filepath = ASSETS_PATH + std::string("/minecraft/models/") + filepath + ".json";

        std::stringstream ss;
        std::ifstream file;

        bool error = filepath == "";
        picojson::value json;

        if (!error)
        {
            file.open(full_filepath);
            if (!file.is_open())
            {
                std::cerr << "Error reading model file at " << full_filepath << std::endl;
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
                    std::cerr << "Error parsing model file at " << full_filepath << "\n";
                    std::cerr << err << std::endl;
                    error = true;
                }
                if (!error)
                {

                    if (!json.is<picojson::object>())
                    {
                        std::cerr << "Error parsing model file at " << full_filepath << std::endl;
                        error = true;
                    }
                }
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

        const picojson::value::object &obj = json.get<picojson::object>();

        auto it = obj.find("parent");
        if (it != obj.end())
        {
            const Model& parent_model = GetModel(it->second.get<std::string>());
            colliders = parent_model.colliders;
#if USE_GUI
            textures_variables = parent_model.textures_variables;
            faces = parent_model.faces;
            ambient_occlusion = parent_model.ambient_occlusion;
#endif
        }

        it = obj.find("ambientocclusion");
        if (it != obj.end())
        {
            ambient_occlusion = it->second.get<bool>();
        }

        it = obj.find("display");
        if (it != obj.end())
        {
            //TODO do something with display information?
        }

#if USE_GUI
        it = obj.find("textures");
        if (it != obj.end())
        {
            const picojson::value::object &obj_tex = it->second.get<picojson::object>();
            for (picojson::value::object::const_iterator j = obj_tex.begin(); j != obj_tex.end(); ++j)
            {
                textures_variables["#" + j->first] = j->second.get<std::string>();
                if (j->second.get<std::string>().rfind("#", 0) == 0)
                {
                    textures_variables[j->second.get<std::string>()] = j->second.get<std::string>();
                }
            }
        }
#endif

        it = obj.find("elements");
        if (it != obj.end())
        {
#if USE_GUI
            //Override any elements from the parent
            faces.clear();
#endif

            const picojson::array &elements_array = it->second.get<picojson::array>();
            for (int j = 0; j < elements_array.size(); ++j)
            {
#if USE_GUI
                std::vector<FaceDescriptor> current_element;
                Renderer::FaceTransformation element_global_transformations;
#endif
                int start_x, start_y, start_z;
                int end_x, end_y, end_z;

                const picojson::value::object &current_element_items = elements_array[j].get<picojson::object>();

                auto it2 = current_element_items.find("from");
                if (it2 != current_element_items.end())
                {
                    picojson::array values = it2->second.get<picojson::array>();
                    start_x = (int)values[0].get<double>();
                    start_y = (int)values[1].get<double>();
                    start_z = (int)values[2].get<double>();
                }

                it2 = current_element_items.find("to");
                if (it2 != current_element_items.end())
                {
                    picojson::array values = it2->second.get<picojson::array>();
                    end_x = (int)values[0].get<double>();
                    end_y = (int)values[1].get<double>();
                    end_z = (int)values[2].get<double>();
                }

                colliders.push_back(AABB(Vector3<double>(start_x + end_x, start_y + end_y, start_z + end_z) / 2.0 / 16.0, Vector3<double>(std::abs(end_x - start_x), std::abs(end_y - start_y), std::abs(end_z - start_z)) / 2.0 / 16.0));
                
                it2 = current_element_items.find("rotation");
                if (it2 != current_element_items.end())
                {
                    const picojson::value::object &rotation = it2->second.get<picojson::object>();

                    float origin_x, origin_y, origin_z;
                    const picojson::array &origin = rotation.find("origin")->second.get<picojson::array>();
                    origin_x = (float)origin[0].get<double>();
                    origin_y = (float)origin[1].get<double>();
                    origin_z = (float)origin[2].get<double>();

                    const std::string axis = rotation.find("axis")->second.get<std::string>();

                    const float angle = (float)rotation.find("angle")->second.get<double>();

#if USE_GUI
                    //Add the rotation to global transformations
                    element_global_transformations.rotations.push_back(Renderer::TransformationPtr(new Renderer::Translation(-((start_x + end_x) / 2.0 - origin_x) / 16.0f, -((start_y + end_y) / 2.0 - origin_y) / 16.0f, -((start_z + end_z) / 2.0 - origin_z) / 16.0f)));
                    if (axis == "x")
                    {
                        element_global_transformations.rotations.push_back(Renderer::TransformationPtr(new Renderer::Rotation(1.0f, 0.0f, 0.0f, angle)));
                    }
                    else if (axis == "y")
                    {
                        element_global_transformations.rotations.push_back(Renderer::TransformationPtr(new Renderer::Rotation(0.0f, 1.0f, 0.0f, angle)));
                    }
                    else if (axis == "z")
                    {
                        element_global_transformations.rotations.push_back(Renderer::TransformationPtr(new Renderer::Rotation(0.0f, 0.0f, 1.0f, angle)));
                    }
                    element_global_transformations.rotations.push_back(Renderer::TransformationPtr(new Renderer::Translation(((start_x + end_x) / 2.0 - origin_x) / 16.0f, ((start_y + end_y) / 2.0 - origin_y) / 16.0f, ((start_z + end_z) / 2.0 - origin_z) / 16.0f)));
#endif

                    bool rescale = false;
                    if (rotation.find("rescale") != rotation.end())
                    {
                        rescale = rotation.find("rescale")->second.get<bool>();
                    }
#if USE_GUI
                    if (rescale)
                    {
                        float scale_factor = abs(1.0f / (cos(angle * 3.14159f / 180.0f)));
                        if (axis == "x")
                        {
                            element_global_transformations.scales.push_back(Renderer::ScalePtr(new Renderer::Scale(1.0f, scale_factor, scale_factor)));
                        }
                        else if (axis == "y")
                        {
                            element_global_transformations.scales.push_back(Renderer::ScalePtr(new Renderer::Scale(scale_factor, 1.0f, scale_factor)));
                        }
                        else if (axis == "z")
                        {
                            element_global_transformations.scales.push_back(Renderer::ScalePtr(new Renderer::Scale(scale_factor, scale_factor, 1.0f)));
                        }
                    }
#endif
                }

                it2 = current_element_items.find("shade");
                if (it2 != current_element_items.end())
                {
                    //TODO do something with shade value
                }

#if USE_GUI
                it2 = current_element_items.find("faces");
                if (it2 != current_element_items.end())
                {
                    const picojson::value::object &faces = it2->second.get<picojson::object>();
                    for (picojson::value::object::const_iterator face = faces.begin(); face != faces.end(); ++face)
                    {
                        FaceDescriptor current_face;
                        if (face->first == "down")
                        {
                            current_face.orientation = Orientation::Bottom;
                        }
                        else if (face->first == "up")
                        {
                            current_face.orientation = Orientation::Top;
                        }
                        else if (face->first == "north")
                        {
                            current_face.orientation = Orientation::North;
                        }
                        else if (face->first == "south")
                        {
                            current_face.orientation = Orientation::South;
                        }
                        else if (face->first == "east")
                        {
                            current_face.orientation = Orientation::East;
                        }
                        else if (face->first == "west")
                        {
                            current_face.orientation = Orientation::West;
                        }

                        const picojson::value::object &face_params = face->second.get<picojson::object>();
                        auto it3 = face_params.find("uv");
                        if (it3 != face_params.end())
                        {
                            picojson::array values = it3->second.get<picojson::array>();
                            int x1 = (int)values[0].get<double>();
                            int y1 = (int)values[1].get<double>();
                            int x2 = (int)values[2].get<double>();
                            int y2 = (int)values[3].get<double>();

                            current_face.transformations.offset_x1 = x1;
                            current_face.transformations.offset_y1 = y1;
                            current_face.transformations.offset_x2 = x2;
                            current_face.transformations.offset_y2 = y2;
                        }
                        //If UV are not specified, we have to get them from [x,y,z] coordinates
                        else
                        {
                            switch (current_face.orientation)
                            {
                            case Orientation::Bottom:
                                current_face.transformations.offset_x1 = start_x;
                                current_face.transformations.offset_y1 = start_z;
                                current_face.transformations.offset_x2 = end_x;
                                current_face.transformations.offset_y2 = end_z;
                                break;
                            case Orientation::Top:
                                current_face.transformations.offset_x1 = start_x;
                                current_face.transformations.offset_y1 = start_z;
                                current_face.transformations.offset_x2 = end_x;
                                current_face.transformations.offset_y2 = end_z;
                                break;
                            case Orientation::East:
                                current_face.transformations.offset_x1 = start_z;
                                current_face.transformations.offset_y1 = 16 - end_y;
                                current_face.transformations.offset_x2 = end_z;
                                current_face.transformations.offset_y2 = 16 - start_y;
                                break;
                            case Orientation::West:
                                current_face.transformations.offset_x1 = start_z;
                                current_face.transformations.offset_y1 = 16 - end_y;
                                current_face.transformations.offset_x2 = end_z;
                                current_face.transformations.offset_y2 = 16 - start_y;
                                break;
                            case Orientation::South:
                                current_face.transformations.offset_x1 = start_x;
                                current_face.transformations.offset_y1 = 16 - end_y;
                                current_face.transformations.offset_x2 = end_x;
                                current_face.transformations.offset_y2 = 16 - start_y;
                                break;
                            case Orientation::North:
                                current_face.transformations.offset_x1 = start_x;
                                current_face.transformations.offset_y1 = 16 - end_y;
                                current_face.transformations.offset_x2 = end_x;
                                current_face.transformations.offset_y2 = 16 - start_y;
                                break;
                            default:
                                break;
                            }
                        }

                        it3 = face_params.find("texture");
                        if (it3 != face_params.end())
                        {
                            std::string texture_name = it3->second.get<std::string>();
                            current_face.texture_names[0] = texture_name;
                            if (textures_variables.find(texture_name) == textures_variables.end())
                            {
                                textures_variables[texture_name] = texture_name;
                            }
                        }

                        it3 = face_params.find("cullface");
                        if (it3 != face_params.end())
                        {
                            std::string value = it3->second.get<std::string>();
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

                        it3 = face_params.find("rotation");
                        if (it3 != face_params.end())
                        {
                            int rotation_value = (int)it3->second.get<double>();
                            current_face.transformations.rotation = rotation_value / 90;
                        }

                        it3 = face_params.find("tintindex");
                        if (it3 != face_params.end())
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
#endif

                //Add the scaling and translation of this element (based on from to)
                float center_x = (end_x + start_x) / 2.0f;
                float center_y = (end_y + start_y) / 2.0f;
                float center_z = (end_z + start_z) / 2.0f;

#if USE_GUI
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
            for (int i = faces.size() - 1; i > -1; --i)
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

            faces[i].transformations.scales.push_back(Renderer::ScalePtr(new Renderer::Scale(0.5f, (height + 1.0) / 32.0f, 0.5f)));
            faces[i].transformations.translations.push_back(Renderer::TransformationPtr(new Renderer::Translation(0.0f, ((height + 1) / 2.0f - 8) / 16.0f, 0.0f)));

            faces[i].transformations.rotation = 0;

            switch (faces[i].orientation)
            {
            case Orientation::Bottom:
                faces[i].transformations.offset_x1 = 0;
                faces[i].transformations.offset_y1 = 0;
                faces[i].transformations.offset_x2 = 16;
                faces[i].transformations.offset_y2 = 16;
                break;
            case Orientation::Top:
                faces[i].transformations.offset_x1 = 0;
                faces[i].transformations.offset_y1 = 0;
                faces[i].transformations.offset_x2 = 16;
                faces[i].transformations.offset_y2 = 16;
                break;
            case Orientation::East:
                faces[i].transformations.offset_x1 = 0;
                faces[i].transformations.offset_y1 = 16 - height - 1;
                faces[i].transformations.offset_x2 = 16;
                faces[i].transformations.offset_y2 = 16;
                break;
            case Orientation::West:
                faces[i].transformations.offset_x1 = 0;
                faces[i].transformations.offset_y1 = 16 - height - 1;
                faces[i].transformations.offset_x2 = 16;
                faces[i].transformations.offset_y2 = 16;
                break;
            case Orientation::South:
                faces[i].transformations.offset_x1 = 0;
                faces[i].transformations.offset_y1 = 16 - height - 1;
                faces[i].transformations.offset_x2 = 16;
                faces[i].transformations.offset_y2 = 16;
                break;
            case Orientation::North:
                faces[i].transformations.offset_x1 = 0;
                faces[i].transformations.offset_y1 = 16 - height - 1;
                faces[i].transformations.offset_x2 = 16;
                faces[i].transformations.offset_y2 = 16;
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