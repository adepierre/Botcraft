#pragma once

#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "botcraft/Game/Physics/AABB.hpp"

#if USE_GUI
#include <map>

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
        // Constructor from a json file
        Model(const std::string& filepath, const bool custom);
        // Fluid constructor
        Model(const double height, const std::string& texture);
    public:
        // Base constructor
        Model();
        static const Model& GetModel(const std::string& filepath, const bool custom);
        static Model GetModel(const double height, const std::string& texture);

        Model& operator+=(const Model& m);

        friend Model operator+(Model m1, const Model& m2)
        {
            m1 += m2;
            return m1;
        }

        /// @brief Compare two models. Will never return true if compiled with GUI
        /// @param other Model to compare to
        /// @return True if both models are the same, false otherwise
        bool IsSame(const Model& other) const;

        const std::set<AABB>& GetColliders() const;
        void SetColliders(const std::set<AABB>& colliders_);

        static void ClearCache();

#if USE_GUI
        const std::vector<FaceDescriptor>& GetFaces() const;
        std::vector<FaceDescriptor>& GetFaces();
#endif
    private:
        static std::unordered_map<std::string, Model> cached_models;

#if USE_GUI
        bool ambient_occlusion;
        std::map<std::string, std::string> textures_variables;
        std::map<std::string, std::pair<int, int> > textures_base_size;

        //All the faces of this model
        std::vector<FaceDescriptor> faces;
#endif
        std::set<AABB> colliders;
    };
} // Botcraft
