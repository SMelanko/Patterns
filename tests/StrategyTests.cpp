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

#include "behavioral/Strategy.h"

#include <UnitTest++/UnitTest++.h>

#include <gsl/gsl>

using pattern::behavioral::ZipCompression;
using pattern::behavioral::ArjCompression;
using pattern::behavioral::RarCompression;
using pattern::behavioral::Compressor;

using pattern::behavioral::Aes;
using pattern::behavioral::Rsa;
using pattern::behavioral::Cryptor;

template<typename T>
void CheckCompression(T compression)
{
	Expects(compression != nullptr);
	auto compressor = std::make_unique<Compressor>(std::forward<T>(compression));
	Expects(compressor != nullptr);
	compressor->Compress("filename.dat");
}

SUITE(StrategyTest)
{
	TEST(ZipTest)
	{
		CheckCompression(std::make_shared<ZipCompression>());
	}

	TEST(ArjTest)
	{
		CheckCompression(std::make_shared<ArjCompression>());
	}

	TEST(RarTest)
	{
		CheckCompression(std::make_shared<RarCompression>());
	}

	TEST(RarToZipTest)
	{
		std::cout << "RAR -> ZIP" << std::endl;
		auto rar = std::make_shared<RarCompression>();
		Expects(rar != nullptr);
		auto compressor = std::make_unique<Compressor>(rar);
		Expects(compressor != nullptr);
		compressor->Compress("filename.dat");
		auto zip = std::make_shared<ZipCompression>();
		compressor->SetCompression(zip);
		compressor->Compress("filename.dat");
	}

	TEST(TemplateAesTest)
	{
		Cryptor<Aes> cryptor;
		cryptor.Encrypt("filename.txt");
	}

	TEST(TemplateRsaTest)
	{
		Cryptor<Rsa> cryptor;
		cryptor.Encrypt("filename.txt");
	}
}

int main(int, char*[])
{
	return UnitTest::RunAllTests();
}
