//
//  Created by Robert Binna
//
#define BOOST_TEST_DYN_LINK

#include <cstring>

#include <utility>
#include <string>

#include <boost/test/unit_test.hpp>
#include <spider/contenthelpers/OptionalValue.hpp>

namespace spider { namespace contenthelpers {

BOOST_AUTO_TEST_SUITE(OptionalValueTest)

BOOST_AUTO_TEST_CASE(testDefaultConstructor) {
	OptionalValue<uint32_t>  optional;
	BOOST_REQUIRE(!optional.mIsValid);
}

BOOST_AUTO_TEST_CASE(testValidConstruction) {
	OptionalValue<uint32_t>  optional { true, 24u };
	BOOST_REQUIRE(optional.mIsValid);
	BOOST_REQUIRE_EQUAL(optional.mValue, 24u);
}

BOOST_AUTO_TEST_CASE(testInvalidConstruction) {
	OptionalValue<uint32_t>  optional { false, 23u };
	BOOST_REQUIRE(!optional.mIsValid);
}

BOOST_AUTO_TEST_CASE(testCompliesWithInvalidSuccess) {
	OptionalValue<uint32_t>  optional { false, 23u };
	OptionalValue<uint32_t>  optionalExpected { false, 22u };

	BOOST_REQUIRE(optional.compliesWith(optionalExpected));
	BOOST_REQUIRE(optionalExpected.compliesWith(optional));
}

BOOST_AUTO_TEST_CASE(testCompliesWithIsValidSuccess) {
	OptionalValue<uint32_t>  optional { true, 42u };
	OptionalValue<uint32_t>  optionalExpected { true, 42u };

	BOOST_REQUIRE(optional.compliesWith(optionalExpected));
	BOOST_REQUIRE(optionalExpected.compliesWith(optional));
}

BOOST_AUTO_TEST_CASE(testCompliesWithIsValidButUnequalValues) {
	OptionalValue<uint32_t>  optional { true, 42u };
	OptionalValue<uint32_t>  optionalExpected { true, 41u };

	BOOST_REQUIRE(!optional.compliesWith(optionalExpected));
	BOOST_REQUIRE(!optionalExpected.compliesWith(optional));
}

BOOST_AUTO_TEST_CASE(testCompliesWithIsValidAndIsInvalidAndSameValues) {
	OptionalValue<uint32_t>  optional { false, 42u };
	OptionalValue<uint32_t>  optionalExpected { true, 42u };

	BOOST_REQUIRE(!optional.compliesWith(optionalExpected));
	BOOST_REQUIRE(!optionalExpected.compliesWith(optional));
}

BOOST_AUTO_TEST_CASE(testCompliesWithIsValidAndIsInvalidAndUnequalValues) {
	OptionalValue<uint32_t>  optional { false, 10u };
	OptionalValue<uint32_t>  optionalExpected { true, 20u };

	BOOST_REQUIRE(!optional.compliesWith(optionalExpected));
	BOOST_REQUIRE(!optionalExpected.compliesWith(optional));
}

BOOST_AUTO_TEST_SUITE_END()

}}