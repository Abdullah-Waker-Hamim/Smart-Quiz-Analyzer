#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <time.h>
 
// Macros 
#define YELLOW 14
#define CYAN   11
#define GREEN  10
#define RED    12
#define WHITE  15
#define PINK   13
#define SECRET_WORD "Ragnarock"
 
//  Structures 
struct User {
    char username[30];
    char password[20];
};
 
struct Question {
    char ques_text[100];
    char option1[30], option2[30], option3[30];
    int correct_ans;
};
 
struct ScoreRecord {
    char name[30];
    int score;
    float time_taken;
    int quiz_id;
};
 
// Function Prototypes 
// Utility Functions
void welcome();
void main_menu();
void line(int c);
void color_add(int c);
void delay(int ms);
void slow_print(char *text, int c, int speed);
void exit_screen();
void about_project();
 
// User Related Functions
void register_user();
void login_user();
void user_dashboard(char user[]);
void start_quiz(char user[], int quiz_choice);
void leaderboard();
 
// Admin Related Functions
void admin_portal();
void register_admin();
void login_admin();
void change_admin_password();
void admin_dashboard_menu();
void manage_questions();
void remove_user();
void clear_leaderboard();
 
 
// Main Function
 
int main() {
    int choice;
    welcome();
 
    while(1) {
        main_menu();
        color_add(WHITE);
        printf("\n\tEnter your choice: ");
 
        if(scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            continue;
        }
 
        switch(choice) {
            case 1: register_user(); break;
            case 2: login_user(); break;
            case 3: admin_portal(); break;
            case 4: leaderboard(); break;
            case 5: about_project(); break;
            case 6: exit_screen(); return 0;
            default:
                printf("\n\tInvalid Choice!\n");
                delay(1000);
        }
    }
    return 0;
}
 
 
// 1. UI & Utility Functions
 
void welcome() {
    system("cls");
    line(RED);
    slow_print("           WELCOME TO SMART QUIZ ANALYZER\n", YELLOW, 30);
    line(RED);
    delay(500);
}
 
void main_menu() {
    system("cls");
    line(CYAN);
    printf("           SMART QUIZ ANALYZER MENU\n");
    line(CYAN);
    slow_print("\n\t1. User Register", WHITE, 20);
    slow_print("\n\t2. User Login", WHITE, 20);
    slow_print("\n\t3. Admin Portal", WHITE, 20);
    slow_print("\n\t4. Leaderboard", WHITE, 20);
    slow_print("\n\t5. About Project", GREEN, 20);
    slow_print("\n\t6. Exit\n", RED, 20);
}
 
void slow_print(char *text, int c, int speed) {
    color_add(c);
    for(int i = 0; text[i] != '\0'; i++) {
        printf("%c", text[i]);
        fflush(stdout);
        Sleep(speed);
    }
    color_add(WHITE);
}
 
void line(int c) {
    color_add(c);
    for(int i = 0; i < 45; i++) printf("=");
    printf("\n");
}
 
