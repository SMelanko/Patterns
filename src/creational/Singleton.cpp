#include "creational/Singleton.h"

namespace pattern
{
namespace creational
{

Session& Session::GetInstance() noexcept
{
	static Session instance;
	return instance;
}

} // namespace creational
} // namespace pattern
