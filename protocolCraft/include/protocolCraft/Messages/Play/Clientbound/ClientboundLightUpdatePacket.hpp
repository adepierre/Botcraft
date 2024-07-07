#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
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

#if PROTOCOL_VERSION < 735 /* < 1.16 */
        DECLARE_FIELDS(
            (VarInt, VarInt, VarInt,   VarInt,     VarInt,        VarInt,          Internal::CustomType<std::vector<std::vector<char>>, &THIS::ReadSkyUpdates, &THIS::WriteSkyUpdates>, Internal::CustomType<std::vector<std::vector<char>>, &THIS::ReadBlockUpdates, &THIS::WriteBlockUpdates>),
            (X,      Z,      SkyYMask, BlockYMask, EmptySkyYMask, EmptyBlockYMask, SkyUpdates,                                                                                          BlockUpdates)
        );
#elif PROTOCOL_VERSION < 755 /* < 1.17 */
        DECLARE_FIELDS(
            (VarInt, VarInt, bool,       VarInt,   VarInt,     VarInt,        VarInt,          Internal::CustomType<std::vector<std::vector<char>>, &THIS::ReadSkyUpdates, &THIS::WriteSkyUpdates>, Internal::CustomType<std::vector<std::vector<char>>, &THIS::ReadBlockUpdates, &THIS::WriteBlockUpdates>),
            (X,      Z,      TrustEdges, SkyYMask, BlockYMask, EmptySkyYMask, EmptyBlockYMask, SkyUpdates,                                                                                          BlockUpdates)
        );
#elif PROTOCOL_VERSION < 757 /* < 1.18 */
        DECLARE_FIELDS(
            (VarInt, VarInt, bool,       std::vector<unsigned long long int>, std::vector<unsigned long long int>, std::vector<unsigned long long int>, std::vector<unsigned long long int>,          std::vector<std::vector<char>>, std::vector<std::vector<char>>),
            (X,      Z,      TrustEdges, SkyYMask,                            BlockYMask,                          EmptySkyYMask,                       EmptyBlockYMask,                              SkyUpdates,                     BlockUpdates)
        );
#else
        DECLARE_FIELDS(
            (VarInt, VarInt, ClientboundLightUpdatePacketData),
            (X,      Z,      LightData)
        );
#endif

        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(X);
        GETTER_SETTER(Z);
#if PROTOCOL_VERSION < 757 /* < 1.18 */
        GETTER_SETTER(SkyYMask);
        GETTER_SETTER(BlockYMask);
        GETTER_SETTER(EmptySkyYMask);
        GETTER_SETTER(EmptyBlockYMask);
        GETTER_SETTER(SkyUpdates);
        GETTER_SETTER(BlockUpdates);
#endif
#if PROTOCOL_VERSION > 722 /* > 1.15.2 */ && PROTOCOL_VERSION < 757 /* < 1.18 */
        GETTER_SETTER(TrustEdges);
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
        GETTER_SETTER(LightData);
#endif
    };
} //ProtocolCraft

#endif
