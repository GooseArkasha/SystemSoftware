#pragma once
#include <Windows.h>
#include <string>

using namespace std;

#define NUMBER_OF_BYTES_IN_SECTOR_OFFSET 0x0B
#define NUMBER_OF_SECTORS_IN_SECTION_FIRST_OFFSET 0x13
#define NUMBER_OF_SECTORS_IN_SECTION_SECOND_OFFSET 0x20

class MBR {
private:

	string drive_path_;

	UINT number_of_bytes_in_sector_;
	UINT number_of_sectors_in_section_;

public:

	MBR(string drive_path);

	void SetDrivePath(string drive_path);
	void SetNumberOfBytesInSector();
	void SetNumberOfSectorsInSection();

	string GetDrivePath();
	UINT GetNumberOfBytesInSector();
	UINT GetNumberOfSectorsInSection();

	MBR& operator= (MBR& mbr);

};