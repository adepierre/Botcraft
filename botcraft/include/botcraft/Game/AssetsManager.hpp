#pragma once

#include "botcraft/Game/World/Biome.hpp"
#include "botcraft/Game/World/Blockstate.hpp"
#include "botcraft/Game/Inventory/Item.hpp"

#include <vector>
#include <unordered_map>

namespace Botcraft
{
#if USE_GUI
    namespace Renderer
    {
        class Atlas;
    }
#endif

    class AssetsManager
    {
    public:
        static AssetsManager& getInstance();

        AssetsManager(AssetsManager const&) = delete;
        void operator=(AssetsManager const&) = delete;

#if PROTOCOL_VERSION < 347
        const std::unordered_map<int, std::unordered_map<unsigned char, std::shared_ptr<Blockstate> > >& Blockstates() const;
#else
        const std::unordered_map<int, std::shared_ptr<Blockstate> >& Blockstates() const;
#endif
        
#if PROTOCOL_VERSION < 358
        const std::unordered_map<unsigned char, std::shared_ptr<Biome> >& Biomes() const;
        const std::shared_ptr<Biome> GetBiome(const unsigned char id);
#else
        const std::unordered_map<int, std::shared_ptr<Biome> >& Biomes() const;
        const std::shared_ptr<Biome> GetBiome(const int id);
#endif

#if PROTOCOL_VERSION < 347
        const std::unordered_map<int, std::unordered_map<unsigned char, std::shared_ptr<Item> > >& Items() const;
#else
        const std::unordered_map<int, std::shared_ptr<Item> >& Items() const;
#endif

#if USE_GUI
        const Renderer::Atlas* GetAtlas() const;
#endif

    private:
        AssetsManager();

        void LoadBlocksFile();
        void LoadBiomesFile();
        void LoadItemsFile();
#if USE_GUI
        void LoadTextures();
#endif
        void ClearCaches();

#if USE_GUI
        void UpdateModelsWithAtlasData();
#endif

    private:
#if PROTOCOL_VERSION < 347
        std::unordered_map<int, std::unordered_map<unsigned char, std::shared_ptr<Blockstate> > > blockstates;
#else
        std::unordered_map<int, std::shared_ptr<Blockstate> > blockstates;
#endif
#if PROTOCOL_VERSION < 358
        std::unordered_map<unsigned char, std::shared_ptr<Biome> > biomes;
#else
        std::unordered_map<int, std::shared_ptr<Biome> > biomes;
#endif
#if PROTOCOL_VERSION < 347
        std::unordered_map<int, std::unordered_map<unsigned char, std::shared_ptr<Item> > > items;
#else
        std::unordered_map<int, std::shared_ptr<Item> > items;
#endif
#if USE_GUI
        std::unique_ptr<Renderer::Atlas> atlas;
#endif
    };
} // Botcraft