#include "query_funcs.h"


void add_player(connection *C, int team_id, int jersey_num, string first_name, string last_name,
                int mpg, int ppg, int rpg, int apg, double spg, double bpg)
{
  work W(*C);
  stringstream ss;
  ss << "INSERT INTO PLAYER (TEAM_ID, UNIFORM_NUM, FIRST_NAME, LAST_NAME, MPG, PPG, RPG, APG, SPG, BPG) VALUES (";
  ss << team_id << ", " << jersey_num << ", " << W.quote(first_name) << ", " << W.quote(last_name) << ", " 
      << mpg << ", " << ppg << ", " << rpg << ", " << apg << ", ";
  ss.setf(ios::fixed, ios::floatfield);
  ss.precision(1);
  ss << spg << ", " << bpg << ");";
  W.exec(ss.str());
  W.commit();
}


void add_team(connection *C, string name, int state_id, int color_id, int wins, int losses)
{
  work W(*C);
  stringstream ss;
  ss << "INSERT INTO TEAM (NAME, STATE_ID, COLOR_ID, WINS, LOSSES) VALUES (";
  ss << W.quote(name) << ", " << state_id << ", " << color_id << ", " << wins << ", " << losses << ");";
  W.exec(ss.str());
  W.commit();
}


void add_state(connection *C, string name)
{
  work W(*C);
  stringstream ss;
  ss << "INSERT INTO STATE (NAME) VALUES (";
  ss << W.quote(name) << ");";
  W.exec(ss.str());
  W.commit();
}


void add_color(connection *C, string name)
{
  work W(*C);
  stringstream ss;
  ss << "INSERT INTO COLOR (NAME) VALUES (";
  ss << W.quote(name) << ");";
  W.exec(ss.str());
  W.commit();
}


void query1(connection *C,
	    int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg
            )
{
  nontransaction N(*C);
  bool has_cond_before = false;
  stringstream ss;
  ss << "SELECT * FROM PLAYER";
  if (use_mpg) {
    if (has_cond_before == false) {
      ss << " WHERE ";
      has_cond_before = true;
    } else {
      ss << " AND ";
    }
    ss << "(MPG BETWEEN " << min_mpg << " AND " << max_mpg << ")";
  }
  if (use_ppg) {
    if (has_cond_before == false) {
      ss << " WHERE ";
      has_cond_before = true;
    } else {
      ss << " AND ";
    }
    ss << "(PPG BETWEEN " << min_ppg << " AND " << max_ppg << ")";
  }
  if (use_rpg) {
    if (has_cond_before == false) {
      ss << " WHERE ";
      has_cond_before = true;
    } else {
      ss << " AND ";
    }
    ss << "(RPG BETWEEN " << min_rpg << " AND " << max_rpg << ")";
  }
  if (use_apg) {
    if (has_cond_before == false) {
      ss << " WHERE ";
      has_cond_before = true;
    } else {
      ss << " AND ";
    }
    ss << "(APG BETWEEN " << min_apg << " AND " << max_apg << ")";
  }
  if (use_spg) {
    if (has_cond_before == false) {
      ss << " WHERE ";
      has_cond_before = true;
    } else {
      ss << " AND ";
    }
    ss.setf(ios::fixed, ios::floatfield);
    ss.precision(1);
    ss << "(SPG BETWEEN " << min_spg << " AND " << max_spg << ")";
  }
  if (use_bpg) {
    if (has_cond_before == false) {
      ss << " WHERE ";
      has_cond_before = true;
    } else {
      ss << " AND ";
    }
    ss.setf(ios::fixed, ios::floatfield);
    ss.precision(1);
    ss << "(BPG BETWEEN " << min_bpg << " AND " << max_bpg << ")";
  }
  ss << ";";
  result R(N.exec(ss.str()));
  // print output
  cout << "PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG\n";
  for (result::const_iterator iter = R.begin(); iter != R.end(); ++iter) {
    for (int i = 0; i < 3; ++i) {
      cout << iter[i].as<int>() << " ";
    }
    for (int i = 3; i < 5; ++i) {
      cout << iter[i].as<string>() << " ";
    }
    for (int i = 5; i < 9; ++i) {
      cout << iter[i].as<int>() << " ";
    }
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(1);
    cout << iter[9].as<double>() << " ";
    cout << iter[10].as<double>() << "\n";
  }
}


void query2(connection *C, string team_color)
{
  nontransaction N(*C);
  stringstream ss;
  ss << "SELECT T.NAME FROM TEAM as T, COLOR as C WHERE T.COLOR_ID=C.COLOR_ID AND C.NAME=";
  ss << N.quote(team_color) << ";";
  result R(N.exec(ss.str()));
  // print result
  cout << "NAME\n";
  for (result::const_iterator iter = R.begin(); iter != R.end(); ++iter) {
    cout << iter[0].as<string>() << "\n";
  }
}


void query3(connection *C, string team_name)
{
  nontransaction N(*C);
  stringstream ss;
  ss << "SELECT FIRST_NAME, LAST_NAME FROM PLAYER as P, TEAM as T ";
  ss << "WHERE P.TEAM_ID=T.TEAM_ID AND T.NAME=";
  ss << N.quote(team_name) << " ";
  ss << "ORDER BY P.PPG DESC;";
  result R(N.exec(ss.str()));
  // print result
  cout << "FIRST_NAME LAST_NAME\n";
  for (result::const_iterator iter = R.begin(); iter != R.end(); ++iter) {
    cout << iter[0].as<string>() << " ";
    cout << iter[1].as<string>() << "\n";
  }
}


void query4(connection *C, string team_state, string team_color)
{
  nontransaction N(*C);
  stringstream ss;
  ss << "SELECT FIRST_NAME, LAST_NAME, UNIFORM_NUM FROM PLAYER AS P, STATE AS S, COLOR AS C, TEAM AS T ";
  ss << "WHERE P.TEAM_ID=T.TEAM_ID AND T.STATE_ID=S.STATE_ID AND T.COLOR_ID=C.COLOR_ID AND ";
  ss << "C.NAME=" << N.quote(team_color) << " AND ";
  ss << "S.NAME=" << N.quote(team_state) << ";";
  result R(N.exec(ss.str()));
  // print result
  cout << "FIRST_NAME LAST_NAME UNIFORM_NUM\n";
  for (result::const_iterator iter = R.begin(); iter != R.end(); ++iter) {
    cout << iter[0].as<string>() << " ";
    cout << iter[1].as<string>() << " ";
    cout << iter[2].as<int>() << "\n";
  }
}


void query5(connection *C, int num_wins)
{
  nontransaction N(*C);
  stringstream ss;
  ss << "SELECT P.FIRST_NAME, P.LAST_NAME, T.NAME, T.WINS FROM PLAYER AS P, TEAM AS T ";
  ss << "WHERE P.TEAM_ID=T.TEAM_ID AND T.WINS>" << num_wins << ";";
  result R(N.exec(ss.str()));
  // print result
  cout << "FIRST_NAME LAST_NAME NAME WINS\n";
  for (result::const_iterator iter = R.begin(); iter != R.end(); ++iter) {
    cout << iter[0].as<string>() << " ";
    cout << iter[1].as<string>() << " ";
    cout << iter[2].as<string>() << " ";
    cout << iter[3].as<int>() << "\n";
  }
}
