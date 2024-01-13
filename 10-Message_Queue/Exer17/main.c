#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>

#define NAME_FILE "/trismeque"
#define MAX_SIZE 8192

typedef struct {
    char Name[50];
    int Age;
    char PhoneNum[50];
    char Home[50];
} Human;

typedef struct {
    long prio_id;
    Human Human;
} Message;

void input_data(mqd_t id_std, Message *info_data) {
    printf("\n| --- Your Information --- |\n");

    // mq_receive(id_std, (char *)&info_data, sizeof(info_data), NULL);

    printf("\nEnter your ID: ");
    scanf("%li", &info_data->prio_id);
    getchar();

    while(info_data->prio_id <= 0) {
        printf("\nInvalid ID, please enter your ID again: ");
        scanf("%li", &info_data->prio_id);
    }

    printf("\nEnter your Name: ");
    fgets(info_data->Human.Name, sizeof(info_data->Human.Name), stdin);

    printf("\nEnter your Age: ");
    scanf("%d", &info_data->Human.Age);
    getchar();

    while(info_data->Human.Age <= 0) {
        printf("\nInvalid Age, please enter your Age again: ");
        scanf("%d", &info_data->Human.Age);
    }

    printf("\nEnter your Phone number: ");
    fgets(info_data->Human.PhoneNum, sizeof(info_data->Human.PhoneNum), stdin);

    printf("\nEnter your Home: ");
    fgets(info_data->Human.Home, sizeof(info_data->Human.Home), stdin);

    mq_send(id_std, (char *)&info_data, sizeof(Message), 0);
}

void display_info_ID(mqd_t id_std, long ID_info, Message *info_data, int n) {
    int check = 0;
    
    for (int i = 0; i < n; i++) {
        mq_receive(id_std, (char *)&info_data, sizeof(MAX_SIZE), 0);

        if (ID_info == info_data->prio_id) {
            printf("\nDisplay Infomation Student - ID: %li\n", ID_info);
            printf("\n--- Your Name: %s", info_data->Human.Name);
            printf("\n--- Your Age: %d\n", info_data->Human.Age);
            printf("\n--- Your Phone: %s", info_data->Human.PhoneNum);
            printf("\n--- Your Home: %s", info_data->Human.Home);

            check = 1;

            mq_send(id_std, (char *)&info_data, sizeof(Message), 0);
        }
        mq_send(id_std, (char *)&info_data, sizeof(Message), 0);
    }

    if (check == 0) {
        printf("\nThere is no student corresponding to the ID!");
    }
}

void display_all_info(mqd_t id_std, Message *info_data) {
    printf("\nDisplay all Information student!\n");

    while(mq_receive(id_std, (char *)&info_data, sizeof(info_data), 0) != -1) {
        printf("\n--------------------");
        printf("\nYour ID: %li", info_data->prio_id);
        printf("\nYour Name: %s", info_data->Human.Name);
        printf("\nYour Age: %d", info_data->Human.Age);
        printf("\nYour Phone: %s", info_data->Human.PhoneNum);
        printf("\nYour Home: %s", info_data->Human.Home);
    }
}

void delete_info(mqd_t id_std, long ID_info, Message *info_data) {
    printf("\nDelete ID info...");

    if (ID_info == info_data->prio_id) {
        printf("\nValid ID, information deleted!");
        mq_receive(id_std, (char *)&info_data, sizeof(info_data), 0);
        mq_send(id_std, (char *)&info_data, sizeof(info_data), 0);
    } else {
        printf("\nYour ID does not match!");
    }
}

int main(int argc, char const *argv[]) {
    Message temp, msque;
    Message *temp_var, *msque_var;
    int option;
    int n = 0;
    int check = 0;
    unsigned int ID;

    struct mq_attr attr;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 100;

    mqd_t mq_id = open(NAME_FILE, O_RDWR | O_CREAT | O_NONBLOCK, 0666, 0);
    mq_getattr(mq_id, &attr);

    while(1) {
        // Menu displays functions
        printf("\n| ------------------------------- |");
        printf("\n| --- Menu displays functions --- |");
        printf("\n|           ------------          |");
        printf("\n| 0 - Exit the program!           |");
        printf("\n| 1 - Enter Information student   |");
        printf("\n| 2 - Display Information student |");
        printf("\n| 3 - Display all Information     |");
        printf("\n| 4 - Delete Information student  |");
        printf("\n| ------------------------------- |\n\n");

        scanf("%d", &option);

        switch (option)
        {
            case 0:
                printf("\nExiting the program ...");
                exit(EXIT_SUCCESS);
                break;

            case 1:
                n++;
                temp_var = &temp;
                input_data(mq_id, temp_var);
                break;

            case 2:
                msque_var = &msque;
                printf("\nEnter the ID you want to display: ");
                scanf("%u", &ID);

                for (int i = 0; i < attr.mq_curmsgs; i++) {
                    if (mq_receive(mq_id, (char *)msque_var, MAX_SIZE, 0) == -1) {
                        printf("\nmq_receive() is failed!");
                        exit(0);
                    }

                    if (msque_var->prio_id == ID) {
                        printf("\nDisplay Infomation Student - ID: %u\n", ID);
                        printf("\n--- Your Name: %s", msque_var->Human.Name);
                        printf("\n--- Your Age: %d\n", msque_var->Human.Age);
                        printf("\n--- Your Phone: %s", msque_var->Human.PhoneNum);
                        printf("\n--- Your Home: %s", msque_var->Human.Home);

                        check = 1;

                        mq_send(mq_id, (const char *)msque_var, sizeof(Message), 0);
                        break;
                    }
                    mq_send(mq_id, (const char *)msque_var, sizeof(Message), 0);
                }

                if (check == 0) {
                    printf("\nThere is no student corresponding to the ID!");
                }
                check = 0;
                break;

            case 3:
                display_all_info(mq_id, &temp);
                break;

            case 4:
                printf("\nEnter the ID you want to delete: ");
                scanf("%u", &ID);
                delete_info(mq_id, ID, &temp);
                ID = 0;
                break;
            
            default:
                break;
        }
    }

    if(mq_close(mq_id) == -1) {
        perror("\nFail to close message queue!");
        return -2;
    }

    if(mq_unlink(NAME_FILE) == -1) {
        perror("\nFail to unlink message queue!");
        return -2;
    }

    return 0;
}