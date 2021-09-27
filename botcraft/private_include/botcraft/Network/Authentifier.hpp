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

        /// <summary>
        /// Authentication using a legacy Mojang account (login + password).
        /// </summary>
        /// <param name="login">Valid Mojang login</param>
        /// <param name="password">Valid Mojang password</param>
        /// <returns>True if successfully authenticated, false otherwise</returns>
        const bool AuthMojang(const std::string& login, const std::string& password);

        /// <summary>
        /// Authentication using a Microsoft account.
        /// Cache credentials in msa_credentials_path 
        /// for future authentications.
        /// </summary>
        /// <returns>True if authenticated successfully, false otherwise</returns>
        const bool AuthMicrosoft();

        // Join a server after encryption request arrived
        const bool JoinServer(const std::string& server_id, const std::vector<unsigned char>& shared_secret, const std::vector<unsigned char>& public_key) const;

        const std::string& GetPlayerDisplayName() const;

    private:
#ifdef USE_ENCRYPTION
        /// <summary>
        /// Check if there is a saved credentials file and
        /// if the token is still valid. Refresh it if not.
        /// If file doesn't exist, launch auth device flow
        /// </summary>
        /// <returns>The microsoft access token, empty if failed.</returns>
        const std::string GetMSAToken() const;

        /// <summary>
        /// Try to authenticate with microsoft account using device flow.
        /// Save the credentials to cached file if success.
        /// </summary>
        /// <returns>The microsoft access token, empty if failed.</returns>
        const std::string MSAAuthDeviceFlow() const;

        /// <summary>
        /// Try to get XBox Live token from Microsoft token.
        /// </summary>
        /// <returns>XBL token, empty if failed.</returns>
        const std::string GetXBLToken(const std::string& msa_token) const;

        /// <summary>
        /// Try to get XSTS token from XBL token.
        /// </summary>
        /// <returns>Pair of {XSTS token, userhash}, empty if failed.</returns>
        const std::pair<std::string, std::string> GetXSTSToken(const std::string& xbl_token) const;

        /// <summary>
        /// Try to get MC token from XSTS token and user hash.
        /// </summary>
        /// <returns>MC token, empty if failed.</returns>
        const std::string GetMCToken(const std::string& xsts_token, const std::string& user_hash) const;

        /// <summary>
        /// Try to get MC profile from MC token.
        /// </summary>
        /// <returns>Pair of {MC UUID, MC name}, empty if failed.</returns>
        const std::pair<std::string, std::string> GetMCProfile(const std::string& mc_token) const;


        /// <summary>
        /// Send a web request with ssl stuff
        /// </summary>
        /// <param name="host">The host address</param>
        /// <param name="raw_request">The full request (header + content) as it should be sent</param>
        /// <returns>A WebRequestResponse</returns>
        const WebRequestResponse WebRequest(const std::string& host, const std::string& raw_request) const;

        /// <summary>
        /// Send POST request with ssl stuff
        /// </summary>
        /// <param name="host">The host address (after https:// and before the first /)</param>
        /// <param name="endpoint">The endpoint (after the first /)</param>
        /// <param name="content_type">Type of the data</param>
        /// <param name="accept">Accept header value</param>
        /// <param name="data">Actual data to send</param>
        /// <returns>A WebRequestResponse</returns>
        const WebRequestResponse POSTRequest(const std::string& host, const std::string& endpoint,
            const std::string& content_type, const std::string& accept, const std::string& data) const;

        /// <summary>
        /// Send GET request with ssl stuff
        /// </summary>
        /// <param name="host">The host address (after https:// and before the first /)</param>
        /// <param name="endpoint">The endpoint (after the first /)</param>
        /// <param name="authorization">Optional authorization header, only set if not empty</param>
        /// <returns>A WebRequestResponse</returns>
        const WebRequestResponse GETRequest(const std::string& host, const std::string& endpoint,
            const std::string& authorization = "") const;
#endif

    private:

        /// <summary>
        /// Path to cache the microsoft token
        /// </summary>
        static const std::string msa_credentials_path;
        /// <summary>
        /// Botcraft app ID for microsoft auth
        /// </summary>
        static const std::string botcraft_app_id;

        std::string player_display_name;
        std::string mc_access_token;
        std::string mc_player_uuid;
    };
}