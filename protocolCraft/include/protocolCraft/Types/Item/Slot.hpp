#pragma once

#include "protocolCraft/NetworkType.hpp"
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
#include "protocolCraft/Types/NBT/NBT.hpp"
#else
#include "protocolCraft/Types/Components/DataComponents.hpp"
#endif

namespace ProtocolCraft
{
    class Slot : public NetworkType
    {
#if PROTOCOL_VERSION < 393 /* < 1.13 */
        DECLARE_FIELDS(
            (short,   char,      short,      NBT::UnnamedValue),
            (BlockId, ItemCount, ItemDamage, Nbt)
        );
#elif PROTOCOL_VERSION < 404 /* < 1.13.2 */
        DECLARE_FIELDS(
            (short,  char,      NBT::UnnamedValue),
            (ItemId, ItemCount, Nbt)
        );
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        DECLARE_FIELDS(
            (bool,    VarInt, char,      NBT::UnnamedValue),
            (Present, ItemId, ItemCount, Nbt)
        );
#else
        DECLARE_FIELDS(
            (VarInt,    VarInt, Components::DataComponentPatch),
            (ItemCount, ItemId, Components)
        );
#endif

#if PROTOCOL_VERSION < 393 /* < 1.13 */
        GETTER_SETTER(BlockId);
        GETTER_SETTER(ItemDamage);
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        GETTER_SETTER(ItemId);
#endif
#if PROTOCOL_VERSION > 401 /* > 1.13.1 */ && PROTOCOL_VERSION < 766 /* < 1.20.5 */
        GETTER_SETTER(Present);
#endif
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        GETTER_SETTER(Nbt);
#else
        GETTER_SETTER(Components);
#endif

    public:
        // Default constructor for empty slot
        Slot()
        {
#if PROTOCOL_VERSION < 350 /* < 1.13 */
            std::get<static_cast<size_t>(FieldsEnum::BlockId)>(fields) = 0;
#elif PROTOCOL_VERSION < 402 /* < 1.13.2 */
            std::get<static_cast<size_t>(FieldsEnum::ItemId)>(fields) = -1;
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
            std::get<static_cast<size_t>(FieldsEnum::Present)>(fields) = false;
            std::get<static_cast<size_t>(FieldsEnum::ItemId)>(fields) = -1;
#elif PROTOCOL_VERSION > 765 /* > 1.20.4 */
            std::get<static_cast<size_t>(FieldsEnum::ItemId)>(fields) = 0;
#endif
            std::get<static_cast<size_t>(FieldsEnum::ItemCount)>(fields) = 0;
        }

        virtual ~Slot() override
        {

        }

        bool SameItem(const Slot& s) const
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
#if PROTOCOL_VERSION < 350 /* < 1.13 */
            return GetBlockId() == s.GetBlockId() && GetItemDamage() == s.GetItemDamage();
#else
            return GetItemId() == s.GetItemId();
#endif
        }

        bool IsEmptySlot() const
        {
#if PROTOCOL_VERSION < 350 /* < 1.13 */
            return GetBlockId() == -1;
#elif PROTOCOL_VERSION < 402 /* < 1.13.2 */
            return GetItemId() == -1;
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
            return !GetPresent();
#elif PROTOCOL_VERSION > 765 /* > 1.20.4 */
            return GetItemCount() <= 0 || GetItemId() == 0;
#endif
        }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        auto& SetItemCount(const char item_count_)
        {
            std::get<static_cast<size_t>(FieldsEnum::ItemCount)>(fields) = item_count_;
            if (item_count_ == 0)
            {
#if PROTOCOL_VERSION < 350 /* < 1.13 */
                SetBlockId(-1);
#elif PROTOCOL_VERSION < 402 /* < 1.13.2 */
                SetItemId(-1);
#elif PROTOCOL_VERSION > 401 /* > 1.13.1 */
                SetPresent(false);
                SetItemId(-1);
#endif
                SetNbt(NBT::Value());
            }
            return *this;
        }
#else
        auto& SetItemCount(const int item_count_)
        {
            std::get<static_cast<size_t>(FieldsEnum::ItemCount)>(fields) = item_count_;
            return *this;
        }
#endif

#if PROTOCOL_VERSION < 350 /* < 1.13 */
        /// @brief Utility function to simplify interfacing between 1.12.2 and later versions
        /// @return Paired { block_id, item_damage }
        std::pair<int, unsigned char> GetItemId() const
        {
            return { static_cast<int>(GetBlockId()), static_cast<unsigned char>(GetItemDamage()) };
        }
#endif

