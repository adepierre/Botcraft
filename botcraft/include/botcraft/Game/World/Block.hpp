#pragma once

#include "botcraft/Game/World/Blockstate.hpp"
#include "botcraft/Game/Vector3.hpp"

namespace Botcraft
{
    class Block
    {
    public:
#if PROTOCOL_VERSION < 347 /* < 1.13 */
        Block(const int id_ = 0, const unsigned char metadata_ = 0);

        void ChangeBlockstate(const int id_, const unsigned char metadata_, const int model_id_ = -1, const Position* pos = nullptr);
#else
        Block(const int id_ = 0);

        void ChangeBlockstate(const int id_, const int model_id_ = -1, const Position* pos = nullptr);
#endif

        const Blockstate* GetBlockstate() const;
        const unsigned short GetModelId() const;

    private:
        const Blockstate* blockstate;
        unsigned short model_id;
    };
} // Botcraft
