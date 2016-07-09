///////////////////////////////////////////////////////////////////////////////
///
/// Copyright (c) 2016 Slava Melanko.
///
/// This code is licensed under the MIT License (MIT).
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
/// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
/// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
/// DEALINGS IN THE SOFTWARE.
///
///////////////////////////////////////////////////////////////////////////////

#include "creational/Builder.h"

#include <UnitTest++/UnitTest++.h>

static void BuildJeep()
{
	auto jeepBuilder = std::make_shared<pattern::creational::JeepBuilder>();
	pattern::creational::Director dir{ jeepBuilder };

	std::cout << std::endl << "Jeep" << std::endl;

	std::shared_ptr<pattern::creational::Car> car = dir.ConstructCar();
	CHECK(car->GetBody().GetShape() == "SUV");
	CHECK(car->GetEngine().GetHorsePower() == 400);
	CHECK(car->GetWheels().at(0).GetSize() == 22);

	std::cout << std::endl;
}

static void BuildMitsubishi()
{
	auto mitsuBuilder = std::make_shared<pattern::creational::MitsubishiBuilder>();
	pattern::creational::Director dir{ mitsuBuilder };

	std::cout << std::endl << "Mitsubishi" << std::endl;

	std::shared_ptr<pattern::creational::Car> car = dir.ConstructCar();
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
