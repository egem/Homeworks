#ifndef __EECAPSULE_H__
#define __EECAPSULE_H__

#include <iostream>
#include <stdlib.h>
#include <cstring>

class EECapsule
{
	private: 
		std::string m_strName;
		unsigned long int m_nCID;
		char m_chLatitude;
		int m_nLongitude;

	public:
		EECapsule(std::string strName, unsigned int nCID, char chLatitude, int nLongitude);
		~EECapsule();
		
		int GetLongitude() const;

		void PrintInfo() const;
		
		bool operator< (const EECapsule& rcRightHandSide);
		bool operator> (const EECapsule& rcRightHandSide);
		bool operator<= (const EECapsule& rcRightHandSide);
		bool operator>= (const EECapsule& rcRightHandSide);
		bool operator== (const EECapsule& rcRightHandSide);

};




#endif 
