#pragma once

#ifndef PATTERNS_CREATIONAL_PROTOTYPE_H
#define PATTERNS_CREATIONAL_PROTOTYPE_H

///
/// A fully initialized instance to be copied or cloned.
///

#include <iostream>
#include <memory>

namespace pattern
{
namespace creational
{

class Warrior;
using WarriorUnPtr = std::unique_ptr<Warrior>;
using WarriorShPtr = std::shared_ptr<Warrior>;

//
// Abstract product.
//

class Warrior
{
public:
	virtual ~Warrior() noexcept = default;

public:
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
	virtual ~Archer() noexcept = default;

public:
	WarriorUnPtr Clone() override
	{
		return std::make_unique<Archer>(*this);
	}
	void PrintInfo() const noexcept override
	{
		std::cout << "class Archer: public Warrior" << std::endl;
	}

private:
	Archer() noexcept = default;
};

class Infantryman: public Warrior
{
	friend class PrototypeFactory;

public:
	virtual ~Infantryman() noexcept = default;

public:
	WarriorUnPtr Clone() override
	{
		return std::make_unique<Infantryman>(*this);
	}
	void PrintInfo() const noexcept override
	{
		std::cout << "class Infantryman: public Warrior" << std::endl;
	}

private:
	Infantryman() noexcept = default;
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

#endif // PATTERNS_CREATIONAL_PROTOTYPE_H
