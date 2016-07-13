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

#include "creational/Singleton.h"

#include <UnitTest++/UnitTest++.h>

SUITE(SingletonTest)
{
	TEST(SessionTest)
	{
		auto& session = pattern::creational::Session::GetInstance();
		auto status = session.Open();
		CHECK(status == pattern::creational::STATUS::OPENED);
		CHECK(session.GetStatus() == pattern::creational::STATUS::OPENED);
		status = session.Close();
		CHECK(status == pattern::creational::STATUS::CLOSED);
		CHECK(session.GetStatus() == pattern::creational::STATUS::CLOSED);
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}
