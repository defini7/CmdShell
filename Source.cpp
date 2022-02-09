#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>
#include <lmcons.h>

namespace FG
{
	int BLACK = 0x0000,
		DARK_BLUE = 0x0001,
		DARK_GREEN = 0x0002,
		DARK_CYAN = 0x0003,
		DARK_RED = 0x0004,
		DARK_MAGENTA = 0x0005,
		DARK_YELLOW = 0x0006,
		GREY = 0x0007,
		DARK_GREY = 0x0008,
		BLUE = 0x0009,
		GREEN = 0x000A,
		CYAN = 0x000B,
		RED = 0x000C,
		MAGENTA = 0x000D,
		YELLOW = 0x000E,
		WHITE = 0x000F;
}
namespace BG
{
	int BLACK = 0x0000,
		DARK_BLUE = 0x0010,
		DARK_GREEN = 0x0020,
		DARK_CYAN = 0x0030,
		DARK_RED = 0x0040,
		DARK_MAGENTA = 0x0050,
		DARK_YELLOW = 0x0060,
		GREY = 0x0070,
		DARK_GREY = 0x0080,
		BLUE = 0x0090,
		GREEN = 0x00A0,
		CYAN = 0x00B0,
		RED = 0x00C0,
		MAGENTA = 0x00D0,
		YELLOW = 0x00E0,
		WHITE = 0x00F0;
}

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
		SetConsoleTextAttribute(hConsole, FG::GREEN);
		std::wcout << username << L" ";

		SetConsoleTextAttribute(hConsole, FG::DARK_YELLOW);

		_wgetcwd(path_buffer, 256);
		std::wcout << path_buffer << L"\n";

		SetConsoleTextAttribute(hConsole, FG::WHITE);
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
		SetConsoleTextAttribute(hConsole, FG::DARK_YELLOW);

		delete[] buffer;
    }

	delete[] path_buffer;
	delete[] username;

	return 0;
}
