#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class PandaEntity : public AnimalEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("unhappy_counter"),
            std::string_view("sneeze_counter"),
            std::string_view("eat_counter"),
            std::string_view("main_gene_id"),
            std::string_view("hidden_gene_id"),
            std::string_view("data_id_flags"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        PandaEntity();
        virtual ~PandaEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        int GetUnhappyCounter() const;
        int GetSneezeCounter() const;
        int GetEatCounter() const;
        char GetMainGeneId() const;
        char GetHiddenGeneId() const;
        char GetDataIdFlags() const;

        void SetUnhappyCounter(const int unhappy_counter);
        void SetSneezeCounter(const int sneeze_counter);
        void SetEatCounter(const int eat_counter);
        void SetMainGeneId(const char main_gene_id);
        void SetHiddenGeneId(const char hidden_gene_id);
        void SetDataIdFlags(const char data_id_flags);

        // Attribute stuff
        double GetAttributeAttackDamageValue() const;

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
