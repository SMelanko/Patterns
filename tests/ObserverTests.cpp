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

#include "behavioral/Observer.h"

#include <UnitTest++/UnitTest++.h>

using pattern::behavioral::Subject;
using pattern::behavioral::BinObserver;
using pattern::behavioral::OctObserver;
using pattern::behavioral::HexObserver;

SUITE(ObserverTest)
{
	TEST(AllNumConvertTest)
	{
		Subject subj;
		BinObserver bin{ subj };
		OctObserver oct{ subj };
		HexObserver hex{ subj };
		CHECK(subj.Count() == 3);
		subj.SetVal(11);
		std::cout << std::endl;
	}

	TEST(NumConvertWithDetachTest)
	{
		Subject subj;
		BinObserver bin{ subj };
		OctObserver oct{ subj };
		HexObserver hex{ subj };
		CHECK(subj.Count() == 3);
		subj.SetVal(10);
		subj.Detach(&bin);
		CHECK(subj.Count() == 2);
		subj.SetVal(20);
		std::cout << std::endl;
	}

	TEST(NumConvertWith2DetachTest)
	{
		Subject subj;
		BinObserver bin{ subj };
		OctObserver oct{ subj };
		HexObserver hex{ subj };
		CHECK(subj.Count() == 3);
		subj.SetVal(7);
		subj.Detach(&bin);
		CHECK(subj.Count() == 2);
		subj.Detach(&bin);
		CHECK(subj.Count() == 2);
		subj.SetVal(33);
		std::cout << std::endl;
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}
