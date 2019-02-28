#include "eeaircraft.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>

EEAircraft::EEAircraft(char chLatitude, int nLongitude, EN_FLIGHT_DIRECTION eDirection)
: m_chLatitude(chLatitude),m_nLongitude(nLongitude),m_eDirection(eDirection)
{
	
}

EEAircraft::~EEAircraft()
{
	m_cCustomerList.ClearQueue();
}

void EEAircraft::Integrate(EECapsule* pcNewCapsule)
{
	m_cCustomerList.QInsert(pcNewCapsule);
}

EECapsule* EEAircraft::Drop()
{
	return m_cCustomerList.QDelete();
}
 

void EEAircraft::Display() const
{
	int nMaxLength = 0;
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
		
	int nDepartureLength = nLongitudeLength + nLatitudeLength+ 3; // two for signs and one for whitespace 

	
	if(nDepartureLength > nMaxLength)
		nMaxLength = nDepartureLength;
	
	nMaxLength = nMaxLength + 19; 	// 19 is for variable names to print s.t Name, CID and Destination
	
	std::cout << std::setfill('=') << std::setw(nMaxLength+50) << std::right << " " << std::setfill(' ') << std::setw(1) << std::right << " " << std::endl;
	std::cout << std::setw(15) << std::left << "EEAircraft" << std::setw(3) << std::left <<  std::endl;
	std::cout << std::setw(15) << std::left << "Departure" << std::setw(3) << std::left << ":" 
				<< std::showpos << (int)m_chLatitude << " " << std::showpos << m_nLongitude << " " <<  std::endl;
	std::cout << std::setw(15) << std::left << "Direction" << std::setw(3) << std::left << ":" << std::showpos <<(int)m_eDirection << " " << std::endl;
				
	std::cout << std::noshowpos;
	std::cout << std::setfill('=') << std::setw(nMaxLength+50) << std::right << " " << std::setfill(' ') << std::setw(1) << std::right << " " << std::endl;

	m_cCustomerList.PrintValues();
	
}

bool EEAircraft::Empty() const
{
	return m_cCustomerList.QEmpty();
}


