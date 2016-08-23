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

#ifndef PATTERN_STRUCTURAL_DECORATOR_H
#define PATTERN_STRUCTURAL_DECORATOR_H

#include <iostream>
#include <memory>

namespace pattern
{
namespace structural
{

///
/// Example #1
///

//
// Interface.
//

class Interface
{
public:
	virtual ~Interface() = default;
	virtual void DoIt() const noexcept = 0;
};

using InterfacePtr = std::shared_ptr<Interface>;

//
// Core functionality.
//

class Core: public Interface
{
public:
	~Core()
	{
		std::cout << "Core dtor\n";
	}

	void DoIt() const noexcept override
	{
		std::cout << "Core functionality";
	}
};

//
// Decorator - optional wrapper.
//

class Decorator: public Interface
{
public:
	explicit Decorator(InterfacePtr inner)
		: _wrap{ inner }
	{
	}

	void DoIt() const noexcept override
	{
		_wrap->DoIt();
	}

private:
	std::shared_ptr<Interface> _wrap;
};

//
// Additional functionalities to the Core.
//

class X: public Decorator
{
public:
	explicit X(InterfacePtr core)
		: Decorator{ core }
	{
	}
	~X()
	{
		std::cout << "X dtor   ";
	}

	void DoIt() const noexcept override
	{
		Decorator::DoIt();
		std::cout << " + X";
	}
};

class Y: public Decorator
{
public:
	explicit Y(InterfacePtr core)
		: Decorator{ core }
	{
	}
	~Y()
	{
		std::cout << "Y dtor   ";
	}

	void DoIt() const noexcept override
	{
		Decorator::DoIt();
		std::cout << " + Y";
	}
};

class Z: public Decorator
{
public:
	explicit Z(InterfacePtr core)
		: Decorator{ core }
	{
	}
	~Z()
	{
		std::cout << "Z dtor   ";
	}

	void DoIt() const noexcept override
	{
		Decorator::DoIt();
		std::cout << " + Z";
	}
};

///
/// Example #2.
///

class Beverage
{
public:
	Beverage() = default;
	explicit Beverage(const std::string& desc)
		: _description{ desc }
	{
	}
	virtual ~Beverage() = default;

	virtual double Cost() const noexcept = 0;
	virtual std::string GetDescription() const noexcept
	{
		return _description;
	}

private:
	std::string _description = "Unknown Beverage";
};

using BeveragePtr = std::shared_ptr<Beverage>;

class DarkRoast : public Beverage
{
public:
	DarkRoast()
		: Beverage{ "Dark Roast" }
	{
	}

	double Cost() const noexcept override
	{
		return 1.69;
	}
};

class Espresso : public Beverage
{
public:
	Espresso()
		: Beverage{ "Espresso" }
	{
	}

	double Cost() const noexcept override
	{
		return 1.99;
	}
};

class CondimentDecorator : public Beverage
{
public:
	explicit CondimentDecorator(BeveragePtr comp)
		: _comp{ comp }
	{
	}

	double Cost() const noexcept override
	{
		return _comp->Cost();
	}
	std::string GetDescription() const noexcept override
	{
		return _comp->GetDescription();
	}

private:
	BeveragePtr _comp;
};

class Milk : public CondimentDecorator
{
public:
	explicit Milk(BeveragePtr comp)
		: CondimentDecorator{ comp }
	{
	}

	double Cost() const noexcept override
	{
		return CondimentDecorator::Cost() + 0.3;
	}
	std::string GetDescription() const noexcept override
	{
		return CondimentDecorator::GetDescription() + ", Milk";
	}
};

class Mocha : public CondimentDecorator
{
public:
	explicit Mocha(BeveragePtr comp)
		: CondimentDecorator{ comp }
	{
	}

	double Cost() const noexcept override
	{
		return CondimentDecorator::Cost() + 0.4;
	}
	std::string GetDescription() const noexcept override
	{
		return CondimentDecorator::GetDescription() + ", Mocha";
	}
};

} // namespace structural
} // namespace pattern

#endif // PATTERN_STRUCTURAL_DECORATOR_H

