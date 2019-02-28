#include "userinterface.h"
#include <iomanip>
#include <sstream>

UserInterface* UserInterface::pcInstance = NULL;

UserInterface::UserInterface()
{
	MainMenuChoice = " ";
	DepartureChoice = " ";
	DepartureString1 = " ";
	DepartureString2 = " ";
	nFlightDirection = 0;
	eFlightDirection = EN_FLIGHT_DIRECTION_WEST;
	InputDirection = " ";
	RegistrationMenuChoice = " ";
	NewPassengerName = " ";
	NewPassengerCID = " ";
	nCID = 0;
	DestinationChoice = " ";
	DestinationString1 = " ";
	nLatitude = 0;
	nLongitude = 0;
	DestinationLatitude = 0;
	DestinationLongitude = 0;
}

UserInterface::~UserInterface()
{
	delete pcInstance;
}

UserInterface* UserInterface::GetInstance()
{
	if(pcInstance == NULL)
		pcInstance = new UserInterface();

	return pcInstance;
}

void UserInterface::PrintWelcomeMessage()
{
	std::cout << "===============================================================================" 	<< std::endl;
	std::cout << "                Welcome EE Tech Easy Everywhere Simulator 					 "	<< std::endl;
	std::cout << "                Author: Ahmet Ege Mahlec	Student ID : 1555200			     "	<< std::endl;
	std::cout << "===============================================================================" 	<< std::endl;
}

void UserInterface::PrintMainMenuOptions()
{
	std::cout	<< 		"EE Tech Easy Everywhere Simulator" 	<< std::endl;
	std::cout	<<		"\t 1- New Flight"						<< std::endl
				<<		"\t 2- Exit"							<< std::endl;
}

void UserInterface::PrintRegistrationMenuOptions()
{
	std::cout	<<		"\t 1- New Passenger"									<< std::endl
				<< 		"\t 2- Close Registration and Simulate the Flight"		<< std::endl;
}

void UserInterface::PrintSuccessfulMessage()
{
	std::cout << "New passenger has been successfully registered!" << std::endl;
}

void UserInterface::PrintSessionClosed()
{
	std::cout << "The registration has been closed and the aircraft to take off is:" << std::endl;
}

void UserInterface::PrintSessionEnd()
{
	std::cout << "Simulation has been ended. " << std::endl;
}


int UserInterface::String2Int(std::string input)
{
	int dValue;

	std::stringstream s_str(input);
	s_str >> dValue;

	return dValue;
}

std::string UserInterface::DivideInputString(std::string& input)
{
	bool bCharacterDetected = false;
	
	int i = 0;
  	for(; i < input.length(); i++)
	{
		if(input[i] != ' ' && input[i] != '\t')
			bCharacterDetected = true;

		if((input[i] == ' ' || input[i] == '\t') && bCharacterDetected)
			break;
			
	}

	std::string newString1(input,0,i); // Formed a string containing the letters until whitespace	
	std::string newstring(input,i+1,(input.length()-i+1));	// Formed a  string starting from whitespace
	
	input = newString1;
	return newstring;
}

