//*******************************************************************
// beeiot.h
// from Project https://github.com/mchresse/BeeIoT
//
// Description:
// BeeIoT - Main Configuration file
//
//----------------------------------------------------------
// Copyright (c) 2019-present, Randolph Esser
// All rights reserved.
// This file is distributed under the BSD-3-Clause License
// The complete license agreement can be obtained at:
//     https://github.com/mchresse/BeeIoT/license
// For used 3rd party open source see also Readme_OpenSource.txt
//*******************************************************************

/* Map of used ESP32-DevKit-C PIN Configuration:
*  For Default board settings see also
*    C:\Users\MCHRESSE\.platformio\packages\framework-arduinoespressif32\variants\esp32
*================================================================
|Pin| Ref. |  IO# |  DevKitC |       | Protocol |  Components    |
|---|------|------|----------|-------|----------|----------------|
|  1| +3.3V|      |          |       |    +3.3V | -              |
|  2|    EN|      |   SW2    |       |          | ePaper-Key2    |
|  3|*  SVP|GPIO36|  Sens-VP | ADC1-0|        - | -              |
|  4|*  SVN|GPIO39|  Sens-VN | ADC1-3|        - | -              |
|  5|* IO34|GPIO34|          | ADC1-6|          | ePDK3/LoRa DIO2|
|  6|* IO35|GPIO35|          | ADC1-7|          | ePaper-Key4    |
|  7|  IO32|GPIO32|   XTAL32 | ADC1-4|OneWire-SD| DS18B20(3x)    |
|  8|  IO33|GPIO33|   XTAL32 | ADC1-5|          | LoRa DIO0      |
|  9|  IO25|GPIO25|     DAC1 | ADC2-8|  Wire-DT | HX711-DT       |
| 10|  IO26|GPIO26|     DAC2 | ADC2-9|  Wire-Clk| HX711-SCK      |
| 11|  IO27|GPIO27|          | ADC2-7| ADS-Alert| ADS1115/BMS    |
| 12|  IO14|GPIO14| HSPI-CLK | ADC2-6|Status-LED| LoRa RST       |
| 13|  IO12|GPIO12| HSPI-MISO| ADC2-5| SPI1-MISO| LoRa CS\       |
| 14|   GND|      |          |       |       GND| -              |
| 15|  IO13|GPIO13| HSPI-MOSI| ADC2-4| SPI1-MOSI| LoRa DIO1      |
| 16|   SD2|GPIO09|FLASH-D2  | U1-RXD|        - | -              |
| 17|   SD3|GPIO10|FLASH-D3  | U1-TXD|        - | -              |
| 18|   CMD|GPIO11|FLASH-CMD | U1-RTS|        - | -              |
| 19|   +5V|      |          |       |      +5V | -              |
| 20|   CLK|GPIO06|FLASH-CLK | U1-CTS|        - | -              |
| 21|   SD0|GPIO07|FLASH-D0  | U2-RTS|        - | -              |
| 22|   SD1|GPIO08|FLASH-D1  | U2-CTS|        - | -              |
| 23|  IO15|GPIO15| HSPI-SS  | ADC2-3|MonLED-red| Red LED        |
| 24|  IO02|GPIO02| HSPI-4WP | ADC2-2|  SPI-CS  | SDcard CS\     |
| 25|  IO00|GPIO00|   SW1    | ADC2-1|          | ePaper-Key1    |
| 26|  IO04|GPIO04| HSPI-4HD | ADC2-0|      CLK | ePaper BUSY    |
| 27|  IO16|GPIO16|UART2-RXD |       |      DT  | ePaper RST     |
| 28|  IO17|GPIO17|UART2-TXD |       |          | ePaper D/C     |
| 29|  IO05|GPIO05| VSPI-SS  |       | SPI0-CS0 | ePD CS\        |
| 30|  IO18|GPIO18| VSPI-CLK |       | SPI0-Clk | ePD/SD/LoRa Clk|
| 31|  IO19|GPIO19| VSPI-MISO| U0-CTS| SPI0-MISO| SD/LoRa MISO   |
| 32|   GND|      |          |       |      GND | -              |
| 33|  IO21|GPIO21| VSPI-4HD |       |  I2C-SDA | ADS1115/BMS    |
| 34|  RXD0|GPIO03|UART0-RX  | U0-RXD| -> USB   | -              |
| 35|  TXD0|GPIO01|UART0-TX  | U0-TXD| -> USB   | -              |
| 36|  IO22|GPIO22| VSPI-4WP | U0-RTS|  I2C-SCL | ADS1115/BMS    |
| 37|  IO23|GPIO23| VSPI-MOSI|       | SPI0-MOSI|ePD/SD/LoRa MOSI|
| 38|   GND|      |          |       |       GND| -              |
*/
//*******************************************************************
#ifndef BEEIOT_h
#define BEEIOT_h

