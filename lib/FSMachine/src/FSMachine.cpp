#include "FSMachine.hpp"

FSMachine::FSMachine() : protocol(Protocol())
{
    currentState = &idle;
}

FSMachine::FSMachine(std::string const &username, std::string const &password) : protocol(Protocol())
{
    currentState = &idle;
    protocol.username = username;
    protocol.password = password;
}

FSMachine::~FSMachine() = default;

Event FSMachine::loop(Event checkEvent, Packet *packet)
{
    std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    protocol.packet = *packet;

    if (checkEvent == Event::RECEIVED)
    {
        protocol.parse();
    }

    for (FSMatrix &element : fsMatrix)
    {
        if (currentState == element.currentState)
        {
            if (checkEvent == element.checkEvent)
            {
                if (!element.nextState->guardAction(checkEvent, &protocol))
                {
                    currentState->exitAction(&protocol);
                    currentState = &idle;
                    currentState->entryAction(element.exitEvent, &protocol);
                }
                else
                {
                    timeoutTimerStart = now;
                    resendTimerStart = now;
                    currentState->exitAction(&protocol);
                    currentState = element.nextState;
                    currentState->entryAction(element.exitEvent, &protocol);

                    *packet = protocol.packet;

                    return element.exitEvent;
                }
            }
        }
    }

    for (FSMatrixTimer &element : fsMatrixTimer)
    {
        if (currentState == element.currentState)
        {
            if (timeoutTimer + timeoutTimerStart < now)
            {
                currentState->exitAction(&protocol);

                *packet = protocol.packet;

                return Event::IDLE;
            }
            if (resendTimer + resendTimerStart < now)
            {
                resendTimerStart = now;
                currentState->timeAction(&protocol);

                *packet = protocol.packet;

                return Event::SEND;
            }
        }
    }

    return Event::IDLE;
}