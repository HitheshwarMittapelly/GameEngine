#pragma once
#include <math.h>
namespace Engine {
	
	class Point2D {

	public:
		Point2D() { m_x = 0; m_y = 0; }

		Point2D(const float i_x, const float i_y) {
			m_x = i_x;
			m_y = i_y;
		}

		Point2D(const Point2D & i_other)
		{
			m_x = i_other.x();
			m_y = i_other.y();
		}
		// get x

		inline float x()  const;
		//get y
		inline float y() const;

		



		// set point
		void SetXY(const float i_x, const float i_y) {
			this->m_x = i_x;
			this->m_y = i_y;
		}

		void Normalize()
		{
			Point2D normalized;
			float magnitude = static_cast<float>( pow(this->m_x,2) + pow(this->m_y,2));
			magnitude = static_cast<float> (sqrt(magnitude));
			normalized.SetXY(this->m_x / magnitude, this->m_y / magnitude);
			this->SetXY(normalized.x(), normalized.y());
		}


		// operator for !=
		bool operator != (const Point2D  & i_other) {
			return m_x != i_other.m_x || m_y != i_other.m_y;

		}

		// operator for ==
		bool operator == (const Point2D  & i_other) {
			return m_x == i_other.m_x && m_y == i_other.m_y;
		}

		Point2D operator =(const Point2D & i_other) {
			this->m_x = i_other.x();
			this->m_y = i_other.y();
			return *this;
		}

		Point2D operator +=(const Point2D &i_other) {
			this->m_x += i_other.x();
			this->m_y += i_other.y();
			return *this;
		}


		Point2D operator -=(const Point2D & i_other) {
			this->m_x -= i_other.x();
			this->m_y -= i_other.y();
			return *this;
		}

		Point2D operator *=(const Point2D & i_other) {
			this->m_x *= i_other.x();
			this->m_y *= i_other.y();
			return *this;
		}

		Point2D operator /=(const Point2D & i_other) {
			this->m_x /= i_other.x();
			this->m_y /= i_other.y();
			return *this;
		}
		Point2D operator /(const float other) {
			Point2D o_Output;
			o_Output.m_x = this->m_x / other;
			o_Output.m_y = this->m_y / other;
			return o_Output;
		}

		Point2D operator *(const float other) {
			Point2D o_Output;
			o_Output.m_x = this->m_x * other;
			o_Output.m_y = this->m_y * other;
			return o_Output;
		}

		Point2D operator +(const Point2D other) {
			Point2D o_Output;
			o_Output.m_x = this->m_x + other.m_x;
			o_Output.m_y = this->m_y + other.m_y;
			return o_Output;
		}

		Point2D operator -(const Point2D other) {
			Point2D o_Output;
			o_Output.m_x = this->m_x - other.m_x;
			o_Output.m_y = this->m_y - other.m_y;
			return o_Output;
		}
		
		
	private:
		float m_x, m_y;


	};
	
}

#include "Point2D-inl.h"

