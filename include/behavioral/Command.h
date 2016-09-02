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
#include <vector>

namespace pattern
{
namespace behavioral
{

//
// Receiver.
//

class GarageDoor
{
public:
	void Down() const noexcept
	{
		std::cout << "GarageDoor::Down";
	}
	void Stop() const noexcept
	{
		std::cout << "GarageDoor::Stop";
	}
	void Up() const noexcept
	{
		std::cout << "GarageDoor::Up";
	}
};

using GarageDoorPtr = std::shared_ptr<GarageDoor>;

class Light
{
public:
	void On() const noexcept
	{
		std::cout << "Light::On";
	}
	void Off() const noexcept
	{
		std::cout << "Light::Off";
	}
};

using LightPtr = std::shared_ptr<Light>;

class Stereo
{
public:
	void On() const noexcept
	{
		std::cout << "Stereo::On";
	}
	void Off() const noexcept
	{
		std::cout << "Stereo::Off";
	}
	void SetCD() const noexcept
	{
		std::cout << "Stereo::SetCD";
	}
	void SetVolume(const uint16_t val) const noexcept
	{
		std::cout << "Stereo::SetVolume " << val;
	}
};

using StereoPtr = std::shared_ptr<Stereo>;

//
// Command.
//

class Command
{
public:
	virtual ~Command() noexcept = default;

	virtual void Execute() = 0;
	virtual void Undo() = 0;
};

using CommandPtr = std::shared_ptr<Command>;

//
// Concrete command.
//

class NoCommand : public Command
{
public:
	void Execute() override
	{
	}
	void Undo() override
	{
	}
};

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
	void Undo() override
	{
		_light->Off();
	}

private:
	LightPtr _light;
};

class LightOffCommand : public Command
{
public:
	explicit LightOffCommand(const LightPtr light)
		: _light{ light }
	{
	}

	void Execute() override
	{
		_light->Off();
	}
	void Undo() override
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
	void Undo() override
	{
		_garageDoor->Down();
	}

private:
	GarageDoorPtr _garageDoor;
};

class GarageDoorCloseCommand : public Command
{
public:
	explicit GarageDoorCloseCommand(const GarageDoorPtr garageDoor)
		: _garageDoor{ garageDoor }
	{
	}

	void Execute() override
	{
		_garageDoor->Down();
	}
	void Undo() override
	{
		_garageDoor->Up();
	}

private:
	GarageDoorPtr _garageDoor;
};

class StereoOnWithCDCommand : public Command
{
public:
	explicit StereoOnWithCDCommand(const StereoPtr stereo)
		: _stereo{ stereo }
	{
	}

	void Execute() override
	{
		_stereo->On();
		_stereo->SetCD();
		_stereo->SetVolume(10);
	}
	void Undo() override
	{
		_stereo->Off();
	}

private:
	StereoPtr _stereo;
};

class StereoOffCommand : public Command
{
public:
	explicit StereoOffCommand(const StereoPtr stereo)
		: _stereo{ stereo }
	{
	}

	void Execute() override
	{
		_stereo->Off();
	}
	void Undo() override
	{
		_stereo->On();
		_stereo->SetCD();
		_stereo->SetVolume(10);
	}

private:
	StereoPtr _stereo;
};

//
// Invoker.
//

class RemoteControl
{
	using CommandPtrArray = std::vector<CommandPtr>;

public:
	RemoteControl() noexcept
	{
		constexpr int size = 7;
		_onCommands.resize(size);
		_offCommands.resize(size);
		CommandPtr noCommand = std::make_shared<NoCommand>();
		std::fill(std::begin(_onCommands), std::end(_onCommands), noCommand);
		std::fill(std::begin(_offCommands), std::end(_offCommands), noCommand);
		_undoCommand = noCommand;
	}

	void OnButtonWasPressed(const size_t slot)
	{
		_onCommands[slot]->Execute();
		_undoCommand = _onCommands[slot];
	}
	void OffButtonWasPressed(const size_t slot)
	{
		_offCommands[slot]->Execute();
		_undoCommand = _offCommands[slot];
	}
	void UndoButtonWasPressed()
	{
		_undoCommand->Undo();
	}

	void SetCommand(const size_t slot,
		const CommandPtr onCommand, const CommandPtr offCommand)
	{
		_onCommands[slot] = onCommand;
		_offCommands[slot] = offCommand;
	}

private:
	CommandPtrArray _onCommands;
	CommandPtrArray _offCommands;
	CommandPtr _undoCommand;
};

using RemoteControlPtr = std::shared_ptr<RemoteControl>;

} // namespace behavioral
} // namespace pattern

#endif // PATTERNS_STRATEGY_H
