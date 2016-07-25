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

#include <include/gsl_util.h>

using InterfacePtr = std::unique_ptr<pattern::structural::Interface>;

SUITE(DecoratorTest)
{
	TEST(DecorTest)
	{
		auto _ = gsl::finally([] { std::cout << std::endl; });

		InterfacePtr x{
			new pattern::structural::X{
				std::make_shared<pattern::structural::Core>() } };
		InterfacePtr xy{
			new pattern::structural::Y{
				std::make_shared<pattern::structural::X>(
					std::make_shared<pattern::structural::Core>()) } };
		InterfacePtr xyz{
			new pattern::structural::Z{
				std::make_shared<pattern::structural::Y>(
					std::make_shared<pattern::structural::X>(
						std::make_shared<pattern::structural::Core>())) } };

		std::cout << std::endl;
		x->DoIt();
		std::cout << std::endl;
		xy->DoIt();
		std::cout << std::endl;
		xyz->DoIt();
		std::cout << std::endl << std::endl;
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}

