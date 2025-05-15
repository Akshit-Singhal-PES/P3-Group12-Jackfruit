#include "sleep_data.h"

int main() {
    int choice;
    load_from_file();  // Load existing data on startup

    printf("\n===== Sleep Tracker =====\n");
    printf("Developed by: Akshit, Adithya, Anirudh, Arabhi\n");
    printf("Version: 1.0\n\n");

    do {
        show_main_menu();
        printf("\nEnter your choice (1-7): ");

        // Robust input handling
        char input[10];
        fgets(input, sizeof(input), stdin);
        choice = atoi(input);  // Convert to integer

        // Clear any extra characters in buffer
        if (strchr(input, '\n') == NULL) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

        switch(choice) {
            case 1:
                add_sleep_entry();
                break;
            case 2:
                view_sleep_log();
                break;
            case 3:
                generate_weekly_report();
                break;
            case 4:
                set_wakeup_alarm();
                break;
            case 5:
                if (entry_count > 0) {
                    float duration = entries[entry_count-1].wake_time -
                                   entries[entry_count-1].sleep_time;
                    if (duration < 0) duration += 24.0;
                    estimate_sleep_stages(duration);
                } else {
                    printf("\nError: No sleep entries available. Add entries first.\n");
                }
                break;
            case 6:
                search_notes();
                break;
            case 7:
                save_to_file();
                printf("\nAll data saved to 'sleep_data.dat'. Goodbye!\n");
                break;
            default:
                printf("\nInvalid input! Please enter a number between 1-7.\n");
        }

        // Pause before continuing (except when exiting)
        if (choice != 7) {
            printf("\nPress Enter to continue...");
            while (getchar() != '\n');
        }

    } while (choice != 7);

    return 0;
}