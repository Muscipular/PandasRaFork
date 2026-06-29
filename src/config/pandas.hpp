#pragma once

	#define Pandas_Basic
	#define Pandas_StructIncrease
	#define Pandas_ScriptEngine
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

			// 当玩家进入 NPC 开启的聊天室时触发过滤器 [Sola丶小克]
			// 事件类型: Filter / 事件名称: OnPCInChatroomFilter
			// 常量名称: NPCF_ENTERCHAT / 变量名称: enterchat_filter_name

			// 当玩家准备插入卡片时触发过滤器 [Sola丶小克]
			// 事件类型: Filter / 事件名称: OnPCInsertCardFilter
			// 常量名称: NPCF_INSERT_CARD / 变量名称: insert_card_filter_name

			// 当玩家准备使用非装备类道具时触发过滤器 [Sola丶小克]
			// 事件类型: Filter / 事件名称: OnPCUseItemFilter
			// 常量名称: NPCF_USE_ITEM / 变量名称: use_item_filter_name

			// 当玩家准备使用技能时触发过滤器 [Sola丶小克]
			// 事件类型: Filter / 事件名称: OnPCUseSkillFilter
			// 常量名称: NPCF_USE_SKILL / 变量名称: use_skill_filter_name

			// 当玩家准备打开乐透大转盘的时候触发过滤器 [Sola丶小克]
			// 事件类型: Filter / 事件名称: OnPCOpenRouletteFilter
			// 常量名称: NPCF_ROULETTE_OPEN / 变量名称: roulette_open_filter_name

			// 当玩家准备查看某个角色的装备时触发过滤器 [Sola丶小克]
			// 事件类型: Filter / 事件名称: OnPCViewEquipFilter
			// 常量名称: NPCF_VIEW_EQUIP / 变量名称: view_equip_filter_name

			// 当玩家准备穿戴装备时触发过滤器 [Sola丶小克]
			// 事件类型: Filter / 事件名称: OnPCEquipFilter
			// 常量名称: NPCF_EQUIP / 变量名称: equip_filter_name

			// 当玩家准备脱下装备时触发过滤器 [Sola丶小克]
			// 事件类型: Filter / 事件名称: OnPCUnequipFilter
			// 常量名称: NPCF_UNEQUIP / 变量名称: unequip_filter_name

			// 当玩家准备获得一个状态(Buff)时触发过滤器 [Sola丶小克]
			// 事件类型: Filter / 事件名称: OnPCBuffStartFilter
			// 常量名称: NPCF_SC_START / 变量名称: sc_start_filter_name

			// 当玩家使用菜单中的原地复活之证时触发过滤器 [Sola丶小克]
			// 事件类型: Filter / 事件名称: OnPCUseReviveTokenFilter
			// 常量名称: NPCF_USE_REVIVE_TOKEN / 变量名称: use_revive_token_filter_name

			// 当玩家使用一键鉴定道具时触发过滤器 [Sola丶小克]
			// 事件类型: Filter / 事件名称: OnPCUseOCIdentifyFilter
			// 常量名称: NPCF_ONECLICK_IDENTIFY / 变量名称: oneclick_identify_filter_name

			// 当玩家准备创建公会时触发过滤器 [聽風]
			// 事件类型: Filter / 事件名称: OnPCGuildCreateFilter
			// 常量名称: NPCF_GUILDCREATE / 变量名称: guildcreate_filter_name

			// 当玩家即将加入公会时触发过滤器 [聽風]
			// 事件类型: Filter / 事件名称: OnPCGuildJoinFilter
			// 常量名称: NPCF_GUILDJOIN / 变量名称: guildjoin_filter_name

			// 当玩家准备离开公会时触发过滤器 [聽風]
			// 事件类型: Filter / 事件名称: OnPCGuildLeaveFilter
			// 常量名称: NPCF_GUILDLEAVE / 变量名称: guildleave_filter_name

			// 当玩家准备创建队伍时触发过滤器 [聽風]
			// 事件类型: Filter / 事件名称: OnPCPartyCreateFilter
			// 常量名称: NPCF_PARTYCREATE / 变量名称: partycreate_filter_name

			// 当玩家即将加入队伍时触发过滤器 [聽風]
			// 事件类型: Filter / 事件名称: OnPCPartyJoinFilter
			// 常量名称: NPCF_PARTYJOIN / 变量名称: partyjoin_filter_name

			// 当玩家准备离开队伍时触发过滤器 [聽風]
			// 事件类型: Filter / 事件名称: OnPCPartyLeaveFilter
			// 常量名称: NPCF_PARTYLEAVE / 变量名称: partyleave_filter_name

			// 当玩家准备丢弃或掉落道具时触发过滤器 [人鱼姬的思念]
			// 事件类型: Filter / 事件名称: OnPCDropItemFilter
			// 常量名称: NPCF_DROPITEM / 变量名称: dropitem_filter_name

			// 当玩家点击魔物墓碑时触发过滤器 [人鱼姬的思念]
			// 事件类型: Filter / 事件名称: OnPCClickTombFilter
			// 常量名称: NPCF_CLICKTOMB / 变量名称: clicktomb_filter_name

			// 当玩家准备将道具存入仓库时触发过滤器 [香草]
			// 事件类型: Filter / 事件名称: OnPCStorageAddFilter
			// 常量名称: NPCF_STORAGE_ADD / 变量名称: storage_add_filter_name

			// 当玩家准备将道具取出仓库时触发过滤器 [香草]
			// 事件类型: Filter / 事件名称: OnPCStorageDelFilter
			// 常量名称: NPCF_STORAGE_DEL / 变量名称: storage_del_filter_name

			// 当玩家准备将道具从背包存入手推车时触发过滤器 [香草]
			// 事件类型: Filter / 事件名称: OnPCCartAddFilter
			// 常量名称: NPCF_CART_ADD / 变量名称: cart_add_filter_name

			// 当玩家准备将道具从手推车取回背包时触发过滤器 [香草]
			// 事件类型: Filter / 事件名称: OnPCCartDelFilter
			// 常量名称: NPCF_CART_DEL / 变量名称: cart_del_filter_name

			// 当玩家准备将道具移入收藏栏位时触发过滤器 [香草]
			// 事件类型: Filter / 事件名称: OnPCFavoriteAddFilter
			// 常量名称: NPCF_FAVORITE_ADD / 变量名称: favorite_add_filter_name

			// 当玩家准备将道具从收藏栏位移出时触发过滤器 [香草]
			// 事件类型: Filter / 事件名称: OnPCFavoriteDelFilter
			// 常量名称: NPCF_FAVORITE_DEL / 变量名称: favorite_del_filter_name
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

		// 使 map_session_data 可记录玩家已经生成的 bonus_script 记录数 [Sola丶小克]
		// 结构体修改定位 pc.hpp -> map_session_data.pandas.bonus_script_counter
		#define Pandas_Struct_Map_Session_Data_BonusScript_Counter
	#endif // Pandas_Struct_Map_Session_Data_Pandas

	// 以下选项开关需要依赖 Pandas_Struct_Map_Session_Data_Pandas 的拓展

	// 使 item_data 有一个独立的结构体用来存放 Pandas 的拓展 [Sola丶小克]
	// 结构体修改定位 itemdb.hpp -> item_data.pandas
	#define Pandas_Struct_Item_Data_Pandas

	// 以下选项开关需要依赖 Pandas_Struct_Item_Data_Pandas 的拓展
	#ifdef Pandas_Struct_Item_Data_Pandas
		// 使 item_data 可记录当前物品的使用、穿戴、卸装脚本的原文 [Sola丶小克]
		// 结构体修改定位 itemdb.hpp -> item_data.pandas.script_plaintext
		#define Pandas_Struct_Item_Data_Script_Plaintext

		// 使 item_data 可记录当前物品可捕捉的魔物编号 [Sola丶小克]
		// 结构体修改定位 itemdb.hpp -> item_data.pandas.taming_mobid
		#define Pandas_Struct_Item_Data_Taming_Mobid

		// 使 item_data 可记录此物品的使用脚本是否执行了 callfunc 指令 [Sola丶小克]
		// 结构体修改定位 itemdb.hpp -> item_data.pandas.has_callfunc
		#define Pandas_Struct_Item_Data_Has_CallFunc

		// 使 item_data 可记录此物品的特殊属性 [Sola丶小克]
		// 效果与 item_data.flag 类似, 只是数据源为 item_properties.yml
		// 结构体修改定位 itemdb.hpp -> item_data.pandas.properties
	#endif // Pandas_Struct_Item_Data_Pandas

	// 使 npc_data 有一个独立的结构体用来存放 Pandas 的拓展 [Sola丶小克]
	// 结构体修改定位 npc.hpp -> npc_data.pandas

	// 以下选项开关需要依赖 Pandas_Struct_Npc_Data_Pandas 的拓展

	// 使 mob_data 有一个独立的结构体用来存放 Pandas 的拓展 [Sola丶小克]
	// 结构体修改定位 mob.hpp -> mob_data.pandas

	// 以下选项开关需要依赖 Pandas_Struct_Mob_Data_Pandas 的拓展

	// 对离线挂店 autotrade 的定义进行拓展处理 [Sola丶小克]
	// 进行拓展处理之后能够在代码改动较少的情况下, 更好的支持多种不同类型的 "离线挂店" 行为
	// 在默认情况下 sd->state.autotrade 的值若为 0 则表示没有离线挂店
	// 若非零的话则表示启用了离线挂店, 且 &2 表示开启的是离线摆摊挂店 &3 表示开启的是离线收购挂店

	// 对 bonus_script_data 的定义进行拓展处理 [Sola丶小克]
	// 默认的 rAthena 中 bonus_script 机制并没有唯一编号的概念, 为了提高对 bonus_script 的控制粒度
	// 我们需要将唯一编号引入到我们需要拓展的相关数据结构体中

	// 使 s_mail.item 能有一个 details 字段用来记录附件道具更详细的信息 [Sola丶小克]

	// 使 s_random_opt_data 能保存脚本的明文 [Sola丶小克]

	// 使 s_item_combo 能保存脚本的明文 [Sola丶小克]

	// 使 status_change 能保存 cloak 是否正在进行中的状态 [Sola丶小克]

	// 使 map_data 能保存全部魔物的刷新点信息 [Sola丶小克]
