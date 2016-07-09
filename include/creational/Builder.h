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

struct Body
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

struct Engine
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

//
// Abstract builder.
//

class Builder
{
public:
	virtual ~Builder() = default;

	virtual Body GetBody() const = 0;
	virtual Engine GetEngine() const = 0;
	virtual Wheels GetWheels() const = 0;
};

//
// Director.
//

class Director
{
public:
	Director() = default;
	Director(std::shared_ptr<Builder> builder)
		: _builder{ builder }
	{
	}

	std::shared_ptr<Car> MakeCar() const
	{
		auto car = std::make_shared<Car>();
		car->SetBody(_builder->GetBody());
		car->SetEngine(_builder->GetEngine());
		car->SetWheels(_builder->GetWheels());
		return car;
	}

	std::shared_ptr<Builder> GetBuilder() const noexcept
	{
		return _builder;
	}

	void SetBuilder(std::shared_ptr<Builder> builder)
	{
		_builder = builder;
	}

private:
	std::shared_ptr<Builder> _builder = nullptr;
};

//
// Concrete builders.
//

class JeepBuilder : public Builder
{
public:
	virtual ~JeepBuilder() = default;

	Body GetBody() const override
	{
		return Body{ "SUV" };
	}
	Engine GetEngine() const override
	{
		return Engine{ 400 };
	}
	Wheels GetWheels() const override
	{
		Wheel wheel{ 22 };
		return { wheel, wheel, wheel, wheel };
	}
};

class MitsubishiBuilder : public Builder
{
public:
	virtual ~MitsubishiBuilder() = default;

	Body GetBody() const override
	{
		return Body{ "Coupe" };
	}
	Engine GetEngine() const override
	{
		return Engine{ 300 };
	}
	Wheels GetWheels() const override
	{
		Wheel wheel{ 19 };
		return { wheel, wheel, wheel, wheel };
	}
};

} // namespace creational
} // namespace pattern

#endif // PATTERNS_BUILDER_H
