#include <SoftwareSerial.h>
#include <MQ135.h>
#include "DHT.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define PIN_MQ135 A2
MQ135 mq135_sensor = MQ135(PIN_MQ135);

SoftwareSerial mySerial(0, 1); // RX, TX

float temperature = 21.0; // assume current temperature. Recommended to measure with DHT22
float humidity = 25.0; // assume current humidity. Recommended to measure with DHT22

#define DHTPIN 3    // what digital pin we're connected to

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

// --------------- Setup
void setup()
{

  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only

  }
  
  reference();
  dht.begin();

  // Start up the library
  sensors.begin();

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
}

void loop() {
  // Give it time to calibrate
  delay(2000);

  // run over and over
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }

  float rzero = mq135_sensor.getRZero();
  float correctedRZero = mq135_sensor.getCorrectedRZero(temperature, humidity);
  float resistance = mq135_sensor.getResistance();
  float ppm = mq135_sensor.getPPM();
  float correctedPPM = mq135_sensor.getCorrectedPPM(temperature, humidity);

  float h = dht.readHumidity();
  // Read Celsius
  float t = dht.readTemperature();
  // Read Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check errors
  if (isnan(h) || isnan(t) || isnan(f)) {
   Serial.println("Failed to read from sensors!");
    return;
  }

//  Serial.println("Start of reading data from New interval  ");
//  Serial.println(" ");
//  Serial.println("Gas concentration reading from exhaust");
//  Serial.println("  ");
//  Serial.println("Other gas concentration from gas exhaust in ppm");
//  Serial.print("MQ135 RZero: ");
//  Serial.print(rzero);
//  Serial.print("\t Corrected RZero: ");
//  Serial.print(correctedRZero);
//  Serial.print("\t Resistance: ");
//  Serial.print(resistance);
//  Serial.print("\t PPM: ");
//  Serial.print(ppm);
//  Serial.print("\t Corrected PPM: ");
//  Serial.print(correctedPPM);
//  Serial.println("ppm");
  Serial.println("  ");

//  Serial.println("Inside Engine Probe Temprature");
//  // call sensors.requestTemperatures() to issue a global temperature
//  // request to all devices on the bus
//  Serial.print("Requesting temperatures from probe sensor ...");
  sensors.requestTemperatures(); // Send the command to get temperatures
//Serial.println("DONE");
  Serial.println("  ");
//Serial.print("Temperature form the Engine is: ");
  Serial.println(sensors.getTempCByIndex(0));

  Serial.println("  ");
//Serial.println("Temperature and Humidity from Engine compartment");
  Serial.println("  ");
//Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %.");
  Serial.println("  ");
//Serial.print("Temperature in Celsius : ");
  Serial.print(t);
//Serial.println(" Degrees Celsius");
  Serial.println("  ");
//Serial.print("Temperature in Fahrenheit : ");
  Serial.print(f);
//Serial.println(" Degrees Fahrenheit ");
  Serial.println("  ");
//Serial.println(" End of reading data from Previous interval  ");
  Serial.println("  ");
}
void reference()
{
//Serial.println (">> --------------------------- <<");
  delay (2000);
}

