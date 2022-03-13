#include "table_funcs.h"

void drop_table(string table_name, connection *C) {
  string sql = "DROP TABLE IF EXISTS " + table_name + ";";
  work W(*C);
  W.exec(sql);
  W.commit();
}

void create_table(string table_name, connection *C) {
  string sql;
  if (table_name == "PLAYER") {
    sql = CREATE_PLAYER_CMD;
  } else if (table_name == "TEAM") {
    sql = CREATE_TEAM_CMD;
  } else if (table_name == "STATE") {
    sql = CREATE_STATE_CMD;
  } else if (table_name == "COLOR") {
    sql = CREATE_COLOR_CMD;
  } else {
    cerr << "Can not create table" << table_name << endl;
    return;
  }
  work W(*C);
  W.exec(sql);
  W.commit();
}

void init_table_player(string file, connection *C) {
  create_table("PLAYER", C); 
  ifstream ifs(file, ifstream::in);
  if (!ifs.is_open()) {
    cerr << "Can not open file \"" << file << "\" to init table";
    return;
  }
  string line;
  int p_id, t_id, u_id, mpg, ppg, rpg, apg;
  string f_name, l_name;
  double spg, bpg;
  while (getline(ifs, line).good()) {
    stringstream ss(line);
    ss >> p_id >> t_id >> u_id >> f_name >> l_name >> mpg >> ppg >> rpg >> apg >> spg >> bpg;
    add_player(C, t_id, u_id, f_name, l_name, mpg, ppg, rpg, apg, spg, bpg);
  }
  ifs.close();
}

void init_table_team(string file, connection *C) {
  create_table("TEAM", C); 
  ifstream ifs(file, ifstream::in);
  if (!ifs.is_open()) {
    cerr << "Can not open file \"" << file << "\" to init table";
    return;
  }
  string line;
  int t_id, s_id, c_id, win, lose;
  string name;
  while (getline(ifs, line).good()) {
    stringstream ss(line);
    ss >> t_id >> name >> s_id >> c_id >> win >> lose;
    add_team(C, name, s_id, c_id, win, lose);
  }
  ifs.close();
}

void init_table_state(string file, connection *C) {
  create_table("STATE", C); 
  ifstream ifs(file, ifstream::in);
  if (!ifs.is_open()) {
    cerr << "Can not open file \"" << file << "\" to init table";
    return;
  }
  string line;
  int s_id;
  string name;
  while (getline(ifs, line).good()) {
    stringstream ss(line);
    ss >> s_id >> name;
    add_state(C, name);
  }
  ifs.close();
}

void init_table_color(string file, connection *C) {
  create_table("COLOR", C); 
  ifstream ifs(file, ifstream::in);
  if (!ifs.is_open()) {
    cerr << "Can not open file \"" << file << "\" to init table";
    return;
  }
  string line;
  int c_id;
  string name;
  while (getline(ifs, line).good()) {
    stringstream ss(line);
    ss >> c_id >> name;
    add_color(C, name);
  }
  ifs.close();
}
