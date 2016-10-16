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

#include "structural/Decorator.h"

#include <UnitTest++/UnitTest++.h>

#include <gsl/gsl>

using InterfacePtr = std::unique_ptr<pattern::structural::Interface>;

SUITE(DecoratorTest)
{
	TEST(DecoratorXTest)
	{
		auto _ = gsl::finally([] { std::cout << std::endl; });

		InterfacePtr x{
			new pattern::structural::X{
				std::make_shared<pattern::structural::Core>() } };
		x->DoIt();
		std::cout << std::endl;
	}

	TEST(DecoratorXYTest)
	{
		auto _ = gsl::finally([] { std::cout << std::endl; });

		InterfacePtr xy{
			new pattern::structural::Y{
				std::make_shared<pattern::structural::X>(
					std::make_shared<pattern::structural::Core>()) } };
		xy->DoIt();
		std::cout << std::endl;
	}

	TEST(DecoratorXYZTest)
	{
		auto _ = gsl::finally([] { std::cout << std::endl; });

		InterfacePtr xyz{
			new pattern::structural::Z{
				std::make_shared<pattern::structural::Y>(
					std::make_shared<pattern::structural::X>(
						std::make_shared<pattern::structural::Core>())) } };
		xyz->DoIt();
		std::cout << std::endl;
	}

	TEST(DarkRoastWithMilkAndMochaTest)
	{
		pattern::structural::BeveragePtr beverage =
			std::make_shared<pattern::structural::DarkRoast>();
		beverage = std::make_shared<pattern::structural::Milk>(beverage);
		beverage = std::make_shared<pattern::structural::Mocha>(beverage);
		std::cout << beverage->Cost() << "$\t"
			<< beverage->GetDescription() << std::endl << std::endl;
	}

	TEST(DarkRoastWithDoubleMilkAndMochaTest)
	{
		pattern::structural::BeveragePtr beverage =
			std::make_shared<pattern::structural::DarkRoast>();
		beverage = std::make_shared<pattern::structural::Milk>(beverage);
		beverage = std::make_shared<pattern::structural::Milk>(beverage);
		beverage = std::make_shared<pattern::structural::Mocha>(beverage);
		std::cout << beverage->Cost() << "$\t"
			<< beverage->GetDescription() << std::endl << std::endl;
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}

