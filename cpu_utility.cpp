#include <Windows.h>
#include <processthreadsapi.h>
#include <thread> 

#include "cpu_utility.h"

void setThreadQoS(APPQOS qos)
{
    THREAD_POWER_THROTTLING_STATE PowerThrottling;
    ZeroMemory(&PowerThrottling, sizeof(PowerThrottling));
    PowerThrottling.Version = THREAD_POWER_THROTTLING_CURRENT_VERSION;

    if (qos == QOS_SYSTEM)
    {
        PowerThrottling.ControlMask = 0;
        PowerThrottling.StateMask = 0;
    }
    else {
        PowerThrottling.ControlMask = THREAD_POWER_THROTTLING_EXECUTION_SPEED;
        PowerThrottling.StateMask = qos == QOS_ECO ? THREAD_POWER_THROTTLING_EXECUTION_SPEED : 0;
    }

    SetThreadInformation(GetCurrentThread(),
        ThreadPowerThrottling,
        &PowerThrottling,
        sizeof(PowerThrottling));
}

void setProcessQoS(APPQOS qos)
{
    PROCESS_POWER_THROTTLING_STATE PowerThrottling;
    RtlZeroMemory(&PowerThrottling, sizeof(PowerThrottling));
    PowerThrottling.Version = PROCESS_POWER_THROTTLING_CURRENT_VERSION;

    if (qos == QOS_SYSTEM)
    {
        PowerThrottling.ControlMask = 0;
        PowerThrottling.StateMask = 0;
    }
    else {
        PowerThrottling.ControlMask = PROCESS_POWER_THROTTLING_EXECUTION_SPEED;
        PowerThrottling.StateMask = qos == QOS_ECO ? PROCESS_POWER_THROTTLING_EXECUTION_SPEED : 0;
    }

    //set the prority to low for the windows efficency mode
    SetPriorityClass(GetCurrentProcess(), qos == QOS_ECO ? IDLE_PRIORITY_CLASS : NORMAL_PRIORITY_CLASS);

    SetProcessInformation(GetCurrentProcess(),
        ProcessPowerThrottling,
        &PowerThrottling,
        sizeof(PowerThrottling));
}

