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

#include "behavioral/Command.h"

#include <UnitTest++/UnitTest++.h>

using pattern::behavioral::RemoteControl;
using pattern::behavioral::RemoteControlPtr;
using pattern::behavioral::CeilingFan;
using pattern::behavioral::CeilingFanPtr;
using pattern::behavioral::GarageDoor;
using pattern::behavioral::GarageDoorPtr;
using pattern::behavioral::Light;
using pattern::behavioral::LightPtr;
using pattern::behavioral::Stereo;
using pattern::behavioral::StereoPtr;
using pattern::behavioral::Command;
using pattern::behavioral::CommandPtr;
using pattern::behavioral::CeilingFanLowCommand;
using pattern::behavioral::CeilingFanMediumCommand;
using pattern::behavioral::CeilingFanHighCommand;
using pattern::behavioral::CeilingFanOffCommand;
using pattern::behavioral::GarageDoorOpenCommand;
using pattern::behavioral::GarageDoorCloseCommand;
using pattern::behavioral::LightOnCommand;
using pattern::behavioral::LightOffCommand;
using pattern::behavioral::StereoOnWithCDCommand;
using pattern::behavioral::StereoOffCommand;
using pattern::behavioral::MacroCommand;

#define CHECK_ON_BUTTON(remote, slot) \
	remote->OnButtonWasPressed(slot);
#define CHECK_OFF_BUTTON(remote, slot) \
	remote->OffButtonWasPressed(slot);

template<typename T = size_t,
	typename Dummy = std::enable_if_t<std::is_integral<T>::value>>
static void TestButtons(RemoteControlPtr remote, const T slot = 0U)
{
	CHECK_ON_BUTTON(remote, slot)
	std::cout << '\t';
	CHECK_OFF_BUTTON(remote, slot)
	std::cout << '\n';
}

void SetCeilingFanCommands(RemoteControlPtr remote, size_t& slot,
	CeilingFanPtr cf = std::make_shared<CeilingFan>())
{
	CommandPtr cfLow = std::make_shared<CeilingFanLowCommand>(cf);
	CommandPtr cfMed = std::make_shared<CeilingFanMediumCommand>(cf);
	CommandPtr cfHigh = std::make_shared<CeilingFanHighCommand>(cf);
	CommandPtr cfOff = std::make_shared<CeilingFanOffCommand>(cf);

	remote->SetCommand(slot++, cfLow, cfOff);
	remote->SetCommand(slot++, cfMed, cfOff);
	remote->SetCommand(slot++, cfHigh, cfOff);
}

void SetGarageDoorCommands(RemoteControlPtr remote, size_t& slot,
	GarageDoorPtr gd = std::make_shared<GarageDoor>())
{
	CommandPtr gdOpen = std::make_shared<GarageDoorOpenCommand>(gd);
	CommandPtr gdClose = std::make_shared<GarageDoorCloseCommand>(gd);

	remote->SetCommand(slot++, gdOpen, gdClose);
}

void SetLightCommands(RemoteControlPtr remote, size_t& slot,
	LightPtr light = std::make_shared<Light>())
{
	CommandPtr lightOn = std::make_shared<LightOnCommand>(light);
	CommandPtr lightOff = std::make_shared<LightOffCommand>(light);

	remote->SetCommand(slot++, lightOn, lightOff);
}

void SetStereoCommands(RemoteControlPtr remote, size_t& slot,
	StereoPtr stereo = std::make_shared<Stereo>())
{
	CommandPtr stereoOn = std::make_shared<StereoOnWithCDCommand>(stereo);
	CommandPtr stereoOff = std::make_shared<StereoOffCommand>(stereo);

	remote->SetCommand(slot++, stereoOn, stereoOff);
}

SUITE(CommandTest)
{
	TEST(CeilingFanTest)
	{
		auto remote = std::make_shared<RemoteControl>(3);

		size_t slot = 0U;
		auto cf = std::make_shared<CeilingFan>();
		SetCeilingFanCommands(remote, slot, cf);

		remote->OnButtonWasPressed(0);
		CHECK(cf->GetSpeed() == CeilingFan::Speed::Low);
		remote->OffButtonWasPressed(0);
		CHECK(cf->GetSpeed() == CeilingFan::Speed::Off);
		remote->UndoButtonWasPressed();
		CHECK(cf->GetSpeed() == CeilingFan::Speed::Low);
		remote->OnButtonWasPressed(1);
		CHECK(cf->GetSpeed() == CeilingFan::Speed::Medium);
		remote->OnButtonWasPressed(2);
		CHECK(cf->GetSpeed() == CeilingFan::Speed::High);
		remote->UndoButtonWasPressed();
		CHECK(cf->GetSpeed() == CeilingFan::Speed::Medium);
		std::cout << std::endl;
	}

	TEST(GarageDoorTest)
	{
		auto remote = std::make_shared<RemoteControl>();

		size_t slot = 0U;
		SetGarageDoorCommands(remote, slot);
		TestButtons(remote);
	}

	TEST(LightTest)
	{
		auto remote = std::make_shared<RemoteControl>();

		size_t slot = 0U;
		SetLightCommands(remote, slot);
		TestButtons(remote);
	}

	TEST(StereoTest)
	{
		auto remote = std::make_shared<RemoteControl>();

		size_t slot = 0U;
		SetStereoCommands(remote, slot);
		TestButtons(remote);
	}

	TEST(MacroTest)
	{
		auto remote = std::make_shared<RemoteControl>();

		auto light = std::make_shared<Light>();
		CommandPtr lightOn = std::make_shared<LightOnCommand>(light);
		CommandPtr lightOff = std::make_shared<LightOffCommand>(light);

		auto stereo = std::make_shared<Stereo>();
		CommandPtr stereoOn = std::make_shared<StereoOnWithCDCommand>(stereo);
		CommandPtr stereoOff = std::make_shared<StereoOffCommand>(stereo);

		auto onCommands = { lightOn, stereoOn };
		CommandPtr macroOn = std::make_shared<MacroCommand>(onCommands);
		auto offCommands = { stereoOff, lightOff };
		CommandPtr macroOff = std::make_shared<MacroCommand>(offCommands);

		remote->SetCommand(0, macroOn, macroOff);
		TestButtons(remote);
	}

	TEST(AllTest)
	{
		auto remote = std::make_shared<RemoteControl>(7);

		size_t slot = 0U;
		SetCeilingFanCommands(remote, slot);
		SetGarageDoorCommands(remote, slot);
		SetLightCommands(remote, slot);
		SetStereoCommands(remote, slot);

		for (decltype(slot) i = 0; i < slot; ++i) {
			TestButtons(remote, i);
		}
	}

	TEST(UndoTest)
	{
		auto remote = std::make_shared<RemoteControl>();
		size_t slot = 0U;
		SetGarageDoorCommands(remote, slot);
		TestButtons(remote);
		std::cout << "Undo was pressed: ";
		remote->UndoButtonWasPressed();
		std::cout << std::endl;
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}
