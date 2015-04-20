#include "CryptoppWrapper.h"

#include <cryptopp\aes.h>
#include <cryptopp\ccm.h>
#include <cryptopp\hex.h>
#include <cryptopp\filters.h>
#include <cryptopp\osrng.h>

#include <iostream>

namespace ThirdParty
{
	void Encrypt(std::string& cipher, std::string& key, std::string& iv, const std::string& plainText)
	{
		CryptoPP::AutoSeededRandomPool aAutoSeededRandomPool;

		byte aKey[CryptoPP::AES::DEFAULT_KEYLENGTH];
		aAutoSeededRandomPool.GenerateBlock(aKey, sizeof(aKey));

		byte aIv[CryptoPP::AES::BLOCKSIZE];
		aAutoSeededRandomPool.GenerateBlock(aIv, sizeof(aIv));

		//*************************************************************************************
		// for test only
		//*************************************************************************************		// Pretty print iv
		std::string aEncodedKey, aEncodedIv;

		aEncodedIv.clear();
		CryptoPP::StringSource(aIv, sizeof(aIv), true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(aEncodedIv)));
		std::cout << "iv: " << aEncodedIv << std::endl;

		// Pretty print key
		aEncodedKey.clear();
		CryptoPP::StringSource(aKey, sizeof(aKey), true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(aEncodedKey)));
		std::cout << "key: " << aEncodedKey << std::endl;
		//*************************************************************************************

		try
		{
			long temp1 = sizeof(aKey);
			CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption aEncryption;
			aEncryption.SetKeyWithIV(aKey, sizeof(aKey), aIv);
			// The StreamTransformationFilter removes padding as required.
			CryptoPP::StringSource aStringSource(plainText,
												 true,
												 new CryptoPP::StreamTransformationFilter(aEncryption, new CryptoPP::StringSink(cipher)));

			key.swap(aEncodedKey);
			iv.swap(aEncodedIv);
		}
		catch (const CryptoPP::Exception& e)
		{
			throw std::runtime_error(e.what());
		}

	}

	void Decrypt(std::string& decipher, const std::string& cipher, const std::string& key, const std::string& iv)
	{
		byte aKey[CryptoPP::AES::DEFAULT_KEYLENGTH];
		byte aIv[CryptoPP::AES::BLOCKSIZE];

		CryptoPP::StringSource ssKey(key,
									 true,
									 new CryptoPP::HexDecoder(new CryptoPP::ArraySink(aKey, CryptoPP::AES::DEFAULT_KEYLENGTH)));

		CryptoPP::StringSource ssIv(iv,
									true,
									new CryptoPP::HexDecoder(new CryptoPP::ArraySink(aIv, CryptoPP::AES::BLOCKSIZE)));

		try
		{
			CryptoPP::CBC_Mode< CryptoPP::AES >::Decryption aDecryption;
			long temp1 = sizeof(aKey);
			aDecryption.SetKeyWithIV(aKey, sizeof(aKey), aIv);

			// The StreamTransformationFilter removes
			//  padding as required.
			CryptoPP::StringSource aStringSource(cipher,
												 true,
												 new CryptoPP::StreamTransformationFilter(aDecryption, new CryptoPP::StringSink(decipher)));
		}
		catch (const CryptoPP::Exception& e)
		{
			throw std::runtime_error(e.what());
		}
	}

	class Aes::Imp
	{
	public:
		Imp();
		~Imp();

		void Encrypt(std::string& cipherText, const std::string& plainText);
		void Decrypt(std::string& plainText, const std::string& cipherText);
	private:
		Imp(const Imp& other);
		Imp& operator=(const Aes&) { return *this; }

		CryptoPP::SecByteBlock mKey;
		CryptoPP::SecByteBlock mIv;
	};

	Aes::Imp::Imp()
		:mKey(CryptoPP::AES::DEFAULT_KEYLENGTH), mIv(CryptoPP::AES::BLOCKSIZE)
	{
		CryptoPP::AutoSeededRandomPool aAutoSeededRandomPool;
		aAutoSeededRandomPool.GenerateBlock(mKey, mKey.size());
		aAutoSeededRandomPool.GenerateBlock(mIv, mIv.size());
	}

	void Aes::Imp::Encrypt(std::string& cipherText, const std::string& plainText)
	{
		try
		{
			cipherText.clear();
			CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption aEncryption;
			aEncryption.SetKeyWithIV(mKey, mKey.size(), mIv);
			// The StreamTransformationFilter removes padding as required.
			CryptoPP::StringSource aStringSource(plainText, true,
												 new CryptoPP::StreamTransformationFilter(aEncryption, new CryptoPP::StringSink(cipherText)));
		}
		catch (const CryptoPP::Exception& e)
		{
			throw std::runtime_error(e.what());
		}
	}

	void Aes::Imp::Decrypt(std::string& plainText, const std::string& cipherText)
	{
		try
		{
			CryptoPP::CBC_Mode< CryptoPP::AES >::Decryption aDecryption;
			long temp1 = sizeof(mKey);
			aDecryption.SetKeyWithIV(mKey, mKey.size(), mIv);

			// The StreamTransformationFilter removes
			//  padding as required.
			CryptoPP::StringSource aStringSource(cipherText,
												 true,
												 new CryptoPP::StreamTransformationFilter(aDecryption, new CryptoPP::StringSink(plainText)));
		}
		catch (const CryptoPP::Exception& e)
		{
			throw std::runtime_error(e.what());
		}
	}

	Aes::Imp::~Imp()
	{
		mKey.empty();
		mIv.empty();
	}

	Aes::Aes()
		:mImp(new Imp())
	{
	}

	Aes::~Aes()
	{
		if (mImp)
			delete mImp;
	}

	void Aes::Encrypt(std::string& cipherText, const std::string& plainText)
	{
		mImp->Encrypt(cipherText, plainText);
	}

	void Aes::Decrypt(std::string& plainText, const std::string& cipherText)
	{
		mImp->Decrypt(plainText, cipherText);
	}

} //namespace ThirdParty

