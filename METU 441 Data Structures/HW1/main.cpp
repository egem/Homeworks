#ifndef __IOSTREAM_H__
#define __IOSTREAM_H__

#include <iostream>
#include <cstring>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;
#endif


#include "ElectronicProduct.h"
#include <vector>

void PrintWelcomeMessage()
{
	cout << "===============================================================================" 	<< endl;
	cout << "                Welcome EE Tech Product Comparison 							"	<< endl;
	cout << "                Author: Ahmet Ege Mahlec	Student ID : 1555200			    "	<< endl;
	cout << "===============================================================================" 	<< endl;
}

void PrintMainMenuOptions()
{
	
	cout	<<		"Enter your choice: "							<< endl << endl
			<<		"\t 1- Enter new product"						<< endl
			<<		"\t 2- Import all product data from TXT"		<< endl
			<<		"\t 3- Display all products"					<< endl
			<<		"\t 4- Choose 3 products to compare"			<< endl
			<<		"\t 5- Export all product data to TXT"			<< endl
			<<		"\t 0- Exit program "							<< endl;
}

void PrintSelectProductTypeOptions()
{
	cout 	<< 		"\t Please enter choice for new product type" 		<< endl
			<< 		"\t\t 1- GameConsole" 								<< endl
			<< 		"\t\t 2- Laptop"									<< endl
			<< 		"\t\t 3- Smart Phone"								<< endl
			<< 		"\t\t 4- Television"								<< endl
			<<		"\t\t 0- Return to main menu"						<< endl;
}

bool CreateNewProduct(vector<ElectronicProduct*> &product, string userChoice)
{
	if(userChoice == "1")
	{//In case of Game Console selection by the user 

		product.push_back(ElectronicProduct::GetInstance(ENUM_PRODUCT_TYPE_GAMECONSOLE));

		cout << setfill('-') << setw(USER_CHOICE_WIDTH) << right << " " << endl;
		cout << setfill(' ') << setw(USER_CHOICE_WIDTH) << right << " " << endl;
		
		cout << "Product is saved. Details are below. " << endl;
		cout << product[product.size()-1]->FindRelevantProperties() << endl;
		
		cout << setfill('-') << setw(USER_CHOICE_WIDTH) << right << " " << endl;
		cout << setfill(' ') << setw(USER_CHOICE_WIDTH) << right << " " << endl;
		return true;
		
	}
	else if(userChoice == "2")
	{//In case of Laptop Computer selection by the user

		product.push_back(ElectronicProduct::GetInstance(ENUM_PRODUCT_TYPE_LAPTOPCOMP));

		cout << setfill('-') << setw(USER_CHOICE_WIDTH) << right << " " << endl;
		cout << setfill(' ') << setw(USER_CHOICE_WIDTH) << right << " " << endl;
		
		cout << "Product is saved. Details are below. " << endl;
		cout << product[product.size()-1]->FindRelevantProperties() << endl;
		
		cout << setfill('-') << setw(USER_CHOICE_WIDTH) << right << " " << endl;
		cout << setfill(' ') << setw(USER_CHOICE_WIDTH) << right << " " << endl;
		return true;

	}
	else if(userChoice == "3")
	{//In case of Smart Phone selection by the user

		product.push_back(ElectronicProduct::GetInstance(ENUM_PRODUCT_TYPE_SMARTPHONE));
		
		cout << setfill('-') << setw(USER_CHOICE_WIDTH) << right << " " << endl;
		cout << setfill(' ') << setw(USER_CHOICE_WIDTH) << right << " " << endl;
		
		cout << "Product is saved. Details are below. " << endl;
		cout << product[product.size()-1]->FindRelevantProperties() << endl;
		
		cout << setfill('-') << setw(USER_CHOICE_WIDTH) << right << " " << endl;
		cout << setfill(' ') << setw(USER_CHOICE_WIDTH) << right << " " << endl;
		return true;
		
	}
	else if(userChoice == "4")
	{//In case of Television selection by the user

		product.push_back(ElectronicProduct::GetInstance(ENUM_PRODUCT_TYPE_TV));
		
		cout << setfill('-') << setw(USER_CHOICE_WIDTH) << right << " " << endl;
		cout << setfill(' ') << setw(USER_CHOICE_WIDTH) << right << " " << endl;
		
		cout << "Product is saved. Details are below. " << endl;
		cout << product[product.size()-1]->FindRelevantProperties() << endl;
		
		cout << setfill('-') << setw(USER_CHOICE_WIDTH) << right << " " << endl;
		cout << setfill(' ') << setw(USER_CHOICE_WIDTH) << right << " " << endl;
		return true;

	}
	else if(userChoice == "0")
	{
		return true;
	}
	else
	{
		cout << " Please enter a number between 0 and 4. " << endl;
		return false;	
	}
}

