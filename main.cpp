#include <iostream>  // for input and output
#include <cctype>    // for toupper()
#include <vector>     // Input file is stored in a vector.
#include <cassert>    // For the assert statement used to validate file open.
#include <fstream>    // For file input and output.
#include <algorithm>
#include <iterator>
#include <string>
#include <iomanip>

using namespace std;

typedef vector < string > TSongs;

// songs class methods
class CSongs {
    TSongs & songs;

    public:
        int64_t insert(string name);
        int64_t find(string);
        int64_t findByName(string);
        int64_t getCount();
        string * getById(int64_t id);

    CSongs();
    ~CSongs();
    TSongs & getSongByFilter(string);
};

CSongs::CSongs(): songs( * new TSongs) {

};

// destructor
CSongs::~CSongs() {
    delete & songs;
};

// CSongs incert fucntion 
int64_t CSongs::insert(string name) {

    for (size_t i = 0; i < songs.size(); i++) {
        if (songs[i] == name) {
            return i;
        };
    }

    songs.emplace_back(name);
    return (songs.size() - 1);
};

// CSongs get by ID method
string * CSongs::getById(int64_t id) {
    if ((id >= 0) and(id < int64_t(songs.size()))) {
        return &(songs[id]);
    } else {
        return nullptr;
    }
};

// CSongs songs counter 
int64_t CSongs::getCount() {
    return songs.size();
};

typedef vector < string > TArtists;
typedef vector < string * > TArtistsP;
typedef vector < int64_t > TArtistsId;

//------------------------------------------------------------------------------------------------

// artists class methods 
class CArtists {
    TArtists & artists;

    public:
        CArtists();
    ~CArtists();
    int64_t insert(string name);
    int64_t getCount();
    string * getById(int64_t id);
    TArtistsId findAll(string str);
};

CArtists::CArtists(): artists( * new TArtists) {
};

// destructor
CArtists::~CArtists() {
    delete & artists;
};

// CArtists get by the ID method 
string * CArtists::getById(int64_t id) {
    if ((id >= 0) and(id < int64_t(artists.size()))) {
        return &(artists[id]);
    } else {
        return nullptr;
    }
};

// TArtist CArtists finder method
TArtistsId CArtists::findAll(string str) {
    TArtistsId recordset = * new TArtistsId;
    transform(str.begin(), str.end(), str.begin(), ::toupper);

    for (size_t i = 0; i < artists.size(); i++) {
        string artistUp = artists[i];
        transform(artistUp.begin(), artistUp.end(), artistUp.begin(), ::toupper);
        if (artistUp.find(str) != string::npos) {
            recordset.push_back(i);
        }
    }
    return recordset;
};

// CArtists incert method
int64_t CArtists::insert(string name) {
    for (size_t i = 0; i < artists.size(); i++) {
        if (artists[i] == name) {
            return i;
        }
    }
    artists.emplace_back(name);
    return (artists.size() - 1);
};

// CArtists counter method
int64_t CArtists::getCount() {
    return artists.size();
};

//------------------------------------------------------------------------------------------------

// TChart struct 
struct TChart {
    int year = 0;
    int month = 0;
    int day = 0;
    string date;
    int rank = 0;
    int64_t songId = 0;
    int64_t artistId = 0;
    int lastWeek = 0;
    int peakRank = 0;
    int weeksOnBoard = 0;
};

typedef vector < TChart > TCharts;
typedef vector < TChart * > TChartsP;

// TRecord struct
struct TRecord {
    string * song = nullptr;
    string * artist = nullptr;
    int count = 0;
    int rank = 0;
    int lastWeek = 0;
    string date;
};

typedef vector < TRecord > TRecordset;

//------------------------------------------------------------------------------------------------

//register fot the chart work 
//holds the register of songs and arrtists 
//has three methods 
// 1) finds songs using part of the artist's name that is ranked 1 
// 2) finds rank 1 songs in the given year interval 
// 3) finds songs with highest weekly climb and returns recordset
class CChartsRegister {
    TCharts & charts;
    CSongs & songs;
    CArtists & artists;

    public:
        CChartsRegister();
    ~CChartsRegister();
    void insert(string name);
    TRecordset getFilterTopOne(int yearStart, int yearEnd);
    TRecordset getFilterTopLong(int yearStart, int yearEnd);
    TRecordset getFilterMaxWeeklyClimb(int yearStart, int yearEnd);
    TRecordset getFilterArtisName(string str);
    int64_t getRecordsCount();
    int64_t getUnicSongsCount();
};

CChartsRegister::CChartsRegister(): charts( * new TCharts), songs( * new CSongs), artists( * new CArtists) {

};

// destructor
CChartsRegister::~CChartsRegister() {
    delete & charts;
    delete & songs;
    delete & artists;
};

