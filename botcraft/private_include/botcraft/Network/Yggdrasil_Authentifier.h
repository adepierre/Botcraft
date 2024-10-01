//
// Created by ws01 on 24-9-29.
//

#ifndef YGGDRASIL_AUTHENTIFIER_H
#define YGGDRASIL_AUTHENTIFIER_H

#include "Authentifier.hpp"

namespace Botcraft
{
    class Yggdrasil_Authentifier : public Authentifier
    {
    public:
        Yggdrasil_Authentifier(const std::string &url, const std::string &email, const std::string &password);
        ~Yggdrasil_Authentifier() = default;

        const bool AuthMicrosoft(const std::string &login) override;
        const bool JoinServer(const std::string &server_id, const std::vector<unsigned char> &shared_secret,
                              const std::vector<unsigned char> &public_key) const override;

    private:
        const WebRequestResponse WebRequest(const std::string &host, const std::string &raw_request) const override;
        void UpdateCached(const std::string &login, const ProtocolCraft::Json::Value &response);
        bool AuthenticateToken();
        bool RefreshToken();
        bool ValidateToken();

    private:
        std::string email;
        std::string password;
        std::string yggdrasil_rul;
        std::string yggdrasil_host;
        std::string yggdrasil_port;
    };
} // namespace Botcraft

#endif // YGGDRASIL_AUTHENTIFIER_H
