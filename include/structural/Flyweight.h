
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

#ifndef PATTERN_STRUCTURAL_FLYWEIGHT_H
#define PATTERN_STRUCTURAL_FLYWEIGHT_H

#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace pattern
{
namespace structural
{

class Icon
{
public:
	explicit Icon(const std::string& filename);

	std::string GetName() const noexcept
	{
		return _filename;
	}

	void Draw(const int x, const int y) const noexcept
	{
		std::cout << "   drawing " << _filename
			<< ": upper left (" << x << "," << y
			<< ") - lower right (" << x + _width << ","
			<< y + _height << ")" << std::endl;
	}

private:
	std::string _filename;
	int _width;
	int _height;
};

using IconPtr = std::shared_ptr<Icon>;
using IconPtrVector = std::vector<IconPtr>;

class FlyweightFactory
{
public:
	FlyweightFactory() = delete;

	static IconPtr GetIcon(const std::string& name);
	static void ReportTheIcons();

private:
	static IconPtr CreateNew(const std::string& name);

private:
	static IconPtrVector _icons;
};

class DialogBox
{
public:
	explicit DialogBox(const int x, const int y, const int incr)
		: _iconsOriginX{ x }
		, _iconsOriginY{ y }
		, _iconsXIncrement{ incr }
	{
	}
	virtual ~DialogBox() = default;

	virtual void Draw() const noexcept = 0;

protected:
	std::array<IconPtr, 3> _icons;
	int _iconsOriginX;
	int _iconsOriginY;
	int _iconsXIncrement;
};

class FileSelection: public DialogBox
{
public:
	FileSelection(IconPtr first, IconPtr second, IconPtr third)
		: DialogBox{ 100, 100, 100 }
	{
		_icons[0] = first;
		_icons[1] = second;
		_icons[2] = third;
	}

	void Draw() const noexcept override
	{
		std::cout << "drawing FileSelection:" << std::endl;
		int i = 0;
		std::for_each(std::begin(_icons), std::end(_icons), [&i, this](IconPtr icon) {
			icon->Draw(_iconsOriginX + (i *_iconsXIncrement), _iconsOriginY);
			++i;
		});
	}
};

class CommitTransaction: public DialogBox
{
public:
	CommitTransaction(IconPtr first, IconPtr second, IconPtr third)
		: DialogBox{ 150, 150, 150 }
	{
		_icons[0] = first;
		_icons[1] = second;
		_icons[2] = third;
	}

	void Draw() const noexcept override
	{
		std::cout << "drawing CommitTransaction:" << std::endl;
		int i = 0;
		std::for_each(std::begin(_icons), std::end(_icons), [&i, this](IconPtr icon) {
			icon->Draw(_iconsOriginX + (i *_iconsXIncrement), _iconsOriginY);
			++i;
		});
	}
};

} // namespace structural
} // namespace pattern

#endif // PATTERN_STRUCTURAL_FLYWEIGHT_H
