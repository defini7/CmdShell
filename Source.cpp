#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>
#include <lmcons.h>

namespace Pixel
{
	int SOLID = 0x2588,
		THREEQUARTERS = 0x2593,
		HALF = 0x2592,
		QUARTER = 0x2591;
}

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	wchar_t path_buffer[256];
	wchar_t username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserName(username, &username_len);

	if (std::system(nullptr) == 0) return 1;

    while (1)
    {
		SetConsoleTextAttribute(hConsole, 0x000A);
		std::wcout << username << L" ";

		SetConsoleTextAttribute(hConsole, 0x0006);

		_wgetcwd(path_buffer, 256);
		std::wcout << path_buffer << L"\n";

		SetConsoleTextAttribute(hConsole, 0x000F);
		std::wcout << "> ";

		wchar_t command[256];
		std::wcin.getline(command, 256);

		const size_t command_sz = (wcslen(command) + 1) * sizeof(wchar_t);
		char* buffer = new char[command_sz];

#ifdef __STDC_LIB_EXT1__
		size_t convertedSize;
		std::wcstombs_s(&convertedSize, buffer, size, input, size);
#else
		std::wcstombs(buffer, command, command_sz);
#endif

		std::system(buffer);
		std::wcout << L"\n";
		SetConsoleTextAttribute(hConsole, 0x0006);

		delete[] buffer;
    }

	delete[] path_buffer;
	delete[] username;

	return 0;
}
