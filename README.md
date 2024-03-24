Sample Code for power and performance on Windows, especially on Intel hybrid architecture CPU.

1. setProcessQoS/setThreadQoS:

   QoS can influence core selection and processor power management
   Most of case it will be scheduled to E-Core when your applications is in background. it can improve the performance of the foreground workloads and improve the battery life.
   
   a. HighQoS - protect your perforamnce sensitive workload, Please restore to the normal priority on time.
   
        setProcessQoS(QOS_HIGH)
   
        performance senstive code
   
        setProcessQoS(QOS_SYSTEM)
   
   b. EcoQoS - no performance or latency requirement, like background animation. which can save power and improve the foregound performance.

3. on going
