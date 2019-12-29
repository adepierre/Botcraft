#ifdef USE_ENCRYPTION

#include "botcraft/Network/AESEncrypter.hpp"
#include <openssl/aes.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>

#include <iostream>
#include <random>
#include <chrono>

namespace Botcraft
{
    AESEncrypter::AESEncrypter()
    {
    }

    AESEncrypter::~AESEncrypter()
    {
        if (encryption_context != nullptr)
        {
            EVP_CIPHER_CTX_free(encryption_context);
            encryption_context = nullptr;
        }

        if (decryption_context != nullptr)
        {
            EVP_CIPHER_CTX_free(decryption_context);
            decryption_context = nullptr;
        }
    }

    void AESEncrypter::Init(const std::vector<unsigned char>& pub_key, const std::vector<unsigned char>& input_token,
        std::vector<unsigned char>& raw_shared_secret, std::vector<unsigned char>& encrypted_token, std::vector<unsigned char>& encrypted_shared_secret)
    {
        const unsigned char* pub_key_ptr = pub_key.data();

        RSA* rsa = d2i_RSA_PUBKEY(nullptr, &pub_key_ptr, pub_key.size());

        std::mt19937 random_gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<unsigned int> random_dist(0, 255);

        raw_shared_secret = std::vector<unsigned char>(AES_BLOCK_SIZE);

        for (int i = 0; i < AES_BLOCK_SIZE; ++i)
        {
            raw_shared_secret[i] = random_dist(random_gen);
        }

        int rsa_size = RSA_size(rsa);

        encrypted_shared_secret = std::vector<unsigned char>(rsa_size);
        encrypted_token = std::vector<unsigned char>(rsa_size);

        RSA_public_encrypt(AES_BLOCK_SIZE, raw_shared_secret.data(), encrypted_shared_secret.data(), rsa, RSA_PKCS1_PADDING);
        RSA_public_encrypt(input_token.size(), input_token.data(), encrypted_token.data(), rsa, RSA_PKCS1_PADDING);

        RSA_free(rsa);

        encryption_context = EVP_CIPHER_CTX_new();
        EVP_EncryptInit_ex(encryption_context, EVP_aes_128_cfb8(), nullptr, raw_shared_secret.data(), raw_shared_secret.data());

        decryption_context = EVP_CIPHER_CTX_new();
        EVP_DecryptInit_ex(decryption_context, EVP_aes_128_cfb8(), nullptr, raw_shared_secret.data(), raw_shared_secret.data());

        blocksize = EVP_CIPHER_block_size(EVP_aes_128_cfb8());
    }

    std::vector<unsigned char> AESEncrypter::Encrypt(const std::vector<unsigned char>& in)
    {
        if (encryption_context == nullptr)
        {
            std::cerr << "Warning, trying to encrypt packet while encryption is not initialized yet" << std::endl;
            return in;
        }

        std::vector<unsigned char> output;
        int size = 0;

        output.resize(in.size() + blocksize);
        EVP_EncryptUpdate(encryption_context, output.data(), &size, in.data(), in.size());
        output.resize(size);

        return output;
    }

    std::vector<unsigned char> AESEncrypter::Decrypt(const std::vector<unsigned char>& in)
    {
        if (decryption_context == nullptr)
        {
            std::cerr << "Warning, trying to decrypt packet while decryption is not initialized yet" << std::endl;
            return in;
        }

        std::vector<unsigned char> output;
        int size = 0;

        output.resize(in.size() + blocksize);
        EVP_DecryptUpdate(decryption_context, output.data(), &size, in.data(), in.size());
        output.resize(size);

        return output;
    }
}
#endif // USE_ENCRYPTION