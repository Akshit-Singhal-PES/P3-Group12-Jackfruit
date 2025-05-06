#include "sleep_data.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

SleepEntry entries[MAX_ENTRIES];
int entry_count = 0;

void load_from_file() {
    FILE *file = fopen("sleep_data.dat", "rb");
    if (!file) return;

    fread(&entry_count, sizeof(int), 1, file);
    fread(entries, sizeof(SleepEntry), entry_count, file);
    fclose(file);
}

void save_to_file() {
    FILE *file = fopen("sleep_data.dat", "wb");

    if (!file) {
        printf("Error saving data!\n");
        return;
    }

    fwrite(&entry_count, sizeof(int), 1, file);
    fwrite(entries, sizeof(SleepEntry), entry_count, file);
    fclose(file);
}

void add_sleep_entry() {
    if (entry_count >= MAX_ENTRIES) {
        printf("Sleep log is full!\n");
        return;
    }

    SleepEntry new_entry;
    printf("\nEnter date (YYYY-MM-DD): ");
    scanf("%s", new_entry.date);

    printf("Enter sleep time (e.g., 22.5 for 10:30 PM): ");
    scanf("%f", &new_entry.sleep_time);

    printf("Enter wake time: ");
    scanf("%f", &new_entry.wake_time);

    printf("Number of interruptions: ");
    scanf("%d", &new_entry.interruptions);

    printf("Notes: ");
    getchar();
    fgets(new_entry.notes, MAX_NOTES_LENGTH, stdin);
    new_entry.notes[strcspn(new_entry.notes, "\n")] = '\0';

    calculate_sleep_score(&new_entry);
    entries[entry_count++] = new_entry;
    printf("Entry added!\n");
}

void view_sleep_log() {
    printf("\n=== Sleep Log ===\n");
    for (int i = 0; i < entry_count; i++) {
        printf("\nDate: %s\n", entries[i].date);
        printf("Sleep: %.2f, Wake: %.2f\n", entries[i].sleep_time, entries[i].wake_time);
        printf("Interruptions: %d\n", entries[i].interruptions);
        printf("Sleep Score: %d\n", entries[i].sleep_score);
        printf("Notes: %s\n", entries[i].notes);
    }
}

void calculate_sleep_score(SleepEntry *entry) {
    float duration = entry->wake_time - entry->sleep_time;
    if (duration < 0) duration += 24.0;

    entry->sleep_score = (int)(duration * 10) - (entry->interruptions * 5);
    if (entry->sleep_score > 100) entry->sleep_score = 100;
    if (entry->sleep_score < 0) entry->sleep_score = 0;
}

void generate_weekly_report() {
    if (entry_count == 0) {
        printf("No data available.\n");
        return;
    }

    float total_duration = 0, total_score = 0;
    for (int i = 0; i < entry_count; i++) {
        float duration = entries[i].wake_time - entries[i].sleep_time;
        if (duration < 0) duration += 24.0;
        total_duration += duration;
        total_score += entries[i].sleep_score;
    }

    printf("\n=== Weekly Report ===\n");
    printf("Average sleep: %.1f hours\n", total_duration/entry_count);
    printf("Average score: %.1f/100\n", total_score/entry_count);
}