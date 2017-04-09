#include "creational/Prototype.h"

namespace pattern
{
namespace creational
{

WarriorUnPtr PrototypeFactory::CreateArcher() const {
	static Archer prototype;
	return prototype.Clone();
}

WarriorUnPtr PrototypeFactory::CreateInfantryman() const {
	static Infantryman prototype;
	return prototype.Clone();
}

} // namespace creational
} // namespace pattern
