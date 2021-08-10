#include "Context.hpp"

using namespace csgo;

namespace csgo {
	Context::Context() {

		// Find window
		this->hwnd = FindWindowA(NULL, "Counter-Strike: Global Offensive");
		GetWindowThreadProcessId(this->hwnd, &(this->pid));

		// Find module base address
		this->module_base = getModuleBaseAddress(CLIENT, this->pid);
		this->engine_base = getModuleBaseAddress(ENGINE, this->pid);

		// Get process handle
		this->handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, this->pid);
		this->hdc = GetDC(this->hwnd);

		// Find offsets
		findOffsets(pid, handle);

		// Allocate space for players
		this->m_players = (Player*) malloc(sizeof(Player) * 32);
		if (this->m_players) {
			for (int i = 0; i < 32; i++) {
				this->m_players[i] = Player(read_mem<uintptr_t>(&this->handle, this->module_base + dwEntityList + i * 0x10), this->module_base, &this->handle);
			}
		}
		this->m_lPlayer = new Player(read_mem<uintptr_t>(&this->handle, this->module_base + dwLocalPlayer), this->module_base, &this->handle);
	}

	Context::~Context() {
		free(this->m_players);
		delete this->m_lPlayer;
	}

	void Context::draw_line(float sx, float sy, float ex, float ey, COLORREF color) {
		int a, b = 0;
		HPEN hOPen;
		HPEN hNPen = CreatePen(PS_SOLID, 2, color);
		hOPen = (HPEN)SelectObject(this->hdc, hNPen);
		MoveToEx(this->hdc, (int) sx, (int) sy, NULL);
		a = LineTo(this->hdc, (int) ex, (int) ey);
		DeleteObject(SelectObject(this->hdc, hOPen));
	}

	uintptr_t Context::get_base() {
		return this->module_base;
	}

	uintptr_t Context::get_enginebase() {
		return this->engine_base;
	}

	HANDLE* Context::get_handle() {
		return &this->handle;
	}

	Player* Context::get_player(int index) {
		return &(this->m_players[index]);
	}

	Player* Context::get_local_player() {
		return this->m_lPlayer;
	}

	ViewMatrix Context::get_view_matrix() {
		return read_mem<ViewMatrix>(&this->handle, this->module_base + dwViewMatrix);
	}

	void Context::draw_cross(float x, float y, COLORREF color) {
		this->draw_line(x - 5, y - 5, x + 5, y + 5, color);
		this->draw_line(x + 5, y - 5, x - 5, y + 5, color);
	}

	void Context::draw_text(const char* text, float x, float y, float font_size, COLORREF color) {
		RECT rect = RECT();
		rect.top = y - font_size / 2;
		rect.bottom = y + font_size / 2;
		rect.right = x + (font_size * strlen(text)) / 2;
		rect.left = x - (font_size * strlen(text)) / 2;

		SetBkMode(this->hdc, TRANSPARENT);
		SetTextColor(this->hdc, color);
		DrawTextA(this->hdc, text, -1, &rect, DT_CENTER);
	}

	float Context::get_sensitivity() {
		DWORD sensitivityPointer = this->module_base + dwSensitivityPtr;
		DWORD sensitivityValue = read_mem<DWORD>(&this->handle, this->module_base + dwSensitivityPtr + 44);
		sensitivityValue ^= sensitivityPointer;
		return *reinterpret_cast<float*>(&sensitivityValue);
	}

	void Context::refresh_players() {
		for (int i = 0; i < 32; i++) {
			this->m_players[i].set_base(read_mem<uintptr_t>(&this->handle, this->module_base + dwEntityList + i * 0x10));
		}
		this->m_lPlayer->set_base(read_mem<uintptr_t>(&this->handle, this->module_base + dwLocalPlayer));
	}

	void Context::force_jump(bool val) {
		write_mem<uintptr_t>(&this->handle, this->module_base + dwForceJump, val ? 5 : 4);
	}

	void Context::force_left(bool val) {
		write_mem<uintptr_t>(&this->handle, this->module_base + dwForceLeft, val ? 5 : 4);
	}

	void Context::force_right(bool val) {
		write_mem<uintptr_t>(&this->handle, this->module_base + dwForceRight, val ? 5 : 4);
	}

	void Context::force_forward(bool val) {
		write_mem<uintptr_t>(&this->handle, this->module_base + dwForceForward, val ? 5 : 4);
	}

	void Context::force_backward(bool val) {
		write_mem<uintptr_t>(&this->handle, this->module_base + dwForceBackward, val ? 5 : 4);
	}

	void Context::force_shoot_primary(bool val) {
		write_mem<uintptr_t>(&this->handle, this->module_base + dwForceAttack, val ? 5 : 4);
	}

	void Context::force_shoot_secondary(bool val) {
		write_mem<uintptr_t>(&this->handle, this->module_base + dwForceAttack2, val ? 5 : 4);
	}

	uintptr_t Context::get_clientstate() {
		return read_mem<uintptr_t>(&this->handle, this->engine_base + dwClientState);
	}

	Vector3 Context::get_viewangle() {
		return read_mem<Vector3>(&this->handle, get_clientstate() + dwClientState_ViewAngles);
	}

	void Context::set_viewangle(Vector3 vec) {
		write_mem<Vector3>(&this->handle, this->get_clientstate() + dwClientState_ViewAngles, vec);
	}

	void Context::force_jump() {
		write_mem<uintptr_t>(&this->handle, this->module_base + dwForceJump, 6);
	}

	void Context::force_left() {
		write_mem<uintptr_t>(&this->handle, this->module_base + dwForceLeft, 6);
	}

	void Context::force_right() {
		write_mem<uintptr_t>(&this->handle, this->module_base + dwForceRight, 6);
	}

	void Context::force_forward() {
		write_mem<uintptr_t>(&this->handle, this->module_base + dwForceForward, 6);
	}

	void Context::force_backward() {
		write_mem<uintptr_t>(&this->handle, this->module_base + dwForceBackward, 6);
	}

	void Context::force_shoot_primary() {
		write_mem<uintptr_t>(&this->handle, this->module_base + dwForceAttack, 6);
	}

	void Context::force_shoot_secondary() {
		write_mem<uintptr_t>(&this->handle, this->module_base + dwForceAttack2, 6);
	}

}