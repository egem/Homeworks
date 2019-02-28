#ifndef __EEAIRCRAFT_H__
#define __EEAIRCRAFT_H__

#include "eecapsule.h"
#include "sorteddynamicqueue.h"
 

typedef enum
{
	EN_FLIGHT_DIRECTION_WEST = -1,
	EN_FLIGHT_DIRECTION_EAST = 1,
}EN_FLIGHT_DIRECTION;

class EEAircraft
{
	private: 
		char m_chLatitude;
		int m_nLongitude;
		EN_FLIGHT_DIRECTION m_eDirection;
 		SortedDynamicQueue m_cCustomerList;
		
	public:
		EEAircraft(char chLatitude, int nLongitude, EN_FLIGHT_DIRECTION eDirection);
		~EEAircraft();
		
		void Integrate(EECapsule* pcNewCapsule);

		EECapsule* Drop(); 

		void Display() const;

		bool Empty() const;

};

#endif
