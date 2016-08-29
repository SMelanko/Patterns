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

#pragma once

#ifndef PATTERNS_COMMAND_H
#define PATTERNS_COMMAND_H

#include <iostream>
#include <memory>
#include <string>

namespace pattern
{
namespace behavioral
{

class GarageDoor
{
public:
	void Down()
	{
		std::cout << "GarageDoor: Door is Down." << std::endl;
	}
	void Stop()
	{
		std::cout << "GarageDoor: Door is Stop." << std::endl;
	}
	void Up()
	{
		std::cout << "GarageDoor: Door is Up." << std::endl;
	}
};

using GarageDoorPtr = std::shared_ptr<GarageDoor>;

class Light
{
public:
	void On()
	{
		std::cout << "Light: Light is On." << std::endl;
	}
};

using LightPtr = std::shared_ptr<Light>;

class Command
{
public:
	virtual ~Command() noexcept = default;

	virtual void Execute() = 0;
};

using CommandPtr = std::shared_ptr<Command>;

class LightOnCommand : public Command
{
public:
	explicit LightOnCommand(const LightPtr light)
		: _light{ light }
	{
	}

	void Execute() override
	{
		_light->On();
	}

private:
	LightPtr _light;
};

class GarageDoorOpenCommand : public Command
{
public:
	explicit GarageDoorOpenCommand(const GarageDoorPtr garageDoor)
		: _garageDoor{ garageDoor }
	{
	}

	void Execute() override
	{
		_garageDoor->Up();
	}

private:
	GarageDoorPtr _garageDoor;
};

class SimpleRemoteControl
{
public:
	void ButtonWasPressed()
	{
		_slot->Execute();
	}

	void SetCommand(const CommandPtr command) noexcept
	{
		_slot = command;
	}

private:
	CommandPtr _slot;
};

} // namespace behavioral
} // namespace pattern

#endif // PATTERNS_STRATEGY_H