// finds songs using part of the artist's name that is ranked 1 
TRecordset CChartsRegister::getFilterArtisName(string str) {
    TChartsP & recordsAll = * new TChartsP;
    TArtistsId findedArtists;
    TRecordset & recordset = * new TRecordset;

    findedArtists = artists.findAll(str);

    for (size_t index = 0; index < charts.size(); index++) {
        if (charts[index].rank == 1) {
            for (size_t i = 0; i < findedArtists.size(); i++) {
                if (charts[index].artistId == findedArtists[i]) {
                    recordsAll.push_back( & (charts[index]));
                    break;
                }
            }
        }
    }

    for (size_t index = 0; index < recordsAll.size(); index++) {

        TRecord record;
        record.song = songs.getById(recordsAll[index] -> songId);
        record.artist = artists.getById(recordsAll[index] -> artistId);
        record.rank = recordsAll[index] -> rank;
        record.date = recordsAll[index] -> date;
        recordset.push_back(record);
    }
    delete & recordsAll;
    return recordset;
}

// CChartsRegister records counter method 
int64_t CChartsRegister::getRecordsCount() {
    return charts.size();
}

// CChartsRegister unigue songs conter method
int64_t CChartsRegister::getUnicSongsCount() {
    return songs.getCount();
};

//finds rank 1 songs in the given year interval 
TRecordset CChartsRegister::getFilterTopOne(int yearStart, int yearEnd) {
    TChartsP & recordsAll = * new TChartsP;
    TRecordset & recordset = * new TRecordset;

    for (size_t i = 0; i < charts.size(); i++) {
        if ((charts[i].rank == 1) and(charts[i].year >= yearStart) and(charts[i].year <= yearEnd)) {
            recordsAll.push_back( & (charts[i]));
        }
    }

    int index = 0;
    while (recordsAll.size() > 0) {
        TRecord record;
        int64_t songId;
        int64_t artistId;
        record.song = songs.getById(recordsAll[index] -> songId);
        record.artist = artists.getById(recordsAll[index] -> artistId);
        record.count = 0;
        songId = recordsAll[index] -> songId;
        artistId = recordsAll[index] -> artistId;
        //recordsAll.erase( recordsAll.begin()+index);
        for (size_t i = 0; i < recordsAll.size(); i++) {
            if ((recordsAll[i] -> songId == songId) and(recordsAll[i] -> artistId == artistId)) {
                record.count++;
                recordsAll.erase(recordsAll.begin() + i);
                i--;
            }
        }
        recordset.push_back(record);
    }

    int max = 0;

    for (size_t index = 0; index < (recordset.size()); index++) {
        if (recordset[index].count > max) {
            max = recordset[index].count;
        }
    }

    for (size_t index = 0; index < recordset.size(); index++) {
        if (recordset[index].count < max) {
            recordset.erase(recordset.begin() + index);
            index--;
        }
    }

    delete & recordsAll;
    return recordset;
};

// songs that been longest in the weekly top and returns recordset 
TRecordset CChartsRegister::getFilterTopLong(int yearStart, int yearEnd) {
    TChartsP & recordsAll = * new TChartsP;
    TRecordset & recordset = * new TRecordset;
    TRecord record;

    for (size_t i = 0; i < charts.size(); i++) {
        if ((charts[i].year >= yearStart) and(charts[i].year <= yearEnd)) {
            recordsAll.push_back( & (charts[i]));
        }
    }

    if (recordsAll.size() == 0) {
        delete & recordsAll;
        return recordset;
    }

    int max = 0;
    TChart * maxPointer = nullptr;

    for (size_t index = 0; index < (recordsAll.size()); index++) {
        if (recordsAll[index] -> weeksOnBoard > max) {
            max = recordsAll[index] -> weeksOnBoard;
            maxPointer = recordsAll[index];
        }
    }

    record.song = songs.getById(maxPointer -> songId);
    record.artist = artists.getById(maxPointer -> artistId);
    record.count = max;
    recordset.push_back(record);

    delete & recordsAll;
    return recordset;
};

// function that finds songs with highest weekly climb and returns recordset
TRecordset CChartsRegister::getFilterMaxWeeklyClimb(int yearStart, int yearEnd) {
    TChartsP & recordsAll = * new TChartsP;
    TRecordset & recordset = * new TRecordset;

    for (size_t i = 0; i < charts.size(); i++) {
        if ((charts[i].year >= yearStart) and(charts[i].year <= yearEnd)) {
            if (charts[i].lastWeek > 0) {
                if (charts[i].rank < charts[i].lastWeek) {
                    recordsAll.push_back( & (charts[i]));
                }
            }
        }
    }

    if (recordsAll.size() == 0) {
        return recordset;
    }

    int max = 0;
    int maxNew = 0;

    for (size_t index = 0; index < recordsAll.size(); index++) {
        maxNew = recordsAll[index] -> lastWeek - recordsAll[index] -> rank;
        if (maxNew > max) {
            max = maxNew;
        }
    }

    for (size_t index = 0; index < recordsAll.size(); index++) {
        if ((recordsAll[index] -> lastWeek - recordsAll[index] -> rank) < max) {
            recordsAll.erase(recordsAll.begin() + index);
            index--;
        }
    }

    for (size_t index = 0; index < recordsAll.size(); index++) {
        TRecord record;
        record.song = songs.getById(recordsAll[index] -> songId);
        record.artist = artists.getById(recordsAll[index] -> artistId);
        record.rank = recordsAll[index] -> rank;
        record.lastWeek = recordsAll[index] -> lastWeek;
        record.date = recordsAll[index] -> date;
        record.count = abs(recordsAll[index] -> rank - recordsAll[index] -> lastWeek);
        recordset.push_back(record);
    }

    return recordset;
};

