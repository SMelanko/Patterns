#include "creational/AbstractFactory.h"

#include <UnitTest++/UnitTest++.h>

using GuiFactoryPtr = std::unique_ptr<pattern::creational::GuiFactory>;

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
	auto button = guiFactory->CreateButton();
	button->Paint();
	auto scroll = guiFactory->CreateScrollBar();
	scroll->Paint();
}

static void CreateMacGui()
{
	GuiFactoryPtr gf = std::make_unique<pattern::creational::MacFactory>();
	auto macBtn = gf->CreateButton();
	macBtn->Paint();
	auto macScroll = gf->CreateScrollBar();
	macScroll->Paint();
}

static void CreateUbuntuGui()
{
	GuiFactoryPtr gf = std::make_unique<pattern::creational::UbuntuFactory>();
	auto ubuntuBtn = gf->CreateButton();
	ubuntuBtn->Paint();
	auto ubuntuScroll = gf->CreateScrollBar();
	ubuntuScroll->Paint();
}

static void CreateWinGui()
{
	GuiFactoryPtr gf = std::make_unique<pattern::creational::WinFactory>();
	auto winBtn = gf->CreateButton();
	winBtn->Paint();
	auto winScroll = gf->CreateScrollBar();
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
