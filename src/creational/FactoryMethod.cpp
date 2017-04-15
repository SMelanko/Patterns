#include "creational/FactoryMethod.h"

namespace pattern
{
namespace creational
{

ExchangeConnectorFactory::MapType ExchangeConnectorFactory::_map;

ExchangeConnectorUnPtr ExchangeConnectorFactory::Create(const std::string& s)
{
	auto it = _map.find(s);

	return (it != _map.end()) ? it->second() : nullptr;
}

REGISTER_DEF_TYPE(GoogleAdX);

REGISTER_DEF_TYPE(Smaato);

WarriorUnPtr InfantryFactory::CreateWarrior()
{
	return std::make_unique<Infantryman>();
}

WarriorUnPtr ArchersFactory::CreateWarrior()
{
	return std::make_unique<Archer>();
}

} // namespace creational
} // namespace pattern
