#include "FSMachine.hpp"

FSMachine::FSMachine()
{
    currentState = &idle;
    protocol = Protocol();
}

FSMachine::~FSMachine()
{
}

Event FSMachine::loop(Event checkEvent, Packet *packet)
{
    std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    protocol.packet = *packet;

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

                    return fsMatrix[i].exitEvent;
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
                return Event::IDLE;
            }
            if (resendTimer + resendTimerStart < now)
            {
                resendTimerStart = now;
                currentState->timeAction(&protocol);
                return Event::SEND;
            }
        }
    }

    return Event::IDLE;
}