#pragma once
#include "Delegates.h"
using namespace Delegates;
namespace InputSystem
{
	typedef unsigned int button_t;
	typedef Delegate<button_t, bool>	ButtonChangeReceiver_t;

	extern MultiCastDelegate<button_t, bool>	ButtonChangeReceivers;

	void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown);
	bool CheckIfKeyDown(unsigned int keyID);
	bool CheckIfKeyUp(unsigned int keyID);
	bool Init();
	bool ShutDown();
}