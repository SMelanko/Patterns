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

#include "behavioral/ChainOfResponsibility.h"

namespace pattern
{
namespace behavioral
{

void Handler1::Handle(int i) const noexcept
{
	if (rand() % 3) {
		std::cout << "H1 passsed " << i << "  ";
		Base::Handle(i);
	} else {
		std::cout << "H1 handled " << i << "  ";
	}
}

void Handler2::Handle(int i) const noexcept
{
	if (rand() % 3) {
		std::cout << "H2 passsed " << i << "  ";
		Base::Handle(i);
	} else {
		std::cout << "H2 handled " << i << "  ";
	}
}

void Handler3::Handle(int i) const noexcept
{
	if (rand() % 3) {
		std::cout << "H3 passsed " << i << "  ";
		Base::Handle(i);
	} else {
		std::cout << "H3 handled " << i << "  ";
	}
}

} // namespace behavioral
} // namespace pattern
