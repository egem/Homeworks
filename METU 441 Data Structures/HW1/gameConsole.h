#ifndef __GAMECONSOLE_H__
#define __GAMECONSOLE_H__

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

class gameConsole : public ElectronicProduct
{
	private:
		GHZ m_deviceCPU;
		GB m_deviceRam;
		GB m_deviceMemory;
		
		bool m_hasBluetooth;
		bool m_hasWifi;
		bool m_hasUsb;
		
		OPTICAL_DEVICE m_opticalDevice;

		void InitRelevantProperties();

		bool GetInputFromUser(ENUM_PROPERTIES property);

	protected:

	public:

		gameConsole(ENUM_PRODUCT_TYPE productType);
		gameConsole(ENUM_PRODUCT_TYPE productType, string productName);
		~gameConsole();	
	
		virtual bool GetDeviceCPU(GHZ& deviceCPU) const;
		virtual bool SetDeviceCPU(GHZ deviceCPU);

		virtual bool GetDeviceRam(GB& deviceRam) const;
		virtual bool SetDeviceRam(GB deviceRam);

		virtual bool GetDeviceMemory(GB& deviceMemory) const;
		virtual bool SetDeviceMemory(GB deviceMemory);

		virtual bool GetHasBluetooth(bool& hasBluetooth) const;
		virtual bool SetHasBluetooth(bool hasBluetooth);

		virtual bool GetHasWifi(bool& hasWifi) const;
		virtual bool SetHasWifi(bool hasWifi);

		virtual bool GetHasUsb(bool& hasUsb) const;
		virtual bool SetHasUsb(bool hasUsb);

		virtual bool GetOpticalDevice(string& opticalDevice) const;		//findBenefitOfOpticalDevice
		virtual bool SetOpticalDevice(ENUM_OPTICAL_DEVICE_TYPE opticalDevice);
		virtual bool SetOpticalDevice(string opticalDevice);
		
		virtual string FindRelevantProperties();
		virtual bool CalculateBenefits();
		

};

#endif
