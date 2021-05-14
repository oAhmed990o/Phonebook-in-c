#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <conio.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>

int last_index = 0;

struct b_date{
    char day[3];
    char month[3];
    char year[5];
};

typedef struct contacts{
    char* last_name;
    char* first_name;
    struct b_date birth_date;
    char* street_address;
    char* email;
    char phone_number[12];
}contacts;

contacts *co_array;

bool is_digit(char* ptr){
    if (NULL == ptr || *ptr == '\0')
        return false;

    while(*ptr){
        char c = *ptr;
        if( c<'0' || c>'9')
            return false;
        ptr++;
    }
    return true;
}

bool is_valid_phone_number(char phone_number[]){
    int i;
    char temp[] = {' ', '\0'};
    if(strlen(phone_number) != 11){
        return false;
    }
    for(i=0;i<strlen(phone_number);i++){
        temp[0] = phone_number[i];
        if(!is_digit(temp)){
            return false;
        }
    }
    return true;
}

bool is_valid_string_input(char string[], int key){
    int i;
    char temp[] = {' ', '\0'};
    if(key == 1){ //first and last name case
        for(i=0;i<strlen(string);i++){
            if(!isalpha(string[i])){
                return false;
            }
        }
    } else if (key == 2){ //address case
        for(i=0;i<strlen(string);i++){
            temp[0] = string[i];
            if(!isalpha(string[i]) && !is_digit(temp) && strcmp(temp, "-") != 0 && strcmp(temp, " ") != 0){
                return false;
            }
        }
    }
    return true;
}

bool is_domain(char domain[]){
    if (domain[0] == '.' || domain[strlen(domain)-1] == '.' || domain == "" || domain[0] == '-' || domain[strlen(domain)-1] == '-' || domain[0] == '\0')
        return false;

    int i;
    char temp[] = {' ', '\0'};
    for(i=0;i<strlen(domain);i++){
        temp[0] = domain[i];
        if(!is_digit(temp) && !isalpha(domain[i]) && domain[i] != '-' && domain[i] != '.'){
            return false;
        }
    }
    return true;
}

bool is_personal_info(char info[]){
    if (info[0] == '.' || info[strlen(info)-1] == '.' || info == "" || info[0] == '\0')
        return false;

    int i;
    char temp[] = {' ', '\0'};
    for(i=0;i<strlen(info);i++){
        temp[0] = info[i];
        if(!is_digit(temp) && !isalpha(info[i])
                             && info[i] != '!'
                                && info[i] != '#'
                                   && info[i] != '$'
                                      && info[i] != '%'
                                         && info[i] != '&'
                                            && info[i] != '\''
                                               && info[i] != '*'
                                                  && info[i] != '+'
                                                     && info[i] != '-'
                                                        && info[i] != '/'
                                                           && info[i] != '='
                                                              && info[i] != '?'
                                                                 && info[i] != '^'
                                                                    && info[i] != '_'
                                                                       && info[i] != '`'
                                                                          && info[i] != '{'
                                                                             && info[i] != '|'
                                                                                && info[i] != '}'
                                                                                   && info[i] != '~'
                                                                                      && info[i] != '.'){
            return false;
        }
    }
    return true;
}

bool is_valid_email(char email[]){
    int i, at = 0;
    char personal_info[50];
    char domain[50];
    if (email[0] == '.' || email[strlen(email)-1] == '.'){
        return false;
    }
    for (i=0;i<strlen(email)-1;i++){
        if(email[i] == '@' || email[i+1] == '@'){
            at = 1;
        }
        if(email[i] == '.' && email[i+1] == '.'){
            return false;
        }
    }

    if (at == 0)
        return false;

    int fill_domain = 0, info_index = 0, domain_index = 0, has_dot = 0;

    char temp[] = {' ', '\0'};
    for(i=0;i<strlen(email);i++){
        if(i+1<=strlen(email)){
            temp[0] = email[i+1];
        }else{
            temp[0] = email[i];
        }

        if(fill_domain == 0){
            personal_info[info_index] = email[i];
            info_index++;
        }else if(fill_domain == 1){
            domain[domain_index] = email[i];
            if(domain[domain_index] == '.'){
                has_dot = 1;
            }
            domain_index++;
        }

        if(email[i] == '@' && ( is_digit(temp) || isalpha(email[i+1]) ) ){
            personal_info[info_index-1] = '\0';
            fill_domain = 1;
        }
    }
    domain[domain_index] = '\0';
    if(!is_domain(domain) || !is_personal_info(personal_info)){
        return false;
    }

    if(has_dot == 0){
        return false;
    }

    return true;
}

