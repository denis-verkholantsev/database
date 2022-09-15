#include<iostream>
#include"Header.h"

int main() {
    DataBase DB = { 0, nullptr };
    char command[512];
    int id = 0;
    for (;;) {
        menu();
        std::cin.getline(command, 512);
        int counter = 0;
        while (command[counter] == ' ') {
            ++counter;
        }
        switch (get_command(command+counter)) {
        case 0: {
            std::cout << "Unknown command: ";
            while (command[counter] != ' ' && command[counter] != '\0') {
                std::cout << command[counter];
                ++counter;
            }
            std::cout << std::endl;
            break;
        }
        case 1: {
            loadDB(DB,command+counter+4); break;
        }
        case 2: {
            saveDB(DB, command+counter+4); break;
        }
        case 3: {
             int indicator = addDB(DB, command + counter + 3, MAX_ID(DB));
             if (indicator == -1) {
                 std::cout << "Wrong input" << std::endl;
             }
             else if(indicator!=1){
                 std::cout << "Record is successfully added" << std::endl;
             }
             break;
        }
        case 4: {
             delDB(DB, command+counter+3); break;
        }
        case 5: {
           ChooseTypePrint(DB,command+counter+5); break;
        }
        case 6: {
            exportDB(DB,command+counter+6); break;
        }
        case 7: {
           findDB(DB, command+counter+4); break;
        }
        }
    }
    return 0;
}