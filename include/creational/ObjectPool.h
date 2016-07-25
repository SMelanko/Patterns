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
