#include <Windows.h>
#include <processthreadsapi.h>
#include <thread>
#include <iostream>
#include <vector>

#include "cpu_utility.h"

using namespace std;

void setThreadQoS(APPQOS qos)
{
    THREAD_POWER_THROTTLING_STATE PowerThrottling;
    ZeroMemory(&PowerThrottling, sizeof(PowerThrottling));
    PowerThrottling.Version = THREAD_POWER_THROTTLING_CURRENT_VERSION;

    if (qos == QOS_SYSTEM) {
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

    if (qos == QOS_SYSTEM) {
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

void GetCpuInfo()
{
    using LogicalProcessors = vector<int>;
    vector<LogicalProcessors> cores_;

    DWORD returnLength = 0;
    GetLogicalProcessorInformationEx(RelationProcessorCore, nullptr, &returnLength);
    auto last_error = GetLastError();
    if (last_error != ERROR_INSUFFICIENT_BUFFER) {
        cout << "Failed to calculate byte size for saving cpu info on windows" << endl;
        return;
    }

    std::unique_ptr<char[]> allocation = std::make_unique<char[]>(returnLength);
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX* processorInfos = reinterpret_cast<SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*>(allocation.get());

    if (!GetLogicalProcessorInformationEx(RelationProcessorCore, processorInfos, &returnLength)) {
        cout << "Failed to calculate byte size for saving cpu info on windows" << endl;
        return;
    }

    int core_id = 0;
    int global_processor_id = 0;
    const BYTE* iter = reinterpret_cast<const BYTE*>(processorInfos);
    const BYTE* end = iter + returnLength;

    while (iter < end) {
        auto processor_info = reinterpret_cast<const SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*>(iter);
        auto size = processor_info->Size;

        if (processor_info->Relationship == RelationProcessorCore &&
            processor_info->Processor.GroupCount == 1) {
            cout << "core " << core_id + 1;
            if (processor_info->Processor.EfficiencyClass == 0) {
                cout << " (E-Core)";
            }
            else {
                cout << " (P-Core)";
            }
            cout << " consist of logical processors: ";
            LogicalProcessors core_global_proc_ids;
            constexpr KAFFINITY bit = 1;
            constexpr int id_upper_bound = sizeof(KAFFINITY) * CHAR_BIT;
            const auto& group_mask = processor_info->Processor.GroupMask[0];
            for (int logical_proessor_id = 0; logical_proessor_id < id_upper_bound; ++logical_proessor_id) {
                if (group_mask.Mask & (bit << logical_proessor_id)) {
                    cout << "CPU " << global_processor_id + 1 << ", ";
                    core_global_proc_ids.push_back(global_processor_id);
                    global_processor_id++;
                }
            }
            cores_.push_back(std::move(core_global_proc_ids));
            core_id++;
            cout << endl;
        }
        iter += size;
    }
    cout << "Total " << cores_.size() << " core(s)" << endl;
}