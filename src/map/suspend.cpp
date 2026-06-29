// Copyright (c) Pandas Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#include "suspend.hpp"

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <new>

#include <common/malloc.hpp> // aMalloc, aFree
#include <common/nullpo.hpp>
#include <common/showmsg.hpp>
#include <common/sql.hpp>

#include "battle.hpp"
#include "channel.hpp"
#include "chat.hpp"
#include "chrif.hpp"
#include "clif.hpp"
#include "duel.hpp"
#include "guild.hpp"
#include "map.hpp"
#include "party.hpp"
#include "pc.hpp"
#include "storage.hpp"
#include "trade.hpp"

#ifdef Pandas_Player_Suspend_System

static DBMap* suspender_db;

void suspend_set_status(s_suspender* sp) {
	if (sp == nullptr)
		return;

	sp->sd->state.autotrade |= AUTOTRADE_ENABLED;

	switch (sp->mode) {
		case SUSPEND_MODE_OFFLINE:
			sp->sd->state.autotrade |= AUTOTRADE_OFFLINE;
			break;
		case SUSPEND_MODE_AFK:
			sp->sd->state.autotrade |= AUTOTRADE_AFK;
			break;
		case SUSPEND_MODE_NORMAL:
			sp->sd->state.autotrade |= AUTOTRADE_NORMAL;
			break;
		default:
			break;
	}

	if (sp->mode != SUSPEND_MODE_NONE && battle_config.suspend_monsterignore & sp->mode)
		sp->sd->state.block_action |= PCBLOCK_IMMUNE;
	else
		sp->sd->state.block_action &= ~PCBLOCK_IMMUNE;

	switch (sp->mode) {
		case SUSPEND_MODE_OFFLINE:
			if (battle_config.suspend_offline_bodydirection >= 0)
				sp->dir = battle_config.suspend_offline_bodydirection;
			if (battle_config.suspend_offline_headdirection >= 0)
				sp->head_dir = battle_config.suspend_offline_headdirection;
			if (battle_config.suspend_offline_sitdown >= 0)
				sp->sit = battle_config.suspend_offline_sitdown;
			break;
		case SUSPEND_MODE_AFK:
			if (battle_config.suspend_afk_bodydirection >= 0)
				sp->dir = battle_config.suspend_afk_bodydirection;
			if (battle_config.suspend_afk_headdirection >= 0)
				sp->head_dir = battle_config.suspend_afk_headdirection;
			if (battle_config.suspend_afk_sitdown >= 0)
				sp->sit = battle_config.suspend_afk_sitdown;
			break;
		case SUSPEND_MODE_NORMAL:
			if (battle_config.suspend_normal_bodydirection >= 0)
				sp->dir = battle_config.suspend_normal_bodydirection;
			if (battle_config.suspend_normal_headdirection >= 0)
				sp->head_dir = battle_config.suspend_normal_headdirection;
			if (battle_config.suspend_normal_sitdown >= 0)
				sp->sit = battle_config.suspend_normal_sitdown;
			break;
		default:
			break;
	}

#ifdef Pandas_Struct_Map_Session_Data_Autotrade_Configure
	sp->sd->pandas.at_dir = sp->dir;
	sp->sd->pandas.at_head_dir = sp->head_dir;
	sp->sd->pandas.at_sit = sp->sit;
#endif // Pandas_Struct_Map_Session_Data_Autotrade_Configure
}

bool suspend_recall(uint32 charid, e_suspend_mode mode, unsigned char body_dir, unsigned char head_dir, unsigned char sit) {
	bool ret = false;

	do {
		if (map_charid2sd(charid) != nullptr)
			break;

		if (Sql_Query(mmysql_handle,
			"SELECT `account_id`, `char_id`, `sex` "
			"FROM `%s` "
			"WHERE `char_id` = %d;",
			"char", charid) != SQL_SUCCESS) {
			Sql_ShowDebug(mmysql_handle);
			break;
		}

		if (Sql_NumRows(mmysql_handle) != 1)
			break;

		if (Sql_NextRow(mmysql_handle) != SQL_SUCCESS)
			break;

		char* data = nullptr;
		s_suspender* sp = nullptr;
		CREATE(sp, s_suspender, 1);
		memset(sp, 0, sizeof(s_suspender));

		Sql_GetData(mmysql_handle, 0, &data, nullptr); sp->account_id = atoi(data);
		Sql_GetData(mmysql_handle, 1, &data, nullptr); sp->char_id = atoi(data);
		Sql_GetData(mmysql_handle, 2, &data, nullptr); sp->sex = (data[0] == 'F') ? SEX_FEMALE : SEX_MALE;

		if (map_id2sd(sp->account_id) != nullptr) {
			aFree(sp);
			break;
		}

		if (chrif_search(sp->account_id) != nullptr) {
			aFree(sp);
			break;
		}

		CREATE(sp->sd, map_session_data, 1);
		new (sp->sd) map_session_data();
		pc_setnewpc(sp->sd, sp->account_id, sp->char_id, 0, gettick(), sp->sex, 0);

		sp->mode = mode;
		sp->dir = body_dir;
		sp->head_dir = head_dir;
		sp->sit = sit;

		suspend_set_status(sp);

		chrif_authreq(sp->sd, true);
		uidb_put(suspender_db, sp->char_id, sp);
		ret = true;
	} while (false);

	Sql_FreeResult(mmysql_handle);
	return ret;
}

