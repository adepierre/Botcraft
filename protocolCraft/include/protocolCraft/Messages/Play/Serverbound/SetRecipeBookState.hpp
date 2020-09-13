#pragma once

#if PROTOCOL_VERSION > 736
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class SetRecipeBookState : public BaseMessage<SetRecipeBookState>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 // 1.16.2 or 1.16.3
            return 0x1F;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Recipe Book State";
        }

        void SetBookID(const int book_ID_)
        {
            book_ID = book_ID_;
        }

        void SetBookOpen(const bool book_open_)
        {
            book_open = book_open_;
        }

        void SetFilterActive(const bool filter_active_)
        {
            filter_active = filter_active_;
        }


        const int GetBookID() const
        {
            return book_ID;
        }

        const bool GetBookOpen() const
        {
            return book_open;
        }

        const int GetFilterActive() const
        {
            return filter_active;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            book_ID = ReadVarInt(iter, length);
            book_open = ReadData<bool>(iter, length);
            filter_active = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(book_ID, container);
            WriteData<bool>(book_open, container);
            WriteData<bool>(filter_active, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["book_ID"] = picojson::value((double)book_ID);
            object["book_open"] = picojson::value(book_open);
            object["filter_active"] = picojson::value(filter_active);
            

            return value;
        }

    private:
        int book_ID;
        bool book_open;
        bool filter_active;
    };
} //ProtocolCraft
#endif