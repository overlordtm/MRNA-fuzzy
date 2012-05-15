#pragma config(Sensor, S3,     lightSensor,         sensorLightActive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*--------------------------------------------------------------------------------------------------------*\
|*                                                                                                        *|
|*                                           - Line Tracker -                                             *|
|*                                            ROBOTC on NXT                                               *|
|*                                                                                                        *|
|*  This program allows your taskbot to follow a line in reverse.                                         *|
|*                                                                                                        *|
|*                                        ROBOT CONFIGURATION                                             *|
|*    NOTES:                                                                                              *|
|*    1)  The Light Sensor is attached to the back of the robot.                                          *|
|*    2)  Be sure to take readings of your Light Sensor over the light and dark areas.  Once you have     *|
|*        the values, add them and divide by 2 to find your threshold.  Then, use your threshold as a     *|
|*        comparison in your program.                                                                     *|
|*                                                                                                        *|
|*    MOTORS & SENSORS:                                                                                   *|
|*    [I/O Port]              [Name]              [Type]              [Description]                       *|
|*    Port B                  motorB              NXT                 Right motor                         *|
|*    Port C                  motorC              NXT                 Left motor                          *|
|*    Port 1                  lightSensor         Light Sensor        Back mounted                        *|
\*---------------------------------------------------------------------------------------------------4246-*/

/*
* Fuzzy logic Line Tracking
* Project MRNA
*
*/

#define K 10
#define STEP 100/K

float Desno[K];
float Levo[K];
float Y[K];

int levi;
int desni;

float max(float a, float b) {
  if(a>b) {
    return a;
  } else {
     return b;
  }
}

float min(float a, float b) {
  if(a>b) {
    return b;
  } else {
    return a;
  }
}

float crno(float x) {
  return max((-0.75/50)*x+1, 0);
}

float belo(float x) {
  return max((0.75/50)*x-0.5, 0);
}

float desno(float x) {
  return max((0.75/50)*x-0.5, 0);
}

float levo(float x) {
  return max((-0.75/50)*x+1, 0);
}

void fill_array() {
  for(int i = 0; i < K; i++) {
    Desno[i] = desno(i*STEP);
    Levo[i] = levo(i*STEP);
  }
}

task main()
{
    fill_array();
    wait1Msec(50);                        // The program waits 50 milliseconds to initialize the light sensor.

   while(true)                           // Infinite loop
   {
      int input = (int)((SensorValue[lightSensor]-30.0)/40.0*100.0);

      nxtDisplayTextLine(0, "Input je %d", input);

      float R1 = belo(input);
      float R2 = crno(input);

      float sum = 0;
      float sum2 = 0;

      for(int i = 0; i < K; i++) {
        Y[i] = max(min(R1, Desno[i]), min(R2, Levo[i]));
        sum += Y[i] * i*STEP;
        sum2 += Y[i];
       }

       float cog = sum/sum2;
       levi = -(int)cog;
       desni = (int)cog-100;

       nxtDisplayTextLine(1, "COG je %f", cog);
       nxtDisplayTextLine(2, "sum je %f", sum);
       nxtDisplayTextLine(3, "sum2 je %f", sum2);
       nxtDisplayTextLine(4, "levi je %d", levi);
       nxtDisplayTextLine(5, "desni je %d", desni);

       // nxtDisplayTextLine(1, "Stanje motorja %d", nMotorRunState[motorB]);


       motor[motorB] = desni;
       motor[motorC] = levi;
    }
}
