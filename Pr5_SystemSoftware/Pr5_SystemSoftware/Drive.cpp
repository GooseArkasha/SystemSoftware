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

#include "Drive.h"

using namespace std;

Drive::Drive(string drive_path) {
	this->drive_path_ = drive_path;

	this->mbr_ = new MBR(drive_path);
}



void Drive::SetDrivePath(string drive_path) {
	this->drive_path_ = drive_path;
}


void Drive::SetMbr(MBR* mbr) {
	this->mbr_ = mbr;
}



string Drive::GetDrivePath() {
	return this->drive_path_;
}


MBR* Drive::GetMbr() {
	return this->mbr_;
}



BYTE* Drive::GetSectorDump(UINT number_of_secter) {

	MBR mbr = *this->GetMbr();

	BYTE* buffer = new BYTE[mbr.GetNumberOfBytesInSector()];

	ifstream infile(this->drive_path_.c_str(), ios::in | ios::binary);
	if (!infile)
	{
		cerr << "Device input could not be set!" << endl;
		exit(102);
	}

	infile.ignore(static_cast<__int64>(mbr.GetNumberOfBytesInSector()) * number_of_secter);		//static_cast <__int64> avoids overflow 

	infile.read((char*)buffer, mbr.GetNumberOfBytesInSector());
	if (infile.gcount() == 0) {
		cerr << "Data read error!" << endl;
		exit(999);
	}

	infile.close();

	return buffer;
}


void Drive::WriteSectorDump(BYTE* buffer, UINT number_of_sector) {

	MBR mbr = *this->GetMbr();

	for (int i = 0; i < mbr.GetNumberOfBytesInSector() / 16; i++) {
		printf("%09X| ", mbr.GetNumberOfBytesInSector() * number_of_sector + i * 16);
		for (int j = 0; j < 16; j++) {
			if (j == 8) {
				printf(" ");
			}
			printf("%02X ", buffer[i * 16 + j]);
		}

		printf(" | ");

		for (int j = 0; j < 16; j++) {
			if (buffer[i * 16 + j] != 0x0A) {
				printf("%c", buffer[i * 16 + j]);
			}
		}
		printf("\n");
	}
}
