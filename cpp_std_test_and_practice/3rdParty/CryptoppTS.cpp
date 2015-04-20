#include "CryptoppTS.h"

#include "CryptoppWrapper.h"

#include <cryptopp\hex.h>
#include <cryptopp\filters.h>

#include <iostream>

using namespace boost::unit_test_framework;

namespace
{
	void doTest()
	{
		std::string aPlainText = "This is Kaprisk test string.";
		std::cout << "plain text: " << aPlainText << std::endl;

		std::string aKey, aIv;

		// test encrypt
		std::string aCipher;
		ThirdParty::Encrypt(aCipher, aKey, aIv, aPlainText);
		std::cout << "cipher: " << aCipher << std::endl;

		// test decrypt
		std::string aDecipher;
		ThirdParty::Decrypt(aDecipher, aCipher, aKey, aIv);
		std::cout << "decipher: " << aDecipher << std::endl;
		

		//*************************************************************************************
		//ThirdParty::TestExample();
	}

	void testAes()
	{
		std::string aPlainText = "This is Kaprisk test string.";
		std::cout << "plain text: " << aPlainText << std::endl;

		ThirdParty::Aes aAes;
		
		std::string aCipherText;
		aAes.Encrypt(aCipherText, aPlainText);

		//use encoded
		std::string aEncodedCipherText;
		aEncodedCipherText.clear();
		CryptoPP::StringSource ssKey(aCipherText,
									 true,
									 new CryptoPP::HexEncoder(new CryptoPP::StringSink(aEncodedCipherText), true));
		std::cout << "cipher: " << aEncodedCipherText << std::endl;

		std::string aRecoveredText;
		aAes.Decrypt(aRecoveredText, aCipherText);

		std::cout << "recovered text: " << aRecoveredText << std::endl;

	}
}

namespace CPP_STD_TEST_AND_PRACTIVE_TS
{
	test_suite* CryptoppTS::suite()
	{
		test_suite* suite = BOOST_TEST_SUITE("CryptoppTS");
		//suite->add(BOOST_TEST_CASE(&doTest));
		suite->add(BOOST_TEST_CASE(&testAes));
		return suite;
	}
}