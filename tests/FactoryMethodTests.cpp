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
	TEST(GoogleAdXTest)
	{
		auto adx = pc::ExchangeConnectorFactory::Create("GoogleAdX");
		CHECK(adx->GetId() == pc::EXCHANGE_CONNECTOR_ID::GOOGLE_ADX);
	}

	TEST(SmaatoTest)
	{
		auto smaato = pc::ExchangeConnectorFactory::Create("Smaato");
		CHECK(smaato->GetId() == pc::EXCHANGE_CONNECTOR_ID::SMAATO);
	}

	TEST(UnknownExchangeTest)
	{
		auto unknown = pc::ExchangeConnectorFactory::Create("Unknown");
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

	TEST(CreateInfantrymanTest)
	{
		pc::WarriorFactoryUnPtr archerFactory = std::make_unique<pc::InfantryFactory>();
		constexpr size_t size = 10;
		std::vector<pc::WarriorShPtr> troop;
		troop.reserve(size);
		for (size_t i = 0; i < size; ++i) {
			troop.push_back(archerFactory->CreateWarrior());
		}
		CHECK(troop.size() == size);
		for_each(std::begin(troop), std::end(troop), [] (pc::WarriorShPtr w) {
			CHECK(w->GetId() == pc::WARRIOR_ID::INFANTRYMAN);
		});
	}

	TEST(CreateArcherTest)
	{
		pc::WarriorFactoryUnPtr archerFactory = std::make_unique<pc::ArchersFactory>();
		constexpr size_t size = 10;
		std::vector<pc::WarriorShPtr> troop;
		troop.reserve(size);
		for (size_t i = 0; i < size; ++i) {
			troop.push_back(archerFactory->CreateWarrior());
		}
		CHECK(troop.size() == size);
		for_each(std::begin(troop), std::end(troop), [] (pc::WarriorShPtr w) {
			CHECK(w->GetId() == pc::WARRIOR_ID::ARCHER);
		});
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}
