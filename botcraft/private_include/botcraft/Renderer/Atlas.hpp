#include <string>
#include <vector>
#include <map>

namespace Botcraft
{
    namespace Renderer
    {
        // Transparency values for textures
        enum class Transparency
        {
            Opaque, // Alpha = 255
            Total,  // Alpha == 0
            Partial // 0 < Alpha < 255
        };

        enum class Animation
        {
            Static,
            Animated
        };

        class Atlas
        {
        public:
            Atlas();
            ~Atlas();

            void Reset(const int height_, const int width_);

            // Load data 
            void LoadData(const std::vector<std::pair<std::string, std::string> > &textures_path);

            const int GetWidth() const;
            const int GetHeight() const;
            // Col / Row
            const std::pair<int, int>& GetPosition(const std::string &name) const;
            const std::pair<int, int>& GetSize(const std::string& name) const;
            const Transparency GetTransparency(const std::string& name) const;
            const Animation GetAnimation(const std::string& name) const;

            unsigned char* Get(const int row = 0, const int col = 0, const int depth = 0);

        private:

            std::vector<unsigned char> data;
            std::map<std::string, Transparency> transparency_map;
            std::map<std::string, Animation> animation_map;

            // col/row
            std::map<std::string, std::pair<int, int>> textures_size_map;
            // col/row
            std::map<std::string, std::pair<int, int>> textures_position_map;
            int height;
            int width;
        };
    } // Renderer
} // Botcraft