#endif // Pandas_StructIncrease

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
	// 是否启用 settrigger 脚本指令 [Sola丶小克]
	// 使用该指令可以设置某个事件或过滤器的触发行为 (是否触发、下次触发、永久触发)
	// 此选项开关需要依赖 Pandas_Struct_Map_Session_Data_EventTrigger 的拓展
	// 是否启用 messagecolor 脚本指令 [Sola丶小克]
	// 使用该指令可以发送指定颜色的消息文本到聊天窗口中
	// 是否启用 copynpc 脚本指令 [Sola丶小克]
	// 使用该指令可以复制指定的 NPC 到一个新的位置 (坐标等相对可以灵活设置)
	// 是否启用 gettimefmt 脚本指令 [Sola丶小克]
	// 将当前时间格式化输出成字符串, 是 gettimestr 的改进版
	// 是否启用 multicatchpet 脚本指令 [Sola丶小克]
	// 与 catchpet 指令类似, 但可以指定更多支持捕捉的魔物编号
	// 此选项开关需要依赖 Pandas_Struct_Map_Session_Data_MultiCatchTargetClass 的拓展
	// 是否启用 selfdeletion 脚本指令 [Sola丶小克]
	// 设置 NPC 的自毁策略, 用于配合 copynpc 实现在开宝箱/挖矿时进行自毁等场景
	// 是否启用 npcexists 脚本指令 [Sola丶小克]
	// 该指令用于判断指定名称的 NPC 是否存在, 就算不存在控制台也不会报错
	// 是否启用 setinventoryinfo 脚本指令 [Sola丶小克]
	// 该指令用于设置指定背包序号道具的部分详细信息, 与 getinventoryinfo 对应
	// 是否启用 updateinventory 脚本指令 [Sola丶小克]
	// 该指令用于重新下发关联玩家的背包数据给客户端 (刷新客户端背包数据)
	// 是否启用 getcharmac 脚本指令 [Sola丶小克]
	// 该指令用于获取指定角色登录时使用的 MAC 地址
	// 此选项开关需要依赖 Pandas_Extract_SSOPacket_MacAddress 的拓展
	// 是否启用 getconstant 脚本指令 [Sola丶小克]
	// 该指令用于查询一个常量字符串对应的数值
	// 是否启用 preg_search 脚本指令 [Sola丶小克]
	// 该指令用于执行一个正则表达式搜索并返回首个匹配的分组内容
	// 是否启用 aura 脚本指令 [Sola丶小克]
	// 该指令用于为角色激活特定组合的光环效果, 光环效果会一直跟随角色
	// 此选项开关需要依赖 Pandas_Aura_Mechanism 的拓展
	// 是否启用 unitaura 脚本指令 [Sola丶小克]
	// 该指令用于调整七种单位的光环组合 (但仅 BL_PC 会被持久化)
	// 七种单位分别是: 玩家/魔物/佣兵/宠物/NPC/精灵/人工生命体
	// 此选项开关需要依赖 Pandas_Aura_Mechanism 的拓展
	// 是否启用 getunittarget 脚本指令 [Sola丶小克]
	// 该指令用于获取指定单位当前正在攻击的目标单位编号
	// 是否启用 unlockcmd 脚本指令 [Sola丶小克]
	// 该指令用于解锁实时事件和过滤器事件的指令限制, 只能用于实时或过滤器事件
	#define Pandas_ScriptCommand_UnlockCmd
	// 是否启用战斗记录相关的脚本指令 [Sola丶小克]
	// 此选项开关需要依赖 Pandas_BattleRecord 的拓展
	// 是否启用 login 脚本指令 [Sola丶小克]
	// 该指令用于将指定的角色以特定的登录模式拉上线
	// 此选项开关需要依赖 Pandas_Player_Suspend_System 的拓展
	// 是否启用 checksuspend 脚本指令 [Sola丶小克]
	// 该指令用于获取指定角色或指定账号当前在线角色的挂机模式
	// 此选项开关需要依赖 Pandas_Struct_Autotrade_Extend 的拓展
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
	// 是否启用 getmobspawns 脚本指令 [Sola丶小克]
	// 该指令用于查询指定魔物在不同地图的刷新点信息
	// 此选项开关需要依赖 Pandas_Struct_Map_Data_Mob_Spawns 的拓展
	// 是否启用 getcalendartime 脚本指令 [Haru]
	// 该指令用于获取下次出现指定时间的 UNIX 时间戳
	// 是否启用 getskillinfo 脚本指令 [聽風]
	// 该指令用于获取指定技能在技能数据库中所配置的各项信息
	// 是否启用 boss_monster 脚本指令 [人鱼姬的思念]
	// 该指令用于召唤魔物并使之能被 BOSS 雷达探测 (哪怕被召唤魔物本身不是 BOSS)
	// 此选项依赖 Pandas_FuncDefine_Mob_Once_Spawn 的拓展
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
	// PYHELP - SCRIPTCMD - INSERT POINT - <Section 1>
#endif // Pandas_ScriptCommands
