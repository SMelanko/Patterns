#include "creational/ObjectPool.h"

namespace pattern
{
namespace creational
{

ObjectPool::ObjectPool(const size_t size) noexcept
{
	_pool.reserve(size);
	for (size_t i = 0; i < size; ++i) {
		_pool.emplace_back(CreateNewItem());
	}
	_cnt = size;
}

ObjectPool& ObjectPool::GetInstance() noexcept
{
	static ObjectPool pool{ 10 };
	return pool;
}

ObjectPtr ObjectPool::Acquire()
{
	for (auto& item : _pool) {
		if (!item._inUse) {
			item._inUse = true;
			--_cnt;
			return item._instance;
		}
	}

	// If there is no free object - extend the pool.
	auto record = CreateNewItem();
	_pool.emplace_back(record);

	return record._instance;
}

void ObjectPool::Release(ObjectPtr obj)
{
	// In fact we only mark that object is free now.
	for (auto& item : _pool) {
		if (item._instance.get() == obj.get()) {
			item._inUse = false;
			++_cnt;
			break;
		}
	}
}

} // namespace creational
} // namespace pattern
