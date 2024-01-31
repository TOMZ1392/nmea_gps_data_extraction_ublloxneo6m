#include <SoftwareSerial.h>
#define MSG_TYPE       0
#define UTC_TIME       1
#define NAV_RECV_WARN  2
#define LATITUDE_VAL   3
#define LAT_POS        4
#define LONGITUDE_VAL  5
#define LONG_POS       6
#define SPEED_KNOT     7
#define DATE           9
// choose pins that connect to UBlox Neo 6m
int RXPin = 2;
int TXPin = 3;

int GPSBaud = 9600;
SoftwareSerial gpsSerial(RXPin, TXPin);

void setup() {
  // put your setup code here, to run once:
  // define pin modes for tx, rx:
  pinMode(RXPin, INPUT);
  pinMode(TXPin, OUTPUT);
  Serial.begin(9600);
  gpsSerial.begin(9600);
  Serial.write("Welcome to the GPS Show");
}

void extractGpsData()
{
  if (gpsSerial.available()) {
    char GPSMSG[13][15];
    memset((char*)GPSMSG, '\0-', 13 * 15);
    //String buff="$GPRMC,084455.00,A,0957.78216,N,07618.35340,E,0.034,,220722,,,A*70";
    String buff = gpsSerial.readStringUntil(0x0a);
    char * msg = buff.c_str();

    if (strstr(msg, "$GPRMC"))
    {
      char *token = strtok(msg, ",");
      uint8_t idx = 0;
      while (token != NULL)
      {
        //Serial.println(token);
        strcpy((char*)&GPSMSG[idx], token);
        token = strtok(NULL, ",");
        idx++;
        if (idx == 13)
        {
          break;
        }
      }
      if (strcmp("V", GPSMSG[NAV_RECV_WARN]) == 0)
      {
        Serial.println("GPS DATA UNAVAILABLE");
      }
      else
      {
        Serial.println(GPSMSG[SPEED_KNOT]);
      }
    }


  }
}

void loop() {

  extractGpsData();
}
