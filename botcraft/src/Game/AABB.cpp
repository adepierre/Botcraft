#include "botcraft/Game/AABB.hpp"

#include <algorithm>

namespace Botcraft
{
    AABB::AABB(const Vector3<double>& center_, const Vector3<double>& half_size_)
    {
        center = center_;
        half_size = half_size_;
    }

    AABB::~AABB()
    {

    }

    const Vector3<double> AABB::GetMin() const
    {
        return center - half_size;
    }

    const Vector3<double> AABB::GetMax() const
    {
        return center + half_size;
    }

    const Vector3<double>& AABB::GetCenter() const
    {
        return center;
    }

    const Vector3<double>& AABB::GetHalfSize() const
    {
        return half_size;
    }

    const bool AABB::Collide(const AABB& b) const
    {
        bool x = std::abs(center.x - b.center.x) <= (half_size.x + b.half_size.x);
        bool y = std::abs(center.y - b.center.y) <= (half_size.y + b.half_size.y);
        bool z = std::abs(center.z - b.center.z) <= (half_size.z + b.half_size.z);

        return x && y && z;
    }

    // Inspired by https://www.gamedev.net/articles/programming/general-and-gameplay-programming/swept-aabb-collision-detection-and-response-r3084/
    const double AABB::SweptCollide(const Vector3<double>& speed, const AABB& b, Vector3<double>& normal) const
    {
        // Distance between the closest/furthest faces
        //of the current box and the tested box
        Vector3<double> entry_dist, exit_dist;

        for (int i = 0; i < 3; ++i)
        {
            if (speed[i] > 0.0)
            {
                entry_dist[i] = (b.center[i] - b.half_size[i]) - (center[i] + half_size[i]);
                exit_dist[i] = (b.center[i] + b.half_size[i]) - (center[i] - half_size[i]);
            }
            else
            {
                entry_dist[i] = (b.center[i] + b.half_size[i]) - (center[i] - half_size[i]);
                exit_dist[i] = (b.center[i] - b.half_size[i]) - (center[i] + half_size[i]);
            }
        }

        // Find fraction of speed for entering
        // and leaving collisions
        Vector3<double> time_entry_axis, time_exit_axis;
        for (int i = 0; i < 3; ++i)
        {
            if (speed[i] == 0.0)
            {
                // Because we do NOT want to divide by 0
                time_entry_axis[i] = -std::numeric_limits<double>::infinity();
                time_exit_axis[i] = std::numeric_limits<double>::infinity();
            }
            else
            {
                time_entry_axis[i] = entry_dist[i] / speed[i];
                time_exit_axis[i] = exit_dist[i] / speed[i];
            }

            if (time_entry_axis[i] > 1.0)
            {
                time_entry_axis[i] = -std::numeric_limits<double>::infinity();
            }
        }
        
        double time_entry = std::max({ time_entry_axis.x, time_entry_axis.y, time_entry_axis.z });
        double time_exit = std::min({ time_exit_axis.x, time_exit_axis.y, time_exit_axis.z });

        // If no collision
        if (time_entry > time_exit ||
            (time_entry_axis.x < 0.0 && time_entry_axis.y < 0.0 && time_entry_axis.z < 0.0))
        {
            return 1.0;
        }
        
        
        // If we are here, there is a collision, set the normal
        // entry_dist.x is the highest value
        if (time_entry_axis.x > time_entry_axis.y && time_entry_axis.x > time_entry_axis.z)
        {
            if (entry_dist.x < 0.0)
            {
                normal = Vector3<double>(1.0, 0.0, 0.0);
            }
            else
            {
                normal = Vector3<double>(-1.0, 0.0, 0.0);
            }
        }
        // entry_dist.y is the highest value
        else if (time_entry_axis.y > time_entry_axis.x && time_entry_axis.y > time_entry_axis.z)
        {
            if (entry_dist.y < 0.0)
            {
                normal = Vector3<double>(0.0, 1.0, 0.0);
            }
            else
            {
                normal = Vector3<double>(0.0, -1.0, 0.0);
            }
        }
        // entry_dist.z is the highest value
        else
        {
            if (entry_dist.z < 0.0)
            {
                normal = Vector3<double>(0.0, 0.0, 1.0);
            }
            else
            {
                normal = Vector3<double>(0.0, 0.0, -1.0);
            }
        }

        return time_entry;
    }

    const bool AABB::Intersect(const Vector3<double>& origin, const Vector3<double>& direction) const
    {
        double tmin = -std::numeric_limits<float>::max();
        double tmax = std::numeric_limits<float>::max();

        Vector3<double> t1 = center - half_size - origin;
        Vector3<double> t2 = center + half_size - origin;

        for (int i = 0; i < 3; ++i)
        {
            if (direction[i] != 0.0)
            {
                double ti1 = t1[i] / direction[i];
                double ti2 = t2[i] / direction[i];

                tmin = std::max(tmin, std::min(ti1, ti2));
                tmax = std::min(tmax, std::max(ti1, ti2));
            }
        }

        return tmin <= tmax;
    }

    bool AABB::operator<(const AABB& other) const
    {
        return center < other.center ||
            (center == other.center && half_size < other.half_size);
    }

    bool AABB::operator==(const AABB& other) const
    {
        return center == other.center && half_size == other.half_size;
    }
} // Botcraft
