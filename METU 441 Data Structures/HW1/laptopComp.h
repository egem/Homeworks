#ifndef __LAPTOPCOMP_H__
#define __LAPTOPCOMP_H__

#ifndef __IOSTREAM_H__
#define __IOSTREAM_H__

#include <iostream>
#include <cstring>
#include <sstream>
#include <cmath>
#include <iomanip>

using namespace std;
#endif



#include "ElectronicProduct_datatype.h"
#include "ElectronicProduct.h"

class laptopComp : public ElectronicProduct
{
	private:
		GHZ m_deviceCPU;
		GB m_deviceRam;
		GB m_deviceMemory;
		INCHES m_screenSize;
		HOURS m_batteryLife;
		
		bool m_hasBluetooth;
		bool m_hasHdmi;

		OPTICAL_DEVICE m_opticalDevice;

		void InitRelevantProperties();

		bool GetInputFromUser(ENUM_PROPERTIES property);

	protected:

	public:

		laptopComp(ENUM_PRODUCT_TYPE productType);
		laptopComp(ENUM_PRODUCT_TYPE productType, string productName);
		~laptopComp();
		
		virtual bool GetDeviceCPU(GHZ& deviceCPU) const;
		virtual bool SetDeviceCPU(GHZ deviceCPU);

		virtual bool GetDeviceRam(GB& deviceRam) const;
		virtual bool SetDeviceRam(GB deviceRam);

		virtual bool GetDeviceMemory(GB& deviceMemory) const;
		virtual bool SetDeviceMemory(GB deviceMemory);

		virtual bool GetScreenSize(INCHES& screenSize) const;
		virtual bool SetScreenSize(INCHES screenSize);

		virtual bool GetBatteryLife(HOURS& batteryLife) const;
		virtual bool SetBatteryLife(HOURS batteryLife);

		virtual bool GetHasBluetooth(bool& hasBluetooth) const;
		virtual bool SetHasBluetooth(bool hasBluetooth);

		virtual bool GetHasHdmi(bool& hasHdmi) const;
		virtual bool SetHasHdmi(bool hasHdmi);

		virtual bool GetOpticalDevice(string& opticalDevice) const;
		virtual bool SetOpticalDevice(ENUM_OPTICAL_DEVICE_TYPE opticalDevice);
		virtual bool SetOpticalDevice(string opticalDevice);
		
		virtual string FindRelevantProperties();
		virtual bool CalculateBenefits();
		

};

#endif 
