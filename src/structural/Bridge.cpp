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

#include "structural/Bridge.h"

namespace pattern
{
namespace structural
{

ConsoleLogger::ConsoleLogger()
	: Logger(
		#ifdef MT
			new MtLoggerImpl{}
		#else
			new StLoggerImpl{}
		#endif
	)
{
}

void ConsoleLogger::Log(std::string& str) noexcept
{
	_pimpl->ConsoleLog(str);
}

FileLogger::FileLogger(const std::string& filename)
	: Logger(
		#ifdef MT
			new MtLoggerImpl{}
		#else
			new StLoggerImpl{}
		#endif
	), _file(filename)
{
}

void FileLogger::Log(std::string& str) noexcept
{
	_pimpl->FileLog(_file, str);
}

SocketLogger::SocketLogger(const std::string& host, const int port)
	: Logger(
		#ifdef MT
			new MtLoggerImpl{}
		#else
			new StLoggerImpl{}
		#endif
	), _host(host), _port(port)
{
}

void SocketLogger::Log(std::string& str) noexcept
{
	_pimpl->SocketLog(_host, _port, str);
}

} // namespace structural
} // namespace pattern
