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

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        void SetCriteria(const std::vector<Identifier>& criteria_)
        {
            criteria = criteria_;
        }
#endif

        void SetRequirements(const std::vector<std::vector<std::string> >& requirements_)
        {
            requirements = requirements_;
        }

#if PROTOCOL_VERSION > 762 /* > 1.19.4 */
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

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        const std::vector<Identifier>& GetCriteria() const
        {
            return criteria;
        }
#endif

        const std::vector<std::vector<std::string> >& GetRequirements() const
        {
            return requirements;
        }

#if PROTOCOL_VERSION > 762 /* > 1.19.4 */
        bool GetSendsTelemetryEvent() const
        {
            return sends_telemetry_event;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            parent_id = ReadData<std::optional<Identifier>>(iter, length);
            display_data = ReadData<std::optional<AdvancementDisplay>>(iter, length);
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            criteria = ReadData<std::vector<Identifier>>(iter, length);
#endif
            requirements = ReadData<std::vector<std::vector<std::string>>>(iter, length);
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */
            sends_telemetry_event = ReadData<bool>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::optional<Identifier>>(parent_id, container);
            WriteData<std::optional<AdvancementDisplay>>(display_data, container);
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            WriteData<std::vector<Identifier>>(criteria, container);
#endif
            WriteData<std::vector<std::vector<std::string>>>(requirements, container);
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */
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
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            output["criteria"] = criteria;
#endif
            output["requirements"] = requirements;
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */
            output["sends_telemetry_event"] = sends_telemetry_event;
#endif

            return output;
        }

    private:
        std::optional<Identifier> parent_id;
        std::optional<AdvancementDisplay> display_data;
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        std::vector<Identifier> criteria;
#endif
        std::vector<std::vector<std::string> > requirements;
#if PROTOCOL_VERSION > 762 /* > 1.19.4 */
        bool sends_telemetry_event = false;
#endif
    };
}
