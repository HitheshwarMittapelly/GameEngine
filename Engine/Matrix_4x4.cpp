#include "Matrix_4x4.h"
#include <cmath> 
#include "ConsolePrint.h"
#include <assert.h>
#include <intrin.h>

#define PI 3.14159265f
#define	Deg2Rad ( PI / 180.0f )				// for radian to degree
namespace Math {
	Matrix_4x4::Matrix_4x4():
		m_11(0), m_12(0), m_13(0), m_14(0),
		m_21(0), m_22(0), m_23(0), m_24(0),
		m_31(0), m_32(0), m_33(0), m_34(0),
		m_41(0), m_42(0), m_43(0), m_44(0)
	{

	}

	Matrix_4x4::Matrix_4x4(
		float i_11, float i_12, float i_13, float i_14,
		float i_21, float i_22, float i_23, float i_24,
		float i_31, float i_32, float i_33, float i_34,
		float i_41, float i_42, float i_43, float i_44
	) :
		m_11(i_11), m_12(i_12), m_13(i_13), m_14(i_14),
		m_21(i_21), m_22(i_22), m_23(i_23), m_24(i_24),
		m_31(i_31), m_32(i_32), m_33(i_33), m_34(i_34),
		m_41(i_41), m_42(i_42), m_43(i_43), m_44(i_44)
	{}

	bool Matrix_4x4::IsEqual(const Matrix_4x4 & i_mtx)
	{
		
		if (this->m_11 != i_mtx.m_11) {
			return false;
		}
		if (this->m_12 != i_mtx.m_12) {
			return false;
		}
		if (this->m_13 != i_mtx.m_13) {
			return false;
		}
		if (this->m_14 != i_mtx.m_14) {
			return false;
		}

		if (this->m_21 != i_mtx.m_21) {
			return false;
		}
		if (this->m_22 != i_mtx.m_22) {
			return false;
		}
		if (this->m_23 != i_mtx.m_23) {
			return false;
		}
		if (this->m_24 != i_mtx.m_24) {
			return false;
		}

		if (this->m_31 != i_mtx.m_31) {
			return false;
		}
		if (this->m_32 != i_mtx.m_32) {
			return false;
		}
		if (this->m_33 != i_mtx.m_33) {
			return false;
		}
		if (this->m_34 != i_mtx.m_34) {
			return false;
		}

		if (this->m_41 != i_mtx.m_41) {
			return false;
		}
		if (this->m_42 != i_mtx.m_42) {
			return false;
		}
		if (this->m_43 != i_mtx.m_43) {
			return false;
		}
		if (this->m_44 != i_mtx.m_44) {
			return false;
		}
		return true;
			
	}

	// Print
	void Matrix_4x4::Print(void) const
	{
		assert(!isnan(m_11));
		DEBUG_PRINT("%f	 %f  %f  %f\n\t %f	 %f  %f  %f\n\t "
			"%f	 %f  %f  %f\n\t %f	 %f  %f  %f\n",
			m_11, m_12, m_13, m_14, m_21, m_22, m_23, m_24,
			m_31, m_32, m_33, m_34, m_41, m_42, m_43, m_44
		);
	}

	// Identity
	Matrix_4x4 Matrix_4x4::CreateIdentity(void)
	{
		return Matrix_4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	}

	Matrix_4x4 Matrix_4x4::CreateXRotation(float i_degrees)
	{
		float radians = i_degrees * Deg2Rad;
		return Matrix_4x4(
			1, 0, 0, 0,
			0, cos(radians), -sin(radians), 0,
			0, sin(radians), cos(radians), 0,
			0, 0, 0, 1
		);
	}

	Matrix_4x4 Matrix_4x4::CreateYRotation(float i_degrees)
	{
		float radians = i_degrees * Deg2Rad;
		return Matrix_4x4(
			cos(radians), 0, sin(radians), 0,
			0, 1, 0, 0,
			-sin(radians), 0, cos(radians), 0,
			0, 0, 0, 1
		);
	}

