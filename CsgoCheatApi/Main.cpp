#include "Context.hpp"
#include <chrono>
#include <string>
using namespace csgo;
using namespace std;
using namespace std::chrono;

namespace cheat {

	Context* context;

	bool aimbot = false;
	bool wallhack = false;
	bool bunnyhop = false;
	bool godmode = false;

	int bone_index = BoneMatrix::HEAD;
	milliseconds last_refresh;
	milliseconds last_input;

	bool force_aim = false;
	bool force_shoot = false;

	milliseconds shoot_delay = 0ms;

	milliseconds lastTime;
	float direction;
	bool begin;

	bool spam;

	bool is_harmful(Player* local, Player* player) {
		return local->get_team() != player->get_team() && player->get_health() > 0 && player->get_health() <= 100 && !player->is_dormant();
	}

	milliseconds current() {
		return duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	}

	int run_cheat() {
		context = new Context();
		while (!GetAsyncKeyState(VK_ADD)) {
			milliseconds cur = current();
			if (lastTime == 0ms) {
				lastTime = cur;
			}
			milliseconds delta = cur - lastTime;
			lastTime = cur;
			Sleep(0);

			if (current() > last_refresh + 100ms) {
				last_refresh = current();
//				std::cout << "Main.cpp: " << dwEntityList << std::endl;
				context->refresh_players();
				
			}

			force_aim = false;
			force_shoot = false;
			Player* target = nullptr;
			Player* local = context->get_local_player();
			int localTeam = local->get_team();

			// Find closest enemy
			Player* closest_player = nullptr;
			context->draw_cross(xhairx, xhairy, 0x00FFFF);
			float closest = FLT_MAX;
			for (int i = 0; i < 32; i++) {
				Player* player = context->get_player(i);
				if (!player->get_base()) {
					continue;
				}
				if (!is_harmful(local, player)) {
					continue;
				}

				player->set_spotted(true);
				// Check if closest
				BoneMatrix bone = player->get_bmatrix(bone_index);
				Vector3 bone_pos = world_to_screen(Vector3(bone.x, bone.y, bone.z), context->get_view_matrix());
				float dist = distance(xhairx, xhairy, bone_pos.x, bone_pos.y);
				if (dist < closest && bone_pos.z > 0.0001f) {
					closest = dist;
					closest_player = player;
				}
			}
			if (closest_player) {
				target = closest_player;
			}

			// Check if any player is aiming at our direction
			Player* closest_aiming = nullptr;
			closest = FLT_MAX;
			for (int i = 0; i < 32; i++) {
				Player* player = context->get_player(i);
				if (!player->get_base()) {
					continue;
				}
				if (!is_harmful(local, player)) {
					continue;
				}
				// Here we use the 8 constant because we only care about head rotation
				BoneMatrix my_head = local->get_bmatrix(BoneMatrix::HEAD);
				Vector3 my_vec = Vector3(my_head.x, my_head.y, my_head.z);
				BoneMatrix other_head = player->get_bmatrix(BoneMatrix::HEAD);
				Vector3 other_vec = Vector3(other_head.x, other_head.y, other_head.z);

				Vector3 danger_angle = look_at(other_vec, my_vec);
				Vector3 actual_angle = player->get_viewangle();

				float xdiff = danger_angle.x - actual_angle.y;
				float ydiff = danger_angle.y - actual_angle.x;
				float diff = distance(0, 0, xdiff, ydiff);

				if (diff <= 7) {
					Vector3 projection = world_to_screen(other_vec, context->get_view_matrix());
					float dist = distance(projection.x, projection.y, xhairx, xhairy);
					if (dist < closest) {
						closest = dist;
					}
					closest_aiming = player;
				}
			}
			if (closest_aiming && godmode) {
				target = closest_aiming;
				force_aim = true;
			}

			// Draw cross on players
			if (wallhack) {
				for (int i = 0; i < 32; i++) {
					Player* player = context->get_player(i);
					if (!player->get_base()) {
						continue;
					}
					if (!is_harmful(local, player)) continue;

					// Draw cross
					BoneMatrix bone = player->get_bmatrix(bone_index);
					Vector3 bone_pos = world_to_screen(Vector3(bone.x, bone.y, bone.z), context->get_view_matrix());
					if (wallhack) {
						if (bone_pos.z > 0.0001f) {
							COLORREF color = 0xFFFF00;
							if (player == closest_player) {
								color = 0x0000FF;
								context->draw_line(xhairx, xhairy, bone_pos.x, bone_pos.y, color);
							}
							if(player == closest_aiming) {
								color = RGB(0, 0, 255);
								context->draw_line(xhairx, xhairy, bone_pos.x, bone_pos.y, color);
							}
							context->draw_cross(bone_pos.x, bone_pos.y, color);
							string health_str = std::to_string(player->get_health());
							const char* health = health_str.c_str();
							context->draw_text(health, bone_pos.x, bone_pos.y - 25, 40, color);
						}
					}
				}
			}

			// Move view to closest player
			if (GetAsyncKeyState(VK_MENU) || force_aim) {
				if (local && target && aimbot) {
					BoneMatrix other_head = target->get_bmatrix(bone_index);
					Vector3 my_head = local->get_camerapos();
					Vector3 other = Vector3(other_head.x, other_head.y, other_head.z);

					Vector3 angle = look_at(my_head, other);
					Vector3 punch = context->get_local_player()->get_punchangle();
					context->set_viewangle(Vector3(angle.y - (punch.x * 1), angle.x - (punch.y * 1), 0));
					force_shoot = true;
				}
			}

			// Automatically handle firing weapons and stuff
			if ((GetAsyncKeyState(VK_LBUTTON) || force_shoot) && godmode) {
				if (current() >= shoot_delay && godmode) {
					context->force_shoot_primary();
					// The farther the player, the more time between each shot
					// More precise
					// Values from 0ms to 500ms
					if (target) {
						BoneMatrix other_head = target->get_bmatrix(bone_index);
						Vector3 other_vec = Vector3(other_head.x, other_head.y, other_head.z);
						Vector3 my_vec = local->get_camerapos();
						float distance = sqrtf(powf(other_vec.x - my_vec.x, 2) + powf(other_vec.y - my_vec.y, 2) + powf(other_vec.z - my_vec.z, 2));
						// Assume distance is in cm
						const float max_delay = 500;
						float delay = (distance / 2000) * max_delay;
						delay = delay > max_delay ? max_delay : delay;
						milliseconds msdelay = chrono::milliseconds((int) delay);
						shoot_delay = msdelay + current();
					}
				}
			}

			// Accept input commands
			if (current() > last_input + 250ms) {
				last_input = current();

				// Change bone index
				if (GetAsyncKeyState(VK_F8)) {
					bone_index++;
				}
				if (GetAsyncKeyState(VK_F7)) {
					bone_index--;
				}
				if (GetAsyncKeyState(VK_F9)) {
					bone_index = BoneMatrix::HEAD;
				}

				// Spambot
				if (GetAsyncKeyState('P')) {
					spam = !spam;
				}
			}

			// Spam
			if (GetAsyncKeyState(VK_LBUTTON) && spam) {
				context->force_shoot_primary(true);
				Sleep(1);
				context->force_shoot_primary(false);
			}

			// Apply bunnyhopping
			if (GetAsyncKeyState(VK_SPACE) && bunnyhop) {
				context->force_jump(local->get_flags() & 1);

				if (!begin) {
					begin = true;
					direction = 0;
				}

				Vector3 angle = context->get_viewangle();
				direction += delta.count() * 0.01f;
				float dir = sinf(direction) / 6;
				context->set_viewangle(Vector3(angle.x, angle.y + dir, angle.z));

				if (dir > 0) {
					context->force_left();
				}
				else {
					context->force_right();
				}
			}
			else {
				begin = false;
			}
		}

		return 0;
	}

}

int main(int argc, char** argv) {

	cheat::aimbot = MessageBoxA(NULL, "Aimbot?", "Aimbot", MB_YESNO) == 6;
	cheat::wallhack = MessageBoxA(NULL, "Wallhack?", "Wallhack", MB_YESNO) == 6;
	cheat::bunnyhop = MessageBoxA(NULL, "Bunnyhop?", "Bunnyhop", MB_YESNO) == 6;
	cheat::godmode = MessageBoxA(NULL, "Godmode?", "Godmode", MB_YESNO) == 6;

	return cheat::run_cheat();
}