void color_add(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
 
void delay(int ms) {
    Sleep(ms);
}
 
void about_project() {
    system("cls");
    line(PINK);
    slow_print("            ABOUT THE PROJECT\n", YELLOW, 30);
    line(PINK);
    color_add(CYAN);
    printf("\n  Smart Quiz Analyzer is a high-performance console application\n");
    printf("  designed to evaluate user knowledge across multiple domains.\n");
    printf("  This project features a secure multi-user system, an advanced\n");
    printf("  admin portal for content management, and a ranking algorithm\n");
    printf("  based on accuracy and time complexity.\n\n");
    color_add(GREEN);
    printf("\t   DEVELOPED BY TEAM RAGNAROCK\n");
    line(WHITE);
    slow_print("\n  1. Abdullah Waker", YELLOW, 20);
    printf("\n     ID: C-253132, 1DM");
    printf("\n     Department of CSE");
    printf("\n     International Islamic University Chittagong (IIUC)");
    slow_print("\n\n  2. [Member Name]", YELLOW, 20);
    printf("\n     ID: [ID Here], Section");
    printf("\n     Department of CSE, IIUC");
    slow_print("\n\n  3. [Member Name]", YELLOW, 20);
    printf("\n     ID: [ID Here], Section");
    printf("\n     Department of CSE, IIUC");
    color_add(WHITE);
    printf("\n\n  -------------------------------------------\n");
    printf("  Press Enter to return to main menu...");
    while(getchar() != '\n');
    getchar(); 
}
 
void exit_screen() {
    system("cls");
    line(PINK);
    slow_print("\n\t      THANK YOU FOR PLAYING!", YELLOW, 40);
    slow_print("\n\t SMART QUIZ ANALYZER IS CLOSING", CYAN, 40);
    slow_print("\n\n\tDEVELOPED BY TEAM RAGNAROCK", GREEN, 40);
    slow_print("\n\n\t  GOODBYE! HAVE A GREAT DAY!!!", WHITE, 50);
    printf("\n");
    line(PINK);
    delay(2000);
}
 
 
// 2. User Functions
 
void register_user() {
    struct User new_u;
    system("cls");
    line(GREEN);
    printf("USER REGISTRATION\n");
    line(GREEN);
    printf("\n\tUsername: ");
    while(getchar() != '\n');
    scanf("%[^\n]", new_u.username);
    printf("\tPassword: ");
    scanf("%s", new_u.password);
    FILE *f = fopen("login.txt", "a");
    if(f) {
        fprintf(f, "%s|%s\n", new_u.username, new_u.password);
        fclose(f);
    }
    printf("\n\tSuccess!\n");
    delay(1000);
}
 
void login_user() {
    char name[50], pass[50];
    struct User temp;
    int found = 0;
    system("cls");
    line(CYAN);
    printf("\t\t USER LOGIN\n");
    line(CYAN);
    printf("\n\tUsername: ");
    while(getchar() != '\n');
    scanf("%[^\n]", name);
    printf("\tPassword: ");
    scanf("%s", pass);
    FILE *f = fopen("login.txt", "r");
    if (f) {
        while (fscanf(f, " %[^|]|%s\n", temp.username, temp.password) != EOF) {
            if (strcmp(name, temp.username) == 0 && strcmp(pass, temp.password) == 0) {
                found = 1;
                break;
            }
        }
        fclose(f);
    }
    if (found) {
        printf("\n\tSuccess!\n");
        delay(1000);
        user_dashboard(name);
    } else {
        printf("\n\tInvalid!\n");
        delay(1500);
    }
}
 
void user_dashboard(char current_user[]) {
    int choice;
    while(1) {
        system("cls");
        line(CYAN);
        printf("    WELCOME TO YOUR DASHBOARD, %s\n", current_user);
        line(CYAN);
        struct ScoreRecord records[300];
        int count = 0, found = 0;
        FILE *fs = fopen("scores.txt", "r");
        printf("\n[ Performance History ]\n");
        printf("%-10s %-15s %-10s %-10s\n", "Quiz ID", "User", "Score", "Time(s)");
        if (fs != NULL) {
            while (fscanf(fs, " %d|%[^|]|%d|%f\n", &records[count].quiz_id, records[count].name, &records[count].score, &records[count].time_taken) != EOF) {
                if (strcmp(records[count].name, current_user) == 0) {
                    printf("Quiz %-6d %-15s %-10d %-10.0f\n", records[count].quiz_id, records[count].name, records[count].score, records[count].time_taken);
                    found = 1;
                }
                count++;
            }
            fclose(fs);
        }
        if (!found) printf("\tNo records.\n");
        printf("\n  1. Quiz 1\n  2. Quiz 2\n  3. Quiz 3\n  4. Logout\n\n  Select: ");
        scanf("%d", &choice);
        if (choice >= 1 && choice <= 3) start_quiz(current_user, choice);
        else break;
    }
}
 
void start_quiz(char user[], int quiz_choice) {
    struct Question q[50];
    char filename[30];
    int current_score = 0, user_ans, q_count = 0;
    int user_answers[50]; 
 
    if(quiz_choice == 1) strcpy(filename, "questions.txt");
    else if(quiz_choice == 2) strcpy(filename, "questions1.txt");
    else strcpy(filename, "questions2.txt");
 
    FILE *fq = fopen(filename, "r");
    if (fq == NULL) {
        printf("\n\tMissing file!\n");
        delay(2000);
        return;
    }
 
    system("cls");
    line(YELLOW);
    printf("    QUIZ %d STARTING: %s\n", quiz_choice, user);
    line(YELLOW);
 
    time_t start_t = time(NULL);
    while (fscanf(fq, " %[^|]|%[^|]|%[^|]|%[^|]|%d\n", q[q_count].ques_text, q[q_count].option1, q[q_count].option2, q[q_count].option3, &q[q_count].correct_ans) != EOF) {
        printf("\nQ%d. %s\n1. %-15s 2. %-15s 3. %s\nAns: ", q_count + 1, q[q_count].ques_text, q[q_count].option1, q[q_count].option2, q[q_count].option3);
        scanf("%d", &user_ans);
        user_answers[q_count] = user_ans;
        if (user_ans == q[q_count].correct_ans) current_score++;
        q_count++;
    }
 
    double time_taken = difftime(time(NULL), start_t);
    fclose(fq);
 
    FILE *fs = fopen("scores.txt", "a");
    if(fs) {
        fprintf(fs, "%d|%s|%d|%.0f\n", quiz_choice, user, current_score, time_taken);
        fclose(fs);
    }
 
    system("cls");
    line(PINK);
    color_add(CYAN);
    printf("\t      QUIZ COMPLETED!\n");
    line(PINK);
    color_add(WHITE);
    printf("\n  Total Questions : %d", q_count);
    color_add(GREEN);
    printf("\n  Correct Answers : %d", current_score);
    color_add(RED);
    printf("\n  Wrong Answers   : %d", q_count - current_score);
    color_add(YELLOW);
    printf("\n  Time Taken      : %.0f seconds", time_taken);
 
    color_add(WHITE);
    printf("\n\n  1. Review Questions\n  2. Return to Dashboard\n\n  Choice: ");
    int review_choice;
    scanf("%d", &review_choice);
 
    if(review_choice == 1) {
        system("cls");
        line(YELLOW);
        printf("          FULL QUIZ REVIEW (ALL OPTIONS)\n");
        line(YELLOW);
        for(int i = 0; i < q_count; i++) {
            color_add(WHITE);
            printf("\nQ%d. %s", i+1, q[i].ques_text);
            printf("\n   1. %-15s 2. %-15s 3. %s", q[i].option1, q[i].option2, q[i].option3);
            if(user_answers[i] == q[i].correct_ans) {
                color_add(GREEN);
                printf("\n   Your Result: CORRECT (Option %d)", user_answers[i]);
            } else {
                color_add(RED);
                printf("\n   Your Result: WRONG (You chose %d)", user_answers[i]);
                color_add(CYAN);
                printf(" -> Correct Answer was: Option %d", q[i].correct_ans);
            }
            color_add(WHITE);
            printf("\n   -----------------------------------------");
        }
        printf("\n  Press Enter to continue...");
        while(getchar() != '\n');
        getchar();
    }
}
 
void leaderboard() {
    struct ScoreRecord records[300], temp;
    int count = 0, target_quiz;
    system("cls");
    printf("\tQuiz ID (1/2/3): ");
    scanf("%d", &target_quiz);
    FILE *fs = fopen("scores.txt", "r");
    if (fs) {
        while (fscanf(fs, " %d|%[^|]|%d|%f\n", &records[count].quiz_id, records[count].name, &records[count].score, &records[count].time_taken) != EOF) {
            if(records[count].quiz_id == target_quiz) count++;
        }
        fclose(fs);
        for (int i = 0; i < count-1; i++) {
            for (int j = 0; j < count-i-1; j++) {
                if (records[j].score < records[j+1].score) {
                    temp = records[j];
                    records[j] = records[j+1];
                    records[j+1] = temp;
                }
            }
        }
        system("cls");
        line(YELLOW);
        printf("QUIZ %d RANKINGS\n", target_quiz);
        line(YELLOW);
        for (int i = 0; i < count; i++) printf("\t#%-4d %-15s Score: %d\n", i+1, records[i].name, records[i].score);
    }
    printf("\n\tPress Enter...");
    while(getchar() != '\n');
    getchar();
}
 
 
// 3. Admin Functions
 
void admin_portal() {
    int choice;
    while(1) {
        system("cls");
        line(PINK);
        printf("              ADMIN ACCESS CENTER\n");
        line(PINK);
        printf("\n\t1. Admin Login\n\t2. Admin Registration\n\t3. Change Admin Password\n\t4. Back to Main Menu");
        printf("\n\n\tSelect Option: ");
        scanf("%d", &choice);
        if(choice == 1) login_admin();
        else if(choice == 2) register_admin();
        else if(choice == 3) change_admin_password();
        else break;
    }
}
 
void register_admin() {
    char name[30], pass[30], word[30];
    system("cls");
    printf("\n\t--- Admin Registration ---");
    printf("\n\tNew Admin Username: ");
    scanf("%s", name);
    printf("\tNew Admin Password: ");
    scanf("%s", pass);
    printf("\tSecret Word: ");
    scanf("%s", word);
    if(strcmp(word, SECRET_WORD) == 0) {
        FILE *f = fopen("admin.txt", "a");
        if(f) {
            fprintf(f, "%s|%s\n", name, pass);
            fclose(f);
            printf("\n\tAdmin Registered Successfully!\n");
        }
    } else printf("\n\tWrong Secret Word!\n");
    delay(1500);
}
 
void login_admin() {
    char name[30], pass[30], f_name[30], f_pass[30];
    int found = 0;
    system("cls");
    printf("\n\t--- Admin Login ---");
    printf("\n\tUsername: ");
    scanf("%s", name);
    printf("\tPassword: ");
    scanf("%s", pass);
    FILE *f = fopen("admin.txt", "r");
    if(f) {
        while(fscanf(f, " %[^|]|%s\n", f_name, f_pass) != EOF) {
            if(strcmp(name, f_name) == 0 && strcmp(pass, f_pass) == 0) {
                found = 1;
                break;
            }
        }
        fclose(f);
    }
    if(found) {
        printf("\n\tAccess Granted!\n");
        delay(1000);
        admin_dashboard_menu();
    } else {
        printf("\n\tInvalid Admin Credentials!\n");
        delay(1500);
    }
}
 
void change_admin_password() {
    char name[30], word[30], new_pass[30], f_name[30], f_pass[30];
    int found = 0;
    system("cls");
    printf("\n\t--- Reset Admin Password ---");
    printf("\n\tEnter Admin Username: ");
    scanf("%s", name);
    printf("\tEnter Secret Word: ");
    scanf("%s", word);
    if(strcmp(word, SECRET_WORD) == 0) {
        FILE *f = fopen("admin.txt", "r");
        FILE *t = fopen("temp_admin.txt", "w");
        if(f && t) {
            while(fscanf(f, " %[^|]|%s\n", f_name, f_pass) != EOF) {
                if(strcmp(name, f_name) == 0) {
                    printf("\tEnter New Password: ");
                    scanf("%s", new_pass);
                    fprintf(t, "%s|%s\n", f_name, new_pass);
                    found = 1;
                } else fprintf(t, "%s|%s\n", f_name, f_pass);
            }
            fclose(f);
            fclose(t);
            remove("admin.txt");
            rename("temp_admin.txt", "admin.txt");
        }
        if(found) printf("\n\tPassword Changed Successfully!\n");
        else printf("\n\tUsername not found!\n");
    } else printf("\n\tWrong Secret Word!\n");
    delay(1500);
}
 
void admin_dashboard_menu() {
    int choice;
    while(1) {
        system("cls");
        line(PINK);
        printf("              ADMIN CONTROL PANEL\n");
        line(PINK);
        printf("\n\t1. Manage Quiz Questions\n\t2. Remove a User\n\t3. Clear Leaderboard\n\t4. Logout\n\n\tChoice: ");
        scanf("%d", &choice);
        if(choice == 1) manage_questions();
        else if(choice == 2) remove_user();
        else if(choice == 3) clear_leaderboard();
        else break;
    }
}
 
void manage_questions() {
    int q_id, sub_choice;
    char filename[30];
    struct Question q_list[100];
    int count = 0;
    system("cls");
    printf("\tSelect Quiz (1=Basic, 2=Medium, 3=Hard): ");
    scanf("%d", &q_id);
    if(q_id == 1) strcpy(filename, "questions.txt");
    else if(q_id == 2) strcpy(filename, "questions1.txt");
    else strcpy(filename, "questions2.txt");
 
    FILE *f = fopen(filename, "r");
    if(f) {
        while(fscanf(f, " %[^|]|%[^|]|%[^|]|%[^|]|%d\n", q_list[count].ques_text, q_list[count].option1, q_list[count].option2, q_list[count].option3, &q_list[count].correct_ans) != EOF) {
            count++;
        }
        fclose(f);
    }
    system("cls");
    line(YELLOW);
    printf("        CURRENT QUESTIONS IN QUIZ %d\n", q_id);
    line(YELLOW);
    for(int i = 0; i < count; i++) printf("%d. %s\n", i+1, q_list[i].ques_text);
 
    printf("\n\t1. Add\n\t2. Remove\n\t3. Back\n\tChoice: ");
    scanf("%d", &sub_choice);
    if(sub_choice == 1) {
        struct Question new_q;
        printf("\n\tEnter Question: ");
        while(getchar() != '\n');
        scanf("%[^\n]", new_q.ques_text);
        printf("\tOption 1: ");
        scanf(" %[^\n]", new_q.option1);
        printf("\tOption 2: ");
        scanf(" %[^\n]", new_q.option2);
        printf("\tOption 3: ");
        scanf(" %[^\n]", new_q.option3);
        printf("\tCorrect Ans: ");
        scanf("%d", &new_q.correct_ans);
        FILE *fa = fopen(filename, "a");
        if(fa) {
            fprintf(fa, "%s|%s|%s|%s|%d\n", new_q.ques_text, new_q.option1, new_q.option2, new_q.option3, new_q.correct_ans);
            fclose(fa);
        }
    } else if(sub_choice == 2 && count > 0) {
        int rem_idx;
        printf("\n\tRemove No: ");
        scanf("%d", &rem_idx);
        if(rem_idx >= 1 && rem_idx <= count) {
            FILE *fw = fopen(filename, "w");
            for(int i = 0; i < count; i++) {
                if(i != rem_idx - 1) fprintf(fw, "%s|%s|%s|%s|%d\n", q_list[i].ques_text, q_list[i].option1, q_list[i].option2, q_list[i].option3, q_list[i].correct_ans);
            }
            fclose(fw);
        }
    }
    delay(1500);
}
 
void remove_user() {
    char target[30];
    struct User temp;
    int found = 0;
    system("cls");
    line(PINK);
    printf("           REMOVE USER ACCOUNT\n");
    line(PINK);
    printf("\n\tEnter Exact Username: ");
    while(getchar() != '\n');
    scanf("%[^\n]", target);
    FILE *f = fopen("login.txt", "r");
    FILE *t = fopen("temp_user.txt", "w");
    if (f) {
        while (fscanf(f, " %[^|]|%s\n", temp.username, temp.password) != EOF) {
            if (strcmp(temp.username, target) == 0) found = 1;
            else fprintf(t, "%s|%s\n", temp.username, temp.password);
        }
        fclose(f);
        fclose(t);
        remove("login.txt");
        rename("temp_user.txt", "login.txt");
    }
    if (found) printf("\n\tSuccess: User removed.\n");
    else printf("\n\tError: User not found!\n");
    delay(2000);
}
 
void clear_leaderboard() {
    char c;
    printf("\n\tClear ALL scores? (y/n): ");
    scanf(" %c", &c);
    if(c == 'y' || c == 'Y') {
        FILE *f = fopen("scores.txt", "w");
        if(f) fclose(f);
        printf("\tCleared!\n");
    }
    delay(1500);
}