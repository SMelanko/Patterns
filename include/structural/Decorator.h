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

} // namespace creational
} // namespace structural

#endif // PATTERN_STRUCTURAL_DECORATOR_H

