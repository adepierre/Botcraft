#pragma once

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/TamableAnimalEntity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    class OcelotEntity : public AnimalEntity
#else
    class OcelotEntity : public TamableAnimalEntity
#endif
    {
    private:
        static constexpr std::array metadata_names{
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
            std::string_view("data_trusting"),
#else
            std::string_view("data_type_id"),
#endif
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        OcelotEntity();
        virtual ~OcelotEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        bool GetDataTrusting() const;

        void SetDataTrusting(const bool data_trusting);
#else
        int GetDataTypeId() const;

        void SetDataTypeId(const int data_type_id);
#endif

        // Attribute stuff
        double GetAttributeAttackDamageValue() const;

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
