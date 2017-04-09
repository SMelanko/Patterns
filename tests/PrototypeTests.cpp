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

#include "creational/Prototype.h"

#include <UnitTest++/UnitTest++.h>

#include <vector>

SUITE(PrototypeTest)
{
	TEST(WarriorsTest)
	{
		pattern::creational::PrototypeFactory factory;

		constexpr size_t size = 10;
		std::vector<pattern::creational::WarriorUnPtr> warriors(size);

		for (size_t i = 0; i < size; ++i) {
			auto warrior = (i % 2 == 0) ?
				factory.CreateArcher() : factory.CreateInfantryman();
			warriors[i] = std::move(warrior);
		}

		std::cout << std::endl;
		for(const auto& warrior : warriors) {
			warrior->PrintInfo();
		}
		std::cout << std::endl;
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}
