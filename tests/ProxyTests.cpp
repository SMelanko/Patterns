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

#include "structural/Proxy.h"

#include <UnitTest++/UnitTest++.h>

#include <array>

#include <include/gsl_util.h>

SUITE(ProxyTest)
{
	TEST(ProxyImgTest)
	{
		auto _ = gsl::finally([]() { std::cout << std::endl << std::endl; });

		constexpr size_t size = 5;
		std::array<pattern::structural::Image, size> images;

		for (size_t i = 0; i < size; ++i) {
			if (i % 2 == 0) {
				continue;
			}

			images[i].Draw();
		}
	}

	TEST(ProxyAllImgTest)
	{
		constexpr size_t size = 5;
		std::array<pattern::structural::Image, size> images;

		for (size_t i = 0; i < size; ++i) {
			images[i].Draw();
		}
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}
