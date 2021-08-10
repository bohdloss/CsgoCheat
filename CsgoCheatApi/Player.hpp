#pragma once
#include "Utils.hpp"

namespace csgo {
	class Player
	{
	private:
		uintptr_t player_base;
		uintptr_t module_base;
		HANDLE* handle;

	public:
		Player(uintptr_t player_base, uintptr_t module_base, HANDLE* handle);
		~Player();

		uintptr_t get_base();
		void set_base(uintptr_t);

		bool is_local();
		int get_health();
		int get_team();
		Vector3 get_location();
		Vector3 get_velocity();
		bool is_dormant();
		struct BoneMatrix get_bmatrix(int index);
		int get_flags();
		Vector3 get_punchangle();
		Vector3 get_camerapos();
		Vector3 get_vecorigin();
		Vector3 get_viewoffset();
		Vector3 get_viewangle();

		void set_flags(int flags);
		void set_punchangle(Vector3 vec);
		void set_vecorigin(Vector3 vec);
		void set_viewoffset(Vector3 vec);
		void set_spotted(bool b);

	};
}