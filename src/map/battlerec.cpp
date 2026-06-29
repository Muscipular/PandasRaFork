// Copyright (c) Pandas Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#include "battlerec.hpp"

#include "battle.hpp"
#include "elemental.hpp"
#include "homunculus.hpp"
#include "mercenary.hpp"
#include "mob.hpp"
#include "pc.hpp"
#include "pet.hpp"
#include "status.hpp"

#include <common/nullpo.hpp>
#include <common/utilities.hpp>

inline int32 batrec_key(struct block_list* bl) {
	if (bl && bl->type == BL_PC) {
		return reinterpret_cast<TBL_PC*>(bl)->status.char_id;
	}

	return bl ? bl->id : 0;
}

inline int32 batrec_key(uint32 block_id) {
	struct block_list* bl = map_id2bl(block_id);

	return batrec_key(bl);
}

bool batrec_cmp_asc(std::pair<uint32, s_batrec_item_ptr>& l,
	std::pair<uint32, s_batrec_item_ptr>& r)
{
	if (l.second->damage != r.second->damage) {
		return l.second->damage < r.second->damage;
	}

	return l.first < r.first;
}

bool batrec_cmp_desc(std::pair<uint32, s_batrec_item_ptr>& l,
	std::pair<uint32, s_batrec_item_ptr>& r)
{
	if (l.second->damage != r.second->damage) {
		return l.second->damage > r.second->damage;
	}

	return l.first > r.first;
}

void batrec_new(struct block_list* bl) {
	nullpo_retv(bl);

	struct s_unit_common_data* ucd = status_get_ucd(bl);
	if (ucd == nullptr)
		return;

	if (!batrec_support(bl)) {
		batrec_free(bl);
		ucd->batrec.dorecord = false;
		return;
	}

	if (ucd->batrec.dmg_receive == nullptr) {
		ucd->batrec.dmg_receive = new batrec_map;
	}
	if (ucd->batrec.dmg_cause == nullptr) {
		ucd->batrec.dmg_cause = new batrec_map;
	}

	ucd->batrec.dmg_receive->clear();
	ucd->batrec.dmg_cause->clear();

	ucd->batrec.dorecord = (battle_config.batrec_autoenabled_unit & bl->type) == bl->type;
}

void batrec_free(struct block_list* bl) {
	nullpo_retv(bl);

	struct s_unit_common_data* ucd = status_get_ucd(bl);
	if (ucd == nullptr)
		return;

	if (ucd->batrec.dmg_receive != nullptr) {
		delete ucd->batrec.dmg_receive;
		ucd->batrec.dmg_receive = nullptr;
	}

	if (ucd->batrec.dmg_cause != nullptr) {
		delete ucd->batrec.dmg_cause;
		ucd->batrec.dmg_cause = nullptr;
	}
}

void batrec_sortout(struct block_list* bl, e_batrec_type type) {
	nullpo_retv(bl);

	batrec_map* rec = batrec_getmap(bl, type);
	if (rec == nullptr)
		return;

	for (auto iter = rec->begin(); iter != rec->end();) {
		struct block_list* tbl = nullptr;
		map_session_data* sd = map_charid2sd(iter->first);

		if (sd != nullptr)
			tbl = &sd->bl;
		if (tbl == nullptr)
			tbl = map_id2bl(iter->first);

		if (tbl == nullptr)
			iter = rec->erase(iter);
		else
			++iter;
	}
}

void batrec_sortout(struct block_list* bl) {
	nullpo_retv(bl);

	batrec_sortout(bl, BRT_DMG_RECEIVE);
	batrec_sortout(bl, BRT_DMG_CAUSE);
}

inline int32 batrec_masterid(struct block_list* bl) {
	nullpo_retr(0, bl);

	TBL_PC* sd = nullptr;

	switch (bl->type) {
		case BL_MOB: {
			TBL_MOB* md = map_id2md(bl->id);
			return md != nullptr ? md->master_id : 0;
		}
		case BL_HOM: {
			TBL_HOM* hd = map_id2hd(bl->id);
			if (hd == nullptr)
				return 0;
			sd = map_charid2sd(hd->homunculus.char_id);
			return sd != nullptr ? sd->bl.id : 0;
		}
		case BL_PET: {
			TBL_PET* pd = map_id2pd(bl->id);
			return pd != nullptr ? pd->pet.account_id : 0;
		}
		case BL_MER: {
			TBL_MER* mc = map_id2mc(bl->id);
			if (mc == nullptr)
				return 0;
			sd = map_charid2sd(mc->mercenary.char_id);
			return sd != nullptr ? sd->bl.id : 0;
		}
		case BL_ELEM: {
			TBL_ELEM* ed = map_id2ed(bl->id);
			if (ed == nullptr)
				return 0;
			sd = map_charid2sd(ed->elemental.char_id);
			return sd != nullptr ? sd->bl.id : 0;
		}
	}

	return 0;
}

