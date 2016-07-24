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

#include "structural/Composite.h"

#include <UnitTest++/UnitTest++.h>

//! Creates Roman legion.
auto CreateLegion()
{
	std::shared_ptr<pattern::structural::CompositeUnit> legion =
		std::make_shared<pattern::structural::CompositeUnit>();
	// Roman legion contains:
	for (int i = 0; i < 3000; ++i) {
		legion->AddUnit(std::make_shared<pattern::structural::Infantryman>());
	}
	for (int i = 0; i < 1200; ++i) {
		legion->AddUnit(std::make_shared<pattern::structural::Archer>());
	}
	for (int i = 0; i < 300; ++i) {
		legion->AddUnit(std::make_shared<pattern::structural::Horseman>());
	}

	return legion;
}

SUITE(AbstractFactoryTest)
{
	TEST(EmptyTest)
	{
		auto army = std::make_unique<pattern::structural::CompositeUnit>();
		for (int i = 0; i < 4; ++i) {
			army->AddUnit(CreateLegion());
		}

		CHECK(army->GetStrength() == 32400);
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}
