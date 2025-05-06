#include "sleep_data.h"

int main() {
    int choice;

    load_from_file();

    printf("===== Sleep Tracker =====\n");

    do {
        show_main_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: add_sleep_entry(); break;
            case 2: view_sleep_log(); break;
            case 3: generate_weekly_report(); break;
            case 4: set_wakeup_alarm(); break;
            case 5: {
                if(entry_count > 0) {
                    float duration = entries[entry_count-1].wake_time -
                                   entries[entry_count-1].sleep_time;
                    if(duration < 0) duration += 24.0;
                    estimate_sleep_stages(duration);
                } else {
                    printf("No sleep entries available.\n");
                }
                break;
            }
            case 6: search_notes(); break;
            case 7: {
                save_to_file();
                printf("Goodbye! Data saved.\n");
                break;
            }
            default: printf("Invalid choice. Try again.\n");
        }
    } while(choice != 7);

    return 0;
}