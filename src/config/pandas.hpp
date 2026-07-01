#pragma once

	#define Pandas_Basic
	#define Pandas_DatabaseIncrease
	#define Pandas_InternalConfigure
	#define Pandas_BattleConfigure
	#define Pandas_StructIncrease
	#define Pandas_FuncIncrease
	#define Pandas_PacketFunction
	#define Pandas_CreativeWork
	#define Pandas_Speedup
	#define Pandas_Crashfix
	#define Pandas_Mapflags
	#define Pandas_ScriptEngine
	#define Pandas_NpcEvent
	#define Pandas_AtCommands
	#define Pandas_ScriptCommands

// ============================================================================
// 基础组 - Pandas_Basic
// ============================================================================

#ifdef Pandas_Basic
	// 熊猫模拟器社区版版本号
	// 在 Windows 环境下版本号优先以资源文件中的文件版本号为准 (失败才会使用此处的版本号)
	// 在 Linux 环境下版本号将直接使用此处定义的版本号
	// 约定:
	// - 版本号的末尾若带有 -dev 后缀则表示这是一个还未 Release 的开发中版本
	// - 在 Windows 环境下资源文件中定义的版本号最后一段如果为 1, 也表示这是一个开发中的版本
	// 例如:
	//   1.0.1.0
	//         ^ 此处第四段为 0 表示这是一个 1.0.1 的正式版本 (Release)
	//   1.0.2.1
	//         ^ 此处第四段为 1 表示这是一个 1.0.2 的开发版本 (develop)
	// 在 Windows 环境下, 程序启动时会根据第四段的值自动携带对应的版本后缀, 以便进行版本区分
	#define Pandas_Version "1.2.5.1"

	// 在启动时显示 Pandas 的 LOGO
	#define Pandas_Show_Logo

	// 在启动时显示 Pandas 的版本号
	#define Pandas_Show_Version

	// 是否启用控制台信息翻译机制 [Sola丶小克]
	#define Pandas_Console_Translate

	// 是否启用 Google Breakpad 用于处理程序崩溃

	// 是否启用一些杂乱的自定义辅助函数
	#define Pandas_Helper_Common_Function

	// 是否启用代码分析工具所建议的处理措施以避免潜在风险
	// 包含的工具有: LGTM, CodeQL, Microsoft Code Analysis 等
	#define Pandas_CodeAnalysis_Suggestion
#endif // Pandas_Basic

// ============================================================================
// 数据结构增强组 - Pandas_StructIncrease
// ============================================================================