void suspend_recall_all() {
	int offline = 0, afk = 0;

	do {
		if (Sql_Query(mmysql_handle,
			"SELECT `account_id`, `char_id`, `sex`, `body_direction`, `head_direction`, `sit`, `mode`, `tick`, `val1`, `val2`, `val3`, `val4` "
			"FROM `%s` "
			"ORDER BY `account_id`;",
			suspend_table) != SQL_SUCCESS) {
			Sql_ShowDebug(mmysql_handle);
			break;
		}

		if (!Sql_NumRows(mmysql_handle))
			break;

		while (Sql_NextRow(mmysql_handle) == SQL_SUCCESS) {
			char* data = nullptr;
			s_suspender* sp = nullptr;
			CREATE(sp, s_suspender, 1);
			memset(sp, 0, sizeof(s_suspender));

			Sql_GetData(mmysql_handle, 0, &data, nullptr); sp->account_id = atoi(data);
			Sql_GetData(mmysql_handle, 1, &data, nullptr); sp->char_id = atoi(data);
			Sql_GetData(mmysql_handle, 2, &data, nullptr); sp->sex = (data[0] == 'F') ? SEX_FEMALE : SEX_MALE;
			Sql_GetData(mmysql_handle, 3, &data, nullptr); sp->dir = atoi(data);
			Sql_GetData(mmysql_handle, 4, &data, nullptr); sp->head_dir = atoi(data);
			Sql_GetData(mmysql_handle, 5, &data, nullptr); sp->sit = atoi(data);
			Sql_GetData(mmysql_handle, 6, &data, nullptr); sp->mode = e_suspend_mode(atoi(data));
			Sql_GetData(mmysql_handle, 7, &data, nullptr); sp->tick = strtoll(data, nullptr, 10);
			Sql_GetData(mmysql_handle, 8, &data, nullptr); sp->val1 = atoi(data);
			Sql_GetData(mmysql_handle, 9, &data, nullptr); sp->val2 = atoi(data);
			Sql_GetData(mmysql_handle, 10, &data, nullptr); sp->val3 = atoi(data);
			Sql_GetData(mmysql_handle, 11, &data, nullptr); sp->val4 = atoi(data);

			if (map_id2sd(sp->account_id) != nullptr) {
				aFree(sp);
				continue;
			}

			if (chrif_search(sp->account_id) != nullptr) {
				aFree(sp);
				continue;
			}

			CREATE(sp->sd, map_session_data, 1);
			new (sp->sd) map_session_data();
			pc_setnewpc(sp->sd, sp->account_id, sp->char_id, 0, gettick(), sp->sex, 0);
			suspend_set_status(sp);

			switch (sp->mode) {
				case SUSPEND_MODE_OFFLINE:
					offline++;
					break;
				case SUSPEND_MODE_AFK:
					afk++;
					break;
				default:
					break;
			}

			chrif_authreq(sp->sd, true);
			uidb_put(suspender_db, sp->char_id, sp);
		}
	} while (false);

	Sql_FreeResult(mmysql_handle);
	ShowStatus("Done loading '" CL_WHITE "%d" CL_RESET "' suspend player records (Offline: '%d', AFK: '%d').\n", db_size(suspender_db), offline, afk);
}

void suspend_recall_postfix(map_session_data* sd) {
	nullpo_retv(sd);

	s_suspender* sp = static_cast<s_suspender*>(uidb_get(suspender_db, sd->status.char_id));

	if (sp != nullptr) {
		pc_setdir(sd, sp->dir, sp->head_dir);
		clif_changed_dir(*sd, AREA_WOS);

		if (sp->sit) {
			pc_setsit(sd);
			skill_sit(sd, true);
			clif_sitting(*sd);
		}

		switch (sp->mode) {
			case SUSPEND_MODE_AFK:
				if (battle_config.suspend_afk_headtop_viewid)
					clif_changelook(sd, LOOK_HEAD_TOP, battle_config.suspend_afk_headtop_viewid);
				break;
			default:
				break;
		}
	}
}

