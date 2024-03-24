Sample Code for power and performance on Windows, especially on Intel hybrid architecture CPU.

1. setProcessQoS/setThreadQoS:

   QoS can influence core selection and processor power management
   Most of case it will be scheduled to E-Core when your applications is in background. it can improve the performance of the foreground workloads and improve the battery life.
   
   a. HighQoS - protect your perforamnce sensitive workload, Please restore to the normal priority on time.
   
        setProcessQoS(QOS_HIGH)
   
        performance senstive code
   
        setProcessQoS(QOS_SYSTEM)
   
   b. EcoQoS - no performance or latency requirement, like background animation. which can save power and improve the foregound performance.

2. GetCpuInfo

   Get the physical/logical core/Big core/Little Core Information.

   The information get from 155H:
   
   core 1 (P-Core) consist of logical processors: CPU 1, CPU 2,
   
   core 2 (E-Core) consist of logical processors: CPU 3,
   
   core 3 (E-Core) consist of logical processors: CPU 4,
   
   core 4 (E-Core) consist of logical processors: CPU 5,
   
   core 5 (E-Core) consist of logical processors: CPU 6,
   
   core 6 (E-Core) consist of logical processors: CPU 7,
   
   core 7 (E-Core) consist of logical processors: CPU 8,
   
   core 8 (E-Core) consist of logical processors: CPU 9,
   
   core 9 (E-Core) consist of logical processors: CPU 10,
   
   core 10 (P-Core) consist of logical processors: CPU 11, CPU 12,
   
   core 11 (P-Core) consist of logical processors: CPU 13, CPU 14,
   
   core 12 (P-Core) consist of logical processors: CPU 15, CPU 16,
   
   core 13 (P-Core) consist of logical processors: CPU 17, CPU 18,
   
   core 14 (P-Core) consist of logical processors: CPU 19, CPU 20,
   
   core 15 (E-Core) consist of logical processors: CPU 21,

   core 16 (E-Core) consist of logical processors: CPU 22,
   
   Total 16 core(s)
   
4. ongoing
