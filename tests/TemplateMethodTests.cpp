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

#include "behavioral/TemplateMethod.h"

#include <UnitTest++/UnitTest++.h>

using pattern::behavioral::CaffeineBeverage;
using pattern::behavioral::Coffee;
using pattern::behavioral::Tea;

#define TEST_BEVERAGE(beverage) \
	std::cout << '\n'; \
	beverage->PrepareRecipe(); \
	std::cout << '\n'; \
	CHECK(true);

SUITE(TemplateMethodTest)
{
	TEST(TeaTest)
	{
		auto tea = std::make_unique<Tea>();
		TEST_BEVERAGE(tea);
	}

	TEST(CaffeeTest)
	{
		auto coffee = std::make_unique<Coffee>();
		TEST_BEVERAGE(coffee);
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}