#include <stdlib.h>
#include <stdint.h>



//*******************************************************************
// Device configuration Matrix field (default: all active)
// 0 = active, uncomment = inactive
//*******************************************************************
// Define if ESP32 WROOM32, or WROVER-B is used
// (Select only one define !)
// #define WROVERB		// use IO Pinning for WROVERB: IO 16+17: NC (subst. by 4 + 15)
#define WROOM			// use of WROOM32 Chip type
// #define BEACON			// Work in Beacon Mode only -> Send LoRa Beacon only.

// Same EPD Definition may work for B/W and B/W/R displays if red is not used -> faster
#define EPD_BW				// Define EPD Type: Black/White only
//*******************************************************************

// Specify workOn Modules of setup() and main loop()
#ifdef WROVERB
// ESP32 WROVER-B (-> with less GPIO ->see EPD pinning)
//#define HX711_CONFIG
//#define ADS_CONFIG
//#define ONEWIRE_CONFIG
//#define WIFI_CONFIG
//#define NTP_CONFIG
//#define SD_CONFIG
#define EPD_CONFIG
#define LORA_CONFIG
#else
#ifdef WROOM

#ifdef BEACON
// ESP32 WROOM in beacon Mode -> Frequent Lora Connect only
#define EPD_CONFIG
#define LORA_CONFIG
#define SD_CONFIG	// for test purpose only (not needed for beacon mode)

#define BEACONFRQ	10		// send beacon each 10 sec.
#define BEACONCHNCFG 0		// Set beacon channel config table Index
// SleepModes: =0 initial startup needed(after reset),
// =1 after deep sleep; =2 after light sleep; =3 ModemSleep Mode; =4 Active Wait Loop
#define BEACONSLEEP  1		// Beacon Sleep Mode: 1 = DeepSleep, 2= Light SLeep

#else	// ESP32 WROOM BeeHive Mode (Default)
#define HX711_CONFIG
#define ADS_CONFIG
#define ONEWIRE_CONFIG
// #define WIFI_CONFIG
// #define NTP_CONFIG
#define SD_CONFIG
#define EPD_CONFIG
#define LORA_CONFIG
#endif	// Beacon
#endif	// WROOM
#endif	// WROVERB

//*******************************************************************
// Pin mapping when using SDCARD in SPI mode.
// With this mapping, SD card can be used both in SPI and 1-line SD mode.

// HSPI not used here -> IO ports reused for STd. GPIO
// #define HSPI_MISO   GPIO_NUM_12    // PIN_NUM_MISO
// #define HSPI_MOSI   GPIO_NUM_13    // PIN_NUM_MOSI
// #define HSPI_SCK    GPIO_NUM_14    // PIN_NUM_CLK
// #define HSPI_CS     GPIO_NUM_15    // PIN_NUM_CS

// ESP32 default SPI port pins for SD/EPD/BEE:
#define VSPI_MISO   MISO  // PIN_NUM_MISO    = 19
#define VSPI_MOSI   MOSI  // PIN_NUM_MOSI    = 23
#define VSPI_SCK    SCK   // PIN_NUM_CLK     = 18
#define VSPI_CS     SS    // PIN_NUM_CS      = 5

#define SD_MISO     VSPI_MISO  // SPI MISO -> VSPI = 19
#define SD_MOSI     VSPI_MOSI  // SPI MOSI -> VSPI = 23
#define SD_SCK      VSPI_SCK   // SPI SCLK -> VSPI = 18
#define SD_CS       GPIO_NUM_2 // SD card CS line - arbitrary selection !

// reused by BEE_RST: Green LED not used anymore
//#define LED_GREEN   14    // GPIO number of green LED

// HX711 ADC GPIO Port to Espressif 32 board
#define HX711_DT    GPIO_NUM_25    // serial dataline
#define HX711_SCK   GPIO_NUM_26    // Serial clock line

// Used I2C Port: 0
#define I2C_PORT	I2C_NUM_0		// Default I2C port for all i2c Devices
#define I2C_SDA		GPIO_NUM_21    // def: SDA=21	common for all I2C dev.
#define I2C_SCL		GPIO_NUM_22    // def. SCL=22	common for all I2C dev.

// for ADS only:
#define ADS_ALERT   GPIO_NUM_27    // arbitrary selection of ALERT line

// OneWire Data Port:
#define ONE_WIRE_BUS GPIO_NUM_32

