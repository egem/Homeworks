#ifndef __IOSTREAM_H__
#define __IOSTREAM_H__

#include <iostream>
#include <cstring>
#include <sstream>
#include <cmath>
#include <iomanip>

using namespace std;
#endif



#include "ElectronicProduct.h"
#include "ElectronicProduct_datatype.h"
#include "smartPhone.h"
#include "laptopComp.h"
#include "gameConsole.h"
#include "tv.h"
#include <vector>

int ElectronicProduct::ms_globalProductID = 1;

ElectronicProduct::ElectronicProduct(ENUM_PRODUCT_TYPE productType)
{
	m_productID = ms_globalProductID;
	ms_globalProductID++;
	TransProductType2String(productType);

	m_price = 0;
	m_deviceBenefit = 0;
	m_priceOverPerformance = 0;

}

ElectronicProduct::ElectronicProduct(ENUM_PRODUCT_TYPE productType, string productName)
{
	m_productName = productName;
	m_productID = ms_globalProductID;
	ms_globalProductID++;
	TransProductType2String(productType);

	m_price = 0;
	m_deviceBenefit = 0;
	m_priceOverPerformance = 0;
}


ElectronicProduct::~ElectronicProduct()
{
	
}


ElectronicProduct* ElectronicProduct::GetInstance(ENUM_PRODUCT_TYPE productType)
{
	//return new ElectronicProduct(productName, productType); 
	if(productType == ENUM_PRODUCT_TYPE_SMARTPHONE)
	{
		return dynamic_cast<ElectronicProduct*>(new smartPhone(productType));
	}
	else if(productType == ENUM_PRODUCT_TYPE_LAPTOPCOMP)
	{
		return dynamic_cast<ElectronicProduct*>(new laptopComp(productType));
	}
	else if(productType == ENUM_PRODUCT_TYPE_GAMECONSOLE)
	{
		return dynamic_cast<ElectronicProduct*>(new gameConsole(productType));
	}
	else if(productType == ENUM_PRODUCT_TYPE_TV)
	{
		return dynamic_cast<ElectronicProduct*>(new tv(productType));
	}
	
}

ElectronicProduct* ElectronicProduct::GetInstance(string productName, string productType)
{
	ENUM_PRODUCT_TYPE en_productType = TransString2ProductType(productType);

	if(en_productType == ENUM_PRODUCT_TYPE_SMARTPHONE)
	{
		return dynamic_cast<ElectronicProduct*>(new smartPhone(en_productType, productName));
	}
	else if(en_productType == ENUM_PRODUCT_TYPE_LAPTOPCOMP)
	{
		return dynamic_cast<ElectronicProduct*>(new laptopComp(en_productType, productName));
	}
	else if(en_productType == ENUM_PRODUCT_TYPE_GAMECONSOLE)
	{
		return dynamic_cast<ElectronicProduct*>(new gameConsole(en_productType, productName));
	}
	else if(en_productType == ENUM_PRODUCT_TYPE_TV)
	{
		return dynamic_cast<ElectronicProduct*>(new tv(en_productType, productName));
	}
	else
	{
		return NULL;
	}
	
}


void ElectronicProduct::TransProductType2String(ENUM_PRODUCT_TYPE productType)
{
	switch(productType)
	{
		case ENUM_PRODUCT_TYPE_SMARTPHONE:
		{
			m_productType = "Smartphone";
		}
		break;
		case ENUM_PRODUCT_TYPE_LAPTOPCOMP:
		{
			m_productType = "LaptopComputer";
		}
		break;
		case ENUM_PRODUCT_TYPE_GAMECONSOLE:
		{
			m_productType = "GameConsole";
		}
		break;
		case ENUM_PRODUCT_TYPE_TV:
		{
			m_productType = "TV";
		}
		break;
		default:
			break;
	}
}

