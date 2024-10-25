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
        DEFINE_CONDITION(HasContent, GetBlockId() != -1);
        SERIALIZED_FIELD(BlockId, short);
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(ItemCount, Internal::Conditioned<char, &Slot::HasContent, false>);
        SERIALIZED_FIELD(ItemDamage, Internal::Conditioned<short, &Slot::HasContent, false>);
        SERIALIZED_FIELD(Nbt, Internal::Conditioned<NBT::UnnamedValue, &Slot::HasContent, false>);
#elif PROTOCOL_VERSION < 404 /* < 1.13.2 */
        DEFINE_CONDITION(HasContent, GetItemId() != -1);
        SERIALIZED_FIELD(ItemId, short);
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(ItemCount, Internal::Conditioned<char, &Slot::HasContent, false>);
        SERIALIZED_FIELD(Nbt, Internal::Conditioned<NBT::UnnamedValue, &Slot::HasContent, false>);
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        DEFINE_CONDITION(HasContent, GetPresent());
        SERIALIZED_FIELD(Present, bool);
        SERIALIZED_FIELD(ItemId, Internal::Conditioned<VarInt, &Slot::HasContent, false>);
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(ItemCount, Internal::Conditioned<char, &Slot::HasContent, false>);
        SERIALIZED_FIELD(Nbt, Internal::Conditioned<NBT::UnnamedValue, &Slot::HasContent, false>);
#else
        DEFINE_CONDITION(HasContent, GetItemCount() > 0);
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(ItemCount, VarInt);
        SERIALIZED_FIELD(ItemId, Internal::Conditioned<VarInt, &Slot::HasContent, false>);
        SERIALIZED_FIELD(Components, Internal::Conditioned<Components::DataComponentPatch, &Slot::HasContent, false>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;

        GETTER(ItemCount);
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        SETTER(ItemCount);
#endif

    public:
        // Default constructor for empty slot
        Slot()
        {
#if PROTOCOL_VERSION < 350 /* < 1.13 */
            BlockId = 0;
#elif PROTOCOL_VERSION < 402 /* < 1.13.2 */
            ItemId = -1;
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
            Present = false;
            ItemId = -1;
#elif PROTOCOL_VERSION > 765 /* > 1.20.4 */
            ItemId = 0;
#endif
            ItemCount = 0;
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
        auto& SetItemCount(const char ItemCount_)
        {
            ItemCount = ItemCount_;
            if (ItemCount == 0)
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
#endif

#if PROTOCOL_VERSION < 350 /* < 1.13 */
        /// @brief Utility function to simplify interfacing between 1.12.2 and later versions
        /// @return Paired { block_id, item_damage }
        std::pair<int, unsigned char> GetItemId() const
        {
            return { static_cast<int>(GetBlockId()), static_cast<unsigned char>(GetItemDamage()) };
        }
#endif
    };
} // ProtocolCraft
