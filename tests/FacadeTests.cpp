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

#include "structural/Facade.h"

#include <UnitTest++/UnitTest++.h>

SUITE(FacadeTest)
{
	TEST(FacilitiesTest)
	{
		pattern::structural::FacilitiesFacade facilities;

		facilities.SubmitNetworkRequest();
		// Making a call until the work in not finished yet.
		while (!facilities.CheckOnStatus()) ;

		std::cout << "Job completed after only "
			<< facilities.GetNumberOfCalls()
			<< " phone calls" << std::endl << std::endl;
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}


