#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include "Utils.hpp"

namespace csgo {

	extern size_t cs_gamerules_data;
	extern size_t m_ArmorValue;
	extern size_t m_Collision;
	extern size_t m_CollisionGroup;
	extern size_t m_Local;
	extern size_t m_MoveType;
	extern size_t m_OriginalOwnerXuidHigh;
	extern size_t m_OriginalOwnerXuidLow;
	extern size_t m_SurvivalGameRuleDecisionTypes;
	extern size_t m_SurvivalRules;
	extern size_t m_aimPunchAngle;
	extern size_t m_aimPunchAngleVel;
	extern size_t m_angEyeAnglesX;
	extern size_t m_angEyeAnglesY;
	extern size_t m_bBombDefused;
	extern size_t m_bBombPlanted;
	extern size_t m_bBombTicking;
	extern size_t m_bFreezePeriod;
	extern size_t m_bGunGameImmunity;
	extern size_t m_bHasDefuser;
	extern size_t m_bHasHelmet;
	extern size_t m_bInReload;
	extern size_t m_bIsDefusing;
	extern size_t m_bIsQueuedMatchmaking;
	extern size_t m_bIsScoped;
	extern size_t m_bIsValveDS;
	extern size_t m_bSpotted;
	extern size_t m_bSpottedByMask;
	extern size_t m_bStartedArming;
	extern size_t m_bUseCustomAutoExposureMax;
	extern size_t m_bUseCustomAutoExposureMin;
	extern size_t m_bUseCustomBloomScale;
	extern size_t m_clrRender;
	extern size_t m_dwBoneMatrix;
	extern size_t m_fAccuracyPenalty;
	extern size_t m_fFlags;
	extern size_t m_flC4Blow;
	extern size_t m_flCustomAutoExposureMax;
	extern size_t m_flCustomAutoExposureMin;
	extern size_t m_flCustomBloomScale;
	extern size_t m_flDefuseCountDown;
	extern size_t m_flDefuseLength;
	extern size_t m_flFallbackWear;
	extern size_t m_flFlashDuration;
	extern size_t m_flFlashMaxAlpha;
	extern size_t m_flLastBoneSetupTime;
	extern size_t m_flLowerBodyYawTarget;
	extern size_t m_flNextAttack;
	extern size_t m_flNextPrimaryAttack;
	extern size_t m_flSimulationTime;
	extern size_t m_flTimerLength;
	extern size_t m_hActiveWeapon;
	extern size_t m_hBombDefuser;
	extern size_t m_hMyWeapons;
	extern size_t m_hObserverTarget;
	extern size_t m_hOwner;
	extern size_t m_hOwnerEntity;
	extern size_t m_hViewModel;
	extern size_t m_iAccountID;
	extern size_t m_iClip1;
	extern size_t m_iCompetitiveRanking;
	extern size_t m_iCompetitiveWins;
	extern size_t m_iCrosshairId;
	extern size_t m_iDefaultFOV;
	extern size_t m_iEntityQuality;
	extern size_t m_iFOVStart;
	extern size_t m_iGlowIndex;
	extern size_t m_iHealth;
	extern size_t m_iItemDefinitionIndex;
	extern size_t m_iItemIDHigh;
	extern size_t m_iMostRecentModelBoneCounter;
	extern size_t m_iObserverMode;
	extern size_t m_iShotsFired;
	extern size_t m_iState;
	extern size_t m_iTeamNum;
	extern size_t m_lifeState;
	extern size_t m_nBombSite;
	extern size_t m_nFallbackPaintKit;
	extern size_t m_nFallbackSeed;
	extern size_t m_nFallbackStatTrak;
	extern size_t m_nForceBone;
	extern size_t m_nTickBase;
	extern size_t m_nViewModelIndex;
	extern size_t m_rgflCoordinateFrame;
	extern size_t m_szCustomName;
	extern size_t m_szLastPlaceName;
	extern size_t m_thirdPersonViewAngles;
	extern size_t m_vecOrigin;
	extern size_t m_vecVelocity;
	extern size_t m_vecViewOffset;
	extern size_t m_viewPunchAngle;
	extern size_t m_zoomLevel;
	extern size_t anim_overlays;
	extern size_t clientstate_choked_commands;
	extern size_t clientstate_delta_ticks;
	extern size_t clientstate_last_outgoing_command;
	extern size_t clientstate_net_channel;
	extern size_t convar_name_hash_table;
	extern size_t dwClientState;
	extern size_t dwClientState_GetLocalPlayer;
	extern size_t dwClientState_IsHLTV;
	extern size_t dwClientState_Map;
	extern size_t dwClientState_MapDirectory;
	extern size_t dwClientState_MaxPlayer;
	extern size_t dwClientState_PlayerInfo;
	extern size_t dwClientState_State;
	extern size_t dwClientState_ViewAngles;
	extern size_t dwEntityList;
	extern size_t dwForceAttack;
	extern size_t dwForceAttack2;
	extern size_t dwForceBackward;
	extern size_t dwForceForward;
	extern size_t dwForceJump;
	extern size_t dwForceLeft;
	extern size_t dwForceRight;
	extern size_t dwGameDir;
	extern size_t dwGameRulesProxy;
	extern size_t dwGetAllClasses;
	extern size_t dwGlobalVars;
	extern size_t dwGlowObjectManager;
	extern size_t dwInput;
	extern size_t dwInterfaceLinkList;
	extern size_t dwLocalPlayer;
	extern size_t dwMouseEnable;
	extern size_t dwMouseEnablePtr;
	extern size_t dwPlayerResource;
	extern size_t dwRadarBase;
	extern size_t dwSensitivity;
	extern size_t dwSensitivityPtr;
	extern size_t dwSetClanTag;
	extern size_t dwViewMatrix;
	extern size_t dwWeaponTable;
	extern size_t dwWeaponTableIndex;
	extern size_t dwYawPtr;
	extern size_t dwZoomSensitivityRatioPtr;
	extern size_t dwbSendPackets;
	extern size_t dwppDirect3DDevice9;
	extern size_t find_hud_element;
	extern size_t force_update_spectator_glow;
	extern size_t interface_engine_cvar;
	extern size_t is_c4_owner;
	extern size_t m_bDormant;
	extern size_t m_flSpawnTime;
	extern size_t m_pStudioHdr;
	extern size_t m_pitchClassPtr;
	extern size_t m_yawClassPtr;
	extern size_t model_ambient_min;
	extern size_t set_abs_angles;
	extern size_t set_abs_origin;

	struct ModuleInfo;

	extern int success_rate;
	extern int total_items;

	void findOffsets(DWORD pid, HANDLE process);
	size_t findOffset(const char* pattern, size_t offset, uint8_t extra, ModuleInfo info);

}