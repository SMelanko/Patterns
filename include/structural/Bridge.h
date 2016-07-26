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

#ifndef PATTERN_STRUCTURAL_BRIDGE_H
#define PATTERN_STRUCTURAL_BRIDGE_H

#include <memory>
#include <string>

#include "structural/utils/LoggerImpl.h"

namespace pattern
{
namespace structural
{

class Logger
{
public:
	explicit Logger(LoggerImpl* impl)
		: _pimpl{ impl }
	{
	}
	virtual ~Logger() = default;

	virtual void Log(std::string& str) noexcept = 0;

protected:
	std::unique_ptr<LoggerImpl> _pimpl;
};

//
// Concrete loggers.
//

class ConsoleLogger : public Logger
{
public:
	ConsoleLogger();

	void Log(std::string& str) noexcept override;
};

class FileLogger : public Logger
{
public:
	explicit FileLogger(const std::string& filename);

	void Log(std::string& str) noexcept override;

private:
	std::string _file;
};

class SocketLogger : public Logger
{
public:
	SocketLogger(const std::string& host, const int port);

	void Log(std::string& str) noexcept override;

private:
	std::string _host;
	int _port;
};

} // namespace structural
} // namespace pattern

#endif // PATTERN_STRUCTURAL_BRIDGE_H
