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
        DECLARE_FIELDS_TYPES(short,   char,      short,      NBT::UnnamedValue);
        DECLARE_FIELDS_NAMES(BlockID, ItemCount, ItemDamage, NBT);
#elif PROTOCOL_VERSION < 404 /* < 1.13.2 */
        DECLARE_FIELDS_TYPES(short,  char,      NBT::UnnamedValue);
        DECLARE_FIELDS_NAMES(ItemID, ItemCount, NBT);
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        DECLARE_FIELDS_TYPES(bool,    VarInt, char,      NBT::UnnamedValue);
        DECLARE_FIELDS_NAMES(Present, ItemID, ItemCount, NBT);
#else
        DECLARE_FIELDS_TYPES(VarInt,    VarInt, Components::DataComponentPatch);
        DECLARE_FIELDS_NAMES(ItemCount, ItemID, Components);
#endif

#if PROTOCOL_VERSION < 393 /* < 1.13 */
        GETTER_SETTER(BlockID);
        GETTER_SETTER(ItemDamage);
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        GETTER_SETTER(ItemID);
#endif
#if PROTOCOL_VERSION > 401 /* > 1.13.1 */ && PROTOCOL_VERSION < 766 /* < 1.20.5 */
        GETTER_SETTER(Present);
#endif
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        GETTER_SETTER(NBT);
#else
        GETTER_SETTER(Components);
#endif

    public:
        // Default constructor for empty slot
        Slot()
        {
#if PROTOCOL_VERSION < 350 /* < 1.13 */
            SetBlockID(0);
#elif PROTOCOL_VERSION < 402 /* < 1.13.2 */
            SetItemID(-1);
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
            SetPresent(false);
            SetItemID(-1);
#elif PROTOCOL_VERSION > 765 /* > 1.20.4 */
            SetItemID(0);
#endif
            SetItemCount(0);
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
#if PROTOCOL_VERSION < 350 /* < 1.13 */
            return GetBlockID() == s.GetBlockID() && GetItemDamage() == s.GetItemDamage();
#else
            return GetItemID() == s.GetItemID();
#endif
        }

        const bool IsEmptySlot() const
        {
#if PROTOCOL_VERSION < 350 /* < 1.13 */
            return GetBlockID() == -1;
#elif PROTOCOL_VERSION < 402 /* < 1.13.2 */
            return GetItemID() == -1;
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
            return !GetPresent();
#elif PROTOCOL_VERSION > 765 /* > 1.20.4 */
            return GetItemCount() <= 0 || GetItemID() == 0;
#endif
        }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        void SetItemCount(const char item_count_)
        {
            SetItemCount(item_count_);
            if (item_count_ == 0)
            {
#if PROTOCOL_VERSION < 350 /* < 1.13 */
                SetBlockID(-1);
#elif PROTOCOL_VERSION < 402 /* < 1.13.2 */
                SetItemID(-1);
#elif PROTOCOL_VERSION > 401 /* > 1.13.1 */
                SetPresent(false);
                SetItemID(-1);
#endif
                SetNBT(NBT::Value());
            }
        }
#else
        void SetItemCount(const int item_count_)
        {
            std::get<static_cast<size_t>(FieldsEnum::ItemCount)>(fields) = item_count_;
        }
#endif

#if PROTOCOL_VERSION < 350 /* < 1.13 */
        /// @brief Utility function to simplify interfacing between 1.12.2 and later versions
        /// @return Paired { block_id, item_damage }
        std::pair<int, unsigned char> GetItemID() const
        {
            return { static_cast<int>(GetBlockID()), static_cast<unsigned char>(GetItemDamage()) };
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
            SetBlockID(ReadData<short>(iter, length));
            if (GetBlockID() == -1)
            {
                return;
            }

            SetItemCount(ReadData<char>(iter, length));
            SetItemDamage(ReadData<short>(iter, length));
#elif PROTOCOL_VERSION < 402 /* < 1.13.2 */
            SetItemID(ReadData<short>(iter, length));
            if (GetItemID() == -1)
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

            SetItemID(ReadData<VarInt>(iter, length));
            SetItemCount(ReadData<char>(iter, length));
#elif PROTOCOL_VERSION > 765 /* > 1.20.4 */
            SetItemCount(ReadData<VarInt>(iter, length));
            if (GetItemCount() <= 0)
            {
                return;
            }
            SetItemID(ReadData<VarInt>(iter, length));
#endif
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            SetNBT(ReadData<NBT::UnnamedValue>(iter, length));
#else
            SetComponents(ReadData<Components::DataComponentPatch>(iter, length));
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 350 /* < 1.13 */
            WriteData<short>(GetBlockID(), container);
            if (GetBlockID() == -1)
            {
                return;
            }
            WriteData<char>(GetItemCount(), container);
            WriteData<short>(GetItemDamage(), container);
#elif PROTOCOL_VERSION < 402 /* < 1.13.2 */
            WriteData<short>(GetItemID(), container);
            if (GetItemID() == -1)
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
            WriteData<VarInt>(GetItemID(), container);
            WriteData<char>(GetItemCount(), container);
#elif PROTOCOL_VERSION > 765 /* > 1.20.4 */
            if (IsEmptySlot())
            {
                WriteData<VarInt>(0, container);
                return;
            }
            WriteData<VarInt>(GetItemCount(), container);
            WriteData<VarInt>(GetItemID(), container);
#endif
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            WriteData<NBT::UnnamedValue>(GetNBT(), container);
#else
            WriteData<Components::DataComponentPatch>(GetComponents(), container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION < 350 /* < 1.13 */
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::BlockID)])] = GetBlockID();
            if (GetBlockID() != -1)
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::ItemDamage)])] = GetItemDamage();
            }
#elif PROTOCOL_VERSION < 402 /* < 1.13.2 */
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::ItemID)])] = GetItemID();
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Present)])] = GetPresent();
            if (GetPresent())
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::ItemID)])] = GetItemID();
            }
#elif PROTOCOL_VERSION > 765 /* > 1.20.4 */
            if (GetItemCount() > 0)
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::ItemID)])] = GetItemID();
            }
#endif
#if PROTOCOL_VERSION < 350 /* < 1.13 */
            if(GetBlockID() != -1)
#elif PROTOCOL_VERSION < 402 /* < 1.13.2 */
            if(GetItemID() != -1)
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
            if (GetPresent())
#elif PROTOCOL_VERSION > 765 /* > 1.20.4 */
            if (GetItemCount() > 0)
#endif
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::ItemCount)])] = GetItemCount();
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
                if (GetNBT().HasData())
                {
                    output[std::string(json_names[static_cast<size_t>(FieldsEnum::NBT)])] = GetNBT();
                }
#else
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Components)])] = GetComponents();
#endif
            }
            return output;
        }
    };
} // ProtocolCraft
