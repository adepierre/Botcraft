#include "botcraft/Game/Entities/Entity.hpp"

namespace Botcraft
{
    Entity::Entity()
    {
        eid = 0;
        position = Vector3<double>(0.0, 0.0, 0.0);
        yaw = 0.0f;
        pitch = 0.0f;
        speed = Vector3<double>(0.0, 0.0, 0.0);

        on_ground = true;
    }

    const int Entity::GetEID() const
    {
        return eid;
    }

    const Vector3<double>& Entity::GetPosition() const
    {
        return position;
    }

    const double Entity::GetX() const
    {
        return position.x;
    }

    const double Entity::GetY() const
    {
        return position.y;
    }

    const double Entity::GetZ() const
    {
        return position.z;
    }

    const float Entity::GetYaw() const
    {
        return yaw;
    }

    const float Entity::GetPitch() const
    {
        return pitch;
    }

    const Vector3<double>& Entity::GetSpeed() const
    {
        return speed;
    }

    const bool Entity::GetOnGround() const
    {
        return on_ground;
    }

    const AABB Entity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + 0.25, position.z), Vector3<double>(0.25, 0.25, 0.25));
    }


    void Entity::SetEID(const int eid_)
    {
        eid = eid_;
    }

    void Entity::SetPosition(const Vector3<double>& pos)
    {
        position = pos;
    }

    void Entity::SetX(const double x)
    {
        position.x = x;
    }

    void Entity::SetY(const double y)
    {
        position.y = y;
    }

    void Entity::SetZ(const double z)
    {
        position.z = z;
    }

    void Entity::SetYaw(const float yaw_)
    {
        yaw = yaw_;
    }

    void Entity::SetPitch(const float pitch_)
    {
        pitch = pitch_;
    }

    void Entity::SetSpeed(const Vector3<double> &speed_)
    {
        speed = speed_;
    }

    void Entity::SetSpeedX(const double speed_x)
    {
        speed.x = speed_x;
    }

    void Entity::SetSpeedY(const double speed_y)
    {
        speed.y = speed_y;
    }

    void Entity::SetSpeedZ(const double speed_z)
    {
        speed.z = speed_z;
    }

    void Entity::SetOnGround(const bool on_ground_)
    {
        on_ground = on_ground_;
    }
} //Botcraft