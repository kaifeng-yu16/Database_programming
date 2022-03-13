#include <iostream>
#include <pqxx/pqxx>

#include "exerciser.h"
#include "query_funcs.h"
#include "table_funcs.h"

using namespace std;
using namespace pqxx;



int main (int argc, char *argv[]) 
{

  //Allocate & initialize a Postgres connection object
  connection *C;

  try{
    //Establish a connection to the database
    //Parameters: database name, user name, user password
    C = new connection("dbname=ACC_BBALL user=postgres password=passw0rd");
    if (C->is_open()) {
      cout << "Opened database successfully: " << C->dbname() << endl;
    } else {
      cout << "Can't open database" << endl;
      return 1;
    }
  } catch (const std::exception &e){
    cerr << e.what() << std::endl;
    return 1;
  }


  //TODO: create PLAYER, TEAM, STATE, and COLOR tables in the ACC_BBALL database
  //      load each table with rows from the provided source txt files
  try{
    drop_table("PLAYER", C);
    drop_table("TEAM", C);
    drop_table("STATE", C);
    drop_table("COLOR", C);
    init_table_state("state.txt", C);
    init_table_color("color.txt", C);
    init_table_team("team.txt", C);
    init_table_player("player.txt", C);
  }
  catch (const pqxx::pqxx_exception & e) {
    cerr << e.base().what() << std::endl;
    return 1;
  }
  catch (const std::exception &e){
    cerr << e.what() << std::endl;
    return 1;
  }

  exercise(C);
  //Close database connection
  C->disconnect();

  return 0;
}


