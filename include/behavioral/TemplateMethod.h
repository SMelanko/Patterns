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

#ifndef PATTERNS_TEMPLATE_METHOD_H
#define PATTERNS_TEMPLATE_METHOD_H

#include <iostream>
#include <random>

namespace pattern
{
namespace behavioral
{

class CaffeineBeverage
{
public:
	virtual ~CaffeineBeverage() = default;

	virtual void PrepareRecipe() noexcept final
	{
		BoilWater();
		Brew();
		PourInCup();
		if (CustomerWantsCondiments()) {
			AddCondiments();
		}
	}

private:
	virtual void BoilWater() noexcept final
	{
		std::cout << "Boiling water\n";
	}

	virtual void Brew() noexcept = 0;

	virtual void PourInCup() noexcept final
	{
		std::cout << "Pouring into cup\n";
	}

	virtual void AddCondiments() noexcept = 0;

	virtual bool CustomerWantsCondiments() noexcept
	{
		std::random_device rd;
		std::mt19937 mt{ rd() };
		std::uniform_int_distribution<> dist{ 1, 2 };
		return (dist(mt) % 2 == 0) ? true : false;
	}
};

class Tea : public CaffeineBeverage
{
private:
	void Brew() noexcept override
	{
		std::cout << "Steeping the tea\n";
	}

	void AddCondiments() noexcept override
	{
		std::cout << "Adding lemon\n";
	}

	bool CustomerWantsCondiments() noexcept override
	{
		return true;
	}
};

class Coffee : public CaffeineBeverage
{
private:
	void Brew() noexcept override
	{
		std::cout << "Dripping coffee through filter\n";
	}

	void AddCondiments() noexcept override
	{
		std::cout << "Adding sugar and milk\n";
	}
};

} // namespace behavioral
} // namespace pattern

#endif // PATTERNS_TEMPLATE_METHOD_H