//*********************************************************************************************

//
//// g++ -g3 -ggdb -O0 -DDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread
//// g++ -g -O2 -DNDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread
//
//#include <CryptoPP/osrng.h>
//using CryptoPP::AutoSeededRandomPool;
//
//#include <iostream>
//using std::cout;
//using std::cerr;
//using std::endl;
//
//#include <string>
//using std::string;
//
//#include <cstdlib>
//using std::exit;
//
//#include <CryptoPP/cryptlib.h>
//using CryptoPP::Exception;
//
//#include <CryptoPP/hex.h>
//using CryptoPP::HexEncoder;
//using CryptoPP::HexDecoder;
//
//#include <CryptoPP/filters.h>
//using CryptoPP::StringSink;
//using CryptoPP::StringSource;
//using CryptoPP::StreamTransformationFilter;
//
//#include <CryptoPP/aes.h>
//using CryptoPP::AES;
//
//#include <CryptoPP/ccm.h>
//using CryptoPP::CBC_Mode;
//
//#include "assert.h"
//
//namespace ThirdParty
//{
//	int TestExample()
//	{
//		AutoSeededRandomPool prng;
//
//		byte key[AES::DEFAULT_KEYLENGTH];
//		prng.GenerateBlock(key, sizeof(key));
//
//		byte iv[AES::BLOCKSIZE];
//		prng.GenerateBlock(iv, sizeof(iv));
//
//		string plain = "CBC Mode Test";
//		string cipher, encoded, recovered;
//
//		/*********************************\
//		\*********************************/
//
//		// Pretty print key
//		encoded.clear();
//		StringSource(key, sizeof(key), true,
//					 new HexEncoder(
//					 new StringSink(encoded)
//					 ) // HexEncoder
//					 ); // StringSource
//		cout << "key: " << encoded << endl;
//
//		// Pretty print iv
//		encoded.clear();
//		StringSource(iv, sizeof(iv), true,
//					 new HexEncoder(
//					 new StringSink(encoded)
//					 ) // HexEncoder
//					 ); // StringSource
//		cout << "iv: " << encoded << endl;
//
//		/*********************************\
//		\*********************************/
//
//		try
//		{
//			cout << "plain text: " << plain << endl;
//
//			CBC_Mode< AES >::Encryption e;
//			e.SetKeyWithIV(key, sizeof(key), iv);
//
//			// The StreamTransformationFilter removes
//			//  padding as required.
//			StringSource s(plain, true,
//						   new StreamTransformationFilter(e,
//						   new StringSink(cipher)
//						   ) // StreamTransformationFilter
//						   ); // StringSource
//
//#if 0
//			StreamTransformationFilter filter(e);
//			filter.Put((const byte*)plain.data(), plain.size());
//			filter.MessageEnd();
//
//			const size_t ret = filter.MaxRetrievable();
//			cipher.resize(ret);
//			filter.Get((byte*)cipher.data(), cipher.size());
//#endif
//		}
//		catch (const CryptoPP::Exception& e)
//		{
//			cerr << e.what() << endl;
//			exit(1);
//		}
//
//		/*********************************\
//		\*********************************/
//
//		// Pretty print
//		encoded.clear();
//		StringSource(cipher, true,
//					 new HexEncoder(
//					 new StringSink(encoded)
//					 ) // HexEncoder
//					 ); // StringSource
//		cout << "cipher text: " << encoded << endl;
//
//		/*********************************\
//		\*********************************/
//
//		try
//		{
//			CBC_Mode< AES >::Decryption d;
//			d.SetKeyWithIV(key, sizeof(key), iv);
//
//			// The StreamTransformationFilter removes
//			//  padding as required.
//			StringSource s(cipher, true,
//						   new StreamTransformationFilter(d,
//						   new StringSink(recovered)
//						   ) // StreamTransformationFilter
//						   ); // StringSource
//
//#if 0
//			StreamTransformationFilter filter(d);
//			filter.Put((const byte*)cipher.data(), cipher.size());
//			filter.MessageEnd();
//
//			const size_t ret = filter.MaxRetrievable();
//			recovered.resize(ret);
//			filter.Get((byte*)recovered.data(), recovered.size());
//#endif
//
//			cout << "recovered text: " << recovered << endl;
//		}
//		catch (const CryptoPP::Exception& e)
//		{
//			cerr << e.what() << endl;
//			exit(1);
//		}
//
//		/*********************************\
//		\*********************************/
//
//		return 0;
//	}
//
//
//}
