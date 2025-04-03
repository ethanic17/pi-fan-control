#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pigpio.h>


int PWM_PIN = 18;
int PWM_FREQ = 25000;

float get_aputemp() {
    FILE *fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    
    int temp = 0;

    if (fscanf(fp, "%d", &temp) != 1) {
        printf("Error reading temperature\n");
        fclose(fp);
        return -1.0f;
    }

    fclose(fp);
    return temp / 1000.0f;
}

int main() {

    if (gpioInitialise() < 0) {
        printf("Error initializing GPIO - pigpio \n");
        return 1;
    }

    gpioHardwarePWM(PWM_PIN, PWM_FREQ, 0);

    if (get_aputemp() == -1.0f) {
        printf("Error reading temperature\n");
        return 1;
    }

    while(1) {
        float temp = get_aputemp();
        if (temp <= 55.0f) {
            gpioHardwarePWM(PWM_PIN, PWM_FREQ, 400000); //40% -- set to 0 for off
            sleep(5);
        }
        else if (temp > 55.0f && temp <= 60.0f) { 
            gpioHardwarePWM(PWM_PIN, PWM_FREQ, 500000); //50%
            sleep(5);
        } 
        else if (temp > 60.0f && temp <= 65.0f) {
            gpioHardwarePWM(PWM_PIN, PWM_FREQ, 700000); //70%
            sleep(5);
        } 
        else if (temp > 65.0f) {
            gpioHardwarePWM(PWM_PIN, PWM_FREQ, 1000000); //100%
            sleep(5);
        } 
    }

    gpioHardwarePWM(PWM_PIN, PWM_FREQ, 0); 
    gpioTerminate();                
    return 0;
}