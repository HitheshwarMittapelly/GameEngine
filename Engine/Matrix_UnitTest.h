#pragma once
#include "Matrix_4x4.h"
#include <assert.h>
namespace Math {

	static bool unittest() {

		Matrix_4x4 MRotZ = Matrix_4x4::CreateZRotation(45);
		MRotZ.Print();

		Matrix_4x4 MScaled = Matrix_4x4::CreateScale(1,2,3);
		MScaled.Print();

		Matrix_4x4 MTranslated = Matrix_4x4::CreateTranslation(4, 5, 6);
		MTranslated.Print();

		//Transpose Test
		Matrix_4x4 MOriginal = Matrix_4x4(1, 1, 1, -1, 1, 1, -1, 1, 1, -1, 1, 1, -1, 1, 1, 1);

		Matrix_4x4 MTranspose = MOriginal.GetTranspose();

		Matrix_4x4 MDoubleTranspose = MTranspose.GetTranspose();

		bool check = MOriginal.IsEqual(MDoubleTranspose);
		assert(check);


		//Inverse test
		Matrix_4x4 M1 = Matrix_4x4(1,1,1,-1,1,1,-1,1,1,-1,1,1,-1,1,1,1);

		Matrix_4x4 M2 = M1.GetInverse();

		Matrix_4x4 M3 = M2.GetInverse();

		//M3 and M1 should be equal
		bool result = M1.IsEqual(M3);
		assert(result);

		// AT x BT =  (B x A)T -- T means Transpose
		Matrix_4x4 ATranspose = M1.GetTranspose();
		Matrix_4x4 BTranspose = M2.GetTranspose();

		Matrix_4x4 ATxBT = ATranspose * BTranspose;

		Matrix_4x4 BxAWholeTranspose = (M2 * M1).GetTranspose();

		result = ATxBT.IsEqual(BxAWholeTranspose);
		assert(result);

		return true;
	}
}