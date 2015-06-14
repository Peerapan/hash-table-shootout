#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <cryptopp/base64.h>
#include <iostream>
#include <string>
#include <set>

int main()
{
	CryptoPP::SHA256 hash;
	std::set<std::string> s_map;
	
	for(int i=0;i<5000000;i+=1){
		byte digest[CryptoPP::SHA256::DIGESTSIZE];
		std::string username, password, src, output;
		src = std::to_string(i);
		hash.CalculateDigest(digest,(const byte *)src.c_str(),src.size());
		CryptoPP::HexEncoder encoder;
		CryptoPP::StringSink *SS = new CryptoPP::StringSink(output);
		encoder.Attach(SS);
		encoder.Put(digest,sizeof(digest));
		encoder.MessageEnd();
		std::cout << src << " -> " << output << std::endl;
		s_map.insert(src);
	}
	
	cout << s_map.size() << endl;
	return 0;
}