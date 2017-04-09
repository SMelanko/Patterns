#pragma once

#ifndef PATTERNS_SINGLETON_H
#define PATTERNS_SINGLETON_H

#include <iostream>
#include <memory>

namespace pattern
{
namespace creational
{

//
// Only for testing.
//

//! Session's handle.
class Handle {};
//! Session's status.
enum class STATUS
{
	OPENED,
	CLOSED,
	UNDEFINED
};

//
// Singleton product.
//

class Session
{
public:
	~Session() noexcept = default;
	// Disable copying.
	Session(const Session&) = delete;
	Session& operator=(const Session&) = delete;
	// Disable moving.
	Session(Session&&) noexcept = delete;
	Session& operator=(Session&&) noexcept = delete;

	static Session& GetInstance() noexcept;

	STATUS Open()
	{
		// Do some work with handle...
		_dummyHandle.reset(new Handle);
		// Update status.
		_status = STATUS::OPENED;

		return _status;
	}

	STATUS Close() noexcept
	{
		// Do some work with handle...
		_dummyHandle = nullptr;
		// Update status.
		_status = STATUS::CLOSED;

		return _status;
	}

	STATUS GetStatus() const noexcept
	{
		return _status;
	}

private:
	Session() = default;

private:
	std::unique_ptr<Handle> _dummyHandle = nullptr;
	STATUS _status = STATUS::UNDEFINED;
};

} // namespace creational
} // namespace pattern

#endif // PATTERNS_SINGLETON_H
