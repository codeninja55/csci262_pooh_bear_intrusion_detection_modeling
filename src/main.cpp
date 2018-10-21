/*********************************************************************************
* CSCI262 (Spring 2018) - Assignment 03
* Pooh Bear Intrusion Detection System main.cpp
* Purpose: main() driver for implementation of specifications
*
* @version 0.7-dev
* @date 2018.10.21
*
* @authors Dinh Che (codeninja55) & Duong Le (daltonle)
* Emails andrew at codeninja55.me & duong.daltonle at gmail.com
* Students Dinh Che (5721970 | dbac496) & Duong Le (5560536 | ndl991)
*********************************************************************************/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string.h>
#include <cstring>
#include <fstream>
#include "Vehicles.h"
#include "ActivityEngine.h"
#include "AnalysisEngine.h"
#include "AlertEngine.h"
using namespace std;

#define BUFFER_SZ 100
#ifdef __linux__
    char OS[] = "linux";
#elif _linux_
    char OS[] = "linux";
#elif _WIN32
    char OS[] = "win";
#elif _WIN64
    char OS[] = "win";
#else
    char OS[] = "linux";
#endif

/* STRUCT DEFINITION */

/* GLOBAL VARIABLES */
unsigned int g_n_vehicles = 0;
unsigned g_days = 0;

/* FUNCTION PROTOTYPES */
void check_directories();
void read_vehicles_file(ifstream &fin, char *vehicles_file, Vehicles &vehicles_dict);
void read_stats_file(ifstream &fin, char *stats_file, Vehicles &vehicles_dict, ActivityEngine &activity_engine);