#ifdef Pandas_StructIncrease
	// 使 map_session_data, npc_data, mob_data, homun_data,
	// mercenary_data, elemental_data, pet_data 能够有一个独立的结构体用来
	// 存放 Pandas 针对多单位通用的拓展 [Sola丶小克]
	#define Pandas_Struct_Unit_CommonData

	#ifdef Pandas_Struct_Unit_CommonData
		// 使 s_unit_common_data 可记录单位的光环信息 [Sola丶小克]
		#define Pandas_Struct_Unit_CommonData_Aura

		// 使 s_unit_common_data 可记录战斗记录信息 [Sola丶小克]
		#define Pandas_Struct_Unit_CommonData_BattleRecord

		#ifdef Pandas_Struct_Unit_CommonData_BattleRecord
			// 启用战斗记录机制 [Sola丶小克]
			#define Pandas_BattleRecord
		#endif // Pandas_Struct_Unit_CommonData_BattleRecord
	#endif // Pandas_Struct_Unit_CommonData

	// 以下选项开关需要依赖 Pandas_Struct_Unit_CommonData 的拓展

	// 使 map_session_data 有一个独立的结构体用来存放 Pandas 的拓展 [Sola丶小克]
	// 结构体修改定位 pc.hpp -> map_session_data.pandas
	#define Pandas_Struct_Map_Session_Data_Pandas

	#ifdef Pandas_Struct_Map_Session_Data_Pandas
		// 使 map_session_data 可记录当前玩家正在处理哪一个脚本事件 [Sola丶小克]
		// 结构体修改定位 pc.hpp -> map_session_data.pandas.workinevent
		#define Pandas_Struct_Map_Session_Data_WorkInEvent

		// 使 map_session_data 可记录事件中断请求 [Sola丶小克]
		// 结构体修改定位 pc.hpp -> map_session_data.pandas.eventhalt
		#define Pandas_Struct_Map_Session_Data_EventHalt

		#ifdef Pandas_Struct_Map_Session_Data_EventHalt
			/************************************************************************/
			/* Filter 类型的过滤事件，这些事件可以被 processhalt 中断                    */
			/************************************************************************/

			// 当玩家在装备鉴定列表中选择好装备, 并点击“确定”按钮时触发过滤器 [Sola丶小克]
			// 事件类型: Filter / 事件名称: OnPCIdentifyFilter
			// 常量名称: NPCF_IDENTIFY / 变量名称: identify_filter_name
			#define Pandas_NpcFilter_IDENTIFY

			// 当玩家进入 NPC 开启的聊天室时触发过滤器 [Sola丶小克]
			// 事件类型: Filter / 事件名称: OnPCInChatroomFilter
			// 常量名称: NPCF_ENTERCHAT / 变量名称: enterchat_filter_name
			#define Pandas_NpcFilter_ENTERCHAT

			// 当玩家准备插入卡片时触发过滤器 [Sola丶小克]
			// 事件类型: Filter / 事件名称: OnPCInsertCardFilter
			// 常量名称: NPCF_INSERT_CARD / 变量名称: insert_card_filter_name
			#define Pandas_NpcFilter_INSERT_CARD

			// 当玩家准备使用非装备类道具时触发过滤器 [Sola丶小克]
			// 事件类型: Filter / 事件名称: OnPCUseItemFilter
			// 常量名称: NPCF_USE_ITEM / 变量名称: use_item_filter_name
			#define Pandas_NpcFilter_USE_ITEM

			// 当玩家准备使用技能时触发过滤器 [Sola丶小克]
			// 事件类型: Filter / 事件名称: OnPCUseSkillFilter
			// 常量名称: NPCF_USE_SKILL / 变量名称: use_skill_filter_name
			#define Pandas_NpcFilter_USE_SKILL

			// 当玩家准备打开乐透大转盘的时候触发过滤器 [Sola丶小克]
			// 事件类型: Filter / 事件名称: OnPCOpenRouletteFilter
			// 常量名称: NPCF_ROULETTE_OPEN / 变量名称: roulette_open_filter_name
			#define Pandas_NpcFilter_ROULETTE_OPEN

			// 当玩家准备查看某个角色的装备时触发过滤器 [Sola丶小克]
			// 事件类型: Filter / 事件名称: OnPCViewEquipFilter
			// 常量名称: NPCF_VIEW_EQUIP / 变量名称: view_equip_filter_name
			#define Pandas_NpcFilter_VIEW_EQUIP

			// 当玩家准备穿戴装备时触发过滤器 [Sola丶小克]
			// 事件类型: Filter / 事件名称: OnPCEquipFilter
			// 常量名称: NPCF_EQUIP / 变量名称: equip_filter_name
			#define Pandas_NpcFilter_EQUIP

			// 当玩家准备脱下装备时触发过滤器 [Sola丶小克]
			// 事件类型: Filter / 事件名称: OnPCUnequipFilter
			// 常量名称: NPCF_UNEQUIP / 变量名称: unequip_filter_name
			#define Pandas_NpcFilter_UNEQUIP

			// 当玩家准备获得一个状态(Buff)时触发过滤器 [Sola丶小克]
			// 事件类型: Filter / 事件名称: OnPCBuffStartFilter
			// 常量名称: NPCF_SC_START / 变量名称: sc_start_filter_name
			#define Pandas_NpcFilter_SC_START

			// 当玩家使用菜单中的原地复活之证时触发过滤器 [Sola丶小克]
			// 事件类型: Filter / 事件名称: OnPCUseReviveTokenFilter
			// 常量名称: NPCF_USE_REVIVE_TOKEN / 变量名称: use_revive_token_filter_name
			#define Pandas_NpcFilter_USE_REVIVE_TOKEN

			// 当玩家使用一键鉴定道具时触发过滤器 [Sola丶小克]
			// 事件类型: Filter / 事件名称: OnPCUseOCIdentifyFilter
			// 常量名称: NPCF_ONECLICK_IDENTIFY / 变量名称: oneclick_identify_filter_name
			#define Pandas_NpcFilter_ONECLICK_IDENTIFY

			// 当玩家准备创建公会时触发过滤器 [聽風]
			// 事件类型: Filter / 事件名称: OnPCGuildCreateFilter
			// 常量名称: NPCF_GUILDCREATE / 变量名称: guildcreate_filter_name
			#define Pandas_NpcFilter_GUILDCREATE

			// 当玩家即将加入公会时触发过滤器 [聽風]
			// 事件类型: Filter / 事件名称: OnPCGuildJoinFilter
			// 常量名称: NPCF_GUILDJOIN / 变量名称: guildjoin_filter_name
			#define Pandas_NpcFilter_GUILDJOIN

			// 当玩家准备离开公会时触发过滤器 [聽風]
			// 事件类型: Filter / 事件名称: OnPCGuildLeaveFilter
			// 常量名称: NPCF_GUILDLEAVE / 变量名称: guildleave_filter_name
			#define Pandas_NpcFilter_GUILDLEAVE

			// 当玩家准备创建队伍时触发过滤器 [聽風]
			// 事件类型: Filter / 事件名称: OnPCPartyCreateFilter
			// 常量名称: NPCF_PARTYCREATE / 变量名称: partycreate_filter_name
			#define Pandas_NpcFilter_PARTYCREATE

			// 当玩家即将加入队伍时触发过滤器 [聽風]
			// 事件类型: Filter / 事件名称: OnPCPartyJoinFilter
			// 常量名称: NPCF_PARTYJOIN / 变量名称: partyjoin_filter_name
			#define Pandas_NpcFilter_PARTYJOIN

			// 当玩家准备离开队伍时触发过滤器 [聽風]
			// 事件类型: Filter / 事件名称: OnPCPartyLeaveFilter
			// 常量名称: NPCF_PARTYLEAVE / 变量名称: partyleave_filter_name
			#define Pandas_NpcFilter_PARTYLEAVE

			// 当玩家准备丢弃或掉落道具时触发过滤器 [人鱼姬的思念]
			// 事件类型: Filter / 事件名称: OnPCDropItemFilter
			// 常量名称: NPCF_DROPITEM / 变量名称: dropitem_filter_name
			#define Pandas_NpcFilter_DROPITEM

			// 当玩家点击魔物墓碑时触发过滤器 [人鱼姬的思念]
			// 事件类型: Filter / 事件名称: OnPCClickTombFilter
			// 常量名称: NPCF_CLICKTOMB / 变量名称: clicktomb_filter_name
			#define Pandas_NpcFilter_CLICKTOMB

			// 当玩家准备将道具存入仓库时触发过滤器 [香草]
			// 事件类型: Filter / 事件名称: OnPCStorageAddFilter
			// 常量名称: NPCF_STORAGE_ADD / 变量名称: storage_add_filter_name
			#define Pandas_NpcFilter_STORAGE_ADD

			// 当玩家准备将道具取出仓库时触发过滤器 [香草]
			// 事件类型: Filter / 事件名称: OnPCStorageDelFilter
			// 常量名称: NPCF_STORAGE_DEL / 变量名称: storage_del_filter_name
			#define Pandas_NpcFilter_STORAGE_DEL

			// 当玩家准备将道具从背包存入手推车时触发过滤器 [香草]
			// 事件类型: Filter / 事件名称: OnPCCartAddFilter
			// 常量名称: NPCF_CART_ADD / 变量名称: cart_add_filter_name
			#define Pandas_NpcFilter_CART_ADD

			// 当玩家准备将道具从手推车取回背包时触发过滤器 [香草]
			// 事件类型: Filter / 事件名称: OnPCCartDelFilter
			// 常量名称: NPCF_CART_DEL / 变量名称: cart_del_filter_name
			#define Pandas_NpcFilter_CART_DEL

			// 当玩家准备将道具移入收藏栏位时触发过滤器 [香草]
			// 事件类型: Filter / 事件名称: OnPCFavoriteAddFilter
			// 常量名称: NPCF_FAVORITE_ADD / 变量名称: favorite_add_filter_name
			#define Pandas_NpcFilter_FAVORITE_ADD

			// 当玩家准备将道具从收藏栏位移出时触发过滤器 [香草]
			// 事件类型: Filter / 事件名称: OnPCFavoriteDelFilter
			// 常量名称: NPCF_FAVORITE_DEL / 变量名称: favorite_del_filter_name
			#define Pandas_NpcFilter_FAVORITE_DEL

		#ifdef Pandas_Character_Title_Controller
			// 当玩家试图变更称号时将触发过滤器 [Sola丶小克]
			// 事件类型: Filter / 事件名称: OnPCChangeTitleFilter
			// 常量名称: NPCF_CHANGETITLE / 变量名称: changetitle_filter_name
			#define Pandas_NpcFilter_CHANGETITLE
		#endif // Pandas_Character_Title_Controller

			// PYHELP - NPCEVENT - INSERT POINT - <Section 1>
		#endif // Pandas_Struct_Map_Session_Data_EventHalt

		// 使 map_session_data 可记录事件触发请求 [Sola丶小克]
		// 结构体修改定位 pc.hpp -> map_session_data.pandas.eventtrigger
		#define Pandas_Struct_Map_Session_Data_EventTrigger

		// 使 map_session_data 可记录当前是否正在进行护身符能力计算 [Sola丶小克]
		// 结构体修改定位 pc.hpp -> map_session_data.pandas.amulet_calculating
		#define Pandas_Struct_Map_Session_Data_AmuletCalculating

		// 使 map_session_data 可记录即将支持捕捉的多个魔物编号 [Sola丶小克]
		#define Pandas_Struct_Map_Session_Data_MultiCatchTargetClass

		// 使 map_session_data 可记录接下来的 pc_setpos 调用是不是一次多人传送 [Sola丶小克]
		// 结构体修改定位 pc.hpp -> map_session_data.pandas.multitransfer
		#define Pandas_Struct_Map_Session_Data_MultiTransfer

		// 使 map_session_data 可记录是否在 LoadEndAck 调用中不弹出队列中的事件 [Sola丶小克]
		// 结构体修改定位 pc.hpp -> map_session_data.pandas.skip_loadendack_npc_event_dequeue
		#define Pandas_Struct_Map_Session_Data_Skip_LoadEndAck_NPC_Event_Dequeue

		// 使 map_session_data 可记录离线挂店 / 挂机角色的朝向等状态数据 [Sola丶小克]
		// rAthena 使用完成 autotrade 的朝向数据后就销毁掉了
		// 为了能够支持离线挂店 / 挂机可以被 recall 召唤, 我们需要保留一部分数据
		#define Pandas_Struct_Map_Session_Data_Autotrade_Configure

		// 使 state.autotrade 支持更多离线交易/挂起状态位 [Sola丶小克]
		#define Pandas_Struct_Autotrade_Extend

		// 以下选项开关需要依赖 Pandas_Struct_Autotrade_Extend 的拓展
		#ifdef Pandas_Struct_Autotrade_Extend
			// 启用玩家挂起系统, 支持离线挂机、离开模式和普通召回 [Sola丶小克]
			#define Pandas_Player_Suspend_System
		#endif // Pandas_Struct_Autotrade_Extend

		// 使 map_session_data 可记录玩家已经生成的 bonus_script 记录数 [Sola丶小克]
		// 结构体修改定位 pc.hpp -> map_session_data.pandas.bonus_script_counter
		#define Pandas_Struct_Map_Session_Data_BonusScript_Counter
	#endif // Pandas_Struct_Map_Session_Data_Pandas

	// 对 bonus_script_data 的定义进行拓展处理 [Sola丶小克]
	// 默认的 rAthena 中 bonus_script 机制并没有唯一编号的概念, 为了提高对 bonus_script 的控制粒度
	// 我们需要将唯一编号引入到需要拓展的相关数据结构体中
	#define Pandas_Struct_BonusScriptData_Extend

	// 以下选项开关需要依赖 Pandas_Struct_Map_Session_Data_Pandas 的拓展

	// 使 item_data 有一个独立的结构体用来存放 Pandas 的拓展 [Sola丶小克]
	// 结构体修改定位 itemdb.hpp -> item_data.pandas
	#define Pandas_Struct_Item_Data_Pandas

	// 以下选项开关需要依赖 Pandas_Struct_Item_Data_Pandas 的拓展
	#ifdef Pandas_Struct_Item_Data_Pandas
		// 使 item_data 可记录当前物品的使用、穿戴、卸装脚本的原文 [Sola丶小克]
		// 结构体修改定位 itemdb.hpp -> item_data.pandas.script_plaintext
		#define Pandas_Struct_Item_Data_Script_Plaintext
		#ifdef Pandas_Struct_Item_Data_Script_Plaintext
			#define Pandas_Persistence_Itemdb_Script
		#endif // Pandas_Struct_Item_Data_Script_Plaintext

		// 使 item_data 可记录当前物品可捕捉的魔物编号 [Sola丶小克]
		// 结构体修改定位 itemdb.hpp -> item_data.pandas.taming_mobid
		#define Pandas_Struct_Item_Data_Taming_Mobid
		#ifdef Pandas_Struct_Item_Data_Taming_Mobid
			#define Pandas_MapFlag_NoCapture
		#endif // Pandas_Struct_Item_Data_Taming_Mobid

		// 使 item_data 可记录此物品的使用脚本是否执行了 callfunc 指令 [Sola丶小克]
		// 结构体修改定位 itemdb.hpp -> item_data.pandas.has_callfunc
		#define Pandas_Struct_Item_Data_Has_CallFunc

		// 使 item_data 可记录此物品的特殊属性 [Sola丶小克]
		// 效果与 item_data.flag 类似, 只是数据源为 item_properties.yml
		// 结构体修改定位 itemdb.hpp -> item_data.pandas.properties
		#define Pandas_Struct_Item_Data_Properties
	#endif // Pandas_Struct_Item_Data_Pandas

	// 使 npc_data 有一个独立的结构体用来存放 Pandas 的拓展 [Sola丶小克]
	// 结构体修改定位 npc.hpp -> npc_data.pandas
	#define Pandas_Struct_Npc_Data_Pandas

	// 以下选项开关需要依赖 Pandas_Struct_Npc_Data_Pandas 的拓展
	#ifdef Pandas_Struct_Npc_Data_Pandas
		// 使 npc_data 结构体可记录此 NPC 的自毁策略 [Sola丶小克]
		// 结构体修改定位 npc.hpp -> npc_data.pandas.destruction_strategy
		#define Pandas_Struct_Npc_Data_DestructionStrategy
	#endif // Pandas_Struct_Npc_Data_Pandas

	// 使 mob_data 有一个独立的结构体用来存放 Pandas 的拓展 [Sola丶小克]
	// 结构体修改定位 mob.hpp -> mob_data.pandas
	#define Pandas_Struct_Mob_Data_Pandas

	// 以下选项开关需要依赖 Pandas_Struct_Mob_Data_Pandas 的拓展
	#ifdef Pandas_Struct_Mob_Data_Pandas
		// 使 mob_data 结构体可记录此魔物被 setunitdata 修改过哪些项目 [Sola丶小克]
		// 结构体修改定位 mob.hpp -> mob_data.pandas.special_setunitdata
		#define Pandas_Struct_Mob_Data_Special_SetUnitData

		#ifdef Pandas_Struct_Mob_Data_Special_SetUnitData
			// 使 setunitdata 对魔物状态数据的修改能够在状态重算后持久化 [Sola丶小克]
			#define Pandas_Persistent_SetUnitData_For_Monster_StatusData
		#endif // Pandas_Struct_Mob_Data_Special_SetUnitData

		// 使 mob_data 结构体可记录此魔物特殊的基础经验或职业经验 [Sola丶小克]
		// 结构体修改定位 mob.hpp -> mob_data.pandas.base_exp 和 job_exp
		#define Pandas_Struct_Mob_Data_SpecialExperience

		#ifdef Pandas_Struct_Mob_Data_SpecialExperience
			// 是否拓展 setunitdata / getunitdata 指令的参数
			// 使之能设置或者读取指定魔物实例的经验值 (BASEEXP / JOBEXP) [人鱼姬的思念]
			#define Pandas_ScriptParams_UnitData_Experience
		#endif // Pandas_Struct_Mob_Data_SpecialExperience
	#endif // Pandas_Struct_Mob_Data_Pandas

	// 对离线挂店 autotrade 的定义进行拓展处理 [Sola丶小克]
	// 进行拓展处理之后能够在代码改动较少的情况下, 更好的支持多种不同类型的 "离线挂店" 行为
	// 在默认情况下 sd->state.autotrade 的值若为 0 则表示没有离线挂店
	// 若非零的话则表示启用了离线挂店, 且 &2 表示开启的是离线摆摊挂店 &3 表示开启的是离线收购挂店

	// 对 bonus_script_data 的定义进行拓展处理 [Sola丶小克]
	// 默认的 rAthena 中 bonus_script 机制并没有唯一编号的概念, 为了提高对 bonus_script 的控制粒度
	// 我们需要将唯一编号引入到我们需要拓展的相关数据结构体中

	// 使 s_mail.item 能有一个 details 字段用来记录附件道具更详细的信息 [Sola丶小克]
	#define Pandas_Struct_S_Mail_With_Details

	#ifdef Pandas_Struct_S_Mail_With_Details
		// 修复邮件附件在发送前未复核物品状态导致的异常 [Sola丶小克]
		#define Pandas_Fix_Mail_ItemAttachment_Check
	#endif // Pandas_Struct_S_Mail_With_Details

	// 使 s_random_opt_data 能保存脚本的明文 [Sola丶小克]
	#define Pandas_Struct_S_Random_Opt_Data_With_Plaintext

	// 使 s_item_combo 能保存脚本的明文 [Sola丶小克]
	#define Pandas_Struct_S_Item_Combo_With_Plaintext

	// 使 status_change 能保存 cloak 是否正在进行中的状态 [Sola丶小克]
	#define Pandas_Struct_Status_Change_Cloak_Reverting

	#ifdef Pandas_Struct_Status_Change_Cloak_Reverting
		// 修复 NPC cloak 翻转过程中的可见状态混淆 [Sola丶小克]
		#define Pandas_Fix_Cloak_Status_Baffling
	#endif // Pandas_Struct_Status_Change_Cloak_Reverting

	// 使 map_data 能保存全部魔物的刷新点信息 [Sola丶小克]
	#define Pandas_Struct_Map_Data_Mob_Spawns
#endif // Pandas_StructIncrease

// ============================================================================
// 数据库增强组 - Pandas_DatabaseIncrease
// ============================================================================

#ifdef Pandas_DatabaseIncrease
	// 是否启用道具特殊属性数据库 [Sola丶小克]
	// 为了避免未来可能存在的冲突, 直接创建一个新的数据库来存放对物品属性的自定义扩充
	// 此选项依赖 Pandas_Struct_Item_Data_Properties 的拓展
	#ifdef Pandas_Struct_Item_Data_Properties
		#define Pandas_Database_ItemProperties
	#endif // Pandas_Struct_Item_Data_Properties

	// 是否启用魔物道具固定掉率数据库及其功能 [Sola丶小克]
	// 通过这个数据库可以指定某个道具的全局固定掉落概率, 且能绕过等级惩罚和VIP掉率加成等机制
	#define Pandas_Database_MobItem_FixedRatio

	// 是否拓展 Yaml 的 Database 操作类使之能抑制错误信息 [Sola丶小克]
	#define Pandas_Database_Yaml_BeQuiet

	// 是否支持用于读取 SQL 连接编码的 Sql_GetEncoding 函数 [Sola丶小克]
	#define Pandas_Database_SQL_GetEncoding