bool batrec_dorecord(struct block_list* bl) {
	nullpo_retr(false, bl);

	struct s_unit_common_data* ucd = status_get_ucd(bl);
	if (ucd == nullptr)
		return false;

	if (ucd->batrec.dorecord) {
		if (ucd->batrec.dmg_receive == nullptr) {
			ucd->batrec.dmg_receive = new batrec_map;
		}
		if (ucd->batrec.dmg_cause == nullptr) {
			ucd->batrec.dmg_cause = new batrec_map;
		}
	}

	return ucd->batrec.dorecord;
}

batrec_map* batrec_getmap(struct block_list* bl, e_batrec_type type) {
	nullpo_retr(nullptr, bl);

	struct s_unit_common_data* ucd = status_get_ucd(bl);
	if (ucd == nullptr)
		return nullptr;

	switch (type) {
		case BRT_DMG_RECEIVE:
			return ucd->batrec.dmg_receive;
		case BRT_DMG_CAUSE:
			return ucd->batrec.dmg_cause;
		default:
			return nullptr;
	}
}

void batrec_aggregation(batrec_map* origin_rec, batrec_map& ret_rec, e_batrec_agg agg) {
	nullpo_retv(origin_rec);

	if (agg != BRA_COMBINE) {
		ret_rec = *origin_rec;
		return;
	}

	ret_rec.clear();

	for (auto& record : *origin_rec) {
		if (record.second->interactive_master_id == 0) {
			if (ret_rec.find(record.first) == ret_rec.end()) {
				s_batrec_item_ptr item = std::make_shared<s_batrec_item>();
				item->interactive_block_id = record.second->interactive_block_id;
				item->interactive_block_type = record.second->interactive_block_type;
				item->interactive_master_id = 0;
				item->damage = record.second->damage;

				ret_rec.insert(std::make_pair(record.first, item));
			}
		} else {
			auto it = ret_rec.find(batrec_key(record.second->interactive_master_id));
			if (it == ret_rec.end()) {
				struct block_list* master_bl = map_id2bl(record.second->interactive_master_id);
				if (master_bl == nullptr)
					continue;

				s_batrec_item_ptr item = std::make_shared<s_batrec_item>();
				item->interactive_block_id = master_bl->id;
				item->interactive_block_type = master_bl->type;
				item->interactive_master_id = 0;
				item->damage = record.second->damage;

				ret_rec.insert(std::make_pair(batrec_key(record.second->interactive_master_id), item));
			} else {
				it->second->damage = rathena::util::safe_addition_cap(
					it->second->damage, record.second->damage, INT64_MAX
				);
			}
		}
	}
}

bool batrec_record(struct block_list* mbl, struct block_list* tbl, e_batrec_type type, int damage) {
	nullpo_retr(false, mbl);
	nullpo_retr(false, tbl);

	if (batrec_key(mbl) == batrec_key(tbl))
		return false;

	if (!batrec_dorecord(mbl))
		return false;

	batrec_map* rec = batrec_getmap(mbl, type);
	if (rec == nullptr)
		return false;

	auto it = rec->find(batrec_key(tbl));
	if (it == rec->end()) {
		s_batrec_item_ptr item = std::make_shared<s_batrec_item>();
		item->interactive_block_id = tbl->id;
		item->interactive_block_type = tbl->type;
		item->interactive_master_id = batrec_masterid(tbl);
		item->damage = damage;

		rec->insert(std::make_pair(batrec_key(tbl), item));
	} else {
		it->second->damage = rathena::util::safe_addition_cap(
			it->second->damage, static_cast<int64>(damage), INT64_MAX
		);
	}

	return true;
}

int64 batrec_query(struct block_list* mbl, uint32 id, e_batrec_type type, e_batrec_agg agg) {
	nullpo_retr(-1, mbl);

	batrec_map* origin_rec = batrec_getmap(mbl, type);
	if (origin_rec == nullptr)
		return -1;

	batrec_map rec;
	batrec_aggregation(origin_rec, rec, agg);

	auto it = rec.find(batrec_key(id));
	if (it == rec.end())
		return -1;

	return it->second->damage;
}

void batrec_reset(struct block_list* mbl) {
	nullpo_retv(mbl);

	struct s_unit_common_data* ucd = status_get_ucd(mbl);
	if (ucd == nullptr)
		return;

	if (ucd->batrec.dmg_receive != nullptr) {
		ucd->batrec.dmg_receive->clear();
	}

	if (ucd->batrec.dmg_cause != nullptr) {
		ucd->batrec.dmg_cause->clear();
	}
}

void batrec_reset(struct block_list* mbl, e_batrec_type type) {
	nullpo_retv(mbl);

	batrec_map* rec = batrec_getmap(mbl, type);
	if (rec != nullptr)
		rec->clear();
}
