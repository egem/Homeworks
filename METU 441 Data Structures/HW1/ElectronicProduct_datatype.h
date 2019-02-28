#ifndef __ELECTRONICPRODUCT_DATATYPE_H__
#define __ELECTRONICPRODUCT_DATATYPE_H__

#ifndef __IOSTREAM_H__
#define __IOSTREAM_H__

#include <iostream>
#include <cstring>
#include <sstream>
#include <cmath>
#include <iomanip>

using namespace std;
#endif


typedef float GHZ;
typedef float INCHES;
typedef float HOURS;

typedef int GB;
typedef int LIRA;

#define QUESTION_PRODUCT_NAME 		"Could you please enter product name?" 
#define QUESTION_PRODUCT_TYPE 		"Could you please enter product type?"
#define QUESTION_CPU_SPEED 			"Could you please enter CPU speed? (in GHz)"
#define QUESTION_RAM_SIZE 			"Could you please enter RAM size? (in GB)"
#define QUESTION_MEMORY_SIZE 		"Could you please enter memory size? (in GB)"
#define QUESTION_SCREEN_SIZE 		"Could you please enter screen size? (in Inches)"
#define QUESTION_BATTERY_LIFE 		"Could you please enter battery life? (in hours)"
#define QUESTION_PRICE				"Could you please enter the price?"
#define QUESTION_HAS4G(x) 			"Has " + x + " got 4G?(Press 1 for YES, 0 for NO)"
#define QUESTION_HASWIFI(x) 		"Has " + x + " got WIFI?(Press 1 for YES, 0 for NO)"
#define QUESTION_HASHDMI(x) 		"Has " + x + " got HDMI?(Press 1 for YES, 0 for NO)"
#define QUESTION_HASBLUETOOTH(x) 	"Has " + x + " got Bluetooth?(Press 1 for YES, 0 for NO)"
#define QUESTION_HASUSB(x)			"Has " + x + " got USB?(Press 1 for YES, 0 for NO)"
#define QUESTION_HASFRONTCAM(x)		"Has " + x + " got Front Camera?(Press 1 for YES, 0 for NO)"
#define QUESTION_OPTICALDEVICE(x)	"Has " + x + " got any optical device?(Press 1 for CD, 2 for DVD, 3 for BLURAY)"

#define USER_CHOICE_WIDTH 80
#define INPUT_FILE_NAME "allProductData.txt"
typedef enum
{
	ENUM_PROPERTY_PRODUCTID,
	ENUM_PROPERTY_PRODUCTNAME,
	ENUM_PROPERTY_DEVICECPU,
	ENUM_PROPERTY_DEVICERAM,
	ENUM_PROPERTY_DEVICEMEMORY,
	ENUM_PROPERTY_SCREENSIZE,
	ENUM_PROPERTY_BATTERYLIFE,
	ENUM_PROPERTY_HAS4G,
	ENUM_PROPERTY_HASBLUETOOTH,
	ENUM_PROPERTY_HASWIFI,
	ENUM_PROPERTY_HASHDMI,
	ENUM_PROPERTY_HASUSB,
	ENUM_PROPERTY_HASFRONTCAMERA,
	ENUM_PROPERTY_OPTICALDEVICE,
	ENUM_PROPERTY_PRICE,
	ENUM_PROPERTY_DEVICEBENEFIT,
	ENUM_PROPERTY_PRICEOVERPERFORMANCE,
	ENUM_PROPERTY_NUM,
}ENUM_PROPERTIES;

typedef enum
{
	ENUM_PRDUCT_TYPE_NONE,
	ENUM_PRODUCT_TYPE_SMARTPHONE,
	ENUM_PRODUCT_TYPE_LAPTOPCOMP,
	ENUM_PRODUCT_TYPE_GAMECONSOLE,
	ENUM_PRODUCT_TYPE_TV,
	ENUM_PRODUCT_TYPE_MAX,
}ENUM_PRODUCT_TYPE;

typedef enum
{
	ENUM_OPTICAL_DEVICE_CD = 1,
	ENUM_OPTICAL_DEVICE_DVD,
	ENUM_OPTICAL_DEVICE_BLURAY,
	ENUM_OPTICAL_DEVICE_MAX,
}ENUM_OPTICAL_DEVICE_TYPE;

typedef enum
{
	ENUM_STATE_IDLE,
	ENUM_STATE_GETNAME,
	ENUM_STATE_GETTYPE,
	ENUM_STATE_GETCPU,
	ENUM_STATE_GETRAM,
	ENUM_STATE_GETMEMORY,
	ENUM_STATE_GETSCREENSIZE,
	ENUM_STATE_GETBATTERYLIFE,
	ENUM_STATE_GET4G,
	ENUM_STATE_GETBLUETOOTH,
	ENUM_STATE_GETWIFI,
	ENUM_STATE_GETHDMI,
	ENUM_STATE_GETUSB,
	ENUM_STATE_GETFRONTCAMERA,
	ENUM_STATE_GETOPTICALDEVICE,
	ENUM_STATE_GETPRICE,
	ENUM_STATE_MAX,
}ENUM_STATE_TYPE;
typedef struct
{
	string deviceName;
	ENUM_OPTICAL_DEVICE_TYPE deviceType;
}OPTICAL_DEVICE;

typedef struct
{
	int productID;
	string productName;
	GHZ deviceCPU;
	GB deviceRam;
	GB deviceMemory;
	INCHES screenSize;
	HOURS batteryLife;
	bool has4g;
	bool hasBluetooth;
	bool hasWifi;
	bool hasHdmi;
	bool hasUsb;
	bool hasFrontCamera;
	OPTICAL_DEVICE opticalDevice;
	LIRA price;	// Price is defined as integer instead of float.
	float deviceBenefit;
	float priceOverPerformance;
}Product_Property;


		

#endif
 
