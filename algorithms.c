#include "sleep_data.h"

void estimate_sleep_stages(float duration) {
    printf("\n=== Estimated Sleep Stages ===\n");
    printf("Light Sleep: %.1f hours\n", duration * 0.5);
    printf("Deep Sleep: %.1f hours\n", duration * 0.3);
    printf("REM Sleep: %.1f hours\n", duration * 0.2);
}

void set_wakeup_alarm() {
    char buffer[10];
    int hour, minute;

    do {
        printf("\nSet alarm (HH:MM): ");
        fgets(buffer, sizeof(buffer), stdin);
    } while (sscanf(buffer, "%d:%d", &hour, &minute) != 2 || hour < 0 || hour >= 24 || minute < 0 || minute >= 60);

    printf("\nAlarm set for %02d:%02d!\n", hour, minute);
    printf("Tip: Place your device away from bed to avoid snoozing.\n");
}