/*Display the features of the products entered by the user. This function may be used in future design. */
void DisplayAllProduct(vector<ElectronicProduct*> product)
{
	for(int i = 0; i<product.size(); i++)
	{
		cout << "=================================================" << endl;
		cout << product[i]->FindRelevantProperties() << endl << endl << endl;
	}
}

/*Only display Products' ID, Name and Type*/
void DisplayProductsSummary(vector<ElectronicProduct*> product)
{
	
	int temp_productID;
	string temp_productName;
	string temp_productType;

	const int column_width = 30;
	
	cout << setfill('-') << setw(USER_CHOICE_WIDTH) << right << " " << endl;
	cout << setfill(' ') << setw(USER_CHOICE_WIDTH) << right << " " << endl;
	
	cout 	<< setw(column_width) << left << "Product ID " 
			<< setw(column_width) << left << "Product Name" 
			<< setw(column_width) << left << "Product Type" << endl;

	cout << setfill('-') << setw(USER_CHOICE_WIDTH) << right << " " << endl;
	cout << setfill(' ') << setw(USER_CHOICE_WIDTH) << right << " " << endl;
	
	for(int i = 0; i < product.size(); i++)
	{
		product[i]->GetProductID(temp_productID);
		product[i]->GetProductName(temp_productName);
		product[i]->GetProductType(temp_productType);
		cout	<< setw(column_width) << left << temp_productID 
				<< setw(column_width) << left << temp_productName 
				<< setw(column_width) << left << temp_productType << endl; 
		
	}

	cout << endl << endl << endl;
	cout << setfill('-') << setw(USER_CHOICE_WIDTH) << right << " " << endl;
	cout << setfill(' ') << setw(USER_CHOICE_WIDTH) << right << " " << endl << endl;
}

bool GetProductID(int* selectedPID, vector<ElectronicProduct*> product)
{
	string input_PID;
	for(int i = 0; i < 3; i++)
	{
		cout << setw(USER_CHOICE_WIDTH) << right << "Choice :" << "\t";
		cin >> input_PID;
		stringstream s_str(input_PID);
		s_str >> selectedPID[i];
		selectedPID[i]--;		// Decrement the input PID because PID first element is 1 whereas vector first element is 0
		if(selectedPID[i] >= 0 && selectedPID[i] < product.size())	 
		{
			for(int j = i-1; j >= 0; j--)
			{
				if(selectedPID[i] == selectedPID[j])
				{
					cout << "You have already select the product whose ID is " << selectedPID[i] << endl;
					cout << "Please try again" << endl;
					i--;
					break;
				}
				else if(!ElectronicProduct::IsProductTypeSame(product[selectedPID[0]], product[selectedPID[i]]))
				{
					string firstProductType;
					product[selectedPID[0]]->GetProductType(firstProductType);
					cout << "Selected products should be same. " << endl;
					cout << "Please select the products whose type is " << firstProductType <<endl;
					i--;
					
				}
			}
		}
		else if(selectedPID[i] == -1)
		{
			return false;
		}
		else
		{
			cout << "Please enter a positive number. Max value is " << product.size() <<  endl;
			i--;
		}
	}

	return true;
}

