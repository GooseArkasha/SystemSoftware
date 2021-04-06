#include <bitset>
#include <iostream>
#include <assert.h>
#include <Windows.h>
#include <string>
#include <fstream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <memory>
#include <strsafe.h>

#include "MBR.h"


MBR::MBR(string drive_path) {
	this->drive_path_ = drive_path;
	SetNumberOfBytesInSector();
	SetNumberOfSectorsInSection();
}



void MBR::SetDrivePath(string drive_path) {
	this->drive_path_ = drive_path;
}


void MBR::SetNumberOfBytesInSector() {

	short int number_of_bytes_in_sector = 0;
	short int* number_of_bytes_in_sector_ptr = &number_of_bytes_in_sector;

	ifstream infile(this->drive_path_.c_str(), ios::in | ios::binary);
	if (!infile)
	{
		cerr << "Device input could not be set!" << endl;
		exit(102);
	}

	infile.ignore(NUMBER_OF_BYTES_IN_SECTOR_OFFSET);

	infile.read((char*)number_of_bytes_in_sector_ptr, sizeof(short int));
	if (infile.gcount() == 0) {
		cerr << "Data read error!" << endl;
		exit(999);
	}

	this->number_of_bytes_in_sector_ = (UINT)number_of_bytes_in_sector;

	infile.close();

}


void MBR::SetNumberOfSectorsInSection() {

	short int number_of_sectors_in_section = 0;
	short int* number_of_sectors_in_section_ptr = &number_of_sectors_in_section;

	ifstream infile(this->drive_path_.c_str(), ios::in | ios::binary);
	if (!infile)
	{
		cerr << "Device input could not be set!" << endl;
		exit(102);
	}

	infile.ignore(NUMBER_OF_SECTORS_IN_SECTION_FIRST_OFFSET);

	infile.read((char*)number_of_sectors_in_section_ptr, sizeof(short int));
	if (infile.gcount() == 0) {
		cerr << "Data read error!" << endl;
		exit(999);
	}

	
	infile.close();

	if (number_of_sectors_in_section != 0) {
		this->number_of_sectors_in_section_ = (UINT)number_of_sectors_in_section;
		
	}
	else {

		ifstream infile(this->drive_path_.c_str(), ios::in | ios::binary);
		if (!infile)
		{
			cerr << "Device input could not be set!" << endl;
			exit(102);
		}

		infile.ignore(NUMBER_OF_SECTORS_IN_SECTION_SECOND_OFFSET);

		infile.read((char*)&this->number_of_sectors_in_section_, sizeof(UINT));
		if (infile.gcount() == 0) {
			cerr << "Data read error!" << endl;
			exit(999);
		}

		infile.close();

	}
}



string MBR::GetDrivePath() {
	return this->drive_path_;
}


UINT MBR::GetNumberOfBytesInSector() {
	return this->number_of_bytes_in_sector_;
}


UINT MBR::GetNumberOfSectorsInSection() {
	return this->number_of_sectors_in_section_;
}



MBR& MBR::operator= (MBR& mbr) {
	this->drive_path_ = mbr.GetDrivePath();
	this->number_of_bytes_in_sector_ = mbr.GetNumberOfBytesInSector();
	this->number_of_sectors_in_section_ = mbr.GetNumberOfSectorsInSection();

	return *this;
}