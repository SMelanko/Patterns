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

#include "structural/Flyweight.h"

#include <UnitTest++/UnitTest++.h>

SUITE(FlyweightTest)
{
	TEST(DialogTest)
	{
		std::vector<std::shared_ptr<pattern::structural::DialogBox>> dialogs;
		dialogs.reserve(2);
		dialogs.push_back(std::make_shared<pattern::structural::FileSelection>(
			pattern::structural::FlyweightFactory::GetIcon("go"),
			pattern::structural::FlyweightFactory::GetIcon("stop"),
			pattern::structural::FlyweightFactory::GetIcon("select")));
		dialogs.push_back(std::make_shared<pattern::structural::CommitTransaction>(
			pattern::structural::FlyweightFactory::GetIcon("select"),
			pattern::structural::FlyweightFactory::GetIcon("stop"),
			pattern::structural::FlyweightFactory::GetIcon("undo")));

		for (const auto& dialog : dialogs) {
			dialog->Draw();
		}

		pattern::structural::FlyweightFactory::ReportTheIcons();
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}
