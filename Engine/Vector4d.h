#pragma once

#include "Vector3d.h"

class Vector4d {

public:
	

	Vector4d() : m_x(0.0f), m_y(0.0f), m_z(0.0f), m_w(0.0f)
	{}

	Vector4d(float i_x, float i_y, float i_z, float i_w)
		: m_x(i_x), m_y(i_y), m_z(i_z), m_w(i_w)
	{}

	Vector4d(const Vector3d & i_Vec, float i_4) :
		m_x(i_Vec.x()), m_y(i_Vec.y()), m_z(i_Vec.z()), m_w(i_4)
	{}

	//Getter functions
	float x() const { return m_x; }
	float y() const { return m_y; }
	float z() const { return m_z; }
	float w() const { return m_w; }

	//Setter functions
	void x(const float i_x) { m_x = i_x; }
	void y(const float i_y) { m_x = i_y; }
	void z(const float i_z) { m_x = i_z; }
	void w(const float i_w) { m_w = i_w; }

	//Some operator overloading
	inline Vector4d operator+(const Vector4d &i_other) const
	{
		Vector4d temp;
		temp.m_x = m_x + i_other.m_x;
		temp.m_y = m_y + i_other.m_y;
		temp.m_z = m_z + i_other.m_z;
		temp.m_w = m_z + i_other.m_w;

		return temp;
	}


	inline Vector4d operator-(const Vector4d &i_other) const
	{
		Vector4d temp;
		temp.m_x = m_x - i_other.m_x;
		temp.m_y = m_y - i_other.m_y;
		temp.m_z = m_z - i_other.m_z;
		temp.m_w = m_w - i_other.m_w;

		return temp;
	}

	inline Vector4d operator/(const Vector4d &i_other) const
	{
		Vector4d temp;
		temp.m_x = m_x / i_other.m_x;
		temp.m_y = m_y / i_other.m_y;
		temp.m_z = m_z / i_other.m_z;
		temp.m_w = m_w / i_other.m_w;

		return temp;
	}

	inline Vector4d operator*(const Vector4d &i_other) const
	{
		Vector4d temp;
		temp.m_x = m_x * i_other.m_x;
		temp.m_y = m_y * i_other.m_y;
		temp.m_z = m_z * i_other.m_z;
		temp.m_w = m_w * i_other.m_w;

		return temp;
	}

	inline void Print() const
	{
		DEBUG_PRINT("m_x = %f\n", m_x);
		DEBUG_PRINT("m_y = %f\n", m_y);
		DEBUG_PRINT("m_z = %f\n", m_z);
		DEBUG_PRINT("m_w = %f\n", m_w);
	}

	

private:
	float m_x, m_y, m_z, m_w;
};








