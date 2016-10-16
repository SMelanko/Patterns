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

#include <algorithm>
#include <array>

#include <gsl/gsl>

constexpr size_t imageArraySize = 5;
using ImagePtr = std::shared_ptr<pattern::structural::Image>;
using ImageArray = std::array<ImagePtr, imageArraySize>;

ImageArray InitImgArray()
{
	ImageArray imgs;
	for (size_t i = 0; i < imageArraySize; ++i) {
		imgs[i] = std::make_shared<pattern::structural::ImageProxy>();
	}

	return imgs;
}

SUITE(ProxyTest)
{
	TEST(ProxyImgTest)
	{
		auto _ = gsl::finally([]() { std::cout << std::endl << std::endl; });

		auto images = InitImgArray();

		for (size_t i = 0; i < imageArraySize; ++i) {
			if (i % 2 == 0) {
				continue;
			}

			images[i]->Draw();
		}
	}

	TEST(ProxyAllImgTest)
	{
		auto images = InitImgArray();

		std::for_each(std::begin(images), std::end(images), [](ImagePtr image) {
			image->Draw();
		});
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}
