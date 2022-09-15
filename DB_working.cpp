#include<iostream>
#include<fstream>
#include"Header.h"

void menu() {
    std::cout << "--------Menu--------" << std::endl;
    std::cout << "1. load <filename>" << std::endl;
    std::cout << "2. save <filename>" << std::endl;
    std::cout << "3. add <date>, <number of rooms>, <number of floor>, <area>, <address>, <price>" << std::endl;
    std::cout << "4. del <ID>" << std::endl;
    std::cout << "5. print" << std::endl;
    std::cout << "6. print N" << std::endl;
    std::cout << "7. export <filename>" << std::endl;
    std::cout << "8. find ID" << std::endl;
    std::cout << "Input name of the command: ";
}

int get_command(const char* command) {
    char first_word[7];
    int counter = 0;
    while (command[counter] != ' ' && command[counter] != '\0' && counter < 7) {
        first_word[counter] = command[counter];
        ++counter;
    }
    if (counter == 7 || counter<3) {
        return 0;
    }
    else {
        first_word[counter] = '\0';
        if (!strcmp(first_word, "load")) {
            return 1;
        }
        else if (!strcmp(first_word, "save")) {
            return 2;
        }
        else if (!strcmp(first_word, "add")) {
            return 3;
        }
        else if (!strcmp(first_word, "del")) {
            return 4;
        }
        else if (!strcmp(first_word, "print")) {
            return 5;
        }
        else if (!strcmp(first_word, "export")) {
            return 6;
        }
        else if (!strcmp(first_word, "find")) {
            return 7;
        }
        else {
            return 0;
        }
    }
}

std::ostream& operator<<(std::ostream& out, const RoomForSale& flat) {
    out << flat.id << ". date: " << flat.date << ", rooms: " << flat.rooms << ", floor: " <<
        flat.floor << ", area: " << flat.area << ", address: " << flat.address << ", price: " << flat.price << std::endl;
    return out;
}

std::ofstream& operator<<(std::ofstream& outFile, const RoomForSale& flat) {
    outFile << flat.id << ". date: " << flat.date << ", rooms: " << flat.rooms << ", floor: " <<
        flat.floor << ", area: " << flat.area << ", address: " << flat.address << ", price: " << flat.price << std::endl;
    return outFile;
}

int MAX_ID(const DataBase& DB) {
    if (DB.count == 0) return 500000;
    int max_id = 0;
    for (int i = 0; i < DB.count; ++i) {
        if (DB.flat[i].id > max_id) {
            max_id = DB.flat[i].id;
        }
    }
    return max_id+1;
}

bool CheckLetters(const char* arr) {
    int counter = 0;
    while (arr[counter] != '\0') {
        if (arr[counter] < '0' || arr[counter]>'9') return false;
        ++counter;
    }
    return true;
}

int CheckDate(const char* day, int counter_day, const char* month, int counter_month, const char* year, int counter_year) {
    int month_ = 0, day_ = 0, year_ = 0;
    if (counter_day == 2) {
        if (day[0] == '0')
            day_ = day[1] - '0';
        else day_ = atoi(day);
    }
    if (counter_month == 2) {
        if (month[0] == '0')
            month_ = month[1] - '0';
        else month_ = atoi(month);
    }
    if (counter_year == 4) {
        year_ = atoi(year);
    }
    if (counter_day == 0 || counter_month == 0 || counter_year == 0) {
        return 1;
    }
    else if (CheckLetters(month) && !CheckLetters(day) && CheckLetters(year)) {
        return 2;
    }
    else if (counter_day > 2 || counter_day == 1) {
        return 3;
    }
    else if (counter_month > 2 || counter_month == 1) {
        return 4;
    }
    else if (month_ != 2 && (day_ == 0 || day_ > 31)) {
        return 5;
    }
    else if (month_ == 2 && day_ == 29 && !((year_ % 4 == 0 && year_ % 100 != 0) || year_ % 400 == 0)) {
        return 6;
    }
    else if (month_ == 2 && day_ > 29 && ((year_ % 4 == 0 && year_ % 100 != 0) || year_ % 400 == 0)) {
        return 7;
    }
    else if (month_ % 2 == 0 && day_ > 30) {
        return 8;
    }
    else if (!CheckLetters(month) && CheckLetters(day) && CheckLetters(year)) {
        return 9;
    }
    else if (month_ == 0 || month_ > 12) {
        return 10;
    }
    else if (counter_year != 4) {
        return 11;
    }
    else if (CheckLetters(month) && CheckLetters(day) && !CheckLetters(year)) {
        return 12;
    }
    return 0;
}

