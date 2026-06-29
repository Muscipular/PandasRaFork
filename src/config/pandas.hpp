#pragma once

	#define Pandas_Basic
	#define Pandas_StructIncrease

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

	// 以下选项开关需要依赖 Pandas_Struct_Unit_CommonData 的拓展

	// 使 map_session_data 有一个独立的结构体用来存放 Pandas 的拓展 [Sola丶小克]
	// 结构体修改定位 pc.hpp -> map_session_data.pandas

	// 以下选项开关需要依赖 Pandas_Struct_Map_Session_Data_Pandas 的拓展

	// 使 item_data 有一个独立的结构体用来存放 Pandas 的拓展 [Sola丶小克]
	// 结构体修改定位 itemdb.hpp -> item_data.pandas

	// 以下选项开关需要依赖 Pandas_Struct_Item_Data_Pandas 的拓展

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
