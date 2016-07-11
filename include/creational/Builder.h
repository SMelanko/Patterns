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

#ifndef PATTERNS_BUILDER_H
#define PATTERNS_BUILDER_H

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
	Body() = default;
	explicit Body(const std::string& shape) noexcept
		: _shape{ shape }
	{
	}

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
	constexpr Engine() = default;
	explicit constexpr Engine(const int horsepower)
		: _horsepower{ horsepower }
	{
	}

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
	constexpr Wheel() = default;
	explicit constexpr Wheel(const int size) noexcept
		: _size{ size }
	{
	}

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

	void PrintSpecifications() const noexcept
	{
		std::cout << "Body: " << body.GetShape() << std::endl;
		std::cout << "Engine horsepower: " << engine.GetHorsePower() << std::endl;
		std::cout << "Tire size: " << wheels[0].GetSize() << "'" << std::endl;
	}

	Body GetBody() const noexcept
	{
		return body;
	}
	Engine GetEngine() const noexcept
	{
		return engine;
	}
	Wheels GetWheels() const noexcept
	{
		return wheels;
	}

	void SetBody(const Body& value)
	{
		body = value;
	}
	void SetEngine(const Engine& value)
	{
		engine = value;
	}
	void SetWheels(const Wheels& value)
	{
		wheels = value;
	}

private:
	Body body;
	Engine engine;
	Wheels wheels;
};

using CarPtr = std::shared_ptr<Car>;

//
// Abstract builder.
//

class Builder
{
public:
	virtual ~Builder() = default;

	virtual void BuildBody() = 0;
	virtual void BuildEngine() = 0;
	virtual void BuildWheels() = 0;

	void CreateNewCar()
	{
		_car.reset(new Car{});
	}

	CarPtr GetCar() const noexcept
	{
		return _car;
	}

protected:
	CarPtr _car;
};

//
// Director.
//

class Director
{
public:
	using BuilderPtr = std::shared_ptr<Builder>;

	Director() = default;
	Director(BuilderPtr builder)
		: _builder{ builder }
	{
	}

	CarPtr ConstructCar() const
	{
		_builder->CreateNewCar();
		_builder->BuildBody();
		_builder->BuildEngine();
		_builder->BuildWheels();
		return _builder->GetCar();
	}

	BuilderPtr GetBuilder() const noexcept
	{
		return _builder;
	}

	void SetBuilder(BuilderPtr builder)
	{
		_builder = builder;
	}

private:
	BuilderPtr _builder = nullptr;
};

//
// Concrete builders.
//

class JeepBuilder : public Builder
{
public:
	virtual ~JeepBuilder() = default;

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

#endif // PATTERNS_BUILDER_H
