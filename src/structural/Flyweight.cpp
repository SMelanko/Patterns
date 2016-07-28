 
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

#include "structural/Flyweight.h"

namespace pattern
{
namespace structural
{

Icon::Icon(const std::string& filename)
	: _filename{ filename }
{
	if (_filename == "go") {
		_width = 20;
		_height = 20;
	} else if (_filename == "stop") {
		_width = 40;
		_height = 40;
	} else if (_filename == "select") {
		_width = 60;
		_height = 60;
	} else if (_filename == "undo") {
		_width = 30;
		_height = 30;
	}
}

IconPtrVector FlyweightFactory::_icons{};

IconPtr FlyweightFactory::GetIcon(const std::string& name)
{
	auto it = std::find_if(_icons.begin(), _icons.end(), [&name](IconPtr icon) {
		return name == icon->GetName();
	});

	if (it != _icons.end()) {
		return *it;
	}

	return CreateNew(name);
}

void FlyweightFactory::ReportTheIcons()
{
	std::cout << "Active Flyweights: ";
	std::for_each(std::cbegin(_icons), std::cend(_icons), [](IconPtr icon) {
		std::cout << icon->GetName() << ' ';
	});
	std::cout << std::endl;
}

IconPtr FlyweightFactory::CreateNew(const std::string& name)
{
	auto newIcon = std::make_shared<Icon>(name);
	_icons.push_back(newIcon);

	return newIcon;
}

} // namespace structural
} // namespace pattern
