#include "botcraft/Renderer/Atlas.hpp"
#include "botcraft/Renderer/ImageSaver.hpp"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include <stb_image/stb_image.h>

// rectpack2D
#include "finders_interface.h"

#include <iostream>
#include <fstream>
#include <string>

namespace Botcraft
{
    namespace Renderer
    {
        // A basic struct to hold a named image data
        struct Texture
        {
            int width;
            int height;
            int depth;
            std::string identifier;
            bool animated;
            std::vector<unsigned char> data;

            const unsigned char Get(const int x, const int y, const int c) const
            {
                return data[(y * width + x) * depth + c];
            }
        };

        Atlas::Atlas()
        {

        }

        Atlas::~Atlas()
        {

        }

        void Atlas::Reset(const int height_, const int width_)
        {
            height = height_;
            width = width_;
            data = std::vector<unsigned char>(height * width * 4, 0);
            transparency_map.clear();
            animation_map.clear();
            textures_size_map.clear();
            textures_position_map.clear();

            //Fill with "undefined" texture
            for (int row = 0; row < height; ++row)
            {
                for (int col = 0; col < width; ++col)
                {
                    unsigned char* pixel_pointer = Get(row, col);

                    bool is_magenta = !((row % 16 < 8 && col % 16 < 8) || (row % 16 >= 8 && col % 16 >= 8));

                    *(pixel_pointer + 0) = is_magenta ? 255 : 0;
                    *(pixel_pointer + 1) = 0;
                    *(pixel_pointer + 2) = is_magenta ? 255 : 0;
                    *(pixel_pointer + 3) = 255;
                }
            }
        }

