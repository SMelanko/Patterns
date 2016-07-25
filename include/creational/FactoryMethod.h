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

#ifndef PATTERNS_FACTORY_METHOD_H
#define PATTERNS_FACTORY_METHOD_H

#include <iostream>
#include <map>
#include <memory>
#include <string>

namespace pattern
{
namespace creational
{

// Only for testing.
enum class WARRIOR_ID : uint32_t
{
	INFANTRYMAN = 1,
	ARCHER = 2
};

//
// Abstract product.
//

class Warrior
{
public:
	virtual ~Warrior() noexcept = default;

	virtual WARRIOR_ID GetId() const noexcept = 0;
	virtual void PrintInfo() const noexcept = 0;
};

using WarriorPtr = std::unique_ptr<Warrior>;

//
// Factory.
//

class Factory
{
public:
	using MapType = std::map<std::string, std::function<WarriorPtr()>>;

	Factory() noexcept = default;
	~Factory() noexcept = default;

	Factory(const Factory&) = delete;
	Factory& operator=(const Factory&) = delete;

	Factory(Factory&&) noexcept = delete;
	Factory& operator=(Factory&&) noexcept = delete;

	static WarriorPtr CreateInstance(const std::string& s)
	{
		auto it = _map.find(s);
		return (it == _map.end()) ? nullptr : it->second();
	}

protected:
	static MapType _map;
};

//
// FactoryRegister.
//

template<typename T>
class FactoryRegister: Factory
{
public:
	FactoryRegister(const std::string& s)
	{
		_map.insert(std::make_pair(s, std::make_unique<T>));
	}
};

#define REGISTER_DEC_TYPE(NAME) \
	static FactoryRegister<NAME> reg

#define REGISTER_DEF_TYPE(NAME) \
	FactoryRegister<NAME> NAME::reg(#NAME)

//
// Concrete warriors.
//

class Infantryman : public Warrior
{
public:
	virtual ~Infantryman() noexcept = default;

	WARRIOR_ID GetId() const noexcept override
	{
		return WARRIOR_ID::INFANTRYMAN;
	}
	void PrintInfo() const noexcept override
	{
		std::cout << "class Infantryman : public Warrior" << std::endl;
	}

private:
	REGISTER_DEC_TYPE(Infantryman);
};

class Archer : public Warrior
{
public:
	virtual ~Archer() noexcept = default;

	WARRIOR_ID GetId() const noexcept override
	{
		return WARRIOR_ID::ARCHER;
	}
	void PrintInfo() const noexcept override
	{
		std::cout << "class Archer : public Warrior" << std::endl;
	}

private:
	REGISTER_DEC_TYPE(Archer);
};

} // namespace creational
} // namespace pattern

#endif // PATTERNS_FACTORY_METHOD_H