int main(int argc, char * argv[])
{
    // when starting the system, delete all the old logs before creating new ones.
    check_directories();

    char days_str[sizeof(int)];
    char vehicles_file[BUFFER_SZ], stats_file[BUFFER_SZ];
    ifstream fin;

    // check the correct amount of args has been passed
    if (argc < 4 || argc > 4) {
        cout << "Usage: Traffic [VEHICLES FILE] [STATS FILE] [DAYS]\n" << flush;
        exit(0);
    } else if (argc == 4) {  // correct number of args passed
        strncpy(vehicles_file, argv[1], BUFFER_SZ);
        strncpy(stats_file, argv[2], BUFFER_SZ);
        // attempting to do int conversion from args safely
        strncpy(days_str, argv[3], sizeof(int));
        g_days = safe_int_convert(days_str, "Incorrect number used for number of days");
    }

    /* WELCOME HEADER */
    FILE *fp = fopen("Welcome_ascii", "r");  // using C file io for efficiency
    char c = getc(fp);
    cout << "\n";
    while (c != EOF) {
        cout << c;
        c = getc(fp);
    }
    cout << endl << endl;
    fclose(fp);

    // vehicles_dict is a Vehicles wrapper object for a hash map dictionary of VehicleType structs.
    // key: name of the type. value: VehicleType structure
    Vehicles vehicles_dict = Vehicles();
    read_vehicles_file(fin, vehicles_file, vehicles_dict);
    console_log("SYSTEM", "Vehicle Types");
    vehicles_dict.print();

    ActivityEngine activity_engine;
    read_stats_file(fin, stats_file, vehicles_dict, activity_engine);
    activity_engine.run(vehicles_dict);

    // AnalysisEngine analysis_engine;
    // analysis_engine.run(vehicles_dict);
    // analysis_engine.generate_stats_baseline();
    AnalysisEngine analysis_engine;
    analysis_engine.run(vehicles_dict);
    analysis_engine.generate_stats_baseline();

    // generate vehicles_dict for baseline data
    /*Vehicles vehicles_dict_baseline;
    char stats_baseline[] = "data/stats_baseline";
    read_vehicles_file(fin, vehicles_file, vehicles_dict_baseline);
    read_stats_file(fin, stats_baseline, vehicles_dict_baseline, activity_engine);*/

    // TODO: debug
    // generate log file name
    /*stringstream log_filename;
    log_filename << "logs_" << ++FILENAME_COUNTER;

    char test_stats[] = "Stats_Test.txt";
    ActivityEngine test_activity_engine(log_filename.str());
    read_stats_file(fin, test_stats, vehicles_dict, test_activity_engine);
    test_activity_engine.run(vehicles_dict);
    AnalysisEngine test_analysis_engine(log_filename.str());
    test_analysis_engine.run(vehicles_dict);
    AlertEngine test_alert_engine(test_stats, log_filename.str());
    int test_days = 3;
    test_alert_engine.run(vehicles_dict_baseline);*/

    // stringstream log_filename;
    // log_filename << "logs_" << ++FILENAME_COUNTER;
    // char test_stats[] = "Stats_Test.txt";
    // ActivityEngine test_activity_engine(log_filename.str());
    // read_stats_file(fin, test_stats, vehicles_dict, test_activity_engine);
    // test_activity_engine.run(vehicles_dict);
    // AnalysisEngine test_analysis_engine(log_filename.str());
    // test_analysis_engine.run(vehicles_dict);
    // AlertEngine test_alert_engine(test_stats, log_filename.str());
    // int test_days = 5;
    // test_alert_engine.run(vehicles_dict, test_days);

    char command;

    // do {
    //     console_log("SYSTEM", "Alert Engine Phase");
    //     cout << "Do you want to continue by inputting a new Statistics file for simulation? [y/N]: ";
    //     cin >> command;
    //     command = static_cast<char>(tolower(command));
    //
    //     if (strncmp(&command, "y", sizeof(command)) == 0) {
    //         cout << "Statistics filename: ";
    //         char user_stats[BUFFER_SZ];
    //         cin >> user_stats;
    //
    //         cout << "Number of days: ";
    //         char user_days_str[sizeof(int)];
    //         cin >> user_days_str;
    //         unsigned user_days = safe_int_convert(user_days_str, "Incorrect number used for number of days");
    //
    //         // generate log file name
    //         stringstream log_filename;
    //         log_filename << "logs_" << ++FILENAME_COUNTER;
    //
    //         ifstream another_fin;
    //         ActivityEngine live_activity_engine();
    //         read_stats_file(another_fin, user_stats, vehicles_dict, live_activity_engine);
    //         live_activity_engine.run(vehicles_dict);  // note number of days set in reading file
    //
    //         AnalysisEngine live_analysis_engine;
    //         live_analysis_engine.run(vehicles_dict);
    //
    //         AlertEngine live_alert_engine(user_stats, "data_");
    //         live_alert_engine.run(vehicles_dict, user_days);
    //
    //     } else if (strncmp(&command, "n", sizeof(command)) == 0) {
    //         /* EXIT MESSAGE */
    //         fp = fopen("Exit_ascii", "r");  // using C file io for efficiency
    //         c = getc(fp);
    //         cout << "\n\n";
    //         while (c != EOF) {
    //             cout << c;
    //             c = getc(fp);
    //         }
    //         cout << endl << endl;
    //         fclose(fp);
    //         break;
    //     }
    // } while (strncmp(&command, "y", sizeof(command)) == 0);

    return 0;
}

void check_directories()
{
    if (is_dir_exists("logs")) {
        if (strcmp(OS, "linux") == 0)
            system("exec rm -rf logs/*");
        else
            system("del logs");
    } else {  // DOS WIN32 or WIN64 systems
        if (strcmp(OS, "linux") == 0)
            system("exec mkdir logs");
        else
            system("mkdir logs");
    }

    if (is_dir_exists("data")) {
        if (strcmp(OS, "linux") == 0)
            system("exec rm -rf data/*");
        else
            system("del data");
    } else {
        if (strcmp(OS, "linux") == 0)
            system("exec mkdir data");
        else
            system("mkdir data");
    }
}

