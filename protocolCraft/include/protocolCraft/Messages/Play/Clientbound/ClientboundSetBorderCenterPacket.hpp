#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetBorderCenterPacket : public BaseMessage<ClientboundSetBorderCenterPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x42;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Border Center";
        }

        virtual ~ClientboundSetBorderCenterPacket() override
        {

        }


        void SetNewCenterX(const double new_center_x_)
        {
            new_center_x = new_center_x_;
        }

        void SetNewCenterZ(const double new_center_z_)
        {
            new_center_z = new_center_z_;
        }


        const double GetNewCenterX() const
        {
            return new_center_x;
        }

        const double GetNewCenterZ() const
        {
            return new_center_z;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            new_center_x = ReadData<double>(iter, length);
            new_center_z = ReadData<double>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<double>(new_center_x, container);
            WriteData<double>(new_center_z, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["new_center_x"] = new_center_x;
            output["new_center_z"] = new_center_z;

            return output;
        }

    private:
        double new_center_x;
        double new_center_z;

    };
} //ProtocolCraft
#endif