bool is_valid_birthdate(char* day, char* month, char* year){
    time_t t;
    time(&t);
    char* time = ctime(&t);
    char current_month[] = {time[4], time[5], time[6], '\0'};
    char current_day[] = {time[8], time[9], '\0'};
    char current_year[] = {time[20], time[21], time[22], time[23], '\0'};

    int int_current_month;
    if(strcasecmp(current_month,"Jan") == 0){
        int_current_month = 1;
    }else if(strcasecmp(current_month,"Feb") == 0){
        int_current_month = 2;
    }else if(strcasecmp(current_month,"Mar") == 0){
        int_current_month = 3;
    }else if(strcasecmp(current_month,"Apr") == 0){
        int_current_month = 4;
    }else if(strcasecmp(current_month,"May") == 0){
        int_current_month = 5;
    }else if(strcasecmp(current_month,"Jun") == 0){
        int_current_month = 6;
    }else if(strcasecmp(current_month,"Jul") == 0){
        int_current_month = 7;
    }else if(strcasecmp(current_month,"Aug") == 0){
        int_current_month = 8;
    }else if(strcasecmp(current_month,"Sep") == 0){
        int_current_month = 9;
    }else if(strcasecmp(current_month,"Oct") == 0){
        int_current_month = 10;
    }else if(strcasecmp(current_month,"Nov") == 0){
        int_current_month = 11;
    }else if(strcasecmp(current_month,"Dec") == 0){
        int_current_month = 12;
    }

    if (!is_digit(day) || atoi(day) > 31 || atoi(day) < 1) return false;
    if (!is_digit(year) || atoi(year) > atoi(current_year) || atoi(year) < 1903) return false;
    if (!is_digit(month) || atoi(month) > 12 || atoi(month) < 1) return false;

    if (is_digit(month) && atoi(month) <= 12 && atoi(month) >= 1) {
        if (atoi(month) == 2) {
            if (atoi(year) % 4 == 0) {
                if (atoi(day) > 29) {
                    return false;
                }
            } else {
                if (atoi(day) > 28) {
                    return false;
                }
            }
        } else if (atoi(month) == 4 || atoi(month) == 6 || atoi(month) == 9 || atoi(month) == 11) {
            if (atoi(day) > 30) {
                return false;
            }
        }
    }

    if(atoi(year) <= atoi(current_year)){
        if(atoi(year) == atoi(current_year) && atoi(month) <= int_current_month) {
            if(atoi(year) == atoi(current_year) && atoi(month) == int_current_month && atoi(day) > atoi(current_day)){
                return false;
            }
        }else if(atoi(year) == atoi(current_year) && atoi(month) > int_current_month){
            return false;
        }
    }else{
        return false;
    }

    return true;
}

void load(){
    free(co_array);
    co_array = (contacts *) malloc(10000);

    char line[1000];
    FILE *fp;
    fp = fopen("contacts.txt", "a+");

    int index = 0;
    while (!feof(fp)) {

        fgets(line, 1000, fp);
        line[sizeof(line) - 1] = '\0';
        char *token = strtok(line, ",\n");

        int flag = 1;
        last_index = index;
        while( token != NULL ) {
            switch(flag){
                case 1:
                    co_array[index].last_name = malloc(sizeof(char)*strlen(token));
                    strcpy(co_array[index].last_name,token);
                    flag++;
                    break;
                case 2:
                    co_array[index].first_name = malloc(sizeof(char)*strlen(token));
                    strcpy(co_array[index].first_name,token);
                    flag++;
                    break;
                case 3:
                    strcpy(co_array[index].birth_date.day,token);
                    flag++;
                    break;
                case 4:
                    strcpy(co_array[index].birth_date.month,token);
                    flag++;
                    break;
                case 5:
                    strcpy(co_array[index].birth_date.year,token);
                    flag++;
                    break;
                case 6:
                    co_array[index].street_address = malloc(sizeof(char)*strlen(token));
                    strcpy(co_array[index].street_address,token);
                    flag++;
                    break;
                case 7:
                    co_array[index].email = malloc(sizeof(char)*strlen(token));
                    strcpy(co_array[index].email,token);
                    flag++;
                    break;
                case 8:
                    strcpy(co_array[index].phone_number,token);
                    flag = 1;
                    break;
                default:
                    break;
            }
            token = strtok(NULL, ",\n");
        }
        free(token);
        index++;
    }
        fclose(fp);
    }

void query(contacts* co_array){
    int index = 0;
    char last_name[30];

    printf("Enter last name :");
    scanf("%29s",last_name);
    while(!is_valid_string_input(last_name, 1)){
        printf("Invalid last name\n");
        printf("Enter last name :");
        scanf("%29s",last_name);
    }

    int any = 0;
    while(index<=last_index){
        int res = strcasecmp(last_name,co_array[index].last_name);
        if (res == 0){
            printf("Last name : %s\n",co_array[index].last_name);
            printf("First name : %s\n",co_array[index].first_name);
            printf("Birthdate : %s %s %s\n",co_array[index].birth_date.day,co_array[index].birth_date.month,co_array[index].birth_date.year);
            printf("Street address : %s\n",co_array[index].street_address);
            printf("Email : %s\n",co_array[index].email);
            printf("Phone number : %s\n\n",co_array[index].phone_number);

            any = 1;
        }
        index++;
    }
    if (any == 0){
        printf("Contact Not Found\n");
    }
} //implement multi-search