ENUM_PRODUCT_TYPE ElectronicProduct::TransString2ProductType(string productType)
{
	if(productType == "Smartphone")
	{
		return ENUM_PRODUCT_TYPE_SMARTPHONE;
	}
	else if(productType == "LaptopComputer")
	{
		return ENUM_PRODUCT_TYPE_LAPTOPCOMP;
	}
	else if(productType == "GameConsole")
	{
		return ENUM_PRODUCT_TYPE_GAMECONSOLE;
	}
	else if(productType == "TV")
	{
		return ENUM_PRODUCT_TYPE_TV;
	}
	else
	{
		return ENUM_PRDUCT_TYPE_NONE;
	}
}

bool ElectronicProduct::GetProductID(int& productID) const
{
	productID = m_productID;
	return true;
}

bool ElectronicProduct::SetProductID(int productID)
{
	m_productID = productID;
	return true;
}

bool ElectronicProduct::GetProductName(string& productName) const
{
	productName = m_productName;
	return true;
}

bool ElectronicProduct::SetProductName(string productName)
{
	m_productName = productName;
	return true;
}

bool ElectronicProduct::GetProductType(string& productType) const
{
	productType = m_productType;
	return true;
}

bool ElectronicProduct::SetProductType(string productType)
{
	m_productType = productType;
	return true;
}

bool ElectronicProduct::GetDeviceCPU(GHZ& deviceCPU) const
{
	//This function will be implemented for appropriate derived classes. 
	return false;
}

bool ElectronicProduct::SetDeviceCPU(GHZ deviceCPU)
{
	//This function will be implemented for appropriate derived classes.
	return false;
}

bool ElectronicProduct::GetDeviceRam(GB& deviceRam) const
{
	//This function will be implemented for appropriate derived classes.
	return false;
}

bool ElectronicProduct::SetDeviceRam(GB deviceRam)
{
	//This function will be implemented for appropriate derived classes.
	return false;
}

bool ElectronicProduct::GetDeviceMemory(GB& deviceMemory) const
{
	//This function will be implemented for appropriate derived classes.
	return false;
}

bool ElectronicProduct::SetDeviceMemory(GB deviceMemory)
{
	//This function will be implemented for appropriate derived classes.
	return false;
}

bool ElectronicProduct::GetScreenSize(INCHES& screenSize) const
{
	//This function will be implemented for appropriate derived classes.
	return false;
}

bool ElectronicProduct::SetScreenSize(INCHES screenSize)
{
	//This function will be implemented for appropriate derived classes.
	return false;
}

bool ElectronicProduct::GetBatteryLife(HOURS& batteryLife) const
{
	//This function will be implemented for appropriate derived classes.
	return false;
}

bool ElectronicProduct::SetBatteryLife(HOURS batteryLife)
{
	//This function will be implemented for appropriate derived classes.
	return false;
}

bool ElectronicProduct::GetHas4G(bool& has4g) const
{
	//This function will be implemented for appropriate derived classes.
	return false;
}

bool ElectronicProduct::SetHas4G(bool has4g)
{
	//This function will be implemented for appropriate derived classes.
	return false;
}

bool ElectronicProduct::GetHasBluetooth(bool& hasBluetooth) const
{
	//This function will be implemented for appropriate derived classes.
	return false;
}

bool ElectronicProduct::SetHasBluetooth(bool hasBluetooth)
{
	//This function will be implemented for appropriate derived classes.
	return false;
}

bool ElectronicProduct::GetHasWifi(bool& hasWifi) const
{
	//This function will be implemented for appropriate derived classes.
	return false;
}

bool ElectronicProduct::SetHasWifi(bool hasWifi)
{
	//This function will be implemented for appropriate derived classes.
	return false;
}

bool ElectronicProduct::GetHasHdmi(bool& hasHdmi) const
{
	return false;
}

bool ElectronicProduct::SetHasHdmi(bool hasHdmi)
{
	//This function will be implemented for appropriate derived classes.
	return false;
}

bool ElectronicProduct::GetHasUsb(bool& hasUsb) const
{
	//This function will be implemented for appropriate derived classes.
	return false;
}

