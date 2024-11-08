#include <windows.h>
#include <iostream>

using namespace std;
int main() {
	LPVOID lpr;
	LPVOID lpc;
	const int kb = 1024;
	const int size = 100;
	lpr = VirtualAlloc(
		(LPVOID)0x00880000,
		size * kb,
		MEM_RESERVE,
		PAGE_READWRITE
	);
	if (!lpr) {
		cout << "Virtual memory reservation failed" << endl;
		return GetLastError();
	}
	cout << "Virtualmemory memory address: " << lpr << endl;

	lpc = VirtualAlloc(
		(LPVOID)0x00880000,
		kb,
		MEM_COMMIT,
		PAGE_READWRITE
	);
	if (!lpc) {
		cout << "Virtual memory allocation failed" << endl;
		return GetLastError();
	}
	cout << "Virtual memory address: " << lpc << endl;

	if (!VirtualFree(lpc, kb, MEM_DECOMMIT)) {
		cout << "Memory decommit failed" << endl;
		return GetLastError();
	}
	if (!VirtualFree(lpr, 0, MEM_RELEASE)) {
		cout << "Memory release failed" << endl;
		return GetLastError();
	}
	return 0;
}
