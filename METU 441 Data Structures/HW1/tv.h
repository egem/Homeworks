#ifndef __TV_H__
#define __TV_H__

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

class tv : public ElectronicProduct
{
	private:
	
		INCHES m_screenSize;
		bool m_hasWifi;
		bool m_hasHdmi;
		bool m_hasUsb;

		void InitRelevantProperties();

		bool GetInputFromUser(ENUM_PROPERTIES property);

	protected:

	public:

		tv(ENUM_PRODUCT_TYPE productType);
		tv(ENUM_PRODUCT_TYPE productType, string productName);
		~tv();
		
		virtual bool GetScreenSize(INCHES& screenSize) const;
		virtual bool SetScreenSize(INCHES screenSize);

		virtual bool GetHasWifi(bool& hasWifi) const;
		virtual bool SetHasWifi(bool hasWifi);

		virtual bool GetHasHdmi(bool& hasHdmi) const;
		virtual bool SetHasHdmi(bool hasHdmi);

		virtual bool GetHasUsb(bool& hasUsb) const;
		virtual bool SetHasUsb(bool hasUsb);

		virtual string FindRelevantProperties();
		virtual bool CalculateBenefits();
	
};



#endif 
 
