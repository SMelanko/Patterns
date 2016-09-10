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

#include "structural/Adapter.h"

#include <UnitTest++/UnitTest++.h>

SUITE(AdapterTest)
{
	TEST(AdapterClassicTest)
	{
		std::unique_ptr<pattern::structural::CelsiusSensor> sensor =
			std::make_unique<pattern::structural::Adapter>(
				new pattern::structural::FahrenheitSensor);
		CHECK(sensor->GetTemperature() == 0);
	}

	TEST(AdapterPrivateInheritanceTest)
	{
		std::unique_ptr<pattern::structural::CelsiusSensor1> sensor =
			std::make_unique<pattern::structural::Adapter1>();
		sensor->Adjust();
		CHECK(sensor->GetTemperature() == 0);
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}
