#pragma once

#ifdef USE_ENCRYPTION

#include <vector>
#include <memory>

typedef struct evp_cipher_ctx_st EVP_CIPHER_CTX;

namespace Botcraft
{
    class AESEncrypter
    {
    public:
        AESEncrypter();
        ~AESEncrypter();
        void Init(const std::vector<unsigned char>& pub_key, const std::vector<unsigned char>& input_token,
            std::vector<unsigned char>& raw_shared_secret, std::vector<unsigned char>& encrypted_token, std::vector<unsigned char>& encrypted_shared_secret);
        std::vector<unsigned char> Encrypt(const std::vector<unsigned char>& in);
        std::vector<unsigned char> Decrypt(const std::vector<unsigned char>& in);

    private:
        EVP_CIPHER_CTX* encryption_context;
        EVP_CIPHER_CTX* decryption_context;
        unsigned int blocksize;
    };
}
#endif // USE_ENCRYPTION