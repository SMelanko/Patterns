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

#ifndef PATTERNS_CHAIN_OF_RESPONSIBILITY_H
#define PATTERNS_CHAIN_OF_RESPONSIBILITY_H

#include <memory>
#include <iostream>
#include <vector>

namespace pattern
{
namespace behavioral
{

class Base
{
public:
	using BaseShPtr = std::shared_ptr<Base>;

	Base() = default;
	virtual ~Base() = default;

	void Add(BaseShPtr node) noexcept
	{
		if (_next) {
			_next->Add(node);
		} else {
			SetNext(node);
		}
	}
	void SetNext(BaseShPtr node) noexcept
	{
		_next = node;
	}

	virtual void Handle(int i) const noexcept
	{
		if (_next) {
			_next->Handle(i);
		}
	}

private:
	BaseShPtr _next = nullptr;
};

class Handler1: public Base
{
public:
	void Handle(int i) const noexcept override;
};

class Handler2: public Base
{
public:
	void Handle(int i) const noexcept override;
};

class Handler3: public Base
{
public:
	void Handle(int i) const noexcept override;
};

//
// Chain of Responsibility: Chain and Composite.
//

class Component
{
public:
	using ComponentShPtr = std::shared_ptr<Component>;

	Component(const int val, ComponentShPtr node)
		: _value{ val }
		, _next{ node }
	{
	}

	void SetNext(ComponentShPtr node)
	{
		_next = node;
	}

	virtual void Traverse()
	{
		std::cout << _value << ' ';
	}

	virtual void Volunteer()
	{
		_next->Volunteer();
	}

private:
	int _value;
	ComponentShPtr _next;
};

class Primitive: public Component
{
public:
	Primitive(int val, ComponentShPtr node = nullptr)
		: Component{ val, node }
	{
	}

	void Volunteer()
	{
		Component::Traverse();

		if (rand() * 100 % 6 != 0) {
			Component::Volunteer();
		}
	}
};

class Composite: public Component
{
public:
	Composite(const int val, ComponentShPtr node = nullptr)
		: Component{ val, node }
	{
	}

	void Add(ComponentShPtr comp)
	{
		_children.push_back(comp);
	}

	void Traverse() override
	{
		Component::Traverse();
		for (decltype(_children.size()) i = 0; i < _children.size(); i++) {
			_children[i]->Traverse();
		}
	}

	void Volunteer() override
	{
		Component::Volunteer();
	}

private:
	std::vector<ComponentShPtr> _children;
};

} // namespace behavioral
} // namespace pattern

#endif // PATTERNS_CHAIN_OF_RESPONSIBILITY_H
