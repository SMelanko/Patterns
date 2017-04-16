#include "creational/Prototype.h"

#include <UnitTest++/UnitTest++.h>

#include <vector>

namespace pc = pattern::creational;

SUITE(PrototypeTest)
{
	TEST(WarriorsTest)
	{
		pc::PrototypeFactory factory;

		constexpr size_t size = 10;
		std::vector<pc::WarriorShPtr> warriors(size);

		for (size_t i = 0; i < size; ++i) {
			pc::WarriorShPtr warrior = (i % 2 == 0) ?
				factory.CreateArcher() : factory.CreateInfantryman();
			warriors[i] = warrior;
		}

		std::cout << std::endl;
		for (const auto& warrior : warriors) {
			warrior->PrintInfo();
		}
		std::cout << std::endl;
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}
