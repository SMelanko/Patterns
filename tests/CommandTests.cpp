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
using pattern::behavioral::Command;
using pattern::behavioral::CommandPtr;
using pattern::behavioral::GarageDoorOpenCommand;
using pattern::behavioral::GarageDoorCloseCommand;
using pattern::behavioral::LightOnCommand;
using pattern::behavioral::LightOffCommand;

void TestButtons(RemoteControlPtr remote, const size_t slot)
{
	remote->OnButtonWasPressed(slot);
	std::cout << '\t';
	remote->OffButtonWasPressed(slot);
	std::cout << '\n';
}

SUITE(CommandTest)
{
	TEST(LightTest)
	{
		auto remote = std::make_shared<RemoteControl>();
		auto light = std::make_shared<Light>();
		CommandPtr lightOn = std::make_shared<LightOnCommand>(light);
		CommandPtr lightOff = std::make_shared<LightOffCommand>(light);

		remote->SetCommand(0, lightOn, lightOff);
		TestButtons(remote, 0);
	}

	TEST(GarageDoorTest)
	{
		auto remote = std::make_shared<RemoteControl>();
		auto gd = std::make_shared<GarageDoor>();
		CommandPtr gdOpen = std::make_shared<GarageDoorOpenCommand>(gd);
		CommandPtr gdClose = std::make_shared<GarageDoorCloseCommand>(gd);

		remote->SetCommand(0, gdOpen, gdClose);
		TestButtons(remote, 0);
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}