#endif // Pandas_DatabaseIncrease

// ============================================================================
// 服务器通用配置组 - Pandas_InternalConfigure
// ============================================================================

#ifdef Pandas_InternalConfigure
	// 是否启用 hide_server_ipaddress 配置选项及其功能 [Sola丶小克]
	// 此选项用于确保服务端不主动返回服务器的 IP 地址给到客户端, 通常用于支持代理方式登录
	#define Pandas_InterConfig_HideServerIpAddress
#endif // Pandas_InternalConfigure

// ============================================================================
// 战斗配置组 - Pandas_BattleConfigure
// ============================================================================

#ifdef Pandas_BattleConfigure
	// 是否支持对战斗配置选项进行完整性检查 [╰づ记忆•斑驳〤 实现] [Sola丶小克 改进]
	#define Pandas_BattleConfig_Verification

	// 是否启用 force_loadevent 配置选项及其功能 [Sola丶小克]
	// 此选项可以强制没有 loadevent 标记的地图也能触发 OnPCLoadMapEvent 事件
	#define Pandas_BattleConfig_Force_LoadEvent

	// 是否启用 force_identified 配置选项及其功能 [Sola丶小克]
	// 此选项用于指定哪些渠道获得的装备会被自动设置为已鉴定
	#define Pandas_BattleConfig_Force_Identified

	// 是否启用 cashmount_useitem_limit 配置选项及其功能 [Sola丶小克]
	// 此选项可以使乘坐“商城坐骑”时禁止使用特定类型的物品
	#define Pandas_BattleConfig_CashMounting_UseitemLimit

	// 是否启用 max_aspd_for_pvp 配置选项及其功能 [Sola丶小克]
	// 此选项用于限制玩家在 PVP 地图上的最大攻速
	#define Pandas_BattleConfig_MaxAspdForPVP

	// 是否启用 max_aspd_for_gvg 配置选项及其功能 [Sola丶小克]
	// 此选项用于限制玩家在 GVG 地图上的最大攻速
	#define Pandas_BattleConfig_MaxAspdForGVG

	// 是否启用 atcmd_no_permission 配置选项及其功能 [Sola丶小克]
	// 此选项用于控制普通玩家无权执行 GM 指令时的处理策略
	#define Pandas_BattleConfig_AtCmd_No_Permission

	// 是否启用 multiplayer_recall_behavior 配置选项及其功能 [Sola丶小克]
	// 此选项用于控制多人召回时是否避开在线摆摊或采购的玩家
	#define Pandas_BattleConfig_Multiplayer_Recall_Behavior

	// 是否启用 always_trigger_npc_killevent 配置选项及其功能 [Sola丶小克]
	// 此选项用于控制魔物触发自己的死亡事件后是否继续触发 OnNPCKillEvent
	#define Pandas_BattleConfig_AlwaysTriggerNPCKillEvent

	// 是否启用 always_trigger_mvp_killevent 配置选项及其功能 [Sola丶小克]
	// 此选项用于控制 MVP 魔物触发自己的死亡事件后是否继续触发 OnPCKillMvpEvent
	#define Pandas_BattleConfig_AlwaysTriggerMVPKillEvent

// 是否启用 suspend_monsterignore 配置选项及其功能 [Sola丶小克]
// 此选项用于指定当玩家使用挂机系列指令时, 哪些模式不会被魔物攻击 (掩码选项)
#define Pandas_BattleConfig_Suspend_MonsterIgnore

// 是否启用 suspend_whisper_response 配置选项及其功能 [Sola丶小克]
// 此选项用于指定当玩家使用挂机系列指令时, 哪些模式会自动回复私聊讯息 (掩码选项)
#define Pandas_BattleConfig_Suspend_Whisper_Response

// 是否启用 suspend_offline_bodydirection 配置选项及其功能 [Sola丶小克]
// 此选项用于指定玩家进入离线挂机模式时, 地图服务器重启后的身体朝向哪里
#define Pandas_BattleConfig_Suspend_Offline_BodyDirection

// 是否启用 suspend_offline_headdirection 配置选项及其功能 [Sola丶小克]
// 此选项用于指定玩家进入离线挂机模式时, 地图服务器重启后的头部朝向哪里
#define Pandas_BattleConfig_Suspend_Offline_HeadDirection

// 是否启用 suspend_offline_sitdown 配置选项及其功能 [Sola丶小克]
// 此选项用于指定玩家进入离线挂机模式时, 地图服务器重启后处于站立还是坐下状态
#define Pandas_BattleConfig_Suspend_Offline_Sitdown

// 是否启用 suspend_afk_bodydirection 配置选项及其功能 [Sola丶小克]
// 此选项用于指定玩家进入离开模式时, 地图服务器重启后的身体朝向哪里
#define Pandas_BattleConfig_Suspend_AFK_BodyDirection

// 是否启用 suspend_afk_headdirection 配置选项及其功能 [Sola丶小克]
// 此选项用于指定玩家进入离开模式时, 地图服务器重启后的头部朝向哪里
#define Pandas_BattleConfig_Suspend_AFK_Headdirection

// 是否启用 suspend_afk_sitdown 配置选项及其功能 [Sola丶小克]
// 此选项用于指定玩家进入离开模式时, 地图服务器重启后处于站立还是坐下状态
#define Pandas_BattleConfig_Suspend_AFK_Sitdown

// 是否启用 suspend_afk_headtop_viewid 配置选项及其功能 [Sola丶小克]
// 此选项用于指定玩家进入离开模式时, 将头饰上的更换为哪一个指定的头饰外观编号
#define Pandas_BattleConfig_Suspend_AFK_HeadTop_ViewID

// 是否启用 suspend_normal_bodydirection 配置选项及其功能 [Sola丶小克]
// 此选项用于指定玩家进入普通模式时, 被拉上线的角色身体朝向哪里
#define Pandas_BattleConfig_Suspend_Normal_BodyDirection

// 是否启用 suspend_normal_headdirection 配置选项及其功能 [Sola丶小克]
// 此选项用于指定玩家进入普通模式时, 被拉上线的角色头部朝向哪里
#define Pandas_BattleConfig_Suspend_Normal_HeadDirection

// 是否启用 suspend_normal_sitdown 配置选项及其功能 [Sola丶小克]
// 此选项用于指定玩家进入普通模式时, 被拉上线的角色处于站立还是坐下状态
#define Pandas_BattleConfig_Suspend_Normal_Sitdown

// 是否启用 batrec_autoenabled_unit 配置选项及其功能 [Sola丶小克]
// 此选项用于指定哪些单位默认开启战斗记录
#define Pandas_BattleConfig_BattleRecord_AutoEnabled_Unit

// 是否启用 repeat_clearunit_interval 配置选项及其功能 [Sola丶小克]
// 此选项用于设置重发魔物死亡封包的间隔时间 (单位为: 毫秒)
#define Pandas_BattleConfig_Repeat_ClearUnit_Interval

// 是否启用 dead_area_size 配置选项及其功能 [Sola丶小克]
// 此选项用于设置魔物死亡封包将会发送给周围多少个格的玩家
#define Pandas_BattleConfig_Dead_Area_Size

// 是否启用 remove_manhole_with_status 配置选项及其功能 [Sola丶小克]
// 此选项用于设置人孔陷阱被移除时是否同时使被捕获的玩家脱困
#define Pandas_BattleConfig_Remove_Manhole_With_Status

// 是否启用 restore_mes_logic 配置选项及其功能 [Sola丶小克]
// 此选项用于使 2021-11-03 及更新版本的客户端在执行 mes 指令时使用经典换行策略
#define Pandas_BattleConfig_Restore_Mes_Logic

// 是否启用 itemdb_warning_policy 配置选项及其功能 [Sola丶小克]
// 此选项用于关闭加载物品数据库时的一些警告信息
#define Pandas_BattleConfig_ItemDB_Warning_Policy

// 是否启用 mob_default_damagemotion 配置选项及其功能 [Sola丶小克]
// 此选项用于设置魔物被攻击时受伤动画的默认播放时长
#define Pandas_BattleConfig_MobDB_DamageMotion_Min

// 是否启用 strict_parameters_of_rand 配置选项及其功能 [Sola丶小克]
// 此选项用于对 rand 脚本指令进行严格的参数检查
#define Pandas_BattleConfig_Strict_Parameters_Of_Rand

// 是否启用 mob_setunitdata_persistence 配置选项及其功能 [Sola丶小克]
// 此选项用于高优先级持久化保存 setunitdata 对魔物的设置
#define Pandas_BattleConfig_Mob_SetUnitData_Persistence

	// PYHELP - BATTLECONFIG - INSERT POINT - <Section 1>
#endif // Pandas_BattleConfigure

// ============================================================================
// 函数修改组 - Pandas_FuncIncrease
// ============================================================================

#ifdef Pandas_FuncIncrease
	// 在 pc.cpp 中的 pc_equipitem 增加 swapping 参数 [Sola丶小克]
	// 新增的 swapping 用于判断当前的装备穿戴调用是否由装备切换机制引发, 默认为 false
	#define Pandas_FuncParams_PC_EQUIPITEM

	// 调整 pc.cpp 中 pc_equipitem 执行道具绑定的时机 [Sola丶小克]
	#define Pandas_FuncLogic_PC_EQUIPITEM_BOUND_OPPORTUNITY

	// 调整 storage.cpp 中 storage_additem 的函数定义, 移除 static 关键字 [Sola丶小克]
	#define Pandas_FuncDefine_STORAGE_ADDITEM

	// 调整 instance.cpp 中 instance_destroy 的定义
	// 增加 skip_erase 参数用于控制成功销毁副本后不 erase 掉 instance 对象
	// 以便交由外部来进行 erase, 这样才能获取下一个指针的正确位置 (C++11) [Sola丶小克]
	#define Pandas_FuncDefine_Instance_Destory
	// 修正在 C++11 标准下使用不正确的 unordered_map::erase 方法会导致地图服务器崩溃的问题
	// 此选项开关需要依赖 Pandas_FuncDefine_Instance_Destory 的拓展 [Sola丶小克]
	#ifdef Pandas_FuncDefine_Instance_Destory
		#define Pandas_Crashfix_UnorderedMap_Erase
	#endif // Pandas_FuncDefine_Instance_Destory

	// 调整各单位的死亡处理函数, 以便支持更多参数信息 [Sola丶小克]
	// 玩家单位	: pc.cpp -> pc_dead
	// 魔物单位	: mob.cpp -> mob_dead
	// 生命体单位	: homunculus.cpp -> hom_dead
	// 佣兵单位	: mercenary.cpp -> mercenary_dead
	// 元素精灵	: elemental.cpp -> elemental_dead
	#define Pandas_FuncDefine_UnitDead_With_ExtendInfo

	// 调整用于计算 MAX_INVENTORY 相关的变量
	// 以便能够支持将背包的最大上限设置成超过 128 的值 [Sola丶小克]
	// 提示: 根据目前的 struct item 和 struct s_storage 的体积情况,
	// 应该可支持将 MAX_INVENTORY 调整到 800 左右, 但设置越大对性能影响会越大
	#define Pandas_FuncExtend_Increase_Inventory

	// 调整 atcommand.cpp 中 atcommand_reload 配置重载指令的逻辑 [Sola丶小克]
	// 我们希望在执行某些 reload 指令 (@reloadbattleconf) 时能重新计算全服玩家的属性和能力值
	#define Pandas_FuncLogic_ATCOMMAND_RELOAD

	// 重写 instance.cpp -> instance_destroy_command 函数
	// 因为 rAthena 官方实现的该函数在切换队长后的处理并不友好 [Sola丶小克]
	#define Pandas_FuncLogic_Instance_Destroy_Command
	// 修正更换队长后, 新队长无法看到销毁副本按钮的问题
	// 此选项开关需要依赖 Pandas_FuncLogic_Instance_Destroy_Command 的拓展 [Sola丶小克]
	#ifdef Pandas_FuncLogic_Instance_Destroy_Command
		#define Pandas_Fix_Dungeon_Command_Status_Refresh
	#endif // Pandas_FuncLogic_Instance_Destroy_Command

	// 当某个 IP 地址被判定为可以连接的时候, 不再将其列入 DDoS 攻击的判定范围 [Sola丶小克]
	// 在默认 rAthena 的逻辑下, 就算某个 IP 地址就算被判定成允许连接,
	// 只要他连接频度过高也依然会在终端呈现出: 发现来自 %d.%d.%d.%d 的 DDoS 攻击!
	// 虽然有提示, 但是根据白名单规则却又进行了放行操作.. 因此这个提示是很没意义的.
	// 启用此选项将改变判断逻辑, 变成如下:
	// 只要 IP 地址被判定为无条件放行, 那么他将不会因为高频连接而被判定为发起了 DDoS 攻击.
	#define Pandas_FuncLogic_Whitelist_Privileges

	// 调整 clif.cpp 中给 clif_item_equip 函数增加 caller 参数 [Sola丶小克]
	// 新增的 caller 参数用来标记调用这个函数的调用者是谁, 以便在必要情况下能够调整返回给客户端的字段值
	#define Pandas_FuncParams_Clif_Item_Equip

	// 在 mob.cpp 中的 mob_once_spawn_sub 增加 spawn_flag 参数 [Sola丶小克]
	// 新增的 spawn_flag 参数可以用来控制召唤出来的魔物是不是 BOSS (可以被 BOSS 雷达探测)
	#define Pandas_FuncDefine_Mob_Once_Spawn_Sub

	// 在 mob.cpp 中的 mob_once_spawn 增加 spawn_flag 参数 [Sola丶小克]
	// 新增的 spawn_flag 参数可以用来控制召唤出来的魔物是不是 BOSS (可以被 BOSS 雷达探测)
	// 此选项依赖 Pandas_FuncDefine_Mob_Once_Spawn_Sub 的拓展
	#ifdef Pandas_FuncDefine_Mob_Once_Spawn_Sub
		#define Pandas_FuncDefine_Mob_Once_Spawn
	#endif // Pandas_FuncDefine_Mob_Once_Spawn_Sub

	// 在 map.cpp 中的 map_getmob_boss 增加 alive_first 参数 [Sola丶小克]
	// 新增的 alive_first 参数可以指定优先返回存活着的 BOSS 魔物
	#define Pandas_FuncDefine_Mob_Getmob_Boss

	// 在 mob.cpp 中的 mvptomb_create 增加 killer_gid 参数 [Sola丶小克]
	// 新增的 killer_gid 参数用于传递杀死 MVP 玩家的游戏单位编号
	#define Pandas_FuncParams_Mob_MvpTomb_Create
