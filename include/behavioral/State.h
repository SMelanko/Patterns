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

#ifndef PATTERNS_STATE_H
#define PATTERNS_STATE_H

#include <cstdint>
#include <iostream>

namespace pattern
{
namespace behavioral
{

class GunballMachine
{
public:
	enum class State
	{
		UNDEFINED,
		SOLD_OUT,
		NO_QUARTER,
		HAS_QUARTER,
		SOLD
	};

public:
	GunballMachine() = default;
	explicit GunballMachine(const int16_t cnt);

	void EjectQuarter() noexcept;
	void InsertQuarter() noexcept;
	void TurnCrank() noexcept;

private:
	void Dispense() noexcept;

private:
	int16_t _cnt = 0;
	State _state = State::UNDEFINED;
};

} // namespace behavioral
} // namespace pattern

#endif // PATTERNS_STATE_H
