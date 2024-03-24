#pragma once

/* set QoS level
*  status
*  QOS_ECO - Eco Mode, E-Core perfered in Hybrid, save the performance to important workloads.
*  QOS_HIGH - High QoS, P-Core perfered in Hybrid, gain more performance for important workloads
*			  use free P-Core, free E-Core and busy logical core in sequence.
*  QOS_SYSTEM - restore to system control
*/

enum APPQOS
{
	QOS_SYSTEM = 0,
	QOS_HIGH = 1,
	QOS_ECO = 2,
};

void setProcessQoS(APPQOS qos);
void setThreadQoS(APPQOS qos);

/* Get the CPU toplogy
* physical/logical core number
* big/little core information
*/
void GetCpuInfo();