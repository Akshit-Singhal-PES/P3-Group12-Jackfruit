#include "sleep_data.h"

void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void search_notes() {
    if (entry_count == 0) {
        printf("\nNo entries to search.\n");
        return;
    }

    char keyword[50];
    printf("\nSearch notes: ");
    fgets(keyword, 50, stdin);
    keyword[strcspn(keyword, "\n")] = '\0';
    to_lowercase(keyword);

    printf("\n=== Search Results ===\n");
    int found = 0;

    for (int i = 0; i < entry_count; i++) {
        char temp_note[MAX_NOTES_LENGTH];
        strcpy(temp_note, entries[i].notes);
        to_lowercase(temp_note);

        if (strstr(temp_note, keyword) != NULL) {
            printf("[%s] %s\n", entries[i].date, entries[i].notes);
            found = 1;
        }
    }

    if (!found) {
        printf("No matches found for '%s'.\n", keyword);
    }
}

void show_main_menu() {
    printf("\n===== Sleep Tracker =====\n");
    printf("1. Add Sleep Entry\n");
    printf("2. View Sleep Log\n");
    printf("3. Generate Weekly Report\n");
    printf("4. Set Wake-Up Alarm\n");
    printf("5. Estimate Sleep Stages\n");
    printf("6. Search Notes\n");
    printf("7. Exit\n");
}