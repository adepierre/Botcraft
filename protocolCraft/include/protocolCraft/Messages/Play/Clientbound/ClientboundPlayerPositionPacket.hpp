#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerPositionPacket : public BaseMessage<ClientboundPlayerPositionPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x2F;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x32;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x35;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x36;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x35;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x34;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x38;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x36;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x39;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x38;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x3C;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3 */
        static constexpr int packet_id = 0x3E;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Player Position";

        virtual ~ClientboundPlayerPositionPacket() override
        {

        }

        void SetX(const double x_)
        {
            x = x_;
        }

        void SetY(const double y_)
        {
            y = y_;
        }

        void SetZ(const double z_)
        {
            z = z_;
        }

        void SetYRot(const float yRot_)
        {
            yRot = yRot_;
        }

        void SetXRot(const float xRot_)
        {
            xRot = xRot_;
        }

        void SetRelativeArguments(const char relative_arguments_)
        {
            relative_arguments = relative_arguments_;
        }

        void SetId_(const int id__)
        {
            id_ = id__;
        }

#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 762 /* < 1.19.4 */
        void SetDismountVehicle(const bool dismount_vehicle_)
        {
            dismount_vehicle = dismount_vehicle_;
        }
#endif


        double GetX() const
        {
            return x;
        }

        double GetY() const
        {
            return y;
        }

        double GetZ() const
        {
            return z;
        }

        float GetYRot() const
        {
            return yRot;
        }

        float GetXRot() const
        {
            return xRot;
        }

        char GetRelativeArguments() const
        {
            return relative_arguments;
        }

        int GetId_() const
        {
            return id_;
        }

#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 762 /* < 1.19.4 */
        bool GetDismountVehicle() const
        {
            return dismount_vehicle;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            x = ReadData<double>(iter, length);
            y = ReadData<double>(iter, length);
            z = ReadData<double>(iter, length);
            yRot = ReadData<float>(iter, length);
            xRot = ReadData<float>(iter, length);
            relative_arguments = ReadData<char>(iter, length);
            id_ = ReadData<VarInt>(iter, length);
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 762 /* < 1.19.4 */
            dismount_vehicle = ReadData<bool>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<double>(x, container);
            WriteData<double>(y, container);
            WriteData<double>(z, container);
            WriteData<float>(yRot, container);
            WriteData<float>(xRot, container);
            WriteData<char>(relative_arguments, container);
            WriteData<VarInt>(id_, container);
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 762 /* < 1.19.4 */
            WriteData<bool>(dismount_vehicle, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["x"] = x;
            output["y"] = y;
            output["z"] = z;
            output["yRot"] = yRot;
            output["xRot"] = xRot;
            output["relative_arguments"] = relative_arguments;
            output["id_"] = id_;
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 762 /* < 1.19.4 */
            output["dismount_vehicle"] = dismount_vehicle;
#endif

            return output;
        }

    private:
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
        float yRot = 0.0f;
        float xRot = 0.0f;
        char relative_arguments = 0;
        int id_ = 0;
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 762 /* < 1.19.4 */
        bool dismount_vehicle = false;
#endif
    };
}
