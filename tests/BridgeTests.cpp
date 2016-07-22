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

#include "structural/Bridge.h"

#include <UnitTest++/UnitTest++.h>

SUITE(BridgeTest)
{
	TEST(StConsoleLoggerTest)
	{
		std::unique_ptr<pattern::structural::Logger> logger =
			std::make_unique<pattern::structural::ConsoleLogger>();
		std::string str{ "message" };
		logger->Log(str);
	}

	TEST(StFileLoggerTest)
	{
		std::unique_ptr<pattern::structural::Logger> logger =
			std::make_unique<pattern::structural::FileLogger>("log.txt");
		std::string str{ "message" };
		logger->Log(str);
	}

	TEST(StSocketLoggerTest)
	{
		std::unique_ptr<pattern::structural::Logger> logger =
			std::make_unique<pattern::structural::SocketLogger>("localhost", 80);
		std::string str{ "message" };
		logger->Log(str);
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}
