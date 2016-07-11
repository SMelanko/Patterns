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

#include "creational/AbstractFactory.h"

#include <UnitTest++/UnitTest++.h>

#include <memory>

using GuiFactoryPtr = std::unique_ptr<pattern::creational::GuiFactory>;
using ButtonPtr = std::unique_ptr<pattern::creational::Button>;
using ScrollBarPtr = std::unique_ptr<pattern::creational::ScrollBar>;

static void CreateCurrentOsGui()
{
	GuiFactoryPtr guiFactory = nullptr;
#if defined(_WIN32) || defined(_WIN64)
	guiFactory = std::make_unique<pattern::creational::WinFactory>();
#elif __APPLE__
	guiFactory = std::make_unique<pattern::creational::MacFactory>();
#elif __linux
	guiFactory = std::make_unique<pattern::creational::UbuntuFactory>();
#endif
	ButtonPtr btn{ guiFactory->CreateButton() };
	btn->Paint();
	ScrollBarPtr scroll{ guiFactory->CreateScrollBar() };
	scroll->Paint();
}

static void CreateMacGui()
{
	GuiFactoryPtr guiFactory = std::make_unique<pattern::creational::MacFactory>();
	ButtonPtr macBtn{ guiFactory->CreateButton() };
	macBtn->Paint();
	ScrollBarPtr macScroll{ guiFactory->CreateScrollBar() };
	macScroll->Paint();
}

static void CreateUbuntuGui()
{
	GuiFactoryPtr guiFactory = std::make_unique<pattern::creational::UbuntuFactory>();
	ButtonPtr ubuntuBtn{ guiFactory->CreateButton() };
	ubuntuBtn->Paint();
	ScrollBarPtr ubuntuScroll{ guiFactory->CreateScrollBar() };
	ubuntuScroll->Paint();
}

static void CreateWinGui()
{
	GuiFactoryPtr guiFactory = std::make_unique<pattern::creational::WinFactory>();
	ButtonPtr winBtn{ guiFactory->CreateButton() };
	winBtn->Paint();
	ScrollBarPtr winScroll{ guiFactory->CreateScrollBar() };
	winScroll->Paint();
}

static void TestFuncHandler(std::function<void()> func)
{
	std::cout << std::endl;
	func();
	std::cout << std::endl;
}

SUITE(AbstractFactoryTest)
{
	TEST(MacGuiTest)
	{
		TestFuncHandler(CreateMacGui);
	}

	TEST(UbuntuGuiTest)
	{
		TestFuncHandler(CreateUbuntuGui);
	}

	TEST(WinGuiTest)
	{
		TestFuncHandler(CreateWinGui);
	}

	TEST(CurrentOsWidgetTest)
	{
		TestFuncHandler(CreateCurrentOsGui);
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}
