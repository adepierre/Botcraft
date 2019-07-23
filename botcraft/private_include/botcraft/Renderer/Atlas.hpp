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

        class Atlas
        {
        public:
            Atlas();
            ~Atlas();

            void Reset(const int texture_height_, const int texture_width_, const int height_, const int width_);

            // Load data 
            void LoadData(const std::vector<std::pair<std::string, std::string> > &textures_path);

            const int GetWidth() const;
            const int GetHeight() const;
            const int GetTextureWidth() const;
            const int GetTextureHeight() const;
            // Col / Row
            const std::pair<int, int>& GetPosition(const std::string &name) const;

            const Transparency GetTransparency(const std::pair<int, int> &pos) const;

            unsigned char* Get(const int y = 0, const int x = 0, const int row = 0, const int col = 0, const int depth = 0);

        private:

            std::vector<unsigned char> data;
            // Col/Row
            std::vector<std::vector<Transparency> > transparency_map;
            // Col/Row
            std::map<std::string, std::pair<int, int> > positions;

            int texture_height;
            int texture_width;
            int height;
            int width;
        };
    } // Renderer
} // Botcraft