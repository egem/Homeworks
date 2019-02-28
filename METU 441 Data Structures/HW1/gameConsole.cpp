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
#include "gameConsole.h"
#include "ElectronicProduct.h"

gameConsole::gameConsole(ENUM_PRODUCT_TYPE productType)
:ElectronicProduct(productType)
{
	InitRelevantProperties();
	m_deviceBenefit = ((int)m_hasBluetooth + (int)m_hasUsb + (int)m_hasWifi + (int)m_opticalDevice.deviceType) 
						* m_deviceCPU * m_deviceMemory * m_deviceRam;

	m_priceOverPerformance = m_price / m_deviceBenefit;
}

gameConsole::gameConsole(ENUM_PRODUCT_TYPE productType, string productName)
:ElectronicProduct(productType, productName)
{

}

gameConsole::~gameConsole()
{

}

bool gameConsole::GetDeviceCPU(GHZ& deviceCPU) const
{
	deviceCPU = m_deviceCPU;
	return true;
}

bool gameConsole::SetDeviceCPU(GHZ deviceCPU)
{
	m_deviceCPU = deviceCPU;
	return true;
}

bool gameConsole::GetDeviceRam(GB& deviceRam) const
{
	deviceRam = m_deviceRam;
	return true;
}

bool gameConsole::SetDeviceRam(GB deviceRam)
{
	m_deviceRam = deviceRam;
	return true;
}

bool gameConsole::GetDeviceMemory(GB& deviceMemory) const
{
	deviceMemory = m_deviceMemory;
	return true;
}

bool gameConsole::SetDeviceMemory(GB deviceMemory)
{
	m_deviceMemory = deviceMemory;
	return true;
}

bool gameConsole::GetHasBluetooth(bool& hasBluetooth) const
{
	hasBluetooth = m_hasBluetooth;
	return true;
}

bool gameConsole::SetHasBluetooth(bool hasBluetooth)
{
	m_hasBluetooth = hasBluetooth;
	return true;
}

bool gameConsole::GetHasWifi(bool& hasWifi) const
{
	hasWifi = m_hasWifi;
	return true;
}

bool gameConsole::SetHasWifi(bool hasWifi)
{
	m_hasWifi = hasWifi;
	return true;
}

bool gameConsole::GetHasUsb(bool& hasUsb) const
{
	hasUsb = m_hasUsb;
	return true;
}

bool gameConsole::SetHasUsb(bool hasUsb)
{
	m_hasUsb = hasUsb;
	return true;
}

bool gameConsole::GetOpticalDevice(string& opticalDevice) const
{
	opticalDevice = m_opticalDevice.deviceName;
	return true;
}

bool gameConsole::SetOpticalDevice(ENUM_OPTICAL_DEVICE_TYPE opticalDevice)
{
	m_opticalDevice.deviceType = opticalDevice;
	switch(opticalDevice)
	{
		case ENUM_OPTICAL_DEVICE_CD:
		{
			m_opticalDevice.deviceName = "CD";
			break;
		}
		case ENUM_OPTICAL_DEVICE_DVD:
		{
			m_opticalDevice.deviceName = "DVD";
			break;
		}
		case ENUM_OPTICAL_DEVICE_BLURAY:
		{
			m_opticalDevice.deviceName = "BLURAY";
			break;
		}
		default:
			return false;
	}
	
	return true;
}

bool gameConsole::SetOpticalDevice(string opticalDevice)
{
	m_opticalDevice.deviceName = opticalDevice;
	
	if(opticalDevice == "CD" || opticalDevice == "CD ")
		m_opticalDevice.deviceType = ENUM_OPTICAL_DEVICE_CD;
	else if(opticalDevice =="DVD" || opticalDevice == "DVD ")
		m_opticalDevice.deviceType = ENUM_OPTICAL_DEVICE_DVD;
	else if(opticalDevice == "BLURAY" || opticalDevice == "BLURAY ")
		m_opticalDevice.deviceType = ENUM_OPTICAL_DEVICE_BLURAY;
	else
		return false;

	return true;

}


