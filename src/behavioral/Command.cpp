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

#include <include/gsl.h>

namespace pattern
{
namespace behavioral
{

RemoteControl::RemoteControl(const size_t btnRows) noexcept
{
	_onCommands.resize(btnRows);
	_offCommands.resize(btnRows);
	CommandPtr noCommand = std::make_shared<NoCommand>();
	Ensures(noCommand != nullptr);
	std::fill(std::begin(_onCommands), std::end(_onCommands), noCommand);
	std::fill(std::begin(_offCommands), std::end(_offCommands), noCommand);
	Ensures(_onCommands.size() == btnRows && _offCommands.size() == btnRows);
	_undoCommand = noCommand;
}

void RemoteControl::OffButtonWasPressed(const size_t slot)
{
	_offCommands[slot]->Execute();
	_undoCommand = _offCommands[slot];
}

void RemoteControl::OnButtonWasPressed(const size_t slot)
{
	_onCommands[slot]->Execute();
	_undoCommand = _onCommands[slot];
}

void RemoteControl::SetCommand(const size_t slot,
	const CommandPtr onCommand, const CommandPtr offCommand)
{
	_onCommands[slot] = onCommand;
	_offCommands[slot] = offCommand;
}

void RemoteControl::UndoButtonWasPressed()
{
	_undoCommand->Undo();
}

} // namespace behavioral
} // namespace pattern
