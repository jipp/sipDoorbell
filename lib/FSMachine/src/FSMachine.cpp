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
                if (fsMatrix[i].nextState->guardAction())
                {
                    timeoutTimerStart = now;
                    resendTimerStart = now;
                    currentState->exitAction();
                    currentState = fsMatrix[i].nextState;
                    currentState->entryAction();

                    return fsMatrix[i].exitEvent;
                }
            }
        }
    }

    return event;
}