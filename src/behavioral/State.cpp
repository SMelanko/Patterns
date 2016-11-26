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

#include "behavioral/State.h"

namespace pattern
{
namespace behavioral
{

void GumballMachine::Init(const uint16_t cnt)
{
	_noQuarterState = std::make_shared<NoQuarterState>(shared_from_this());
	_hasQuarterState = std::make_shared<HasQuarterState>(shared_from_this());
	_soldState = std::make_shared<SoldState>(shared_from_this());
	_soldOutState = std::make_shared<SoldOutState>(shared_from_this());

	_cnt = cnt;

	if (_cnt > 0) {
		_state = _noQuarterState;
	} else {
		_state = _soldOutState;
	}
}

void GumballMachine::EjectQuarter()
{
	_state->EjectQuarter();
}

void GumballMachine::InsertQuarter()
{
	_state->InsertQuarter();
}

void GumballMachine::TurnCrank()
{
	_state->TurnCrank();
	_state->Dispense();
}

void GumballMachine::ReleaseBall() noexcept
{
	std::cout << "A gumball comes rollingout the slot...\n";
	if (_cnt > 0) {
		--_cnt;
	}
}

void GumballMachine::SetState(StateShPtr state) noexcept
{
	_state = state;
}

void NoQuarterState::InsertQuarter()
{
	std::cout << "You have inserted a quarter\n";
	_gm->SetState(_gm->GetHasQuarterState());
}

void NoQuarterState::EjectQuarter()
{
	std::cout << "You haven't inserted a quarter\n";
}

void NoQuarterState::TurnCrank()
{
	std::cout << "You turned but there's no quarter\n";
}

void NoQuarterState::Dispense()
{
	std::cout << "You need to pay first\n";
}

void HasQuarterState::InsertQuarter()
{
	std::cout << "You can't insert another quarter\n";
}

void HasQuarterState::EjectQuarter()
{
	std::cout << "Quarter returned\n";
	_gm->SetState(_gm->GetNoQuarterState());
}

void HasQuarterState::TurnCrank()
{
	std::cout << "You turned...\n";
	_gm->SetState(_gm->GetSoldState());
}

void HasQuarterState::Dispense()
{
	std::cout << "No gumballs dispensed\n";
}

void SoldState::InsertQuarter()
{
	std::cout << "Please wait, we're already giving you a gumball\n";
}

void SoldState::EjectQuarter()
{
	std::cout << "Sorry, you have already turned the crank\n";
}

void SoldState::TurnCrank()
{
	std::cout << "Turning twice doesn't get you another gumball!\n";
}

void SoldState::Dispense()
{
	_gm->ReleaseBall();
	if (_gm->GetCount() <= 0) {
		std::cout << "Oops, out of gumballs!\n";
		_gm->SetState(_gm->GetSoldOutState());
	} else {
		_gm->SetState(_gm->GetNoQuarterState());
	}
}

void SoldOutState::InsertQuarter()
{
	std::cout << "You can't insert a quarter, the machine is sold out\n";
}

void SoldOutState::EjectQuarter()
{
	std::cout << "You can't eject, you haven't inserted a quarter yet\n";
}

void SoldOutState::TurnCrank()
{
	std::cout << "You turned but there are no gumballs\n";
}

void SoldOutState::Dispense()
{
	std::cout << "No gumballs dispensed\n";
}

} // namespace behavioral
} // namespace pattern
