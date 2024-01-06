#pragma once

#include <ostream>
#include <cassert>
#include <cmath>

#include "protocolCraft/Types/NetworkPosition.hpp"

namespace Botcraft
{
    template <typename T>
    struct Vector3
    {
        Vector3(const T& v = 0)
        {
            x = v;
            y = v;
            z = v;
        }

        Vector3(const T& x_, const T& y_, const T& z_)
        {
            x = x_;
            y = y_;
            z = z_;
        }

        Vector3(const ProtocolCraft::NetworkPosition& position)
        {
            x = position.GetX();
            y = position.GetY();
            z = position.GetZ();
        }

        template <typename U>
        Vector3(const Vector3<U>& position)
        {
            x = static_cast<T>(position.x);
            y = static_cast<T>(position.y);
            z = static_cast<T>(position.z);
        }

        Vector3(const std::vector<T>& v)
        {
            assert(v.size() == 3);
            x = v[0];
            y = v[1];
            z = v[2];
        }

        Vector3(const std::array<T, 3>& v)
        {
            x = v[0];
            y = v[1];
            z = v[2];
        }

        T x;
        T y;
        T z;

        Vector3 operator+(const Vector3& a) const
        {
            return Vector3(a.x + x, a.y + y, a.z + z);
        }

        Vector3 operator-(const Vector3& a) const
        {
            return Vector3(x - a.x, y - a.y, z - a.z);
        }

        Vector3 operator*(const Vector3& v) const
        {
            return Vector3(x * v.x, y * v.y, z * v.z);
        }

        Vector3 operator/(const Vector3& v) const
        {
            return Vector3(x / v.x, y / v.y, z / v.z);
        }

        bool operator==(const Vector3& a) const
        {
            return (x == a.x) && (y == a.y) && (z == a.z);
        }

        bool operator!=(const Vector3& a) const
        {
            return (x != a.x) || (y != a.y) || (z != a.z);
        }

        bool operator<(const Vector3& a) const
        {
            return (x < a.x) ||
                (x == a.x && y < a.y) ||
                (x == a.x && y == a.y && z < a.z);
        }

        Vector3 operator*(const T d) const
        {
            return Vector3(x * d, y * d, z * d);
        }

        Vector3 operator-(const T d) const
        {
            return Vector3(x - d, y - d, z - d);
        }

        Vector3 operator+(const T d) const
        {
            return Vector3(x + d, y + d, z + d);
        }

        Vector3 operator/(const T d) const
        {
            return Vector3(x / d, y / d, z / d);
        }

        Vector3& operator+= (const Vector3& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        Vector3& operator+= (const T v)
        {
            x += v;
            y += v;
            z += v;
            return *this;
        }

        Vector3& operator-= (const Vector3& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        Vector3& operator-= (const T v)
        {
            x -= v;
            y -= v;
            z -= v;
            return *this;
        }

        Vector3& operator*= (const Vector3& v)
        {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            return *this;
        }

        Vector3& operator*= (const T v)
        {
            x *= v;
            y *= v;
            z *= v;
            return *this;
        }

        Vector3& operator/= (const Vector3& v)
        {
            x /= v.x;
            y /= v.y;
            z /= v.z;
            return *this;
        }

        Vector3& operator/= (const T v)
        {
            x /= v;
            y /= v;
            z /= v;
            return *this;
        }

        double dot(const Vector3& v) const
        {
            double output = 0.0;
            output += x * v.x;
            output += y * v.y;
            output += z * v.z;
            return output;
        }

        double SqrDist(const Vector3& v) const
        {
            return (x - v.x) * (x - v.x)
                 + (y - v.y) * (y - v.y)
                 + (z - v.z) * (z - v.z);
        }

        Vector3 Abs() const
        {
            return Vector3(
                std::abs(x),
                std::abs(y),
                std::abs(z)
            );
        }

        T& operator[] (const int i)
        {
            assert(i > -1);
            assert(i < 3);
            switch (i)
            {
            case 0:
                return x;
                break;
            case 1:
                return y;
                break;
            case 2:
                return z;
                break;
            }
            // This doesn't happen
            return x;
        }

        const T& operator[] (const int i) const
        {
            assert(i > -1);
            assert(i < 3);
            switch (i)
            {
            case 0:
                return x;
                break;
            case 1:
                return y;
                break;
            case 2:
                return z;
                break;
            }
            // This doesn't happen
            return x;
        }

        void Normalize()
        {
            const double norm = std::sqrt(SqrNorm());
            x /= norm;
            y /= norm;
            z /= norm;
        }

        double SqrNorm() const
        {
            return x * x + y * y + z * z;
        }

        friend std::ostream& operator << (std::ostream& o, const Vector3& vec)
        {
            o << "(" << vec.x << "," << vec.y << "," << vec.z << ")";
            return o;
        }

        ProtocolCraft::Json::Value Serialize() const
        {
            return ProtocolCraft::Json::Value({ x, y, z });
        }

        ProtocolCraft::NetworkPosition ToNetworkPosition() const
        {
            ProtocolCraft::NetworkPosition output;
            output.SetX(x);
            output.SetY(y);
            output.SetZ(z);

            return output;
        }
    };
    typedef Vector3<int> Position;
} // Botcraft

namespace std
{
    template <typename T>
    struct hash<Botcraft::Vector3<T> > 
    {
        inline size_t operator()(const Botcraft::Vector3<T>& v) const
        {
            std::hash<T> hasher;
            size_t value = hasher(v.x);
            value ^= hasher(v.y) + 0x9e3779b9 + (value << 6) + (value >> 2);
            value ^= hasher(v.z) + 0x9e3779b9 + (value << 6) + (value >> 2);
            return value;
        }
    };
}
