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

#ifndef PATTERNS_ABSTRACT_FACTORY_H
#define PATTERNS_ABSTRACT_FACTORY_H

#include <iostream>
#include <memory>

namespace pattern
{
namespace creational
{

//
// Abstract product A.
//

class Button
{
public:
	inline virtual ~Button() = default;
	virtual void Paint() const noexcept = 0;
};

// Product A1.
class WinButton : public Button
{
public:
	inline virtual ~WinButton() = default;
	void Paint() const noexcept override
	{
		std::cout << "WinButton" << std::endl;
	}
};

// Product A2.
class MacButton : public Button
{
public:
	inline virtual ~MacButton() = default;
	void Paint() const noexcept override
	{
		std::cout << "MacButton" << std::endl;
	}
};

// Product A3.
class UbuntuButton : public Button
{
public:
	inline virtual ~UbuntuButton() = default;
	void Paint() const noexcept override
	{
		std::cout << "UbuntuButton" << std::endl;
	}
};

//
// Abstract product B.
//

class ScrollBar
{
public:
	inline virtual ~ScrollBar() = default;
	virtual void Paint() const noexcept = 0;
};

// Product B1.
class WinScrollBar : public ScrollBar
{
public:
	inline virtual ~WinScrollBar() = default;
	void Paint() const noexcept override
	{
		std::cout << "WinScrollBar" << std::endl;
	}
};

// Product B2.
class MacScrollBar : public ScrollBar
{
public:
	inline virtual ~MacScrollBar() = default;
	void Paint() const noexcept override
	{
		std::cout << "MacScrollBar" << std::endl;
	}
};

// Product B3.
class UbuntuScrollBar : public ScrollBar
{
public:
	inline virtual ~UbuntuScrollBar() = default;
	void Paint() const noexcept override
	{
		std::cout << "UbuntuScrollBar" << std::endl;
	}
};

//
// Abstract factory.
//

class GuiFactory
{
public:
	inline virtual ~GuiFactory() = default;
	virtual std::unique_ptr<Button> CreateButton() const = 0;
	virtual std::unique_ptr<ScrollBar> CreateScrollBar() const = 0;
};

// Concrete factory 1.
class WinFactory : public GuiFactory
{
public:
	inline virtual ~WinFactory() = default;
	std::unique_ptr<Button> CreateButton() const override
	{
		return std::make_unique<WinButton>();
	}
	std::unique_ptr<ScrollBar> CreateScrollBar() const override
	{
		return std::make_unique<WinScrollBar>();
	}
};

// Concrete factory 2.
class MacFactory : public GuiFactory
{
public:
	inline virtual ~MacFactory() = default;
	std::unique_ptr<Button> CreateButton() const override
	{
		return std::make_unique<MacButton>();
	}
	std::unique_ptr<ScrollBar> CreateScrollBar() const override
	{
		return std::make_unique<MacScrollBar>();
	}
};

// Concrete factory 3.
class UbuntuFactory : public GuiFactory
{
public:
	inline virtual ~UbuntuFactory() = default;
	std::unique_ptr<Button> CreateButton() const override
	{
		return std::make_unique<UbuntuButton>();
	}
	std::unique_ptr<ScrollBar> CreateScrollBar() const override
	{
		return std::make_unique<UbuntuScrollBar>();
	}
};

} // namespace creational
} // namespace pattern

#endif // PATTERNS_ABSTRACT_FACTORY_H