bool ElectronicProduct::SetHasUsb(bool hasUsb)
{
	//This function will be implemented for appropriate derived classes.
	return false;
}

bool ElectronicProduct::GetHasFrontCamera(bool& hasFrontCamera) const
{
	//This function will be implemented for appropriate derived classes.
	return false;
}

bool ElectronicProduct::SetHasFrontCamera(bool hasFrontCamera)
{
	//This function will be implemented for appropriate derived classes.
	return false;
}

bool ElectronicProduct::GetOpticalDevice(string& opticalDevice) const
{
	//This function will be implemented for appropriate derived classes.
	return false;
}

bool ElectronicProduct::SetOpticalDevice(ENUM_OPTICAL_DEVICE_TYPE opticalDevice)
{
	//This function will be implemented for appropriate derived classes.
	return false;
}

bool ElectronicProduct::SetOpticalDevice(string opticalDevice)
{
	//This function will be implemented for appropriate derived classes.
	return false;
}


bool ElectronicProduct::GetPrice(LIRA& price) const
{
	price = m_price;
	return true;
}

bool ElectronicProduct::SetPrice(LIRA price)
{
	m_price = price;
	return true;
}

bool ElectronicProduct::GetDeviceBenefit(float& deviceBenefit) const
{
	deviceBenefit = m_deviceBenefit;
	return true;
}

bool ElectronicProduct::SetDeviceBenefit(float deviceBenefit)
{
	m_deviceBenefit = deviceBenefit;
	return true;
}

bool ElectronicProduct::GetPriceOverPerformance(float& priceOverPerformance) const
{
	priceOverPerformance = m_priceOverPerformance;
	return true;
}

bool ElectronicProduct::SetPriceOverPerformance(float priceOverPerformance)
{
	m_priceOverPerformance = priceOverPerformance;
	return true;
}

bool ElectronicProduct::IsProductTypeSame(ElectronicProduct* product1, ElectronicProduct* product2)
{
	string productType1, productType2;
	product1->GetProductType(productType1);
	product2->GetProductType(productType2);
	if(productType1 == productType2)
		return true;
	else
		return false;
}

