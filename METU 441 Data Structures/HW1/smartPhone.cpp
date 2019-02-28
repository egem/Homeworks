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
#include "smartPhone.h"
#include "ElectronicProduct.h"

smartPhone::smartPhone(ENUM_PRODUCT_TYPE productType)
:ElectronicProduct(productType)
{
	InitRelevantProperties();
	m_deviceBenefit = ((int)m_has4g + (int)m_hasBluetooth + (int)m_hasFrontCamera) 
						* m_deviceCPU * m_deviceMemory * m_deviceRam * m_screenSize * m_batteryLife;

	m_priceOverPerformance = m_price / m_deviceBenefit;
}

smartPhone::smartPhone(ENUM_PRODUCT_TYPE productType, string productName)
:ElectronicProduct(productType, productName)
{

}

smartPhone::~smartPhone()
{

}

bool smartPhone::GetDeviceCPU(GHZ& deviceCPU) const
{
	deviceCPU = m_deviceCPU;
	return true;
}

bool smartPhone::SetDeviceCPU(GHZ deviceCPU)
{
	m_deviceCPU = deviceCPU;
	return true;
}

bool smartPhone::GetDeviceRam(GB& deviceRam) const
{
	deviceRam = m_deviceRam;
	return true;
}

bool smartPhone::SetDeviceRam(GB deviceRam)
{
	m_deviceRam = deviceRam;
	return true;
}

bool smartPhone::GetDeviceMemory(GB& deviceMemory) const
{
	deviceMemory = m_deviceMemory;
	return true;
}

bool smartPhone::SetDeviceMemory(GB deviceMemory)
{
	m_deviceMemory = deviceMemory;
	return true;
}

bool smartPhone::GetScreenSize(INCHES& screenSize) const
{
	screenSize = m_screenSize;
	return true;
}

bool smartPhone::SetScreenSize(INCHES screenSize)
{
	m_screenSize = screenSize;
	return true;
}

bool smartPhone::GetBatteryLife(HOURS& batteryLife) const
{
	batteryLife = m_batteryLife;
	return true;
}

bool smartPhone::SetBatteryLife(HOURS batteryLife)
{
	m_batteryLife = batteryLife;
	return true;
}

bool smartPhone::GetHas4G(bool& has4g) const
{
	has4g = m_has4g;
	return true;
}

bool smartPhone::SetHas4G(bool has4g)
{
	m_has4g = has4g;
	return true;
}

bool smartPhone::GetHasBluetooth(bool& hasBluetooth) const
{
	hasBluetooth = m_hasBluetooth;
	return true;
}

bool smartPhone::SetHasBluetooth(bool hasBluetooth)
{
	m_hasBluetooth = hasBluetooth;
	return true;
}

bool smartPhone::GetHasFrontCamera(bool& hasFrontCamera) const
{
	hasFrontCamera = m_hasFrontCamera;
	return true;
}

bool smartPhone::SetHasFrontCamera(bool hasFrontCamera)
{
	m_hasFrontCamera = hasFrontCamera;
	return true;
}

string smartPhone::FindRelevantProperties()
{
	string relevantProperties = "";

	string hasBluetooth = m_hasBluetooth == true ? "True" : "False";
	string has4g = m_has4g == true ? "True" : "False";
	string hasFrontCam = m_hasFrontCamera == true ? "True" : "False";

	/*Float to string conversion*/
	ostringstream oss_cpu;
	oss_cpu.precision(2);	
	oss_cpu << fixed << m_deviceCPU;

	ostringstream oss_screen;
	oss_screen.precision(2);	
	oss_screen << fixed << m_screenSize;

	ostringstream oss_battery;
	oss_battery.precision(2);	
	oss_battery << fixed << m_batteryLife;
	/*Float to string conversion*/

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
							"Mem      : " + oss_memory.str() + " GB" + "\n" +
							"Screen   : " + oss_screen.str() + " ''" + "\n" +
							"battLife : " + oss_battery.str() + " h " + "\n" + 
							"hasBT    : " + hasBluetooth + " \n" +
							"has4g    : " + has4g + " \n" + 
							"hasFrCam : " + hasFrontCam + " \n" +
							"Price    : " + oss_price.str() + " TL" + "\n";
	
	return relevantProperties;
}

void smartPhone::InitRelevantProperties()
{
	cout << "Enter Smart Phone Properties : " << endl;
	while(!GetInputFromUser(ENUM_PROPERTY_PRODUCTNAME));
	while(!GetInputFromUser(ENUM_PROPERTY_DEVICECPU));
	while(!GetInputFromUser(ENUM_PROPERTY_DEVICERAM));
	while(!GetInputFromUser(ENUM_PROPERTY_DEVICEMEMORY));
	while(!GetInputFromUser(ENUM_PROPERTY_SCREENSIZE));
	while(!GetInputFromUser(ENUM_PROPERTY_BATTERYLIFE));
	while(!GetInputFromUser(ENUM_PROPERTY_HASBLUETOOTH));
	while(!GetInputFromUser(ENUM_PROPERTY_HAS4G));
	while(!GetInputFromUser(ENUM_PROPERTY_HASFRONTCAMERA));
	while(!GetInputFromUser(ENUM_PROPERTY_PRICE));

}

bool smartPhone::GetInputFromUser(ENUM_PROPERTIES property)
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
		case ENUM_PROPERTY_SCREENSIZE:
		{
			float screenSize;
			cout << setw(MAX_QUESTION_WIDTH) << left << QUESTION_SCREEN_SIZE << "\t";
			cin >> input;
			stringstream s_str(input);
			s_str >> screenSize;
			if(screenSize > 0)
			{
				bRet = SetScreenSize(screenSize);
			}
			else
			{
				cout << "Please enter a positive number. Please try again. " << endl;
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
		case ENUM_PROPERTY_HAS4G:
		{
			cout << setw(MAX_QUESTION_WIDTH) << left << QUESTION_HAS4G(m_productName) << "\t";
			cin >> input;
			if(input == "1")
			{
				bRet = SetHas4G(true);
			}
			else if(input == "0")
			{
				bRet = SetHas4G(false);
			}
			else
			{
				cout <<"Please try again. " << endl;
				bRet = false;
			}
			
		}
		break;
		case ENUM_PROPERTY_HASFRONTCAMERA:
		{
			cout << setw(MAX_QUESTION_WIDTH) << left << QUESTION_HASFRONTCAM(m_productName) << "\t";
			cin >> input;
			if(input == "1")
			{
				bRet = SetHasFrontCamera(true);
			}
			else if(input == "0")
			{
				bRet = SetHasFrontCamera(false);
			}
			else
			{
				cout <<"Please try again. " << endl;
				bRet = false;
			}
			
		}
		break;
		case ENUM_PROPERTY_BATTERYLIFE:
		{
			float batteryLife;
			cout << setw(MAX_QUESTION_WIDTH) << left << QUESTION_BATTERY_LIFE << "\t";
			cin >> input;
			stringstream s_str(input);
			s_str >> batteryLife;
			if(batteryLife > 0)
			{
				bRet = SetBatteryLife(batteryLife);
			}
			else
			{
				cout << "Please enter a positive number. Please try again. " << endl;
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

bool smartPhone::CalculateBenefits()
{
	m_deviceBenefit = ((int)m_has4g + (int)m_hasBluetooth + (int)m_hasFrontCamera) 
						* m_deviceCPU * m_deviceMemory * m_deviceRam * m_screenSize * m_batteryLife;

	m_priceOverPerformance = m_price / m_deviceBenefit;

	return true;
}

