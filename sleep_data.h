#ifndef SLEEP_DATA_H
#define SLEEP_DATA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_ENTRIES 100
#define MAX_NOTES_LENGTH 200

typedef struct {
    char date[11];
    float sleep_time;
    float wake_time;
    int interruptions;
    char notes[MAX_NOTES_LENGTH];
    int sleep_score;
} SleepEntry;

extern SleepEntry entries[MAX_ENTRIES];
extern int entry_count;

// Core functions
void add_sleep_entry();
void view_sleep_log();
void calculate_sleep_score(SleepEntry *entry);
void generate_weekly_report();
void save_to_file();
void load_from_file();
int is_valid_date(const char *date);

// UI functions
void show_main_menu();
void search_notes();

// Alarm and analysis
void set_wakeup_alarm();
void estimate_sleep_stages(float duration);

#endif