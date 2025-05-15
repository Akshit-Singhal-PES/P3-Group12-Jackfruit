#include "sleep_data.h"

SleepEntry entries[MAX_ENTRIES];
int entry_count = 0;

int is_valid_date(const char *date) {
    if (strlen(date) != 10) return 0;
    int year, month, day;
    if (sscanf(date, "%d-%d-%d", &year, &month, &day) != 3) return 0;
    return (year >= 1900) && (month >= 1 && month <= 12) && (day >= 1 && day <= 31);
}

void load_from_file() {
    FILE *file = fopen("sleep_data.dat", "rb");
    if (!file) {
        printf("No existing data found. Starting fresh.\n");
        return;
    }

    if (fread(&entry_count, sizeof(int), 1, file) != 1) {
        printf("Error reading entry count!\n");
        entry_count = 0;
        fclose(file);
        return;
    }

    if (fread(entries, sizeof(SleepEntry), entry_count, file) != entry_count) {
        printf("Warning: Data file corrupted! Loaded partial data.\n");
    }

    fclose(file);
    printf("Loaded %d entries from previous session.\n", entry_count);
}

void save_to_file() {
    FILE *file = fopen("sleep_data.dat", "wb");
    if (!file) {
        perror("Failed to save data");
        return;
    }

    if (fwrite(&entry_count, sizeof(int), 1, file) != 1) {
        printf("Error saving entry count!\n");
    }

    if (fwrite(entries, sizeof(SleepEntry), entry_count, file) != entry_count) {
        printf("Error saving entries!\n");
    }

    fclose(file);
}

void add_sleep_entry() {
    if (entry_count >= MAX_ENTRIES) {
        printf("Error: Sleep log is full!\n");
        return;
    } else if (entry_count >= MAX_ENTRIES - 5) {
        printf("Warning: Only %d slots remaining!\n", MAX_ENTRIES - entry_count);
    }

    SleepEntry new_entry;
    char buffer[100];

    // Date input
    do {
        printf("\nEnter date (YYYY-MM-DD): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
    } while (!is_valid_date(buffer));
    strcpy(new_entry.date, buffer);

    // Sleep time
    do {
        printf("Sleep time (0-24): ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%f", &new_entry.sleep_time);
    } while (new_entry.sleep_time < 0 || new_entry.sleep_time >= 24);

    // Wake time
    do {
        printf("Wake time (0-24): ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%f", &new_entry.wake_time);
    } while (new_entry.wake_time < 0 || new_entry.wake_time >= 24);

    // Interruptions
    printf("Number of interruptions: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &new_entry.interruptions);

    // Notes
    printf("Notes: ");
    fgets(new_entry.notes, MAX_NOTES_LENGTH, stdin);
    new_entry.notes[strcspn(new_entry.notes, "\n")] = '\0';

    calculate_sleep_score(&new_entry);
    entries[entry_count++] = new_entry;
    printf("\nEntry added successfully!\n");
}

void calculate_sleep_score(SleepEntry *entry) {
    float duration = entry->wake_time - entry->sleep_time;
    if (duration < 0) duration += 24.0;

    entry->sleep_score = (int)(duration * 10) - (entry->interruptions * 5);
    if (entry->sleep_score > 100) entry->sleep_score = 100;
    if (entry->sleep_score < 0) entry->sleep_score = 0;
}

void view_sleep_log() {
    if (entry_count == 0) {
        printf("\nNo entries found.\n");
        return;
    }

    printf("\n=== Sleep Log (%d entries) ===\n", entry_count);
    for (int i = 0; i < entry_count; i++) {
        printf("\n[Entry %d]\n", i+1);
        printf("Date: %s\n", entries[i].date);
        printf("Sleep: %.2f | Wake: %.2f\n", entries[i].sleep_time, entries[i].wake_time);
        printf("Interruptions: %d | Score: %d/100\n", entries[i].interruptions, entries[i].sleep_score);
        printf("Notes: %s\n", entries[i].notes);
    }
}

void generate_weekly_report() {
    if (entry_count == 0) {
        printf("\nNo data available for reports.\n");
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
    printf("Average sleep duration: %.1f hours\n", total_duration/entry_count);
    printf("Average sleep score: %.1f/100\n", total_score/entry_count);

    if (total_score/entry_count < 50) {
        printf("\nRecommendation: Maintain consistent bedtimes and reduce screen time before sleep.\n");
    }
}