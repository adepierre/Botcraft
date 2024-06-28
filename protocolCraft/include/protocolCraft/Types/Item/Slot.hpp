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
        // We don't store conditioned values as optional in Slot cause we already have a IsEmptySlot function to check for data presence
#if PROTOCOL_VERSION < 393 /* < 1.13 */
        DECLARE_CONDITION(HasContent, GetBlockId() != -1);
        DECLARE_FIELDS(
            (short,   Internal::Conditioned<char, &Slot::HasContent, false>, Internal::Conditioned<short, &Slot::HasContent, false>, Internal::Conditioned<NBT::UnnamedValue, &Slot::HasContent, false>),
            (BlockId, ItemCount,                                             ItemDamage,                                             Nbt)
        );
#elif PROTOCOL_VERSION < 404 /* < 1.13.2 */
        DECLARE_CONDITION(HasContent, GetItemId() != -1);
        DECLARE_FIELDS(
            (short,  Internal::Conditioned<char, &Slot::HasContent, false>, Internal::Conditioned<NBT::UnnamedValue, &Slot::HasContent, false>),
            (ItemId, ItemCount,                                             Nbt)
        );
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        DECLARE_CONDITION(HasContent, GetPresent());
        DECLARE_FIELDS(
            (bool,    Internal::Conditioned<VarInt, &Slot::HasContent, false>, Internal::Conditioned<char, &Slot::HasContent, false>, Internal::Conditioned<NBT::UnnamedValue, &Slot::HasContent, false>),
            (Present, ItemId,                                                  ItemCount,                                             Nbt)
        );
#else
        DECLARE_CONDITION(HasContent, GetItemCount() > 0);
        DECLARE_FIELDS(
            (VarInt,    Internal::Conditioned<VarInt, &Slot::HasContent, false>, Internal::Conditioned<Components::DataComponentPatch, &Slot::HasContent, false>),
            (ItemCount, ItemId,                                                  Components)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

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
    };
} // ProtocolCraft
