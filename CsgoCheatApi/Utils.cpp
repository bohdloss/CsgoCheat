#include "Utils.hpp"

	const int csgo::SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
	const int csgo::xhairx = SCREEN_WIDTH / 2;
	const int csgo::SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);
	const int csgo::xhairy = SCREEN_HEIGHT / 2;

	csgo::Vector3::Vector3() : x(0.f), y(0.f), z(0.f) {
	}

	csgo::Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {
	}

	csgo::Vector2::Vector2() : x(0.f), y(0.f) {
	}

	csgo::Vector2::Vector2(float x, float y) : x(x), y(y) {
	}

	float csgo::distance(float x1, float y1, float x2, float y2) {
		return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	}

	csgo::Vector3 csgo::world_to_screen(Vector3 pos, struct csgo::ViewMatrix matrix) {
		Vector3 out;
		float _x = matrix.matrix[0] * pos.x + matrix.matrix[1] * pos.y + matrix.matrix[2] * pos.z + matrix.matrix[3];
		float _y = matrix.matrix[4] * pos.x + matrix.matrix[5] * pos.y + matrix.matrix[6] * pos.z + matrix.matrix[7];
		out.z = matrix.matrix[12] * pos.x + matrix.matrix[13] * pos.y + matrix.matrix[14] * pos.z + matrix.matrix[15];

		_x *= 1.f / out.z;
		_y *= 1.f / out.z;

		out.x = SCREEN_WIDTH * .5f;
		out.y = SCREEN_HEIGHT * .5f;

		out.x += 0.5f * _x * SCREEN_WIDTH + 0.5f;
		out.y -= 0.5f * _y * SCREEN_HEIGHT + 0.5f;

		return out;
	}

	csgo::Vector3 csgo::look_at(Vector3 start, Vector3 end) {
		float xdiff = end.x - start.x;
		float ydiff = end.y - start.y;
		float zdiff = end.z - start.z;
		float dist = distance(start.x, start.y, end.x, end.y);

		float ang_x = (atan2f(ydiff, xdiff) / M_PI) * 180;
		float ang_y = (atan2f(dist, zdiff) / M_PI) * 180 - 90;
		return Vector3(ang_x, ang_y, 0);
	}

	const char* csgo::CLIENT = "client.dll";
	const char* csgo::ENGINE = "engine.dll";

	void csgo::getModule(const char* name, DWORD pid, MODULEENTRY32* output) {
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
		if (hSnap != INVALID_HANDLE_VALUE) {
			MODULEENTRY32 mod_entry;
			mod_entry.dwSize = sizeof(mod_entry);
			if (Module32First(hSnap, &mod_entry)) {
				do {
					if (!strcmp(mod_entry.szModule, name)) {
						CloseHandle(hSnap);
						*output = mod_entry;
						return;
					}
				} while (Module32Next(hSnap, &mod_entry));
			}
		}
	
	}

	size_t csgo::getModuleBaseAddress(const char* name, DWORD pid) {
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
		if (hSnap != INVALID_HANDLE_VALUE) {
			MODULEENTRY32 mod_entry;
			mod_entry.dwSize = sizeof(mod_entry);
			if (Module32First(hSnap, &mod_entry)) {
				do {
					if (!strcmp(mod_entry.szModule, name)) {
						CloseHandle(hSnap);
						return (size_t)mod_entry.modBaseAddr;
					}
				} while (Module32Next(hSnap, &mod_entry));
			}
		}
		return 0;
	}