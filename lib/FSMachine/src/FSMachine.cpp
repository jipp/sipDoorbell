#include "FSMachine.hpp"

FSMachine::FSMachine()
{
    currentState = &idle;
}

FSMachine::~FSMachine()
{
}

Event FSMachine::loop(Event event)
{
    std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    for (int i = 0; i < sizeof(fsMatrix) / sizeof(FSMatrix); i++)
    {
        if (currentState == fsMatrix[i].currentState)
        {
            if (event == fsMatrix[i].checkEvent)
            {
                if (fsMatrix[i].nextState->guardAction(event))
                {
                    timeoutTimerStart = now;
                    resendTimerStart = now;
                    currentState->exitAction(event);
                    currentState = fsMatrix[i].nextState;
                    currentState->entryAction(event);

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
                currentState->exitAction(event);
                return Event::IDLE;
            }
            if (resendTimer + resendTimerStart < now)
            {
                resendTimerStart = now;
                currentState->timeAction(event);
                return Event::SEND;
            }
        }
    }

    return Event::IDLE;
}