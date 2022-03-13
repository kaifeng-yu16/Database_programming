#ifndef _TABLE_FUNCS_
#define _TABLE_FUNCS_

#include <string>
#include <fstream>
#include <sstream>
#include "query_funcs.h"
#include "table_cmd.h"

using namespace std;
using namespace pqxx;

void drop_table(string table_name, connection *C);

void create_table(string table_name, connection *C);

void init_table_player(string file, connection *C);

void init_table_team(string file, connection *C);

void init_table_state(string file, connection *C);

void init_table_color(string file, connection *C);


#endif //_TABLE_FUNCS_