int SpacesAndCommaAfterWord(const char* command, int counter) {
    while (command[counter] != ',' && command[counter] != '\0') {
        ++counter;
    }
    if (command[counter] != '\0') ++counter;

    while (command[counter] == ' ') {
        ++counter;
    }
    return counter;
}

int StringsArgs(const char* command, int counter) {
    int arg_ = -1, counter_arg = 0;
    char arg[10];
    while (command[counter] != ' ' && command[counter] != ',' && command[counter] != '\0' && counter_arg<10) {
        arg[counter_arg] = command[counter];
        ++counter_arg;
        ++counter;
    }
    if (counter_arg == 10) {
        return -1;
    }
    arg[counter_arg] = '\0';
    if (!CheckLetters(arg) || counter_arg == 0) return -1;
    if (arg[0] != '0') {
        arg_ = atoi(arg);
    }
    return arg_;
}

int NumberOfCharactersInNumber(int number) {
    int cnt = 0;
    while (number) {
        number /= 10;
        ++cnt;
    }
    return cnt;
}

int FindRecord(const DataBase& DB, int id) {
    for (int i = 0; i < DB.count; ++i) {
        if (DB.flat[i].id == id) return i;
    }
    return -1;
}

bool CheckFilename(const char* filename, int counter_) {
    if (filename[counter_ - 4] == '.' && filename[counter_ - 3] == 't' &&
        filename[counter_ - 2] == 'x' && filename[counter_ - 1] == 't') {
        return true;
    }
    return false;
}



