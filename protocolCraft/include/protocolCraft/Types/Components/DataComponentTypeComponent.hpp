#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeComponent : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeComponent()
            {

            }


            const Chat& GetComponent() const
            {
                return component;
            }


            void SetComponent(const Chat& component_)
            {
                component = component_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                component = ReadData<Chat>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<Chat>(component, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["name"] = component;

                return output;
            }

        private:
            Chat component;

        };
    }
}
#endif