void add(contacts* co_array){
    last_index++;
    char token[50];

    printf("Enter last name :");
    scanf("%29s", token);
    co_array[last_index].last_name = malloc(sizeof(char)*strlen(token));
    strcpy(co_array[last_index].last_name, token);

    printf("Enter first name :");
    scanf("%29s", token);
    co_array[last_index].first_name = malloc(sizeof(char)*strlen(token));
    strcpy(co_array[last_index].first_name, token);

    printf("Enter birthdate dd/mm/yyyy :");
    scanf("%2s %2s %4s",co_array[last_index].birth_date.day, co_array[last_index].birth_date.month, co_array[last_index].birth_date.year);

    printf("Enter street address :");
    scanf("%49s", token);
    co_array[last_index].street_address = malloc(sizeof(char)*strlen(token));
    strcpy(co_array[last_index].street_address, token);

    printf("Enter email :");
    scanf("%29s", token);
    co_array[last_index].email = malloc(sizeof(char)*strlen(token));
    strcpy(co_array[last_index].email, token);

    printf("Enter phone number :");
    scanf("%11s",co_array[last_index].phone_number);
} //malfunctions

void delete(contacts* co_array){
    char last_name[30];
    char first_name[30];

    printf("Enter last name :");
    scanf("%29s",last_name);
    while(!is_valid_string_input(last_name, 1)){
        printf("Invalid last name\n");
        printf("Enter last name :");
        scanf("%29s",last_name);
    }

    printf("Enter first name :");
    scanf("%29s",first_name);
    while(!is_valid_string_input(first_name, 1)){
        printf("Invalid first name\n");
        printf("Enter first name :");
        scanf("%29s",first_name);
    }
    printf("\n");

    int index = 0;
    while(index<=last_index){
        int res_last = strcasecmp(last_name,co_array[index].last_name);
        int res_first = strcasecmp(first_name,co_array[index].first_name);
        if (res_last == 0 && res_first == 0){
            strcpy(co_array[index].last_name, co_array[last_index].last_name);
            strcpy(co_array[index].first_name, co_array[last_index].first_name);
            strcpy(co_array[index].birth_date.day, co_array[last_index].birth_date.day);
            strcpy(co_array[index].birth_date.month, co_array[last_index].birth_date.month);
            strcpy(co_array[index].birth_date.year, co_array[last_index].birth_date.year);
            strcpy(co_array[index].street_address, co_array[last_index].street_address);
            strcpy(co_array[index].email, co_array[last_index].email);
            strcpy(co_array[index].phone_number, co_array[last_index].phone_number);
            last_index--;
            index--;
        }
        index++;
    }
}

void modify(contacts* co_array){
    int index = 0;
    char last_name[30];
    puts("Enter last name :");
    scanf("%29s",last_name);
    while(!is_valid_string_input(last_name, 1)){
        printf("Invalid last name\n");
        printf("Enter last name :");
        scanf("%29s",last_name);
    }

    while(index<=last_index){
        int res = strcasecmp(last_name,co_array[index].last_name);
        if (res == 0){
            printf("%d - %s %s\n",index+1,co_array[index].last_name,co_array[index].first_name);
        }
        index++;
    }
    printf("\n");
    puts("Enter new contact ID to modify :");
    scanf("%d",&index); //validate id ?

    puts("Enter new last name :");
    scanf("%29s",co_array[index-1].last_name);
    while(!is_valid_string_input(co_array[index-1].last_name, 1)){
        printf("Invalid last name\n");
        puts("Enter new last name :");
        scanf("%29s",co_array[index-1].last_name);
    }

    puts("Enter new first name :");
    scanf("%29s",co_array[index-1].first_name);
    while(!is_valid_string_input(co_array[index-1].first_name, 1)){
        printf("Invalid first name\n");
        puts("Enter new first name :");
        scanf("%29s",co_array[index-1].first_name);
    }

    puts("Enter new birthdate dd/mm/yyyy :"); //malfunctions
    scanf("%2s %2s %4s",co_array[index-1].birth_date.day, co_array[index-1].birth_date.month, co_array[index-1].birth_date.year);
    while(!is_valid_birthdate(co_array[index-1].birth_date.day, co_array[index-1].birth_date.month, co_array[index-1].birth_date.year)){
        printf("Invalid birthdate\n");
        puts("Enter new birthdate dd/mm/yyyy :");
        scanf("%2s %2s %4s",co_array[index-1].birth_date.day, co_array[index-1].birth_date.month, co_array[index-1].birth_date.year);
    }

    puts("Enter new street address :");
    scanf("%49s",co_array[index-1].street_address);
    while(!is_valid_string_input(co_array[index-1].street_address, 2)){
        printf("Invalid street address\n");
        puts("Enter new street address :");
        scanf("%49s",co_array[index-1].street_address);
    }

    puts("Enter new email :");
    scanf("%29s",co_array[index-1].email);
    while(!is_valid_email(co_array[index-1].email)){
        printf("Invalid email\n");
        puts("Enter new email :");
        scanf("%29s",co_array[index-1].email);
    }

    puts("Enter new phone number :");
    scanf("%11s",co_array[index-1].phone_number);
    while(!is_valid_phone_number(co_array[index-1].phone_number)){
        printf("Invalid phone number\n");
        puts("Enter new phone number :");
        scanf("%11s",co_array[index-1].phone_number);
    }
}

