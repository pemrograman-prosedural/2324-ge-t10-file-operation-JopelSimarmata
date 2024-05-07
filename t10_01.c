// 12S23013 - Andika Nadapdap
// 12S23036 - Jopel Simarmata

#include <stdio.h>
#include "./libs/dorm.h"
#include "./libs/student.h"
#include "./libs/repository.h"
#include <string.h>
#include <stdlib.h>

int main(int _argc, char **_argv)
{
    int total_dorms = 0;
    int total_students = 0;
    struct dorm_t dorms[20] ;
    struct student_t students[20];
    FILE *file;
    char buffer[200];
    int index_student = 0;
    int index_dorm = 0;


    file = fopen("./storage/dorm-repository.txt", "r");
    while (fgets(buffer, 200, file) != NULL)
    {
        char *token = strtok(buffer, "|");
        char  *name = token;
        token = strtok(NULL, "|");
        short unsigned capacity = atoi(token);
        token = strtok(NULL, "|");
        if (strcmp(token,"male\n")==0){
            dorms[total_dorms]=create_dorm(name, capacity, GENDER_MALE);
            total_dorms++;
        } else {
            dorms[total_dorms]=create_dorm(name, capacity, GENDER_FEMALE);
            total_dorms++;
        }

    }

    file = fopen("./storage/student-repository.txt", "r");
    while (fgets(buffer, 200, file) != NULL)
    {
        char *token = strtok(buffer, "|");
        char  *id = token;
        token = strtok(NULL, "|");
        char *name = token;
        token = strtok(NULL, "|");
        char *year = token;
        token = strtok(NULL, "|");
        if  (strcmp(token,"male\n")==0){
            students[total_students]=create_student(id, name, year,GENDER_MALE);
            total_students++;
        } else {
            students[total_students]=create_student(id, name, year,GENDER_FEMALE);
            total_students++;
        }
    }

    fclose(file);


    char perintah[60];
    while(1){
        fgets(perintah, 60, stdin);
        if (perintah[strlen(perintah) - 1] == '\n' || perintah[strlen(perintah) - 1] == '\r')
        {
            perintah[strlen(perintah) - 1] = '\0';
        }

        if (strcmp(perintah, "dorm-print-all-detail")==0){
            for (int i = 0; i < total_dorms; i++)
            {
                print_dorm_detail(dorms[i]);
            }
        } else if (strcmp(perintah,"student-print-all-detail")==0){
            for (int i = 0; i < total_students; i++)
            {
                print_student_detail(students[i]);
            }
        } else if (strcmp(perintah,"student-print-all")==0){
            for (int i = 0; i < total_students; i++)
            {
                print_student(students[i]);
            }

        } else if (strcmp(perintah,"dorm-print-all")==0){
            for (int i = 0; i < total_dorms; i++)
            {
                print_dorm(dorms[i]);
            }
        } else if (strcmp(perintah,"---")==0){
            break;
        }
        char *token = strtok(perintah, "#");
        if (strcmp(token,"student-add")==0){
            token = strtok(NULL, "#");
            char *id = token;
            token = strtok(NULL, "#");
            char *name = token;
            token = strtok(NULL, "#");
            char *year = token;
            token = strtok(NULL, "#");
            if (strcmp(token,"male")==0){
                students[total_students]=create_student(id, name, year,GENDER_MALE);
                total_students++;
            } else {
                students[total_students]=create_student(id, name, year, GENDER_FEMALE);
                total_students++;
            }
        } else if (strcmp(token,"dorm-add")==0){
            token = strtok(NULL, "#");
            char *name = token;
            token = strtok(NULL, "#");
            short unsigned capacity = atoi(token);
            token = strtok(NULL, "#");
            if (strcmp(token,"male")==0){
                dorms[total_dorms]=create_dorm(name, capacity,GENDER_MALE);
                total_dorms++;
            } else {
                dorms[total_dorms]=create_dorm(name, capacity, GENDER_FEMALE);
                total_dorms++;
            }    
        } else if (strcmp(token,"student-assign")==0){
            token = strtok(NULL, "#");
            char *_id = token;
            token = strtok(NULL, "#");
            char *_dorm_name = token;
            for (int i = 0; i < total_students; i++){
                if(strcmp(students[i].id,_id)==0){
                    index_student = i;
                }
            }
            for (int j = 0; j < total_dorms; j++){
                if(strcmp(dorms[j].name,_dorm_name)==0){
                    index_dorm = j;
                }
            }
            assign_student(&students[index_student],&dorms[index_dorm],_id,_dorm_name);
        }
    }
    return 0;
}
