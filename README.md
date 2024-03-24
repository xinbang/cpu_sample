Sample Code for power and performance on Windows, especially on Intel hybrid architecture CPU.

1. setProcessQoS/setThreadQoS: QoS can influence core selection and processor power management
   Most of case it will be scheduled to E-Core when your applications is in background. it can improve the performance of the foreground workloads and improve the battery life.
   a. HighQoS - protect your perforamnce sensitive workload, Please restore to the normal priority on time.
     opt-in High QoS API
     your important workload
     opt-out High QoS API
   b. EcoQoS - no performance or latency requirement, like background animation.
