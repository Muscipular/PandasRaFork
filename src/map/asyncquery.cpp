#include "asyncquery.hpp"

#include "log.hpp"
#include "map.hpp"

#include <common/future.hpp>
#include <common/showmsg.hpp>
#include <common/strlib.hpp>

#include <chrono>
#include <cstdlib>
#include <thread>

using namespace std;
using namespace rathena::server_core;

extern int map_server_port;
extern std::string map_server_ip;
extern std::string map_server_id;
extern std::string map_server_pw;
extern std::string map_server_db;

extern uint16 log_db_port;
extern std::string log_db_ip;
extern std::string log_db_id;
extern std::string log_db_pw;
extern std::string log_db_db;

size_t DBResultData::Index(size_t Row, size_t Column) {
	return Row * ColumnNum + Column;
}

const char* DBResultData::GetData(size_t Row, size_t Column) {
	return data.at(Index(Row, Column)).c_str();
}

void DBResultData::SetData(size_t Row, size_t Column, Sql* handle) {
	char* sql_data = nullptr;
	Sql_GetData(handle, Column, &sql_data, nullptr);
	data.at(Index(Row, Column)) = sql_data ? sql_data : "";
}

int8 DBResultData::GetInt8(size_t Row, size_t Column) {
	return atoi(GetData(Row, Column));
}

uint8 DBResultData::GetUInt8(size_t Row, size_t Column) {
	return atoi(GetData(Row, Column));
}

int16 DBResultData::GetInt16(size_t Row, size_t Column) {
	return atoi(GetData(Row, Column));
}

uint16 DBResultData::GetUInt16(size_t Row, size_t Column) {
	return atoi(GetData(Row, Column));
}

int32 DBResultData::GetInt32(size_t Row, size_t Column) {
	return atoi(GetData(Row, Column));
}

uint32 DBResultData::GetUInt32(size_t Row, size_t Column) {
	return strtoul(GetData(Row, Column), nullptr, 10);
}

int64 DBResultData::GetInt64(size_t Row, size_t Column) {
	return strtoll(GetData(Row, Column), nullptr, 10);
}

uint64 DBResultData::GetUInt64(size_t Row, size_t Column) {
	return strtoull(GetData(Row, Column), nullptr, 10);
}

thread* db_thread = nullptr;
Sql* MainDBHandle = nullptr;
Sql* LogDBHandle = nullptr;

JobQueue<dbJob> dbJobs;

Sql* getHandle(dbType type) {
	switch (type) {
		default:
		case dbType::MAIN_DB:
			return MainDBHandle;
		case dbType::LOG_DB:
			return LogDBHandle;
	}
}

void asyncquery_addDBJob(dbType dType, string query, futureJobFunc resultFunc) {
	dbJobs.push_back({ dType, query, resultFunc });
}

void asyncquery_addDBJob(dbType dType, string query) {
	dbJobs.push_back({ dType, query, nullptr });
}

void doQuery(dbJob& job) {
	Sql* handle = getHandle(job.dType);
	int sql_result_value;

	if (SQL_ERROR == (sql_result_value = Sql_QueryStr(handle, job.query.c_str()))) {
		Sql_ShowDebug(handle);

		if (job.resultFunc) {
			DBResultData* r = new DBResultData(0, 0, 0);
			r->sql_result_value = sql_result_value;
			future_add(job.resultFunc, (FutureData)r);
		}
	} else if (job.resultFunc) {
		DBResultData* r = new DBResultData(
			(size_t)Sql_NumRows(handle),
			(size_t)Sql_NumColumns(handle),
			(size_t)Sql_NumRowsAffected(handle)
		);

		r->sql_result_value = sql_result_value;

		for (size_t Row = 0; Row < r->RowNum && SQL_SUCCESS == Sql_NextRow(handle); Row++)
			for (size_t ColumnNum = 0; ColumnNum < r->ColumnNum; ColumnNum++)
				r->SetData(Row, ColumnNum, handle);

		future_add(job.resultFunc, (FutureData)r);
	}

	Sql_FreeResult(handle);
}

void db_runtime(void) {
	while (global_core->is_running()) {
		this_thread::sleep_for(chrono::milliseconds(50));

		dbJobs.Run([](dbJob& job) {
			doQuery(job);
		});
	}
}

void asyncquery_init(void) {
	MainDBHandle = Sql_Malloc();

	ShowInfo("Connecting to the Map DB Server(async thread)....\n");
	if (SQL_ERROR == Sql_Connect(MainDBHandle, map_server_id.c_str(), map_server_pw.c_str(), map_server_ip.c_str(), map_server_port, map_server_db.c_str())) {
		ShowError("Couldn't connect with uname='%s',passwd='%s',host='%s',port='%d',database='%s'\n",
			map_server_id.c_str(), map_server_pw.c_str(), map_server_ip.c_str(), map_server_port, map_server_db.c_str());
		Sql_ShowDebug(MainDBHandle);
		Sql_Free(MainDBHandle);
		exit(EXIT_FAILURE);
	}
	ShowStatus("Connect success! (Map DB Server(async thread) Connection)\n");

	if (log_config.sql_logs) {
		LogDBHandle = Sql_Malloc();

		ShowInfo("Connecting to the Log DB Server(async thread)....\n");
		if (SQL_ERROR == Sql_Connect(LogDBHandle, log_db_id.c_str(), log_db_pw.c_str(), log_db_ip.c_str(), log_db_port, log_db_db.c_str())) {
			ShowError("Couldn't connect with uname='%s',passwd='%s',host='%s',port='%d',database='%s'\n",
				log_db_id.c_str(), log_db_pw.c_str(), log_db_ip.c_str(), log_db_port, log_db_db.c_str());
			Sql_ShowDebug(LogDBHandle);
			Sql_Free(LogDBHandle);
			exit(EXIT_FAILURE);
		}

		ShowStatus("Connect success! (Log DB Server(async thread) Connection)\n");
	}

	db_thread = new thread(db_runtime);
}

void asyncquery_final(void) {
	db_thread->join();

	ShowStatus("Close Map DB Server(async thread) Connection....\n");
	Sql_Free(MainDBHandle);
	MainDBHandle = nullptr;
	if (log_config.sql_logs) {
		ShowStatus("Close Log DB Server(async thread) Connection....\n");
		Sql_Free(LogDBHandle);
		LogDBHandle = nullptr;
	}
}
