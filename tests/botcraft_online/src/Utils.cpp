#include "Utils.hpp"

#include <botcraft/Utilities/ItemUtilities.hpp>

void SendCommandSetItem(const std::string& botname, const std::string& item_name, const Botcraft::EquipmentSlot slot, const std::map<Botcraft::Enchantment, int>& enchantments)
{
    std::string command;
#if PROTOCOL_VERSION < 393 /* < 1.13 */
    command = "replaceitem entity " + botname + " slot.";
#elif PROTOCOL_VERSION < 755 /* < 1.17 */
    command = "replaceitem entity " + botname + " ";
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
    command = "item replace entity " + botname + " ";
#else
    command = "item replace entity " + botname + " ";
#endif

    switch (slot)
    {
    case Botcraft::EquipmentSlot::MainHand:
        command += "weapon.mainhand";
        break;
    case Botcraft::EquipmentSlot::OffHand:
        command += "weapon.offhand";
        break;
    case Botcraft::EquipmentSlot::Boots:
        command += "armor.feet";
        break;
    case Botcraft::EquipmentSlot::Leggings:
        command += "armor.legs";
        break;
    case Botcraft::EquipmentSlot::ChestPlate:
        command += "armor.chest";
        break;
    case Botcraft::EquipmentSlot::Helmet:
        command += "armor.head";
        break;
    }

#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
    command += " with";
#endif

    command += " " + item_name;

#if PROTOCOL_VERSION < 393 /* < 1.13 */
    command += " 1 0";
#endif

    if (enchantments.size() > 0)
    {
#if PROTOCOL_VERSION < 393 /* < 1.13 */
        command += " {ench:[";
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        command += "{Enchantments:[";
#else
        command += "[enchantments={levels:{";
#endif

        size_t index = 0;
        for (const auto& [id, lvl] : enchantments)
        {
#if PROTOCOL_VERSION < 393 /* < 1.13 */
            command += "{id:" + std::to_string(static_cast<int>(id)) + ",lvl:" + std::to_string(lvl) + "}";
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
            command += "{id:" + std::string(Botcraft::Utilities::EnchantmentToString(id)) + ",lvl:" + std::to_string(lvl) + "}";

#else
            command += std::string(Botcraft::Utilities::EnchantmentToString(id)) + ":" + std::to_string(lvl);
#endif
            index += 1;
            if (index < enchantments.size())
            {
                command += ",";
            }
        }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        command += "]}";
#else
        command += "}}]";
#endif
    }

#if PROTOCOL_VERSION > 340 /* > 1.12.2 */ && PROTOCOL_VERSION < 766 /* < 1.20.5 */
    command += " 1";
#endif

    MinecraftServer::GetInstance().SendLine(command);
    // TODO: wait line (?)
}

void SendCommandSetItem(const std::string& botname, const std::string& item_name, const Botcraft::EquipmentSlot slot, const Botcraft::Enchantment enchantment)
{
    return SendCommandSetItem(botname, item_name, slot, { {enchantment, 1} });
}

std::string ReplaceCharacters(const std::string& in, const std::vector<std::pair<char, std::string>>& replacements)
{
    std::string output;
    output.reserve(in.size());

    for (size_t i = 0; i < in.size(); ++i)
    {
        bool found = false;
        for (size_t j = 0; j < replacements.size(); ++j)
        {
            if (replacements[j].first == in[i])
            {
                output += replacements[j].second;
                found = true;
                break;
            }
        }
        if (!found)
        {
            output += in[i];
        }
    }

    return output;
}
