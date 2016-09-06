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

class CeilingFan
{
public:
	enum class Speed
	{
		Off,
		Low,
		Medium,
		High
	};

public:
	CeilingFan() noexcept = default;

	auto GetSpeed() const noexcept
	{
		return _speed;
	}
	void SetSpeed(const Speed speed) noexcept
	{
		_speed = speed;
	}
	void Off() noexcept
	{
		SetSpeed(Speed::Off);
	}

private:
	Speed _speed = Speed::Off;
};

using CeilingFanPtr = std::shared_ptr<CeilingFan>;

class GarageDoor
{
public:
	void Down() const noexcept
	{
		std::cout << "GarageDoor::Down ";
	}
	void Stop() const noexcept
	{
		std::cout << "GarageDoor::Stop ";
	}
	void Up() const noexcept
	{
		std::cout << "GarageDoor::Up ";
	}
};

using GarageDoorPtr = std::shared_ptr<GarageDoor>;

class Light
{
public:
	void On() const noexcept
	{
		std::cout << "Light::On ";
	}
	void Off() const noexcept
	{
		std::cout << "Light::Off ";
	}
};

using LightPtr = std::shared_ptr<Light>;

class Stereo
{
public:
	void On() const noexcept
	{
		std::cout << "Stereo::On ";
	}
	void Off() const noexcept
	{
		std::cout << "Stereo::Off ";
	}
	void SetCD() const noexcept
	{
		std::cout << "Stereo::SetCD ";
	}
	void SetVolume(const uint16_t val) const noexcept
	{
		std::cout << "Stereo::SetVolume " << val << " ";
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

	virtual void Execute() noexcept = 0;
	virtual void Undo() noexcept = 0;
};

using CommandPtr = std::shared_ptr<Command>;
using CommandPtrArray = std::vector<CommandPtr>;

//
// Concrete command.
//

class NoCommand : public Command
{
public:
	void Execute() noexcept override
	{
	}
	void Undo() noexcept override
	{
	}
};

class CeilingFanCommand : public Command
{
public:
	explicit CeilingFanCommand(const CeilingFanPtr ceilingFan) noexcept
		: _ceilingFan{ ceilingFan }
	{
	}
	virtual ~CeilingFanCommand() noexcept = default;

	void Undo() noexcept override
	{
		_ceilingFan->SetSpeed(_prevSpeed);
	}

protected:
	void Exec(const CeilingFan::Speed speed) noexcept
	{
		_prevSpeed = _ceilingFan->GetSpeed();
		_ceilingFan->SetSpeed(speed);
	}

private:
	CeilingFanPtr _ceilingFan;
	CeilingFan::Speed _prevSpeed;
};

class CeilingFanLowCommand : public CeilingFanCommand
{
public:
	explicit CeilingFanLowCommand(const CeilingFanPtr ceilingFan) noexcept
		: CeilingFanCommand{ ceilingFan }
	{
	}

	void Execute() noexcept override
	{
		CeilingFanCommand::Exec(CeilingFan::Speed::Low);
	}
};

class CeilingFanMediumCommand : public CeilingFanCommand
{
public:
	explicit CeilingFanMediumCommand(const CeilingFanPtr ceilingFan) noexcept
		: CeilingFanCommand{ ceilingFan }
	{
	}

	void Execute() noexcept override
	{
		CeilingFanCommand::Exec(CeilingFan::Speed::Medium);
	}
};

class CeilingFanHighCommand : public CeilingFanCommand
{
public:
	explicit CeilingFanHighCommand(const CeilingFanPtr ceilingFan) noexcept
		: CeilingFanCommand{ ceilingFan }
	{
	}

	void Execute() noexcept override
	{
		CeilingFanCommand::Exec(CeilingFan::Speed::High);
	}
};

class CeilingFanOffCommand : public CeilingFanCommand
{
public:
	explicit CeilingFanOffCommand(const CeilingFanPtr ceilingFan) noexcept
		: CeilingFanCommand{ ceilingFan }
	{
	}

	void Execute() noexcept override
	{
		CeilingFanCommand::Exec(CeilingFan::Speed::Off);
	}
};

class GarageDoorOpenCommand : public Command
{
public:
	explicit GarageDoorOpenCommand(const GarageDoorPtr door) noexcept
		: _door{ door }
	{
	}

	void Execute() noexcept override
	{
		_door->Up();
	}
	void Undo() noexcept override
	{
		_door->Down();
	}

private:
	GarageDoorPtr _door;
};

class GarageDoorCloseCommand : public Command
{
public:
	explicit GarageDoorCloseCommand(const GarageDoorPtr door) noexcept
		: _door{ door }
	{
	}

	void Execute() noexcept override
	{
		_door->Down();
	}
	void Undo() noexcept override
	{
		_door->Up();
	}

private:
	GarageDoorPtr _door;
};

class LightOnCommand : public Command
{
public:
	explicit LightOnCommand(const LightPtr light) noexcept
		: _light{ light }
	{
	}

	void Execute() noexcept override
	{
		_light->On();
	}
	void Undo() noexcept override
	{
		_light->Off();
	}

private:
	LightPtr _light;
};

class LightOffCommand : public Command
{
public:
	explicit LightOffCommand(const LightPtr light) noexcept
		: _light{ light }
	{
	}

	void Execute() noexcept override
	{
		_light->Off();
	}
	void Undo() noexcept override
	{
		_light->On();
	}

private:
	LightPtr _light;
};

class StereoOnWithCDCommand : public Command
{
public:
	explicit StereoOnWithCDCommand(const StereoPtr stereo) noexcept
		: _stereo{ stereo }
	{
	}

	void Execute() noexcept override
	{
		_stereo->On();
		_stereo->SetCD();
		_stereo->SetVolume(10);
	}
	void Undo() noexcept override
	{
		_stereo->Off();
	}

private:
	StereoPtr _stereo;
};

class StereoOffCommand : public Command
{
public:
	explicit StereoOffCommand(const StereoPtr stereo) noexcept
		: _stereo{ stereo }
	{
	}

	void Execute() noexcept override
	{
		_stereo->Off();
	}
	void Undo() noexcept override
	{
		_stereo->On();
		_stereo->SetCD();
		_stereo->SetVolume(10);
	}

private:
	StereoPtr _stereo;
};

class MacroCommand : public Command
{
public:
	explicit MacroCommand(CommandPtrArray&& commands) noexcept
		: _commands{ std::move(commands) }
	{
	}

	void Execute() noexcept override
	{
		for (auto& command : _commands) {
			command->Execute();
		}
	}
	void Undo() noexcept override
	{
		for (auto& command : _commands) {
			command->Undo();
		}
	}

private:
	CommandPtrArray _commands;
};

//
// Invoker.
//

class RemoteControl
{
public:
	explicit RemoteControl(const size_t btnRows = 1U) noexcept;

	void OnButtonWasPressed(const size_t slot);
	void OffButtonWasPressed(const size_t slot);
	void UndoButtonWasPressed();

	void SetCommand(const size_t slot,
		const CommandPtr onCommand, const CommandPtr offCommand);

private:
	CommandPtrArray _onCommands;
	CommandPtrArray _offCommands;
	CommandPtr _undoCommand;
};

using RemoteControlPtr = std::shared_ptr<RemoteControl>;

} // namespace behavioral
} // namespace pattern

#endif // PATTERNS_STRATEGY_H
