#pragma once

#include "protocolCraft/BasePacket.hpp"

#if PROTOCOL_VERSION > 776 /* > 26.2 */
#include <array>
#include <optional>
#include <utility>
#include <vector>
#endif

namespace ProtocolCraft
{
    class ClientboundMoveEntityPacketPos : public BasePacket<ClientboundMoveEntityPacketPos>
    {
    public:
        static constexpr std::string_view packet_name = "Move Entity Pos";

#if PROTOCOL_VERSION > 776 /* > 26.2 */
        DEFINE_CONDITION(IsSingleStep, GetStepCount() <= 0);

    private:
        std::optional<std::vector<std::pair<int, std::array<short, 3>>>> ReadStepped(ReadIterator& iter, size_t& length) const
        {
            const int step_count = GetStepCount();
            if (step_count > 0)
            {
                std::vector<std::pair<int, std::array<short, 3>>> deltas(step_count);
                for (int i = 0; i < step_count; ++i)
                {
                    deltas[i].first = ReadData<VarInt>(iter, length);
                    deltas[i].second = ReadData<std::array<short, 3>>(iter, length);
                }
                return deltas;
            }
            return std::nullopt;
        }

        void WriteStepped(const std::optional<std::vector<std::pair<int, std::array<short, 3>>>>& stepped_deltas_, WriteContainer& c) const
        {
            if (stepped_deltas_.has_value())
            {
                const std::vector<std::pair<int, std::array<short, 3>>>& v = stepped_deltas_.value();
                for (size_t i = 0; i < v.size(); ++i)
                {
                    WriteData<VarInt>(v[i].first, c);
                    WriteData<std::array<short, 3>>(v[i].second, c);
                }
            }
        }
#endif

        SERIALIZED_FIELD(EntityId, VarInt);
#if PROTOCOL_VERSION < 107 /* < 1.9 */
        SERIALIZED_FIELD(XA, char);
        SERIALIZED_FIELD(YA, char);
        SERIALIZED_FIELD(ZA, char);
        SERIALIZED_FIELD(OnGround, bool);
#elif PROTOCOL_VERSION < 777 /* < 26.3 */
        SERIALIZED_FIELD(XA, short);
        SERIALIZED_FIELD(YA, short);
        SERIALIZED_FIELD(ZA, short);
        SERIALIZED_FIELD(OnGround, bool);
#else
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Properties, VarInt);
        SERIALIZED_FIELD(SingleDelta, Internal::Conditioned<std::array<short, 3>, &THIS::IsSingleStep>);
        SERIALIZED_FIELD(SteppedDeltas, Internal::CustomType<std::optional<std::vector<std::pair<int, std::array<short, 3>>>>, &THIS::ReadStepped, &THIS::WriteStepped, nullptr>);
#endif

#if PROTOCOL_VERSION > 776 /* > 26.2 */
    public:
        bool GetOnGround() const
        {
            return static_cast<bool>(Properties & 1);
        }

        THIS& SetOnGround(const bool b)
        {
            Properties = (Properties & ~1) | static_cast<int>(b);
            return *this;
        }

        int GetStepCount() const
        {
            return Properties >> 1;
        }

        THIS& SetStepCount(const int i)
        {
            Properties = (Properties & 1) | (i << 1);
            return *this;
        }
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
