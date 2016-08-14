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

#include <functional>
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

using ObserverWeakPtr = std::weak_ptr<Observer>;
using ObserverShPtr = std::shared_ptr<Observer>;
using ObserverPtrVector = std::vector<ObserverWeakPtr>;

//
// Subject.
//

class Subject
{
public:
	void Attach(ObserverShPtr obs);
	auto Count() const noexcept
	{
		return _views.size();
	}
	void Detach(const ObserverShPtr obs);

	inline auto GetVal() const noexcept
	{
		return _val;
	}
	void SetVal(const int val);

	void Notify() noexcept;

private:
	void Remove(std::function<bool (ObserverWeakPtr)> func);

private:
	ObserverPtrVector _views;
	// Here should be data members.
	int _val;
	// ...
};

//
// Concrete observers.
//

class BinObserver : public Observer
{
public:
	void Update(const Subject& subj) const noexcept override;
};

class OctObserver : public Observer
{
public:
	void Update(const Subject& subj) const noexcept override;
};

class HexObserver : public Observer
{
public:
	void Update(const Subject& subj) const noexcept override;
};

} // namespace behavioral
} // namespace pattern

#endif // PATTERNS_OBSERVER_H
