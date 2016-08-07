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

#ifndef PATTERNS_STRATEGY_H
#define PATTERNS_STRATEGY_H

#include <iostream>
#include <memory>
#include <string>

namespace pattern
{
namespace behavioral
{

//
// Classic.
//

class Compression
{
public:
	virtual ~Compression() = default;

	virtual void Compress(const std::string& filename) const noexcept = 0;
};

using CompressionShPtr = std::shared_ptr<Compression>;

class ZipCompression : public Compression
{
public:
	void Compress(const std::string& filename) const noexcept override
	{
		std::cout << "ZIP compression -> " << filename << std::endl;
	}
};

class ArjCompression : public Compression
{
public:
	void Compress(const std::string& filename) const noexcept override
	{
		std::cout << "ARJ compression -> " << filename << std::endl;
	}
};

class RarCompression : public Compression
{
public:
	void Compress(const std::string& filename) const noexcept override
	{
		std::cout << "RAR compression -> " << filename << std::endl;
	}
};

class Compressor
{
public:
	Compressor() = default;
	explicit Compressor(CompressionShPtr comp)
		: _comp{ comp }
	{
	}
	~Compressor() = default;

	void Compress(const std::string& filename) const noexcept
	{
		_comp->Compress(filename);
	}

	void SetCompression(CompressionShPtr comp) noexcept
	{
		_comp = comp;
	}

private:
	CompressionShPtr _comp = nullptr;
};

//
// Template parameter.
//

class Aes
{
public:
	void Encrypt(const std::string& filename) const noexcept
	{
		std::cout << "AES encrypting -> " << filename << std::endl;
	}
};

class Rsa
{
public:
	void Encrypt(const std::string& filename) const noexcept
	{
		std::cout << "RSA encrypting -> " << filename << std::endl;
	}
};

template<typename Algo>
class Cryptor : public Algo
{
public:
	void Encrypt(const std::string& filename) const noexcept
	{
		Algo::Encrypt(filename);
	}
};

} // namespace behavioral
} // namespace pattern

#endif // PATTERNS_STRATEGY_H
