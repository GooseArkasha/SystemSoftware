#include <iostream>
#include <Windows.h>

#include "MBR.h"
#include "Drive.h"

using namespace std;

string drive_path  = "\\\\.\\Q:";

int main()
{
    Drive drive(drive_path);
    MBR mbr = *drive.GetMbr();
    cout << drive_path << " number of bytes in sector: " << mbr.GetNumberOfBytesInSector() << endl;
    cout << drive_path << " number of sectors in section: " << mbr.GetNumberOfSectorsInSection() << endl;

    string buffer;
    UINT number_of_sector;

    cout << "Input number of sector [0; " << mbr.GetNumberOfSectorsInSection() << "]: ";
    cin >> buffer;
    try {
        number_of_sector = stoi(buffer);
    }
    catch (std::invalid_argument e) {
        cerr << "Caught Invalid Argument Exception\n";
    }

    drive.WriteSectorDump(drive.GetSectorDump(number_of_sector), number_of_sector);

}
