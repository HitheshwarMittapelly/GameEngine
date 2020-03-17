#include "InputSystem.h"
#include "GLib.h"

#include <iostream>
namespace InputSystem {
	MultiCastDelegate<button_t, bool> ButtonChangeReceivers;

	void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
	{
		
		ButtonChangeReceivers.ExecuteOnBound(i_VKeyID, bWentDown);

	}


	bool CheckIfKeyDown(unsigned int i_keyID)
	{
		int returnVal = GLib::GetKeyState(i_keyID);
		if (returnVal == 1) {
			return true;
		}
		else
			return false;
	}
	bool CheckIfKeyUp(unsigned int i_keyID)
	{
		int returnVal = GLib::GetKeyState(i_keyID);
		if (returnVal == 0) {
			return true;
		}
		else
			return false;

	}

	bool Init()
	{
		GLib::SetKeyStateChangeCallback(TestKeyCallback);

		return true;
	}
	bool ShutDown()
	{
		ButtonChangeReceivers.~MultiCastDelegate();
		return true;
	}
}
