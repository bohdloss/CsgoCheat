#pragma once
#include "Player.hpp"

namespace csgo {
	class Context final
	{
	private:
		// Windows stuff
		HWND hwnd;
		HDC hdc;
		DWORD pid;
		HANDLE handle;
		uintptr_t module_base;
		uintptr_t engine_base;

		// Player list
		Player* m_players;
		Player* m_lPlayer;

	public:
		Context();
		~Context();

		uintptr_t get_base();
		uintptr_t get_enginebase();
		HANDLE* get_handle();
		void draw_line(float sx, float sy, float ex, float ey, COLORREF color);
		void draw_cross(float x, float y, COLORREF color);
		void draw_text(const char* text, float x, float y, float font_size, COLORREF color);
		Player* get_player(int index);
		Player* get_local_player();
		ViewMatrix get_view_matrix();
		float get_sensitivity();
		uintptr_t get_clientstate();
		Vector3 get_viewangle();

		void refresh_players();

		void force_jump(bool val);
		void force_left(bool val);
		void force_right(bool val);
		void force_forward(bool val);
		void force_backward(bool val);
		void force_shoot_primary(bool val);
		void force_shoot_secondary(bool val);

		void force_jump();
		void force_left();
		void force_right();
		void force_forward();
		void force_backward();
		void force_shoot_primary();
		void force_shoot_secondary();

		void set_viewangle(Vector3 vec);
	};
}