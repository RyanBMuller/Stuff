int lightPin = A0;  //Define Analog Input Pin for PhotoResistor
int ledPin=A1;     //Define Analog Pin for LED
float MaxVal = 0; //Define Max Value of PhotoResistor
float MinVal = 0; //Define Min Value of PhotoResistor
int LightVal = 0; //Define Current Reading of PhotoResistor
float Slope = 0; //Define Slope of Light Emitted vs Light Collected
float Brightness = 0; //Brightness of the LED between 0 and 255
int YIntercept = 0; //Y Intercept to Keep Brightness Between 0 and 255

void setup()
{
    Serial.begin(9600);  //Pour a Bowl of Cereal
    pinMode(ledPin, OUTPUT ); //LED Pin is an Output
    pinMode(lightPin, INPUT); //PhotoResistor is an Input
    delay(1000); //Delay One Second
    if (MaxVal == 0){ //Set the Max and Min Values to Current PhotoResistor Value
      MaxVal = analogRead(lightPin);
      MinVal = analogRead(lightPin);
    }
    delay(1000); //Delay One Second
}

void loop()
{
    LightVal = analogRead(lightPin); //Read Current Value
    if (LightVal > MaxVal) { //If the Value is Greater than Any Previous Value
      MaxVal = LightVal; //Set it as the New Max Value
    }
    if (LightVal < MinVal) { //If the Value is Less than Any Previous Value
      MinVal = LightVal; //Set it as the New Min Value
    }
    if (MaxVal > MinVal) { //Once the Max and Min Values are Different
      Slope = 255 /(MaxVal-MinVal); //Determine the Slope of the Line (y2-y1)/(x2-x1) Where Delta Y is 255
    }
    YIntercept = (Slope*MinVal); //Determine the Point at Which the Line Crosses the Y Axis
    Brightness = (Slope * LightVal)-YIntercept; //Y=MX+B Where The Brightness is a Value from 0 to 255 Based on the Slope, Current Reading, and the Y Intercept
    analogWrite(ledPin, Brightness); //Make the LED the Value of Brightness
    delay(100); //Delay for Sanity
}
