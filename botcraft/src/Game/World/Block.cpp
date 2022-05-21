#include "botcraft/Game/World/Block.hpp"
#include "botcraft/Game/AssetsManager.hpp"

namespace Botcraft
{
#if PROTOCOL_VERSION < 347
    Block::Block(const int id_, const unsigned char metadata_)
    {
        ChangeBlockstate(id_, metadata_);
    }

    void Block::ChangeBlockstate(const int id_, const unsigned char metadata_, const int model_id_, const Position* pos)
    {
        auto &blockstates_map = AssetsManager::getInstance().Blockstates();
        auto it = blockstates_map.find(id_);
        if (it != blockstates_map.end())
        {
            auto it2 = it->second.find(metadata_);
            if (it2 != it->second.end())
            {
                blockstate = it2->second.get();
            }
            else
            {
                blockstate = it->second.at(0).get();
            }
        }
        else
        {
            blockstate = blockstates_map.at(-1).at(0).get();
        }
        if (model_id_ < 0)
        {
            model_id = blockstate->GetRandomModelId();
        }
        else
        {
            model_id = model_id_;
        }
    }
#else
    Block::Block(const int id_)
    {
        ChangeBlockstate(id_);
    }

    void Block::ChangeBlockstate(const int id_, const int model_id_, const Position* pos)
    {
        // For air we know there is no model, so we can optimize this
        if (id_ == 0)
        {
            static const Blockstate* air_blockstate = AssetsManager::getInstance().Blockstates().at(0).get();
            blockstate = air_blockstate;
            model_id = model_id_;
            return;
        }

        auto &blockstates_map = AssetsManager::getInstance().Blockstates();
        auto it = blockstates_map.find(id_);
        if (it != blockstates_map.end())
        {
            blockstate = it->second.get();
        }
        else
        {
            blockstate = blockstates_map.at(-1).get();
        }

        model_id = model_id_ < 0 ? blockstate->GetRandomModelId(pos) : model_id_;
    }
#endif

    const Blockstate* Block::GetBlockstate() const
    {
        return blockstate;
    }

    const unsigned short Block::GetModelId() const
    {
        return model_id;
    }
} //Botcraft