	Matrix_4x4 Matrix_4x4::CreateZRotation(float i_degrees)
	{
		float radians = i_degrees * Deg2Rad;
		return Matrix_4x4(
			cos(radians), -sin(radians), 0, 0,
			sin(radians), cos(radians), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
		
	}

	

	

	Matrix_4x4 Matrix_4x4::CreateTranslation(Vector3d i_trans)
	{
		return Matrix_4x4::CreateTranslation(i_trans.x(), i_trans.y(), i_trans.z());
	}

	Matrix_4x4 Matrix_4x4::CreateTranslation(float i_TransX, float i_TransY, float i_TransZ)
	{
		return Matrix_4x4(
			1, 0, 0, i_TransX,
			0, 1, 0, i_TransY,
			0, 0, 1, i_TransZ,
			0, 0, 0, 1
		);
	}

	Matrix_4x4 Matrix_4x4::CreateScale(Vector3d i_Scale)
	{
		return Matrix_4x4::CreateScale(i_Scale.x(), i_Scale.y(), i_Scale.z());
	}

	Matrix_4x4 Matrix_4x4::CreateScale(float i_ScaleX, float i_ScaleY, float i_SccaleZ)
	{
		return Matrix_4x4(
			i_ScaleX, 0, 0, 0,
			0, i_ScaleY, 0, 0,
			0, 0, i_SccaleZ, 0,
			0, 0, 0, 1
		);
	}

	void Matrix_4x4::Transpose(void)	
	{
		*this = this->GetTranspose();
	}

	Matrix_4x4 Matrix_4x4::GetTranspose(void) const		
	{
		Matrix_4x4 temp = *this;

		temp.m_21 = m_12;
		temp.m_31 = m_13;
		temp.m_41 = m_14;

		temp.m_12 = m_21;
		temp.m_32 = m_23;
		temp.m_42 = m_24;

		temp.m_13 = m_31;
		temp.m_23 = m_32;
		temp.m_43 = m_34;

		temp.m_14 = m_41;
		temp.m_24 = m_42;
		temp.m_34 = m_43;

		return temp;
	}

	Matrix_4x4 Matrix_4x4::GetInverse() const
	{
		
		float inv[17]; 

		inv[1] = m_22 * m_33 * m_44
			+ m_23 * m_34 * m_42
			+ m_24 * m_32 * m_43
			- m_24 * m_33 * m_42
			- m_22 * m_34 * m_43
			- m_23 * m_32 * m_44;

		inv[2] = m_21 * m_33 * m_44
			+ m_23 * m_34 * m_41
			+ m_24 * m_31 * m_43
			- m_21 * m_34 * m_43
			- m_23 * m_31 * m_44
			- m_24 * m_33 * m_41;

		inv[3] = m_21 * m_32 * m_44
			+ m_22 * m_34 * m_41
			+ m_24 * m_31 * m_42
			- m_24 * m_32 * m_41
			- m_22 * m_31 * m_44
			- m_21 * m_34 * m_42;

		inv[4] = m_21 * m_32 * m_43
			+ m_22 * m_33 * m_41
			+ m_23 * m_31 * m_42
			- m_23 * m_32 * m_41
			- m_22 * m_31 * m_43
			- m_21 * m_33 * m_42;

		inv[5] = m_12 * m_33 * m_44
			+ m_13 * m_34 * m_42
			+ m_14 * m_32 * m_43
			- m_14 * m_33 * m_42
			- m_13 * m_32 * m_44
			- m_12 * m_34 * m_43;

		inv[6] = m_11 * m_33 * m_44
			+ m_13 * m_34 * m_41
			+ m_14 * m_31 * m_43
			- m_14 * m_33 * m_41
			- m_13 * m_31 * m_44
			- m_11 * m_34 * m_43;

		inv[7] = m_11 * m_32 * m_44
			+ m_12 * m_34 * m_41
			+ m_14 * m_31 * m_42
			- m_14 * m_32 * m_41
			- m_12 * m_31 * m_44
			- m_11 * m_34 * m_42;

		inv[8] = m_11 * m_32 * m_43
			+ m_12 * m_33 * m_41
			+ m_13 * m_31 * m_42
			- m_13 * m_32 * m_41
			- m_12 * m_31 * m_43
			- m_11 * m_33 * m_42;

		inv[9] = m_12 * m_23 * m_44
			+ m_13 * m_24 * m_42
			+ m_14 * m_22 * m_43
			- m_14 * m_23 * m_42
			- m_13 * m_22 * m_44
			- m_12 * m_24 * m_43;

		inv[10] = m_11 * m_23 * m_44
			+ m_13 * m_24 * m_41
			+ m_14 * m_21 * m_43
			- m_14 * m_23 * m_41
			- m_13 * m_21 * m_44
			- m_11 * m_24 * m_43;

		inv[11] = m_11 * m_22 * m_44
			+ m_12 * m_24 * m_41
			+ m_14 * m_21 * m_42
			- m_14 * m_22 * m_41
			- m_12 * m_21 * m_44
			- m_11 * m_24 * m_42;

		inv[12] = m_11 * m_22 * m_43
			+ m_12 * m_23 * m_41
			+ m_13 * m_21 * m_42
			- m_13 * m_22 * m_41
			- m_12 * m_21 * m_43
			- m_11 * m_23 * m_42;

		inv[13] = m_12 * m_23 * m_34
			+ m_13 * m_24 * m_32
			+ m_14 * m_22 * m_33
			- m_14 * m_23 * m_32
			- m_13 * m_22 * m_34
			- m_12 * m_24 * m_33;

		inv[14] = m_11 * m_23 * m_34
			+ m_13 * m_24 * m_31
			+ m_14 * m_21 * m_33
			- m_14 * m_23 * m_31
			- m_13 * m_21 * m_34
			- m_11 * m_24 * m_33;

		inv[15] = m_11 * m_22 * m_34
			+ m_12 * m_24 * m_31
			+ m_14 * m_21 * m_32
			- m_14 * m_22 * m_31
			- m_12 * m_21 * m_34
			- m_11 * m_24 * m_32;

		inv[16] = m_11 * m_22 * m_33
			+ m_12 * m_23 * m_31
			+ m_13 * m_21 * m_32
			- m_13 * m_22 * m_31
			- m_12 * m_21 * m_33
			- m_11 * m_23 * m_32;


		float detrminant = m_11 * inv[1] - m_21 * inv[5]
			+ m_31 * inv[9] - m_41 * inv[13];

		if (detrminant == 0)
		{
			DEBUG_PRINT("Can't find Inverse. Determinant is 0.");
			return Matrix_4x4();
		}
		else
		{
			float invOfDet = 1 / detrminant;

			Matrix_4x4 temp(inv[1], -inv[5], inv[9], -inv[13],
				-inv[2], inv[6], -inv[10], inv[14],
				inv[3], -inv[7], inv[11], -inv[15],
				-inv[4], inv[8], -inv[12], inv[16]);

			// Inverse  = [ 1/det(A) ] * adj(A);
			Matrix_4x4 Inverse = temp * invOfDet;

			return Inverse;
		}
	}

	// * with float
	Matrix_4x4 Matrix_4x4::operator*(const float & i_float) const
	{
		Matrix_4x4 temp;

		temp.m_11 = m_11 * i_float;
		temp.m_12 = m_12 * i_float;
		temp.m_13 = m_13 * i_float;
		temp.m_14 = m_14 * i_float;
		temp.m_21 = m_21 * i_float;
		temp.m_22 = m_22 * i_float;
		temp.m_23 = m_23 * i_float;
		temp.m_24 = m_24 * i_float;
		temp.m_31 = m_31 * i_float;
		temp.m_32 = m_32 * i_float;
		temp.m_33 = m_33 * i_float;
		temp.m_34 = m_34 * i_float;
		temp.m_41 = m_41 * i_float;
		temp.m_42 = m_42 * i_float;
		temp.m_43 = m_43 * i_float;
		temp.m_44 = m_44 * i_float;

		return temp;
	}

	Matrix_4x4 Matrix_4x4::operator*(const Matrix_4x4 & i_Oth) const
	{
		//return MultiplySSE(i_Oth);
		float temp[17];

		temp[1] = m_11 * i_Oth.m_11 + m_12 * i_Oth.m_21 + m_13 * i_Oth.m_31 + m_14 * i_Oth.m_41;
		temp[2] = m_11 * i_Oth.m_12 + m_12 * i_Oth.m_22 + m_13 * i_Oth.m_32 + m_14 * i_Oth.m_42;
		temp[3] = m_11 * i_Oth.m_13 + m_12 * i_Oth.m_23 + m_13 * i_Oth.m_33 + m_14 * i_Oth.m_43;
		temp[4] = m_11 * i_Oth.m_14 + m_12 * i_Oth.m_24 + m_13 * i_Oth.m_34 + m_14 * i_Oth.m_44;

		temp[5] = m_21 * i_Oth.m_11 + m_22 * i_Oth.m_21 + m_23 * i_Oth.m_31 + m_24 * i_Oth.m_41;
		temp[6] = m_21 * i_Oth.m_12 + m_22 * i_Oth.m_22 + m_23 * i_Oth.m_32 + m_24 * i_Oth.m_42;
		temp[7] = m_21 * i_Oth.m_13 + m_22 * i_Oth.m_23 + m_23 * i_Oth.m_33 + m_24 * i_Oth.m_43;
		temp[8] = m_21 * i_Oth.m_14 + m_22 * i_Oth.m_24 + m_23 * i_Oth.m_34 + m_24 * i_Oth.m_44;

		temp[9] = m_31 * i_Oth.m_11 + m_32 * i_Oth.m_21 + m_33 * i_Oth.m_31 + m_34 * i_Oth.m_41;
		temp[10] = m_31 * i_Oth.m_12 + m_32 * i_Oth.m_22 + m_33 * i_Oth.m_32 + m_34 * i_Oth.m_42;
		temp[11] = m_31 * i_Oth.m_13 + m_32 * i_Oth.m_23 + m_33 * i_Oth.m_33 + m_34 * i_Oth.m_43;
		temp[12] = m_31 * i_Oth.m_14 + m_32 * i_Oth.m_24 + m_33 * i_Oth.m_34 + m_34 * i_Oth.m_44;

		temp[13] = m_41 * i_Oth.m_11 + m_42 * i_Oth.m_21 + m_43 * i_Oth.m_31 + m_44 * i_Oth.m_41;
		temp[14] = m_41 * i_Oth.m_12 + m_42 * i_Oth.m_22 + m_43 * i_Oth.m_32 + m_44 * i_Oth.m_42;
		temp[15] = m_41 * i_Oth.m_13 + m_42 * i_Oth.m_23 + m_43 * i_Oth.m_33 + m_44 * i_Oth.m_43;
		temp[16] = m_41 * i_Oth.m_14 + m_42 * i_Oth.m_24 + m_43 * i_Oth.m_34 + m_44 * i_Oth.m_44;

		return Matrix_4x4(temp[1], temp[2], temp[3], temp[4],
			temp[5], temp[6], temp[7], temp[8],
			temp[9], temp[10], temp[11], temp[12],
			temp[13], temp[14], temp[15], temp[16]);
	}

	// Multiply Vector Left
	Vector4d Matrix_4x4::MultiplyLeft(const Vector4d & i_Oth) const
	{
		float x = i_Oth.x() * m_11 + i_Oth.y() * m_21 + i_Oth.z() * m_31 + i_Oth.w() * m_41;
		float y = i_Oth.x() * m_12 + i_Oth.y() * m_22 + i_Oth.z() * m_32 + i_Oth.w() * m_42;
		float z = i_Oth.x() * m_13 + i_Oth.y() * m_23 + i_Oth.z() * m_33 + i_Oth.w() * m_43;
		float w = i_Oth.x() * m_14 + i_Oth.y() * m_24 + i_Oth.z() * m_34 + i_Oth.w() * m_44;

		return Vector4d(x, y, z, w);
	}

	Vector4d Matrix_4x4::MultiplyRight(const Vector4d & i_Oth) const
	{
		float x = m_11 * i_Oth.x() + m_12 * i_Oth.y() + m_13 * i_Oth.z() + m_14 * i_Oth.w();
		float y = m_21 * i_Oth.x() + m_22 * i_Oth.y() + m_23 * i_Oth.z() + m_24 * i_Oth.w();
		float z = m_31 * i_Oth.x() + m_32 * i_Oth.y() + m_33 * i_Oth.z() + m_34 * i_Oth.w();
		float w = m_41 * i_Oth.x() + m_42 * i_Oth.y() + m_43 * i_Oth.z() + m_44 * i_Oth.w();

		return Vector4d(x, y, z, w);
	}


	void Matrix_4x4::InverseSSE(Matrix_4x4 & i_Out) const
	{
		
		__m128 temp = { 0.0f };
		__m128 row0, row1, row2, row3;
		__m128 minor0, minor1, minor2, minor3;

		temp = _mm_loadh_pi(_mm_loadl_pi(temp, reinterpret_cast<const __m64 *>(&m_11)), reinterpret_cast<const __m64 *>(&m_21));
		row1 = _mm_loadh_pi(_mm_loadl_pi(temp, reinterpret_cast<const __m64 *>(&m_31)), reinterpret_cast<const __m64 *>(&m_41));
		row0 = _mm_shuffle_ps(temp, row1, 0x88);
		row1 = _mm_shuffle_ps(row1, temp, 0xDD);
		temp = _mm_loadh_pi(_mm_loadl_pi(temp, reinterpret_cast<const __m64 *>(&m_13)), reinterpret_cast<const __m64 *>(&m_23));
		row3 = _mm_loadh_pi(_mm_loadl_pi(temp, reinterpret_cast<const __m64 *>(&m_33)), reinterpret_cast<const __m64 *>(&m_43));
		row2 = _mm_shuffle_ps(temp, row3, 0x88);
		row3 = _mm_shuffle_ps(row3, temp, 0xDD);

		// -----------------------------------------------
		temp = _mm_mul_ps(row2, row3);
		temp = _mm_shuffle_ps(temp, temp, 0xB1);
		minor0 = _mm_mul_ps(row1, temp);
		minor1 = _mm_mul_ps(row0, temp);
		temp = _mm_shuffle_ps(temp, temp, 0x4E);
		minor0 = _mm_sub_ps(_mm_mul_ps(row1, temp), minor0);
		minor1 = _mm_sub_ps(_mm_mul_ps(row0, temp), minor1);
		minor1 = _mm_shuffle_ps(minor1, minor1, 0x4E);

		// -----------------------------------------------
		temp = _mm_mul_ps(row1, row2);
		temp = _mm_shuffle_ps(temp, temp, 0xB1);
		minor0 = _mm_add_ps(_mm_mul_ps(row3, temp), minor0);
		minor3 = _mm_mul_ps(row0, temp);
		temp = _mm_shuffle_ps(temp, temp, 0x4E);
		minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row3, temp));
		minor3 = _mm_sub_ps(_mm_mul_ps(row0, temp), minor3);
		minor3 = _mm_shuffle_ps(minor3, minor3, 0x4E);

