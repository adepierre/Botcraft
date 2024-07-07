#pragma once

#include "protocolCraft/Utilities/Json.hpp"
#include "protocolCraft/Utilities/Templates.hpp"
#include "protocolCraft/Utilities/AutoSerializedToJson.hpp"
#include "protocolCraft/BinaryReadWrite.hpp"

namespace ProtocolCraft
{
    namespace Internal
    {
        template <typename T, auto ReadFunc = nullptr, auto WriteFunc = nullptr, auto SerializeFunc = nullptr>
        struct CustomType
        {
            using storage_type = typename SerializedType<T>::storage_type;
            using serialization_type = typename SerializedType<T>::serialization_type;

            template <typename C>
            static storage_type Read(const C* c, std::vector<unsigned char>::const_iterator& iter, size_t& length)
            {
                if constexpr (ReadFunc == nullptr)
                {
                    return ReadData<storage_type, serialization_type>(iter, length);
                }
                else
                {
                    return (c->*ReadFunc)(iter, length);
                }
            }

            template <typename C>
            static void Write(const C* c, const storage_type& val, std::vector<unsigned char>& container)
            {
                if constexpr (WriteFunc == nullptr)
                {
                    WriteData<storage_type, serialization_type>(val, container);
                }
                else
                {
                    (c->*WriteFunc)(val, container);
                }
            }

            template <typename C>
            static std::optional<Json::Value> Serialize(const C* c, const storage_type& val)
            {
                if constexpr (SerializeFunc == nullptr)
                {
                    return SerializeType<storage_type>(val);
                }
                else
                {
                    return (c->*SerializeFunc)(val);
                }
            }
        };
    }
}
