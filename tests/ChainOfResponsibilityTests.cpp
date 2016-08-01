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

#include "behavioral/ChainOfResponsibility.h"

#include <UnitTest++/UnitTest++.h>

#include <ctime>

SUITE(ChainOfResponsibilityTest)
{
	TEST(BaseTest)
	{
		srand(time(0));

		auto root = std::make_shared<pattern::behavioral::Handler1>();
		auto two = std::make_shared<pattern::behavioral::Handler2>();
		auto thr = std::make_shared<pattern::behavioral::Handler3>();
		root->Add(two);
		root->Add(thr);
		thr->SetNext(root);

		for (int i = 1; i < 10; i++) {
			root->Handle(i);
			std::cout << '\n';
		}
	}

	TEST(ChainAndCompositeTest)
	{
		using pattern::behavioral::Primitive;
		using pattern::behavioral::Composite;

		srand(time(0));                                      // 1
		auto seven = std::make_shared<Primitive>(7);         // |
		auto six = std::make_shared<Primitive>(6, seven);    // +-- 2
		auto three = std::make_shared<Composite>(3, six);    // |   |
		three->Add(six);                                     // |   |
		three->Add(seven);                                   // |   +-- 4 5
		auto five = std::make_shared<Primitive>(5, three);   // |
		auto four = std::make_shared<Primitive>(4, five);    // +-- 3
		auto two = std::make_shared<Composite>(2, four);     // |   |
		two->Add(four);                                      // |   |
		two->Add(five);                                      // |   +-- 6 7
		auto one = std::make_shared<Composite>(1, two);      // |
		auto nine = std::make_shared<Primitive>(9, one);     // +-- 8 9
		auto eight = std::make_shared<Primitive>(8, nine);
		one->Add(two);
		one->Add(three);
		one->Add(eight);
		one->Add(nine);
		seven->SetNext(eight);

		std::cout << "\ntraverse: ";
		one->Traverse();
		std::cout << '\n';
		for (int i = 0; i < 8; i++) {
			one->Volunteer();
			std::cout << '\n';
		}
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}
