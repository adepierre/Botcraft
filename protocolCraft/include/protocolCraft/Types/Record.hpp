#pragma once

#if PROTOCOL_VERSION < 739
#include <string>

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class Record : public NetworkType
    {
    public:
        virtual ~Record() override
        {

        }

        void SetHorizontalPosition(const unsigned char h)
        {
            horizontal_position = h;
        }
        
        void SetYCoordinate(const unsigned char y)
        {
            y_coordinate = y;
        }
        
        void SetBlockId(const int i)
        {
            block_id = i;
        }
    
    
        unsigned char GetHorizontalPosition() const
        {
            return horizontal_position;
        }
        
        unsigned char GetYCoordinate() const
        {
            return y_coordinate;
        }
        
        int GetBlockId() const
        {
            return block_id;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            horizontal_position = ReadData<unsigned char>(iter, length);
            y_coordinate = ReadData<unsigned char>(iter, length);
            block_id = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<unsigned char>(horizontal_position, container);
            WriteData<unsigned char>(y_coordinate, container);
            WriteData<VarInt>(block_id, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["horizontal_position"] = horizontal_position;
            output["y_coordinate"] = y_coordinate;
            output["block_id"] = block_id;

            return output;
        }

    private:
        unsigned char horizontal_position;
        unsigned char y_coordinate;
        int block_id;
    };
}
#endif
