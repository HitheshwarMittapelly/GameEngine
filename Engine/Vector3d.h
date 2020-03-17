#pragma once
#include "ConsolePrint.h"
#include "GameObject2D.h"

class Vector3d {

public:
	

	Vector3d() : m_x(0.0f), m_y(0.0f), m_z(0.0f)
	{}

	Vector3d(float i_x, float i_y, float i_z)
		: m_x(i_x), m_y(i_y), m_z(i_z)
	{}

	Vector3d(const Point2D & i_other)
		:m_x(i_other.x()),m_y(i_other.y()),m_z(0)
	{}

	//Getter functions
	float x() const { return m_x; }
	float y() const { return m_y; }
	float z() const { return m_z; }

	//setter functions
	void x(const float i_x) { m_x = i_x; }
	void y(const float i_y) { m_x = i_y; }
	void z(const float i_z) { m_x = i_z; }

	Vector3d & operator=(const Point2D & i_other) {
		this->m_x = i_other.x();
		this->m_y = i_other.y();
		this->m_z = 0;
		return *this;
	}

	// Operators
	inline Vector3d operator+(const Vector3d &i_other) const
	{
		Vector3d temp;
		temp.m_x = m_x + i_other.m_x;
		temp.m_y = m_y + i_other.m_y;
		temp.m_z = m_z + i_other.m_z;

		return temp;
	}

	
	inline Vector3d operator-(const Vector3d &i_other) const
	{
		Vector3d temp;
		temp.m_x = m_x - i_other.m_x;
		temp.m_y = m_y - i_other.m_y;
		temp.m_z = m_z - i_other.m_z;

		return temp;
	}

	
	inline Vector3d operator/(const Vector3d &i_other) const
	{
		Vector3d temp;
		temp.m_x = m_x / i_other.m_x;
		temp.m_y = m_y / i_other.m_y;
		temp.m_z = m_z / i_other.m_z;

		return temp;
	}

	
	inline Vector3d operator*(const Vector3d &i_other) const
	{
		Vector3d temp;
		temp.m_x = m_x * i_other.m_x;
		temp.m_y = m_y * i_other.m_y;
		temp.m_z = m_z * i_other.m_z;

		return temp;
	}

	
	void Print() const
	{
		DEBUG_PRINT("m_x = %f\n", m_x);
		DEBUG_PRINT("m_y = %f\n", m_y);
		DEBUG_PRINT("m_z = %f\n", m_z);
	}

	
	inline void Absolute()
	{
		if (m_x < 0) { m_x = -m_x; }
		if (m_y < 0) { m_y = -m_y; }
		if (m_z < 0) { m_z = -m_z; }
	}

	

private:
	float m_x, m_y, m_z;
};