void CompareProducts(vector<ElectronicProduct*> product)
{
	if(product.size() >= 3)
	{
		cout << "Please enter 3 products ID. The products type should be same. " << endl;
		cout << "Press 0 to return to main menu." << endl;
		int selectedPID[3] = {0};

		if(GetProductID(selectedPID, product))
			ElectronicProduct::CompareElectronicProducts(product[selectedPID[0]], product[selectedPID[1]], product[selectedPID[2]]);
		
	}
	else
	{
		cout << "You have to enter at least 3 product to use this feature!" << endl << endl << endl;
	}
	
}

/* Remove the blanks located at the input string*/
string TrimInputString(string input)
{
	/*Removing blanks from the beginning*/
	int i = 0;
  	for(; i < input.length(); i++)
	{
		if(input[i] != ' ' && input[i] != '\t')
			break;
			
	}

	/*Remove the blanks from the end*/
	int j = input.length()-1;
	for(; j>0; j--)
	{
		if(input[i] != ' ' && input[i] != '\t' && input[i] != '\n')
			break;
	}
	
	string newstring(input,i,(j-i+1));	// Formed a (j-i) length string starting from ith character

	return newstring;
}

float String2Float(string input)
{
	float fValue;

	stringstream s_str(input);
	s_str >> fValue;

	return fValue;
}

int String2Int(string input)
{
	int dValue;

	stringstream s_str(input);
	s_str >> dValue;

	return dValue;
}

bool String2Bool(string input)
{
	if(input == "true" || input == "True" || input == "TRUE" || input == "true " || input == "True " || input == "TRUE ")
		return true;
	else 
		return false;
}

