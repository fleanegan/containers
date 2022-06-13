#include "testUtils.hpp"

int foo();

TEST(iterators, init) {
	ASSERT_EQ(1, foo());
}