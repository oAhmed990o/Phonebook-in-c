#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

contacts** load(){
    contacts** co_array = (contacts**)malloc(10000);

    for(int i=0;i<10000;i++)
        co_array[i] = malloc(sizeof (contacts));

    char line[1000];
    FILE* fp;
    fp = fopen("contacts.txt","a+");

    int index = 0;
    char *token;
    while(!feof(fp)){

        fgets(line, 1000, fp);
        line[sizeof(line)-1] = '\0';
        token = strtok(line, ",\n");

        int flag = 1;
        last_index = index;;
        
        while( token != NULL ) {
            switch(flag){
                case 1:
                    co_array[index]->last_name = malloc(sizeof(char*)*sizeof(token));
                    strcpy(co_array[index]->last_name,token);
                    flag++;
                    break;
                case 2:
                    co_array[index]->first_name = malloc(sizeof(char*)*sizeof(token));
                    strcpy(co_array[index]->first_name,token);
                    flag++;
                    break;
                case 3:
                    strcpy(co_array[index]->birth_date.day,token);
                    flag++;
                    break;
                case 4:
                    strcpy(co_array[index]->birth_date.month,token);
                    flag++;
                    break;
                case 5:
                    strcpy(co_array[index]->birth_date.year,token);
                    flag++;
                    break;
                case 6:
                    co_array[index]->street_address = malloc(sizeof(char*)*sizeof(token));
                    strcpy(co_array[index]->street_address,token);
                    flag++;
                    break;
                case 7:
                    co_array[index]->email = malloc(sizeof(char*)*sizeof(token));
                    strcpy(co_array[index]->email,token);
                    flag++;
                    break;
                case 8:
                    strcpy(co_array[index]->phone_number,token);
                    flag = 1;
                    break;
                default:
                    break;
            }
            token = strtok(NULL, ",\n");
        }
        index++;
    }

    fclose(fp);
    return *&co_array;
}

void query(contacts** co_array){
    int index = 0;
    char last_name[30];
    printf("Enter last name : ");
    scanf("%s",last_name);

    while(index<=last_index){ 
        int res = strcasecmp(last_name,co_array[index]->last_name);
        if (res == 0){
            printf("Last name : %s\n",co_array[index]->last_name);
            printf("First name : %s\n",co_array[index]->first_name);
            printf("Birthdate : %s %s %s\n",co_array[index]->birth_date.day,co_array[index]->birth_date.month,co_array[index]->birth_date.year);
            printf("Street address : %s\n",co_array[index]->street_address);
            printf("Email : %s\n",co_array[index]->email);
            printf("Phone number : %s\n\n",co_array[index]->phone_number);
        }
        index++;
    }
}

void add(contacts** co_array){
    last_index++;
    printf("Enter last name : ");
    scanf("%s",co_array[last_index]->last_name);
    
    printf("Enter first name : ");
    scanf("%s",co_array[last_index]->first_name);
    
    printf("Enter birthdate dd/mm/yyyy : ");
    scanf("%s %s %s",co_array[last_index]->birth_date.day, co_array[last_index]->birth_date.month, co_array[last_index]->birth_date.year);
    
    printf("Enter street address : ");
    scanf("%s",co_array[last_index]->street_address);
    
    printf("Enter email : ");
    scanf("%s",co_array[last_index]->email);
    
    printf("Enter phone number : ");
    scanf("%s",co_array[last_index]->phone_number);
    
}

void delete(contacts** co_array){
    char last_name[30];
    char first_name[30];
    printf("Enter last name : ");
    scanf("%s",last_name);
    
    printf("Enter first name : ");
    scanf("%s",first_name);
    printf("\n");
    
    int index = 0;
    while(index<=last_index){
        int res_last = strcasecmp(last_name,co_array[index]->last_name);
        int res_first = strcasecmp(first_name,co_array[index]->first_name);
        if (res_last == 0 && res_first == 0){
            strcpy(co_array[index]->last_name, co_array[last_index]->last_name);
            strcpy(co_array[index]->first_name, co_array[last_index]->first_name);
            strcpy(co_array[index]->birth_date.day, co_array[last_index]->birth_date.day);
            strcpy(co_array[index]->birth_date.month, co_array[last_index]->birth_date.month);
            strcpy(co_array[index]->birth_date.year, co_array[last_index]->birth_date.year);
            strcpy(co_array[index]->street_address, co_array[last_index]->street_address);
            strcpy(co_array[index]->email, co_array[last_index]->email);
            strcpy(co_array[index]->phone_number, co_array[last_index]->phone_number);
            last_index--;
            index--;
        }
        index++;
    }
}