void StateMachine(string input, vector<ElectronicProduct*> &product, bool newTxt)
{
	static ENUM_STATE_TYPE state = ENUM_STATE_IDLE;
	stringstream iss(input);
	static string productName;
	static string productType;
	string productInput;

	if(newTxt == true)
		state = ENUM_STATE_IDLE;
	
	switch(state)
	{
		case ENUM_STATE_IDLE:
		{
			if(input[0] == '=')
			{
				state = ENUM_STATE_GETNAME;
			}
		}
		break;
		case ENUM_STATE_GETNAME:
		{
			getline(iss, productName, ':');	
			getline(iss,productName);	
			productName = TrimInputString(productName);
			state = ENUM_STATE_GETTYPE;
		}
		break;
		case ENUM_STATE_GETTYPE:
		{
			getline(iss, productType, ':');
			getline(iss,productType);
			productType = TrimInputString(productType);
			product.push_back(ElectronicProduct::GetInstance(productName, productType));

			if(productType == "Smartphone")
				state = ENUM_STATE_GETCPU;
			else if(productType == "LaptopComputer")
				state = ENUM_STATE_GETCPU;
			else if(productType == "GameConsole")
				state = ENUM_STATE_GETCPU;
			else if(productType == "TV")
				state = ENUM_STATE_GETSCREENSIZE;
			else
				state = ENUM_STATE_IDLE;
		}
		break;
		case ENUM_STATE_GETCPU:
		{
			getline(iss, productInput, ':');
			getline(iss, productInput, 'G');
			productInput = TrimInputString(productInput);
			product[product.size()-1]->SetDeviceCPU(String2Float(productInput));
			state = ENUM_STATE_GETRAM;
			
		}
		break;
		case ENUM_STATE_GETRAM:
		{
			getline(iss, productInput, ':');
			getline(iss, productInput, 'G');
			productInput = TrimInputString(productInput);
			product[product.size()-1]->SetDeviceRam(String2Int(productInput));
			state = ENUM_STATE_GETMEMORY;
		}
		break;
		case ENUM_STATE_GETMEMORY:
		{
			getline(iss, productInput, ':');
			getline(iss, productInput, 'G');
			productInput = TrimInputString(productInput);
			product[product.size()-1]->SetDeviceMemory(String2Int(productInput));
			
			if(productType == "Smartphone")
				state = ENUM_STATE_GETSCREENSIZE;
			else if(productType == "LaptopComputer")
				state = ENUM_STATE_GETSCREENSIZE;
			else if(productType == "GameConsole")
				state = ENUM_STATE_GETBLUETOOTH;
			else if(productType == "TV")
				state = ENUM_STATE_GETSCREENSIZE;
			else
				state = ENUM_STATE_IDLE;
		}
		break;
		case ENUM_STATE_GETSCREENSIZE:
		{
			getline(iss, productInput, ':');
			getline(iss, productInput, '\'');
			productInput = TrimInputString(productInput);
			product[product.size()-1]->SetScreenSize(String2Float(productInput));

			if(productType == "Smartphone")
				state = ENUM_STATE_GETBATTERYLIFE;
			else if(productType == "LaptopComputer")
				state = ENUM_STATE_GETBATTERYLIFE;
			else if(productType == "GameConsole")
				state = ENUM_STATE_GETBLUETOOTH;
			else if(productType == "TV")
				state = ENUM_STATE_GETWIFI;
			else
				state = ENUM_STATE_IDLE;
		}
		break;
		case ENUM_STATE_GETBATTERYLIFE:
		{
			getline(iss, productInput, ':');
			getline(iss, productInput, 'h');
			productInput = TrimInputString(productInput);
			product[product.size()-1]->SetBatteryLife(String2Float(productInput));

			if(productType == "Smartphone")
				state = ENUM_STATE_GET4G;
			else if(productType == "LaptopComputer")
				state = ENUM_STATE_GETBLUETOOTH;
			else if(productType == "GameConsole")
				state = ENUM_STATE_GETBLUETOOTH;
			else if(productType == "TV")
				state = ENUM_STATE_GETWIFI;
			else
				state = ENUM_STATE_IDLE;
		}
		break;
		case ENUM_STATE_GET4G:
		{
			getline(iss, productInput, ':');
			getline(iss, productInput);
			productInput = TrimInputString(productInput);
			product[product.size()-1]->SetHas4G(String2Bool(productInput));

			if(productType == "Smartphone")
				state = ENUM_STATE_GETBLUETOOTH;
			else if(productType == "LaptopComputer")
				state = ENUM_STATE_GETBLUETOOTH;
			else if(productType == "GameConsole")
				state = ENUM_STATE_GETBLUETOOTH;
			else if(productType == "TV")
				state = ENUM_STATE_GETWIFI;
			else
				state = ENUM_STATE_IDLE;
		}
		break;
		case ENUM_STATE_GETBLUETOOTH:
		{
			getline(iss, productInput, ':');
			getline(iss, productInput);
			productInput = TrimInputString(productInput);
			product[product.size()-1]->SetHasBluetooth(String2Bool(productInput));

			if(productType == "Smartphone")
				state = ENUM_STATE_GETFRONTCAMERA;
			else if(productType == "LaptopComputer")
				state = ENUM_STATE_GETHDMI;
			else if(productType == "GameConsole")
				state = ENUM_STATE_GETWIFI;
			else if(productType == "TV")
				state = ENUM_STATE_GETWIFI;
			else
				state = ENUM_STATE_IDLE;
		}
		break;
		case ENUM_STATE_GETWIFI:
		{
			getline(iss, productInput, ':');
			getline(iss, productInput);
			productInput = TrimInputString(productInput);
			product[product.size()-1]->SetHasWifi(String2Bool(productInput));

			if(productType == "Smartphone")
				state = ENUM_STATE_GETFRONTCAMERA;
			else if(productType == "LaptopComputer")
				state = ENUM_STATE_GETHDMI;
			else if(productType == "GameConsole")
				state = ENUM_STATE_GETUSB;
			else if(productType == "TV")
				state = ENUM_STATE_GETHDMI;
			else
				state = ENUM_STATE_IDLE;
		}
		break;
		case ENUM_STATE_GETHDMI:
		{
			getline(iss, productInput, ':');
			getline(iss, productInput);
			productInput = TrimInputString(productInput);
			product[product.size()-1]->SetHasHdmi(String2Bool(productInput));

			if(productType == "Smartphone")
				state = ENUM_STATE_GETFRONTCAMERA;
			else if(productType == "LaptopComputer")
				state = ENUM_STATE_GETOPTICALDEVICE;
			else if(productType == "GameConsole")
				state = ENUM_STATE_GETUSB;
			else if(productType == "TV")
				state = ENUM_STATE_GETUSB;
			else
				state = ENUM_STATE_IDLE;
		}
		break;
		case ENUM_STATE_GETUSB:
		{
			getline(iss, productInput, ':');
			getline(iss, productInput);
			productInput = TrimInputString(productInput);
			product[product.size()-1]->SetHasUsb(String2Bool(productInput));

			if(productType == "Smartphone")
				state = ENUM_STATE_GETFRONTCAMERA;
			else if(productType == "LaptopComputer")
				state = ENUM_STATE_GETOPTICALDEVICE;
			else if(productType == "GameConsole")
				state = ENUM_STATE_GETOPTICALDEVICE;
			else if(productType == "TV")
				state = ENUM_STATE_GETPRICE;
			else
				state = ENUM_STATE_IDLE;
		}
		break;
		case ENUM_STATE_GETFRONTCAMERA:
		{
			getline(iss, productInput, ':');
			getline(iss, productInput);
			productInput = TrimInputString(productInput);
			product[product.size()-1]->SetHasFrontCamera(String2Bool(productInput));

			if(productType == "Smartphone")
				state = ENUM_STATE_GETPRICE;
			else if(productType == "LaptopComputer")
				state = ENUM_STATE_GETOPTICALDEVICE;
			else if(productType == "GameConsole")
				state = ENUM_STATE_GETOPTICALDEVICE;
			else if(productType == "TV")
				state = ENUM_STATE_GETPRICE;
			else
				state = ENUM_STATE_IDLE;
		}
		case ENUM_STATE_GETOPTICALDEVICE:
		{
			getline(iss, productInput, ':');
			getline(iss, productInput);
			productInput = TrimInputString(productInput);
			product[product.size()-1]->SetOpticalDevice(productInput);

			if(productType == "Smartphone")
				state = ENUM_STATE_GETPRICE;
			else if(productType == "LaptopComputer")
				state = ENUM_STATE_GETPRICE;
			else if(productType == "GameConsole")
				state = ENUM_STATE_GETPRICE;
			else if(productType == "TV")
				state = ENUM_STATE_GETPRICE;
			else
				state = ENUM_STATE_IDLE;
		}
		break;
		case ENUM_STATE_GETPRICE:
		{
			getline(iss, productInput, ':');
			getline(iss, productInput, 'T');
			productInput = TrimInputString(productInput);
			product[product.size()-1]->SetPrice(String2Int(productInput));
			product[product.size()-1]->CalculateBenefits();
			state = ENUM_STATE_IDLE;
		}
		break;
		default:
		break;
	}
}
void ImportProductsFromTXT(vector<ElectronicProduct*> &product)
{
	#define EXPECTED 0
#if(EXPECTED == 0)
	cout << "Enter the file name. Press 0 to return the main menu" << endl;
	cout << setw(USER_CHOICE_WIDTH) << right << "Output file name :" << "\t";

	string inputFilePath;
	cin >> inputFilePath;

	if(inputFilePath == "0")
		return;
		
	ifstream inf(inputFilePath);
#else
	ifstream inf(INPUT_FILE_NAME);
#endif
	bool newTxt = true;
 	string input;
 	
    if (!inf)
    {
#if(EXPECTED == 0)
        cout << inputFilePath << " couldn't be opened" << endl;
#else
		cout << INPUT_FILE_NAME << " couldn't be opened" << endl;
#endif
        
    }
    else
    { 
		while (inf)
	    {
	        // read stuff from the file into a string and print it
	        getline(inf, input);
	        StateMachine(input, product,newTxt);
	        newTxt = false;
	    }
		cout << "Data is imported from text successfully" << endl;
    }
 
}