// WavePaper ePaper port
// mapping suggestion for ESP32 DevKit or LOLIN32, see .../variants/.../pins_arduino.h for your board
// Default: BUSY -> 4,       RST -> 16, 	  DC  -> 17, 	CS -> SS(5),
// 			CLK  -> SCK(18), DIN -> MOSI(23), GND -> GND, 3.3V -> 3.3V
#define EPD_MISO	VSPI_MISO 	// SPI MISO -> VSPI
#define EPD_MOSI	VSPI_MOSI 	// SPI MOSI -> VSPI
#define EPD_SCK		VSPI_SCK  	// SPI SCLK -> VSPI
#define EPD_CS		GPIO_NUM_5  // SPI SS   -> VSPI
#ifdef WROVERB					// If ESP32 WROVERB is used IO16+17 are internally used.
#define EPD_DC    GPIO_NUM_15		// DC use of LED_RED IO PIN !
#define EPD_RST   GPIO_NUM_4		// RST use of EPD_BUSY PIN !
#define EPD_BUSY  GPIO_NUM_39     	// No BUSY Mode !
#define LED_RED   -1  			  	// GPIO number of red LED
#else
#define EPD_DC    GPIO_NUM_17		// arbitrary selection of DC   > def: 17
#define EPD_RST   GPIO_NUM_16		// arbitrary selection of RST  > def: 16
#define EPD_BUSY  GPIO_NUM_4     	// arbitrary selection of BUSY > def:  4  -> if 35 -> RD only GPIO !
#define LED_RED   GPIO_NUM_15    	// GPIO number of red LED
#endif
#define EPD_KEY1  GPIO_NUM_0     	// via 40-pin RPi slot at ePaper Pin29 (P5)
#define EPD_KEY2  EN     			// via 40-pin RPi slot at ePaper Pin31 (P6)
#define EPD_KEY3  GPIO_NUM_34     	// via 40-pin RPi slot at ePaper Pin33 (P13)
#define EPD_KEY4  GPIO_NUM_35     	// via 40-pin RPi slot at ePaper Pin35 (P19)

// LoRa-Bee Board
#define BEE_MISO VSPI_MISO	// SPI MISO -> VSPI:	19
#define BEE_MOSI VSPI_MOSI	// SPI MOSI -> VSPI:	23
#define BEE_SCK  VSPI_SCK	// SPI SCLK -> VSPI: 	18
#define BEE_CS   GPIO_NUM_12	// CS = NSS
#define BEE_RST	 GPIO_NUM_14  	//
#define BEE_DIO0 GPIO_NUM_33	// RXDone, TXDone - Main Lora_Interrupt line
#define BEE_DIO1 GPIO_NUM_13	// RXTout - FSK
#define BEE_DIO2 GPIO_NUM_34	// not used by BEE_Lora;  EPD K3 -> but is a RD only GPIO !


// Definitions of LogLevel masks instead of verbose mode (for uint16_t bitfield)
#define LOGBH		1		// 1:   Behive Setup & Loop program flow control
#define LOGOW		2		// 2:   1-wire discovery and value read
#define LOGHX		4		// 4:   HX711 init & get values
#define LOGEPD		8		// 8:   ePaper init & control
#define LOGLAN		16		// 16:  Wifi init & LAN Import/export in all formats and protocols
#define LOGSD		32		// 32:  SD Card & local data handling
#define LOGADS		64              // 64:  ADS BMS monitoring routines /w ADS1115S
#define LOGSPI		128		// 128: SPI Init
#define LOGLORAR	256		// 256: LoRa Init: Radio class
#define LOGLORAW	512		// 512: LoRa Init: BeeIoT-WAN (NwSrv class)
#define LOGQUE		1024	//1024: MsgQueue & MsgBuffer class handling
#define LOGJOIN		2048	//2048: JOIN service class
#define LOGBIOT		4096	//4096: BIoT	Application class
#define LOGGH		8192	//8192: GH		Application class
#define LOGTURTLE  16384	//16384:Turtle	Application class

#define	BHLOG(m)	if(lflags & m)	// macro for Log evaluation (type: uint)

#define NETWORKSTATE_LOGGED       1
#define NETWORKSTATE_NOTLOGGED    0
#define SDLOGPATH	"/logdata.txt"				// path of logfile for sensor data set bursts

#define NODESTATE_RESET                    3    // S3 = connection + subscription established after user reset
#define NODESTATE_PING                     2    // S2 = connection still open, successful ping
#define NODESTATE_OK                       1    // S1 = connection + subscription established
#define NODESTATE_NOTSPECIFIEDERROR        0    // E0 = unspecified error
#define NODESTATE_NOTCPCONNECTION         -1    // E1 = connection not established because of no tcp connection to test broker
#define NODESTATE_NOMQTTCONNECTION        -2    // E2 = connection not established because broker rejected MQTT connection attempt
#define NODESTATE_NOMQTTSUBSCRIPTION      -3    // E3 = broker rejected subscription attempt
#define NODESTATE_NOPING                  -4    // E4 = ping was not successful, connection lost

