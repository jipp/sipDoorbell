#include "Protocol.hpp"

#include <iostream>

Protocol::Protocol()
{
    cSeq = 0;
    cSeqRegister = 0;
    cSeqInvite = 0;
    cSeqAck = 0;
#ifdef UNIT_TEST
    cSeqSimulate = 0;
    branch = "1234567890abcdef";
    callID = "234567890abcdef1";
    local.tag = "34567890abcdef12";
#else
    const int branchLength = 16;
    const int callIDLength = 10;
    const int tagLength = 16;
    branch = getRandomString(branchLength);
    callID = getRandomString(callIDLength);
    local.tag = getRandomString(tagLength);
#endif
    remote.tag.clear();
    answer = StatusCode::not_defined;
}

Protocol::~Protocol(void) = default;

void Protocol::parse()
{
    char *end;
    const int base = 10;
    tokenizePayload();
    answer = StatusCode(strtol(getToken("SIP/2.0", 1).c_str(), &end, base));
    branch = getValue("Via:", "branch=", ";");
    remote.tag = getValue("To:", "tag=", "\r\n");
    remote.addr = getValue("To:", " ", ";");
    local.tag = getValue("From:", "tag=", "\r\n");
    local.addr = getValue("From:", " ", ";");
    realm = getValue("WWW-Authenticate:", "realm=\"", "\"");
    nonce = getValue("WWW-Authenticate:", "nonce=\"", "\"");
    callID = getValue("Call-ID:", " ", "@");
    cSeq = strtol(getToken("CSeq:", 1).c_str(), &end, base);
    flow = getToken("CSeq:", 2);
}

void Protocol::tokenizePayload()
{
    std::istringstream payload(packet.payload);
    std::string buffer;

    lines.clear();

    while (std::getline(payload, buffer))
    {
        lines.push_back(buffer);
    }
}

std::string Protocol::getToken(std::string const &linePattern, int n)
{
    unsigned int i = 0;
    std::vector<std::string> token;
    std::istringstream line;
    std::string buffer;

    if (lines.empty())
    {
        return {};
    }

    for (i = 0; i < lines.size(); i++)
    {
        if (lines[i].find(linePattern) != std::string::npos)
        {
            break;
        }
    }

    if (lines[i].find(linePattern) == std::string::npos)
    {
        return {};
    }

    line = std::istringstream(lines[i]);

    while (std::getline(line, buffer, ' '))
    {
        token.push_back(buffer);
    }

    if (n > token.size())
    {
        return {};
    }

    return token[n];
}

std::string Protocol::getValue(std::string const &linePattern, std::string const &pattern, std::string const &delimiter)
{
    unsigned int i = 0;
    unsigned int start = 0;
    unsigned int end = 0;
    std::string buffer;

    for (i = 0; i < lines.size(); i++)
    {
        if (lines[i].find(linePattern) != std::string::npos)
        {
            if (lines[i].find(pattern) != std::string::npos)
            {
                start = lines[i].find(pattern) + pattern.length();
                end = lines[i].find(delimiter, start);
                break;
            }
            else
            {
                return {};
            }
        }
    }

    if (i >= lines.size())
    {
        return {};
    }

    buffer = lines[i].substr(start, end - start);

    return buffer.erase(buffer.find_last_not_of("\t\v\f\r\n ") + 1);
}

std::string Protocol::calcHash(const std::string &buffer)
{
#ifdef ESP32
    MD5Builder md5Builder = MD5Builder();
    const int digestLength = 33;
    char digest[digestLength];

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
    std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::random_device random_device;
    std::mt19937 random_engine(random_device());
    std::uniform_int_distribution<int> distribution(0, alphabet.size() - 1);
    std::string res;

    for (int i = 0; i < n; i++)
    {
        res += alphabet.at(distribution(random_engine));
    }

    return res;
}
