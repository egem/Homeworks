#include "eecapsule.h"
#include <iomanip>
#include <cmath>

#define EECAPSULE_DEBUG(str)		//do{ std::cout << str << std::endl; } while(false)
#define EECAPSULE_ERROR(str)		do{ std::cout << str << std::endl; } while(false)
#define EECAPSULE_FUNCTION(str)		//do{ std::cout << str << std::endl; } while(false)


EECapsule::EECapsule(std::string strName, unsigned int nCID, char chLatitude, int nLongitude)
: m_strName(strName), m_nCID(nCID), m_chLatitude(chLatitude), m_nLongitude(nLongitude)
{
	EECAPSULE_FUNCTION("[EECAPSULE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);
	
}

EECapsule::~EECapsule()
{
	EECAPSULE_FUNCTION("[EECAPSULE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);

}

int EECapsule::GetLongitude() const
{
	EECAPSULE_FUNCTION("[EECAPSULE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);
	return m_nLongitude;
}

void EECapsule::PrintInfo() const
{
	EECAPSULE_FUNCTION("[EECAPSULE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);

	int nMaxLength = 0;
	int nNameLength = m_strName.length();
	int nCIDLength = std::floor(std::log10(std::abs(m_nCID))) + 1;
	int nLongitudeLength = 0;
	int nLatitudeLength = 0;
	
	if(m_nLongitude == 0)
		nLongitudeLength = 1;
	else
		nLongitudeLength = std::floor(std::log10(std::abs(m_nLongitude))) + 1;

	if(m_chLatitude == 0)
		nLatitudeLength = 1;
	else
		nLatitudeLength = std::floor(std::log10(std::abs((int)m_chLatitude))) + 1;
		
	int nDestinationLength = nLongitudeLength + nLatitudeLength + 3; // two for signs and one for whitespace 
	
	if(nNameLength > nMaxLength)
		nMaxLength = nNameLength;

	if(nCIDLength > nMaxLength)
		nMaxLength = nCIDLength;

	if(nDestinationLength > nMaxLength)
		nMaxLength = nDestinationLength;
	
	nMaxLength = nMaxLength + 19; 	// 19 is for variable names to print s.t Name, CID and Destination
	
	std::cout << std::setfill('=') << std::setw(nMaxLength) << std::right << " " << std::setfill(' ') << std::setw(1) << std::right << " " << std::endl;
	std::cout << std::setw(15) << std::left << "Name" << std::setw(3) << std::left << ":" << m_strName << " " << std::endl;
	std::cout << std::setw(15) << std::left << "CID"  << std::setw(3) << std::left << ":" << m_nCID << " " << std::endl;
	std::cout << std::setw(15) << std::left << "Destination" << std::setw(3) << std::left << ":" 
				<< std::showpos << (int)m_chLatitude << " " << std::showpos << m_nLongitude << " " <<  std::endl;
	std::cout << std::noshowpos;
	std::cout << std::setfill('=') << std::setw(nMaxLength) << std::right << " " << std::setfill(' ') << std::setw(1) << std::right << " " << std::endl;
	
	
}

bool EECapsule::operator< (const EECapsule& rcRightHandSide)
{
	EECAPSULE_FUNCTION("[EECAPSULE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);
	if(rcRightHandSide.m_nLongitude > m_nLongitude)
		return true;
	else
		return false;
}

bool EECapsule::operator> (const EECapsule& rcRightHandSide)
{
	EECAPSULE_FUNCTION("[EECAPSULE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);
	if(rcRightHandSide.m_nLongitude < m_nLongitude)
		return true;
	else
		return false;
}

bool EECapsule::operator<= (const EECapsule& rcRightHandSide)
{
	EECAPSULE_FUNCTION("[EECAPSULE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);
	if(rcRightHandSide.m_nLongitude >= m_nLongitude)
		return true;
	else
		return false;
}

bool EECapsule::operator>= (const EECapsule& rcRightHandSide)
{
	EECAPSULE_FUNCTION("[EECAPSULE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);
	if(rcRightHandSide.m_nLongitude <= m_nLongitude)
		return true;
	else
		return false;
}

bool EECapsule::operator== (const EECapsule& rcRightHandSide)
{
	EECAPSULE_FUNCTION("[EECAPSULE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);
	if(	rcRightHandSide.m_strName == m_strName &&
		rcRightHandSide.m_nCID == m_nCID )
		return true;
	else
		return false;
}


