#pragma once

#include <string>

namespace Botcraft
{
    class Item
    {
    public:
#if PROTOCOL_VERSION < 347
        Item(const int id_, const unsigned char damage_id_, const std::string& name_, const unsigned char stack_size_);
#else
        Item(const int id_, const std::string& name_, const unsigned char stack_size_);
#endif
        const int GetId() const;
        const std::string& GetName() const;
        const unsigned char GetStackSize() const;
#if PROTOCOL_VERSION < 347
        const unsigned char GetDamageId() const;
#endif

    private:
        int id;
        std::string name;
        unsigned char stack_size;
#if PROTOCOL_VERSION < 347
        unsigned char damage_id;
#endif
    };
} // Botcraft