int addDB(DataBase& DB, const char* command, int id) {
    int counter = 0, counter_ = 0;
    char date[80];
    while (command[counter] == ' ' && command[counter] != '\0') {
        ++counter;
    }
    while (command[counter] != ' ' && command[counter] != '\0' && command[counter] != ',' && counter_<80) {
        date[counter_] = command[counter];
        ++counter;
        ++counter_;
    }
    date[counter_] = '\0';
    if (counter_ == 80) {
        return -1;
    }
    char day[20], month[20], year[40];
    counter_ = 0;
    int counter_day = 0, counter_month = 0, counter_year = 0;

    while (date[counter_] != '.' && date[counter_] != '\0' && date[counter_] != ',' && counter_day<20) {
        day[counter_day] = date[counter_];
        ++counter_day;
        ++counter_;
    }
    if (counter_day == 20) {
        return -1;
    }
    if (counter_day) {
        day[counter_day] = '\0';
    }
    if (date[counter_] != '\0') {
        ++counter_;
    }

    while (date[counter_] != '.' && date[counter_] != '\0' && date[counter_] != ',' && counter<20) {
        month[counter_month] = date[counter_];
        ++counter_month;
        ++counter_;
    }
    if (counter_month == 20) {
        return -1;
    }
    if (counter_month) {
        month[counter_month] = '\0';
    }
    if (date[counter_] != '\0') {
        ++counter_;
    }

    while (date[counter_] != '\0' && date[counter_] != ',' && date[counter_] != ' ' && counter_year<40) {
        year[counter_year] = date[counter_];
        ++counter_year;
        ++counter_;
    }
    if (counter_year == 40) {
        return -1;
    }
    if (counter_year) {
        year[counter_year] = '\0';
    }

    int error = CheckDate(day, counter_day, month, counter_month, year, counter_year);
    bool flag = true;
    if (error == 1) {
        std::cout << "Wrong date format: " << date << std::endl;
        flag = !flag;
    }
    else if (error > 0 && error < 9 && error != 4) {
        std::cout << "Day value is invalid: " << day << std::endl;
        flag = !flag;
    }
    else if (error == 4 || error > 8 && error < 11) {
        std::cout << "Month value is invalid: " << month << std::endl;
        flag = !flag;
    }
    else if (error > 10) {
        std::cout << "Year value is invalid: " << year << std::endl;
        flag = !flag;
    }

    if (!flag) return 1;

    counter = SpacesAndCommaAfterWord(command, counter);
    int rooms_ = StringsArgs(command, counter);
    if (rooms_ == -1) {
        return -1;
    }
    counter += NumberOfCharactersInNumber(rooms_);

    counter = SpacesAndCommaAfterWord(command, counter);
    int floor_ = StringsArgs(command, counter);
    if (floor_ == -1) {
        return -1;
    }
    counter += NumberOfCharactersInNumber(floor_);

    counter = SpacesAndCommaAfterWord(command, counter);
    int area_ = StringsArgs(command, counter);
    if (area_ == -1) {
        return -1;
    }
    counter += NumberOfCharactersInNumber(area_);

    counter = SpacesAndCommaAfterWord(command, counter);

    char address[65];
    int counter_address = 0;
    while (command[counter] != ',' && command[counter] != '\0' && counter_address<65) {
        address[counter_address] = command[counter];
        ++counter_address;
        ++counter;
    }
    if (counter_address == 65) {
        return -1;
    }
    address[counter_address] = '\0';
    counter = SpacesAndCommaAfterWord(command, counter);
    int price_ = StringsArgs(command, counter);
    if (price_ == -1) {
        return -1;
    }
    ++DB.count;
    RoomForSale* tmp = new RoomForSale[DB.count];
    for (int i = 0; i < DB.count - 1; ++i) {
        tmp[i] = DB.flat[i];
    }
    if (DB.flat)
        delete[] DB.flat;

    DB.flat = tmp;

    DB.flat[DB.count - 1].id = id;
    for (int i = 0; i < 11; ++i) {
        DB.flat[DB.count - 1].date[i] = date[i];
    }
    DB.flat[DB.count - 1].rooms = rooms_;
    DB.flat[DB.count - 1].floor = floor_;
    DB.flat[DB.count - 1].area = area_;
    for (int i = 0; i < counter_address; ++i) {
        DB.flat[DB.count - 1].address[i] = address[i];
    }
    DB.flat[DB.count - 1].address[counter_address] = '\0';
    DB.flat[DB.count - 1].price = price_;
    return 0;
}

int loadDB(DataBase& DB, const char* command) {
    int counter = 0, counter_ = 0;
    char filename[256];
    while (command[counter] == ' ' && command[counter] != '\0') {
        ++counter;
    }
    while (command[counter] != ' ' && command[counter] != '\0' && counter_<256) {
        filename[counter_] = command[counter];
        ++counter_;
        ++counter;
    }
    if (counter_ < 256 && counter_!=0) {
        filename[counter_] = '\0';
        std::ifstream inFile(filename, std::ios_base::binary);
        if (!inFile) {
            std::cout << "Can not open file " << filename << std::endl;
            return -1;
        }
        if (DB.flat) {
            delete[] DB.flat;
        }
        int count;
        inFile.read((char*)&count, sizeof(int));
        DB.count = count;
        DB.flat = new RoomForSale[count];
        inFile.read((char*)DB.flat, sizeof(RoomForSale) * DB.count);
        inFile.close();
    }
    else {
        std::cout << "Wrong filename" << std::endl;
    }
    return 0;
}

