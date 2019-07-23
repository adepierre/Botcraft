#include "botcraft/Renderer/Atlas.hpp"
#include "botcraft/Renderer/ImageSaver.hpp"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include <stb_image/stb_image.h>

#include <iostream>

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

        void Atlas::Reset(const int texture_height_, const int texture_width_, const int height_, const int width_)
        {
            texture_height = texture_height_;
            texture_width = texture_width_;
            height = height_;
            width = width_;
            data = std::vector<unsigned char>(texture_height * height * texture_width * width * 4, 0);
            transparency_map = std::vector<std::vector<Transparency> >(width, std::vector<Transparency>(height, Transparency::Opaque));
            positions.clear();
            positions[""] = { 0, 0 };

            //Fill with "undefined" texture
            for (int atlas_row = 0; atlas_row < height; ++atlas_row)
            {
                for (int atlas_col = 0; atlas_col < width; ++atlas_col)
                {
                    for (int row = 0; row < texture_height; ++row)
                    {
                        for (int col = 0; col < texture_width; ++col)
                        {
                            unsigned char* pixel_pointer = Get(atlas_row, atlas_col, row, col);

                            bool is_magenta = !((row < texture_height / 2 && col < texture_width / 2) || (row >= texture_height / 2 && col >= texture_width / 2));

                            *(pixel_pointer + 0) = is_magenta ? 255 : 0;
                            *(pixel_pointer + 1) = 0;
                            *(pixel_pointer + 2) = is_magenta ? 255 : 0;
                            *(pixel_pointer + 3) = 255;
                        }
                    }
                    transparency_map[atlas_col][atlas_row] = Transparency::Opaque;
                }
            }
        }

        void Atlas::LoadData(const std::vector<std::pair<std::string, std::string> > &textures_path_names)
        {
            if (textures_path_names.size() == 0)
            {
                Reset(2, 2, 1, 1);
                return;
            }

            stbi_set_flip_vertically_on_load(true);
            std::vector<Texture> textures;
            textures.reserve(textures_path_names.size());

            int textures_width = std::numeric_limits<int>::max();
            int textures_height = std::numeric_limits<int>::max();

            for (int i = 0; i < textures_path_names.size(); ++i)
            {
                if (textures_path_names[i].first.empty())
                {
                    continue;
                }
                Texture tex;
                unsigned char *data = stbi_load(textures_path_names[i].first.c_str(), &tex.width, &tex.height, &tex.depth, 0);
                if (data != nullptr)
                {
                    tex.data = std::vector<unsigned char>(data, data + tex.width * tex.height * tex.depth);
                    tex.identifier = textures_path_names[i].second;
                    textures.push_back(tex);
                    if (tex.width < textures_width)
                    {
                        textures_width = tex.width;
                    }
                    if (tex.height < textures_height)
                    {
                        textures_height = tex.height;
                    }
                }
                stbi_image_free(data);
            }


            // Copy the textures with correct size (crop if the size is too big
            // and ignore if the size is too small)
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

                // If it's too small same
                if (textures[i].width < textures_width || textures[i].height < textures_height)
                {
                    std::cout << "Warning, texture " << textures[i].identifier << " is too small" << std::endl;
                    continue;
                }

                // If it's too big, keep the top left rectangle
                // Simple case, just take te first N lines
                if (textures[i].width == textures_width && textures[i].height > textures_height)
                {
                    std::cout << "Warning, textures height is not uniform, keep only the first rows for texture: " << textures[i].identifier << std::endl;
                    Texture new_texture;
                    new_texture.width = textures_width;
                    new_texture.height = textures_height;
                    new_texture.depth = textures[i].depth;
                    new_texture.identifier = textures[i].identifier;
                    new_texture.data = std::vector<unsigned char>(textures[i].data.begin(), textures[i].data.begin() + textures_width * textures_height * textures[i].depth);
                    kept_textures.push_back(new_texture);
                }
                // Less straightforward case, copy data pixel by pixel
                else if (textures[i].width > textures_width)
                {
                    std::cout << "Warning, textures height is not uniform, keep only the top left image for texture: " << textures[i].identifier << std::endl;
                    Texture new_texture;
                    new_texture.width = textures_width;
                    new_texture.height = textures_height;
                    new_texture.depth = textures[i].depth;
                    new_texture.identifier = textures[i].identifier;
                    new_texture.data = std::vector<unsigned char>(textures_width * textures_height * textures[i].depth);

                    for (int y = 0; y < textures_height; ++y)
                    {
                        for (int x = 0; x < textures_width; ++x)
                        {
                            for (int c = 0; c < textures[i].depth; ++c)
                            {
                                new_texture.data[(y * textures_width + x) * textures[i].depth + c] = textures[i].Get(x, y, c);
                            }
                        }
                    }

                    kept_textures.push_back(new_texture);
                }
                else
                {
                    kept_textures.push_back(textures[i]);
                }
            }

            //Compute atlas dimensions

            //Add one for the "undefined" texture
            int texture_counter = 1 + kept_textures.size();

            int atlas_width = (int)std::ceil(std::sqrt(texture_counter));
            int atlas_height = atlas_width;

            //Compute the global texture image
            Reset(textures_height, textures_width, atlas_height, atlas_width);

            for (int i = 0; i < kept_textures.size(); ++i)
            {
                const int texture_index = i + 1;
                positions[kept_textures[i].identifier] = std::pair<int, int>(texture_index % width, texture_index / width);

                for (int row = 0; row < textures_height; ++row)
                {
                    for (int col = 0; col < textures_width; ++col)
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

                        *(Get(texture_index / width, texture_index % width, row, col, 0)) = r;
                        *(Get(texture_index / width, texture_index % width, row, col, 1)) = g;
                        *(Get(texture_index / width, texture_index % width, row, col, 2)) = b;
                        *(Get(texture_index / width, texture_index % width, row, col, 3)) = a;

                        if (a == 0 && transparency_map[texture_index % width][texture_index / width] != Transparency::Partial)
                        {
                            transparency_map[texture_index % width][texture_index / width] = Transparency::Total;
                        }
                        else if (a < 255)
                        {
                            transparency_map[texture_index % width][texture_index / width] = Transparency::Partial;
                        }
                    }
                }
            }

            //In case we want to save the atlas to check the data
            //WriteImage("atlas.png", textures_height * height, textures_width * width, 4, data.data(), false);
        }

        const int Atlas::GetWidth() const
        {
            return width;
        }

        const int Atlas::GetHeight() const
        {
            return height;
        }

        const int Atlas::GetTextureWidth() const
        {
            return texture_width;
        }

        const int Atlas::GetTextureHeight() const
        {
            return texture_height;
        }

        const std::pair<int, int>& Atlas::GetPosition(const std::string &name) const
        {
            auto it = positions.find(name);
            if (it != positions.end())
            {
                return it->second;
            }

            return positions.at("");
        }

        const Transparency Atlas::GetTransparency(const std::pair<int, int> &pos) const
        {
            return transparency_map[pos.first][pos.second];
        }

        unsigned char* Atlas::Get(const int y, const int x, const int row, const int col, const int depth)
        {
            return data.data() + (((y * texture_height + row) * width + x) * texture_width + col) * 4 + depth;
        }
    } // Renderer
} // Botcraft