void suspend_set_unit_idle(const map_session_data* sd, packet_idle_unit* p) {
	nullpo_retv(sd);
	nullpo_retv(p);

	if (sd->type != BL_PC)
		return;

	s_suspender* sp = static_cast<s_suspender*>(uidb_get(suspender_db, sd->status.char_id));

	if (sp != nullptr) {
		switch (sp->mode) {
			case SUSPEND_MODE_AFK:
				if (battle_config.suspend_afk_headtop_viewid)
					p->accessory2 = battle_config.suspend_afk_headtop_viewid;
				break;
			default:
				break;
		}
	}
}

void suspend_set_unit_walking(const map_session_data* sd, packet_unit_walking* p) {
	nullpo_retv(sd);
	nullpo_retv(p);

	if (sd->type != BL_PC)
		return;

	s_suspender* sp = static_cast<s_suspender*>(uidb_get(suspender_db, sd->status.char_id));

	if (sp != nullptr) {
		switch (sp->mode) {
			case SUSPEND_MODE_AFK:
				if (battle_config.suspend_afk_headtop_viewid)
					p->accessory2 = battle_config.suspend_afk_headtop_viewid;
				break;
			default:
				break;
		}
	}
}

void suspend_active(map_session_data* sd, e_suspend_mode smode) {
	nullpo_retv(sd);

	long val[4] = { 0 };
	int sitting = -1, headdirection = -1, bodydirection = -1;

	suspend_deactive(sd, false);

	sd->state.autotrade |= AUTOTRADE_ENABLED;

	switch (smode) {
		case SUSPEND_MODE_OFFLINE:
			sd->state.autotrade |= AUTOTRADE_OFFLINE;
			break;
		case SUSPEND_MODE_AFK:
			sd->state.autotrade |= AUTOTRADE_AFK;
			break;
		case SUSPEND_MODE_NORMAL:
			sd->state.autotrade |= AUTOTRADE_NORMAL;
			break;
		default:
			break;
	}

	if (smode != SUSPEND_MODE_NONE && battle_config.suspend_monsterignore & smode)
		sd->state.block_action |= PCBLOCK_IMMUNE;
	else
		sd->state.block_action &= ~PCBLOCK_IMMUNE;

	switch (smode) {
		case SUSPEND_MODE_AFK:
			if (battle_config.suspend_afk_sitdown == 0)
				sitting = 0;
			else if (battle_config.suspend_afk_sitdown == 1)
				sitting = 1;
			if (battle_config.suspend_afk_bodydirection >= 0)
				bodydirection = battle_config.suspend_afk_bodydirection;
			if (battle_config.suspend_afk_headdirection >= 0)
				headdirection = battle_config.suspend_afk_headdirection;
			if (battle_config.suspend_afk_headtop_viewid)
				clif_changelook(sd, LOOK_HEAD_TOP, battle_config.suspend_afk_headtop_viewid);
			break;
		case SUSPEND_MODE_OFFLINE:
			if (battle_config.suspend_offline_sitdown == 0)
				sitting = 0;
			else if (battle_config.suspend_offline_sitdown == 1)
				sitting = 1;
			if (battle_config.suspend_offline_bodydirection >= 0)
				bodydirection = battle_config.suspend_offline_bodydirection;
			if (battle_config.suspend_offline_headdirection >= 0)
				headdirection = battle_config.suspend_offline_headdirection;
			break;
		case SUSPEND_MODE_NORMAL:
			if (battle_config.suspend_normal_sitdown == 0)
				sitting = 0;
			else if (battle_config.suspend_normal_sitdown == 1)
				sitting = 1;
			if (battle_config.suspend_normal_bodydirection >= 0)
				bodydirection = battle_config.suspend_normal_bodydirection;
			if (battle_config.suspend_normal_headdirection >= 0)
				headdirection = battle_config.suspend_normal_headdirection;
			break;
		default:
			break;
	}

	if (sitting == 0 && pc_issit(sd)) {
		pc_setstand(sd, true);
		skill_sit(sd, false);
		clif_standing(*sd);
	} else if (sitting == 1 && !pc_issit(sd)) {
		pc_setsit(sd);
		skill_sit(sd, true);
		clif_sitting(*sd);
	}

	if (bodydirection >= 0) {
		pc_setdir(sd, bodydirection, sd->head_dir);
		clif_changed_dir(*sd, AREA_WOS);
		clif_changed_dir(*sd, SELF);
	}

	if (headdirection >= 0) {
		pc_setdir(sd, sd->ud.dir, headdirection);
		clif_changed_dir(*sd, AREA_WOS);
		clif_changed_dir(*sd, SELF);
	}

	s_suspender* sp = nullptr;
	CREATE(sp, s_suspender, 1);
	memset(sp, 0, sizeof(s_suspender));

	sp->account_id = sd->status.account_id;
	sp->char_id = sd->status.char_id;
	sp->sex = sd->status.sex;
	sp->dir = sd->ud.dir;
	sp->head_dir = sd->head_dir;
	sp->sit = pc_issit(sd);
	sp->mode = smode;
	sp->tick = static_cast<t_tick>(time(nullptr));
	uidb_put(suspender_db, sp->char_id, sp);

#ifdef Pandas_Struct_Map_Session_Data_Autotrade_Configure
	// 这里需要立刻填充相关的备份信息, 避免在完成指令下线后,
	// 服务器没还重启的情况下, 角色就被 recall 导致朝向等数据无法恢复
	sd->pandas.at_dir = sd->ud.dir;
	sd->pandas.at_head_dir = sd->head_dir;
	sd->pandas.at_sit = pc_issit(sd);
#endif // Pandas_Struct_Map_Session_Data_Autotrade_Configure

	if (Sql_Query(mmysql_handle, "INSERT INTO `%s`(`account_id`, `char_id`, `sex`, `map`, `x`, `y`, `body_direction`, `head_direction`, `sit`, `mode`, `tick`, `val1`, `val2`, `val3`, `val4`) "
		"VALUES( %d, %d, '%c', '%s', %d, %d, '%d', '%d', '%d', '%hu', '%" PRtf "', '%ld', '%ld', '%ld', '%ld' );",
		suspend_table, sd->status.account_id, sd->status.char_id, sd->status.sex == SEX_FEMALE ? 'F' : 'M', map_getmapdata(sd->m)->name,
		sd->x, sd->y, sd->ud.dir, sd->head_dir, pc_issit(sd), int(smode), gettick(), val[0], val[1], val[2], val[3]) != SQL_SUCCESS) {
		Sql_ShowDebug(mmysql_handle);
	}

	if (sd->chatID)
		chat_leavechat(sd, 0);

	if (sd->state.trading)
		trade_tradecancel(sd);

	if (sd->state.storage_flag == 1)
		storage_storage_quit(sd, 0);
	else if (sd->state.storage_flag == 2)
		storage_guild_storage_quit(sd, 0);
	else if (sd->state.storage_flag == 3)
		storage_premiumStorage_quit(sd);

	sd->state.storage_flag = 0;

	if (sd->party_invite > 0)
		party_reply_invite(*sd, sd->party_invite, 0);

	if (sd->guild_invite > 0)
		guild_reply_invite(*sd, sd->guild_invite, 0);

	if (sd->guild_alliance > 0)
		guild_reply_reqalliance(sd, sd->guild_alliance_account, 0);

	if (sd->duel_group > 0)
		duel_leave(sd->duel_group, sd);

	channel_pcquit(sd, 0xF);
	clif_authfail_fd(sd->fd, 15);
	chrif_save(sd, CSAVE_AUTOTRADE);
}

