#include "sleep_data.h"

void estimate_sleep_stages(float sleep_duration) {
    printf("\nEstimated Sleep Stages:\n");
    printf("Light Sleep: %.1f hours\n", sleep_duration * 0.5);
    printf("Deep Sleep: %.1f hours\n", sleep_duration * 0.3);
    printf("REM Sleep: %.1f hours\n", sleep_duration * 0.2);
}

void set_wakeup_alarm() {
    int hour, minute;
    printf("\nSet wake-up alarm (24h format)\n");
    printf("Hour: ");
    scanf("%d", &hour);
    printf("Minute: ");
    scanf("%d", &minute);
    
    printf("Alarm set for %02d:%02d\n", hour, minute);
    printf("Make sure to wake up on time for better sleep habits!\n");
}