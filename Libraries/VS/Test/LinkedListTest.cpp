

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(LinkedListsTest)
#include "Utilities/LinkedList.h"






struct TestObject
{
	TestObject() {};
	~TestObject() {};
};

struct SimpleTestFixture
{

	SimpleTestFixture()
	{

		myIntList.add(1);
		myIntList.add(2);
		myIntList.add(3);
		myIntList.add(4);
	}

	LinkedList<int> myIntList;
};

BOOST_AUTO_TEST_CASE(SimpleAdd)
{

	LinkedList<int> myIntList;

	myIntList.add(1);
	myIntList.add(2);
	myIntList.add(3);
	myIntList.add(4);

	BOOST_CHECK_MESSAGE((*myIntList.begin()) == 1, "Begin does not equal correct value");
	BOOST_CHECK_MESSAGE(myIntList.end() == NULL, "End does not equal correct value");


}


BOOST_AUTO_TEST_CASE(FullSimpleIncrement)
{
	SimpleTestFixture fixture;
	int i = 1;
	for (LinkedList<int>::Iterator iter = fixture.myIntList.begin(); iter != fixture.myIntList.end(); ++iter, ++i)
	{
		BOOST_CHECK_MESSAGE(*iter == i, "Iterator is not correct value");
	}
}

BOOST_AUTO_TEST_CASE(FullSimpleDecrement)
{
	SimpleTestFixture fixture;
	int i = 4;
	LinkedList<int>::Iterator iter = fixture.myIntList.last();

	LinkedList<int>::Iterator stop = fixture.myIntList.begin();
	--stop;
	for (; iter != stop; --iter, --i)
	{
		BOOST_CHECK_MESSAGE(*iter == i, "Iterator is not correct value");
	}
}

BOOST_AUTO_TEST_CASE(TestSize)
{
	SimpleTestFixture fixture;

	BOOST_CHECK_MESSAGE(fixture.myIntList.size() == 4, "Wrong list size");
}

BOOST_AUTO_TEST_CASE(TestIndex)
{
	SimpleTestFixture fixture;

	BOOST_CHECK_MESSAGE(fixture.myIntList[3] == 4, "Wrong value at index 3");
}

BOOST_AUTO_TEST_CASE(SimpleRemove)
{
	SimpleTestFixture fixture;

	fixture.myIntList.remove(3);

	BOOST_CHECK_MESSAGE(fixture.myIntList.size() == 3, "Wrong list size after remove");

	BOOST_CHECK_MESSAGE(fixture.myIntList[0] == 1, "Wrong value at index 0");
	BOOST_CHECK_MESSAGE(fixture.myIntList[1] == 2, "Wrong value at index 1");
	BOOST_CHECK_MESSAGE(fixture.myIntList[2] == 4, "Wrong value at index 2");
}

BOOST_AUTO_TEST_SUITE_END()