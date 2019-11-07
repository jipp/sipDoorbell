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

FSMachine::~FSMachine()
{
}

Event FSMachine::loop(Event checkEvent, Packet *packet)
{
    std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    protocol.packet = *packet;

    if (checkEvent == Event::RECEIVED)
        protocol.parse();

    for (int i = 0; i < sizeof(fsMatrix) / sizeof(FSMatrix); i++)
    {
        if (currentState == fsMatrix[i].currentState)
        {
            if (checkEvent == fsMatrix[i].checkEvent)
            {
                if (fsMatrix[i].nextState->guardAction(checkEvent, &protocol))
                {
                    timeoutTimerStart = now;
                    resendTimerStart = now;
                    currentState->exitAction(&protocol);
                    currentState = fsMatrix[i].nextState;
                    currentState->entryAction(fsMatrix[i].exitEvent, &protocol);

                    *packet = protocol.packet;

                    return fsMatrix[i].exitEvent;
                }
                else
                {
                    currentState->exitAction(&protocol);
                    currentState = &idle;
                    currentState->entryAction(fsMatrix[i].exitEvent, &protocol);
                }
            }
        }
    }

    for (int i = 0; i < sizeof(fsMatrixTimer) / sizeof(FSMatrixTimer); i++)
    {
        if (currentState == fsMatrixTimer[i].currentState)
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