#endif // Pandas_FuncIncrease

// ============================================================================
// 封包修改组 - Pandas_PacketFunction
// ============================================================================

#ifdef Pandas_PacketFunction
	// 没有什么需要修改
#endif // Pandas_PacketFunction

// ============================================================================
// 原创功能组 - Pandas_CreativeWork
// ============================================================================

#ifdef Pandas_CreativeWork
	// 扩展信息配置文件 (Msg_conf) 的 ID 最大上限,
	// 同时提供 msg_txt_cn 宏定义函数, 方便在工程中使用自定义信息 [Sola丶小克]
	#define Pandas_Message_Conf

	// 对消息文件进行清理, 移除几乎用不到的其他国家语言
	// 同时也暂时移除掉 langtype 管理员指令, 这个指令目前不太合适熊猫模拟器
	// 主要留下: 英文, 简体中文, 繁体中文 这三种. [Sola丶小克]
	#define Pandas_Message_Reorganize

	// 将部分硬编码的字符串提取到消息文件中 [Sola丶小克]
	// 这么做的主要目的是在有需要的时候, 可以将内容进行汉化或者其他处理
	#define Pandas_Message_Hardcode_Extract

	// 是否支持在 map_athena.conf 中设定封包混淆密钥 [Sola丶小克]
	#ifdef PACKET_OBFUSCATION
		#define Pandas_Support_Specify_PacketKeys
	#endif // PACKET_OBFUSCATION

	// 是否支持读取 UTF8-BOM 编码的配置或者数据文件 [Sola丶小克]
	#define Pandas_Support_UTF8BOM_Files

	// 在使用 _M/_F 注册的时候, 能够限制使用中文等字符作为游戏账号 [Sola丶小克]
	// 这里的 PCRE_SUPPORT 在"项目属性 -> C/C++ -> 预处理器"中定义
	#ifdef PCRE_SUPPORT
		#define Pandas_Strict_Userid_Verification
	#endif // PCRE_SUPPORT

	// 是否支持隐藏角色服务器的在线人数 [Sola丶小克]
	#define Pandas_Support_Hide_Online_Players_Count

	// 是否扩展魔物名称能展现的信息, 比如体型、种族、属性 [Sola丶小克 改进]
	#define Pandas_MobInfomation_Extend

	// 是否加强 2013-12-23 以及 2013-08-07 客户端的混淆密钥 [Sola丶小克]
	#define Pandas_Packet_Obfuscation_Keys

	// 使影子装备可以支持插卡, 而不会被强制转换成普通道具 [Sola丶小克]
	#define Pandas_Shadowgear_Support_Card

	// 使 pointshop 类型的商店能支持指定变量别名, 用于展现给玩家 [Sola丶小克]
	#define Pandas_Support_Pointshop_Variable_DisplayName

	// 使墓碑中的魔物名称能尊重 override_mob_names 战斗配置选项的设置 [Sola丶小克]
	#define Pandas_Make_Tomb_Mobname_Follow_Override_Mob_Names

	// 检测 import 目录是否存在, 若不存在能够从 import-tmpl 复制一份 [Sola丶小克]
	#define Pandas_Deploy_Import_Directories

	// 是否对数据库配置相关的一系列逻辑进行优化 [Sola丶小克]
	#define Pandas_SQL_Configure_Optimization

	// 是否启用一列用于控制角色称号的指令、事件等等 [Sola丶小克]
	#define Pandas_Character_Title_Controller

	#ifdef Pandas_Character_Title_Controller
		// 是否启用 title 管理员指令 [Sola丶小克]
		// 给角色设置一个指定的称号ID, 客户端封包版本大于等于 20150513 才可用
	#endif // Pandas_Character_Title_Controller

	#ifndef _WIN32
		// 在 Linux 环境下输出信息时, 能转换成终端自适应编码 [Sola丶小克]
		#define Pandas_Console_Charset_SmartConvert
	#endif // _WIN32

	// 建立 MySQL 连接的时候主动禁止 SSL 模式 [Sola丶小克]
	#ifdef _WIN32
		#define Pandas_MySQL_SSL_Mode_Disabled
	#endif // _WIN32

	// 使公会的初始化人数以及“扩充组合体制”(GD_EXTENSION)每级增加人数可被宏定义 [Sola丶小克]
	#define Pandas_Guild_Extension_Configure

	// 是否支持使用 @recall 等指令单独召唤离线挂店 / 离线挂机的角色
	// 主要用于管理员调整挂机单位的站位, 避免阻挡到其他的 NPC 或者传送点等 [Sola丶小克]
	// 此选项依赖以下拓展, 任意一个不成立则将会 undef 此选项的定义
	// - Pandas_Struct_Map_Session_Data_MultiTransfer
	// - Pandas_Struct_Map_Session_Data_Autotrade_Configure
	// - Pandas_Struct_Map_Session_Data_Skip_LoadEndAck_NPC_Event_Dequeue
	// - Pandas_Player_Suspend_System
	#define Pandas_Support_Transfer_Autotrade_Player

	#ifndef Pandas_Struct_Map_Session_Data_MultiTransfer
		#undef Pandas_Support_Transfer_Autotrade_Player
	#endif // Pandas_Struct_Map_Session_Data_MultiTransfer
	#ifndef Pandas_Struct_Map_Session_Data_Autotrade_Configure
		#undef Pandas_Support_Transfer_Autotrade_Player
	#endif // Pandas_Struct_Map_Session_Data_Autotrade_Configure
	#ifndef Pandas_Struct_Map_Session_Data_Skip_LoadEndAck_NPC_Event_Dequeue
		#undef Pandas_Support_Transfer_Autotrade_Player
	#endif // Pandas_Struct_Map_Session_Data_Skip_LoadEndAck_NPC_Event_Dequeue
	#ifndef Pandas_Player_Suspend_System
		#undef Pandas_Support_Transfer_Autotrade_Player
	#endif // Pandas_Player_Suspend_System

	// 是否支持根据系统语言读取对应的消息数据库文件 [Sola丶小克]
	// 此选项依赖 Pandas_Support_UTF8BOM_Files 的拓展
	#ifdef Pandas_Support_UTF8BOM_Files
		#define Pandas_Adaptive_Importing_Message_Database
	#endif // Pandas_Support_UTF8BOM_Files

	// 是否支持处理 Windows 10 编码选项带来的中文乱码问题 [Sola丶小克]
	#ifdef _WIN32
		#define Pandas_Setup_Console_Output_Codepage
	#endif // _WIN32

	// 实验性读取 SSO 登录封包传递的 MAC 地址和客户端内网 IP 地址信息 [Sola丶小克]
	#define Pandas_Extract_SSOPacket_MacAddress

	// 是否启用角色光环机制 [Sola丶小克]
	// 此选项依赖 Pandas_Struct_Unit_CommonData_Aura 的拓展
	#define Pandas_Aura_Mechanism

	#ifndef Pandas_Struct_Unit_CommonData_Aura
		#undef Pandas_Aura_Mechanism
	#endif // Pandas_Struct_Unit_CommonData_Aura

	// 优化对极端计算的支持 (AKA: 变态服拓展包) [Sola丶小克]
	#define Pandas_Extreme_Computing

	// 是否启用 bonus_script 的唯一编号机制 [Sola丶小克]
	// 此选项依赖 Pandas_Struct_BonusScriptData_Extend 与 Pandas_Struct_Map_Session_Data_BonusScript_Counter
	#define Pandas_BonusScript_Unique_ID

	#ifndef Pandas_Struct_BonusScriptData_Extend
		#undef Pandas_BonusScript_Unique_ID
	#endif // Pandas_Struct_BonusScriptData_Extend
	#ifndef Pandas_Struct_Map_Session_Data_BonusScript_Counter
		#undef Pandas_BonusScript_Unique_ID
	#endif // Pandas_Struct_Map_Session_Data_BonusScript_Counter

	// 是否启用对负载均衡的友好处理支持 [Sola丶小克]
	#define Pandas_Health_Monitors_Silent

	// 解锁仓库以及背包的最大容量限制 [Sola丶小克]
	#define Pandas_Unlock_Storage_Capacity_Limit

	// 是否扩展 e_job_types 枚举类型的可选值 [Sola丶小克]
	#define Pandas_Update_NPC_Identity_Information

	// 是否支持 future 封装以便执行异步任务 [Sola丶小克]
	#define Pandas_Support_Future_Execution

	// PYHELP - CREATIVEWORK - INSERT POINT - <Section 1>
#endif // Pandas_CreativeWork

#ifndef Pandas_Support_Transfer_Autotrade_Player
	#undef Pandas_BattleConfig_Multiplayer_Recall_Behavior
#endif // Pandas_Support_Transfer_Autotrade_Player

// ============================================================================
// 官方崩溃修正组 - Pandas_Crashfix
// ============================================================================

