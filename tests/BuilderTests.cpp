#include "creational/Builder.h"

#include <UnitTest++/UnitTest++.h>

namespace pc = pattern::creational;

static void BuildJeep()
{
	auto jeepBuilder = std::make_shared<pc::JeepBuilder>();
	pc::Director dir{ jeepBuilder };

	std::cout << std::endl << "Jeep" << std::endl;

	auto car = dir.ConstructCar();
	CHECK(car->GetBody().GetShape() == "SUV");
	CHECK(car->GetEngine().GetHorsePower() == 400);
	CHECK(car->GetWheels().at(0).GetSize() == 22);
	car->PrintSpecifications();

	std::cout << std::endl;
}

static void BuildMitsubishi()
{
	auto mitsuBuilder = std::make_shared<pc::MitsubishiBuilder>();
	pc::Director dir{ mitsuBuilder };

	std::cout << std::endl << "Mitsubishi" << std::endl;

	auto car = dir.ConstructCar();
	CHECK(car->GetBody().GetShape() == "Coupe");
	CHECK(car->GetEngine().GetHorsePower() == 300);
	CHECK(car->GetWheels().at(0).GetSize() == 19);
	car->PrintSpecifications();

	std::cout << std::endl;
}

SUITE(BuilderTest)
{
	TEST(JeepTest)
	{
		BuildJeep();
	}

	TEST(MitsubishiTest)
	{
		BuildMitsubishi();
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}
