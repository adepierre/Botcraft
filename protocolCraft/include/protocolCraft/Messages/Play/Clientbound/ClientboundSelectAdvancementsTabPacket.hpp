#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSelectAdvancementsTabPacket : public BaseMessage<ClientboundSelectAdvancementsTabPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x37;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x3A;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x3C;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x3D;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x3C;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x3C;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x40;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Select Advancement Tab";
        }

        virtual ~ClientboundSelectAdvancementsTabPacket() override
        {

        }

        void SetTab(const std::string& tab_)
        {
            tab = tab_;
        }


        const std::string& GetTab() const
        {
            return tab;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            const bool has_tab = ReadData<bool>(iter, length);
            if (has_tab)
            {
                tab = ReadData<std::string>(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<bool>(!tab.empty(), container);
            if (!tab.empty())
            {
                WriteData<std::string>(tab, container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            if (!tab.empty())
            {
                output["tab"] = tab;
            }

            return output;
        }

    private:
        std::string tab;

    };
} //ProtocolCraft