#ifdef Pandas_Crashfix
	// 对部分比较关键的变量初始化时进行置空处理 [Sola丶小克]
	// 特别针对那些单纯依赖目标是否为 Null 作为野指针判断的相关变量

	// 是否在 Release 模式下也启用 nullpo_ret 等系列指令 [Sola丶小克]
	// 在 rAthena 的设计中, nullpo_ret 等指令仅在 Debug 模式会拦截空指针的情况并记录下位置信息
	// 为了健壮性考虑, 熊猫模拟器会试图在 Release 模式下也使这些指令可以拦截空指针的情况
	// 因为有些空指针时在运行时产生的, 日常测试非常难以覆盖到这些异常情况
	// 若未来在生产环境执行过程中也碰到了空指针错误, 可考虑尝试上报到服务端进行统计分析

	// 对函数的参数进行合法性校验 [Sola丶小克]

	// 对潜在的空指针调用崩溃情况进行校验和判断 [Sola丶小克]

	// 对除数可能为零的情况进行一些规避处理 [Sola丶小克]

	// 修复使用 getd 操作的变量名存在空格开头时,
	// 若 getd 的结果直接作为参数传入其他脚本指令, 会导致地图服务器崩溃的问题 [Sola丶小克]
	// 重现方法:
	// 使 NPC 调用 .@result = inarray(getd(" $test"), 100); 即可触发崩溃

	// 修正 Visual Studio 2019 的 16.3 在支持 AVX512 指令集的设备上
	// 使用 std::unordered_map::reserve 会提示 Illegal instruction 并导致地图服务器崩溃的问题.
	// 虽然根据微软的回复已经在 Visual Studio 2019 的 16.4 Preview 4 中解决了问题,
	// 考虑部分用户可能会一直停留在存在问题的编译器上工作, 因此做一个热修复.
	// 此修复只对 _MSC_VER == 1923 的 Visual Studio 编译器有效 (对应 Visual Studio 2019 16.3 版本)
	// https://developercommunity.visualstudio.com/content/problem/787296/vs2019-163-seems-to-incorrectly-detect-avx512-on-w.html
	// 感谢"李小狼"在阿里云服务器上暴露此问题, 并提供调试环境

	// 修正在 NPC 事件脚本代码中执行 unloadnpc 会导致地图服务器崩溃的问题 [Sola丶小克]
	// unloadnpc 的时候会重新构造 script_event 这个 std::map 的内容
	// 这会导致 npc_script_event 中提前获取的 vector 引用所指向的内容被清空,
	// 以至于在执行下一轮循环的时候, 无法获取已经被清空的原 script_event 内容, 而触发崩溃
	// 感谢"聽風"指出重现此问题的条件和环境

	// 修正 delchar 指令可能会导致地图服务器崩溃的问题 [Sola丶小克]
	// 会导致崩溃的示例脚本: .@m$ = delchar("", 0);

	// 修正 SC_BOSSMAPINFO 会导致地图服务器崩溃的问题 [Sola丶小克]

	// 修正释放或删除 ev_db 时, 对应的 script_event 节点没清空的问题 [Sola丶小克]
	// 在 reloadscript 时可能会因为 ev_db 被清空, 其他环节直接使用 script_event 的值而崩溃

	// 修正部分局部变量未初始化可能导致的潜在崩溃问题 [Sola丶小克]
	#define Pandas_Crashfix_Variable_Init

	// 在 Release 模式中也启用空指针检查机制 [Sola丶小克]
	#define Pandas_Crashfix_Use_NullptrCheck_In_ReleaseMode

	// 修正部分函数没有验证传入参数可能导致的崩溃问题 [Sola丶小克]
	#define Pandas_Crashfix_FunctionParams_Verify

	// 修正部分空指针访问可能导致的崩溃问题 [Sola丶小克]
	#define Pandas_Crashfix_Prevent_NullPointer

	// 修正部分除数为零可能导致的崩溃问题 [Sola丶小克]
	#define Pandas_Crashfix_Divide_by_Zero

	// 修正 getd/setd 变量名前后空白可能导致脚本崩溃的问题 [Sola丶小克]
	#define Pandas_Crashfix_ScriptCommand_Getd_And_Setd

	// 修正 Visual Studio 2019 16.3 在支持 AVX512 指令设备上的 unordered_map reserve 崩溃问题 [Sola丶小克]
	#define Pandas_Crashfix_VisualStudio_UnorderedMap_AVX512

	// 修正在 NPC 事件中执行 unloadnpc 可能导致事件列表引用失效的问题 [Sola丶小克]
	#define Pandas_Crashfix_Unloadnpc_In_Event

	// 修正 delchar 指令可能会导致地图服务器崩溃的问题 [Sola丶小克]
	// 会导致崩溃的示例脚本: .@m$ = delchar("", 0);
	#define Pandas_Crashfix_ScriptCommand_Delchar

	// 修正 SC_BOSSMAPINFO 会导致地图服务器崩溃的问题 [Sola丶小克]
	#define Pandas_Crashfix_BossMapinfo

	// 修正释放或删除 ev_db 时, 对应的 script_event 节点没清空的问题 [Sola丶小克]
	// 在 reloadscript 时可能会因为 ev_db 被清空, 其他环节直接使用 script_event 的值而崩溃
	#define Pandas_Crashfix_EventDatabase_Clean_Synchronize

	// 修正在未开启大乐透功能的情况下启动服务端, 再重新打开大乐透功能
	// 并用 @reloadbattleconf 使之立刻生效之后, 点击大乐透按钮会导致地图服务器崩溃的问题 [Sola丶小克]
	#define Pandas_Crashfix_RouletteData_UnInit

	// 修正释放 script_code 后没有将指针置空, 导致的崩溃问题 [Sola丶小克]
	// 感谢 Renee / HongShin 协助进行相关测试, 感谢 ╰づ记忆•斑驳〤 提出此问题
	// 重现方法:
	// - 编译成 Release 模式 (Debug 模式下编译器有内存访问越界保护, 无法被触发)
	// - 登录游戏, 将 Alt+M 中的表情快捷键的 8 设置为 @reloaditemdb
	// - 使用 @item 指令获取道具 12491, 双击执行
	// - 不做出任何选择, 直接按 Alt+8 触发 @reloaditemdb
	// - 完成重载后, 选择某一个菜单项 - 此时应该触发崩溃
	// - 若没有崩溃, 则重复使用 12491 -> reload -> 选择, 直到崩溃
	// reloaditemdb -> item_db.reload(); -> 触发每一个 item_data 的析构函数 (destruct function) ->
	// script_free_code 释放掉 script/equip_script/unequip_script 的 script_code
	// 但是释放后没有将对应的指针设为 NULL. 导致上述重现步骤中 script_free_state 函数针对 st->script->local.vars
	// 和 st->script->local.arrays 的空指针判断被绕过, 继而触发崩溃
	#define Pandas_Crashfix_ScriptFreeCode_SetPointerNull

	// 修正 pc_setpos 在特殊操作情况下可能会导致崩溃的问题 [Sola丶小克]
	// 重现方法:
	// - 构造一个 NPC, 对话开始时 sleep 5000 然后用 atcommand 指令调用 @warp
	// - 玩家与其对话然后立刻下线, 时间到之后会触发 warp 指令并导致崩溃
	// 因为触发 atcommand 的时候角色已经下线, 因此 atcommand_sub 会生成一个 dummy_sd 来替代,
	// 而 dummy_sd 并非真实存在的 sd 对象, 最后会导致地图服务器崩溃
	#define Pandas_Crashfix_PC_Setpos_With_Invaild_Player

	// 修正 getinstancevar 传递无效的副本编号会导致地图服务器崩溃的问题 [Sola丶小克]
	#define Pandas_Crashfix_GetInstanceVar_Invaild_InstanceID

	// 修正 setinstancevar 传递无效的副本编号会导致地图服务器崩溃的问题 [Sola丶小克]
	#define Pandas_Crashfix_SetInstanceVar_Invaild_InstanceID

	// 规避脚本引擎在定时器唤醒后可能导致的潜在崩溃 [Sola丶小克]
	// 目前常看到的崩溃调用堆栈是:
	// 在脚本被 sleep / sleep2 定时机制安排在未来继续执行某脚本时,
	// 如果在脚本恢复执行之前, 就因为其他原因把整个脚本释放掉, 就会在恢复执行脚本的时候导致地图服务器崩溃.
	// 具体: 从 run_script_timer 恢复进入 run_script_main 之后崩溃
	// 至于什么地方会在脚本还没恢复执行之前就将 script_code 释放暂时还没有特别明确的线索
	#define Pandas_Crashfix_Invaild_Script_Code

	// 规避在 map_addblock 和 map_delblock 因检查不严而导致崩溃的问题 [Renee]

	// 避免非 DelayConsume 类型的道具在使用脚本中调用 laphine_synthesis 脚本指令时,
	// 当最后一个物品被消耗时会导致地图服务器崩溃的问题 [Sola丶小克]

	// 避免非 DelayConsume 类型的道具在使用脚本中调用 laphine_upgrade 脚本指令时,
	// 当最后一个物品被消耗时会导致地图服务器崩溃的问题 [Sola丶小克]
#endif // Pandas_Crashfix

// ============================================================================
// 优化加速组 - Pandas_Speedup
// ============================================================================

#ifdef Pandas_Speedup
	// 是否在一些关键耗时节点打印出耗时情况 [Sola丶小克]

	// 优化 map_readfromcache 中对每个 cell 的分配方式 [Sola丶小克]
	// 主要降低 map_gat2cell 的调用次数, 因为一张地图需要加载 40000 个 cell
	// 虽然已经启用了 static 和 inline 但内部调用 struct 创建构体也是开销非常大的.
	// 优化后性能表现参考信息 (VS2019 + Win32)
	// 在 Debug 模式下越提速约 1.79 倍 (3350ms -> 1200ms)
	// 在 Release 模式下提速约 17.65% (1000ms -> 850ms)

	// 在 Windows 环境下对加载地图时滚动输出的信息进行限流 [Sola丶小克]
	// 好处在于极大的提升加载速度, 坏处在于类似 LeeStarter 等工具中打开地图服务器,
	// 会发现加载地图时的信息是跳跃显示的, 但并不影响实际情况下的使用
	// 优化后性能表现参考信息
	// VS2019 + Win32 启用 Pandas_Speedup_Map_Read_From_Cache 的情况下
	// 在 Debug 模式下提速约 64% (1250ms -> 760ms)
	// 在 Release 模式下地图加载信息默认不再显示 (通过 DETAILED_LOADING_OUTPUT 控制)
	#ifdef _WIN32
	#endif // _WIN32

	// 规避卸载 NPC 时的 npc_read_event_script 调用 [Sola丶小克]
	// OnInit 调用了大量的 unloadnpc, 而每次调用都会触发 npc_read_event_script
	// 在 Pandas_Crashfix_EventDatabase_Clean_Synchronize 启用的情况下
	// npc_unload_ev 每次卸载 NPC 时会将 script_event 中与 ev_db 相关的节点清理掉
	// 因此没必要在卸载 NPC 的时候调用 npc_read_event_script
	// 优化后性能表现参考信息 (VS2019 + Win32)
	// 在 Debug 模式下越提速约 2.72 倍 (5608ms -> 1506ms)
	// 在 Release 模式下提速约 1.65 倍 (1985ms -> 750ms)
	// 以下选项开关需要依赖 Pandas_Crashfix_EventDatabase_Clean_Synchronize 的拓展
	#ifdef Pandas_Crashfix_EventDatabase_Clean_Synchronize
		#define Pandas_Speedup_Unloadnpc_Without_Refactoring_ScriptEvent
	#endif // Pandas_Crashfix_EventDatabase_Clean_Synchronize

	// 通过微调程序逻辑改善 C26817 这样的常量引用性能优化场景 [Sola丶小克]
#endif // Pandas_Speedup

// ============================================================================
// 地图标记组 - Pandas_Mapflags
// ============================================================================

