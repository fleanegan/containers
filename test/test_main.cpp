#include <cstdio>
#include "gtest/gtest.h"
#include "testUtils.hpp"
#include "testStack.hpp"
#include "testIterators.hpp"
#include "testVectorIterator.hpp"
#include "testVector.hpp"
#include "testPair.hpp"
#include "testBinarySearchTree.hpp"

GTEST_API_ int main(int argc, char **argv) {
	std::cout << "Running main() from " << __FILE__ << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
