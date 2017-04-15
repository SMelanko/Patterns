#pragma once

#ifndef PATTERNS_CREATIONAL_ABSTRACT_FACTORY_H
#define PATTERNS_CREATIONAL_ABSTRACT_FACTORY_H

///
/// Creates an instance of several families of classes.
///

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
	inline virtual ~Button() noexcept = default;

public:
	virtual void Paint() const noexcept = 0;
};

using ButtonUnPtr = std::unique_ptr<Button>;

//
// Specific A products.
//

class WinButton : public Button
{
public:
	inline virtual ~WinButton() noexcept = default;

public:
	void Paint() const noexcept override
	{
		std::cout << "WinButton" << std::endl;
	}
};

class MacButton : public Button
{
public:
	inline virtual ~MacButton() noexcept = default;

public:
	void Paint() const noexcept override
	{
		std::cout << "MacButton" << std::endl;
	}
};

class UbuntuButton : public Button
{
public:
	inline virtual ~UbuntuButton() noexcept = default;

public:
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
	inline virtual ~ScrollBar() noexcept = default;

public:
	virtual void Paint() const noexcept = 0;
};

using ScrollBarUnPtr = std::unique_ptr<ScrollBar>;

//
// Specific B products.
//

class WinScrollBar : public ScrollBar
{
public:
	inline virtual ~WinScrollBar() noexcept = default;

public:
	void Paint() const noexcept override
	{
		std::cout << "WinScrollBar" << std::endl;
	}
};

class MacScrollBar : public ScrollBar
{
public:
	inline virtual ~MacScrollBar() noexcept = default;

public:
	void Paint() const noexcept override
	{
		std::cout << "MacScrollBar" << std::endl;
	}
};

class UbuntuScrollBar : public ScrollBar
{
public:
	inline virtual ~UbuntuScrollBar() noexcept = default;

public:
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
	inline virtual ~GuiFactory() noexcept = default;

public:
	virtual ButtonUnPtr CreateButton() const = 0;
	virtual ScrollBarUnPtr CreateScrollBar() const = 0;
};

//
// Specific factories.
//

class WinFactory : public GuiFactory
{
public:
	inline virtual ~WinFactory() noexcept = default;

public:
	ButtonUnPtr CreateButton() const override
	{
		return std::make_unique<WinButton>();
	}
	ScrollBarUnPtr CreateScrollBar() const override
	{
		return std::make_unique<WinScrollBar>();
	}
};

class MacFactory : public GuiFactory
{
public:
	inline virtual ~MacFactory() noexcept = default;

public:
	ButtonUnPtr CreateButton() const override
	{
		return std::make_unique<MacButton>();
	}
	ScrollBarUnPtr CreateScrollBar() const override
	{
		return std::make_unique<MacScrollBar>();
	}
};

class UbuntuFactory : public GuiFactory
{
public:
	inline virtual ~UbuntuFactory() noexcept = default;

public:
	ButtonUnPtr CreateButton() const override
	{
		return std::make_unique<UbuntuButton>();
	}
	ScrollBarUnPtr CreateScrollBar() const override
	{
		return std::make_unique<UbuntuScrollBar>();
	}
};

} // namespace creational
} // namespace pattern

#endif // PATTERNS_CREATIONAL_ABSTRACT_FACTORY_H
