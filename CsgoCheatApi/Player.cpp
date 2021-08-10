#include "Player.hpp"

using namespace csgo;

namespace csgo {

	Player::Player(uintptr_t player_base, uintptr_t module_base, HANDLE* handle) {
		this->player_base = player_base;
		this->module_base = module_base;
		this->handle = handle;
	}

	Player::~Player() {

	}

	uintptr_t Player::get_base() {
		return this->player_base;
	}

	bool Player::is_local() {
		return read_mem<uintptr_t>(this->handle, this->module_base + dwLocalPlayer) == this->player_base;
	}

	int Player::get_health() {
		return read_mem<int>(this->handle, this->player_base + m_iHealth);
	}

	Vector3 Player::get_location() {
		return read_mem<Vector3>(this->handle, this->player_base + m_vecOrigin);
	}

	Vector3 Player::get_velocity() {
		return read_mem<Vector3>(this->handle, this->player_base + m_vecVelocity);
	}

	bool Player::is_dormant() {
		return read_mem<int>(this->handle, this->player_base + m_bDormant);
	}

	struct BoneMatrix Player::get_bmatrix(int index) {
		uintptr_t bone_base = read_mem<uintptr_t>(this->handle, this->player_base + m_dwBoneMatrix);
		return read_mem<BoneMatrix>(this->handle, bone_base + (sizeof(BoneMatrix) * index));
	}

	int Player::get_team() {
		return read_mem<int>(this->handle, this->player_base + m_iTeamNum);
	}

	void Player::set_base(uintptr_t base) {
		this->player_base = base;
	}

	int Player::get_flags() {
		return read_mem<int>(this->handle, this->player_base + m_fFlags);
	}

	void Player::set_flags(int flags) {
		write_mem<int>(this->handle, this->player_base + m_fFlags, flags);
	}

	Vector3 Player::get_vecorigin() {
		return read_mem<Vector3>(this->handle, this->player_base + m_vecOrigin);
	}

	void Player::set_vecorigin(Vector3 vec) {
		write_mem<Vector3>(this->handle, this->player_base + m_vecOrigin, vec);
	}

	Vector3 Player::get_viewoffset() {
		return read_mem<Vector3>(this->handle, this->player_base + m_vecViewOffset);
	}

	void Player::set_viewoffset(Vector3 vec) {
		write_mem<Vector3>(this->handle, this->player_base + m_vecViewOffset, vec);
	}

	Vector3 Player::get_camerapos() {
		Vector3 vecorigin = this->get_vecorigin();
		Vector3 viewoffset = this->get_viewoffset();
		return Vector3(vecorigin.x + viewoffset.x, vecorigin.y + viewoffset.y, vecorigin.z + viewoffset.z);
	}

	Vector3 Player::get_punchangle() {
		uintptr_t local = read_mem<uintptr_t>(this->handle, this->player_base + m_Local);
		uintptr_t punch = read_mem<uintptr_t>(this->handle, local + m_aimPunchAngle);
		return read_mem<Vector3>(this->handle, this->player_base + m_aimPunchAngle);
	}

	void Player::set_spotted(bool b) {
		write_mem<bool>(this->handle, this->player_base + m_bSpotted, b);
	}

	Vector3 Player::get_viewangle() {
		return read_mem<Vector3>(this->handle, this->player_base + m_angEyeAnglesX);
	}

}