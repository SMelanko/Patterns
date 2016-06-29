///////////////////////////////////////////////////////////////////////////////
///
/// Copyright (c) 2016 Slava Melanko. All rights reserved.
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
	virtual void Paint() noexcept = 0;
};

// Product A1.
class WinButton : public Button
{
	inline virtual ~WinButton() = default;
	void Paint() noexcept override
	{
		std::cout << "WinButton" << std::endl;
	}
};

// Product A2.
class MacButton : public Button
{
	inline virtual ~MacButton() = default;
	void Paint() noexcept override
	{
		std::cout << "MacButton" << std::endl;
	}
};

// Product A3.
class UbuntuButton : public Button
{
	inline virtual ~UbuntuButton() = default;
	void Paint() noexcept override
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
	virtual void Paint() noexcept = 0;
};

// Product B1.
class WinScrollBar : public ScrollBar
{
	inline virtual ~WinScrollBar() = default;
	void Paint() noexcept override
	{
		std::cout << "WinScrollBar" << std::endl;
	}
};

// Product B2.
class MacScrollBar : public ScrollBar
{
	inline virtual ~MacScrollBar() = default;
	void Paint() noexcept override
	{
		std::cout << "MacScrollBar" << std::endl;
	}
};

// Product B3.
class UbuntuScrollBar : public ScrollBar
{
	inline virtual ~UbuntuScrollBar() = default;
	void Paint() noexcept override
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
	virtual Button* CreateButton() = 0;
	virtual ScrollBar* CreateScrollBar() = 0;
};

// Concrete factory 1.
class WinFactory : public GuiFactory
{
public:
	inline virtual ~WinFactory() = default;
	Button* CreateButton() override
	{
		return new WinButton{};
	}
	ScrollBar* CreateScrollBar() override
	{
		return new WinScrollBar{};
	}
};

// Concrete factory 2.
class MacFactory : public GuiFactory
{
public:
	inline virtual ~MacFactory() = default;
	Button* CreateButton() override
	{
		return new MacButton{};
	}
	ScrollBar* CreateScrollBar() override
	{
		return new MacScrollBar{};
	}
};

// Concrete factory 3.
class UbuntuFactory : public GuiFactory
{
public:
	inline virtual ~UbuntuFactory() = default;
	Button* CreateButton() override
	{
		return new UbuntuButton{};
	}
	ScrollBar* CreateScrollBar() override
	{
		return new UbuntuScrollBar{};
	}
};

} // namespace creational
} // namespace pattern

#endif // PATTERNS_ABSTRACT_FACTORY_H
