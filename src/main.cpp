#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <string>

using namespace std;

// Umur dalam tahun
int yearsOld(tm* inputTgl, tm* currentTgl);
// Umur dalam bulan
int monthsOld(tm* inputTgl, tm* currentTgl);
// Hari dalam seminggu (Minggu, Senin, ..., Sabtu)
string dayOfDate(tm* inputTgl, tm* currentTgl);

int main(int argc, char ** argv) 
{
    // time_t -> data structure untuk waktu
    time_t currentTime;

    // set variable currentTime ke data sekarang
    time(&currentTime);

    // ubah ke localtime (UTC+7)
    tm* currentTgl = localtime(&currentTime);

    // print tanggal sekarang (di comment)
     //cout    <<" year:" << currentTgl->tm_year+1900 //<-- perlu diperhatikan
       //    <<" month:"<< currentTgl->tm_mon+1
        //<<" day:" << currentTgl->tm_mday <<endl;

    int yearnow = currentTgl->tm_year+1900;    
    int monthnow = currentTgl->tm_mon+1;
    int daynow = currentTgl->tm_mday;
    int dayofweek = currentTgl->tm_wday;       // <-- start dari hari minggu

    // input tanggal lahir
    int yearinput, monthinput, dayinput;
    string inputstr;
    char ch;
    // silahkan uncomment kode dibawah untuk debugging
    //cout << "Input tanggal dalam format DD/MM/YYYY:";
    cin >> inputstr;
    stringstream ss(inputstr);
    ss >> dayinput >> ch >> monthinput >> ch >> yearinput;

    // silahkan uncomment untuk debugging
    cout << "Tanggal Input: " << dayinput << "/" << monthinput << "/" << yearinput << endl;
    // buat tm* untuk tanggal input
    tm* inputTgl = new tm();
    inputTgl->tm_year = yearinput-1900;
    inputTgl->tm_mon = monthinput-1;
    inputTgl->tm_mday = dayinput;

    //cout << "inputTgl->tm_mon: " << inputTgl->tm_mon << "; inputTgl->tm_year: " << inputTgl->tm_year << "; currentTgl->tm_mon: " << currentTgl->tm_mon << "; currentTgl->tm_year: " << currentTgl->tm_year << endl;

    // ----------------------------------------------------------------------------------------------------------------
    // --- Ubah di sini
    // ---  * output yang diinginkan: 32 390 Selasa
    // ---                  32 -> usia dalam tahun, 390 -> usia dalam bulan, Selasa -> hari dari tanggal input
    // ----------------------------------------------------------------------------------------------------------------
    int ageOfYear = yearsOld(inputTgl, currentTgl);
    int ageOfMonth = monthsOld(inputTgl, currentTgl);
    string dayName = dayOfDate(inputTgl, currentTgl);

    cout << ageOfYear << " " << ageOfMonth << " " << dayName;
    // ----------------------------------------------------------------------------------------------------------------

    return 0;
}

//*********************************************************************************************************************
// Silahkan masukkan kode Anda pada fungsi-fungsi berikut
//*********************************************************************************************************************
int yearsOld(tm* inputTgl, tm* currentTgl)
{
    int ageOfYear = currentTgl->tm_year - inputTgl->tm_year;
    return inputTgl->tm_mday <= currentTgl->tm_mday && inputTgl->tm_mon <= currentTgl->tm_mon ? ageOfYear: ageOfYear - 1;
}
//*********************************************************************************************************************
//*********************************************************************************************************************
int monthsOld(tm* inputTgl, tm* currentTgl) //1 bulan = 28 hari
{
    int daysSince = 0;
    int dayOfTheMonth = inputTgl->tm_mday;
    int daysInMonth;
    int startingMonth;
    int totalMonths;

    if (inputTgl->tm_mon < currentTgl->tm_mon)
    {
        startingMonth = inputTgl->tm_mon;
    }
    else
    {
        startingMonth = 0;
    }

    for (int i = startingMonth; i <= currentTgl->tm_mon; i++) 
    {
        switch(i)
        {
            case 1:
                //feb                           periksa tahun kabisat                                                                 
                daysInMonth = currentTgl->tm_year % 4 == 0 && (currentTgl->tm_year+1900) % 100 != 0 || currentTgl->tm_year+1900 % 400 == 0 ? 29 : 28;
                break;
            case 3:
            case 5:
            case 8:
            case 10:
                //apr jun sep nov
                daysInMonth = 30;
                break;
            default:
                //jan mar may jul aug oct dec
                daysInMonth = 31;
                break;
        }
        daysSince += daysInMonth - dayOfTheMonth;
        daysSince = i == currentTgl->tm_mon ? daysSince - (daysInMonth - currentTgl->tm_mday) : daysSince;
        dayOfTheMonth = 0;
    }
    totalMonths = inputTgl->tm_year != currentTgl->tm_year ? 12 - inputTgl->tm_mon + 12*(currentTgl->tm_year - inputTgl->tm_year - 1) + daysSince/30 : daysSince/30;
    return totalMonths;
}
//*********************************************************************************************************************
//*********************************************************************************************************************
string dayOfDate(tm* inputTgl, tm* currentTgl)
{
    string bulan[12] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
    string hari[7] = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu", "Minggu"};

    bool kabisat;

    int daysInMonth;
    int dayOfTheMonth = inputTgl->tm_mday;
    int daysSince = 0;
    int startingMonth = inputTgl->tm_mon;

    for (int i = inputTgl->tm_year; i <= currentTgl->tm_year; i++)
    {
        kabisat = (i % 4 == 0 && i+1900  % 100 != 0) || ((i + 1900) % 400 == 0);
        for (int j = startingMonth; j <= 11; j++)
        {
            switch(j)
            {
                case 1:
                    daysInMonth = kabisat ? 29 : 28;
                    break;
                case 3:
                case 5:
                case 8:
                case 10:
                    daysInMonth = 30;
                    break;
                default:
                    daysInMonth = 31;
                    break;
            }
            daysSince += daysInMonth - dayOfTheMonth;
            daysSince = i == currentTgl->tm_year && j == currentTgl->tm_mon ? daysSince - (daysInMonth - currentTgl->tm_mday) : daysSince;
            dayOfTheMonth = 0;
            if (i == currentTgl->tm_year && j == currentTgl->tm_mon)
            {
                break;
            }
        }
        startingMonth = 0;
    }
    daysSince -= currentTgl->tm_wday;
    return hari[6 - daysSince % 7];
}
//*********************************************************************************************************************
//*********************************************************************************************************************