#ifdef Pandas_Mapflags
	// 是否启用 mobinfo 地图标记 [Sola丶小克]
	// 该标记用于指定某地图的 show_mob_info 值, 以此控制该地图魔物名称的展现信息
	// 此地图标记依赖 Pandas_MobInfomation_Extend 的拓展
	#ifdef Pandas_MobInfomation_Extend
		#define Pandas_MapFlag_MobInfo
	#endif // Pandas_MobInfomation_Extend

	// 是否启用 noautoloot 地图标记 [Sola丶小克]
	// 该标记用于在给定此标记的地图上禁止玩家使用自动拾取功能, 或使已激活的自动拾取功能失效

	// 是否启用 notoken 地图标记 [Sola丶小克]
	// 该标记用于禁止玩家在指定的地图上使用“原地复活之证”道具

	// 是否启用 nocapture 地图标记 [Sola丶小克]
	// 该标记用于禁止玩家在地图上使用宠物捕捉道具或贤者的"随机技能"来捕捉宠物
	// 此地图标记依赖 Pandas_Struct_Item_Data_Taming_Mobid 的拓展

	// 是否启用 hideguildinfo 地图标记 [Sola丶小克]
	// 使当前地图上的玩家无法见到其他人的公会图标、公会名称、职位等信息 (自己依然可见)

	// 是否启用 hidepartyinfo 地图标记 [Sola丶小克]
	// 使当前地图上的玩家无法见到其他人的队伍名称 (自己依然可见)

	// 是否启用 nomail 地图标记 [Sola丶小克]
	// 该标记用于禁止玩家在地图上打开邮件界面或进行邮件系统的相关操作

	// 是否启用 nopet 地图标记 [Sola丶小克]
	// 该标记用于禁止玩家在地图上召唤宠物, 宠物进入该地图会自动变回宠物蛋

	// 是否启用 nohomun 地图标记 [Sola丶小克]
	// 该标记用于禁止玩家在地图上召唤人工生命体, 生命体进入该地图会自动安息

	// 是否启用 nomerc 地图标记 [Sola丶小克]
	// 该标记用于禁止玩家在地图上召唤佣兵, 佣兵进入该地图会自动隐藏

	// 是否启用 mobdroprate 地图标记 [Sola丶小克]
	// 该标记用于额外调整此地图上普通魔物的物品掉落倍率

	// 是否启用 mvpdroprate 地图标记 [Sola丶小克]
	// 该标记用于额外调整此地图上 MVP 魔物的物品掉落倍率

	// 是否启用 maxheal 地图标记 [Sola丶小克]
	// 该标记用于限制此地图上单位的治愈系技能最大的 HP 治愈量

	// 是否启用 maxdmg_skill 地图标记 [Sola丶小克]
	// 该标记用于限制此地图上单位的最大技能伤害 (不含治愈系技能)

	// 是否启用 maxdmg_normal 地图标记 [Sola丶小克]
	// 该标记用于限制此地图上单位的最大平砍伤害 (包括二刀连击和刺客拳刃平砍)

	// 是否启用 noskill2 地图标记 [Sola丶小克]
	// 该标记用于禁止此地图上的指定单位使用技能 (支持掩码指定多种类型的单位)

	// 是否启用 noaura 地图标记 [Sola丶小克]
	// 该标记用于在当前地图上禁用角色的光环效果
	// 此地图标记依赖 Pandas_Aura_Mechanism 的拓展
	#ifdef Pandas_Aura_Mechanism
		#define Pandas_MapFlag_NoAura
	#endif // Pandas_Aura_Mechanism

	// 是否启用 maxaspd 地图标记 [Sola丶小克]
	// 该标记用于限制此地图上单位的最大攻击速度 (ASDP: 1~199)

	// 是否启用 noslave 地图标记 [HongShin]
	// 该标记用于禁止此地图上的魔物召唤随从

	// 是否启用 nobank 地图标记 [聽風]
	// rAthena 官方已经实现此标记, 当前宏定义所包含的代码用于处理体验细节

	// 是否启用 nouseitem 地图标记 [HongShin]
	// 该标记用于禁止玩家在地图上使用消耗型物品道具

	// 是否启用 hidedamage 地图标记 [HongShin]
	// 该标记用于隐藏此地图上任何攻击的实际伤害数值 (无论什么单位, 无论是否 MISS)

	// 是否启用 noattack 地图标记 [HongShin]
	// 该标记用于禁止此地图上的任何单位进行普通攻击

	// 是否启用 noattack2 地图标记 [HongShin]
	// 该标记用于禁止此地图上指定单位进行普通攻击 (支持掩码指定多种类型的单位)

	// PYHELP - MAPFLAG - INSERT POINT - <Section 1>
#endif // Pandas_Mapflags

// ============================================================================
// 脚本引擎修改组 - Pandas_ScriptEngine
// ============================================================================

#ifdef Pandas_ScriptEngine
	// 使脚本引擎能够支持穿越事件队列机制, 直接执行某些事件 [Sola丶小克]
	#define Pandas_ScriptEngine_Express

	#ifdef Pandas_ScriptEngine_Express
		/************************************************************************/
		/* Express 类型的快速事件，这些事件将会被立刻执行, 不进事件队列                */
		/************************************************************************/

		// 当角色能力被重新计算时触发事件 [Sola丶小克]
		// 事件类型: Express / 事件名称: OnPCStatCalcEvent
		// 常量名称: NPCE_STATCALC / 变量名称: statcalc_express_name
		// 正常按照命名规范这个事件应该叫 NPCX_STATCALC 和 OnPCStatCalcExpress
		// 但这个事件比较特殊, 之前 rAthena 官方出现过. 考虑到对老脚本的兼容, 继续沿用老的事件常量和名称

		// 当玩家成功解除一个状态(Buff)后触发实时事件 [Sola丶小克]
		// 事件类型: Express / 事件名称: OnPCBuffEndExpress
		// 常量名称: NPCX_SC_END / 变量名称: sc_end_express_name

		// 当玩家成功获得一个状态(Buff)后触发实时事件 [Sola丶小克]
		// 事件类型: Express / 事件名称: OnPCBuffStartExpress
		// 常量名称: NPCX_SC_START / 变量名称: sc_start_express_name

		// 当玩家进入或者改变地图时触发实时事件 [Sola丶小克]
		// 事件类型: Express / 事件名称: OnPCEnterMapExpress
		// 常量名称: NPCX_ENTERMAP / 变量名称: entermap_express_name

		// 当 progressbar 进度条被打断时触发实时事件 [Sola丶小克]
		// 事件类型: Express / 事件名称: OnPCProgressAbortExpress
		// 常量名称: NPCX_PROGRESSABORT / 变量名称: progressabort_express_name

		// 当某个单位被击杀时触发实时事件 [Sola丶小克]
		// 事件类型: Express / 事件名称: OnUnitKillExpress
		// 常量名称: NPCX_UNIT_KILL / 变量名称: unit_kill_express_name

		// 当魔物即将掉落道具时触发实时事件 [Sola丶小克]
		// 事件类型: Express / 事件名称: OnMobDropItemExpress
		// 常量名称: NPCX_MOBDROPITEM / 变量名称: mobdropitem_express_name

		// 当玩家发起攻击并即将进行结算时触发实时事件 [聽風]
		// 事件类型: Express / 事件名称: OnPCAttackExpress
		// 常量名称: NPCX_PCATTACK / 变量名称: pcattack_express_name

		// 当玩家成功召唤出佣兵时触发实时事件 [HongShin]
		// 事件类型: Express / 事件名称: OnPCMerCallExpress
		// 常量名称: NPCX_MER_CALL / 变量名称: mer_call_express_name

		// 当佣兵离开玩家时触发实时事件 [HongShin]
		// 事件类型: Express / 事件名称: OnPCMerLeaveExpress
		// 常量名称: NPCX_MER_LEAVE / 变量名称: mer_leave_express_name

		// 当玩家往聊天框发送信息时触发实时事件 [人鱼姬的思念]
		// 事件类型: Express / 事件名称: OnPCTalkExpress
		// 常量名称: NPCX_PC_TALK / 变量名称: pc_talk_express_name

		// 当玩家受到伤害并即将进行结算时触发实时事件 [人鱼姬的思念]
		// 事件类型: Express / 事件名称: OnPCHarmedExpress
		// 常量名称: NPCX_PCHARMED / 变量名称: pcharmed_express_name
		// PYHELP - NPCEVENT - INSERT POINT - <Section 13>
	#endif // Pandas_ScriptEngine_Express

	// 调整脚本引擎在 add_str 中分配内存的步进空间 [Sola丶小克]
	// 避免过于频繁的 RECREATE 申请并移动内存中的数据, 减少内存分配开销
	// 性能表现参考信息
	// - 调整前 str_buf  需要被重新分配 1174 次, 调整后为 37 次
	// - 调整前 str_data 需要被重新分配 185  次, 调整后为 47 次

	// 使脚本引擎能够支持备份无数个脚本堆栈 [Sola丶小克]
	// 以此避免嵌套调用超过两层的脚本会导致程序崩溃的问题 (如: script4each -> getitem -> 成就系统)

	// 脚本语法验证时能够考虑双字节字符与转义序列的关系 [Sola丶小克]
	// rAthena 在大部分情况下可以正常工作, 除了中文紧挨着待转义的双引号这种情况:
	// script4eachmob "{ unittalk $@gid, \"中文紧挨着待转义的双引号无法通过语法检测\"; }", 0;
	// ASCII码表: https://baike.baidu.com/item/ASCII
	// 若一个字符对应的字节编码 <= 0x7e 那么说明它在 ASCII 编码范围
	// rAthena 在最原始的判断中, 只判断了 p 不作为双字节字符的低位出现, 就认为 p 是独立的反斜杠
	// 注意: 但部分 GBK 的中文的低位, 若紧挨着 \ 就会导致 rAthena 的方法出现误判.
	// 例如: [文] 这个字符在 GBK 的编码是 0xCDC4
	// 若编写的时候出现这样的情况: "\"中文\"" 我们预期输出的就是 "中文"
	// 但这里我们重点看下 [文\] 这两个字符挨在一起的时候, 它们的十六进制是: 0xCDC45C
	// 此处的 0x5C 就是反斜杠的字符编码 (位于 ASCII 码表),
	// rAthena 的代码走到 p == 0x5C 的时候,
	// 判断一看 p[-1] 即 0xC4 <= 0x7E 不成立, 那么认为 p 是一个独立反斜杠
	// 但实际上此时的反斜杠和下一个字符的 " 构成的 \" 才是真正的一组转义序列,
	// 如果认为 p 是独立反斜杠, 那么 " 也将被独立, 不再成为转义序列的一部分. 从而提前关闭第一个双引号,
	// 原计划输出的 "中文" 输出将变成: "中文
	// 而最末末尾的 " 将被作为一个新的字符串起点, 导致语法检测双引号无法闭合而报错

	// 修正 add_str 触发 str_buf 的扩容分配后 st->funcname 的所指向的指令名称无效的问题,
	// 因为 st->funcname 指针指向的内存已在扩容分配时被释放 [Sola丶小克]
#endif // Pandas_ScriptEngine

// ============================================================================
// NPC 事件组 - Pandas_NpcEvent
// ============================================================================

#ifdef Pandas_NpcEvent
	/************************************************************************/
	/* Event 类型的标准事件，这些事件不能被 processhalt 打断                    */
	/************************************************************************/

	// 当玩家杀死 MVP 魔物后触发事件 [Sola丶小克]
	// 事件类型: Event / 事件名称: OnPCKillMvpEvent
	// 常量名称: NPCE_KILLMVP / 变量名称: killmvp_event_name
	#define Pandas_NpcEvent_KILLMVP
#endif // Pandas_NpcEvent

// ============================================================================
// 道具机制组 - Pandas_Item_Properties
// ============================================================================