void ExportProducts2TXT(vector<ElectronicProduct*> product)
{
	bool terminateExportProductsLoop = false;
	cout << "Enter the file name. Press 0 to return the main menu" << endl;
	while(!terminateExportProductsLoop)
	{
		cout << setw(USER_CHOICE_WIDTH) << right << "Output file name :" << "\t";

		string input;
		cin >> input;

		if(input == "0")
			break;
		ofstream outf(input);

		if (!outf)
	    {
	        // Print an error and exit
	        cout << "File couldn't be created. Please try again" << endl;
	       	terminateExportProductsLoop = false;
	    }
		else
		{
			outf << "EE Tech All Product Data " << endl;		
		    for(int i = 0; i<product.size(); i++)
			{
				outf << "=================================================" << endl;
				outf << product[i]->FindRelevantProperties() << endl << endl << endl;
			}

			cout << "Exporting the products to file ," << input << ", is successfull " << endl; 
			terminateExportProductsLoop = true;
		}
	}

}

int main()
{
	bool terminateMainLoop = false;
	bool terminateNewProductLoop;
	string mainMenuChoice;
	string newProductMenuChoice;
	vector<ElectronicProduct*> product;

	PrintWelcomeMessage();
	
	while(!terminateMainLoop)
	{//Program Main Loop
		PrintMainMenuOptions();

		cout << setw(USER_CHOICE_WIDTH) << right << "Choice :" << "\t";
		cin >> mainMenuChoice;

		if(mainMenuChoice == "1")
		{
			terminateNewProductLoop = false;
			while(!terminateNewProductLoop)
			{//New Product Loop
				PrintSelectProductTypeOptions();

				cout << setw(USER_CHOICE_WIDTH) << right << "Choice :" << "\t";
				cin >> newProductMenuChoice;

				terminateNewProductLoop = CreateNewProduct(product, newProductMenuChoice);
				
			}// End of new product loop

			terminateMainLoop = false;
		}
		else if(mainMenuChoice == "2")
		{
			/*This function will not be worked with the txt file given to us. The format of the txt file should be 
					
					NAME,
					TYPE,
					CPU,
					RAM,
					MEMORY,
					SCREENSIZE,
					BATTERYLIFE,
					4G,
					BLUETOOTH,
					WIFI,
					HDMI,
					USB,
					FRONTCAMERA,
					OPTICALDEVICE,
					PRICE,

				This is the sequence given to us in the pdf. You can export a txt file then you can try to import it or you can create a txt file on your own
			*/
			ImportProductsFromTXT(product);
			terminateMainLoop = false;
		}
		else if(mainMenuChoice == "3")
		{
			DisplayProductsSummary(product);

			terminateMainLoop = false;
		}
		else if(mainMenuChoice == "4")
		{
			CompareProducts(product);

			terminateMainLoop = false;
		}
		else if(mainMenuChoice == "5")
		{
			ExportProducts2TXT(product);

			/*Refresh product list*/
			for(int i = 0; i<product.size(); i++)
			{
				delete product[i];
			}
			product.clear();
			ElectronicProduct::SetGlobalProductID(1);
			/*Refresh product list*/
			terminateMainLoop = false;
		}
		else if(mainMenuChoice == "0")
		{
			cout << " Thank you for using. Program will exit now! " << endl;
			terminateMainLoop = true;
			
		}
		else 
		{
			cout << " Please enter a number between 0 and 5. " << endl;
			terminateMainLoop = false;
		}
			
				
	}//End of program main loop
	
	/*Program is terminating. Therefore we need to erase the heap memory allocated for the each product.*/
	for(int i = 0; i<product.size(); i++)
	{
		delete product[i];
	}
	product.clear();
	
	
		
}




