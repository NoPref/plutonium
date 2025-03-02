//
// Created by Admin on 18.08.2024.
//

#ifndef STANDOFF2_APK_unity_H
#define STANDOFF2_APK_unity_H

#define OBFUSCATE_BNM(x) x

inline float deg2rad(float radius)
{
    static constexpr float pi     = 3.14159265358979323846f;
    static constexpr int   pi_rad = 180;

    float deg = radius * pi / pi_rad;
    return deg;
}

inline float rad2deg(float degree)
{
    static constexpr float pi     = 3.14159265358979323846f;
    static constexpr int   pi_rad = 180;

    float rad = degree * pi_rad / pi;
    return rad;
}

#include "Color.hpp"
#include "Quaternion.hpp"
#include "Ray.hpp"
#include "RaycastHit.hpp"
#include "Rect.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Matrix3x3.hpp"
#include "Matrix4x4.hpp"

#endif //STANDOFF2_APK_unity_H

using namespace unity::structures;
constexpr float floatInf = std::numeric_limits<float>::infinity();

const Vector2 Vector2::positiveInfinity = {floatInf, floatInf};
const Vector2 Vector2::negativeInfinity = {-floatInf, -floatInf};
const Vector2 Vector2::down = {0.f, -1.f};
const Vector2 Vector2::left = {-1.f, 0.f};
const Vector2 Vector2::one = {1.f, 1.f};
const Vector2 Vector2::right = {1.f, 0.f};
const Vector2 Vector2::up = {0.f, 1.f};
const Vector2 Vector2::zero = {0.f, 0.f};

Vector2::operator Vector3() const { return {x, y, 0}; }

const Vector3 Vector3::positiveInfinity = {floatInf, floatInf, floatInf};
const Vector3 Vector3::negativeInfinity = {-floatInf, -floatInf, -floatInf};
const Vector3 Vector3::back = {0.f, 0.f, -1.f};
const Vector3 Vector3::down = {0.f, -1.f, 0.f};
const Vector3 Vector3::forward = {0.f, 0.f, 1.f};
const Vector3 Vector3::left = {-1.f, 0.f, 0.f};
const Vector3 Vector3::one = {1.f, 1.f, 1.f};
const Vector3 Vector3::right = {1.f, 0.f, 0.f};
const Vector3 Vector3::up = {0.f, 1.f, 0.f};
const Vector3 Vector3::zero = {0.f, 0.f, 0.f};

const Vector4 Vector4::positiveInfinity = {floatInf, floatInf, floatInf, floatInf};
const Vector4 Vector4::negativeInfinity = {-floatInf, -floatInf, -floatInf, -floatInf};
const Vector4 Vector4::zero = {0.f, 0.f, 0.f, 0.f};
const Vector4 Vector4::one = {1.f, 1.f, 1.f, 1.f};

const Quaternion Quaternion::identity = {0.f, 0.f, 0.f, 1.f};

const Matrix4x4 Matrix4x4::identity(InitIdentity::kIdentity);

Matrix3x3& Matrix3x3::operator=(const Matrix4x4& other) {
    m_Data[0] = other.m_Data[0];
    m_Data[1] = other.m_Data[1];
    m_Data[2] = other.m_Data[2];
    m_Data[3] = other.m_Data[4];
    m_Data[4] = other.m_Data[5];
    m_Data[5] = other.m_Data[6];
    m_Data[6] = other.m_Data[8];
    m_Data[7] = other.m_Data[9];
    m_Data[8] = other.m_Data[10];
    return *this;
}
Matrix3x3::Matrix3x3(const Matrix4x4& other) {
    m_Data[0] = other.m_Data[0];
    m_Data[1] = other.m_Data[1];
    m_Data[2] = other.m_Data[2];
    m_Data[3] = other.m_Data[4];
    m_Data[4] = other.m_Data[5];
    m_Data[5] = other.m_Data[6];
    m_Data[6] = other.m_Data[8];
    m_Data[7] = other.m_Data[9];
    m_Data[8] = other.m_Data[10];
}
Matrix3x3& Matrix3x3::operator*=(const Matrix4x4& inM) {
    for (int i = 0; i < 3; i++) {
        float v[3] = {Get(i, 0), Get(i, 1), Get(i, 2)};
        Get(i, 0) = v[0] * inM.Get(0, 0) + v[1] * inM.Get(1, 0) + v[2] * inM.Get(2, 0);
        Get(i, 1) = v[0] * inM.Get(0, 1) + v[1] * inM.Get(1, 1) + v[2] * inM.Get(2, 1);
        Get(i, 2) = v[0] * inM.Get(0, 2) + v[1] * inM.Get(1, 2) + v[2] * inM.Get(2, 2);
    }
    return *this;
}
bool Matrix3x3::Invert() {
    Matrix4x4 m = *this;
    bool success = InvertMatrix4x4_Full(m.GetPtr(), m.GetPtr());
    *this = m;
    return success;
}