// CChartsRegister insert method
void CChartsRegister::insert(string line) {
    TChart record;
    size_t index = 0;
    // обработка даты
    index = line.find(',');
    string date = line.substr(0, index);
    record.date = date;
    record.month = stoi(date.substr(0, date.find('/')));
    date = date.substr(date.find('/') + 1);
    record.day = stoi(date.substr(0, date.find('/')));
    date = date.substr(date.find('/') + 1);
    record.year = stoi(date);

    // обработка ранга
    line = line.substr(index + 1);
    index = line.find(',');
    record.rank = (atoi(line.substr(0, index).c_str()));

    //обработка песни
    line = line.substr(index + 1);
    index = line.find(',');
    record.songId = songs.insert(line.substr(0, index));

    //обработка артиста
    line = line.substr(index + 1);
    index = line.find(',');
    record.artistId = artists.insert(line.substr(0, index));

    //обработка Прошлой недели
    line = line.substr(index + 1);
    index = line.find(',');
    record.lastWeek = (atoi(line.substr(0, index).c_str()));

    //обработка Максимально ранга
    line = line.substr(index + 1);
    index = line.find(',');
    record.peakRank = (atoi(line.substr(0, index).c_str()));

    //обработка количества недель в топе
    line = line.substr(index + 1);
    record.weeksOnBoard = (atoi(line.c_str()));

    charts.emplace_back(record);
};

//------------------------------------------------------------------------------------------------

// filereader to read the data from csv file
void readFile(string fileName, CChartsRegister & charts) {
    ifstream fileStream;
    fileStream.open(fileName);
    assert(fileStream.fail() == false);
    string line = "";
    getline(fileStream, line);

    while (getline(fileStream, line)) {
        charts.insert(line);
        //if (count++ > 3000) break;
    }
};

// Display welcome message, introducing the user to the program and describing the instructions for the game
void displayWelcomeMessage() {
    cout << "Program 4: BillBoard Analysis " << endl;
    cout << "CS 141, Spring 2022, UIC " << endl << " " << endl;
    cout << "This program will analyze weekly Billboard data spanning from 1960 - 2020." << endl << endl;
    cout << "Select file option:" << endl;
    cout << "   1. To analyze charts top 50: 1960 - 1980 data file" << endl;
    cout << "   2. To analyze charts top 50: 1981 - 2000 data file" << endl;
    cout << "   3. To analyze charts top 50: 2001 - 2020 data file" << endl;
} //end displayWelcomeMessage()

// function to display the choices after the file oprions.
void displayChoice() {
    cout << "Select a menu option: " << endl;
    cout << "   1. Display overall information about the data" << endl;
    cout << "   2. Display the Billboard info of the song with the most #1 occurrences for a given decade or year" << endl;
    cout << "   3. Display the Billboard info for the most long-lasting song on the charts for a given decade or year" << endl;
    cout << "   4. Display the Billboard info for the song with the greatest weekly climb on the charts given a decade or year" << endl;
    cout << "   5. Artist Search - Return the Billboard info for records that matches user input for artist search" << endl;
    cout << "   6. Exit" << endl;
} //end of displayChoice()

