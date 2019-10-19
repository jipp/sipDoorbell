#include "RegisterState.hpp"


RegisterState::RegisterState()
{
}

RegisterState::~RegisterState()
{
}

void RegisterState::entryAction(Event exitEvent, Protocol *protocol)
{
    if (exitEvent == Event::SEND)
        protocol->cSeqRegister++;
    generate(protocol);
}

void RegisterState::exitAction(Protocol *protocol)
{
}

bool RegisterState::guardAction(Event checkEvent, Protocol *protocol)
{
    switch (protocol->answer)
    {
    case StatusCode::not_defined:
    case StatusCode::UNAUTHORIZED:
        return true;
    case StatusCode::INTERNAL_SERVER_ERROR:
        return false;
    default:
        return false;
    };
}

void RegisterState::timeAction(Protocol *protocol)
{
    generate(protocol);
}

void RegisterState::generate(Protocol *protocol)
{
    std::stringstream buffer;
    std::string digest1, digest2, digest3;

    buffer << "REGISTER"
           << " sip:"
           << protocol->packet.remote.address
           << " SIP/2.0\r\n";
    buffer << "Via: SIP/2.0/UDP "
           << protocol->packet.local.address
           << ":"
           << protocol->packet.local.port
           << ";branch="
           << protocol->branch
           << ";rport\r\n";
    buffer << "Max-Forwards: 70\r\n";
    buffer << "From: " << protocol->username
           << " <sip:"
           << protocol->username
           << "@"
           << protocol->packet.remote.address
           << ">;tag="
           << protocol->local.tag
           << "\r\n";
    buffer << "To: " << protocol->username << " <sip:"
           << protocol->username
           << "@"
           << protocol->packet.remote.address;
    protocol->remote.tag.empty() ? buffer << ">\r\n" : buffer << ">;tag=" << protocol->remote.tag << "\r\n";
    buffer << "Call-ID: "
           << protocol->callID
           << "@"
           << protocol->packet.local.address
           << "\r\n";
    buffer << "CSeq: "
           << protocol->cSeqRegister
           << " "
           << "REGISTER"
           << "\r\n";
    buffer << "Contact: <sip:"
           << protocol->username
           << "@"
           << protocol->packet.local.address
           << ">\r\n";
    if (!protocol->nonce.empty())
    {
        digest1 = protocol->calcHash(protocol->username + ":" + protocol->realm + ":" + protocol->password);
        digest2 = protocol->calcHash("REGISTER:sip:" + protocol->packet.remote.address);
        digest3 = protocol->calcHash(digest1 + ":" + protocol->nonce + ":" + digest2);
        buffer << "Authorization: Digest username=\""
               << protocol->username
               << "\", realm=\""
               << protocol->realm
               << "\", nonce=\""
               << protocol->nonce
               << "\", opaque=\"\", uri=\"sip:"
               << protocol->packet.remote.address
               << "\", response=\""
               << digest3
               << "\"\r\n";
    }
    buffer << "Content-Length: 0\r\n\r\n";

    protocol->packet.payload = buffer.str();
}