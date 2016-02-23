/*----------------------------------------------------- 
Author:  --<>
Date: 2014-02-04
Description:

-----------------------------------------------------*/

void setup() {
    // put your setup code here, to run once:
    pinMode(13, OUTPUT);

}

void loop() {
    // put your main code here, to run repeatedly:

    blinkLED(13, 10, 100, 50);
    delay(300);

}
