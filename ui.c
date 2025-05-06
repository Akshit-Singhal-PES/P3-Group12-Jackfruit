#include "sleep_data.h"

void show_main_menu() {
    printf("\n===== Sleep Tracker Menu =====\n");
    printf("1. Add Sleep Entry\n");
    printf("2. View Sleep Log\n");
    printf("3. Weekly Report\n");
    printf("4. Set Alarm\n");
    printf("5. Estimate Sleep Stages\n");
    printf("6. Search Notes\n");
    printf("7. Exit\n");
}

void search_notes() {
    char keyword[50];
    printf("\nEnter keyword to search in notes: ");
    scanf("%49s", keyword);

    printf("\n=== Search Results ===\n");
    int found = 0;

    for(int i = 0; i < entry_count; i++) {
        if(strstr(entries[i].notes, keyword) != NULL) {
            printf("Date: %s - Note: %s\n", entries[i].date, entries[i].notes);
            found = 1;
        }
    }

    if(!found) {
        printf("No entries found with that keyword.\n");
    }
}