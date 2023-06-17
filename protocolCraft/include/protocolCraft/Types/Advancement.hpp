#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/AdvancementDisplay.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class Advancement : public NetworkType
    {
    public:
        virtual ~Advancement() override
        {

        }


        void SetParentId(const std::optional<Identifier>& parent_id_)
        {
            parent_id = parent_id_;
        }

        void SetDisplayData(const std::optional<AdvancementDisplay>& display_data_)
        {
            display_data = display_data_;
        }

        void SetCriteria(const std::vector<Identifier>& criteria_)
        {
            criteria = criteria_;
        }
        
        void SetRequirements(const std::vector<std::vector<std::string> >& requirements_)
        {
            requirements = requirements_;
        }

#if PROTOCOL_VERSION > 762
        void SetSendsTelemetryEvent(const bool sends_telemetry_event_)
        {
            sends_telemetry_event = sends_telemetry_event_;
        }
#endif


        const std::optional<Identifier>& GetParentId() const
        {
            return parent_id;
        }

        const std::optional<AdvancementDisplay>& GetDisplayData() const
        {
            return display_data;
        }

        const std::vector<Identifier>& GetCriteria() const
        {
            return criteria;
        }
        
        const std::vector<std::vector<std::string> >& GetRequirements() const
        {
            return requirements;
        }

#if PROTOCOL_VERSION > 762
        bool GetSendsTelemetryEvent() const
        {
            return sends_telemetry_event;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            parent_id = ReadOptional<Identifier>(iter, length);
            display_data = ReadOptional<AdvancementDisplay>(iter, length);
            criteria = ReadVector<Identifier>(iter, length);
            requirements = ReadVector<std::vector<std::string>>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    return ReadVector<std::string>(i, l);
                }
            );
#if PROTOCOL_VERSION > 762
            sends_telemetry_event = ReadData<bool>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteOptional<Identifier>(parent_id, container);
            WriteOptional<AdvancementDisplay>(display_data, container);
            WriteVector<Identifier>(criteria, container);
            WriteVector<std::vector<std::string>>(requirements, container,
                [](const std::vector<std::string>& v, WriteContainer& c)
                {
                    WriteVector<std::string>(v, c);
                }
            );
#if PROTOCOL_VERSION > 762
            WriteData<bool>(sends_telemetry_event, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            if (parent_id.has_value())
            {
                output["parent_id"] = parent_id.value();
            }
            if (display_data.has_value())
            {
                output["display_data"] = display_data.value();
            }
            output["criteria"] = criteria;
            output["requirements"] = requirements;
#if PROTOCOL_VERSION > 762
            output["sends_telemetry_event"] = sends_telemetry_event;
#endif

            return output;
        }

    private:
        std::optional<Identifier> parent_id;
        std::optional<AdvancementDisplay> display_data;
        std::vector<Identifier> criteria;
        std::vector<std::vector<std::string> > requirements;
#if PROTOCOL_VERSION > 762
        bool sends_telemetry_event = false;
#endif
    };
}
