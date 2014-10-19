/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */

#define dotPeriod 100
#define dashPeriod (dotPeriod*3)
#define relaxTime (dotPeriod)
#define letterSpace (dotPeriod*2)
#define wordSpace (dotPeriod*4)
#define wordEnd (wordSpace*4)
#define output 0

String text = "ricardo";

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(output, OUTPUT);     
}

void dot() {
  custom_beep(dotPeriod);
}

void dash() {
  custom_beep(dashPeriod);
}

void custom_beep(int period){
  int starttime = millis();
  int endtime = starttime;
  while ((endtime - starttime) <= period) // do this loop for up to 1000mS
  {
  digitalWrite(output, HIGH);
  //delay(100);
  delayMicroseconds(100);
  digitalWrite(output, LOW);
  //delay(100);
  delayMicroseconds(100);
  endtime = millis();
  }
  delay(relaxTime);
}

// the loop routine runs over and over again forever:
void loop() {
  for(int i=0; i<=text.length(); i++){
    processLetter(text.charAt(i));
  }
  delay(2000);
}


void processLetter(char character) {
  
  switch (character) {
   case 'a':
     dot();dash();
   break;
   case 'b':
     dash();dot();dot();dot();
   break;
   case 'c':
     dash();dot();dash();dot();
   break;
   case 'd':
     dash();dot();dot();
   break;
   case 'e':
     dot();
   break;
   case 'f':
     dot();dot();dash();dot();
   break;
   case 'g':
     dash();dash();dot();
   break;
   case 'h':
     dot();dot();dot();dot();
   break;
   case 'i':
     dot();dot();
   break;
   case 'j':
     dot();dash();dash();dash();
   break;
   case 'k':
     dash();dot();dash();
   break;
   case 'l':
     dot();dash();dot();dot();
   break;
   case 'm':
     dash();dash();
   break;
   case 'n':
     dash();dot();
   break;
   case 'o':
     dash();dash();dash();
   break;
   case 'p':
     dot();dash();dash();dot();
   break;
   case 'q':
     dash();dash();dot();dash();
   break;
   case 'r':
     dot();dash();dot();
   break;
   case 's':
     dot();dot();dot();
   break;
   case 't':
     dash();
   break;
   case 'u':
     dot();dot();dash();
   break;
   case 'v':
     dot();dot();dot();dash();
   break;
   case 'w':
     dot();dash();dash();
   break;
   case 'x':
     dash();dot();dot();dash();
   break;
   case 'y':
     dash();dot();dash();dash();
   break;
   case 'z':
     dash();dash();dot();dot();
   break;
   case ' ':
     delay(wordSpace);
    break;
  }
  delay(letterSpace);
}
