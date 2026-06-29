#pragma once

	#define Pandas_Basic
	#define Pandas_StructIncrease
	#define Pandas_ScriptEngine

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

		// 使 map_session_data 可记录事件触发请求 [Sola丶小克]
		// 结构体修改定位 pc.hpp -> map_session_data.pandas.eventtrigger

		// 使 map_session_data 可记录当前是否正在进行护身符能力计算 [Sola丶小克]
		// 结构体修改定位 pc.hpp -> map_session_data.pandas.amulet_calculating

		// 使 map_session_data 可记录即将支持捕捉的多个魔物编号 [Sola丶小克]

		// 使 map_session_data 可记录接下来的 pc_setpos 调用是不是一次多人传送 [Sola丶小克]
		// 结构体修改定位 pc.hpp -> map_session_data.pandas.multitransfer

		// 使 map_session_data 可记录是否在 LoadEndAck 调用中不弹出队列中的事件 [Sola丶小克]
		// 结构体修改定位 pc.hpp -> map_session_data.pandas.skip_loadendack_npc_event_dequeue

		// 使 map_session_data 可记录离线挂店 / 挂机角色的朝向等状态数据 [Sola丶小克]
		// rAthena 使用完成 autotrade 的朝向数据后就销毁掉了
		// 为了能够支持离线挂店 / 挂机可以被 recall 召唤, 我们需要保留一部分数据

		// 使 map_session_data 可记录玩家已经生成的 bonus_script 记录数 [Sola丶小克]
		// 结构体修改定位 pc.hpp -> map_session_data.pandas.bonus_script_counter
	#endif // Pandas_Struct_Map_Session_Data_Pandas

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

// ============================================================================
// 脚本引擎修改组 - Pandas_ScriptEngine
// ============================================================================

#ifdef Pandas_ScriptEngine
	// 使脚本引擎能够支持穿越事件队列机制, 直接执行某些事件 [Sola丶小克]

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
