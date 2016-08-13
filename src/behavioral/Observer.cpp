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

namespace pattern
{
namespace behavioral
{

void Subject::Attach(ObserverPtr obs)
{
	_views.push_back(obs);
}

void Subject::Detach(const ObserverPtr obs)
{
	auto func = [obs](const ObserverPtr o) { return o == obs; };
	auto it = std::find_if(std::cbegin(_views), std::cend(_views), func);
	if (it != std::cend(_views)) {
		_views.erase(it);
	}
}

void Subject::SetVal(const int val)
{
	_val = val;
	Notify();
}

void Subject::Notify() const noexcept
{
	for (const auto& view : _views) {
		view->Update(*this);
	}
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