string gameConsole::FindRelevantProperties()
{
	string relevantProperties = "";

	string hasBluetooth = m_hasBluetooth == true ? "true" : "false";
	string hasWifi = m_hasWifi == true ? "true" : "false";
	string hasUsb = m_hasUsb == true ? "true" : "false";

	/*Float to string conversion.*/
	ostringstream oss_cpu;
	oss_cpu.precision(2);	
	oss_cpu << fixed << m_deviceCPU;
	/*Float to string conversion.*/

	/*Int to string conversion*/
	ostringstream oss_ram;
	oss_ram.precision(2);	
	oss_ram << fixed << m_deviceRam;

	ostringstream oss_memory;
	oss_memory.precision(2);	
	oss_memory << fixed << m_deviceMemory;

	ostringstream oss_price;
	oss_price.precision(2);	
	oss_price << fixed << m_price;
	/*Int to string conversion*/
	
	relevantProperties = 	"Name     : " + m_productName + "\n" +
							"Type     : " + m_productType + "\n" +
							"CPU      : " + oss_cpu.str() + " GHz" + "\n" +
							"RAM      : " + oss_ram.str() + " GB " + "\n" +
							"Mem      : " + oss_memory.str() + " GB" + " \n" + 
							"hasBT    : " + hasBluetooth + " \n" +
							"hasWifi  : " + hasWifi + " \n" + 
							"hasUsb   : " + hasUsb + " \n" + 
							"opticDev : " + m_opticalDevice.deviceName+ " \n" +
							"Price    : " + oss_price.str() + " TL" + "\n";

	return relevantProperties;
}

void gameConsole::InitRelevantProperties()
{
	cout << "Enter Game Console Properties : " << endl;
	while(!GetInputFromUser(ENUM_PROPERTY_PRODUCTNAME));
	while(!GetInputFromUser(ENUM_PROPERTY_DEVICECPU));
	while(!GetInputFromUser(ENUM_PROPERTY_DEVICERAM));
	while(!GetInputFromUser(ENUM_PROPERTY_DEVICEMEMORY));
	while(!GetInputFromUser(ENUM_PROPERTY_HASBLUETOOTH));
	while(!GetInputFromUser(ENUM_PROPERTY_HASWIFI));
	while(!GetInputFromUser(ENUM_PROPERTY_HASUSB));
	while(!GetInputFromUser(ENUM_PROPERTY_OPTICALDEVICE));
	while(!GetInputFromUser(ENUM_PROPERTY_PRICE));
	
}

