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

class GumballMachine;
using GumballMachineShPtr = std::shared_ptr<GumballMachine>;

class State
{
public:
	virtual ~State() = default;

public:
	virtual void InsertQuarter() = 0;
	virtual void EjectQuarter() = 0;
	virtual void TurnCrank() = 0;
	virtual void Dispense() = 0;
};

using StateShPtr = std::shared_ptr<State>;

class NoQuarterState : public State
{
public:
	explicit NoQuarterState(GumballMachineShPtr gm) noexcept
		: _gm{ gm }
	{
	}

public:
	void InsertQuarter() override;
	void EjectQuarter() override;
	void TurnCrank() override;
	void Dispense() override;

private:
	GumballMachineShPtr _gm;
};

class HasQuarterState : public State
{
public:
	explicit HasQuarterState(GumballMachineShPtr gm) noexcept
		: _gm{ gm }
	{
	}

public:
	void InsertQuarter() override;
	void EjectQuarter() override;
	void TurnCrank() override;
	void Dispense() override;

private:
	GumballMachineShPtr _gm;
};

class SoldState : public State
{
public:
	explicit SoldState(GumballMachineShPtr gm) noexcept
		: _gm{ gm }
	{
	}

public:
	void InsertQuarter() override;
	void EjectQuarter() override;
	void TurnCrank() override;
	void Dispense() override;

private:
	GumballMachineShPtr _gm;
};

class SoldOutState : public State
{
public:
	explicit SoldOutState(GumballMachineShPtr gm) noexcept
		: _gm{ gm }
	{
	}

public:
	void InsertQuarter() override;
	void EjectQuarter() override;
	void TurnCrank() override;
	void Dispense() override;

private:
	GumballMachineShPtr _gm;
};

class GumballMachine : public std::enable_shared_from_this<GumballMachine>
{
public:
	GumballMachine() = default;
	void Init(const uint16_t cnt);

	void InsertQuarter();
	void EjectQuarter();
	void TurnCrank();
	void Dispense();

	void ReleaseBall() noexcept;
	void SetState(StateShPtr state) noexcept;

	StateShPtr GetNoQuarterState() noexcept
	{
		return _noQuarterState;
	}
	StateShPtr GetHasQuarterState() noexcept
	{
		return _hasQuarterState;
	}
	StateShPtr GetSoldState() noexcept
	{
		return _soldState;
	}
	StateShPtr GetSoldOutState() noexcept
	{
		return _soldOutState;
	}
	auto GetCount() const noexcept
	{
		return _cnt;
	}

private:
	StateShPtr _noQuarterState = nullptr;
	StateShPtr _hasQuarterState = nullptr;
	StateShPtr _soldState = nullptr;
	StateShPtr _soldOutState = nullptr;

	StateShPtr _state = nullptr;
	uint16_t _cnt = 0;
};

} // namespace behavioral
} // namespace pattern

#endif // PATTERNS_STATE_H
