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

using pattern::behavioral::SimpleRemoteControl;
using pattern::behavioral::GarageDoor;
using pattern::behavioral::Light;
using pattern::behavioral::Command;
using pattern::behavioral::CommandPtr;
using pattern::behavioral::GarageDoorOpenCommand;
using pattern::behavioral::LightOnCommand;

SUITE(CommandTest)
{
	TEST(LightOnTest)
	{
		auto remote = std::make_unique<SimpleRemoteControl>();
		auto light = std::make_shared<Light>();
		CommandPtr lightOn = std::make_shared<LightOnCommand>(light);

		remote->SetCommand(lightOn);
		remote->ButtonWasPressed();
	}

	TEST(GarageDoorOpenTest)
	{
		auto remote = std::make_unique<SimpleRemoteControl>();
		auto gd = std::make_shared<GarageDoor>();
		CommandPtr gdOpen = std::make_shared<GarageDoorOpenCommand>(gd);

		remote->SetCommand(gdOpen);
		remote->ButtonWasPressed();
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}
