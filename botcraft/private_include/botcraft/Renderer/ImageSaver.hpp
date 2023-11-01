#include <string>

namespace Botcraft
{
    namespace Renderer
    {
        void WriteImage(const std::string& path, const int height, const int width, const int depth, const unsigned char* data, const bool vertical_revert = true);
    } // Renderer
} // Botcraft