bool gameConsole::GetInputFromUser(ENUM_PROPERTIES property)
{	
	bool bRet = false;
	
	string input;	//All the inputs will be gotten as a string so that we can check whether the input is in suitable format.

	const int MAX_QUESTION_WIDTH = USER_CHOICE_WIDTH;
	
	switch(property)
	{
		case ENUM_PROPERTY_PRODUCTNAME:
		{
			cout << setw(MAX_QUESTION_WIDTH) << left << QUESTION_PRODUCT_NAME << "\t";
			cin >> input;
			if(input.length() >= 2)
			{
				bRet = SetProductName(input);
			}
			else
			{
				cout << "Please enter a name which has more than 2 characters. Please try again" << endl;
				bRet = false;
			}
		}
		break;
		case ENUM_PROPERTY_DEVICECPU:
		{		
			GHZ deviceCPU;
			cout << setw(MAX_QUESTION_WIDTH) << left << QUESTION_CPU_SPEED << "\t";
			cin >> input;
			stringstream s_str(input);
			s_str >> deviceCPU;
			if(deviceCPU > 0)
			{
				bRet = SetDeviceCPU(deviceCPU);
			}
			else
			{
				cout << "Please enter a positive number. Please try again." << endl;
				bRet = false; 
			}
		}
		break;
		case ENUM_PROPERTY_DEVICERAM:
		{
			float deviceRam;
			cout << setw(MAX_QUESTION_WIDTH) << left << QUESTION_RAM_SIZE << "\t";
			cin >> input;
			stringstream s_str(input);
			s_str >> deviceRam;
			if(deviceRam > 0)
			{
				if(deviceRam == static_cast<float>(static_cast<GB>(deviceRam)))
				{
					bRet = SetDeviceRam(static_cast<GB>(deviceRam)); 
				}
				else
				{
					cout << "Please enter an integer number. Please try again" << endl;
					bRet = false;
				}
			}
			else
			{
				cout << "Please enter a positive number. Please try again." << endl;
				bRet = false;
			}
		}
		break;
		case ENUM_PROPERTY_DEVICEMEMORY:
		{
			float deviceMemory;
			cout << setw(MAX_QUESTION_WIDTH) << left << QUESTION_MEMORY_SIZE << "\t";
			cin >> input;
			stringstream s_str(input);
			s_str >> deviceMemory;
			if(deviceMemory > 0)
			{
				if(deviceMemory == static_cast<float>(static_cast<GB>(deviceMemory)))
				{
					bRet = SetDeviceMemory(static_cast<GB>(deviceMemory)); 
				}
				else
				{
					cout << "Please enter an integer number. Please try again" << endl;
					bRet = false;
				}
			}
			else
			{
				cout << "Please enter a positive number. Please try again." << endl;
				bRet = false;
			}
			 
		}
		break;
		case ENUM_PROPERTY_HASBLUETOOTH:
		{
			cout << setw(MAX_QUESTION_WIDTH) << left << QUESTION_HASBLUETOOTH(m_productName) << "\t";
			cin >> input;
			if(input == "1")
			{
				bRet = SetHasBluetooth(true);
			}
			else if(input == "0")
			{
				bRet = SetHasBluetooth(false);
			}
			else
			{
				cout <<"Please try again. " << endl;
				bRet = false;
			}
			
		}
		break;
		case ENUM_PROPERTY_HASWIFI:
		{
			cout << setw(MAX_QUESTION_WIDTH) << left << QUESTION_HASWIFI(m_productName) << "\t";
			cin >> input;
			if(input == "1")
			{
				bRet = SetHasWifi(true);
			}
			else if(input == "0")
			{
				bRet = SetHasWifi(false);
			}
			else
			{
				cout <<"Please try again. " << endl;
				bRet = false;
			}
			
		}
		break;
		case ENUM_PROPERTY_HASUSB:
		{
			cout << setw(MAX_QUESTION_WIDTH) << left << QUESTION_HASUSB(m_productName) << "\t";
			cin >> input;
			if(input == "1")
			{
				bRet = SetHasUsb(true);
			}
			else if(input == "0")
			{
				bRet = SetHasUsb(false);
			}
			else
			{
				cout <<"Please try again. " << endl;
				bRet = false;
			}
			
		}
		break;
		case ENUM_PROPERTY_OPTICALDEVICE:
		{
			cout << setw(MAX_QUESTION_WIDTH) << left << QUESTION_OPTICALDEVICE(m_productName) << "\t";
			cin >> input;
			if(input == "1")
			{
				bRet = SetOpticalDevice(ENUM_OPTICAL_DEVICE_CD);
			}
			else if(input == "2")
			{
				bRet = SetOpticalDevice(ENUM_OPTICAL_DEVICE_DVD);
			}
			else if(input == "3")
			{
				bRet = SetOpticalDevice(ENUM_OPTICAL_DEVICE_BLURAY);
			}
			else
			{
				cout << "Please try again. " << endl;
				bRet = false;
			}
		}
		break;
		case ENUM_PROPERTY_PRICE:
		{
			float price;
			cout << setw(MAX_QUESTION_WIDTH) << left << QUESTION_PRICE << "\t";
			cin >> input;
			stringstream s_str(input);
			s_str >> price;
			if(price > 0)
			{
				if(price == static_cast<float>(static_cast<LIRA>(price)))
				{
					bRet = SetPrice(static_cast<LIRA>(price)); 
				}
				else
				{
					cout << "Please enter an integer number. Please try again" << endl;
					bRet = false;
				}
			}
			else
			{
				cout << "Please enter a positive number. Please try again. " << endl;
			}
			
		}
		break;
		default: 
		break;	


	}

	return bRet;

}

bool gameConsole::CalculateBenefits()
{
	m_deviceBenefit = ((int)m_hasBluetooth + (int)m_hasUsb + (int)m_hasWifi + (int)m_opticalDevice.deviceType) 
						* m_deviceCPU * m_deviceMemory * m_deviceRam;

	m_priceOverPerformance = m_price / m_deviceBenefit;

	return true;
}