void print(contacts* co_array){
    int i,j;
    struct contacts proxy;
    for (i=0;i<last_index;i++)
        for (j=0;j<last_index-i;j++){
            if( strcasecmp(co_array[j].last_name, co_array[j+1].last_name) > 0){
                proxy = co_array[j];
                co_array[j] = co_array[j+1];
                co_array[j+1] = proxy;
            }
            else if(strcasecmp(co_array[j].last_name, co_array[j+1].last_name) == 0){
                if( strcasecmp(co_array[j].first_name, co_array[j+1].first_name) > 0){
                    proxy = co_array[j];
                    co_array[j] = co_array[j+1];
                    co_array[j+1] = proxy;
                }
            }
        }
    for(i = 0;i<last_index+1;i++) {
        printf("Last name : %s\n",co_array[i].last_name);
        printf("First name : %s\n",co_array[i].first_name);
        printf("Birthdate : %s %s %s\n",co_array[i].birth_date.day,co_array[i].birth_date.month,co_array[i].birth_date.year);
        printf("Street address : %s\n",co_array[i].street_address);
        printf("Email : %s\n",co_array[i].email);
        printf("Phone number : %s\n\n",co_array[i].phone_number);
    }
} //implement sorting based on date of birth

void save(contacts* co_array){
    FILE* fp;
    fp = fopen("contacts.txt","w+");
    int index = 0;
    while(index <= last_index){
        char buffer[512] = "";

        strcat(buffer, co_array[index].last_name);
        strcat(buffer, ",");
        strcat(buffer, co_array[index].first_name);
        strcat(buffer, ",");
        strcat(buffer, co_array[index].birth_date.day);
        strcat(buffer, ",");
        strcat(buffer, co_array[index].birth_date.month);
        strcat(buffer, ",");
        strcat(buffer, co_array[index].birth_date.year);
        strcat(buffer, ",");
        strcat(buffer, co_array[index].street_address);
        strcat(buffer, ",");
        strcat(buffer, co_array[index].email);
        strcat(buffer, ",");
        strcat(buffer, co_array[index].phone_number);

        if(index != last_index)
            strcat(buffer, "\n");

        fputs(buffer,fp);
        index++;
    }
    fclose(fp);
}

int quit(){
    char choice;
    puts("Unsaved changes will be lost");
    puts("Are you sure you want to quit? y/n :");
    scanf("%c",&choice);
    puts("\n");
    if(choice == 'y'){
        return 2;
    }
    else{
        return 1;
    }
}

void main() {

    load();
    //query(co_array);
    //add(co_array); //malfunction
    //delete(co_array);
    modify(co_array);
    print(co_array);
    //save(co_array);
    //quit();
    //printf("exit output %d",quit());

    /*int q = 1;
    int choice = 0;

    while (q != 2) {
        sleep(2);
        puts("1 - query\n2 - add\n3 - delete\n4 - modify\n5 - print\n6 - save\n7 - exit\nEnter desired function ID :");
        scanf("%d", &choice);
        //system("cls");
        switch (choice) {
            case 1:
                //puts("query\n");
                query(co_array);
                break;
            case 2:
                //puts("add\n");
                add(co_array);
                break;
            case 3:
                //puts("delete\n");
                delete(co_array);
                break;
            case 4:
                //puts("modify\n");
                modify(co_array);
                break;
            case 5:
                //puts("print\n");
                print(co_array);
                break;
            case 6:
                //system("cls");
                //puts("save\n");
                save(co_array);
                break;
            case 7:
                //puts("quit\n");
                q = quit();
                break;
            default:
                puts("ID doesn't exist\n");
                break;
        }
    }*/

}