// main menu of the program that asks for the input, couts the sentences and returns the result
void showMenu() {

    // initialize
    int choiceMain;
    int choiceSecond;
    string fileName;
    string artist;
    int yearUser;
    char yearOrDeca;
    displayWelcomeMessage();
    TRecordset rs;
    CChartsRegister & charts = * new CChartsRegister;
    cout << "Your choice --> ";
    cin >> choiceMain;
    cout << endl;

    // choice of the first file
    if (choiceMain == 1) {
        fileName = "charts_top50_1960_1980.csv";
        readFile(fileName, charts);
        cout << endl;
        displayChoice();
        cout << "Your choice --> ";
        cin >> choiceSecond;
        cout << endl;
        while (choiceSecond != 6) {
            if (choiceSecond == 1) {
                cout << "	Total number of rows: " << charts.getRecordsCount() << endl;
                cout << "	Number of unique songs represented in the dataset: " << charts.getUnicSongsCount() << endl;
            } else if (choiceSecond == 2) {
                while (true) {

                    cout << "Enter D to select a decade or Y to select a year." << endl;
                    cout << "Your choice --> ";
                    cin >> yearOrDeca;
                    yearOrDeca = toupper(yearOrDeca);
                    if (yearOrDeca == 'Y'
                        or yearOrDeca == 'D') {
                        break;
                    }
                    cout << "Invalid entry. Try again." << endl;
                }
                switch (yearOrDeca) {
                case 'Y':
                    cout << endl << "Enter the year you would like to choose (e.g. 2001)." << endl;
                    cin >> yearUser;
                    if (yearUser < 1960 or yearUser > 1980) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        cout << endl;
                        break;
                    }
                    cout << endl << endl << "The song(s) with the most #1 occurrences for selected time period is:" << endl;
                    rs = charts.getFilterTopOne(yearUser, yearUser);

                    for (size_t i = 0; i < rs.size(); i++) {
                        cout << endl;
                        cout << "	Song Title: " << * (rs[i].song) << endl;
                        cout << "	Artist: " << * (rs[i].artist) << endl;
                        cout << "	# of occurrences: " << rs[i].count << endl;
                        cout << endl;
                    }
                    break;

                case 'D':
                    cout << endl << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
                    cin >> yearUser;
                    if (yearUser < 1960 or yearUser > 1980) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        cout << endl;
                        break;
                    }

                    if (yearUser >= 1960 and yearUser <= 1969) {
                        rs = charts.getFilterTopOne(1960, 1969);
                    } else if (yearUser >= 1970 and yearUser <= 1979) {
                        rs = charts.getFilterTopOne(1970, 1979);
                    } else if (yearUser == 1980) {
                        rs = charts.getFilterTopOne(1980, 1980);

                    }
                    cout << endl << endl << "The song(s) with the most #1 occurrences for selected time period is:" << endl;

                    for (size_t i = 0; i < rs.size(); i++) {
                        cout << "	Song Title: " << * (rs[i].song) << endl;
                        cout << "	Artist: " << * (rs[i].artist) << endl;
                        cout << "	# of occurrences: " << rs[i].count << endl;
                    }
                    break;
                    break;

                default:
                    break;
                }

            } else if (choiceSecond == 3) {
                while (true) {

                    cout << "Enter D to select a decade or Y to select a year." << endl;
                    cout << "Your choice --> ";
                    cin >> yearOrDeca;
                    yearOrDeca = toupper(yearOrDeca);
                    if (yearOrDeca == 'Y'
                        or yearOrDeca == 'D') {
                        break;
                    }
                    cout << "Invalid entry. Try again." << endl;
                }
                switch (yearOrDeca) {
                case 'Y':
                    cout << endl << "Enter the year you would like to choose (e.g. 2001)." << endl;
                    cin >> yearUser;
                    if (yearUser < 1960 or yearUser > 1980) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        cout << endl;
                        break;
                    }
                    rs = charts.getFilterTopLong(yearUser, yearUser);
                    if (rs.size() == 0) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        break;
                    }

                    cout << endl << endl << "The song with the highest number of weeks on the charts is:" << endl;

                    cout << endl;
                    cout << "    " << * (rs[0].song) << " by " << * (rs[0].artist) << " with " << rs[0].count << " weeks on the chart." << endl;
                    cout << endl;

                    break;

                case 'D':
                    cout << endl << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
                    cin >> yearUser;
                    if (yearUser < 1960 or yearUser > 1980) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        cout << endl;
                        break;
                    }

                    if (yearUser >= 1960 and yearUser <= 1969) {
                        rs = charts.getFilterTopLong(1960, 1969);
                    } else if (yearUser >= 1970 and yearUser <= 1979) {
                        rs = charts.getFilterTopLong(1970, 1979);

                    } else if (yearUser == 1980) {
                        rs = charts.getFilterTopLong(1980, 1980);

                    }
                    if (rs.size() == 0) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        break;
                    }

                    cout << endl << endl << "The song with the highest number of weeks on the charts is:" << endl;

                    cout << endl;
                    cout << "    " << * (rs[0].song) << " by " << * (rs[0].artist) << " with " << rs[0].count << " weeks on the chart." << endl;
                    cout << endl;

                    break;

                default:
                    break;
                }
            } else if (choiceSecond == 4) {
                while (true) {

                    cout << "Enter D to select a decade or Y to select a year." << endl;
                    cout << "Your choice --> ";
                    cin >> yearOrDeca;
                    yearOrDeca = toupper(yearOrDeca);
                    if (yearOrDeca == 'Y'
                        or yearOrDeca == 'D') {
                        break;
                    }
                    cout << "Invalid entry. Try again." << endl;
                }
                switch (yearOrDeca) {
                case 'Y':
                    cout << endl << "Enter the year you would like to choose (e.g. 2001)." << endl;
                    cin >> yearUser;
                    if (yearUser < 1960 or yearUser > 1980) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        cout << endl;
                        break;
                    }
                    rs = charts.getFilterMaxWeeklyClimb(yearUser, yearUser);
                    if (rs.size() == 0) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        break;
                    }

                    cout << endl << endl << "The song(s) with the greatest climb from previous week to current week position: " << endl;

                    for (size_t i = 0; i < rs.size(); i++) {
                        cout << endl;
                        cout << "	Song Title: " << * (rs[i].song) << endl;
                        cout << "	Artist: " << * (rs[i].artist) << endl;
                        cout << "	Week of: " << rs[i].date << endl;
                        cout << "	Previous Week Position: " << rs[i].lastWeek << endl;
                        cout << "	Current Week Position: " << rs[i].rank << endl;
                        cout << "	Difference of " << rs[i].count << " between previous week and current week position" << endl;
                        cout << endl;
                    }

                    break;

                case 'D':
                    cout << endl << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
                    cin >> yearUser;
                    if (yearUser < 1960 or yearUser > 1980) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        cout << endl;
                        break;
                    }

                    cout << endl << endl << "The song(s) with the greatest climb from previous week to current week position: " << endl;
                    if (yearUser >= 1960 and yearUser <= 1969) {
                        rs = charts.getFilterMaxWeeklyClimb(1960, 1969);
                    } else if (yearUser >= 1970 and yearUser <= 1979) {
                        rs = charts.getFilterMaxWeeklyClimb(1970, 1979);

                    } else if (yearUser == 1980) {
                        rs = charts.getFilterMaxWeeklyClimb(1980, 1980);

                    }

                    for (size_t i = 0; i < rs.size(); i++) {
                        cout << endl;
                        cout << "	Song Title: " << * (rs[i].song) << endl;
                        cout << "	Artist: " << * (rs[i].artist) << endl;
                        cout << "	Week of: " << rs[i].date << endl;
                        cout << "	Previous Week Position: " << rs[i].lastWeek << endl;
                        cout << "	Current Week Position: " << rs[i].rank << endl;
                        cout << "	Difference of " << rs[i].count << " between previous week and current week position" << endl;
                        cout << endl;
                    }
                    break;

                default:
                    break;
                }
            } else if (choiceSecond == 5) {
                cout << "Enter search text to retrieve first 10 records of #1 songs that match by artist name: " << endl;
                cin.clear();
                cin.sync();
                cin.ignore(1);
                getline(cin, artist, '\n');
                rs = charts.getFilterArtisName(artist);
                if (rs.size() == 0) {
                    cout << "No matching artists were found." << endl;
                } else {
                    cout << "Retrieval of first 10 #1 records found based upon search by artist name: " << endl;
                    for (size_t i = 0; i < 10 and i < rs.size(); i++) {
                        cout << i + 1 << ")  Song: " << * (rs[i].song) << endl;
                        cout << "    Artist: " << * (rs[i].artist) << endl;
                        cout << "    Week of: " << rs[i].date << endl;
                        cout << "    Week Position: " << rs[i].rank << endl;

                    }
                }

            } else {
                cout << "Invalid value.  Please re-enter a value from the menu options below." << endl << endl;
            }
            displayChoice();
            cout << "Your choice --> ";
            cin >> choiceSecond;
        } //end of while.
    } //end of if.

    // choice of the second file
    else if (choiceMain == 2) {
        fileName = "charts_top50_1981_2000.csv";
        readFile(fileName, charts);
        //fileReader(sizeChart, date, rank, songName, artist, lastWeek, peakRank, weeksBoard, fileName);
        cout << endl;
        displayChoice();
        cout << "Your choice --> ";
        cin >> choiceSecond;
        cout << endl;
        while (choiceSecond != 6) {
            if (choiceSecond == 1) {
                cout << "	Total number of rows: " << charts.getRecordsCount() << endl;
                cout << "	Number of unique songs represented in the dataset: " << charts.getUnicSongsCount() << endl;
            } else if (choiceSecond == 2) {
                while (true) {

                    cout << "Enter D to select a decade or Y to select a year." << endl;
                    cout << "Your choice --> ";
                    cin >> yearOrDeca;
                    yearOrDeca = toupper(yearOrDeca);
                    if (yearOrDeca == 'Y'
                        or yearOrDeca == 'D') {
                        break;
                    }
                    cout << "Invalid entry. Try again." << endl;
                }
                switch (yearOrDeca) {
                case 'Y':
                    cout << endl << "Enter the year you would like to choose (e.g. 2001)." << endl;
                    cin >> yearUser;

                    if (yearUser < 1981 or yearUser > 2000) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        cout << endl;
                        break;
                    }
                    rs = charts.getFilterTopOne(yearUser, yearUser);
                    cout << endl << endl << "The song(s) with the most #1 occurrences for selected time period is:" << endl;

                    for (size_t i = 0; i < rs.size(); i++) {
                        cout << endl;
                        cout << "	Song Title: " << * (rs[i].song) << endl;
                        cout << "	Artist: " << * (rs[i].artist) << endl;
                        cout << "	# of occurrences: " << rs[i].count << endl;
                        cout << endl;
                    }
                    break;

                case 'D':

                    cout << endl << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
                    cin >> yearUser;
                    if (yearUser < 1980 or yearUser > 2000) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        cout << endl;
                        break;
                    }
                    if (yearUser >= 1980 and yearUser <= 1989) {
                        rs = charts.getFilterTopOne(1981, 1989);
                    } else if (yearUser >= 1990 and yearUser <= 1999) {
                        rs = charts.getFilterTopOne(1990, 1999);

                    } else if (yearUser == 2000) {
                        rs = charts.getFilterTopOne(2000, 2000);

                    }
                    cout << endl << endl << "The song(s) with the most #1 occurrences for selected time period is:" << endl;

                    for (size_t i = 0; i < rs.size(); i++) {
                        cout << endl;
                        cout << "	Song Title: " << * (rs[i].song) << endl;
                        cout << "	Artist: " << * (rs[i].artist) << endl;
                        cout << "	# of occurrences: " << rs[i].count << endl;
                        cout << endl;
                    }
                    break;

                default:
                    break;
                }
            } else if (choiceSecond == 3) {
                while (true) {

                    cout << "Enter D to select a decade or Y to select a year." << endl;
                    cout << "Your choice --> ";
                    cin >> yearOrDeca;
                    yearOrDeca = toupper(yearOrDeca);
                    if (yearOrDeca == 'Y'
                        or yearOrDeca == 'D') {
                        break;
                    }
                    cout << "Invalid entry. Try again." << endl;
                }
                switch (yearOrDeca) {
                case 'Y':
                    cout << endl << "Enter the year you would like to choose (e.g. 2001)." << endl;
                    cin >> yearUser;
                    if (yearUser < 1981 or yearUser > 2000) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        cout << endl;
                        break;
                    }
                    rs = charts.getFilterTopLong(yearUser, yearUser);
                    if (rs.size() == 0) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        break;
                    }

                    cout << endl << endl << "The song with the highest number of weeks on the charts is:" << endl;
                    cout << endl;
                    cout << "    " << * (rs[0].song) << " by " << * (rs[0].artist) << " with " << rs[0].count << " weeks on the chart." << endl;
                    cout << endl;

                    break;

                case 'D':
                    cout << endl << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
                    cin >> yearUser;
                    if (yearUser < 1980 or yearUser > 2000) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        cout << endl;
                        break;
                    }

                    if (yearUser >= 1980 and yearUser <= 1989) {
                        rs = charts.getFilterTopLong(1981, 1989);
                    } else if (yearUser >= 1990 and yearUser <= 1999) {
                        rs = charts.getFilterTopLong(1990, 1999);

                    } else if (yearUser == 2000) {
                        rs = charts.getFilterTopLong(2000, 2000);

                    }
                    if (rs.size() == 0) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        break;

                    }

                    cout << endl << endl << "The song with the highest number of weeks on the charts is:" << endl;

                    cout << endl;
                    cout << "    " << * (rs[0].song) << " by " << * (rs[0].artist) << " with " << rs[0].count << " weeks on the chart." << endl;
                    cout << endl;

                    break;

                default:
                    break;
                }
            } else if (choiceSecond == 4) {
                while (true) {

                    cout << "Enter D to select a decade or Y to select a year." << endl;
                    cout << "Your choice --> ";
                    cin >> yearOrDeca;
                    yearOrDeca = toupper(yearOrDeca);
                    if (yearOrDeca == 'Y'
                        or yearOrDeca == 'D') {
                        break;
                    }
                    cout << "Invalid entry. Try again." << endl;
                }
                switch (yearOrDeca) {
                case 'Y':
                    cout << endl << "Enter the year you would like to choose (e.g. 2001)." << endl;
                    cin >> yearUser;
                    if (yearUser < 1981 or yearUser > 2000) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        cout << endl;
                        break;
                    }
                    cout << endl << endl << "The song(s) with the greatest climb from previous week to current week position: " << endl;
                    rs = charts.getFilterMaxWeeklyClimb(yearUser, yearUser);

                    for (size_t i = 0; i < rs.size(); i++) {
                        cout << endl;
                        cout << "	Song Title: " << * (rs[i].song) << endl;
                        cout << "	Artist: " << * (rs[i].artist) << endl;
                        cout << "	Week of: " << rs[i].date << endl;
                        cout << "	Previous Week Position: " << rs[i].lastWeek << endl;
                        cout << "	Current Week Position: " << rs[i].rank << endl;
                        cout << "	Difference of " << rs[i].count << " between previous week and current week position" << endl;
                        cout << endl;
                    }
                    break;

                case 'D':
                    cout << endl << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
                    cin >> yearUser;
                    if (yearUser < 1980 or yearUser > 2000) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        cout << endl;
                        break;
                    }

                    cout << endl << endl << "The song(s) with the greatest climb from previous week to current week position: " << endl;

                    if (yearUser >= 1980 and yearUser <= 1989) {
                        rs = charts.getFilterMaxWeeklyClimb(1981, 1989);
                    } else if (yearUser >= 1990 and yearUser <= 1999) {
                        rs = charts.getFilterMaxWeeklyClimb(1990, 1999);

                    } else if (yearUser == 2000) {
                        rs = charts.getFilterMaxWeeklyClimb(2000, 2000);

                    }

                    for (size_t i = 0; i < rs.size(); i++) {
                        cout << "	Song Title: " << * (rs[i].song) << endl;
                        cout << "	Artist: " << * (rs[i].artist) << endl;
                        cout << "	Week of: " << rs[i].date << endl;
                        cout << "	Previous Week Position: " << rs[i].lastWeek << endl;
                        cout << "	Current Week Position: " << rs[i].rank << endl;
                        cout << "	Difference of " << rs[i].count << " between previous week and current week position" << endl;
                    }
                    break;

                default:
                    break;
                }
            } else if (choiceSecond == 5) {
                cout << "Enter search text to retrieve first 10 records of #1 songs that match by artist name: " << endl;
                cin.clear();
                cin.sync();
                cin.ignore(1);
                getline(cin, artist, '\n');
                rs = charts.getFilterArtisName(artist);
                if (rs.size() == 0) {
                    cout << "No matching artists were found." << endl;
                } else {
                    cout << "Retrieval of first 10 #1 records found based upon search by artist name: " << endl;
                    for (size_t i = 0; i < 10 and i < rs.size(); i++) {
                        cout << i + 1 << ")  Song: " << * (rs[i].song) << endl;
                        cout << "    Artist: " << * (rs[i].artist) << endl;
                        cout << "    Week of: " << rs[i].date << endl;
                        cout << "    Week Position: " << rs[i].rank << endl;

                    }
                }
            } else {
                cout << "Invalid value.  Please re-enter a value from the menu options below." << endl << endl;
            }
            displayChoice();
            cout << "Your choice --> ";
            cin >> choiceSecond;
        } //end of while.

    // choice of the third file
    } else if (choiceMain == 3) {
        fileName = "charts_top50_2001_2020.csv";
        readFile(fileName, charts);
        //	fileReader(sizeChart, date, rank, songName, artist, lastWeek, peakRank, weeksBoard, fileName);
        cout << endl;
        displayChoice();
        cout << "Your choice --> ";
        cin >> choiceSecond;
        cout << endl;
        while (choiceSecond != 6) {
            if (choiceSecond == 1) {
                cout << "	Total number of rows: " << charts.getRecordsCount() << endl;
                cout << "	Number of unique songs represented in the dataset: " << charts.getUnicSongsCount() << endl;
            } else if (choiceSecond == 2) {
                while (true) {

                    cout << "Enter D to select a decade or Y to select a year." << endl;
                    cout << "Your choice --> ";
                    cin >> yearOrDeca;
                    yearOrDeca = toupper(yearOrDeca);
                    if (yearOrDeca == 'Y'
                        or yearOrDeca == 'D') {
                        break;
                    }
                    cout << "Invalid entry. Try again." << endl;
                }
                switch (yearOrDeca) {
                case 'Y':
                    cout << endl << "Enter the year you would like to choose (e.g. 2001)." << endl;
                    cin >> yearUser;

                    if (yearUser < 2001 or yearUser > 2020) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        cout << endl;
                        break;
                    }

                    rs = charts.getFilterTopOne(yearUser, yearUser);
                    cout << endl << endl << "The song(s) with the most #1 occurrences for selected time period is:" << endl;

                    for (size_t i = 0; i < rs.size(); i++) {
                        cout << endl;
                        cout << "	Song Title: " << * (rs[i].song) << endl;
                        cout << "	Artist: " << * (rs[i].artist) << endl;
                        cout << "	# of occurrences: " << rs[i].count << endl;
                        cout << endl;
                    }
                    break;

                case 'D':

                    cout << endl << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
                    cin >> yearUser;
                    if (yearUser < 2000 or yearUser > 2020) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        cout << endl;
                        break;
                    }
                    if (yearUser >= 2000 and yearUser <= 2009) {
                        rs = charts.getFilterTopOne(2001, 2009);
                    } else if (yearUser >= 2010 and yearUser <= 2019) {
                        rs = charts.getFilterTopOne(2010, 2019);

                    } else if (yearUser == 2020) {
                        rs = charts.getFilterTopOne(2020, 2020);

                    }
                    cout << endl << endl << "The song(s) with the most #1 occurrences for selected time period is:" << endl;

                    for (size_t i = 0; i < rs.size(); i++) {
                        cout << endl;
                        cout << "	Song Title: " << * (rs[i].song) << endl;
                        cout << "	Artist: " << * (rs[i].artist) << endl;
                        cout << "	# of occurrences: " << rs[i].count << endl;
                        cout << endl;
                    }
                    break;

                default:
                    break;
                }
            } else if (choiceSecond == 3) {
                while (true) {

                    cout << "Enter D to select a decade or Y to select a year." << endl;
                    cout << "Your choice --> ";
                    cin >> yearOrDeca;
                    yearOrDeca = toupper(yearOrDeca);
                    if (yearOrDeca == 'Y'
                        or yearOrDeca == 'D') {
                        break;
                    }
                    cout << "Invalid entry. Try again." << endl;
                }
                switch (yearOrDeca) {
                case 'Y':
                    cout << endl << "Enter the year you would like to choose (e.g. 2001)." << endl;
                    cin >> yearUser;
                    if (yearUser < 2001 or yearUser > 2020) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        cout << endl;
                        break;
                    }
                    rs = charts.getFilterTopLong(yearUser, yearUser);

                    if (rs.size() == 0) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        break;
                    }

                    cout << endl << endl << "The song with the highest number of weeks on the charts is:" << endl;
                    cout << endl;
                    cout << "    " << * (rs[0].song) << " by " << * (rs[0].artist) << " with " << rs[0].count << " weeks on the chart." << endl;
                    cout << endl;

                    break;

                case 'D':
                    cout << endl << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
                    cin >> yearUser;
                    if (yearUser < 2000 or yearUser > 2020) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        cout << endl;
                        break;
                    }
                    if (yearUser >= 2000 and yearUser <= 2009) {
                        rs = charts.getFilterTopLong(2001, 2009);
                    } else if (yearUser >= 2010 and yearUser <= 2019) {
                        rs = charts.getFilterTopLong(2010, 2019);

                    } else if (yearUser == 2020) {
                        rs = charts.getFilterTopLong(2020, 2020);

                    }
                    if (rs.size() == 0) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        break;
                    }

                    cout << endl << endl << "The song with the highest number of weeks on the charts is:" << endl;

                    cout << endl;
                    cout << "    " << * (rs[0].song) << " by " << * (rs[0].artist) << " with " << rs[0].count << " weeks on the chart." << endl;
                    cout << endl;

                    break;

                default:
                    break;
                }
            } else if (choiceSecond == 4) {
                while (true) {

                    cout << "Enter D to select a decade or Y to select a year." << endl;
                    cout << "Your choice --> ";
                    cin >> yearOrDeca;
                    yearOrDeca = toupper(yearOrDeca);
                    if (yearOrDeca == 'Y'
                        or yearOrDeca == 'D') {
                        break;
                    }
                    cout << "Invalid entry. Try again." << endl;
                }
                switch (yearOrDeca) {
                case 'Y':
                    cout << endl << "Enter the year you would like to choose (e.g. 2001)." << endl;
                    cin >> yearUser;
                    if (yearUser < 2001 or yearUser > 2020) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        cout << endl;
                        break;
                    }
                    cout << endl << endl << "The song(s) with the greatest climb from previous week to current week position: " << endl;
                    rs = charts.getFilterMaxWeeklyClimb(yearUser, yearUser);
                    if (rs.size() == 0) {

                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        break;
                    }

                    for (size_t i = 0; i < rs.size(); i++) {
                        cout << endl;
                        cout << "	Song Title: " << * (rs[i].song) << endl;
                        cout << "	Artist: " << * (rs[i].artist) << endl;
                        cout << "	Week of: " << rs[i].date << endl;
                        cout << "	Previous Week Position: " << rs[i].lastWeek << endl;
                        cout << "	Current Week Position: " << rs[i].rank << endl;
                        cout << "	Difference of " << rs[i].count << " between previous week and current week position" << endl;
                        cout << endl;
                    }
                    break;

                case 'D':
                    cout << endl << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
                    cin >> yearUser;
                    if (yearUser < 2000 or yearUser > 2020) {
                        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
                        cout << endl;
                        break;
                    }
                    cout << endl << endl << "The song(s) with the greatest climb from previous week to current week position: " << endl;

                    if (yearUser >= 2000 and yearUser <= 2009) {
                        rs = charts.getFilterMaxWeeklyClimb(2001, 2009);
                    } else if (yearUser >= 2010 and yearUser <= 2019) {
                        rs = charts.getFilterMaxWeeklyClimb(2010, 2019);

                    } else if (yearUser == 2020) {
                        rs = charts.getFilterMaxWeeklyClimb(2020, 2020);

                    }

                    for (size_t i = 0; i < rs.size(); i++) {
                        cout << endl;
                        cout << "	Song Title: " << * (rs[i].song) << endl;
                        cout << "	Artist: " << * (rs[i].artist) << endl;
                        cout << "	Week of: " << rs[i].date << endl;
                        cout << "	Previous Week Position: " << rs[i].lastWeek << endl;
                        cout << "	Current Week Position: " << rs[i].rank << endl;
                        cout << "	Difference of " << rs[i].count << " between previous week and current week position" << endl;
                        cout << endl;
                    }
                    break;

                default:
                    break;
                }
            } else if (choiceSecond == 5) {
                cout << "Enter search text to retrieve first 10 records of #1 songs that match by artist name: " << endl;
                cin.clear();
                cin.sync();
                cin.ignore(1);
                getline(cin, artist, '\n');
                rs = charts.getFilterArtisName(artist);
                if (rs.size() == 0) {
                    cout << "No matching artists were found." << endl;
                } else {
                    cout << "Retrieval of first 10 #1 records found based upon search by artist name: " << endl;
                    for (size_t i = 0; i < 10 and i < rs.size(); i++) {
                        cout << i + 1 << ")  Song: " << * (rs[i].song) << endl;
                        cout << "    Artist: " << * (rs[i].artist) << endl;
                        cout << "    Week of: " << rs[i].date << endl;
                        cout << "    Week Position: " << rs[i].rank << endl;

                    }
                }
            } else {
                cout << "Invalid value.  Please re-enter a value from the menu options below." << endl << endl;
            }
            displayChoice();
            cout << "Your choice --> ";
            cin >> choiceSecond;
        } //end of while.

    // wrong choice 
    } else {
        cout << "Invalid value. Exiting Program.";
    }

}

// main
int main() {
        showMenu();
        return 0;
}