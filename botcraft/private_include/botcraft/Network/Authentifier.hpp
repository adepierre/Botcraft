#pragma once
#include <nlohmann/json.hpp>

#include <string>

namespace Botcraft
{
    struct WebRequestResponse
    {
        nlohmann::json response;
        unsigned int status_code;
        std::string status_message;
    };

    class Authentifier
    {
    public:
        Authentifier();
        ~Authentifier();

        /// @brief Authentication using a legacy Mojang account (login + password).
        /// @param login Valid Mojang login
        /// @param password Valid Mojang password
        /// @return True if successfully authenticated, false otherwise
        const bool AuthMojang(const std::string& login, const std::string& password);

        /// @brief Authentication using a Microsoft account.
        /// Cache credentials in msa_credentials_path 
        /// for future authentications.
        /// @return True if authenticated successfully, false otherwise
        const bool AuthMicrosoft();

        // Join a server after encryption request arrived
        const bool JoinServer(const std::string& server_id, const std::vector<unsigned char>& shared_secret, const std::vector<unsigned char>& public_key) const;

        const std::string& GetPlayerDisplayName() const;

    private:
#ifdef USE_ENCRYPTION
        
        /// @brief Check if there is a saved credentials file and
        /// if the token is still valid. Refresh it if not.
        /// If file doesn't exist, launch auth device flow
        /// @return The microsoft access token, empty if failed.
        const std::string GetMSAToken() const;

        /// @brief Try to authenticate with microsoft account using device flow.
        /// Save the credentials to cached file if success.
        /// @return The microsoft access token, empty if failed.
        const std::string MSAAuthDeviceFlow() const;

        /// @brief Try to get XBox Live token from Microsoft token.
        /// @param msa_token Microsoft access token
        /// @return XBL token, empty if failed.
        const std::string GetXBLToken(const std::string& msa_token) const;
                
        /// @brief Try to get XSTS token from XBL token.
        /// @param xbl_token XBL token
        /// @return Pair of {XSTS token, userhash}, empty if failed.
        const std::pair<std::string, std::string> GetXSTSToken(const std::string& xbl_token) const;

        /// @brief Try to get MC token from XSTS token and user hash.
        /// @param xsts_token XSTS Token
        /// @param user_hash User hash
        /// @return Minecraft token, empty if failed.
        const std::string GetMCToken(const std::string& xsts_token, const std::string& user_hash) const;

        /// @brief Try to get Minecraft profile from Minecraft token.
        /// @param mc_token Minecraft token
        /// @return Pair of {MC UUID, MC name}, empty if failed.
        const std::pair<std::string, std::string> GetMCProfile(const std::string& mc_token) const;

        /// @brief Send a web request with ssl stuff
        /// @param host The host address
        /// @param raw_request The full request (header + content) as it should be sent
        /// @return A WebRequestResponse returned by the server
        const WebRequestResponse WebRequest(const std::string& host, const std::string& raw_request) const;

        /// @brief Send a POST request with ssl stuff
        /// @param host The host address (after https:// and before the first /)
        /// @param endpoint The endpoint (after the first /)
        /// @param content_type Data type
        /// @param accept Accept header value
        /// @param data Actual data to send
        /// @return A WebRequestResponse returned by the server
        const WebRequestResponse POSTRequest(const std::string& host, const std::string& endpoint,
            const std::string& content_type, const std::string& accept, const std::string& data) const;

        /// @brief Send a GET request with ssl stuff
        /// @param host The host address (after https:// and before the first /)
        /// @param endpoint The endpoint (after the first /)
        /// @param authorization Optional authorization header, only set if not empty
        /// @return A WebRequestResponse returned by the server
        const WebRequestResponse GETRequest(const std::string& host, const std::string& endpoint,
            const std::string& authorization = "") const;
#endif

    private:
        
        /// @brief Path to cache the microsoft token
        static const std::string msa_credentials_path;
                
        /// @brief Botcraft app ID for microsoft auth
        static const std::string botcraft_app_id;

        std::string player_display_name;
        std::string mc_access_token;
        std::string mc_player_uuid;
    };
}