        void Atlas::LoadData(const std::vector<std::pair<std::string, std::string> >& textures_path_names)
        {
            if (textures_path_names.size() == 0)
            {
                Reset(16, 16);
                return;
            }

            std::vector<Texture> textures;
            textures.reserve(textures_path_names.size());

            for (int i = 0; i < textures_path_names.size(); ++i)
            {
                if (textures_path_names[i].first.empty())
                {
                    continue;
                }
                Texture tex;
                unsigned char* data = stbi_load(textures_path_names[i].first.c_str(), &tex.width, &tex.height, &tex.depth, 0);
                if (data != nullptr)
                {
                    tex.data = std::vector<unsigned char>(data, data + tex.width * tex.height * tex.depth);
                    tex.identifier = textures_path_names[i].second;
                    std::ifstream animation_file((textures_path_names[i].first + ".mcmeta").c_str());
                    tex.animated = animation_file.good();

                    textures.push_back(tex);
                }
                stbi_image_free(data);
            }


            // Copy the textures with correct size (crop if it's an animated texture)
            std::vector<Texture> kept_textures;
            kept_textures.reserve(textures.size());
            for (int i = 0; i < textures.size(); ++i)
            {
                // If the depth is not good, don't keep the texture
                if (textures[i].depth < 1 || textures[i].depth > 4)
                {
                    std::cout << "Warning, unknown depth format (" << textures[i].depth << ") for texture " << textures[i].identifier << std::endl;
                    continue;
                }
                kept_textures.push_back(textures[i]);
            }

            //Compute atlas dimensions using rectpack2D
            using spaces_type = rectpack2D::empty_spaces<false>;
            using rect_type = rectpack2D::output_rect_t<spaces_type>;

            std::vector<rect_type> rectangles;
            rectangles.emplace_back(rectpack2D::rect_xywh(0, 0, 16, 16));
            for (int i = 0; i < kept_textures.size(); ++i)
            {
                rectangles.emplace_back(rectpack2D::rect_xywh(0, 0, kept_textures[i].width, kept_textures[i].height));
            }

            const auto result_size = rectpack2D::find_best_packing<spaces_type>(
                rectangles,
                make_finder_input(
                    10000,
                    1,
                    [](rect_type&) {
                        return rectpack2D::callback_result::CONTINUE_PACKING;
                    },
                    [](rect_type&) {
                        std::cerr << "Error packing the textures, aborting" << std::endl;
                        return rectpack2D::callback_result::ABORT_PACKING;
                    },
                    rectpack2D::flipping_option::DISABLED
                )
                );

            std::cout << "All textures packed, resultant atlas size: " << result_size.h << "x" << result_size.w << std::endl;
            
            //Compute the global texture image
            Reset(result_size.h, result_size.w);

            //Set the default texture
            transparency_map[""] = Transparency::Opaque;
            animation_map[""] = Animation::Static;
            textures_size_map[""] = { rectangles[0].w, rectangles[0].h };
            textures_position_map[""] = { rectangles[0].x, rectangles[0].y };

            for (int i = 0; i < kept_textures.size(); ++i)
            {
                const rect_type& rectangle = rectangles[i + 1];
                
                transparency_map[kept_textures[i].identifier] = Transparency::Opaque;
                animation_map[kept_textures[i].identifier] = (kept_textures[i].animated ? Animation::Animated : Animation::Static);
                textures_size_map[kept_textures[i].identifier] = { rectangle.w, rectangle.h };
                textures_position_map[kept_textures[i].identifier] = { rectangle.x, rectangle.y };

                for (int row = 0; row < rectangle.h; ++row)
                {
                    for (int col = 0; col < rectangle.w; ++col)
                    {
                        int r = 0;
                        int g = 0;
                        int b = 0;
                        int a = 0;

                        switch (kept_textures[i].depth)
                        {
                        case 1: //Grayscale image
                            r = kept_textures[i].Get(col, row, 0);
                            g = kept_textures[i].Get(col, row, 0);
                            b = kept_textures[i].Get(col, row, 0);
                            a = 255;
                            break;
                        case 2: //Grayscale + Alpha image
                            r = kept_textures[i].Get(col, row, 0);
                            g = kept_textures[i].Get(col, row, 0);
                            b = kept_textures[i].Get(col, row, 0);
                            a = kept_textures[i].Get(col, row, 1);
                            break;
                        case 3: //RGB image
                            r = kept_textures[i].Get(col, row, 0);
                            g = kept_textures[i].Get(col, row, 1);
                            b = kept_textures[i].Get(col, row, 2);
                            a = 255;
                            break;
                        case 4: //RGBA image
                            r = kept_textures[i].Get(col, row, 0);
                            g = kept_textures[i].Get(col, row, 1);
                            b = kept_textures[i].Get(col, row, 2);
                            a = kept_textures[i].Get(col, row, 3);
                            break;
                        }

                        *(Get(rectangle.y + row, rectangle.x + col, 0)) = r;
                        *(Get(rectangle.y + row, rectangle.x + col, 1)) = g;
                        *(Get(rectangle.y + row, rectangle.x + col, 2)) = b;
                        *(Get(rectangle.y + row, rectangle.x + col, 3)) = a;

                         
                        if (a == 0 && transparency_map[kept_textures[i].identifier] != Transparency::Partial)
                        {
                            transparency_map[kept_textures[i].identifier] = Transparency::Total;
                        }
                        else if (a < 255)
                        {
                            transparency_map[kept_textures[i].identifier] = Transparency::Partial;
                        }
                    }
                }
            }

            //In case we want to save the atlas to check the data
            //WriteImage("atlas.png", height, width, 4, data.data(), false);
        }

        const int Atlas::GetWidth() const
        {
            return width;
        }

        const int Atlas::GetHeight() const
        {
            return height;
        }

        const std::pair<int, int>& Atlas::GetSize(const std::string& name) const
        {
            auto it =textures_size_map.find(name);
            if (it != textures_size_map.end())
            {
                return it->second;
            }

            return textures_size_map.at("");
        }

        const std::pair<int, int>& Atlas::GetPosition(const std::string& name) const
        {
            auto it = textures_position_map.find(name);
            if (it != textures_position_map.end())
            {
                return it->second;
            }

            return textures_position_map.at("");
        }

        const Transparency Atlas::GetTransparency(const std::string& name) const
        {
            auto it = transparency_map.find(name);
            if (it != transparency_map.end())
            {
                return it->second;
            }

            return transparency_map.at("");
        }

        const Animation Atlas::GetAnimation(const std::string& name) const
        {
            auto it = animation_map.find(name);
            if (it != animation_map.end())
            {
                return it->second;
            }

            return animation_map.at("");
        }

        unsigned char* Atlas::Get(const int row, const int col, const int depth)
        {
            return data.data() + ((row * width + col) * 4 + depth);
        }
    } // Renderer
} // Botcraft