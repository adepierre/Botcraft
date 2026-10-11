#ifdef USE_ENCRYPTION
#pragma once

#include "protocolCraft/Utilities/Json.hpp"

#include <string>
#include <vector>

namespace Botcraft
{
    struct WebRequestResponse
    {
        ProtocolCraft::Json::Value response;
        unsigned int status_code = 0;
        std::string status_message;
    };

    /// @brief Send a POST request with ssl stuff
    /// @param host The host address (after https:// and before the first /)
    /// @param endpoint The endpoint (after the first /)
    /// @param content_type Data type
    /// @param accept Accept header value
    /// @param data Actual data to send
    /// @param authorization Optional authorization header, only if not empty
    /// @return A WebRequestResponse returned by the server
    WebRequestResponse POSTRequest(
        const std::string& host, const std::string& endpoint,
        const std::string& content_type, const std::string& accept,
        const std::string& authorization, const std::string& data
    );

    /// @brief Send a GET request with ssl stuff
    /// @param host The host address (after https:// and before the first /)
    /// @param endpoint The endpoint (after the first /)
    /// @param authorization Optional authorization header, only set if not empty
    /// @return A WebRequestResponse returned by the server
    WebRequestResponse GETRequest(
        const std::string& host,
        const std::string& endpoint,
        const std::string& authorization = ""
    );

    /// @brief Check that a WebRequestResponse has the right fields and return code, throw if not
    /// @param response
    /// @param s String to display in the error message
    /// @param fields Expected fields to have in the response
    /// @param expected_status
    /// @return The response as json
    ProtocolCraft::Json::Value CheckJsonResponse(
        const WebRequestResponse& response,
        const std::string& s,
        const std::vector<std::string>& fields,
        const unsigned int expected_status = 200
    );

}
#endif // USE_ENCRYPTION
