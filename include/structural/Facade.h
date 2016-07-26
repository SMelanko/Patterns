 
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

#ifndef PATTERN_STRUCTURAL_FACADE_H
#define PATTERN_STRUCTURAL_FACADE_H

#include <iostream>

namespace pattern
{
namespace structural
{

class MisDepartment
{
public:
	constexpr MisDepartment() = default;

	constexpr bool CheckOnStatus() noexcept
	{
		return (++_state == Complete) ? true : false;
	}
	constexpr void SubmitNetworkRequest() noexcept
	{
		_state = 0;
	}

private:
	enum States
	{
		Received, DenyAllKnowledge, ReferClientToFacilities,
		FacilitiesHasNotSentPaperwork, ElectricianIsNotDone,
		ElectricianDidItWrong, DispatchTechnician, SignedOff,
		DoesNotWork, FixElectriciansWiring, Complete
	};

	int _state{ 0 };
};

class ElectricianUnion
{
public:
	constexpr ElectricianUnion() = default;

	constexpr bool CheckOnStatus() noexcept
	{
		return (++_state == Complete) ? true : false;
	}
	constexpr void SubmitNetworkRequest() noexcept
	{
		_state = 0;
	}

private:
	enum States
	{
		Received, RejectTheForm, SizeTheJob, SmokeAndJokeBreak,
		WaitForAuthorization, DoTheWrongJob, BlameTheEngineer,
		WaitToPunchOut, DoHalfAJob, ComplainToEngineer,
		GetClarification, CompleteTheJob, TurnInThePaperwork,
		Complete
	};

	int _state{ 0 };
};

class FacilitiesDepartment
{
public:
	constexpr FacilitiesDepartment() = default;

	constexpr bool CheckOnStatus() noexcept
	{
		return (++_state == Complete) ? true : false;
	}
	constexpr void SubmitNetworkRequest() noexcept
	{
		_state = 0;
	}

private:
	enum States
	{
		Received, AssignToEngineer, EngineerResearches, RequestIsNotPossible,
		EngineerLeavesCompany, AssignToNewEngineer, NewEngineerResearches,
		ReassignEngineer, EngineerReturns, EngineerResearchesAgain,
		EngineerFillsOutPaperWork, Complete
	};

	int _state{ 0 };
};

class FacilitiesFacade
{
public:
	constexpr FacilitiesFacade() = default;

	bool CheckOnStatus() noexcept;
	constexpr int GetNumberOfCalls() noexcept
	{
		return _count;
	}
	constexpr void SubmitNetworkRequest() noexcept
	{
		_state = 0;
	}

private:
	enum States
	{
		Received, SubmitToEngineer, SubmitToElectrician, SubmitToTechnician
	};

	int _state{ 0 };
	int _count{ 0 };
	FacilitiesDepartment _engineer{};
	ElectricianUnion _electrician{};
	MisDepartment _technician{};
};

} // namespace structural
} // namespace pattern

#endif // PATTERN_STRUCTURAL_FACADE_H