void read_vehicles_file(ifstream &fin, char *vehicles_file, Vehicles &vehicles_dict)
{
    fin.open(vehicles_file, ifstream::in);
    if (!fin.good()) {
        stringstream ss;
        ss << "Unable to read Vehicles file from: " << vehicles_file << "\nExiting...";
        console_log("FILE ERROR", ss.str());
        perror(ss.str().c_str());
        exit(1);
    }

    fin >> g_n_vehicles;  // read the first line as number of vehicle types and store it globally
    // read subsequent lines from Vehicles.txt as:
    // "Vehicle name:Parking flag:Registration format:Volume weight:Speed weight:"
    while (!fin.eof()) {
        fin.ignore(); // ignore newline before getline()

        string tmp_name;
        getline(fin, tmp_name, ':');

        if (tmp_name.empty())  // check if blank line before EOF
            break;

        VehicleType new_vehicle;
        new_vehicle.name = tmp_name;

        // read each parking value as 0 (false flag) and 1 (true flag) and convert to bool
        string parking;
        getline(fin, parking, ':');
        new_vehicle.parking_flag = (parking == "1");

        getline(fin, new_vehicle.reg_format, ':');

        // read both volume and speed weights as a string initially and use safe_int_convert()
        // function to safely convert them to an unsigned int
        string vol_str, speed_str;
        getline(fin, vol_str, ':');
        getline(fin, speed_str, ':');
        new_vehicle.vol_weight = safe_int_convert(vol_str.c_str(),
                "Incorrect number used for volume weight. Must be integer.");
        new_vehicle.speed_weight = safe_int_convert(speed_str.c_str(),
                "Incorrect number used for speed weight. Must be integer.");
        // insert each new_vehicle struct into the Vehicles hash map dictionary
        vehicles_dict.insert(new_vehicle);
    }
    fin.close();
}

void read_stats_file(ifstream &fin, char *stats_file, Vehicles &vehicles_dict, ActivityEngine &activity_engine)
{
    fin.open(stats_file, ifstream::in);
    if (!fin.good()) {
        stringstream ss;
        ss << "Unable to read Stats file from: " << stats_file << "\nExiting...";
        console_log("FILE ERROR", ss.str());
        perror(ss.str().c_str());
        exit(1);
    }

    // read the first line as positive integers
    // number of vehicle types monitored | length of road in km | speed limit in km/h | number of parking spaces
    char *unused_end;
    unsigned veh_monitored, parking_spots;
    float speed_lim, road_len;
    string veh_monitored_str, parking_spots_str, speed_lim_str, road_len_str;

    fin >> veh_monitored_str >> road_len_str >> speed_lim_str >> parking_spots_str;
    veh_monitored = safe_int_convert(veh_monitored_str.c_str(),
            "Incorrect number used for number of vehicles monitored. Must be integer.");
    parking_spots = safe_int_convert(parking_spots_str.c_str(),
            "Incorrect number used for number of vehicles monitored. Must be integer.");
    speed_lim = strtof(speed_lim_str.c_str(), &unused_end);
    road_len = strtof(road_len_str.c_str(), &unused_end);

    stringstream stats_message;
    stats_message << "Input from " << stats_file;
    console_log("SYSTEM", stats_message.str());
    cout << left << setw(27) << "Vehicles Monitored: " << veh_monitored << '\n'
         << left << setw(27) << "Road Length: " << road_len << '\n'
         << left << setw(27) << "Parking Spots Available: " << parking_spots << '\n'
         << left << setw(27) << "Speed Limit: " << speed_lim << " km/h\n\n";

    activity_engine.set_statistics(g_days, veh_monitored, road_len, speed_lim, parking_spots);

    // read subsequent lines from Stats.txt as:
    // Vehicle type:Number mean:Number standard deviation:Speed mean: Speed standard deviation:
    while (!fin.eof()) {
        fin.ignore(); // ignore left over newline before getline()

        // read both each int type as a string initially and use safe_int_convert()
        // function to safely convert them to an unsigned int
        string name;
        string num_mean_str, num_stddev_str, speed_mean_str, speed_stddev_str;
        float num_mean, num_stddev, speed_mean, speed_stddev;
        getline(fin, name, ':');

        if (name.empty())
            break;

        getline(fin, num_mean_str, ':');
        getline(fin, num_stddev_str, ':');
        getline(fin, speed_mean_str, ':');
        getline(fin, speed_stddev_str, ':');

        num_mean = strtof(num_mean_str.c_str(), &unused_end);
        num_stddev = strtof(num_stddev_str.c_str(), &unused_end);
        speed_mean = strtof(speed_mean_str.c_str(), &unused_end);
        speed_stddev = strtof(speed_stddev_str.c_str(), &unused_end);

        // check to see if vehicle type stats was added successfully
        // TODO: should log this to a file
        if (!vehicles_dict.add_stats(name, num_mean, num_stddev, speed_mean, speed_stddev))
            console_log("SYSTEM", "Vehicle type " + name + " cannot be found.");
    }
    fin.close();
}