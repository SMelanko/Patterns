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

#ifndef PATTERNS_OBSERVER_H
#define PATTERNS_OBSERVER_H

#include <ios>
#include <iostream>
#include <memory>
#include <vector>

namespace pattern
{
namespace behavioral
{

class Subject;

//
// Observer.
//

class Observer
{
public:
	virtual ~Observer() = default;

	virtual void Update(const Subject& sub) const noexcept = 0;
};

using ObserverPtr = Observer*;
using ObserverPtrVector = std::vector<ObserverPtr>;

//
// Subject.
//

class Subject
{
public:
	void Attach(ObserverPtr obs);
	auto Count() const noexcept
	{
		return _views.size();
	}
	void Detach(const ObserverPtr obs);

	inline auto GetVal() const noexcept
	{
		return _val;
	}
	void SetVal(const int val);

	void Notify() const noexcept;

private:
	ObserverPtrVector _views;

	int _val;
};

//
// Concrete observers.
//

class BinObserver : public Observer
{
public:
	BinObserver(Subject& subj)
	{
		subj.Attach(this);
	}

	void Update(const Subject& subj) const noexcept override;
};

class OctObserver : public Observer
{
public:
	OctObserver(Subject& subj)
	{
		subj.Attach(this);
	}

	void Update(const Subject& subj) const noexcept override;
};

class HexObserver : public Observer
{
public:
	HexObserver(Subject& subj)
	{
		subj.Attach(this);
	}

	void Update(const Subject& subj) const noexcept override;
};

} // namespace behavioral
} // namespace pattern

#endif // PATTERNS_OBSERVER_H
