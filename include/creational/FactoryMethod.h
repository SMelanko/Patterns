#pragma once

#ifndef PATTERNS_CREATIONAL_FACTORY_METHOD_H
#define PATTERNS_CREATIONAL_FACTORY_METHOD_H

/*

Intent:
	Define an interface for creating an object, but let subclasses decide which class to instantiate.
	The Factory method lets a class defer instantiation it uses to subclasses.

Applicability:
	- a class can't anticipate the class of objects it must create.
	- a class wants its subclasses to specify the objects it creates.
	- classes delegate responsibility to one of several helper classes, and
	  you want to localize the knowledge of which helper subclass is the delegate.
*/

#include <iostream>
#include <map>
#include <memory>
#include <string>

namespace pattern
{
namespace creational
{

////////////////////////////////////////////////////////////////////////////////
///
/// Example #1.
///

// Only for testing.
enum class EXCHANGE_CONNECTOR_ID : uint32_t
{
	GOOGLE_ADX = 1,
	SMAATO = 2
};

//
// Abstract exchange connector.
//

class ExchangeConnector
{
public:
	virtual ~ExchangeConnector() noexcept = default;

public:
	virtual EXCHANGE_CONNECTOR_ID GetId() const noexcept = 0;
};

using ExchangeConnectorUnPtr = std::unique_ptr<ExchangeConnector>;
using ExchangeConnectorShPtr = std::shared_ptr<ExchangeConnector>;

//
// Exchange connector factory.
//

class ExchangeConnectorFactory
{
public:
	using MapType = std::map<std::string, std::function<ExchangeConnectorUnPtr()>>;

public:
	ExchangeConnectorFactory() noexcept = default;
	virtual ~ExchangeConnectorFactory() noexcept = default;

	ExchangeConnectorFactory(const ExchangeConnectorFactory&) = delete;
	ExchangeConnectorFactory& operator=(const ExchangeConnectorFactory&) = delete;

	ExchangeConnectorFactory(ExchangeConnectorFactory&&) noexcept = delete;
	ExchangeConnectorFactory& operator=(ExchangeConnectorFactory&&) noexcept = delete;

public:
	static ExchangeConnectorUnPtr Create(const std::string& s);

protected:
	static MapType _map;
};

template<typename T>
class ExchangeConnectorRegister : ExchangeConnectorFactory
{
public:
	ExchangeConnectorRegister(const std::string& s)
	{
		_map.insert(std::make_pair(s, std::make_unique<T>));
	}
};

#define REGISTER_DEC_TYPE(NAME) \
	static ExchangeConnectorRegister<NAME ## ExchangeConnector> reg

#define REGISTER_DEF_TYPE(NAME) \
	ExchangeConnectorRegister<NAME ## ExchangeConnector> \
		NAME ## ExchangeConnector::reg(#NAME)

//
// Specific exchange connectors.
//

class GoogleAdXExchangeConnector : public ExchangeConnector
{
public:
	EXCHANGE_CONNECTOR_ID GetId() const noexcept override
	{
		return EXCHANGE_CONNECTOR_ID::GOOGLE_ADX;
	}

private:
	REGISTER_DEC_TYPE(GoogleAdX);
};

class SmaatoExchangeConnector : public ExchangeConnector
{
public:
	EXCHANGE_CONNECTOR_ID GetId() const noexcept override
	{
		return EXCHANGE_CONNECTOR_ID::SMAATO;
	}

private:
	REGISTER_DEC_TYPE(Smaato);
};

////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////
///
/// Example #3 Classical version.
///

// Only for testing.
enum class WARRIOR_ID : uint32_t
{
	INFANTRYMAN = 1,
	ARCHER = 2
};

//
// Abstract warrior.
//

class Warrior
{
public:
	virtual ~Warrior() noexcept = default;

public:
	virtual WARRIOR_ID GetId() const noexcept = 0;
};

using WarriorUnPtr = std::unique_ptr<Warrior>;
using WarriorShPtr = std::shared_ptr<Warrior>;

//
// Specific warriors.
//

class Infantryman : public Warrior
{
public:
	WARRIOR_ID GetId() const noexcept override
	{
		return WARRIOR_ID::INFANTRYMAN;
	}
};

class Archer : public Warrior
{
public:
	WARRIOR_ID GetId() const noexcept override
	{
		return WARRIOR_ID::ARCHER;
	}
};

//
// Abstract warrior factory.
//

class WarriorFactory
{
public:
	virtual ~WarriorFactory() noexcept = default;

public:
	virtual WarriorUnPtr CreateWarrior() = 0;
};

using WarriorFactoryUnPtr = std::unique_ptr<WarriorFactory>;

//
// Specific warrior factory.
//

class InfantryFactory : public WarriorFactory
{
public:
	WarriorUnPtr CreateWarrior() override;
};

class ArchersFactory : public WarriorFactory
{
public:
	WarriorUnPtr CreateWarrior() override;
};

} // namespace creational
} // namespace pattern

#endif // PATTERNS_CREATIONAL_FACTORY_METHOD_H