        std::tuple_element_t<static_cast<size_t>(FieldsEnum::ItemCount), decltype(fields)> GetItemCount() const
        {
            return std::get<static_cast<size_t>(FieldsEnum::ItemCount)>(fields);
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 350 /* < 1.13 */
            SetBlockId(ReadData<short>(iter, length));
            if (GetBlockId() == -1)
            {
                return;
            }

            SetItemCount(ReadData<char>(iter, length));
            SetItemDamage(ReadData<short>(iter, length));
#elif PROTOCOL_VERSION < 402 /* < 1.13.2 */
            SetItemId(ReadData<short>(iter, length));
            if (GetItemId() == -1)
            {
                return;
            }

            SetItemCount(ReadData<char>(iter, length));
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
            SetPresent(ReadData<bool>(iter, length));
            if (!GetPresent())
            {
                return;
            }

            SetItemId(ReadData<VarInt>(iter, length));
            SetItemCount(ReadData<char>(iter, length));
#elif PROTOCOL_VERSION > 765 /* > 1.20.4 */
            SetItemCount(ReadData<VarInt>(iter, length));
            if (GetItemCount() <= 0)
            {
                return;
            }
            SetItemId(ReadData<VarInt>(iter, length));
#endif
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            SetNbt(ReadData<NBT::UnnamedValue>(iter, length));
#else
            SetComponents(ReadData<Components::DataComponentPatch>(iter, length));
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 350 /* < 1.13 */
            WriteData<short>(GetBlockId(), container);
            if (GetBlockId() == -1)
            {
                return;
            }
            WriteData<char>(GetItemCount(), container);
            WriteData<short>(GetItemDamage(), container);
#elif PROTOCOL_VERSION < 402 /* < 1.13.2 */
            WriteData<short>(GetItemId(), container);
            if (GetItemId() == -1)
            {
                return;
            }
            WriteData<char>(GetItemCount(), container);
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
            WriteData<bool>(GetPresent(), container);
            if (!GetPresent())
            {
                return;
            }
            WriteData<VarInt>(GetItemId(), container);
            WriteData<char>(GetItemCount(), container);
#elif PROTOCOL_VERSION > 765 /* > 1.20.4 */
            if (IsEmptySlot())
            {
                WriteData<VarInt>(0, container);
                return;
            }
            WriteData<VarInt>(GetItemCount(), container);
            WriteData<VarInt>(GetItemId(), container);
#endif
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            WriteData<NBT::UnnamedValue>(GetNbt(), container);
#else
            WriteData<Components::DataComponentPatch>(GetComponents(), container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION < 350 /* < 1.13 */
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::BlockId)])] = GetBlockId();
            if (GetBlockId() != -1)
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::ItemDamage)])] = GetItemDamage();
            }
#elif PROTOCOL_VERSION < 402 /* < 1.13.2 */
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::ItemId)])] = GetItemId();
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Present)])] = GetPresent();
            if (GetPresent())
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::ItemId)])] = GetItemId();
            }
#elif PROTOCOL_VERSION > 765 /* > 1.20.4 */
            if (GetItemCount() > 0)
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::ItemId)])] = GetItemId();
            }
#endif
#if PROTOCOL_VERSION < 350 /* < 1.13 */
            if(GetBlockId() != -1)
#elif PROTOCOL_VERSION < 402 /* < 1.13.2 */
            if(GetItemId() != -1)
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
            if (GetPresent())
#elif PROTOCOL_VERSION > 765 /* > 1.20.4 */
            if (GetItemCount() > 0)
#endif
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::ItemCount)])] = GetItemCount();
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
                if (GetNbt().HasData())
                {
                    output[std::string(json_names[static_cast<size_t>(FieldsEnum::Nbt)])] = GetNbt();
                }
#else
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Components)])] = GetComponents();
#endif
            }
            return output;
        }
    };
} // ProtocolCraft
