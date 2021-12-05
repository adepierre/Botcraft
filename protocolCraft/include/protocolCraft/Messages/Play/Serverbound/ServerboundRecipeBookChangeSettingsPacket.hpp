#pragma once

#if PROTOCOL_VERSION > 736
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundRecipeBookChangeSettingsPacket : public BaseMessage<ServerboundRecipeBookChangeSettingsPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x1E;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x1E;
#elif PROTOCOL_VERSION == 757 // 1.18
            return 0x1E;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Recipe Book Change Settings";
        }

        virtual ~ServerboundRecipeBookChangeSettingsPacket() override
        {

        }

        void SetBookType(const int book_type_)
        {
            book_type = book_type_;
        }

        void SetIsOpen(const bool is_open_)
        {
            is_open = is_open_;
        }

        void SetIsFiltering(const bool is_filtering_)
        {
            is_filtering = is_filtering_;
        }


        const int GetBookType() const
        {
            return book_type;
        }

        const bool GetIsOpen() const
        {
            return is_open;
        }

        const int GetIsFiltering() const
        {
            return is_filtering;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            book_type = ReadData<VarInt>(iter, length);
            is_open = ReadData<bool>(iter, length);
            is_filtering = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(book_type, container);
            WriteData<bool>(is_open, container);
            WriteData<bool>(is_filtering, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["book_type"] = book_type;
            output["is_open"] = is_open;
            output["is_filtering"] = is_filtering;
            

            return output;
        }

    private:
        int book_type;
        bool is_open;
        bool is_filtering;
    };
} //ProtocolCraft
#endif