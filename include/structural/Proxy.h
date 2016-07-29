
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

#ifndef PATTERN_STRUCTURAL_PROXY_H
#define PATTERN_STRUCTURAL_PROXY_H

#include <memory>
#include <iostream>

namespace pattern
{
namespace structural
{

class Image
{
public:
	virtual ~Image() = default;

	virtual void Draw() noexcept = 0;
};

class RealImage : public Image
{
public:
	explicit RealImage(const int id)
		: _id{ id }
	{
		std::cout << "\tctor: " << _id << '\n';
	}
	~RealImage()
	{
		std::cout << "\tdtor: " << _id << '\n';
	}

	void Draw() noexcept override
	{
		std::cout << "\tdrawing image " << _id << '\n';
	}

private:
	int _id;
};

class ImageProxy : public Image
{
public:
	~ImageProxy()
	{
		if (_realImg) {
			--_next;
		}
	}

	void Draw() noexcept override
	{
		// Real object is created after first request.
		if (!_realImg) {
			_realImg.reset(new RealImage{ _next++ });
		}

		_realImg->Draw();
	}

private:
	static int _next;

	std::unique_ptr<Image> _realImg;
};

} // namespace structural
} // namespace pattern

#endif // PATTERN_STRUCTURAL_PROXY_H
