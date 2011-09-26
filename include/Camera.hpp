/**
    Classe que lida com as funcoes de uma camera sintetica.
 **/
#ifndef _BRUNODEA_CAMERA_HPP_
#define _BRUNODEA_CAMERA_HPP_

#include "math/matrix_functions.hpp"
#include "math/math_aux.hpp"

class Camera
{
public:
    Camera(const math::Vector3 &eye, const math::Vector3 &target, const math::Vector3 &up)
        : m_vEye3(eye), m_vTarget3(target), m_vUp3(up), m_fRollAngle(0.f), m_fYawAngle(0.f), m_fPitchAngle(0.f)
    {
        adjustAxes();
        m_fSpeed = 1.f;
    }

    void rotate(float roll_angle, float yaw_angle, float pitch_angle)
    {
        setRollAngle(getRollAngle()+math::radToDegree(roll_angle));
        setYawAngle(getYawAngle()+math::radToDegree(yaw_angle));
        setPitchAngle(getPitchAngle()+math::radToDegree(pitch_angle));
    }

    void moveForward() { m_vEye3 += m_vDirection3*m_fSpeed; }
    void moveBackwards() { m_vEye3 -= m_vDirection3*m_fSpeed; }
    void moveLeft() { m_vEye3 += m_vRight3*m_fSpeed; }
    void moveRight() { m_vEye3 -= m_vRight3*m_fSpeed; }
    void moveUp() { m_vEye3 -= m_vUp3*m_fSpeed; }
    void moveDown() { m_vEye3 += m_vUp3*m_fSpeed; }
    
    math::Vector3 eye() { return m_vEye3; }
    void setEye(const math::Vector3 &eye) { m_vEye3 = eye; }

    math::Vector3 target() { return m_vTarget3; }
    void setTarget(const math::Vector3 &target) { m_vTarget3 = target; }

    math::Vector3 up() { return m_vUp3; }
    void setUp(const math::Vector3 &up) { m_vUp3 = up; }

    math::Vector3 direction() { return m_vDirection3; }
    void setDirection(const math::Vector3 &direction) { m_vDirection3 = direction; }

    math::Vector3 right() { return m_vRight3; }
    void setRight(const math::Vector3 &right) { m_vRight3 = right; }

    void setSpeed(float speed) { m_fSpeed = speed; }
    float getSpeed() { return m_fSpeed; }

    void adjustAxes()
    {
        m_vDirection3 = math::normalize(m_vTarget3 - m_vEye3);
        m_vRight3 = math::normalize(m_vUp3.crossProduct(m_vDirection3));
        m_vUp3 = m_vDirection3.crossProduct(m_vRight3);
    }

    void setRollAngle(float roll) { m_fRollAngle = roll; }
    float getRollAngle() { return m_fRollAngle; }

    void setYawAngle(float yaw) { m_fYawAngle = yaw; }
    float getYawAngle() { return m_fYawAngle; }

    void setPitchAngle(float pitch) { m_fPitchAngle = pitch; }
    float getPitchAngle() { return m_fPitchAngle; }

private:
    math::Vector3 m_vEye3;
    math::Vector3 m_vTarget3;
    math::Vector3 m_vUp3;
    math::Vector3 m_vDirection3;
    math::Vector3 m_vRight3;

    float m_fSpeed;

    float m_fRollAngle;
    float m_fYawAngle;
    float m_fPitchAngle;

}; //end of class Camera.
#endif
