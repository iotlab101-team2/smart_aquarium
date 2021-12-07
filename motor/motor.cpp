#include "motor.h"

 Servo servo;

const int pin = 15;
unsigned long interval = 1000;
int count = 0;
int cycle_count =0;
int flag = 0;
int flag1 = 0;
int start = 0;
int cycle_flag = 0;

void Servo_sensor(int *feed_num,int *feed_cycle){
    unsigned long currentMillis = millis();
    servo.attach(pin);

    if(currentMillis - interval >= 1000)
    {
        interval = currentMillis;
        count++;
        cycle_count++;
    }

    if(*feed_cycle>0 && cycle_flag == 0)
    {
        cycle_count = 0;
        cycle_flag = 1;
    }
    else if(cycle_flag == 1 && cycle_count>= 10*(*feed_cycle))
    {
        *feed_num = *feed_num + 1;
        cycle_flag =0;
    }

    if(*feed_num>0)
    {
        if(flag1 == 0 && start == 0)
        {
            servo.write(180);
            count = 0;
            flag = 1;
            flag1 = 1;
            Serial.println("남은회수 = "+String(*feed_num)+"회");
        }
        else if(count>=1 && flag1 == 0)
        {
            servo.write(180);
            count =0;
            flag1 = 1;
            flag = 1;
        }         
    }

    if(count>=1 && flag ==1)  
    {    
        flag = 0;
        flag1 = 0;
        count = 0;
        servo.write(0);
        *feed_num = *feed_num - 1;
        Serial.println("남은회수 = "+String(*feed_num)+"회");
        if(*feed_num > 0)
            start = 1;
        else
            start = 0;
    }
}