// 以下选项依赖 Pandas_Struct_Item_Data_Properties 的拓展
#ifdef Pandas_Struct_Item_Data_Properties
	// 启用道具特殊属性的部分生效代码 [Sola丶小克]
	// 此选项开启后 item_properties.yml 数据库中 AvoidConsumeForUse / AvoidConsumeForSkill 才能发挥作用
	#define Pandas_Item_Properties
	// 启用护身符道具系统 [Sola丶小克]
	#define Pandas_Item_Amulet_System
	// 启用道具外观控制机制 [Sola丶小克]
	// 此选项开启后 item_properties.yml 数据库中 ControlViewID 才能发挥作用
	// 此选项依赖 Pandas_FuncParams_Clif_Item_Equip 的拓展
	#ifdef Pandas_FuncParams_Clif_Item_Equip
		#define Pandas_Item_ControlViewID
	#endif // Pandas_FuncParams_Clif_Item_Equip
	// 启用道具特殊公告策略 [Sola丶小克]
	#define Pandas_Item_Special_Annouce
#endif // Pandas_Struct_Item_Data_Properties

// ============================================================================
// 管理员指令组 - Pandas_AtCommands
// ============================================================================

#ifdef Pandas_AtCommands
	// 是否启用 recallmap 管理员指令 [Sola丶小克]
	// 召唤当前(或指定)地图的玩家来到身边 (处于离线挂店模式的角色不会被召唤)
	#define Pandas_AtCommand_RecallMap

	// 是否启用 crashtest 管理员指令 [Sola丶小克]
	// 执行崩溃测试, 在比较严格的环境上故意触发地图服务器崩溃
	#define Pandas_AtCommand_Crashtest

	#ifdef Pandas_Character_Title_Controller
		// 是否启用 title 管理员指令 [Sola丶小克]
		// 给角色设置一个指定的称号ID, 客户端封包版本大于等于 20150513 才可用
		#define Pandas_AtCommand_Title
	#endif // Pandas_Character_Title_Controller

	// 是否启用 suspend 管理员指令 [Sola丶小克]
	// 使角色进入离线挂机模式, 维持当前的全部状态 (朝向, 站立与否)
	#define Pandas_AtCommand_Suspend

	// 是否启用 afk 管理员指令 [Sola丶小克]
	// 使角色进入离开模式, 角色将会坐到地上并自动使用 AFK 头饰 (表示角色暂时离开)
	#define Pandas_AtCommand_AFK

	// 是否启用 aura 管理员指令 [Sola丶小克]
	// 使角色可以激活特定组合的光环效果, 光环效果会一直跟随角色
	// 此选项开关需要依赖 Pandas_Aura_Mechanism 的拓展
	#ifdef Pandas_Aura_Mechanism
		#define Pandas_AtCommand_Aura
	#endif // Pandas_Aura_Mechanism

	// 是否启用 reloadauradb 管理员指令 [Sola丶小克]
	// 重新加载光环数据库 (aura_db.yml)
	// 此选项开关需要依赖 Pandas_Aura_Mechanism 的拓展
	#ifdef Pandas_Aura_Mechanism
		#define Pandas_AtCommand_ReloadAuraDB
	#endif // Pandas_Aura_Mechanism

	// 是否启用 reloadlaphinedb 管理员指令 [Sola丶小克]
	// 重新加载 Laphine 数据库 (laphine_synthesis.yml 和 laphine_upgrade.yml)
	#define Pandas_AtCommand_ReloadLaphineDB
	// PYHELP - ATCMD - INSERT POINT - <Section 1>
#endif // Pandas_AtCommands

// ============================================================================
// 脚本指令组 - Pandas_ScriptCommands
// ============================================================================

