///////////////////////////////////////////////////////////////////////////////
///
/// Copyright (c) 2016 Slava Melanko. All rights reserved.
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

static void CreateMacGui()
{
	std::unique_ptr<pattern::creational::GuiFactory> guiFactory
		= std::make_unique<pattern::creational::MacFactory>();
	std::unique_ptr<pattern::creational::Button> macBtn{
		guiFactory->CreateButton() };
	macBtn->Paint();
	std::unique_ptr<pattern::creational::ScrollBar> macScroll{
		guiFactory->CreateScrollBar() };
	macScroll->Paint();
}

static void CreateUbuntuGui()
{
	std::unique_ptr<pattern::creational::GuiFactory> guiFactory
		= std::make_unique<pattern::creational::UbuntuFactory>();
	std::unique_ptr<pattern::creational::Button> ubuntuBtn{
		guiFactory->CreateButton() };
	ubuntuBtn->Paint();
	std::unique_ptr<pattern::creational::ScrollBar> ubuntuScroll{
		guiFactory->CreateScrollBar() };
	ubuntuScroll->Paint();
}

static void CreateWinGui()
{
	std::unique_ptr<pattern::creational::GuiFactory> guiFactory
		= std::make_unique<pattern::creational::WinFactory>();
	std::unique_ptr<pattern::creational::Button> winBtn{
		guiFactory->CreateButton() };
	winBtn->Paint();
	std::unique_ptr<pattern::creational::ScrollBar> winScroll{
		guiFactory->CreateScrollBar() };
	winScroll->Paint();
}

SUITE(AbstractFactoryTest)
{
	TEST(MacGuiTest)
	{
		CreateMacGui();
	}

	TEST(UbuntuGuiTest)
	{
		CreateUbuntuGui();
	}

	TEST(WinGuiTest)
	{
		CreateWinGui();
	}
}

int main(int, const char *[])
{
	return UnitTest::RunAllTests();
}