void modify(contacts** co_array){
    int index = 0;
    char last_name[30];
    printf("Enter last name : ");
    scanf("%s",last_name);

    while(index<=last_index){ 
        int res = strcasecmp(last_name,co_array[index]->last_name);
        if (res == 0){
            printf("%d - %s %s\n",index+1,co_array[index]->last_name,co_array[index]->first_name);
        }
        index++;
    }
    printf("\n");
    printf("Enter new contact ID to modify : ");
    scanf("%d",&index);
    //co_array[index-1]
    
    printf("Enter new last name : ");
    scanf("%s",co_array[index-1]->last_name);
    
    printf("Enter new first name : ");
    scanf("%s",co_array[index-1]->first_name);
    
    printf("Enter new birthdate dd/mm/yyyy : ");
    scanf("%s %s %s",co_array[index-1]->birth_date.day, co_array[index-1]->birth_date.month, co_array[index-1]->birth_date.year);
    
    printf("Enter new street address : ");
    scanf("%s",co_array[index-1]->street_address);
    
    printf("Enter new email : ");
    scanf("%s",co_array[index-1]->email);
    
    printf("Enter new phone number : ");
    scanf("%s",co_array[index-1]->phone_number);
}

void sort(contacts** co_array){
    int i,j;
    contacts* proxy = malloc(sizeof(contacts));
    for (i=0;i<last_index;i++)
        for (j=0;j<last_index-i;j++){
            if( strcasecmp(co_array[j]->last_name, co_array[j+1]->last_name) > 0){
                proxy = co_array[j];
                co_array[j] = co_array[j+1];
                co_array[j+1] = proxy;
            }
            else if(strcasecmp(co_array[j]->last_name, co_array[j+1]->last_name) == 0){
                if( strcasecmp(co_array[j]->first_name, co_array[j+1]->first_name) > 0){
                    proxy = co_array[j];
                    co_array[j] = co_array[j+1];
                    co_array[j+1] = proxy;
                }
            }
        }
}

void save(contacts** co_array){
    FILE* fp;
    fp = fopen("contacts.txt","w");
    int index = 0;
    while(index <= last_index){
        fprintf(fp,"%s,%s,%s,%s,%s,%s,%s,%s\n",co_array[index]->last_name,co_array[index]->first_name,
        co_array[index]->birth_date.day,co_array[index]->birth_date.month,co_array[index]->birth_date.year,
        co_array[index]->street_address,co_array[index]->email,co_array[index]->phone_number);
        index++;
    }
    fclose(fp);
}

int quit(){
    char choice;
    printf("Unsaved changes will be lost\n");
    printf("Are you sure you want to quit? y/n : ");
    scanf("%c",&choice);
    if(choice == 'y'){
        return -1;    
    }
    else{
        return 0;
    }
}

void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

int main() {
    int i;
    contacts** arr;
    arr = load();
    int q = 0;
    int choice;
    while (q != -1){
        system("clear");
        printf("1 - query\n2 - add\n3 - delete\n4 - modify\n5 - print\n6 - save\n7 - exit\n");
        printf("Enter desired function ID : ");
        scanf("%d",&choice);
        system("clear");
        /*switch(choice){
            case 1:
                system("clear");
                query(arr);
                break;
            case 2:
                system("clear");
                add(arr);
                break;
            case 3:
                system("clear");
                delete(arr);
                break;
            case 4:
                system("clear");
                modify(arr);
                break;
            case 5:
                system("clear");
                sort(arr);
                break;
            case 6:
                system("clear");
                save(arr);
                break;
            case 7:
                system("clear");
                q = quit();
                break;
            default:
                printf("ID doesn't exist");
                break;
        }*/
        if (choice == 1){
            system("clear");
            query(arr);
        }
        else if(choice == 2){
            system("clear");
            add(arr);
        }
        else if(choice == 3){
            system("clear");
            delete(arr);
        }
        else if(choice == 4){
            system("clear");
            modify(arr);
        }
        else if(choice == 5){
            system("clear");
            sort(arr);
        }
        else if(choice == 6){
            system("clear");
            save(arr);
        }
        else if(choice == 7){
            system("clear");
            q = quit();
        }
        else{
            printf("ID doesn't exist");
            delay(3);
        }
    }
    /*for(i = 0;i<last_index+1;i++) {
        printf("%s %s %s %s %s %s %s %s\n", arr[i]->last_name, arr[i]->first_name, arr[i]->birth_date.day,
               arr[i]->birth_date.month,arr[i]->birth_date.year, arr[i]->street_address, arr[i]->email, arr[i]->phone_number);
    }*/
    return 0;
}

