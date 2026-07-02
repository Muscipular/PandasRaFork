// Copyright (c) Pandas Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#include "cryptopp.hpp"

#include "assistant.hpp"
#include "utf8.hpp"

#include <exception>

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include "../../3rdparty/cryptopp/base64.h"
#include "../../3rdparty/cryptopp/files.h"
#include "../../3rdparty/cryptopp/hex.h"
#include "../../3rdparty/cryptopp/md5.h"
#include "../../3rdparty/cryptopp/osrng.h"
#include "../../3rdparty/cryptopp/rsa.h"

using namespace CryptoPP;

static RandomPool& GlobalRNG() {
	static RandomPool randomPool;
	return randomPool;
}

std::string crypto_Base64Encode(std::string strplain) {
	try {
		std::string plainUtf8 = PandasUtf8::ansiToUtf8(strplain);

		Base64Encoder encoder(nullptr, false);
		AlgorithmParameters params = MakeParameters(Name::Pad(), true)(Name::InsertLineBreaks(), false);
		encoder.IsolatedInitialize(params);
		encoder.Put(reinterpret_cast<const byte*>(plainUtf8.c_str()), plainUtf8.length());
		encoder.MessageEnd();

		std::string encoded;
		size_t size = static_cast<size_t>(encoder.MaxRetrievable());
		if (size != 0) {
			encoded.resize(size);
			encoder.Get(reinterpret_cast<byte*>(&encoded[0]), encoded.size());
			return encoded;
		}
	}
	catch (const std::exception&) {
	}

	return "";
}

static std::string crypto_PemToOneline(std::string pemKey) {
	strReplace(pemKey, "-----BEGIN PUBLIC KEY-----", "");
	strReplace(pemKey, "-----END PUBLIC KEY-----", "");
	strReplace(pemKey, "-----BEGIN PRIVATE KEY-----", "");
	strReplace(pemKey, "-----END PRIVATE KEY-----", "");
	strReplace(pemKey, "\r\n", "");
	strReplace(pemKey, "\n", "");
	strReplace(pemKey, " ", "");
	return pemKey;
}

std::string crypto_RSAEncryptString(std::string pemPublicKey, std::string message) {
	try {
		if (pemPublicKey.empty()) {
			return "";
		}

		std::string plainUtf8 = PandasUtf8::ansiToUtf8(message);
		pemPublicKey = crypto_PemToOneline(pemPublicKey);

		StringSource strSource(pemPublicKey, true, new Base64Decoder);
		RSA::PublicKey publicKey;
		publicKey.Load(strSource);

		RSAES_OAEP_SHA_Encryptor pub(publicKey);
		std::string ciphertext;
		StringSource(plainUtf8, true, new PK_EncryptorFilter(
			GlobalRNG(), pub, new Base64Encoder(new StringSink(ciphertext), false)
		));
		return ciphertext;
	}
	catch (const std::exception&) {
		return "";
	}
}

std::string crypto_RSADecryptString(std::string pemPrivateKey, std::string ciphertext) {
	try {
		if (pemPrivateKey.empty()) {
			return "";
		}

		pemPrivateKey = crypto_PemToOneline(pemPrivateKey);
		StringSource strSource(pemPrivateKey, true, new Base64Decoder);
		RSA::PrivateKey privateKey;
		privateKey.Load(strSource);

		RSAES_OAEP_SHA_Decryptor priv(privateKey);
		std::string message;
		StringSource(ciphertext, true, new Base64Decoder(
			new PK_DecryptorFilter(GlobalRNG(), priv, new StringSink(message))
		));
		return PandasUtf8::utf8ToAnsi(message);
	}
	catch (const std::exception&) {
		return "";
	}
}

std::string crypto_GetFileMD5(const std::string& path) {
	try {
		Weak1::MD5 md5;
		const size_t buffsize = Weak1::MD5::DIGESTSIZE * 2;
		byte buff[buffsize] = { 0 };

		FileSource(path.c_str(), true,
			new HashFilter(md5,
				new HexEncoder(new ArraySink(buff, buffsize))
			)
		);

		return std::string(reinterpret_cast<const char*>(buff), buffsize);
	}
	catch (const std::exception&) {
		return "";
	}
}

std::string crypto_GetStringMD5(const std::string& content) {
	try {
		std::string digest;
		Weak::MD5 md5;

		StringSource(content, true,
			new HashFilter(md5,
				new HexEncoder(new StringSink(digest))
			)
		);

		return digest;
	}
	catch (const std::exception&) {
		return "";
	}
}
