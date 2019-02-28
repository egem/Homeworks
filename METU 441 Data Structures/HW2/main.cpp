#include "eecapsule.h"
#include "eeaircraft.h"
#include <cstring>
#include <iomanip>
#include <sstream>
#include "userinterface.h"


void SimulateFlight(EEAircraft cAircraft)
{
	while(!cAircraft.Empty())
	{
		EECapsule *tempCapsule = cAircraft.Drop();
		std::cout << "Dropped Capsule: " << std::endl;
		tempCapsule->PrintInfo();
		std::cout << "Current Aircraft:" << std::endl;
		cAircraft.Display();
		std::cout << "***" << std::endl;

	}
}


int main()
{
	UserInterface::GetInstance()->PrintWelcomeMessage();
	EEAircraft *cAirCraft;
	
	while(true)
	{
		while(!UserInterface::GetInstance()->GetInputFromUser(EN_INPUT_MAIN_MENU));

		if(UserInterface::GetInstance()->MainMenuChoice == "1")
		{
			while(!UserInterface::GetInstance()->GetInputFromUser(EN_INPUT_DEPARTURE_CHOICE));
			
			cAirCraft = new EEAircraft(UserInterface::GetInstance()->nLatitude,UserInterface::GetInstance()->nLongitude,UserInterface::GetInstance()->eFlightDirection);

			while(!UserInterface::GetInstance()->GetInputFromUser(EN_INPUT_INPUT_DIRECTION));

			while(true)
			{
				while(!UserInterface::GetInstance()->GetInputFromUser(EN_INPUT_REGISTRATION_MENU_CHOICE));

				if(UserInterface::GetInstance()->RegistrationMenuChoice == "1")
				{
					while(!UserInterface::GetInstance()->GetInputFromUser(EN_INPUT_NEW_PASSENGER_NAME));

					while(!UserInterface::GetInstance()->GetInputFromUser(EN_INPUT_NEW_PASSENGER_CID));

					while(!UserInterface::GetInstance()->GetInputFromUser(EN_INPUT_DESTINATION_CHOICE));

					EECapsule *newCapsule = new EECapsule(UserInterface::GetInstance()->NewPassengerName,static_cast<unsigned long>(UserInterface::GetInstance()->nCID), static_cast<char>(UserInterface::GetInstance()->DestinationLatitude), UserInterface::GetInstance()->DestinationLongitude);

					cAirCraft->Integrate(newCapsule);

					UserInterface::GetInstance()->PrintSuccessfulMessage();
						
				}
				else if(UserInterface::GetInstance()->RegistrationMenuChoice == "2")
				{
					UserInterface::GetInstance()->PrintSessionClosed();
					SimulateFlight(*cAirCraft);
					UserInterface::GetInstance()->PrintSessionEnd();
					
					break;
				}
					
			}

		}
		else if(UserInterface::GetInstance()->MainMenuChoice == "2")
		{
			break;
		}

	}
	

	
}

