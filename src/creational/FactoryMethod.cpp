#include "creational/FactoryMethod.h"

namespace pattern
{
namespace creational
{

Factory::MapType Factory::_map;

WarriorUnPtr Factory::CreateInstance(const std::string& s)
{
	auto it = _map.find(s);

	return (it == _map.end()) ? nullptr : it->second();
}

REGISTER_DEF_TYPE(Infantryman);

REGISTER_DEF_TYPE(Archer);

} // namespace creational
} // namespace pattern
