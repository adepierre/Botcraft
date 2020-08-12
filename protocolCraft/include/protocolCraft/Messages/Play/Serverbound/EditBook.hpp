#pragma once

#if PROTOCOL_VERSION > 385
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class EditBook : public BaseMessage<EditBook>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x0B;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x0c;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x0C;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x0C;
#elif PROTOCOL_VERSION == 751 // 1.16.2
            return 0x0C;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Edit Book";
        }

        void SetNewBook(const Slot& new_book_)
        {
            new_book = new_book_;
        }

        void SetIsSigning(const bool is_signing_)
        {
            is_signing = is_signing_;
        }

#if PROTOCOL_VERSION > 393
        void SetHand(const int hand_)
        {
            hand = hand_;
        }
#endif


        const Slot& GetNewBook() const
        {
            return new_book;
        }

        const bool GetIsSigning() const
        {
            return is_signing;
        }

#if PROTOCOL_VERSION > 393
        const int GetHand() const
        {
            return hand;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            new_book.Read(iter, length);
            is_signing = ReadData<bool>(iter, length);
#if PROTOCOL_VERSION > 393
            hand = ReadVarInt(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            new_book.Write(container);
            WriteData<bool>(is_signing, container);
#if PROTOCOL_VERSION > 393
            WriteVarInt(hand, container);
#endif
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["new_book"] = new_book.Serialize();
            object["is_signing"] = picojson::value(is_signing);
#if PROTOCOL_VERSION > 393
            object["hand"] = picojson::value((double)hand);
#endif

            return value;
        }

    private:
        Slot new_book;
        bool is_signing;
#if PROTOCOL_VERSION > 393
        int hand;
#endif

    };
} //ProtocolCraft
#endif
