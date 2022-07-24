#include <MQ135.h>
#include <DHT.h>
#include <DHT_U.h>
#include<Servo.h>


#define DHTPIN 7
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

float humidity;
float temperature;

int sensorValue;
int digitalValue;

Servo servo;
int pos;

void setup()
{
  servo.attach(3);
  Serial.begin(9600);
  dht.begin();
}

void loop()
{

    delay(2000);

    humidity = dht.readHumidity();
    temperature = dht.readTemperature();
    sensorValue = analogRead(0);  
    digitalValue = digitalRead(2);

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print("%, Temp: ");
    Serial.print(temperature);
    Serial.print(" Celsius");
    Serial.print(" CO2 Conc.= ");
    Serial.print(sensorValue, DEC);
    Serial.println(" PPM");


    
    delay(1000);


  if(temperature > 21.6 || temperature < 20 || humidity > 60 || humidity < 30 || sensorValue > 200)
  {
      for(pos=0;pos<=90;pos++)
      {
          servo.write(pos);
          delay(15);
      }
      delay(10000);
      for(pos=90;pos>=0;pos--)
      {
          servo.write(pos);
          delay(15);
      }
  }
     delay(10000);
}
