#include "Protocol.hpp"

Protocol::Protocol(void)
{
    cSeq = 0;
    cSeqRegister = 0;
    cSeqInvite = 0;
    cSeqAck = 0;
    local.tag = getRandomString(16);
    remote.tag.clear();
    branch = getRandomString(16);
    callID = getRandomString(10);
    answer = StatusCode::not_defined;
}

Protocol::~Protocol(void)
{
}

void Protocol::parse(void)
{
    if (!packet.payload.empty())
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

std::string Protocol::calcHash(const std::string &buffer)
{
#ifdef ESP32
    MD5Builder md5Builder;
    char digest[33];

    md5Builder.begin();
    md5Builder.add(buffer.c_str());
    md5Builder.calculate();
    md5Builder.getChars(digest);

    return std::string(digest);
#else
    return "md5hash";
#endif
}

std::string Protocol::getRandomString(int n)
{
    char alphabet[] = {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"};

    std::string res = "";
    for (int i = 0; i < n; i++)
        res = res + alphabet[std::rand() * (sizeof(alphabet) - 1ull) / RAND_MAX];

    return res;
}