static void suspend_suspender_remove(s_suspender* sp, bool remove) {
	nullpo_retv(sp);

	if (remove)
		uidb_remove(suspender_db, sp->char_id);

	aFree(sp);
}

static int32 suspend_suspender_free(DBKey key, DBData* data, va_list ap) {
	s_suspender* sp = static_cast<s_suspender*>(db_data2ptr(data));

	if (sp == nullptr)
		return -1;

	suspend_suspender_remove(sp, false);
	return 0;
}

void suspend_deactive(map_session_data* sd, bool keep_database) {
	nullpo_retv(sd);

	if (!keep_database) {
		if (Sql_Query(mmysql_handle, "DELETE FROM `%s` WHERE `account_id` = %d;", suspend_table, sd->status.account_id) != SQL_SUCCESS)
			Sql_ShowDebug(mmysql_handle);
	}

	s_suspender* sp = static_cast<s_suspender*>(uidb_get(suspender_db, sd->status.char_id));

	if (sp != nullptr)
		suspend_suspender_remove(sp, true);
}

void do_final_suspend() {
	suspender_db->destroy(suspender_db, suspend_suspender_free);
}

void do_init_suspend() {
	suspender_db = uidb_alloc(DB_OPT_BASE);
}

#endif // Pandas_Player_Suspend_System
