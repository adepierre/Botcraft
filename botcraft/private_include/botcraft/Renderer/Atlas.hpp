#include <string>
#include <vector>
#include <unordered_map>

#include "botcraft/Renderer/Enums.hpp"

namespace Botcraft
{
    namespace Renderer
    {
        struct TextureData
        {
            /// @brief <Width, Height>
            std::pair<int, int> size;
            /// @brief <Col, Row>
            std::pair<int, int> position;
            Transparency transparency;
            Animation animation;
        };

        class Atlas
        {
        public:
            Atlas();
            ~Atlas();

            void Reset(const int height_, const int width_);

            // Load data 
            void LoadData(const std::vector<std::pair<std::string, std::string> >& textures_path);

            int GetWidth() const;
            int GetHeight() const;

            const TextureData& GetData(const std::string& name) const;

            const unsigned char* Get(const int row = 0, const int col = 0, const int depth = 0) const;

        private:
            unsigned char* Get(const int row = 0, const int col = 0, const int depth = 0);

        private:

            std::vector<unsigned char> data;
            std::unordered_map<std::string, TextureData> textures_map;

            int height;
            int width;
        };
    } // Renderer
} // Botcraft