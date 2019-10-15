#include "Protocol.hpp"

Protocol::Protocol(void)
{
    cSeq = 0;
}

Protocol::~Protocol(void)
{
}

void Protocol::parse(void)
{
    tokenizePayload();
    answer = StatusCode(atoi(getToken("SIP/2.0", 1).c_str()));
    branch = getValue("Via:", "branch=", ";");
    remote.tag = getValue("To:", "tag=", "\r\n");
    remote.addr = getValue("To:", " ", ";");
    local.tag = getValue("From:", "tag=", "\r\n");
    local.addr = getValue("From:", " ", ";");
    realm = getValue("WWW-Authenticate:", "realm=\"", "\"");
    nonce = getValue("WWW-Authenticate:", "nonce=\"", "\"");
    callID = getValue("Call-ID:", " ", "@");
    cSeq = atoi(getToken("CSeq:", 1).c_str());
    flow = getToken("CSeq:", 2);
}

void Protocol::tokenizePayload(void)
{
    std::istringstream payload(packet.payload);
    std::string buffer;

    lines.clear();

    while (std::getline(payload, buffer))
        lines.push_back(buffer);
}

std::string Protocol::getToken(std::string linePattern, int n)
{
    int i = 0;
    std::vector<std::string> token;
    std::istringstream line;
    std::string buffer;

    for (i = 0; i < lines.size(); i++)
        if (lines[i].find(linePattern) != std::string::npos)
            break;

    if (lines[i].find(linePattern) == std::string::npos)
        return "";

    line = std::istringstream(lines[i]);

    while (std::getline(line, buffer, ' '))
        token.push_back(buffer);

    if (n > token.size())
        return "";

    return token[n];
}

std::string Protocol::getValue(std::string linePattern, std::string pattern, std::string delimiter)
{
    int i = 0;
    int start = 0;
    int end = 0;
    std::string buffer;

    for (i = 0; i < lines.size(); i++)
        if (lines[i].find(linePattern) != std::string::npos)
        {
            if (lines[i].find(pattern) != std::string::npos)
            {
                start = lines[i].find(pattern) + pattern.length();
                end = lines[i].find(delimiter, start);
                break;
            }
            else
                return "";
        }

    if (i >= lines.size())
        return "";

    buffer = lines[i].substr(start, end - start);

    return buffer.erase(buffer.find_last_not_of("\t\v\f\r\n ") + 1);
}