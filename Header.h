#pragma once
struct RoomForSale {
    int id;
    char date[11];
    int rooms;
    int floor;
    int area;
    char address[65];
    int price;
};

struct DataBase {
    int count;
    RoomForSale* flat;
};

void menu();
int get_command(const char* command);
std::ostream& operator<<(std::ostream& out, const RoomForSale& flat);
std::ofstream& operator<<(std::ofstream& outFile, const RoomForSale& flat);
int MAX_ID(const DataBase& DB);
bool CheckLetters(const char* arr);
int CheckDate(const char* day, int counter_day, const char* month, int counter_month, const char* year, int counter_year);
int SpacesAndCommaAfterWord(const char* command, int counter);
int StringsArgs(const char* command, int counter);
int NumberOfCharactersInNumber(int number);
int FindRecord(const DataBase& DB, int id);
bool CheckFilename(const char* filename, int counter_);
int addDB(DataBase& DB, const char* command, int id);
int loadDB(DataBase& DB, const char* command);
void saveDB(const DataBase& DB, const char* command);
void delDB(DataBase& DB, const char* command);
void SortAndPrint(RoomForSale* tmp, int count);
void modified_printDB(const DataBase& DB, int num_rooms);
void ChooseTypePrint(const DataBase& DB, const char* command);
void exportDB(const DataBase& DB, const char* command);
void findDB(const DataBase& DB, const char* command);
