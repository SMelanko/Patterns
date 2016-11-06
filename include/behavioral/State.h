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

	explicit GunballMachine(const int16_t cnt)
		: _cnt{ cnt }
	{
		if (_cnt > 0) {
			_state = State::NO_QUARTER;
		}
	}

	void EjectQuarter() noexcept
	{
		switch (_state) {
		case State::HAS_QUARTER:
			std::cout << "Quarter returned\n";
			_state = State::NO_QUARTER;
			break;
		case State::NO_QUARTER:
			std::cout << "You haven't inserted a quarter\n";
			break;
		case State::SOLD_OUT:
			std::cout << "You can't eject, you haven't inserted a quarter yet\n";
			break;
		case State::SOLD:
			std::cout << "Sorry, you have already turned the crank\n";
			break;
		default:
			break;
		}
	}

	void Dispense() noexcept
	{
		switch (_state) {
		case State::HAS_QUARTER:
			std::cout << "No gumballs dispensed\n";
			break;
		case State::NO_QUARTER:
			std::cout << "You need to pay first\n";
			break;
		case State::SOLD_OUT:
			std::cout << "No gumballs dispensed\n";
			break;
		case State::SOLD:
			std::cout << "A gumball comes rolling  out the slot\n";
			if (--_cnt == 0) {
				std::cout << "Oops, out of gumballs!\n";
				_state = State::SOLD_OUT;
			} else {
				_state = State::NO_QUARTER;
			}
			break;
		default:
			break;
		}
	}

	State GetState() const noexcept
	{
		return _state;
	}

	void InsertQuarter() noexcept
	{
		switch (_state) {
		case State::HAS_QUARTER:
			std::cout << "You can't insert another quarter\n";
			break;
		case State::NO_QUARTER:
			std::cout << "You have inserted a quarter\n";
			_state = State::HAS_QUARTER;
			break;
		case State::SOLD_OUT:
			std::cout << "You can't insert a quarter, the machine is sold out\n";
			break;
		case State::SOLD:
			std::cout << "Please wait, we're already giving you a gumball\n";
			break;
		default:
			break;
		}
	}

	void TurnCrank() noexcept
	{
		switch (_state) {
		case State::HAS_QUARTER:
			std::cout << "You turned...\n";
			_state = State::SOLD;
			Dispense();
			break;
		case State::NO_QUARTER:
			std::cout << "You turned but there is no quarter\n";
			break;
		case State::SOLD_OUT:
			std::cout << "You turned but there are no gumballs\n";
			break;
		case State::SOLD:
			std::cout << "Turning twice doesn't get you another gumball!\n";
			break;
		default:
			break;
		}
	}

private:
	int16_t _cnt = 0;
	State _state = State::UNDEFINED;
};

} // namespace behavioral
} // namespace pattern

#endif // PATTERNS_STATE_H
