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

#ifndef PATTERN_STRUCTURAL_ADAPTER_CLASSIC_H
#define PATTERN_STRUCTURAL_ADAPTER_CLASSIC_H

#include <memory>

namespace pattern
{
namespace structural
{

//
// Adapter classic.
//

// This is already existing class.
class FahrenheitSensor
{
public:
	float GetFahrenheitTemp() const noexcept
	{
		float t = 32.0;
		// ...
		return t;
	}
};

class CelsiusSensor
{
public:
	virtual ~CelsiusSensor() = default;

	virtual float GetTemperature() const noexcept = 0;
};

class Adapter : public CelsiusSensor
{
public:
	explicit Adapter(FahrenheitSensor* p)
		: _fsensor{ p }
	{
	}

	float GetTemperature() const noexcept override
	{
		return (_fsensor->GetFahrenheitTemp() - 32.0) * 5.0 / 9.0;
	}

private:
	std::unique_ptr<FahrenheitSensor> _fsensor;
};

//
// Adapter with private inheritance.
//

// This is already existing class.
class FahrenheitSensor1
{
public:
	auto GetFahrenheitTemp() const noexcept {
		float t = 32.0;
		// ...
		return t;
	}

protected:
	void Adjust() const noexcept
	{
		// ...
	}
};

class CelsiusSensor1
{
public:
	virtual ~CelsiusSensor1() = default;

	virtual void Adjust() const noexcept = 0;
	virtual float GetTemperature() const noexcept = 0;
};

class Adapter1 : public CelsiusSensor1, private FahrenheitSensor1
{
public:
	virtual ~Adapter1() = default;

	void Adjust() const noexcept override
	{
		FahrenheitSensor1::Adjust();
	}
	float GetTemperature() const noexcept override
	{
		return (GetFahrenheitTemp() - 32.0) * 5.0 / 9.0;
	}
};

} // namespace structural
} // namespace pattern

#endif // PATTERN_STRUCTURAL_ADAPTER_CLASSIC_H
