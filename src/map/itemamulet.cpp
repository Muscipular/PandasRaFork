// Copyright (c) Pandas Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#include "itemamulet.hpp"

#include <cstring>

#include <common/nullpo.hpp>
#include <common/utils.hpp>

#include "itemdb.hpp"
#include "itemprops.hpp"
#include "pc.hpp"
#include "script.hpp"

#ifdef Pandas_Item_Amulet_System

extern int16 current_equip_item_index;

// 给定一个道具编号确认它是否为一个护身符类型的道具
bool amulet_is(t_itemid nameid) {
	struct item_data* item = itemdb_search(nameid);
	return ITEM_PROPERTIES_HASFLAG(item, special_mask, ITEM_PRO_IS_AMULET_ITEM);
}

// 给定一个道具编号返回它的道具类型, 此函数用于 clif 给客户端发数据前使用
int amulet_pandas_type(t_itemid nameid) {
	return amulet_is(nameid) ? IT_ETC : itemdb_search(nameid)->type;
}

// 给定的 item 是否为该角色身上同类型护身符中的第一个
bool amulet_is_firstone(map_session_data *sd, struct item *item, int amount) {
	nullpo_retr(false, sd);
	nullpo_retr(false, item);

	amount = cap_value(amount, 0, MAX_AMOUNT);
	if (item->nameid == 0 || amount <= 0)
		return false;

	if (!amulet_is(item->nameid))
		return false;

	struct item_data *id = itemdb_search(item->nameid);
	if (!itemdb_isstackable2(id) || item->expire_time != 0)
		return false;

	for (uint32 i = 0; i < MAX_INVENTORY; i++) {
		if (sd->inventory.u.items_inventory[i].nameid == item->nameid &&
			sd->inventory.u.items_inventory[i].bound == item->bound &&
			sd->inventory.u.items_inventory[i].expire_time == 0 &&
			sd->inventory.u.items_inventory[i].unique_id == item->unique_id &&
			memcmp(&sd->inventory.u.items_inventory[i].card, &item->card, sizeof(item->card)) == 0) {
			return false;
		}
	}

	return true;
}

// 判断删除掉指定数量的护身符道具后, 角色身上就不存在其他同类护身符了
bool amulet_is_lastone(map_session_data *sd, int n, int amount) {
	nullpo_retr(false, sd);

	amount = cap_value(amount, 0, MAX_AMOUNT);
	if (n < 0 || n >= MAX_INVENTORY || sd->inventory_data[n] == nullptr || amount <= 0)
		return false;

	struct item_data *item = sd->inventory_data[n];
	if (!amulet_is(item->nameid))
		return false;

	return (sd->inventory.u.items_inventory[n].amount - amount) <= 0;
}

// 添加新的护身符道具时, 根据需要重算角色的能力
void amulet_apply_additem(map_session_data *sd, int n, bool is_firstone) {
	nullpo_retv(sd);

	if (n < 0 || n >= MAX_INVENTORY || sd->inventory_data[n] == nullptr)
		return;

	struct item_data *item = sd->inventory_data[n];
	if (!amulet_is(item->nameid))
		return;

	if (is_firstone && item->equip_script) {
		// 如果这是背包中出现的第一个同种类护身符, 那么触发"穿戴脚本"
		run_script(item->equip_script, 0, sd->id, 0);
		status_calc_pc(sd, SCO_NONE);
	} else if (item->script) {
		// 否则如果有"使用脚本"的话, 也需要重算一下角色能力
		status_calc_pc(sd, SCO_NONE);
	}
}

// 删除老的护身符道具时, 根据需要重算角色的能力
void amulet_apply_delitem(map_session_data *sd, int n, bool is_lastone) {
	nullpo_retv(sd);

	if (n < 0 || n >= MAX_INVENTORY || sd->inventory_data[n] == nullptr)
		return;

	struct item_data *item = sd->inventory_data[n];
	if (!amulet_is(item->nameid))
		return;

	if (is_lastone && item->unequip_script) {
		// 如果移除的护身符是身上同种类护身符的最后一个, 那么触发"卸装脚本"
		int16 save_current_equip_item_index = current_equip_item_index;
		current_equip_item_index = n;
		run_script(item->unequip_script, 0, sd->id, 0);
		current_equip_item_index = save_current_equip_item_index;
		status_calc_pc(sd, SCO_NONE);
	} else if (item->script) {
		// 否则如果有"使用脚本"的话, 也需要重算一下角色能力
		status_calc_pc(sd, SCO_NONE);
	}
}

// 重新应用角色身上全部护身符道具的脚本效果
void amulet_status_calc(map_session_data *sd, uint8 opt) {
	nullpo_retv(sd);

	if (sd->pandas.amulet_calculating)
		return;

	sd->pandas.amulet_calculating = true;

	int16 save_current_equip_item_index = current_equip_item_index;

	for (uint32 i = 0; i < MAX_INVENTORY; i++) {
		if (sd->inventory_data[i] == nullptr)
			continue;

		if (!amulet_is(sd->inventory_data[i]->nameid))
			continue;

		std::shared_ptr<item_data> id = item_db.find(sd->inventory_data[i]->nameid);
		if (id && itemdb_isNoEquip(id.get(), sd->m))
			continue;

		current_equip_item_index = i;

		if ((opt & SCO_FIRST) && sd->inventory_data[i]->equip_script) {
			run_script(sd->inventory_data[i]->equip_script, 0, sd->id, 0);
		}

		if (sd->inventory_data[i]->script) {
			// 这件护身符在身上有多少个, 就执行多少次"使用脚本"
			for (uint16 k = 0; k < sd->inventory.u.items_inventory[i].amount; k++) {
				run_script(sd->inventory_data[i]->script, 0, sd->id, 0);
				if (!sd->pandas.amulet_calculating) {
					current_equip_item_index = save_current_equip_item_index;
					return;
				}
			}
		}
	}

	current_equip_item_index = save_current_equip_item_index;
	sd->pandas.amulet_calculating = false;
}

#endif // Pandas_Item_Amulet_System
