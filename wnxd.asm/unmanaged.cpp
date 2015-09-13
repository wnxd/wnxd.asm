#include "unmanaged.h";

void* IL_PtrRun(int ptr, void* args, void* vs)
{
	__asm
	{
		push ecx;
		push edx;
		push ebx;
		mov eax, dword ptr[ebp + 0Ch];
		mov ecx, dword ptr[eax + 04h];
		test ecx, ecx;
		je Label1;
		add eax, 0Ch;
		mov edx, dword ptr[ebp + 08h];
		add edx, 08h;
		mov bl, byte ptr[edx];
		test bl, bl;
		mov ebx, dword ptr[eax];
		je Label2;
		mov ebx, dword ptr[ebx + 04h];
	Label2:
		mov edi, ebx;
		cmp ecx, 01h;
		je Label3;
		add eax, 04h;
		add edx, 01h;
		mov bl, byte ptr[edx];
		test bl, bl;
		mov ebx, dword ptr[eax];
		je Label4;
		mov ebx, dword ptr[ebx + 04h];
	Label4:
		mov esi, ebx;
		cmp ecx, 02h;
		je Label5;
		sub ecx, 02h;
		imul ebx, ecx, 04h;
		add eax, ebx;
		add edx, ecx;
	Label7:
		mov bl, byte ptr[edx];
		test bl, bl;
		mov ebx, dword ptr[eax];
		je Label6;
		mov ebx, dword ptr[ebx + 04h];
	Label6:
		push ebx;
		sub eax, 04h;
		sub edx, 01h;
		loop Label7;
	Label5:
		mov edx, esi;
	Label3:
		mov ecx, edi;
	Label1:
		mov eax, dword ptr[ebp - 08h];
		call eax;
		pop ebx;
		leave;
		retn 0004h;
	}
}