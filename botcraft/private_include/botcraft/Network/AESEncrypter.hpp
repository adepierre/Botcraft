#pragma once

#ifdef USE_ENCRYPTION

#include <vector>
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include <string>
#endif

struct evp_cipher_ctx_st;
typedef struct evp_cipher_ctx_st EVP_CIPHER_CTX;
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
struct rsa_st;
typedef struct rsa_st RSA;
#endif

namespace Botcraft
{
    class AESEncrypter
    {
    public:
        AESEncrypter();
        ~AESEncrypter();
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        /// @brief Initialize the encryption context for this connection
        /// @param pub_key Server public key
        /// @param input_nonce Server input nonce
        /// @param raw_shared_secret Output shared secret
        /// @param encrypted_nonce Input nonce encrypted using server public key key
        /// @param encrypted_shared_secret Shared secret encrypted using server public key
        void Init(const std::vector<unsigned char>& pub_key, const std::vector<unsigned char>& input_nonce,
            std::vector<unsigned char>& raw_shared_secret, std::vector<unsigned char>& encrypted_nonce, std::vector<unsigned char>& encrypted_shared_secret);
#elif PROTOCOL_VERSION < 761 /* < 1.19.3 */
        /// @brief Initialize the encryption context for this connection
        /// @param pub_key Server public key
        /// @param input_nonce Server input nonce
        /// @param private_key Player private RSA certificate
        /// @param raw_shared_secret Output shared secret
        /// @param encrypted_shared_secret Shared secret encrypted using server public key
        /// @param salt Output random salt used to compute the signature
        /// @param salted_nonce_signature Output signature of the salted nonce
        void Init(const std::vector<unsigned char>& pub_key, const std::vector<unsigned char>& input_nonce, RSA* private_key,
            std::vector<unsigned char>& raw_shared_secret, std::vector<unsigned char>& encrypted_shared_secret,
            long long int& salt, std::vector<unsigned char>& salted_nonce_signature);
#else
        /// @brief Initialize the encryption context for this connection
        /// @param pub_key Server public key
        /// @param input_nonce Server input nonce
        /// @param raw_shared_secret Output shared secret
        /// @param encrypted_shared_secret Shared secret encrypted using server public key
        /// @param encrypted_challenge Output encrypted challenge
        void Init(const std::vector<unsigned char>& pub_key, const std::vector<unsigned char>& input_nonce,
            std::vector<unsigned char>& raw_shared_secret, std::vector<unsigned char>& encrypted_shared_secret,
            std::vector<unsigned char>& encrypted_challenge);
#endif
        std::vector<unsigned char> Encrypt(const std::vector<unsigned char>& in);
        std::vector<unsigned char> Decrypt(const std::vector<unsigned char>& in);

    private:
        EVP_CIPHER_CTX* encryption_context;
        EVP_CIPHER_CTX* decryption_context;
        unsigned int blocksize;
    };
}
#endif // USE_ENCRYPTION
