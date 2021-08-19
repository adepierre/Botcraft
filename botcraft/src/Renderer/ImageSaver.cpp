#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "botcraft/Renderer/ImageSaver.hpp"

namespace Botcraft
{
    namespace Renderer
    {
        void WriteImage(const std::string &path, const int height, const int width, const int depth, const unsigned char* data, const bool vertical_revert)
        {
            stbi_flip_vertically_on_write(vertical_revert);
            stbi_write_png(path.c_str(), width, height, depth, data, depth * width);
        }
    } // Renderer
} // Botcraft