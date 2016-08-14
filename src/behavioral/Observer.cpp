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

#include "behavioral/Observer.h"

#include <algorithm>
#include <ios>
#include <iostream>

namespace pattern
{
namespace behavioral
{

void Subject::Attach(ObserverShPtr obs)
{
	_views.push_back(obs);
}

void Subject::Detach(const ObserverShPtr obs)
{
	// Removes observer from the list.
	auto func = [obs](ObserverWeakPtr wptr) {
		auto sptr = wptr.lock();
		return (sptr) ? sptr.get() == obs.get() : false;
	};

	Remove(func);
}

void Subject::SetVal(const int val)
{
	_val = val;
	Notify();
}

void Subject::Notify() noexcept
{
	bool clear = false;
	for (const auto& view : _views) {
		auto observer = view.lock();
		if (observer) {
			observer->Update(*this);
		} else {
			clear = true;
		}
	}

	if (clear) {
		// Removes observer from the list which is dangle.
		Remove([](ObserverWeakPtr obs) { return obs.lock() == nullptr; });
	}
}

void Subject::Remove(std::function<bool (ObserverWeakPtr)> func)
{
	auto it = std::remove_if(std::begin(_views), std::end(_views), func);
	_views.erase(it, _views.end());
}

void BinObserver::Update(const Subject& subj) const noexcept
{
	const auto val = subj.GetVal();
	const auto bin = std::bitset<8>(val).to_string();
	std::cout << "Bin is " << bin << '\n';
}

void OctObserver::Update(const Subject& subj) const noexcept
{
	const auto val = subj.GetVal();
	std::cout << "Oct is " << std::oct << val << '\n';
}

void HexObserver::Update(const Subject& subj) const noexcept
{
	const auto val = subj.GetVal();
	std::cout << "Hex is " << std::hex << val << '\n';
}

} // namespace behavioral
} // namespace pattern
