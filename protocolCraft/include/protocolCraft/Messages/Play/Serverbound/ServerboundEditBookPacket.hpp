#pragma once

#if PROTOCOL_VERSION > 385
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class ServerboundEditBookPacket : public BaseMessage<ServerboundEditBookPacket>
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
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x0C;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Edit Book";
        }

        virtual ~ServerboundEditBookPacket() override
        {

        }

        void SetBook(const Slot& book_)
        {
            book = book_;
        }

        void SetSigning(const bool signing_)
        {
            signing = signing_;
        }

#if PROTOCOL_VERSION > 393
        void SetSlot(const int slot_)
        {
            slot = slot_;
        }
#endif


        const Slot& GetBook() const
        {
            return book;
        }

        const bool GetSigning() const
        {
            return signing;
        }

#if PROTOCOL_VERSION > 393
        const int GetSlot() const
        {
            return slot;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            book.Read(iter, length);
            signing = ReadData<bool>(iter, length);
#if PROTOCOL_VERSION > 393
            slot = ReadVarInt(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            book.Write(container);
            WriteData<bool>(signing, container);
#if PROTOCOL_VERSION > 393
            WriteVarInt(slot, container);
#endif
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["book"] = book.Serialize();
            object["signing"] = picojson::value(signing);
#if PROTOCOL_VERSION > 393
            object["slot"] = picojson::value((double)slot);
#endif

            return value;
        }

    private:
        Slot book;
        bool signing;
#if PROTOCOL_VERSION > 393
        int slot;
#endif

    };
} //ProtocolCraft
#endif
