#pragma once

#ifndef PATTERNS_CREATIONAL_BUILDER_H
#define PATTERNS_CREATIONAL_BUILDER_H

///
/// Allows constructing complex objects step by step.
/// Separates object construction from its representation.
///

#include <array>
#include <iostream>
#include <memory>

namespace pattern
{
namespace creational
{

//
// Definitions of the car's parts.
//

class Body
{
public:
	Body() noexcept = default;
	explicit Body(const std::string& shape)
		: _shape{ shape }
	{
	}

public:
	std::string GetShape() const noexcept
	{
		return _shape;
	}

	void SetShape(const std::string& shape)
	{
		_shape = shape;
	}

private:
	std::string _shape;
};

class Engine
{
public:
	constexpr Engine() noexcept = default;
	explicit constexpr Engine(const int horsepower)
		: _horsepower{ horsepower }
	{
	}

public:
	constexpr int GetHorsePower() const noexcept
	{
		return _horsepower;
	}

	constexpr void SetHorsePower(const int horsepower)
	{
		_horsepower = horsepower;
	}

private:
	int _horsepower = 0;
};

class Wheel
{
public:
	constexpr Wheel() noexcept = default;
	explicit constexpr Wheel(const int size) noexcept
		: _size{ size }
	{
	}

public:
	constexpr int GetSize() const noexcept
	{
		return _size;
	}

	constexpr void SetSize(const int size)
	{
		_size = size;
	}

private:
	int _size = 0;
};

using Wheels = std::array<Wheel, 4>;

//
// Product.
//

class Car
{
public:
	Car() = default;

public:
	void PrintSpecifications() const noexcept
	{
		std::cout << "Body: " << _body.GetShape() << std::endl;
		std::cout << "Engine horsepower: " << _engine.GetHorsePower() << std::endl;
		std::cout << "Tire size: " << _wheels[0].GetSize() << "'" << std::endl;
	}

	Body GetBody() const noexcept
	{
		return _body;
	}
	Engine GetEngine() const noexcept
	{
		return _engine;
	}
	Wheels GetWheels() const noexcept
	{
		return _wheels;
	}

	void SetBody(const Body& body)
	{
		_body = body;
	}
	void SetEngine(const Engine& engine)
	{
		_engine = engine;
	}
	void SetWheels(const Wheels& sheels)
	{
		_wheels = sheels;
	}

private:
	Body _body;
	Engine _engine;
	Wheels _wheels;
};

using CarShPtr = std::shared_ptr<Car>;

//
// Abstract builder.
//

class Builder
{
public:
	virtual ~Builder() noexcept = default;

public:
	virtual void BuildBody() = 0;
	virtual void BuildEngine() = 0;
	virtual void BuildWheels() = 0;

	void CreateNewCar()
	{
		_car.reset(new Car{});
	}

	CarShPtr GetCar() const noexcept
	{
		return _car;
	}

protected:
	CarShPtr _car;
};

using BuilderShPtr = std::shared_ptr<Builder>;

//
// Director.
//

class Director
{
public:
	Director() noexcept = default;
	Director(BuilderShPtr builder)
		: _builder{ builder }
	{
	}

public:
	CarShPtr ConstructCar() const
	{
		_builder->CreateNewCar();
		_builder->BuildBody();
		_builder->BuildEngine();
		_builder->BuildWheels();
		return _builder->GetCar();
	}

	BuilderShPtr GetBuilder() const noexcept
	{
		return _builder;
	}

	void SetBuilder(BuilderShPtr builder)
	{
		_builder = builder;
	}

private:
	BuilderShPtr _builder = nullptr;
};

//
// Concrete builders.
//

class JeepBuilder : public Builder
{
public:
	virtual ~JeepBuilder() noexcept = default;

public:
	void BuildBody() override
	{
		_car->SetBody(Body{ "SUV" });
	}
	void BuildEngine() override
	{
		_car->SetEngine(Engine{ 400 });
	}
	void BuildWheels() override
	{
		Wheel wheel{ 22 };
		_car->SetWheels({ wheel, wheel, wheel, wheel });
	}
};

class MitsubishiBuilder : public Builder
{
public:
	virtual ~MitsubishiBuilder() = default;

	void BuildBody() override
	{
		_car->SetBody(Body{ "Coupe" });
	}
	void BuildEngine() override
	{
		_car->SetEngine(Engine{ 300 });
	}
	void BuildWheels() override
	{
		Wheel wheel{ 19 };
		_car->SetWheels({ wheel, wheel, wheel, wheel });
	}
};

} // namespace creational
} // namespace pattern

#endif // PATTERNS_CREATIONAL_BUILDER_H
