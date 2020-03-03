#pragma once

#include <string>
#include <tuple>
#include <map>
#include <unordered_map>
#include <vector>
#include <deque>

#include "botcraft/Game/AABB.hpp"
#if USE_GUI
#include "botcraft/Game/Enums.hpp"
#include "botcraft/Renderer/Transformation.hpp"
#include "botcraft/Renderer/Face.hpp"
#endif

namespace Botcraft 
{
#if USE_GUI
    struct FaceDescriptor
    {
        FaceDescriptor()
        {
            texture_names = { "" };
            use_tintindexes = { false };
        }
        Renderer::FaceTransformation transformations;
        Orientation orientation;
        Renderer::Face face;
        std::vector<std::string> texture_names;
        Orientation cullface_direction;
        std::vector<bool> use_tintindexes;
    };
#endif

    class Model
    {

    private:
        // Constructor from a minecraft json file
        Model(const std::string& filepath);
        // Fluid constructor
        Model(const unsigned char height, const std::string& texture);
    public:
        // Base constructor
        Model();
        static const Model& GetModel(const std::string& filepath);
        static const Model GetModel(const unsigned char height, const std::string& texture);

        Model &operator+=(const Model &m);

        friend Model operator+(Model m1, const Model &m2)
        {
            m1 += m2;
            return m1;
        }

        const std::vector<AABB> &GetColliders() const;
        std::vector<AABB> &GetColliders();

        static void ClearCache();

#if USE_GUI
        const std::vector<FaceDescriptor> &GetFaces() const;
        std::vector<FaceDescriptor> &GetFaces();
#endif
    private:
        static std::unordered_map<std::string, Model> cached_models;

        bool ambient_occlusion;

#if USE_GUI
        std::map<std::string, std::string> textures_variables;

        //All the faces of this model
        std::vector<FaceDescriptor> faces;
#endif
        std::vector<AABB> colliders;
    };
} // Botcraft