void saveDB(const DataBase& DB, const char* command) {
    int counter = 0, counter_ = 0;
    char filename[256];
    while (command[counter] == ' ' && command[counter] != '\0') {
        ++counter;
    }
    while (command[counter] != ' ' && command[counter] != '\0' && counter_<256) {
        filename[counter_] = command[counter];
        ++counter_;
        ++counter;
    }
    if (counter_ < 256 && counter_!=0) {
        filename[counter_] = '\0';
        std::ofstream outFile(filename, std::ios_base::binary);
        outFile.write((const char*)&DB.count, sizeof(int));
        outFile.write((const char*)DB.flat, sizeof(RoomForSale) * DB.count);
        outFile.close();
    }
    else {
        std::cout << "Wrong filename" << std::endl;
    }
}

void delDB(DataBase& DB, const char* command) {
    int counter = 0, counter_id = 0;
    while (command[counter] == ' ' && command[counter] != '\0') {
        ++counter;
    }
    char ID[10];
    while (command[counter] != ' ' && command[counter] != '\0' && counter_id < 10) {
        ID[counter_id] = command[counter];
        ++counter;
        ++counter_id;
    }
    if (counter_id != 10 && counter_id != 0) {
        ID[counter_id] = '\0';
        if (!CheckLetters(ID) || ID[0] == '0') {
            std::cout << "There are no record with this id" << std::endl;
        }
        else {
            int id = atoi(ID);
            if (FindRecord(DB, id) == -1) {
                std::cout << "There are no record with this id" << std::endl;
            }
            else {
                char decision;
                std::cout << "Are you sure? Y/N: ";
                do {
                    std::cin >> decision;
                } while (decision != 'Y' && decision != 'y' && decision != 'N' && decision != 'n');
                std::cin.ignore();
                if (decision == 'Y' || decision == 'y') {
                    RoomForSale* tmp = new RoomForSale[DB.count - 1];
                    int num_of_del = FindRecord(DB, id);
                    int cnt_tmp = 0, cnt_DB = 0;
                    while (cnt_tmp < DB.count - 1) {
                        if (cnt_DB != num_of_del) {
                            tmp[cnt_tmp] = DB.flat[cnt_DB];
                            ++cnt_tmp;
                        }
                        ++cnt_DB;
                    }
                    if (DB.flat)
                        delete[] DB.flat;
                    DB.flat = tmp;
                    --DB.count;
                    std::cout << "Record is successfully deleted" << std::endl;
                }
            }
        }
    }
    else {
        std::cout << "There are no record with this ID" << std::endl;
    }
}

void SortAndPrint(RoomForSale* tmp, int count) {
    int num_res = 0, k = 0;
    for (int i = 0; i < count - 1; ++i) {
        int k = i;
        for (int j = k + 1; j < count; ++j) {
            if (tmp[j].price < tmp[k].price) {
                k = j;
            }
        }
        if (i < k) {
            std::swap(tmp[k], tmp[i]);
        }
    }
    for (int i = 0; i < count; ++i) {
        std::cout << tmp[i];
    }
}

void modified_printDB(const DataBase& DB, int num_rooms) {
    int positive_res = 0;
    for (int i = 0; i < DB.count; ++i) {
        if (DB.flat[i].rooms == num_rooms) {
            ++positive_res;
        }
    }
    if (positive_res == 0) {
        std::cout << "There are no records satisfying the condition" << std::endl;
    }
    else {
        RoomForSale* tmp = new RoomForSale[positive_res];
        int j = 0;
        for (int i = 0; i < DB.count; ++i) {
            if (DB.flat[i].rooms == num_rooms) {
                tmp[j] = DB.flat[i];
                ++j;
            }
        }
        SortAndPrint(tmp, positive_res);
        delete[] tmp;
    }
}

