#ifndef CRYPTOPP_WRAPPER_H_
#define CRYPTOPP_WRAPPER_H_

#include <string>

namespace ThirdParty 
{
	void Encrypt(std::string& cipherText, 
				 std::string& key, 
				 std::string& iv, 
				 const std::string& plainText);
	void Decrypt(std::string& decipherText, 
				 const std::string& plainText, 
				 const std::string& key, 
				 const std::string& iv);


	class Aes
	{
	public:
		void Encrypt(std::string& cipherText, const std::string& plainText);
		void Decrypt(std::string& plainText, const std::string& cipherText);

		Aes();
		~Aes();
	private:

		Aes(const Aes& other);
		Aes& operator=(const Aes&) { return *this; }

		class Imp;
		Imp *mImp;
	};

	int TestExample();

}



#endif
