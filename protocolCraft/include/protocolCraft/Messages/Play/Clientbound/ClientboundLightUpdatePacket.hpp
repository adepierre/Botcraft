#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Utilities/CustomType.hpp"
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
#include "protocolCraft/Types/ClientboundLightUpdatePacketData.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundLightUpdatePacket : public BaseMessage<ClientboundLightUpdatePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Light Update";

#if PROTOCOL_VERSION < 755 /* < 1.17 */
    private:
        std::vector<std::vector<char>> ReadSkyUpdates(ReadIterator& iter, size_t& length) const
        {
            std::vector<std::vector<char>> sky_updates;
            sky_updates.reserve(18);
            for (int i = 0; i < 18; ++i)
            {
                if ((GetSkyYMask() >> i) & 1)
                {
                    sky_updates.push_back(ReadData<std::vector<char>>(iter, length)); // Should always contain 2048 chars
                }
            }
            return sky_updates;
        }

        void WriteSkyUpdates(const std::vector<std::vector<char>>& sky_updates, WriteContainer& container) const
        {
            for (const auto& v : sky_updates)
            {
                WriteData<std::vector<char>>(v, container);
            }
        }

        std::vector<std::vector<char>> ReadBlockUpdates(ReadIterator& iter, size_t& length) const
        {
            std::vector<std::vector<char>> block_updates;
            block_updates.reserve(18);
            for (int i = 0; i < 18; ++i)
            {
                if ((GetBlockYMask() >> i) & 1)
                {
                    block_updates.push_back(ReadData<std::vector<char>>(iter, length)); // Should always contain 2048 chars
                }
            }
            return block_updates;
    }

        void WriteBlockUpdates(const std::vector<std::vector<char>>& block_updates, WriteContainer& container) const
        {
            for (const auto& v : block_updates)
            {
                WriteData<std::vector<char>>(v, container);
            }
        }
#endif

        SERIALIZED_FIELD(X, VarInt);
        SERIALIZED_FIELD(Z, VarInt);
#if PROTOCOL_VERSION > 722 /* > 1.15.2 */ && PROTOCOL_VERSION < 757 /* < 1.18 */
        SERIALIZED_FIELD(TrustEdges, bool);
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        SERIALIZED_FIELD(SkyYMask, VarInt);
        SERIALIZED_FIELD(BlockYMask, VarInt);
        SERIALIZED_FIELD(EmptySkyYMask, VarInt);
        SERIALIZED_FIELD(EmptyBlockYMask, VarInt);
        SERIALIZED_FIELD(SkyUpdates, Internal::CustomType<std::vector<std::vector<char>>, &THIS::ReadSkyUpdates, &THIS::WriteSkyUpdates>);
        SERIALIZED_FIELD(BlockUpdates, Internal::CustomType<std::vector<std::vector<char>>, &THIS::ReadBlockUpdates, &THIS::WriteBlockUpdates>);
#elif PROTOCOL_VERSION < 757 /* < 1.18 */
        SERIALIZED_FIELD(SkyYMask, std::vector<unsigned long long int>);
        SERIALIZED_FIELD(BlockYMask, std::vector<unsigned long long int>);
        SERIALIZED_FIELD(EmptySkyYMask, std::vector<unsigned long long int>);
        SERIALIZED_FIELD(EmptyBlockYMask, std::vector<unsigned long long int>);
        SERIALIZED_FIELD(SkyUpdates, std::vector<std::vector<char>>);
        SERIALIZED_FIELD(BlockUpdates, std::vector<std::vector<char>>);
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
        SERIALIZED_FIELD(LightData, ClientboundLightUpdatePacketData);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft

#endif
