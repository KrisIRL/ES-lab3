#include "mbed.h"
#include "MMA7660.h"
#include "C12832.h"

float PI = 3.14159265;
int Average[5];
double res;

MMA7660 MMA(p28, p27);
C12832 lcd(p5, p7, p6, p8, p11);

DigitalOut connectionLed(LED1);

float calculateAngle(float x, float y, float z){
    float angle = 0;
    double val = 180.0 / PI;
    double bott_part = sqrt(pow((double)y, 2.0) + pow((double)z, 2.0));
    double top_part = (double)x;
    angle = atan(top_part/bott_part);
    return angle*val;
}

int main() {
    if (MMA.testConnection())
        connectionLed = 1;

    lcd.cls();
    lcd.locate(0,0);
    lcd.printf("MMA7660 Test\n");

    while(1) {
        double res1 = calculateAngle(MMA.x(), MMA.y(), MMA.z());
        wait(0.05);
        double res2 = calculateAngle(MMA.x(), MMA.y(), MMA.z());
        wait(0.05);
        double res3 = calculateAngle(MMA.x(), MMA.y(), MMA.z());
        wait(0.05);
        double res4 = calculateAngle(MMA.x(), MMA.y(), MMA.z());
        wait(0.05); 
        double res5 = calculateAngle(MMA.x(), MMA.y(), MMA.z());
        wait(0.05);
        
        float avg_res = (res1 + res2 + res3 + res4 + res5)/5;
        lcd.cls();
        lcd.locate(0,0);
        lcd.printf("Angle: %5.2f", avg_res);
        printf("Average angle is: %f \n\r", avg_res);
        wait(1);
    }
}
