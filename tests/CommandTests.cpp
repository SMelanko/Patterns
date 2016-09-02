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
using pattern::behavioral::GarageDoor;
using pattern::behavioral::Light;
using pattern::behavioral::Stereo;
using pattern::behavioral::Command;
using pattern::behavioral::CommandPtr;
using pattern::behavioral::GarageDoorOpenCommand;
using pattern::behavioral::GarageDoorCloseCommand;
using pattern::behavioral::LightOnCommand;
using pattern::behavioral::LightOffCommand;
using pattern::behavioral::StereoOnWithCDCommand;
using pattern::behavioral::StereoOffCommand;

#define CHECK_ON_BUTTON(remote, slot) \
	remote->OnButtonWasPressed(slot);
#define CHECK_OFF_BUTTON(remote, slot) \
	remote->OffButtonWasPressed(slot);

template<typename T = size_t,
	typename Dummy = typename std::enable_if<std::is_integral<T>::value>::type>
static void TestButtons(RemoteControlPtr remote, const T slot = 0U)
{
	CHECK_ON_BUTTON(remote, slot)
	std::cout << '\t';
	CHECK_OFF_BUTTON(remote, slot)
	std::cout << '\n';
}

void SetLightCommands(RemoteControlPtr remote, const size_t slot = 0)
{
	auto light = std::make_shared<Light>();
	CommandPtr lightOn = std::make_shared<LightOnCommand>(light);
	CommandPtr lightOff = std::make_shared<LightOffCommand>(light);

	remote->SetCommand(slot, lightOn, lightOff);
}

void SetGarageDoorCommands(RemoteControlPtr remote, const size_t slot = 0)
{
	auto gd = std::make_shared<GarageDoor>();
	CommandPtr gdOpen = std::make_shared<GarageDoorOpenCommand>(gd);
	CommandPtr gdClose = std::make_shared<GarageDoorCloseCommand>(gd);

	remote->SetCommand(slot, gdOpen, gdClose);
}

void SetStereoCommands(RemoteControlPtr remote, const size_t slot = 0)
{
	auto stereo = std::make_shared<Stereo>();
	CommandPtr stereoOn = std::make_shared<StereoOnWithCDCommand>(stereo);
	CommandPtr stereoOff = std::make_shared<StereoOffCommand>(stereo);

	remote->SetCommand(slot, stereoOn, stereoOff);
}

SUITE(CommandTest)
{
	TEST(LightTest)
	{
		auto remote = std::make_shared<RemoteControl>();
		SetLightCommands(remote);
		TestButtons(remote);
	}

	TEST(GarageDoorTest)
	{
		auto remote = std::make_shared<RemoteControl>();
		SetGarageDoorCommands(remote);
		TestButtons(remote);
	}

	TEST(StereoTest)
	{
		auto remote = std::make_shared<RemoteControl>();
		SetStereoCommands(remote);
		TestButtons(remote);
	}

	TEST(AllTest)
	{
		auto remote = std::make_shared<RemoteControl>();

		size_t slot = 0;
		SetLightCommands(remote, slot++);
		SetGarageDoorCommands(remote, slot++);
		SetStereoCommands(remote, slot++);

		for (decltype(slot) i = 0; i < slot; ++i) {
			TestButtons(remote, i);
		}
	}

	TEST(UndoTest)
	{
		auto remote = std::make_shared<RemoteControl>();
		SetGarageDoorCommands(remote);
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