// Battery thresholds for LiPo 3.7V battery type
#ifndef BATTERY_MAX_LEVEL
    #define BATTERY_MAX_LEVEL        4130 // mV
    #define BATTERY_MIN_LEVEL        3200 // mV
    #define BATTERY_SHUTDOWN_LEVEL   3170 // mV
#endif


//*******************************************************************
// Global data declarations
//*******************************************************************
#define DROWNOTELEN	129
#define LENTMSTAMP	20
typedef struct {				// data elements of one log line entry
    int     index;
    char  	timeStamp[LENTMSTAMP]; // time stamp of sensor row  e.g. 'YYYY\MM\DD HH:MM:SS'
	float	HiveWeight;			// weight in [kg]
	float	TempHive;			// internal temp. of bee hive
	float	TempExtern;			// external temperature
	float	TempIntern;			// internal temp. of weight cell (for compensation)
	float	TempRTC;			// internal temp. of RTC module
	int16_t ESP3V;				// ESP32 DevKit 3300 mV voltage level
	int16_t Board5V;			// Board 5000 mV Power line voltage level
	int16_t BattCharge;			// Battery Charge voltage input >0 ... 5000mV
	int16_t BattLoad;			// Battery voltage level (typ. 3700 mV)
	int16_t BattLevel;			// Battery Level in % (3200mV (0%) - 4150mV (100%))
	char	 comment[DROWNOTELEN];
} datrow;

#define datasetsize	4			// max. # of dynamic dataset buffer: each for "looptime" seconds
#define LENFDATE 	21			// length of ISO8601 TimeSTamp (BIoTWan.h)
#define LENDATE		11
#define LENTIME		9
#define LENIPADDR	16
typedef struct {
	// save timestamp of last datarow entry:
    char	formattedDate[LENFDATE]; // Variable to save date and time; 2019-10-28T08:09:47Z
    char	date[LENDATE];  	// stamp of the day: 2019\10\28
    char	time[LENTIME]; 		// Timestamp: 08:10:15
    char	ipaddr[LENIPADDR];	// IPv4 Address xxx:xxx:xxx:xxx
    int     loopid;             // sensor data read sample ID
	int		laps;				// # of hangovers till datasetsize reached by loopid++
	// Board Identification data
	uint64_t  BoardID;  		// unique Identifier (=MAC) of MCU board (use only lower 6By. (of8)
	int		  chipID;			// get chiptype: 0=WROOM32, 1=WROVER-B, ...
	esp_chip_info_t chipTYPE;	// get chip board type and revision -> relevant for sytem API vaildation
	datrow	dlog[datasetsize];	// all sensor logs till upload to server
	// for beacon mode
	int		rssi;
	int		snr;
} dataset;


//*******************************************************************
// Global Helper functions declaration
//*******************************************************************
int setup_hx711Scale(int mode);
int setup_owbus		(int mode);
int setup_wifi		(int mode);
int setup_ntp		(int mode);
int setup_i2c_ADS	(int mode);
int setup_i2c_MAX	(int mode);
int setup_rtc		(int mode);		// in rtc.cpp
int setup_spi_VSPI	(int mode);		// in multiSPI.cpp
int setup_sd		(int mode);		// in sdcard.cp
int setup_epd		(int mode);		// in epd.cpp

// in hx711Scale.cpp
float   HX711_read  (int mode);

// in wifi.cpp
void    wifi_scan   (void);
int     wifi_connect(const char * ssid, const char * pwd, const char* hostname);
int 	wifi_disconnect();
int		WiFi_AccessPointStart(char* AccessPointNetworkSSID);
void 	WiFi_SetBothModesNetworkStationAndAccessPoint();
String 	WiFi_GetOwnIPAddressInRouterNetwork();

// Draft functions
void 	Webserver_Start();
String 	Webserver_GetRequestGETParameter();
void 	Webserver_SendHTMLPage(String HTMLPage);
String 	EncodeFormHTMLFromValues(String TitleOfForm, int CountOfConfigValues);
int 	DecodeGETParameterAndSetConfigValues(String GETParameter);
int 	ConnectToATT();
void 	SendSensorDateToATT(String SensorName, byte SensorDate);

// in rtc.cpp
int 	ntp2rtc		(void);
int 	getRTCtime	(void);
void	rtc_test	(void);

// in getntp.cpp
int    	getTimeStamp(void);
void	printLocalTime(void);

// in owbus.cpp
void 	GetOWsensor	(int sample);

// in main.cpp
void	Logdata     (void);
void	mydelay		(int32_t tval);

// in max123x.cpp
uint16_t adc_read(int channel);

// epd.cpp functions
void drawBitmapFromSD(const char *filename, int16_t x, int16_t y, bool with_color = true);
void drawBitmaps_200x200();
void drawBitmaps_other(void);
void showdata		(int sampleID);
void showbeacon 	(int sampleID);

// end of BeeIoT.h
#endif // BeeIoT_h
