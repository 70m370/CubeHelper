#pragma once

namespace MEM {
	//patch binaries
	void PATCH(BYTE* byte, BYTE* addrs, int bytes);
	//write on memory
	void WRITEMEM(uintptr_t addrs, int newValue);

	void WRITEMEM64(DWORD64 addrs, int newValue);
}