		// -----------------------------------------------
		temp = _mm_mul_ps(_mm_shuffle_ps(row1, row1, 0x4E), row3);
		temp = _mm_shuffle_ps(temp, temp, 0xB1);
		row2 = _mm_shuffle_ps(row2, row2, 0x4E);
		minor0 = _mm_add_ps(_mm_mul_ps(row2, temp), minor0);
		minor2 = _mm_mul_ps(row0, temp);
		temp = _mm_shuffle_ps(temp, temp, 0x4E);
		minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row2, temp));
		minor2 = _mm_sub_ps(_mm_mul_ps(row0, temp), minor2);
		minor2 = _mm_shuffle_ps(minor2, minor2, 0x4E);

		// -----------------------------------------------
		temp = _mm_mul_ps(row0, row1);
		temp = _mm_shuffle_ps(temp, temp, 0xB1);
		minor2 = _mm_add_ps(_mm_mul_ps(row3, temp), minor2);
		minor3 = _mm_sub_ps(_mm_mul_ps(row2, temp), minor3);
		temp = _mm_shuffle_ps(temp, temp, 0x4E);
		minor2 = _mm_sub_ps(_mm_mul_ps(row3, temp), minor2);
		minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row2, temp));

		// -----------------------------------------------
		temp = _mm_mul_ps(row0, row3);
		temp = _mm_shuffle_ps(temp, temp, 0xB1);
		minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row2, temp));
		minor2 = _mm_add_ps(_mm_mul_ps(row1, temp), minor2);
		temp = _mm_shuffle_ps(temp, temp, 0x4E);
		minor1 = _mm_add_ps(_mm_mul_ps(row2, temp), minor1);
		minor2 = _mm_sub_ps(minor2, _mm_mul_ps(row1, temp));

		// -----------------------------------------------
		temp = _mm_mul_ps(row0, row2);
		temp = _mm_shuffle_ps(temp, temp, 0xB1);
		minor1 = _mm_add_ps(_mm_mul_ps(row3, temp), minor1);
		minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row1, temp));
		temp = _mm_shuffle_ps(temp, temp, 0x4E);
		minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row3, temp));
		minor3 = _mm_add_ps(_mm_mul_ps(row1, temp), minor3);

		// -----------------------------------------------
		__m128 det;

		det = _mm_mul_ps(row0, minor0);
		det = _mm_add_ps(_mm_shuffle_ps(det, det, 0x4E), det);
		det = _mm_add_ss(_mm_shuffle_ps(det, det, 0xB1), det);
		temp = _mm_rcp_ss(det);
		det = _mm_sub_ss(_mm_add_ss(temp, temp), _mm_mul_ss(det, _mm_mul_ss(temp, temp)));
		det = _mm_shuffle_ps(det, det, 0x00);

		minor0 = _mm_mul_ps(det, minor0);
		_mm_storel_pi(reinterpret_cast<__m64 *>(&i_Out.m_11), minor0);
		_mm_storeh_pi(reinterpret_cast<__m64 *>(&i_Out.m_13), minor0);

		minor1 = _mm_mul_ps(det, minor1);
		_mm_storel_pi(reinterpret_cast<__m64 *>(&i_Out.m_21), minor1);
		_mm_storeh_pi(reinterpret_cast<__m64 *>(&i_Out.m_23), minor1);

		minor2 = _mm_mul_ps(det, minor2);
		_mm_storel_pi(reinterpret_cast<__m64 *>(&i_Out.m_31), minor2);
		_mm_storeh_pi(reinterpret_cast<__m64 *>(&i_Out.m_33), minor2);

		minor3 = _mm_mul_ps(det, minor3);
		_mm_storel_pi(reinterpret_cast<__m64 *>(&i_Out.m_41), minor3);
		_mm_storeh_pi(reinterpret_cast<__m64 *>(&i_Out.m_43), minor3);

		
	}

	void Matrix_4x4::MultiplySSE(const Matrix_4x4 & i_other, Matrix_4x4 & i_Out) const
	{
		
		// load i_other
		__m128 rhs_row1 = _mm_load_ps(&i_other.m_11);
		__m128 rhs_row2 = _mm_load_ps(&i_other.m_21);
		__m128 rhs_row3 = _mm_load_ps(&i_other.m_31);
		__m128 rhs_row4 = _mm_load_ps(&i_other.m_41);

		__m128 acc;

		// (*this).col1 * i_other
		// m_11 * i_other.row1
		acc = _mm_mul_ps(_mm_load1_ps(&m_11), rhs_row1);
		// m_12 * i_other.row2
		acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_12), rhs_row2));
		// m_13 * i_other.row3
		acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_13), rhs_row3));
		// m_14 * i_other.row4
		acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_14), rhs_row4));

		// write result
		_mm_storel_pi(reinterpret_cast<__m64 *>(&i_Out.m_11), acc);
		_mm_storeh_pi(reinterpret_cast<__m64 *>(&i_Out.m_13), acc);

		// (*this).col2 * i_other
		// m_21 * i_other.row1
		acc = _mm_mul_ps(_mm_load1_ps(&m_21), rhs_row1);
		// m_22 * i_other.row2
		acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_22), rhs_row2));
		// m_23 * i_other.row3
		acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_23), rhs_row3));
		// m_24 * i_other.row4
		acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_24), rhs_row4));

		// write result
		_mm_storel_pi(reinterpret_cast<__m64 *>(&i_Out.m_21), acc);
		_mm_storeh_pi(reinterpret_cast<__m64 *>(&i_Out.m_23), acc);

		// (*this).col3 * i_other
		// m_31 * i_other.row1
		acc = _mm_mul_ps(_mm_load1_ps(&m_31), rhs_row1);
		// m_32 * i_other.row2
		acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_32), rhs_row2));
		// m_33 * i_other.row3
		acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_33), rhs_row3));
		// m_34 * i_other.row4
		acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_34), rhs_row4));

		// write result
		_mm_storel_pi(reinterpret_cast<__m64 *>(&i_Out.m_31), acc);
		_mm_storeh_pi(reinterpret_cast<__m64 *>(&i_Out.m_33), acc);

		// (*this).col4 * i_other
		// m_41 * i_other.row1
		acc = _mm_mul_ps(_mm_load1_ps(&m_41), rhs_row1);
		// m_42 * i_other.row2
		acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_42), rhs_row2));
		// m_43 * i_other.row3
		acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_43), rhs_row3));
		// m_44 * i_other.row4
		acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_44), rhs_row4));

		// write result
		_mm_storel_pi(reinterpret_cast<__m64 *>(&i_Out.m_41), acc);
		_mm_storeh_pi(reinterpret_cast<__m64 *>(&i_Out.m_43), acc);
		
	}


}