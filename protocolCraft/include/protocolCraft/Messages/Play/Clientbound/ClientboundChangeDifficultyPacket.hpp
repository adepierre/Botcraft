#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundChangeDifficultyPacket : public BaseMessage<ClientboundChangeDifficultyPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x0D;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x0D;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x0D;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x0E;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
            return 0x0D;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x0D;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x0E;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x0E;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x0B;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x0B;
#elif PROTOCOL_VERSION == 761 // 1.19.3
            return 0x0B;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Change Difficulty";
        }

        virtual ~ClientboundChangeDifficultyPacket() override
        {

        }

        void SetDifficulty(const int difficulty_)
        {
            difficulty = difficulty_;
        }

#if PROTOCOL_VERSION >= 477
        void SetLocked(const bool locked_)
        {
            locked = locked_;
        }
#endif

        const int GetDifficulty() const
        {
            return difficulty;
        }

#if PROTOCOL_VERSION >= 477
        const bool GetLocked() const
        {
            return locked;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            difficulty = ReadData<unsigned char>(iter, length);
#if PROTOCOL_VERSION >= 477
            locked = ReadData<bool>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<unsigned char>((unsigned char)difficulty, container);
#if PROTOCOL_VERSION >= 477
            WriteData<bool>(locked, container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["difficulty"] = difficulty;
#if PROTOCOL_VERSION >= 477
            output["locked"] = locked;
#endif

            return output;
        }

    private:
        int difficulty;

#if PROTOCOL_VERSION >= 477
        bool locked;
#endif
    };
} //ProtocolCraft