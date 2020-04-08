unsigned long lastMillis_readSensor;
unsigned long lastMillis_checkHiVal;
unsigned long lastMillis_buildNewSpeed;
unsigned long lastMillis_simulate;
unsigned long lastMillis_decreaseFanSpeed;

int sensorValue = 10000;
int highestValue = 0;
int currentValue = 10000;
int dreceasingFanSpeedMillis = 100; // millisecond interval in which currentValue will be decreased by 1
int minimalValue = 1;               // treshol value so smal curent changes dosn't start SetUpNewSpeed(); function
float timeToBuildUpNewSpeed = 2.5;  // change this value to increase the time, so the fans can reach the highes sensor value
bool newhigGestValue = false;
bool firstFrameSetupSpeed = false;
bool fansAreBuildingUp = false;
bool fansAreDecreasingSpeed = false;

void setup(){
      
    Serial.begin(57600);
 Serial.println("start");
}

void loop()
{
    ReadSensor();
    CheckHighestValue();
    if (newhigGestValue)
    {
        SetupNewSpeed();
    }

    if (!newhigGestValue && !fansAreBuildingUp)
    {
        DecreasingFanSpeed();
    }
}



void DecreasingFanSpeed()
{
    if (millis() - lastMillis_decreaseFanSpeed > dreceasingFanSpeedMillis)
    {
        currentValue--;
        lastMillis_decreaseFanSpeed = millis();
    }
    if(currentValue <= minimalValue){
        fansAreDecreasingSpeed = false;
    }
    //Serial.println(currentValue);
}

void SetupNewSpeed()
{   
    // functions Setup
    if (firstFrameSetupSpeed)
    {
        lastMillis_buildNewSpeed = millis();
        firstFrameSetupSpeed = false;
        fansAreBuildingUp = true;
    }

    // time to finish building up the new speed
    if (millis() - lastMillis_buildNewSpeed > 2500)
    {
        fansAreBuildingUp = false;
        highestValue = false;
        fansAreDecreasingSpeed = true;
    }
}

void CheckHighestValue()
{
    if (sensorValue > highestValue)
    {
        Serial.println("new highestValue: "+ sensorValue);
        highestValue = sensorValue;
    }

    // register if ther's a new higest value in 1000 milliseconds
    if (millis() - lastMillis_checkHiVal > 1000)
    {
        if (highestValue > minimalValue)
        {
            newhigGestValue = true;
            firstFrameSetupSpeed = true;
            currentValue = newhigGestValue; // convertation needed !!
            fansAreDecreasingSpeed = false;
        }
        lastMillis_checkHiVal = millis();
    }
}

void ReadSensor()
{
    if (millis() - lastMillis_readSensor > 200)
    {
        SimulateSensorValue();
        lastMillis_readSensor = millis();
    }
}

void SimulateSensorValue()
{
    if (millis() - lastMillis_simulate > 200)
    {
        lastMillis_simulate = millis();
        sensorValue = random(0, 1024);
        // Serial.println("new sensor valu: "+ sensorValue)
    }
}
