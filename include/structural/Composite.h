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

#ifndef PATTERN_STRUCTURAL_COMPOSITE_H
#define PATTERN_STRUCTURAL_COMPOSITE_H

#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>

namespace pattern
{
namespace structural
{

//
// Component.
//

class Unit
{
public:
	virtual ~Unit() = default;

	virtual void AddUnit(std::shared_ptr<Unit>)
	{
		assert(false);
	}
	virtual int GetStrength() const noexcept = 0;
};

using UnitPtr = std::shared_ptr<Unit>;

//
// Primitives.
//

class Archer: public Unit
{
public:
	int GetStrength() const noexcept override
	{
		return 1;
	}
};

class Infantryman: public Unit
{
public:
	int GetStrength() const noexcept override
	{
		return 2;
	}
};

class Horseman: public Unit
{
public:
	int GetStrength() const noexcept override
	{
		return 3;
	}
};

//
// Composite.
//

class CompositeUnit: public Unit
{
public:
	void AddUnit(UnitPtr p) override
	{
		_units.push_back(p);
	}
	int GetStrength() const noexcept override
	{
		int total = 0;

		std::for_each(std::begin(_units), std::end(_units),
			[&total](UnitPtr unit) { total += unit->GetStrength(); });

		return total;
	}

private:
	std::vector<UnitPtr> _units;
};

} // namespace creational
} // namespace structural

#endif // PATTERN_STRUCTURAL_COMPOSITE_H
