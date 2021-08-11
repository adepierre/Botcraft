#pragma once

#include <string>

namespace Botcraft
{
    class Authentifier
    {
    public:
        Authentifier();
        ~Authentifier();

        // Take login and password as input,
        // return true if authenticated successfully, false otherwise
        bool AuthMojang(const std::string& login, const std::string& password);

        /// <summary>
        /// Check if there is a saved credentials file, if not
        /// start the whole Microsoft auth flow
        /// </summary>
        /// <returns>true if authenticated successfully, false otherwise</returns>
        bool AuthMicrosoft();

        // Join a server after encryption request arrived
        bool JoinServer(const std::string& server_id, const std::vector<unsigned char>& shared_secret, const std::vector<unsigned char>& public_key);

        const std::string& GetPlayerDisplayName() const;

    private:
        const std::string SendPostRequest(const std::string& host, const std::string& endpoint, const std::string& data,
            unsigned int& status_code, std::string& status_message);

        bool AuthFromCacheFile();

    private:

        static const std::string mojang_auth_server_URL;
        static const std::string mojang_session_server_URL;
        static const std::string msa_credentials_path;

        std::string player_display_name;
        std::string access_token;
        std::string player_uuid;
    };
}