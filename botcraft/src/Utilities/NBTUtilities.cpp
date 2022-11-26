#include "botcraft/Utilities/NBTUtilities.hpp"

#include "protocolCraft/Types/NBT/TagList.hpp"
#include "protocolCraft/Types/NBT/TagCompound.hpp"
#include "protocolCraft/Types/NBT/TagShort.hpp"
#include "protocolCraft/Types/NBT/TagString.hpp"

using namespace ProtocolCraft;

namespace Botcraft
{
    short GetEnchantmentLvl(const NBT& item_nbt, const std::string& enchantment_name)
    {
        if (!item_nbt.HasData())
        {
            return 0;
        }

        const std::shared_ptr<Tag>& enchantments = item_nbt.GetTag("Enchantments");
        if (enchantments == nullptr || enchantments->GetType() != TagType::List)
        {
            return 0;
        }

        for (const auto& enchantment_tag : std::dynamic_pointer_cast<TagList>(enchantments)->GetValues())
        {
            if (enchantment_tag->GetType() != TagType::Compound)
            {
                continue;
            }

            const std::shared_ptr<Tag>& id_tag = std::dynamic_pointer_cast<TagCompound>(enchantment_tag)->GetValue("id");
            const std::shared_ptr<Tag>& lvl_tag = std::dynamic_pointer_cast<TagCompound>(enchantment_tag)->GetValue("lvl");

            if (id_tag == nullptr || lvl_tag == nullptr
                || id_tag->GetType() != TagType::String || lvl_tag->GetType() != TagType::Short)
            {
                continue;
            }

            if (std::dynamic_pointer_cast<TagString>(id_tag)->GetValue() == enchantment_name)
            {
                return std::dynamic_pointer_cast<TagShort>(lvl_tag)->GetValue();
            }
        }

        return 0;
    }
}
