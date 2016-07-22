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

#ifndef PATTERN_STRUCTURAL_UTILS_LOGGER_IMPL_H
#define PATTERN_STRUCTURAL_UTILS_LOGGER_IMPL_H

#include <iostream>
#include <string>

namespace pattern
{
namespace structural
{

class LoggerImpl
{
public:
	virtual ~LoggerImpl() = default;

	virtual void ConsoleLog(std::string& /*str*/) = 0;
	virtual void FileLog(std::string& /*file*/, std::string& /*str*/) = 0;
	virtual void SocketLog(std::string& /*host*/, int /*port*/, std::string& /*str*/) = 0;
};

class StLoggerImpl : public LoggerImpl
{
public:
	void ConsoleLog(std::string&)
	{
		std::cout << "Single-threaded console logger" << std::endl;
	}
	void FileLog(std::string&, std::string&)
	{
		std::cout << "Single-threaded file logger" << std::endl;
	}
	void SocketLog(std::string&, int, std::string&)
	{
		std::cout << "Single-threaded socket logger" << std::endl;
	}
};

class MtLoggerImpl : public LoggerImpl
{
public:
	void ConsoleLog(std::string&)
	{
		std::cout << "Multithreaded console logger" << std::endl;
	}
	void FileLog(std::string&, std::string&)
	{
		std::cout << "Multithreaded file logger" << std::endl;
	}
	void SocketLog(std::string&, int, std::string&)
	{
		std::cout << "Multithreaded socket logger" << std::endl;
	}
};

} // namespace creational
} // namespace structural

#endif // PATTERN_STRUCTURAL_UTILS_LOGGER_IMPL_H
