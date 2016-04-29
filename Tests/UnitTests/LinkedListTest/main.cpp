
#include <Utilities/LinkedList.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>


#define BOOST_TEST_MODULE LinkedListTests
#include <boost/test/unit_test.hpp>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>



struct TestFixture
{
	TestFixture()
	{
		
		integerList.add(new int(1));
		integerList.add(new int(2));
		integerList.add(new int(3));
		integerList.add(new int(4));

	}

	~TestFixture()
	{
	}

	LinkedList<int> integerList;

};

BOOST_AUTO_TEST_SUITE(LinkedListTests)

BOOST_AUTO_TEST_CASE( LinkedListAdd )
{
	LinkedList<int> integerList;
	BOOST_CHECK_MESSAGE(integerList.add(new int(1)), "Failed to add an integer to the list");
	BOOST_CHECK_MESSAGE((integerList.size()), "Size incorrect after adding an element.");
	integerList.add(new int(2));
	integerList.add(new int(3));
	BOOST_CHECK_MESSAGE(integerList.add(new int(4)), "Failed to add a fourth integer to the list");
	BOOST_CHECK_MESSAGE((integerList.size() == 4), "Size incorrect after adding a fourth element");
}

BOOST_AUTO_TEST_CASE( AccessingElements )
{
	TestFixture fixture;

	BOOST_CHECK_MESSAGE((*(fixture.integerList[2]) == 3), "Failed to access element 2 properly");
	BOOST_CHECK_MESSAGE((*(fixture.integerList[3]) == 4), "Failed to access element 3 properly");
	BOOST_CHECK_MESSAGE((*(fixture.integerList[0]) == 1), "Failed to access element 0 properly");
	BOOST_CHECK_MESSAGE((*(fixture.integerList[-1]) == 4), "Failed to access the last element properly");

}

BOOST_AUTO_TEST_CASE( RemovingElements )
{
	TestFixture fixture;

	BOOST_CHECK_MESSAGE(fixture.integerList.remove(fixture.integerList[2]), "Failed to remove element 2");

	BOOST_CHECK_MESSAGE((*(fixture.integerList[2]) == 4), "Removal of element 2 failed");
	BOOST_CHECK_MESSAGE((fixture.integerList.size() == 3), "Array size count unexpected when removing element 2");

	BOOST_CHECK_MESSAGE(fixture.integerList.remove(fixture.integerList[0]), "Failed to remove element 0");

	BOOST_CHECK_MESSAGE((*(fixture.integerList[0]) == 2), "Removal of element 0 failed");
	BOOST_CHECK_MESSAGE((fixture.integerList.size() == 2), "Array size count unexpected when removing element 0");

	BOOST_CHECK_MESSAGE(!fixture.integerList.remove(fixture.integerList[4]), "Remove reported success when it shouldn't have - accessing element out of bounds.");

	BOOST_CHECK_MESSAGE((fixture.integerList[4] == 0), "Accessed element out of bounds, but got a value.");
	BOOST_CHECK_MESSAGE((fixture.integerList.size() == 2), "Array size count unexpected when failed to remove an element");

	BOOST_CHECK_MESSAGE(fixture.integerList.remove(fixture.integerList[-1]), "Failed to remove last element.");

	BOOST_CHECK_MESSAGE((*(fixture.integerList[0]) == 2), "Failed to access head value.");
	BOOST_CHECK_MESSAGE((fixture.integerList.size() == 1), "Array size count unexpected when removing last place element");

	BOOST_CHECK_MESSAGE(!fixture.integerList.remove(0), "Remove reported success when it shouldn't have - null element");

	BOOST_CHECK_MESSAGE((fixture.integerList[0] != 0), "Accessed element out of bounds, but got a value.");
	BOOST_CHECK_MESSAGE((fixture.integerList.size() == 1), "Array size count unexpected when removing element 0");

}

BOOST_AUTO_TEST_CASE( AccessingOutOfBounds )
{
	TestFixture fixture;
	int* i = new int(14);
	BOOST_CHECK_MESSAGE(!fixture.integerList.remove(i), "Remove call failed when removing non-existing element.");
	
	//cleanup the integer since it wasn't added.
	delete i;

}



BOOST_AUTO_TEST_SUITE_END()