bool ElectronicProduct::CompareElectronicProducts(ElectronicProduct* product1, ElectronicProduct* product2, ElectronicProduct* product3)
{
	if(	(!ElectronicProduct::IsProductTypeSame(product1,product2)) 	
		|| (!ElectronicProduct::IsProductTypeSame(product1,product3)))
		return false;

	const int column_width = 20;
	const int column_number = 4;
	Product_Property product1_Property = {0};
	Product_Property product2_Property = {0};
	Product_Property product3_Property = {0};

	ostringstream oss1, oss2, oss3;
	oss1.precision(2);
	oss2.precision(2);
	oss3.precision(2);

	cout << setfill('-') << setw(column_width*column_number) << right << " " << endl;
	cout << setfill(' ') << setw(column_width*column_number) << right << " " << endl;
	
	if(product1->GetProductName(product1_Property.productName) && 
		product2->GetProductName(product2_Property.productName) && 
		product3->GetProductName(product3_Property.productName))
	{
		cout 	<< setw(column_width) << " " 
				<< setw(column_width) << left << product1_Property.productName
				<< setw(column_width) << left << product2_Property.productName
				<< setw(column_width) << left << product3_Property.productName << endl;
	}

	cout << setfill('-') << setw(column_width*column_number) << right << " " << endl;
	cout << setfill(' ') << setw(column_width*column_number) << right << " " << endl;

	if(product1->GetDeviceCPU(product1_Property.deviceCPU) &&
		product2->GetDeviceCPU(product2_Property.deviceCPU) &&
		product3->GetDeviceCPU(product3_Property.deviceCPU))
	{
		oss1 << fixed << product1_Property.deviceCPU;
		oss2 << fixed << product2_Property.deviceCPU;
		oss3 << fixed << product3_Property.deviceCPU;
		cout 	<< setw(column_width) << left << "CPU : " 
				<< setw(column_width) << left << oss1.str() + " GHz" 
				<< setw(column_width) << left << oss2.str() + " GHz"
				<< setw(column_width) << left << oss3.str() + " GHz" << endl;

		oss1.str("");	// erase the buffer
		oss1.clear();	// reset error flags
		oss2.str("");	// erase the buffer
		oss2.clear();	// reset error flags
		oss3.str("");	// erase the buffer
		oss3.clear();	// reset error flags
	}

	if(product1->GetDeviceRam(product1_Property.deviceRam) &&
		product2->GetDeviceRam(product2_Property.deviceRam) &&
		product3->GetDeviceRam(product3_Property.deviceRam))
	{
		oss1 << fixed << product1_Property.deviceRam;
		oss2 << fixed << product2_Property.deviceRam;
		oss3 << fixed << product3_Property.deviceRam;
		cout 	<< setw(column_width) << left << "RAM : " 
				<< setw(column_width) << left << oss1.str() + " GB" 
				<< setw(column_width) << left << oss2.str() + " GB"
				<< setw(column_width) << left << oss3.str() + " GB" << endl;

		oss1.str("");	// erase the buffer
		oss1.clear();	// reset error flags
		oss2.str("");	// erase the buffer
		oss2.clear();	// reset error flags
		oss3.str("");	// erase the buffer
		oss3.clear();	// reset error flags
	
	}

	if(product1->GetDeviceMemory(product1_Property.deviceMemory) &&
		product2->GetDeviceMemory(product2_Property.deviceMemory) &&
		product3->GetDeviceMemory(product3_Property.deviceMemory))
	{
		oss1 << fixed << product1_Property.deviceMemory;
		oss2 << fixed << product2_Property.deviceMemory;
		oss3 << fixed << product3_Property.deviceMemory;
		cout 	<< setw(column_width) << left << "MEMORY : " 
				<< setw(column_width) << left << oss1.str() + " GB" 
				<< setw(column_width) << left << oss2.str() + " GB"
				<< setw(column_width) << left << oss3.str() + " GB" << endl;

		oss1.str("");	// erase the buffer
		oss1.clear();	// reset error flags
		oss2.str("");	// erase the buffer
		oss2.clear();	// reset error flags
		oss3.str("");	// erase the buffer
		oss3.clear();	// reset error flags

	}

	if(product1->GetScreenSize(product1_Property.screenSize) &&
		product2->GetScreenSize(product2_Property.screenSize) &&
		product3->GetScreenSize(product3_Property.screenSize))
	{
		oss1 << fixed << product1_Property.screenSize;
		oss2 << fixed << product2_Property.screenSize;
		oss3 << fixed << product3_Property.screenSize;
		cout 	<< setw(column_width) << left << "SCREEN : " 
				<< setw(column_width) << left << oss1.str() + " ''" 
				<< setw(column_width) << left << oss2.str() + " ''"
				<< setw(column_width) << left << oss3.str() + " ''" << endl;

		oss1.str("");	// erase the buffer
		oss1.clear();	// reset error flags
		oss2.str("");	// erase the buffer
		oss2.clear();	// reset error flags
		oss3.str("");	// erase the buffer
		oss3.clear();	// reset error flags
		
	}

	if(product1->GetBatteryLife(product1_Property.batteryLife) &&
		product2->GetBatteryLife(product2_Property.batteryLife) &&
		product3->GetBatteryLife(product3_Property.batteryLife))
	{
		oss1 << fixed << product1_Property.batteryLife;
		oss2 << fixed << product2_Property.batteryLife;
		oss3 << fixed << product3_Property.batteryLife;
		cout 	<< setw(column_width) << left << "BATTERY LIFE : " 
				<< setw(column_width) << left << oss1.str() + " h" 
				<< setw(column_width) << left << oss2.str() + " h"
				<< setw(column_width) << left << oss3.str() + " h" << endl;

		oss1.str("");	// erase the buffer
		oss1.clear();	// reset error flags
		oss2.str("");	// erase the buffer
		oss2.clear();	// reset error flags
		oss3.str("");	// erase the buffer
		oss3.clear();	// reset error flags

	}

	if(product1->GetHas4G(product1_Property.has4g) &&
		product2->GetHas4G(product2_Property.has4g) &&
		product3->GetHas4G(product3_Property.has4g))
	{
		cout 	<< setw(column_width) << left << "4G : " 
				<< setw(column_width) << left << boolalpha << product1_Property.has4g
				<< setw(column_width) << left << boolalpha << product2_Property.has4g
				<< setw(column_width) << left << boolalpha << product3_Property.has4g << endl;
	}

	if(product1->GetHasBluetooth(product1_Property.hasBluetooth) &&
		product2->GetHasBluetooth(product2_Property.hasBluetooth) &&
		product3->GetHasBluetooth(product3_Property.hasBluetooth))
	{
		cout 	<< setw(column_width) << left << "BLUETOOTH : " 
				<< setw(column_width) << left << boolalpha << product1_Property.hasBluetooth
				<< setw(column_width) << left << boolalpha << product2_Property.hasBluetooth
				<< setw(column_width) << left << boolalpha << product3_Property.hasBluetooth << endl;
	}

	if(product1->GetHasWifi(product1_Property.hasWifi) &&
		product2->GetHasWifi(product2_Property.hasWifi) &&
		product3->GetHasWifi(product3_Property.hasWifi))
	{
		cout 	<< setw(column_width) << left << "WIFI : " 
				<< setw(column_width) << left << boolalpha << product1_Property.hasWifi
				<< setw(column_width) << left << boolalpha << product2_Property.hasWifi
				<< setw(column_width) << left << boolalpha << product3_Property.hasWifi << endl;
	}

	if(product1->GetHasHdmi(product1_Property.hasHdmi) &&
		product2->GetHasHdmi(product2_Property.hasHdmi) &&
		product3->GetHasHdmi(product3_Property.hasHdmi))
	{
		cout 	<< setw(column_width) << left << "HDMI : " 
				<< setw(column_width) << left << boolalpha << product1_Property.hasHdmi
				<< setw(column_width) << left << boolalpha << product2_Property.hasHdmi
				<< setw(column_width) << left << boolalpha << product3_Property.hasHdmi << endl;
	}

	if(product1->GetHasUsb(product1_Property.hasUsb) &&
		product2->GetHasUsb(product2_Property.hasUsb) &&
		product3->GetHasUsb(product3_Property.hasUsb))
	{
		cout 	<< setw(column_width) << left << "USB : " 
				<< setw(column_width) << left << boolalpha << product1_Property.hasUsb
				<< setw(column_width) << left << boolalpha << product2_Property.hasUsb
				<< setw(column_width) << left << boolalpha << product3_Property.hasUsb << endl;
	}

	if(product1->GetHasFrontCamera(product1_Property.hasFrontCamera) &&
		product2->GetHasFrontCamera(product2_Property.hasFrontCamera) &&
		product3->GetHasFrontCamera(product3_Property.hasFrontCamera))
	{
		cout 	<< setw(column_width) << left << "FRONT CAMERA : " 
				<< setw(column_width) << left << boolalpha << product1_Property.hasFrontCamera
				<< setw(column_width) << left << boolalpha << product2_Property.hasFrontCamera
				<< setw(column_width) << left << boolalpha << product3_Property.hasFrontCamera << endl;
	}

	if(product1->GetOpticalDevice(product1_Property.opticalDevice.deviceName) &&
		product2->GetOpticalDevice(product2_Property.opticalDevice.deviceName) &&
		product3->GetOpticalDevice(product3_Property.opticalDevice.deviceName))
	{
		cout 	<< setw(column_width) << left << "BATTERY LIFE : " 
				<< setw(column_width) << left << product1_Property.opticalDevice.deviceName
				<< setw(column_width) << left << product2_Property.opticalDevice.deviceName
				<< setw(column_width) << left << product3_Property.opticalDevice.deviceName << endl;
	}

	if(product1->GetPrice(product1_Property.price) &&
		product2->GetPrice(product2_Property.price) &&
		product3->GetPrice(product3_Property.price))
	{
		oss1 << fixed << product1_Property.price;
		oss2 << fixed << product2_Property.price;
		oss3 << fixed << product3_Property.price;
		cout 	<< setw(column_width) << left << "PRICE : " 
				<< setw(column_width) << left << oss1.str() + " TL" 
				<< setw(column_width) << left << oss2.str() + " TL"
				<< setw(column_width) << left << oss3.str() + " TL" << endl;

		oss1.str("");	// erase the buffer
		oss1.clear();	// reset error flags
		oss2.str("");	// erase the buffer
		oss2.clear();	// reset error flags
		oss3.str("");	// erase the buffer
		oss3.clear();	// reset error flags

	}

	cout << setfill('-') << setw(column_width*column_number) << right << " " << endl;
	cout << setfill(' ') << setw(column_width*column_number) << right << " " << endl;

	if(product1->GetDeviceBenefit(product1_Property.deviceBenefit) &&
		product2->GetDeviceBenefit(product2_Property.deviceBenefit) &&
		product3->GetDeviceBenefit(product3_Property.deviceBenefit))
	{
		oss1 << fixed << product1_Property.deviceBenefit;
		oss2 << fixed << product2_Property.deviceBenefit;
		oss3 << fixed << product3_Property.deviceBenefit;
		cout 	<< setw(column_width) << left << "BENEFIT : " 
				<< setw(column_width) << left << oss1.str()
				<< setw(column_width) << left << oss2.str()
				<< setw(column_width) << left << oss3.str() << endl;

		oss1.str("");	// erase the buffer
		oss1.clear();	// reset error flags
		oss2.str("");	// erase the buffer
		oss2.clear();	// reset error flags
		oss3.str("");	// erase the buffer
		oss3.clear();	// reset error flags

	}

	if(product1->GetPriceOverPerformance(product1_Property.priceOverPerformance) &&
		product2->GetPriceOverPerformance(product2_Property.priceOverPerformance) &&
		product3->GetPriceOverPerformance(product3_Property.priceOverPerformance))
	{
		oss1 << fixed << product1_Property.priceOverPerformance;
		oss2 << fixed << product2_Property.priceOverPerformance;
		oss3 << fixed << product3_Property.priceOverPerformance;
		cout 	<< setw(column_width) << left << "PRICE/PERFORMANCE : " 
				<< setw(column_width) << left << oss1.str()
				<< setw(column_width) << left << oss2.str()
				<< setw(column_width) << left << oss3.str() << endl;

		oss1.str("");	// erase the buffer
		oss1.clear();	// reset error flags
		oss2.str("");	// erase the buffer
		oss2.clear();	// reset error flags
		oss3.str("");	// erase the buffer
		oss3.clear();	// reset error flags

	}

	cout << setfill('-') << setw(column_width*column_number) << right << " " << endl;
	cout << setfill(' ') << setw(column_width*column_number) << right << " " << endl;

	float min_value = min(product1_Property.priceOverPerformance, min(product2_Property.priceOverPerformance,product3_Property.priceOverPerformance));

	if(min_value == product1_Property.priceOverPerformance)
		cout << "Best choice is " << product1_Property.productName << endl;
	else if(min_value == product2_Property.priceOverPerformance)
		cout << "Best choice is " << product2_Property.productName << endl;
	else if(min_value == product3_Property.priceOverPerformance)
		cout << "Best choice is " << product3_Property.productName << endl;

	cout << setfill('-') << setw(column_width*column_number) << right << " " << endl;
	cout << setfill(' ') << setw(column_width*column_number) << right << " " << endl;

	
	return true;
}

bool ElectronicProduct::SetGlobalProductID(int productID)
{
	ms_globalProductID = productID;
}



