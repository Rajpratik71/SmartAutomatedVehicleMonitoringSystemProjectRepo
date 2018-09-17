#include "DHT.h"
#include <OneWire.h>
#include <DallasTemperature.h>

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

DHT dht(DHTPIN, DHTTYPE);

// declaring variable initial values.
int minor_value = 80;
int largest_value = 350;

// --------------- Setup
void setup()
{

  Serial.begin(9600);
  reference();
  dht.begin();

  // Start up the library
  sensors.begin();
}

void loop() {
  // Give it time to calibrate
  delay(2000);

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

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.println("Start of reading data from New interval  ");
  Serial.println(" ");
  Serial.println("Gas concentration reading from exhaust");
  int mq7 = analogRead (2);
  // reference: map (read value, lowest_valid_value, highest_validvalue, minimum%, max%)
  mq7 = map (mq7, minor_value, largest_value, 0, 100);
  Serial.print (mq7);
  Serial.println ("% CO in air");
  Serial.println("  ");

  Serial.println("Inside Engine Probe Temprature");
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print("Requesting temperatures from probe sensor ...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  Serial.println("  ");
  Serial.print("Temperature form the Engine is: ");
  Serial.println(sensors.getTempCByIndex(0));

  Serial.println("  ");
  Serial.println("Temperature and Humidity from Engine compartment");
  Serial.println("  ");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %.");
  Serial.println("  ");
  Serial.print("Temperature in Celsius : ");
  Serial.print(t);
  Serial.println(" Degrees Celsius");
  Serial.println("  ");
  Serial.print("Temperature in Fahrenheit : ");
  Serial.print(f);
  Serial.println(" Degrees Fahrenheit ");
  Serial.println("  ");
  Serial.println(" End of reading data from Previous interval  ");
  Serial.println("  ");
}

// ---------------------------- Functions:
void func_adjustment(int mq7) // Simple automatic setting of maximums and minima
{
if (mq7> largest_value)
{
  largest_value = mq7;
}
if(mq7 <minor_value)
{
  minor_value = mq7;
}
}
void reference()
{
  //Serial.println (">> --------------------------- <<");
  delay (2000);
}
