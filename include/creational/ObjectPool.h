#pragma once

#ifndef PATTERNS_OBJECT_POOL_H
#define PATTERNS_OBJECT_POOL_H

#include <memory>
#include <vector>

namespace pattern
{
namespace creational
{

class Object
{
};

using ObjectPtr = std::shared_ptr<Object>;

//
// Object pool.
//

class ObjectPool
{
	struct PoolItem;

public:
	~ObjectPool() noexcept = default;
	// Disable copying.
	ObjectPool(const ObjectPool&) = delete;
	ObjectPool& operator=(const ObjectPool&) = delete;
	// Disable moving.
	ObjectPool(ObjectPool&&) noexcept = delete;
	ObjectPool& operator=(ObjectPool&&) noexcept = delete;

	static ObjectPool& GetInstance() noexcept;

	ObjectPtr Acquire();
	void Release(ObjectPtr obj);

	uint32_t Count() const noexcept
	{
		return _cnt;
	}
	size_t Size() const noexcept
	{
		return _pool.size();
	}

private:
	ObjectPool() noexcept = default;
	explicit ObjectPool(const size_t size) noexcept;

	PoolItem CreateNewItem() const
	{
		return PoolItem{ std::make_shared<Object>(), false };
	}

private:
	struct PoolItem
	{
		ObjectPtr _instance;
		bool _inUse;
	};

	std::vector<PoolItem> _pool;
	uint32_t _cnt;
};

} // namespace creational
} // namespace pattern

#endif // PATTERNS_OBJECT_POOL_H
