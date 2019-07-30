#include "botcraft/Game/Inventory/Slot.hpp"

namespace Botcraft
{
    Slot::Slot()
    {
#if PROTOCOL_VERSION < 350
        block_id = -1;
        item_damage = 0;
#elif PROTOCOL_VERSION < 402
        item_id = -1;
#elif PROTOCOL_VERSION >= 402
        present = false;
        item_id = -1;
#endif
        item_count = 0;
        nbt = NBT();
    }

#if PROTOCOL_VERSION < 350
    const short Slot::GetBlockID() const
    {
        return block_id;
    }

    const short Slot::GetItemDamage() const
    {
        return item_damage;
    }
#elif PROTOCOL_VERSION < 402
    const short Slot::GetItemID() const
    {
        return item_id;
    }
#elif PROTOCOL_VERSION >= 402
    const bool Slot::GetPresent() const
    {
        return present;
    }

    const short Slot::GetItemID() const
    {
        return item_id;
    }
#endif

    const char Slot::GetItemCount() const
    {
        return item_count;
    }

    const NBT& Slot::GetNBT() const
    {
        return nbt;
    }

    void Slot::ReadImpl(ReadIterator &iter, size_t &length)
    {
#if PROTOCOL_VERSION < 350
        block_id = ReadData<short>(iter, length);
        if (block_id == -1)
        {
            return;
        }

        item_count = ReadData<char>(iter, length);
        item_damage = ReadData<short>(iter, length);
#elif PROTOCOL_VERSION < 402
        item_id = ReadData<short>(iter, length);
        if (item_id == -1)
        {
            return;
        }

        item_count = ReadData<char>(iter, length);
#elif PROTOCOL_VERSION >= 402
        present = ReadData<bool>(iter, length);
        if (!present)
        {
            return;
        }

        item_id = ReadVarInt(iter, length);
        item_count = ReadData<char>(iter, length);
#endif
        nbt.Read(iter, length);
    }

    void Slot::WriteImpl(WriteContainer &container) const
    {

#if PROTOCOL_VERSION < 350
        WriteData<short>(block_id, container);
        if (block_id == -1)
        {
            return;
        }
        WriteData<char>(item_count, container);
        WriteData<short>(item_damage, container);
#elif PROTOCOL_VERSION < 402
        WriteData<short>(item_id, container);
        if (item_id == -1)
        {
            return;
        }
        WriteData<char>(item_count, container);
#elif PROTOCOL_VERSION >= 402
        WriteData<bool>(present, container);
        if (!present)
        {
            return;
        }
        WriteVarInt(item_id, container);
        WriteData<char>(item_count, container);
#endif
        nbt.Write(container);
    }

} //Botcraft