/*PINS ON COLOR SENSOR
 *OE    :   A high state on Output Enable (OE) places the output in a high-impedance state for multiple-unit sharing of amicrocontroller input line. Enable for fo (active low).
 *OUT   :   Output frequency (fo).
 *S0,S1 :   Output frequency scaling selection inputs:    S0-LOW  S1-LOW     POWER DOWN
 *                                                        S0-LOW  S1-HIGH    2%
 *                                                        S0-HIGH S1-LOW     20%
 *                                                        S0-HIGH S1-HIGH    100%
 *S2,S3 :   Photodiode type selection inputs:             S2-LOW  S3-LOW     Red
 *                                                        S2-LOW  S3-HIGH    Blue
 *                                                        S2-HIGH S3-LOW     Clear(no filter)
 *                                                        S2-HIGH S3-HIGH    Green
 */

 
const int S0=2; //Color sensor's S0 pin is connected to digital pin 2 of Arduino 
const int S1=3; //Color sensor's S1 pin is connected to digital pin 3 of Arduino
const int S2=4; //Color sensor's S2 pin is connected to digital pin 4 of Arduino
const int S3=5; //Color sensor's S3 pin is connected to digital pin 5 of Arduino


