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

#if PROTOCOL_VERSION < 735 /* < 1.16 */
        DECLARE_FIELDS(
            (VarInt, VarInt, VarInt,   VarInt,     VarInt,        VarInt,          std::vector<std::vector<char>>, std::vector<std::vector<char>>),
            (X,      Z,      SkyYMask, BlockYMask, EmptySkyYMask, EmptyBlockYMask, SkyUpdates,                     BlockUpdates)
        );
#elif PROTOCOL_VERSION < 755 /* < 1.17 */
        DECLARE_FIELDS(
            (VarInt, VarInt, bool,       VarInt,   VarInt,     VarInt,        VarInt,          std::vector<std::vector<char>>, std::vector<std::vector<char>>),
            (X,      Z,      TrustEdges, SkyYMask, BlockYMask, EmptySkyYMask, EmptyBlockYMask, SkyUpdates,                     BlockUpdates)
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

        DECLARE_SERIALIZE;

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

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetX(ReadData<VarInt>(iter, length));
            SetZ(ReadData<VarInt>(iter, length));
#if PROTOCOL_VERSION < 757 /* < 1.18 */
#if PROTOCOL_VERSION > 722 /* > 1.15.2 */
            SetTrustEdges(ReadData<bool>(iter, length));
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            SetSkyYMask(ReadData<VarInt>(iter, length));
            SetBlockYMask(ReadData<VarInt>(iter, length));
            SetEmptySkyYMask(ReadData<VarInt>(iter, length));
            SetEmptyBlockYMask(ReadData<VarInt>(iter, length));
#else
            SetSkyYMask(ReadData<std::vector<unsigned long long int>>(iter, length));
            SetBlockYMask(ReadData<std::vector<unsigned long long int>>(iter, length));
            SetEmptySkyYMask(ReadData<std::vector<unsigned long long int>>(iter, length));
            SetEmptyBlockYMask(ReadData<std::vector<unsigned long long int>>(iter, length));
#endif

#if PROTOCOL_VERSION < 755 /* < 1.17 */
            std::vector<std::vector<char>> sky_updates;
            for (int i = 0; i < 18; ++i)
            {
                if ((GetSkyYMask() >> i) & 1)
                {
                    sky_updates.push_back(ReadData<std::vector<char>>(iter, length)); // Should always contain 2048 chars
                }
            }
            SetSkyUpdates(sky_updates);

            std::vector<std::vector<char>> block_updates;
            for (int i = 0; i < 18; ++i)
            {
                if ((GetBlockYMask() >> i) & 1)
                {
                    block_updates.push_back(ReadData<std::vector<char>>(iter, length)); // Should always contain 2048 chars
                }
            }
            SetBlockUpdates(block_updates);
#else
            SetSkyUpdates(ReadData<std::vector<std::vector<char>>>(iter, length)); // Subvectors should always contain 2048 chars
            SetBlockUpdates(ReadData<std::vector<std::vector<char>>>(iter, length)); // Subvectors should always contain 2048 chars
#endif
#else
            SetLightData(ReadData<ClientboundLightUpdatePacketData>(iter, length));
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(GetX(), container);
            WriteData<VarInt>(GetZ(), container);
#if PROTOCOL_VERSION < 757 /* < 1.18 */
#if PROTOCOL_VERSION > 722 /* > 1.15.2 */
            WriteData<bool>(GetTrustEdges(), container);
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            WriteData<VarInt>(GetSkyYMask(), container);
            WriteData<VarInt>(GetBlockYMask(), container);
            WriteData<VarInt>(GetEmptySkyYMask(), container);
            WriteData<VarInt>(GetEmptyBlockYMask(), container);
#else
            WriteData<std::vector<unsigned long long int>>(GetSkyYMask(), container);
            WriteData<std::vector<unsigned long long int>>(GetBlockYMask(), container);
            WriteData<std::vector<unsigned long long int>>(GetEmptySkyYMask(), container);
            WriteData<std::vector<unsigned long long int>>(GetEmptyBlockYMask(), container);
#endif

#if PROTOCOL_VERSION < 755 /* < 1.17 */
            for (const auto& v : GetSkyUpdates())
            {
                WriteData<std::vector<char>>(v, container);
            }
#else
            WriteData<std::vector<std::vector<char>>>(GetSkyUpdates(), container);
#endif

#if PROTOCOL_VERSION < 755 /* < 1.17 */
            for (const auto& v : GetBlockUpdates())
            {
                WriteData<std::vector<char>>(v, container);
            }
#else
            WriteData<std::vector<std::vector<char>>>(GetBlockUpdates(), container);
#endif
#else
            WriteData<ClientboundLightUpdatePacketData>(GetLightData(), container);
#endif
        }

    };
} //ProtocolCraft

#endif