#ifdef Pandas_ScriptCommands
	// 是否拓展 announce 脚本指令 [Sense 提交] [Sola丶小克 改进]
	// 使 announce 指令能够支持 bc_name 标记位
	// 携带此标记位的公告能够在双击公告时将发布者角色名称填写到聊天窗口
	// 备注: 自己发送的公告自己双击则无效
	// 提示: 使用 20130807 客户端测试通过, 更早之前的客户端没有测试过
	// 是否拓展 unitexists 脚本指令 [Sola丶小克]
	// 添加一个可选参数, 用于强调单位必须存在且活着才返回 true
	// 是否启用 setheaddir 脚本指令 [Sola丶小克]
	// 用于调整角色纸娃娃脑袋的朝向 (0 - 正前方; 1 - 向右看; 2 - 向左看)
	// 是否启用 setbodydir 脚本指令 [Sola丶小克]
	// 用于调整角色纸娃娃身体的朝向 (与 NPC 一致, 从 0 到 7 共 8 个方位可选择)
	// 是否启用 openbank 脚本指令 [Sola丶小克]
	// 2022-4-20 修订备注:
	// 由于 rAthena 官方已经实现了 openbank 指令且重名,
	// 因此这里的开关只控制 openbank 指令是否如以前版本一样给予返回值
	// 是否启用 instance_users 脚本指令 [Sola丶小克]
	// 获取指定的副本实例中已经进入副本地图的人数
	// 是否启用 cap 脚本指令 [Sola丶小克]
	// 由于 rAthena 已经实现 cap_value 指令, 这里兼容老版本 cap 指令
	// 是否启用 mobremove 脚本指令 [Sola丶小克]
	// 根据 GID 移除一个魔物单位 (只是移除, 不会让魔物死亡)
	#define Pandas_ScriptCommand_MobRemove
	// 是否启用 mesclear 脚本指令 [Sola丶小克]
	// 由于 rAthena 已经实现 clear 指令, 这里兼容老版本 mesclear 指令
	// 是否启用 battleignore 脚本指令 [Sola丶小克]
	// 将角色设置为魔物免战状态, 避免被魔物攻击 (与 GM 指令的 monsterignore 效果一致)
	// 是否启用 gethotkey 脚本指令 [Sola丶小克]
	// 获取指定快捷键位置当前的信息 (该指令有一个用于兼容的别名: get_hotkey)
	// 是否启用 sethotkey 脚本指令 [Sola丶小克]
	// 设置指定快捷键位置的信息 (该指令有一个用于兼容的别名: set_hotkey)
	// 是否启用 showvend 脚本指令 [Jian916]
	// 使指定的 NPC 头上可以显示露天商店的招牌, 点击招牌可触发与 NPC 的对话
	// 是否启用 viewequip 脚本指令 [Sola丶小克]
	// 使用该指令可以查看指定在线角色的装备面板信息 (注意: v2.0.0 以前是通过账号编号)
	// 是否启用 countitemidx 脚本指令 [Sola丶小克]
	// 获取指定背包序号的道具在背包中的数量 (该指令有一个用于兼容的别名: countinventory)
	// 是否启用 delitemidx 脚本指令的别名 delinventory [Sola丶小克]
	// https://github.com/rathena/rathena/commit/c18707bb6dd2bd6068bc0d3708401871a2d7270c
	// 由于 rAthena 官方实现了 delitemidx, 因此使用它来接替原先熊猫模拟器的自定义实现
	// 是否启用 identifyidx 脚本指令 [Sola丶小克]
	// 鉴定指定背包序号的道具 (该指令有一个用于兼容的别名: identifybyidx)
	// 是否启用 unequipidx 脚本指令 [Sola丶小克]
	// 脱下指定背包序号的道具 (该指令有一个用于兼容的别名: unequipinventory)
	// 是否启用 equipidx 脚本指令 [Sola丶小克]
	// 穿戴指定背包序号的道具 (该指令有一个用于兼容的别名: equipinventory)
	// 是否启用 itemexists 脚本指令 [Sola丶小克]
	// 确认物品数据库中是否存在指定物品 (该指令有一个用于兼容的别名: existitem)
	// 是否启用 renttime 脚本指令 [Sola丶小克]
	// 增加/减少指定位置装备的租赁时间 (该指令有一个用于兼容的别名: resume)
	// 是否启用 getequipidx 脚本指令 [Sola丶小克]
	// 获取指定位置装备的背包序号
	// 是否启用 statuscalc 脚本指令 [Sola丶小克]
	// 由于 rAthena 已经实现 recalculatestat 指令, 这里兼容老版本 statuscalc 指令
	// 是否启用 getequipexpiretick 脚本指令 [Sola丶小克]
	// 获取指定位置装备的租赁到期剩余秒数 (该指令有一个用于兼容的别名: isrental)
	// 是否启用 getinventoryinfo 系列脚本指令 [Sola丶小克]
	// 查询指定背包、公会仓库、手推车、个人仓库/扩充仓库序号的道具详细信息
	// 包含以下几个指令变体:
	// getinventoryinfo <道具的背包序号>,<要查看的信息类型>{,<角色编号>};
	// getcartinfo <道具的手推车序号>,<要查看的信息类型>{,<角色编号>};
	// getguildstorageinfo <道具的公会仓库序号>,<要查看的信息类型>{,<角色编号>};
	// getstorageinfo <道具的个人仓库/扩充仓库序号>,<要查看的信息类型>{{,<仓库编号>},<角色编号>};
	// 是否启用 statuscheck 脚本指令 [Sola丶小克]
	// 判断状态是否存在, 并取得相关的状态参数 (该指令有一个用于兼容的别名: sc_check)
	// 是否启用 renttimeidx 脚本指令 [Sola丶小克]
	// 增加/减少指定背包序号道具的租赁时间
	// 是否启用 party_leave 脚本指令 [Sola丶小克]
	// 使当前角色或指定角色退出队伍 (主要出于兼容目的而实现该指令)
	// 是否启用 script4each / script4eachmob / script4eachnpc 脚本指令 [Sola丶小克]
	// 对指定范围的玩家 / 魔物 / NPC 执行相同的一段脚本
	// 是否启用 searcharray 脚本指令 [Sola丶小克]
	// 由于 rAthena 已经实现 inarray 指令, 这里兼容老版本 searcharray 指令
	// 是否启用 getsameipinfo 脚本指令 [Sola丶小克]
	// 获得某个指定 IP 在线的玩家信息
	// 是否启用 logout 脚本指令 [Sola丶小克]
	// 使指定的角色立刻登出游戏
	// 是否启用 warppartyrevive 脚本指令 [Sola丶小克]
	// 与 warpparty 类似, 但可以复活死亡的队友并传送 (该指令有一个用于兼容的别名: warpparty2)
	// 是否启用 getareagid 脚本指令 [Sola丶小克]
	// 获取指定范围内特定类型单位的全部 GID (注意: 该指令不再兼容以前 rAthenaCN 的同名指令)
	// 是否启用 processhalt 脚本指令 [Sola丶小克]
	// 在事件处理代码中使用该指令, 可以中断源代码的后续处理逻辑
	// 此选项开关需要依赖 Pandas_Struct_Map_Session_Data_EventHalt 的拓展
	#ifdef Pandas_Struct_Map_Session_Data_EventHalt
		#define Pandas_ScriptCommand_ProcessHalt
	#endif // Pandas_Struct_Map_Session_Data_EventHalt
	// 是否启用 settrigger 脚本指令 [Sola丶小克]
	// 使用该指令可以设置某个事件或过滤器的触发行为 (是否触发、下次触发、永久触发)
	// 此选项开关需要依赖 Pandas_Struct_Map_Session_Data_EventTrigger 的拓展
	#ifdef Pandas_Struct_Map_Session_Data_EventTrigger
		#define Pandas_ScriptCommand_SetEventTrigger
	#endif // Pandas_Struct_Map_Session_Data_EventTrigger
	// 是否启用 messagecolor 脚本指令 [Sola丶小克]
	// 使用该指令可以发送指定颜色的消息文本到聊天窗口中
	// 是否启用 copynpc 脚本指令 [Sola丶小克]
	// 使用该指令可以复制指定的 NPC 到一个新的位置 (坐标等相对可以灵活设置)
	#define Pandas_ScriptCommand_Copynpc
	// 是否启用 gettimefmt 脚本指令 [Sola丶小克]
	// 将当前时间格式化输出成字符串, 是 gettimestr 的改进版
	// 是否启用 multicatchpet 脚本指令 [Sola丶小克]
	// 与 catchpet 指令类似, 但可以指定更多支持捕捉的魔物编号
	// 此选项开关需要依赖 Pandas_Struct_Map_Session_Data_MultiCatchTargetClass 的拓展
	#ifdef Pandas_Struct_Map_Session_Data_MultiCatchTargetClass
		#define Pandas_ScriptCommand_MultiCatchPet
	#endif // Pandas_Struct_Map_Session_Data_MultiCatchTargetClass
	// 是否启用 selfdeletion 脚本指令 [Sola丶小克]
	// 设置 NPC 的自毁策略, 用于配合 copynpc 实现在开宝箱/挖矿时进行自毁等场景
	// 是否启用 npcexists 脚本指令 [Sola丶小克]
	// 该指令用于判断指定名称的 NPC 是否存在, 就算不存在控制台也不会报错
	#ifdef Pandas_FuncDefine_STORAGE_ADDITEM
		// 是否启用 storagegetitem 脚本指令 [Sola丶小克]
		// 往仓库直接创造一个指定的道具, 必须在仓库关闭的时候才能调用
		#define Pandas_ScriptCommand_StorageGetItem
	#endif // Pandas_FuncDefine_STORAGE_ADDITEM
	// 是否启用 setinventoryinfo 脚本指令 [Sola丶小克]
	// 该指令用于设置指定背包序号道具的部分详细信息, 与 getinventoryinfo 对应
	// 是否启用 updateinventory 脚本指令 [Sola丶小克]
	// 该指令用于重新下发关联玩家的背包数据给客户端 (刷新客户端背包数据)
	// 是否启用 getcharmac 脚本指令 [Sola丶小克]
	// 该指令用于获取指定角色登录时使用的 MAC 地址
	// 此选项开关需要依赖 Pandas_Extract_SSOPacket_MacAddress 的拓展
	#ifdef Pandas_Extract_SSOPacket_MacAddress
		#define Pandas_ScriptCommand_GetCharMacAddress
	#endif // Pandas_Extract_SSOPacket_MacAddress

	// 是否启用 getconstant 脚本指令 [Sola丶小克]
	// 该指令用于查询一个常量字符串对应的数值
	// 是否启用 preg_search 脚本指令 [Sola丶小克]
	// 该指令用于执行一个正则表达式搜索并返回首个匹配的分组内容
	// 是否启用 aura 脚本指令 [Sola丶小克]
	// 该指令用于为角色激活特定组合的光环效果, 光环效果会一直跟随角色
	// 此选项开关需要依赖 Pandas_Aura_Mechanism 的拓展
	#ifdef Pandas_Aura_Mechanism
		#define Pandas_ScriptCommand_Aura
	#endif // Pandas_Aura_Mechanism
	// 是否启用 unitaura 脚本指令 [Sola丶小克]
	// 该指令用于调整七种单位的光环组合 (但仅 BL_PC 会被持久化)
	// 七种单位分别是: 玩家/魔物/佣兵/宠物/NPC/精灵/人工生命体
	// 此选项开关需要依赖 Pandas_Aura_Mechanism 的拓展
	#ifdef Pandas_Aura_Mechanism
		#define Pandas_ScriptCommand_UnitAura
	#endif // Pandas_Aura_Mechanism
	// 是否启用 getunittarget 脚本指令 [Sola丶小克]
	// 该指令用于获取指定单位当前正在攻击的目标单位编号
	// 是否启用 unlockcmd 脚本指令 [Sola丶小克]
	// 该指令用于解锁实时事件和过滤器事件的指令限制, 只能用于实时或过滤器事件
	#define Pandas_ScriptCommand_UnlockCmd
	// 是否启用战斗记录相关的脚本指令 [Sola丶小克]
	// 此选项开关需要依赖 Pandas_BattleRecord 的拓展
	#ifdef Pandas_BattleRecord
		// 是否启用 batrec_query 脚本指令 [Sola丶小克]
		// 查询指定单位的战斗记录, 查看与交互目标单位产生的具体记录值
		#define Pandas_ScriptCommand_BattleRecordQuery
		// 是否启用 batrec_rank 脚本指令 [Sola丶小克]
		// 查询指定单位的战斗记录并对记录的值进行排序, 返回排行榜单
		#define Pandas_ScriptCommand_BattleRecordRank
		// 是否启用 batrec_sortout 脚本指令 [Sola丶小克]
		// 移除指定单位的战斗记录中交互单位已经不存在 (或下线) 的记录
		#define Pandas_ScriptCommand_BattleRecordSortout
		// 是否启用 batrec_reset 脚本指令 [Sola丶小克]
		// 清除指定单位的战斗记录
		#define Pandas_ScriptCommand_BattleRecordReset
		// 是否启用 enable_batrec 脚本指令 [Sola丶小克]
		// 该指令用于启用指定单位的战斗记录
		#define Pandas_ScriptCommand_EnableBattleRecord
		// 是否启用 disable_batrec 脚本指令 [Sola丶小克]
		// 该指令用于禁用指定单位的战斗记录
		#define Pandas_ScriptCommand_DisableBattleRecord
	#endif // Pandas_BattleRecord
	// 是否启用 login 脚本指令 [Sola丶小克]
	// 该指令用于将指定的角色以特定的登录模式拉上线
	// 此选项开关需要依赖 Pandas_Player_Suspend_System 的拓展
	#ifdef Pandas_Player_Suspend_System
		#define Pandas_ScriptCommand_Login
	#endif // Pandas_Player_Suspend_System
	// 是否启用 checksuspend 脚本指令 [Sola丶小克]
	// 该指令用于获取指定角色或指定账号当前在线角色的挂机模式
	// 此选项开关需要依赖 Pandas_Struct_Autotrade_Extend 和 Pandas_Player_Suspend_System 的拓展
	#ifdef Pandas_Struct_Autotrade_Extend
		#ifdef Pandas_Player_Suspend_System
			#define Pandas_ScriptCommand_CheckSuspend
		#endif // Pandas_Player_Suspend_System
	#endif // Pandas_Struct_Autotrade_Extend
	// 是否启用 bonus_script_remove 脚本指令 [Sola丶小克]
	// 该指令用于移除指定的 bonus_script 效果脚本
	// 是否启用 bonus_script_list 脚本指令 [Sola丶小克]
	// 该指令用于获取指定角色当前激活的全部 bonus_script 效果脚本编号
	// 是否启用 bonus_script_exists 脚本指令 [Sola丶小克]
	// 该指令用于查询指定角色是否已经激活了特定的 bonus_script 效果脚本
	// 是否启用 bonus_script_getid 脚本指令 [Sola丶小克]
	// 该指令用于查询效果脚本代码对应的效果脚本编号
	// 是否启用 bonus_script_info 脚本指令 [Sola丶小克]
	// 该指令用于查询指定效果脚本的相关信息
	// 是否启用 expandinventory_adjust 脚本指令 [Sola丶小克]
	// 该指令用于增加角色的背包容量上限
	// 是否启用 getinventorysize 脚本指令 [Sola丶小克]
	// 该指令用于查询并获取当前角色的背包容量上限
	// 是否启用 getmapspawns 脚本指令 [Sola丶小克]
	// 该指令用于获取指定地图的魔物刷新点信息
	// 此选项开关需要依赖 Pandas_Struct_Map_Data_Mob_Spawns 的拓展
	#ifdef Pandas_Struct_Map_Data_Mob_Spawns
		#define Pandas_ScriptCommand_GetMapSpawns
	#endif // Pandas_Struct_Map_Data_Mob_Spawns
	// 是否启用 getmobspawns 脚本指令 [Sola丶小克]
	// 该指令用于查询指定魔物在不同地图的刷新点信息
	// 此选项开关需要依赖 Pandas_Struct_Map_Data_Mob_Spawns 的拓展
	#ifdef Pandas_Struct_Map_Data_Mob_Spawns
		#define Pandas_ScriptCommand_GetMobSpawns
	#endif // Pandas_Struct_Map_Data_Mob_Spawns
	// 是否启用 getcalendartime 脚本指令 [Haru]
	// 该指令用于获取下次出现指定时间的 UNIX 时间戳
	// 是否启用 getskillinfo 脚本指令 [聽風]
	// 该指令用于获取指定技能在技能数据库中所配置的各项信息
	// 是否启用 boss_monster 脚本指令 [人鱼姬的思念]
	// 该指令用于召唤魔物并使之能被 BOSS 雷达探测 (哪怕被召唤魔物本身不是 BOSS)
	// 此选项依赖 Pandas_FuncDefine_Mob_Once_Spawn 的拓展
	#ifdef Pandas_FuncDefine_Mob_Once_Spawn
		#define Pandas_ScriptCommand_BossMonster
	#endif // Pandas_FuncDefine_Mob_Once_Spawn
	// 是否启用 sleep3 脚本指令 [人鱼姬的思念]
	// 该指令用于休眠一段时间再执行后续脚本, 与 sleep2 类似但忽略报错
	// 是否启用 getquesttime 脚本指令 [Sola丶小克]
	// 该指令用于查询角色指定任务的时间信息 (感谢 "SSBoyz" 建议)
	// 是否启用 unitspecialeffect 脚本指令 [人鱼姬的思念]
	// 该指令用于使指定游戏单位可以显示某个特效, 并支持控制特效可见范围
	// 是否启用 next_dropitem_special 脚本指令 [Sola丶小克]
	// 该指令用于对下一个掉落到地面上的物品进行特殊设置, 支持魔物掉落道具和 makeitem 系列指令
	// 是否启用 getgradeitem 脚本指令 [Sola丶小克]
	// 该指令用于创造带有指定附魔评级的道具, 由于 rAthena 已经正式实现了 getitem4,
	// getgradeitem 仅用于兼容旧版本的脚本, 请尽量使用 getitem4
	// 是否启用 getrateidx 脚本指令 [Sola丶小克]
	// 随机获取一个数值型数组的索引序号, 数组中每个元素的值为权重值
	// 是否启用 getbossinfo 脚本指令 [Sola丶小克]
	// 该指令用于查询 BOSS 魔物重生时间及其坟墓等信息
	#define Pandas_ScriptCommand_GetBossInfo
	// 是否启用 whodropitem 脚本指令 [Sola丶小克]
	// 该指令用于查询指定道具会从哪些魔物身上掉落以及掉落的机率信息
	// 是否扩充 getinventorylist 脚本指令 [Sola丶小克]
	// 主要包括了查询返回值的信息扩充, 衍生查询仓库和手推车的变体指令, 可控制每次需要被赋值的具体数组
	// - 查询返回值的信息扩充相比 rAthena 多返回以下内容
	//	 - @inventorylist_uid$[]
	//   - @inventorylist_equipswitch[]
	// - 衍生查询仓库和手推车的变体指令
	//   - getstoragelist;
	//   - getguildstoragelist;
	//   - getcartlist;
	// - 可控制每次想查询的数据类型
	//   - 用于解决仓库和背包容量超大时候填充大量不使用的数据带来的性能问题
	// 更多详细用法请移步 doc/pandas_script_commands.txt 文件
	// 是否支持异步查询数据库的脚本指令 [Sola丶小克]
	// 此选项开关需要依赖 Pandas_Support_Future_Execution 的拓展
	// 当前涉及到的脚本指令有以下几个:
	// - query_sql_async
	// - query_logsql_async
	// 此功能由 inhyositsu <inhyositsu@gmail.com> 实现,
	// 后续由 Sola丶小克 进行微调并汇入熊猫模拟器
	#ifdef Pandas_Support_Future_Execution
		#define Pandas_ScriptCommand_QuerySql_Async
	#endif // Pandas_Support_Future_Execution
	#ifdef Pandas_Character_Title_Controller
		// 是否启用 setchartitle 脚本指令 [Sola丶小克]
		// 设置指定玩家的称号ID, 客户端封包版本大于等于 20150513 才可用
		#define Pandas_ScriptCommand_SetCharTitle

		// 是否启用 getchartitle 脚本指令 [Sola丶小克]
		// 获得指定玩家的称号ID, 客户端封包版本大于等于 20150513 才可用
		#define Pandas_ScriptCommand_GetCharTitle
	#endif // Pandas_Character_Title_Controller
	// PYHELP - SCRIPTCMD - INSERT POINT - <Section 1>
#endif // Pandas_ScriptCommands
