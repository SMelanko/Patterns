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

#include "behavioral/State.h"

#include <UnitTest++/UnitTest++.h>

#include "gsl/gsl_util"

SUITE(StateTest)
{
	TEST(GumballTest1)
	{
		auto _ = gsl::finally([](){ std::cout << std::endl; });

		auto gm = std::make_unique<pattern::behavioral::GunballMachine>(5);
		gm->InsertQuarter();
		gm->TurnCrank();
	}

	TEST(GumballTest2)
	{
		auto _ = gsl::finally([](){ std::cout << std::endl; });

		auto gm = std::make_unique<pattern::behavioral::GunballMachine>(5);
		gm->InsertQuarter();
		gm->EjectQuarter();
		gm->TurnCrank();
	}

	TEST(GumballTest3)
	{
		auto _ = gsl::finally([](){ std::cout << std::endl; });

		auto gm = std::make_unique<pattern::behavioral::GunballMachine>(5);
		gm->InsertQuarter();
		gm->TurnCrank();
		gm->InsertQuarter();
		gm->TurnCrank();
		gm->EjectQuarter();
	}

	TEST(GumballTest4)
	{
		auto _ = gsl::finally([](){ std::cout << std::endl; });

		auto gm = std::make_unique<pattern::behavioral::GunballMachine>(3);
		gm->InsertQuarter();
		gm->TurnCrank();
		gm->InsertQuarter();
		gm->TurnCrank();
		gm->EjectQuarter();
		gm->InsertQuarter();
		gm->InsertQuarter();
		gm->TurnCrank();
		gm->TurnCrank();
		gm->InsertQuarter();
		gm->TurnCrank();
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}
