#pragma once
#include <Windows.h>
#include <string>

#include "MBR.h"

class Drive {
private:

	string drive_path_;
	MBR* mbr_;

public:

	Drive(string drive_path);

	void SetDrivePath(string drive_path);
	void SetMbr(MBR* mbr);

	string GetDrivePath();
	MBR* GetMbr();

	BYTE* GetSectorDump(UINT number_of_secter);
	void WriteSectorDump(BYTE* buffer, UINT number_of_sector);

};