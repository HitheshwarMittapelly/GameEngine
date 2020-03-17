#include "Delegates.h"

#include <assert.h>


namespace Delegates {
	
	
	void Delegates__UnitTest()
	{
#ifdef _DEBUG
		using namespace Delegates;

		typedef int					param_t;
		typedef Delegate<param_t>	TestDelegate_t;
		class TestClass
		{
		public:
			void TestMethod(param_t i)
			{}
		};

		TestClass TestInstance;

		TestDelegate_t TestDelegate1 = TestDelegate_t::Create<TestClass, &TestClass::TestMethod>(&TestInstance);
		TestDelegate_t TestDelegate2 = TestDelegate_t::Create<TestClass, &TestClass::TestMethod>(&TestInstance);

		
		assert(TestDelegate1 == TestDelegate2);
		
#endif // _DEBUG
	}

}