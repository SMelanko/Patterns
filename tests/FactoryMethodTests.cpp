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

#include "creational/FactoryMethod.h"

#include <UnitTest++/UnitTest++.h>

#include <vector>

namespace pc = pattern::creational;

SUITE(FactoryMethodTest)
{
	TEST(InfantrymanTest)
	{
		auto infantryman = pc::Factory::CreateInstance("Infantryman");
		CHECK(infantryman->GetId() == pc::WARRIOR_ID::INFANTRYMAN);
		infantryman->PrintInfo();
	}

	TEST(ArcherTest)
	{
		auto archer = pc::Factory::CreateInstance("Archer");
		CHECK(archer->GetId() == pc::WARRIOR_ID::ARCHER);
		archer->PrintInfo();
	}

	TEST(SetTest)
	{
		constexpr uint32_t size = 10;
		std::vector<pc::WarriorUnPtr> v(size);
		for (uint32_t i = 0; i < size; ++i) {
			v[i] = (i % 2 == 0) ? pc::Factory::CreateInstance("Archer")
				: pc::Factory::CreateInstance("Infantryman");
		}
		for (uint32_t i = 0; i < size; ++i) {
			if (i % 2 == 0) {
				CHECK(v[i]->GetId() == pc::WARRIOR_ID::ARCHER);
			} else {
				CHECK(v[i]->GetId() == pc::WARRIOR_ID::INFANTRYMAN);
			}
		}
	}

	TEST(UnknownWarriorTest)
	{
		auto unknown = pc::Factory::CreateInstance("Unknown");
		CHECK(unknown == nullptr);
	}

	TEST(CreateProductATest)
	{
		auto a = pc::ProductFactory::Create(pc::PRODUCT_ID::PRODUCT_A, 123);
		CHECK(a->GetId() == pc::PRODUCT_ID::PRODUCT_A);
	}

	TEST(CreateProductAFailTest)
	{
		auto a = pc::ProductFactory::Create(pc::PRODUCT_ID::PRODUCT_A, "");
		CHECK(a == nullptr);
	}

	TEST(CreateProductBTest)
	{
		auto b = pc::ProductFactory::Create(pc::PRODUCT_ID::PRODUCT_B, "");
		CHECK(b->GetId() == pc::PRODUCT_ID::PRODUCT_B);
	}

	TEST(CreateProductBFailTest)
	{
		auto b = pc::ProductFactory::Create(pc::PRODUCT_ID::PRODUCT_B, 321);
		CHECK(b == nullptr);
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}
