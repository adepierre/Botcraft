#include "botcraft/Game/Inventory/Item.hpp"

namespace Botcraft
{
#if PROTOCOL_VERSION < 347
    Item::Item(const int id_, const unsigned char damage_id_, const std::string& name_) :
        id(id_), damage_id(damage_id_), name(name_)
#else
    Item::Item(const int id_, const std::string& name_) :
        id(id_), name(name_)
#endif
    {

    }

    const int Item::GetId() const
    {
        return id;
    }

    const std::string& Item::GetName() const
    {
        return name;
    }

#if PROTOCOL_VERSION < 347
    const unsigned char Item::GetDamageId() const
    {
        return damage_id;
    }
#endif
} //Botcraft