bool UserInterface::GetInputFromUser(EN_INPUT input)
{	
	bool bRet = false;
	

	switch(input)
	{
		case EN_INPUT_MAIN_MENU:
		{
			PrintMainMenuOptions();
			std::cout << std::setw(USER_CHOICE_WIDTH) << std::right << "Choice :" << "\t";
			std::cin >> MainMenuChoice;

			if(MainMenuChoice == "1")
				bRet = true;
			else if(MainMenuChoice == "2")
				bRet = true;
			else
				std::cout << "Please enter a valid input!" << std::endl;
		}
		break;
		case EN_INPUT_DEPARTURE_CHOICE:
		{
			std::cout << "Input Departure Latitude, Longitude and Flight Direction:" << std::endl;
			std::cout << std::setw(USER_CHOICE_WIDTH) << std::right << "Choice :" << "\t";
			std::cin.ignore(1000, '\n');
			std::getline(std::cin, DepartureChoice);	

			std::stringstream s_str(DepartureChoice);
			s_str >> nLatitude;
			s_str >> nLongitude;
			s_str >> nFlightDirection;
			
			if(nLatitude >= -90 && nLatitude <= 90 && nLongitude >= -180 && nLongitude <= 180 && (nFlightDirection == -1 || nFlightDirection == 1))
			{
				nFlightDirection == -1 ? eFlightDirection = EN_FLIGHT_DIRECTION_WEST : eFlightDirection = EN_FLIGHT_DIRECTION_EAST;
				bRet = true;
			}
			else
				std::cout << "Please enter a valid input!" << std::endl;
			
		}
		break;
		case EN_INPUT_INPUT_DIRECTION:
		{
			std::cout << "Input Direction :" << std::endl;
			std::cout << std::setw(USER_CHOICE_WIDTH) << std::right << "Choice :" << "\t";
			std::cin >> InputDirection;

			if((InputDirection == "1" && eFlightDirection == EN_FLIGHT_DIRECTION_EAST) || (InputDirection == "-1" && eFlightDirection == EN_FLIGHT_DIRECTION_WEST))
			{
				bRet = true;
			}
			else if((InputDirection == "-1" && eFlightDirection == EN_FLIGHT_DIRECTION_EAST) || (InputDirection == "1" && eFlightDirection == EN_FLIGHT_DIRECTION_WEST))
			{
				std::cout << "No Flight available" << std::endl;
				if(eFlightDirection == EN_FLIGHT_DIRECTION_EAST)
				{
					std::cout << "There is no flight to the West. Please select 1 to book to the East" << std::endl;
				}
				else if(eFlightDirection == EN_FLIGHT_DIRECTION_WEST)
				{
					std::cout << "There is no flight to the East. Please select -1 to book to the West" << std::endl;
				}
				else
				{
					std::cout << "Please enter a valid input!" << std::endl;
				}
			}
		}
		break;
		case EN_INPUT_REGISTRATION_MENU_CHOICE:
		{
			std::cout << "EE Tech Easy Everywhere" << std::endl;
			PrintRegistrationMenuOptions();
			std::cout << std::setw(USER_CHOICE_WIDTH) << std::right << "Choice :" << "\t";
			std::cin >> RegistrationMenuChoice;

			if(RegistrationMenuChoice == "1")
			{
				bRet = true;
			}
			else if(RegistrationMenuChoice == "2")
			{
				bRet = true;
			}
			else
			{
				std::cout << "Please enter a valid input!" << std::endl;
			}
		}
		break;
		case EN_INPUT_NEW_PASSENGER_NAME:
		{
			std::cout << "Name of the passenger:" << std::endl;
			std::cout << std::setw(USER_CHOICE_WIDTH) << std::right << "Choice :" << "\t";
			std::cin.ignore(1000, '\n');
			std::getline(std::cin, NewPassengerName);
			bRet = true;
		}
		break;

		case EN_INPUT_NEW_PASSENGER_CID:
		{
			std::cout << "CID of the passenger:" << std::endl;
			std::cout << std::setw(USER_CHOICE_WIDTH) << std::right << "Choice :" << "\t";
			std::cin >> NewPassengerCID;
			std::stringstream s_str(NewPassengerCID);
			s_str >> nCID;

			if(nCID != 0)
				bRet = true;
		}
		break;

		case EN_INPUT_DESTINATION_CHOICE:
		{
			std::cout << "Destination (Lat. & Long):" << std::endl;
			std::cout << std::setw(USER_CHOICE_WIDTH) << std::right << "Choice :" << "\t";
			std::cin.ignore(1000, '\n');
			std::getline(std::cin, DestinationChoice);

			std::stringstream s_str(DestinationChoice);
			s_str >> DestinationLatitude;
			s_str >> DestinationLongitude;

			if(DestinationLatitude >= -90 && DestinationLatitude <= 90 && DestinationLongitude >= -180 && DestinationLongitude <= 180)
			{
				bRet = true;
			}
		}
		break;
	}

	return bRet;
}	


#if 0	
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
#endif
