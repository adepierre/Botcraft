#ifdef USE_ENCRYPTION

#include "botcraft/Network/AESEncrypter.hpp"
#include "botcraft/Utilities/Logger.hpp"
#include <openssl/aes.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>

#include <random>
#include <chrono>

#if PROTOCOL_VERSION > 758
#include <openssl/pem.h>

#include <array>
#endif

namespace Botcraft
{
    AESEncrypter::AESEncrypter()
    {
        blocksize = 0;
        encryption_context = nullptr;
        decryption_context = nullptr;
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


#if PROTOCOL_VERSION < 759
    void AESEncrypter::Init(const std::vector<unsigned char>& pub_key, const std::vector<unsigned char>& input_nonce,
        std::vector<unsigned char>& raw_shared_secret, std::vector<unsigned char>& encrypted_nonce, std::vector<unsigned char>& encrypted_shared_secret)
#elif PROTOCOL_VERSION < 761
    void AESEncrypter::Init(const std::vector<unsigned char>& pub_key, const std::vector<unsigned char>& input_nonce, const std::string& private_key,
        std::vector<unsigned char>& raw_shared_secret, std::vector<unsigned char>& encrypted_shared_secret,
        long long int& salt, std::vector<unsigned char>& salted_nonce_signature)
#else
    void AESEncrypter::Init(const std::vector<unsigned char>& pub_key, const std::vector<unsigned char>& input_challenge,
        std::vector<unsigned char>& raw_shared_secret, std::vector<unsigned char>& encrypted_shared_secret,
        std::vector<unsigned char>& encrypted_challenge)
#endif
    {
        const unsigned char* pub_key_ptr = pub_key.data();

        RSA* rsa = d2i_RSA_PUBKEY(nullptr, &pub_key_ptr, static_cast<long>(pub_key.size()));

        std::mt19937 random_gen(static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()));
        std::uniform_int_distribution<unsigned int> random_dist(0, 255);

        raw_shared_secret = std::vector<unsigned char>(AES_BLOCK_SIZE);

        for (int i = 0; i < AES_BLOCK_SIZE; ++i)
        {
            raw_shared_secret[i] = random_dist(random_gen);
        }

        int rsa_size = RSA_size(rsa);

        encrypted_shared_secret = std::vector<unsigned char>(rsa_size);
        RSA_public_encrypt(AES_BLOCK_SIZE, raw_shared_secret.data(), encrypted_shared_secret.data(), rsa, RSA_PKCS1_PADDING);
#if PROTOCOL_VERSION < 759
        // Pre-1.19 behaviour, compute encrypted nonce
        encrypted_nonce = std::vector<unsigned char>(rsa_size);
        RSA_public_encrypt(input_nonce.size(), input_nonce.data(), encrypted_nonce.data(), rsa, RSA_PKCS1_PADDING);
#elif PROTOCOL_VERSION < 761
        // 1.19, 1.19.1 and 1.19.2 behaviour, signature of salted nonce
        // Generate random salt
        salt = std::uniform_int_distribution<long long int>(std::numeric_limits<long long int>::min(), std::numeric_limits<long long int>::max())(random_gen);
        std::array<unsigned char, 8> salt_bytes;
        for (int i = 0; i < 8; ++i)
        {
            salt_bytes[i] = static_cast<unsigned char>((salt >> (8 * (7 - i))) & 0xFF);
        }
        // Compute salted nonce hash
        std::array<unsigned char, SHA256_DIGEST_LENGTH> salted_hash;
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, input_nonce.data(), input_nonce.size());
        SHA256_Update(&sha256, salt_bytes.data(), salt_bytes.size());
        SHA256_Final(salted_hash.data(), &sha256);

        // Extract signature key from PEM string
        RSA* rsa_signature = nullptr;
        const char* c_string = private_key.c_str();
        BIO* keybio = BIO_new_mem_buf((void*)c_string, -1);
        rsa_signature = PEM_read_bio_RSAPrivateKey(keybio, &rsa_signature, NULL, NULL);
        BIO_free(keybio);

        // Compute signature
        const int rsa_signature_size = RSA_size(rsa_signature);
        salted_nonce_signature = std::vector<unsigned char>(rsa_signature_size);
        unsigned int salted_nonce_signature_size;
        RSA_sign(NID_sha256, salted_hash.data(), salted_hash.size(), salted_nonce_signature.data(), &salted_nonce_signature_size, rsa_signature);
        RSA_free(rsa_signature);
        salted_nonce_signature.resize(salted_nonce_signature_size);
#else
        // 1.19.3 behaviour, back to compute encrypted challenge
        encrypted_challenge = std::vector<unsigned char>(rsa_size);
        RSA_public_encrypt(static_cast<int>(input_challenge.size()), input_challenge.data(), encrypted_challenge.data(), rsa, RSA_PKCS1_PADDING);
#endif
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
            LOG_WARNING("Warning, trying to encrypt packet while encryption is not initialized yet");
            return in;
        }

        std::vector<unsigned char> output;
        int size = 0;

        output.resize(in.size() + blocksize);
        EVP_EncryptUpdate(encryption_context, output.data(), &size, in.data(), static_cast<int>(in.size()));
        output.resize(size);

        return output;
    }

    std::vector<unsigned char> AESEncrypter::Decrypt(const std::vector<unsigned char>& in)
    {
        if (decryption_context == nullptr)
        {
            LOG_WARNING("Warning, trying to decrypt packet while decryption is not initialized yet");
            return in;
        }

        std::vector<unsigned char> output;
        int size = 0;

        output.resize(in.size() + blocksize);
        EVP_DecryptUpdate(decryption_context, output.data(), &size, in.data(), static_cast<int>(in.size()));
        output.resize(size);

        return output;
    }
}
#endif // USE_ENCRYPTION
