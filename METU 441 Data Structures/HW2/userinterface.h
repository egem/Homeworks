#ifndef _USERINTERFACE_H__
#define _USERINTERFACE_H__

#include <cstring>
#include "eeaircraft.h"
#include <iostream>

#define USER_CHOICE_WIDTH 80

typedef enum
{
	EN_INPUT_MAIN_MENU,
	EN_INPUT_DEPARTURE_CHOICE,
	EN_INPUT_INPUT_DIRECTION,
	EN_INPUT_REGISTRATION_MENU_CHOICE,
	EN_INPUT_NEW_PASSENGER_NAME,
	EN_INPUT_NEW_PASSENGER_CID,
	EN_INPUT_DESTINATION_CHOICE,
	EN_INPUT_COUNT,
}EN_INPUT;
class UserInterface
{
	private: 
		UserInterface();
		~UserInterface();

		static UserInterface* pcInstance;

		
		void PrintMainMenuOptions();
		void PrintRegistrationMenuOptions();
		int String2Int(std::string input);
		std::string DivideInputString(std::string& input);

	public:
		std::string MainMenuChoice;
		std::string DepartureChoice;
		std::string DepartureString1;
		std::string DepartureString2;
		int nFlightDirection;
		EN_FLIGHT_DIRECTION eFlightDirection;
		std::string InputDirection;
		std::string RegistrationMenuChoice;
		std::string NewPassengerName;
		std::string NewPassengerCID;
		int nCID;
		std::string DestinationChoice;
		std::string DestinationString1;
		int nLatitude;
		int nLongitude;
		int DestinationLatitude;
		int DestinationLongitude;
		static UserInterface* GetInstance();

		void PrintWelcomeMessage();
		bool GetInputFromUser(EN_INPUT input);

		void PrintSuccessfulMessage();

		void PrintSessionClosed();
		void PrintSessionEnd();


};

#endif
