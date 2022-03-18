import os
import django
from django.db import connection

os.environ.setdefault("DJANGO_SETTINGS_MODULE", "mydatabase.settings")
django.setup()

# your imports, e.g. Django models
from ACC_BBALL.models import *
from exerciser import exercise
from query_funcs import *

def delete_players():
  if 'ACC_BBALL_player' in connection.introspection.table_names():
    PLAYER.objects.all().delete()

def delete_teams():
  if 'ACC_BBALL_team' in connection.introspection.table_names():
    TEAM.objects.all().delete()

def delete_states():
  if 'ACC_BBALL_state' in connection.introspection.table_names():
    STATE.objects.all().delete()

def delete_colors():
  if 'ACC_BBALL_color' in connection.introspection.table_names():
    COLOR.objects.all().delete()

def add_players(file):
  f = open(file, "r")
  for line in f:
    p_id,t_id,u_id,f_name,l_name,mpg,ppg,rpg,apg,spg,bpg = line.split(' ')
    add_player(p_id, t_id, u_id, f_name, l_name, mpg, ppg, rpg, apg, spg, bpg)

def add_teams(file):
  f = open(file, "r")
  for line in f:
    t_id,name,s_id,c_id,win,lose = line.split(' ')
    add_team(t_id, name, s_id, c_id, win, lose)
  
def add_states(file):
  f = open(file, "r")
  for line in f:
    s_id,name = line.split(' ')
    add_state(s_id, name[0:-1])
  
def add_colors(file):
  f = open(file, "r")
  for line in f:
    c_id,name = line.split(' ')
    add_color(c_id, name[0:-1])


if __name__ == "__main__":
  delete_players()
  delete_teams()
  delete_states()
  delete_colors()
  add_states("state.txt")
  add_colors("color.txt")
  add_teams("team.txt")
  add_players("player.txt")
  exercise()


