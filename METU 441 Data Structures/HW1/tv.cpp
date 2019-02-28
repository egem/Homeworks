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
#include "tv.h"
#include "ElectronicProduct.h"

tv::tv(ENUM_PRODUCT_TYPE productType)
:ElectronicProduct(productType)
{
	InitRelevantProperties();
	m_deviceBenefit = ((int)m_hasHdmi + (int)m_hasUsb + (int)m_hasWifi) * m_screenSize;

	m_priceOverPerformance = m_price / m_deviceBenefit;
}

tv::tv(ENUM_PRODUCT_TYPE productType, string productName)
:ElectronicProduct(productType, productName)
{

}

tv::~tv()
{

}

bool tv::GetScreenSize(INCHES& screenSize) const
{
	screenSize = m_screenSize;
	return true;
}

bool tv::SetScreenSize(INCHES screenSize)
{
	m_screenSize = screenSize;
	return true;
}

bool tv::GetHasWifi(bool& hasWifi) const
{
	hasWifi = m_hasWifi;
	return true;
}

bool tv::SetHasWifi(bool hasWifi)
{
	m_hasWifi = hasWifi;
	return true;
}

bool tv::GetHasHdmi(bool& hasHdmi) const
{
	hasHdmi = m_hasHdmi;
	return true;
}

bool tv::SetHasHdmi(bool hasHdmi)
{
	m_hasHdmi = hasHdmi;
	return true;
}

bool tv::GetHasUsb(bool& hasUsb) const
{
	hasUsb = m_hasUsb;
	return true;
}

bool tv::SetHasUsb(bool hasUsb)
{
	m_hasUsb = hasUsb;
	return true;
}

string tv::FindRelevantProperties()
{
	string relevantProperties = "";
	
	string hasWifi = m_hasWifi == true ? "True" : "False";
	string hasHdmi = m_hasHdmi== true ? "True" : "False";
	string hasUsb = m_hasUsb == true ? "True" : "False";

	/*Float to string conversion*/
	ostringstream oss_screen;
	oss_screen.precision(2);	
	oss_screen << fixed << m_screenSize;
	/*Float to string conversion*/

	/*Int to string conversion*/
	ostringstream oss_price;
	oss_price.precision(2);	
	oss_price << fixed << m_price;
	/*Int to string conversion*/
	
	relevantProperties = 	"Name     : " + m_productName + "\n" +
							"Type     : " + m_productType + "\n" +
							"Screen   : " + oss_screen.str() + " ''" + "\n" +
							"hasWifi  : " + hasWifi + "\n" +
							"hasHdmi  : " + hasHdmi + "\n" +
							"hasUsb   : " + hasUsb + "\n" +
							"Price    : " + oss_price.str() + " TL" + "\n";

	return relevantProperties;
}

void tv::InitRelevantProperties()
{
	cout << "Enter Television Properties : " << endl;
	while(!GetInputFromUser(ENUM_PROPERTY_PRODUCTNAME));
	while(!GetInputFromUser(ENUM_PROPERTY_SCREENSIZE));
	while(!GetInputFromUser(ENUM_PROPERTY_HASWIFI));
	while(!GetInputFromUser(ENUM_PROPERTY_HASHDMI));
	while(!GetInputFromUser(ENUM_PROPERTY_HASUSB));
	while(!GetInputFromUser(ENUM_PROPERTY_PRICE));

}

bool tv::GetInputFromUser(ENUM_PROPERTIES property)
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
		case ENUM_PROPERTY_HASHDMI:
		{
			cout << setw(MAX_QUESTION_WIDTH) << left << QUESTION_HASHDMI(m_productName) << "\t";
			cin >> input;
			if(input == "1")
			{
				bRet = SetHasHdmi(true);
			}
			else if(input == "0")
			{
				bRet = SetHasHdmi(false);
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

bool tv::CalculateBenefits()
{
	m_deviceBenefit = ((int)m_hasHdmi + (int)m_hasUsb + (int)m_hasWifi) * m_screenSize;

	m_priceOverPerformance = m_price / m_deviceBenefit;

	return true;
}


