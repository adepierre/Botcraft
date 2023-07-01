#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"

namespace ProtocolCraft 
{
    class Slot : public NetworkType
    {
    public:
        // Default constructor for empty slot
        Slot()
        {
#if PROTOCOL_VERSION < 350
            block_id = -1;
#elif PROTOCOL_VERSION < 402
            item_id = -1;
#elif PROTOCOL_VERSION >= 402
            present = false;
            item_id = -1;
#endif
            item_count = 0;
        }

        virtual ~Slot() override
        {

        }

        const bool SameItem(const Slot& s) const
        {
            if (IsEmptySlot() && s.IsEmptySlot())
            {
                return true;
            }
            if (IsEmptySlot() && !s.IsEmptySlot())
            {
                return false;
            }
            // !IsEmptySlot
            if (s.IsEmptySlot())
            {
                return false;
            }

            // Both are non empty
#if PROTOCOL_VERSION < 350
            return block_id == s.GetBlockID() && item_damage == s.GetItemDamage();
#else
            return item_id == s.GetItemID();
#endif
        }

        const bool IsEmptySlot() const
        {
#if PROTOCOL_VERSION < 350
            return block_id == -1;
#elif PROTOCOL_VERSION < 402
            return item_id == -1;
#elif PROTOCOL_VERSION >= 402
            return !present;
#endif
        }

#if PROTOCOL_VERSION < 350
        void SetBlockID(const short block_id_)
        {
            block_id = block_id_;
        }

        void SetItemDamage(const short item_damage_)
        {
            item_damage = item_damage_;
        }
#elif PROTOCOL_VERSION < 402
        void SetItemID(const short item_id_)
        {
            item_id = item_id_;
        }
#elif PROTOCOL_VERSION >= 402
        void SetPresent(const bool present_)
        {
            present = present_;
        }

        void SetItemID(const short item_id_)
        {
            item_id = item_id_;
        }
#endif

        void SetItemCount(const char item_count_)
        {
            item_count = item_count_;
            if (item_count == 0)
            {
#if PROTOCOL_VERSION < 350
                block_id = -1;
#elif PROTOCOL_VERSION < 402
                item_id = -1;
#elif PROTOCOL_VERSION >= 402
                present = false;
                item_id = -1;
#endif
                nbt = NBT::Value();
            }
        }

        void SetNBT(const NBT::Value& nbt_)
        {
            nbt = nbt_;
        }

#if PROTOCOL_VERSION < 350
        short GetBlockID() const
        {
            return block_id;
        }

        short GetItemDamage() const
        {
            return item_damage;
        }

        /// @brief Utility function to simplify interfacing between 1.12.2 and later versions
        /// @return Paired { block_id, item_damage }
        std::pair<int, unsigned char> GetItemID() const
        {
            return { static_cast<int>(block_id), static_cast<unsigned char>(item_damage) };
        }
#elif PROTOCOL_VERSION < 402
        short GetItemID() const
        {
            return item_id;
        }
#elif PROTOCOL_VERSION >= 402
        bool GetPresent() const
        {
            return present;
        }

        short GetItemID() const
        {
            return item_id;
        }
#endif

        char GetItemCount() const
        {
            return item_count;
        }

        const NBT::Value& GetNBT() const
        {
            return nbt;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
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

            item_id = ReadData<VarInt>(iter, length);
            item_count = ReadData<char>(iter, length);
#endif
            nbt = ReadData<NBT::Value>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
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
            WriteData<VarInt>(item_id, container);
            WriteData<char>(item_count, container);
#endif
            WriteData<NBT::Value>(nbt, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION < 350
            output["block_id"] = block_id;
            if (block_id != -1)
            {
                output["item_damage"] = item_damage;
            }
#elif PROTOCOL_VERSION < 402
            output["item_id"] = item_id;
#elif PROTOCOL_VERSION >= 402
            output["present"] = present;
            if (present)
            {
                output["item_id"] = item_id;
            }
#endif
#if PROTOCOL_VERSION < 350
            if(block_id != -1)
#elif PROTOCOL_VERSION < 402
            if(item_id != -1)
#elif PROTOCOL_VERSION >= 402
            if (present)
#endif
            {
                output["item_count"] = item_count;
                if (nbt.HasData())
                {
                    output["nbt"] = nbt;
                }
            }
            return output;
        }

    private:
#if PROTOCOL_VERSION < 350
        short block_id = 0;
        short item_damage = 0;
#elif PROTOCOL_VERSION < 402
        short item_id = 0;
#elif PROTOCOL_VERSION >= 402
        bool present = false;
        short item_id = 0;
#endif
        char item_count = 0;
        NBT::Value nbt;
    };
} // ProtocolCraft
