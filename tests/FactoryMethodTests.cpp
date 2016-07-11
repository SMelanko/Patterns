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

SUITE(FactoryMethodTest)
{
	TEST(InfantrymanTest)
	{
		auto infantryman = pattern::creational::Factory::CreateInstance("Infantryman");
		CHECK(infantryman->GetId() == pattern::creational::WARRIOR_ID::INFANTRYMAN);
		std::cout << std::endl;
		infantryman->PrintInfo();
		std::cout << std::endl;
	}

	TEST(ArcherTest)
	{
		auto archer = pattern::creational::Factory::CreateInstance("Archer");
		CHECK(archer->GetId() == pattern::creational::WARRIOR_ID::ARCHER);
		std::cout << std::endl;
		archer->PrintInfo();
		std::cout << std::endl;
	}

	TEST(SetTest)
	{
		constexpr uint32_t size = 10;
		std::vector<pattern::creational::WarriorPtr> v(size);
		for (uint32_t i = 0; i < size; ++i) {
			v[i] = (i % 2 == 0) ?
				pattern::creational::Factory::CreateInstance("Archer") :
				pattern::creational::Factory::CreateInstance("Infantryman");
		}
		for (uint32_t i = 0; i < size; ++i) {
			if (i % 2 == 0) {
				CHECK(v[i]->GetId() == pattern::creational::WARRIOR_ID::ARCHER);
			} else {
				CHECK(v[i]->GetId() == pattern::creational::WARRIOR_ID::INFANTRYMAN);
			}
		}
	}

	TEST(UnknownWarriorTest)
	{
		auto unknown = pattern::creational::Factory::CreateInstance("Unknown");
		CHECK(unknown == nullptr);
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}
