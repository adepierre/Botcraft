#pragma once

#if PROTOCOL_VERSION > 385
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundRenameItemPacket : public BaseMessage<ServerboundRenameItemPacket>
    {
    public:
#if   PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x1C;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498 || PROTOCOL_VERSION == 573 ||  \
      PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x1E;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736
        static constexpr int packet_id = 0x1F;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754 || PROTOCOL_VERSION == 755 ||  \
      PROTOCOL_VERSION == 756 || PROTOCOL_VERSION == 757 ||  \
      PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x20;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x22;
#elif PROTOCOL_VERSION == 760 || PROTOCOL_VERSION == 761 ||  \
      PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x23;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Rename Item";

        virtual ~ServerboundRenameItemPacket() override
        {

        }

        void SetName_(const std::string& name__)
        {
            name_ = name__;
        }


        const std::string& GetName_() const
        {
            return name_;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            name_ = ReadData<std::string>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(name_, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["name_"] = name_;

            return output;
        }

    private:
        std::string name_;

    };
} //ProtocolCraft
#endif
