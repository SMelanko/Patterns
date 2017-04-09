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

#ifndef PATTERNS_PROTOTYPE_H
#define PATTERNS_PROTOTYPE_H

#include <iostream>
#include <memory>

namespace pattern
{
namespace creational
{

class Warrior;
using WarriorUnPtr = std::unique_ptr<Warrior>;

//
// Abstract product.
//

class Warrior
{
public:
	virtual ~Warrior() = default;

	virtual WarriorUnPtr Clone() = 0;
	virtual void PrintInfo() const noexcept = 0;
};

//
// Concrete products.
//

class Archer: public Warrior
{
	friend class PrototypeFactory;

public:
	virtual ~Archer() = default;

	WarriorUnPtr Clone() override
	{
		return std::make_unique<Archer>(*this);
	}
	void PrintInfo() const noexcept override
	{
		std::cout << "class Archer: public Warrior" << std::endl;
	}

private:
	Archer() = default;
};

class Infantryman: public Warrior
{
	friend class PrototypeFactory;

public:
	virtual ~Infantryman() = default;

	WarriorUnPtr Clone() override
	{
		return std::make_unique<Infantryman>(*this);
	}
	void PrintInfo() const noexcept override
	{
		std::cout << "class Infantryman: public Warrior" << std::endl;
	}

private:
	Infantryman() = default;
};

//
// Prototype.
//

class PrototypeFactory
{
public:
	WarriorUnPtr CreateArcher() const;
	WarriorUnPtr CreateInfantryman() const;
};

} // namespace creational
} // namespace pattern

#endif // PATTERNS_PROTOTYPE_H
