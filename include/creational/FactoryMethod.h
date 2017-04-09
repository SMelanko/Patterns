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

///
/// Example #1.
///

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

public:
	virtual WARRIOR_ID GetId() const noexcept = 0;
	virtual void PrintInfo() const noexcept = 0;
};

using WarriorUnPtr = std::unique_ptr<Warrior>;
using WarriorShPtr = std::shared_ptr<Warrior>;

//
// Factory.
//

class Factory
{
public:
	using MapType = std::map<std::string, std::function<WarriorUnPtr()>>;

public:
	Factory() noexcept = default;
	virtual ~Factory() noexcept = default;

	Factory(const Factory&) = delete;
	Factory& operator=(const Factory&) = delete;

	Factory(Factory&&) noexcept = delete;
	Factory& operator=(Factory&&) noexcept = delete;

public:
	static WarriorUnPtr CreateInstance(const std::string& s);

protected:
	static MapType _map;
};

//
// FactoryRegister.
//

template<typename T>
class FactoryRegister : Factory
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
// Specific warriors.
//

class Infantryman : public Warrior
{
public:
	virtual ~Infantryman() noexcept = default;

public:
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

public:
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

///
/// Example #2. Generalized Constructor.
///

enum class PRODUCT_ID : uint32_t
{
	PRODUCT_A = 1,
	PRODUCT_B = 2
};

//
// Abstract product.
//

class Product
{
public:
	virtual ~Product() noexcept = default;

public:
	virtual PRODUCT_ID GetId() const noexcept = 0;
};

using ProductShPtr = std::shared_ptr<Product>;

//
// Specific products.
//

class ProductA : public Product
{
public:
	ProductA(const int)
	{
	};

	virtual ~ProductA() noexcept = default;

public:
	PRODUCT_ID GetId() const noexcept override
	{
		return PRODUCT_ID::PRODUCT_A;
	}
};

class ProductB : public Product
{
public:
	ProductB(const std::string&)
	{
	};

	virtual ~ProductB() noexcept = default;

public:
	PRODUCT_ID GetId() const noexcept override
	{
		return PRODUCT_ID::PRODUCT_B;
	}
};

//
// Product factory.
//

class ProductFactory
{
public:
	template <class... Args>
	static ProductShPtr Create(const PRODUCT_ID id, Args&&... args)
	{
		switch (id) {
		case PRODUCT_ID::PRODUCT_A:
			return Create<ProductA>(std::forward<Args>(args)...);
		case PRODUCT_ID::PRODUCT_B:
			return Create<ProductB>(std::forward<Args>(args)...);
		default:
			return nullptr;
		}
	}

private:
	template<typename T, typename... Args>
	static std::enable_if_t<
		std::is_constructible<T, Args...>::value, ProductShPtr
	> Create(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T, typename... Args>
	static std::enable_if_t<
		!std::is_constructible<T, Args...>::value, ProductShPtr
	> Create(Args&&...)
	{
		return nullptr;
	}
};

} // namespace creational
} // namespace pattern

#endif // PATTERNS_FACTORY_METHOD_H
