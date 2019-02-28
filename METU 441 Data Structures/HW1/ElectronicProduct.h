#ifndef __ELECTRONICPRODUCT_H__
#define __ELECTRONICPRODUCT_H__

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
#include <vector>

class ElectronicProduct
{
private:
	void TransProductType2String(ENUM_PRODUCT_TYPE productType);
	static ENUM_PRODUCT_TYPE TransString2ProductType(string productType);
protected:
	int m_productID;
	static int ms_globalProductID;
	string m_productName;
	string m_productType;
	LIRA m_price;	// Price is defined as integer instead of float.
	float m_deviceBenefit;
	float m_priceOverPerformance;

public:
	ElectronicProduct(ENUM_PRODUCT_TYPE productType);
	ElectronicProduct(ENUM_PRODUCT_TYPE productType, string productName);
	virtual ~ElectronicProduct();

	static ElectronicProduct* GetInstance(ENUM_PRODUCT_TYPE productType);
	static ElectronicProduct* GetInstance(string productName, string productType);

	virtual bool GetProductID(int& productID) const;
	virtual bool SetProductID(int productID);

	virtual bool GetProductName(string& productName) const;
	virtual bool SetProductName(string productName);
	
	virtual bool GetProductType(string& productType) const;
	virtual bool SetProductType(string productType);

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

	virtual bool GetHas4G(bool& has4g) const;
	virtual bool SetHas4G(bool has4g);

	virtual bool GetHasBluetooth(bool& hasBluetooth) const;
	virtual bool SetHasBluetooth(bool hasBluetooth);

	virtual bool GetHasWifi(bool& hasWifi) const;
	virtual bool SetHasWifi(bool hasWifi);

	virtual bool GetHasHdmi(bool& hasHdmi) const;
	virtual bool SetHasHdmi(bool hasHdmi);

	virtual bool GetHasUsb(bool& hasUsb) const;
	virtual bool SetHasUsb(bool hasUsb);

	virtual bool GetHasFrontCamera(bool& hasFrontCamera) const;
	virtual bool SetHasFrontCamera(bool hasFrontCamera);

	virtual bool GetOpticalDevice(string& opticalDevice) const;
	virtual bool SetOpticalDevice(ENUM_OPTICAL_DEVICE_TYPE opticalDevice);
	virtual bool SetOpticalDevice(string opticalDevice);

	virtual bool GetPrice(LIRA& price) const;
	virtual bool SetPrice(LIRA price);

	virtual bool GetDeviceBenefit(float& deviceBenefit) const;
	virtual bool SetDeviceBenefit(float deviceBenefit);

	virtual bool GetPriceOverPerformance(float& priceOverPerformance) const;
	virtual bool SetPriceOverPerformance(float priceOverPerformance);
		

	virtual string FindRelevantProperties() = 0;
	virtual bool CalculateBenefits() = 0;

	static bool IsProductTypeSame(ElectronicProduct* product1, ElectronicProduct* product2);

	static bool CompareElectronicProducts(ElectronicProduct* product1, ElectronicProduct* product2, ElectronicProduct* product3);

	static bool SetGlobalProductID(int productID);

};

#endif
