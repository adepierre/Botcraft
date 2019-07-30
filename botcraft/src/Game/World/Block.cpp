#include "botcraft/Game/World/Block.hpp"
#include "botcraft/Game/AssetsManager.hpp"

namespace Botcraft
{
#if PROTOCOL_VERSION < 347
    Block::Block(const int id_, const unsigned char metadata_)
    {
        ChangeBlockstate(id_, metadata_);
    }

    void Block::ChangeBlockstate(const int id_, const unsigned char metadata_, const int model_id_)
    {
        auto &blockstates_map = AssetsManager::getInstance().Blockstates();
        auto it = blockstates_map.find(id_);
        if (it != blockstates_map.end())
        {
            auto it2 = it->second.find(metadata_);
            if (it2 != it->second.end())
            {
                blockstate = it2->second;
            }
            else
            {
                blockstate = it->second.at(0);
            }
        }
        else
        {
            blockstate = blockstates_map.at(-1).at(0);
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

    void Block::ChangeBlockstate(const int id_, const int model_id_)
    {
        auto &blockstates_map = AssetsManager::getInstance().Blockstates();
        auto it = blockstates_map.find(id_);
        if (it != blockstates_map.end())
        {
            blockstate = it->second;
        }
        else
        {
            blockstate = blockstates_map.at(-1);
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
#endif

    const std::shared_ptr<Blockstate> Block::GetBlockstate() const
    {
        return blockstate;
    }

    const unsigned short Block::GetModelId() const
    {
        return model_id;
    }
} //Botcraft