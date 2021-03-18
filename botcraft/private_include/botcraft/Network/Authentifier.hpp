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
        bool AuthToken(const std::string& login, const std::string& password);

        // Take a launcher accounts file as input,
        // return true if authenticated successfully, false otherwise
        bool AuthToken(const std::string& launcher_accounts_path);

        // Join a server after encryption request arrived
        bool JoinServer(const std::string& server_id, const std::vector<unsigned char>& shared_secret, const std::vector<unsigned char>& public_key);

        const std::string& GetPlayerDisplayName() const;

    private:

        static const std::string auth_server_URL;
        static const std::string session_server_URL;

        std::string player_display_name;
        std::string access_token;
        std::string player_uuid;
    };
}