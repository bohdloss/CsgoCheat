#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include "Offsets.hpp"
#include <malloc.h>
#define _USE_MATH_DEFINES
#include <math.h>

namespace csgo {
	extern const int SCREEN_WIDTH;
	extern const int xhairx;
	extern const int SCREEN_HEIGHT;
	extern const int xhairy;

	class Vector2 {
	public:
		float x, y;
		Vector2(float x, float y);
		Vector2();
	};

	class Vector3 {
	public:
		float x, y, z;
		Vector3(float x, float y, float z);
		Vector3();
	};

	struct ViewMatrix {
		float matrix[16];
	};

	struct BoneMatrix {
		static const int HEAD = 8;

		byte pad3[12];
		float x;
		byte pad1[12];
		float y;
		byte pad2[12];
		float z;
	};

	struct PlayerInfo {
		int64_t __pad0;

		union {
			int64_t xuid;

			struct {
				int32_t xuidlow;
				int32_t xuidhigh;
			};
		};

		char name[128];
		int userid;
		char guid[33];
		unsigned int friendsid;
		char friendsname[128];
		bool fakeplayer;
		bool ishltv;
		unsigned int customfiles[4];
		unsigned char filesdownloaded;
	};

	struct CUserCmd {
		int pad;
		int command_number;
		int tick_count;
		Vector3 viewangles;
		Vector3 aimdirection;
		float forwardmove;
		float sidemove;
		float upmove;
		int buttons;
		char impulse;
		int weaponselect;
		int weaponsubtype;
		int randomseed;
		short mousedx;
		short mousedy;
		bool hasbeenpredicted;
	};

	struct Radar {
		Vector3  AbsOrigin;
		DWORD   unknown[10];
		int     Health;
		char Name[32];
	};

	template<typename T> T read_mem(HANDLE* handle, SIZE_T address) {
		T buffer;
		ReadProcessMemory(*handle, (LPCVOID)address, &buffer, sizeof(T), NULL);
		return buffer;
	}

	template<typename T> void write_mem(HANDLE* handle, SIZE_T address, T buffer) {
		WriteProcessMemory(*handle, (LPVOID)address, &buffer, sizeof(buffer), NULL);
	}

	struct ModuleInfo {
		uint8_t* data;
		size_t base_address;
		size_t base_size;
		HANDLE process;
	};

	float distance(float x1, float y1, float x2, float y2);
	Vector3 world_to_screen(Vector3 pos, struct ViewMatrix matrix);
	Vector3 look_at(Vector3 start, Vector3 end);

	extern const char* CLIENT;
	extern const char* ENGINE;

	void getModule(const char* name, DWORD pid, MODULEENTRY32* output);
	size_t getModuleBaseAddress(const char* name, DWORD pid);

}