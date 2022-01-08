#if PROTOCOL_VERSION > 404
#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class PandaEntity : public AnimalEntity
    {
    protected:
        static constexpr int metadata_count = 6;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        PandaEntity();
        virtual ~PandaEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual AABB GetCollider() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual nlohmann::json Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

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

    };
}
#endif
