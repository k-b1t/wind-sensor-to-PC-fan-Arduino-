/*
#define analogPinForRV 1 // change to pins you the analog pins are using
#define analogPinForTMP 0
const float zeroWindAdjustment = .2; // negative numbers yield smaller wind speeds and vice versa.
int TMP_Therm_ADunits;               //temp termistor value from wind sensor
float RV_Wind_ADunits;               //RV output from wind sensor
float RV_Wind_Volts;
unsigned long lastMillis;
int TempCtimes100;
float zeroWind_ADunits;
float zeroWind_volts;
float WindSpeed_MPH;



float maxWindSpeed = 50.00; // <---------------------- ieraksti maximālo vēju ātrumu ar komatu piem: 63.55, 50.0;
int speed_ = 0;
int highestValue = 0;
bool newHighValue = true;
int slowDownValue = 1;
int lowestSpeedValue = 1;

void setup()
{
  Serial.begin(57600);
  Serial.println("start");
  pinMode(A2, INPUT);    // GND pin
  pinMode(A3, INPUT);    // VCC pin
  digitalWrite(A3, LOW); // turn off pullups
}

void loop()
{
  if (millis() - lastMillis > 200)
  { // read every 200 ms - printing slows this down further
    TMP_Therm_ADunits = analogRead(analogPinForTMP);
    RV_Wind_ADunits = analogRead(analogPinForRV);
    RV_Wind_Volts = (RV_Wind_ADunits * 0.0048828125);
    TempCtimes100 = (0.005 * ((float)TMP_Therm_ADunits * (float)TMP_Therm_ADunits)) - (16.862 * (float)TMP_Therm_ADunits) + 9075.4;
    zeroWind_ADunits = -0.0006 * ((float)TMP_Therm_ADunits * (float)TMP_Therm_ADunits) + 1.0727 * (float)TMP_Therm_ADunits + 47.172; //  13.0C  553  482.39
    zeroWind_volts = (zeroWind_ADunits * 0.0048828125) - zeroWindAdjustment;
    WindSpeed_MPH = pow(((RV_Wind_Volts - zeroWind_volts) / .2300), 2.7265);
    //PrintStuff();

    speed_ = map(WindSpeed_MPH, 0, maxWindSpeed, 0, 255);
    // check highest value

    if (speed_ >= highestValue)
    {
      highestValue = speed_;
      newHighValue = true;
    }

    // go slow
    if (newHighValue == true)
    {
     //  -= slowDownValue;
      speed_ = highestValue;
    }

    analogWrite(9, speed_);
    lastMillis = millis();
  }
}

void BuildUpSpeed()
{

}

void PrintStuff()
{
  Serial.print("  TMP volts ");
  Serial.print(TMP_Therm_ADunits * 0.0048828125);
  Serial.print(" RV volts ");
  Serial.print((float)RV_Wind_Volts);
  Serial.print("\t  TempC*100 ");
  Serial.print(TempCtimes100);
  Serial.print("   ZeroWind volts ");
  Serial.print(zeroWind_volts);
  Serial.print("   WindSpeed MPH ");
  Serial.println((float)WindSpeed_MPH);
}
*/
