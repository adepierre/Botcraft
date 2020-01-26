#pragma once

#include "botcraft/Protocol/NetworkType.hpp"
#include "botcraft/NBT/NBT.hpp"
#include "botcraft/Version.hpp"

namespace Botcraft 
{
    class Slot : public NetworkType
    {
    public:
        Slot();
#if PROTOCOL_VERSION < 350
        const short GetBlockID() const;
        const short GetItemDamage() const;
#elif PROTOCOL_VERSION < 402
        const short GetItemID() const;
#elif PROTOCOL_VERSION >= 402
        const bool GetPresent() const;
        const short GetItemID() const;
#endif
        const char GetItemCount() const;
        const NBT& GetNBT() const;

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override;
        virtual void WriteImpl(WriteContainer &containenr) const override;
        virtual const picojson::value SerializeImpl() const override;

    private:
#if PROTOCOL_VERSION < 350
        short block_id;
        short item_damage;
#elif PROTOCOL_VERSION < 402
        short item_id;
#elif PROTOCOL_VERSION >= 402
        bool present;
        short item_id;
#endif
        char item_count;
        NBT nbt;
    };
} // Botcraft