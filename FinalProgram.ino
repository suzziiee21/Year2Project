#include <Adafruit_TCS34725.h>
#include <Servo.h>

Adafruit_TCS34725 tcs = Adafruit_TCS34725(
  TCS34725_INTEGRATIONTIME_50MS,
  TCS34725_GAIN_4X
);

Servo miservo;   // Servo 1 (pin 9)
Servo miservo2;  // Servo 2 (pin 10)

void setup() {
  Serial.begin(115200);

  if (!tcs.begin()) {
    Serial.println("No TCS34725 found");
    while (1);
  }

  miservo.attach(9);    // Pan
  miservo2.attach(10); // Tilt

  miservo.write(0);
  miservo2.write(0);
}

void loop() {
  float red, green, blue;
  tcs.getRGB(&red, &green, &blue);

  int R = int(red);
  int G = int(green);
  int B = int(blue);

  String color = "";

  if ((R - G > 65) && (R - B > 45)) {
    color = "Red";
    miservo2.write(0);
    miservo.write(170);      
    miservo2.write(180); 
    delay(500);
    miservo2.write(0);
    delay(200); 
      
  }

  else if ((B - G > 100) && (B - R > 150)) {
    color = "Blue";
    miservo2.write(0);
    miservo.write(90);     
    miservo2.write(180);
    delay(500);
    miservo2.write(0);
    delay(200);
    
  }

  else if ((R - B > 50) && (G - B > 35)) {
    color = "Yellow";
    miservo2.write(0);
    miservo.write(0);      
    miservo2.write(180);
    delay(500);
    miservo2.write(0);
    delay(200);
   
  }
 

  Serial.print("R: "); Serial.print(R);
  Serial.print("   G: "); Serial.print(G);
  Serial.print("   B: "); Serial.print(B); 
  Serial.print("   Color: "); Serial.print(color);
  Serial.println();

  delay(300);
}