void ChooseTypePrint(const DataBase& DB, const char* command) {
    if (DB.count != 0) {
        int counter = 0;
        while (command[counter] == ' ' && command[counter] != '\0') {
            ++counter;
        }
        if (command[counter] == '\0') {
            SortAndPrint(DB.flat,DB.count);
        }
        else {
            char num_rooms[10];
            int counter_ = 0;
            while (command[counter] != '\0' && command[counter] != ' ' && counter_<10) {
                num_rooms[counter_] = command[counter];
                ++counter;
                ++counter_;
            }
            if (counter_ == 10) {
                std::cout << "Wrong number of rooms" << std::endl;
            }
            else {
                num_rooms[counter_] = '\0';
                if (CheckLetters(num_rooms)) {
                    if (num_rooms[0] == '0') {
                        std::cout << "Wrong input" << std::endl;
                    }
                    else {
                        int num_rooms_ = atoi(num_rooms);
                        modified_printDB(DB, num_rooms_);
                    }
                }
                else {
                    std::cout << "Wrong input" << std::endl;
                }
            }
        }
    }
    else {
        std::cout << "There are no records in data base" << std::endl;
    }
}

void exportDB(const DataBase& DB, const char* command) {
    int counter = 0;
    while (command[counter] == ' ' && command[counter] != '\0') {
        ++counter;
    }
    if (command[counter] == '\0') {
        std::cout << "Wrong input" << std::endl;
    }
    else {
        char filename[256];
        int counter_ = 0;
        while (command[counter] != ' ' && command[counter] != '\0' && counter_<256) {
            filename[counter_] = command[counter];
            ++counter;
            ++counter_;
        }
        if (counter_ < 256 && counter_>3 && CheckFilename(filename, counter_)) {
            filename[counter_] = '\0';
            std::ofstream outFile(filename);
            if (!outFile) {
                std::cout << "Can not open file " << filename << std::endl;
                outFile.close();
            }
            else {
                if (DB.count != 0) {
                    for (int i = 0; i < DB.count; ++i) {
                        outFile << DB.flat[i];
                    }
                    outFile.close();
                    std::cout << "Data in the file " << filename << std::endl;
                }
                else {
                    std::cout << "There are no records in data base" << std::endl;
                }
            }
        }
        else {
            std::cout << "Wrong input" << std::endl;
        }
    }
}

void findDB(const DataBase& DB, const char* command) {
    int counter = 0, counter_ = 0;
    while (command[counter] == ' ' && command[counter] != '\0') {
        ++counter;
    }
    if (command[counter] == '\0') {
        std::cout << "Wrong input" << std::endl;
    }
    else {
        char ID[10];
        while (command[counter] != ' ' && command[counter] != '\0' && counter_<10) {
            ID[counter_] = command[counter];
            ++counter;
            ++counter_;
        }
        if (counter_ == 10) {
            std::cout << "There are no records with this ID" << std::endl;
        }
        else {
            ID[counter_] = '\0';
            if (ID[0] == '0' || !CheckLetters(ID)) {
                std::cout << "Wrong input" << std::endl;
            }
            else {
                int id = atoi(ID);
                int num_of_rec = -1;
                for (int i = 0; i < DB.count; ++i) {
                    if (DB.flat[i].id == id) {
                        num_of_rec = i;
                        break;
                    }
                }
                if (num_of_rec != -1) {
                    int positive_res = 0;
                    for (int i = 0; i < DB.count; ++i) {
                        if (DB.flat[i].rooms == DB.flat[num_of_rec].rooms &&
                            DB.flat[i].floor == DB.flat[num_of_rec].floor &&
                            ( DB.flat[num_of_rec].area * 0.8 <= DB.flat[i].area &&
                            DB.flat[num_of_rec].area * 1.2 >= DB.flat[i].area) && i != num_of_rec) {
                            ++positive_res;
                            std::cout << DB.flat[i];
                        }
                    }
                    if (!positive_res) {
                        std::cout << "There are no suitable records" << std::endl;
                    }
                }
                else {
                    std::cout << "There are no records with this ID" << std::endl;
                }
            }
        }
    }
}