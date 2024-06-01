#include <rtc.h>

CustomuRTCLib::CustomuRTCLib(const int address)
    : uRTCLib(address)
{
}

bool CustomuRTCLib::clockDataChanged () {
    bool data = false;
    clockNow = second(); // Mendapatkan waktu sekarang dari RTC

    // Memeriksa apakah data RTC berubah sejak terakhir kali diperbarui
    if (clockNow != lastClock)
    {
        // Update tampilan LCD
        lastClock = clockNow; // Perbarui waktu terakhir diperbarui
        data = true;
    }

    return data;
}

bool CustomuRTCLib::dateDataChanged () {
    bool data = false;
    dateNow = day(); // Mendapatkan waktu sekarang dari RTC

    // Memeriksa apakah data RTC berubah sejak terakhir kali diperbarui
    if (dateNow != lastDate)
    {
        // Update tampilan LCD
        lastDate = dateNow; // Perbarui waktu terakhir diperbarui
        data = true;
    }

    return data;
}