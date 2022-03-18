import os
import django

os.environ.setdefault("DJANGO_SETTINGS_MODULE", "mydatabase.settings")
django.setup()

# your imports, e.g. Django models
from ACC_BBALL.models import *

def query1(use_mpg, min_mpg, max_mpg,\
           use_ppg, min_ppg, max_ppg,\
           use_rpg, min_rpg, max_rpg,\
           use_apg, min_apg, max_apg,\
           use_spg, min_spg, max_spg,\
           use_bpg, min_bpg, max_bpg):
  objs = PLAYER.objects.all()
  if (use_mpg == 1):
    objs = objs.filter(MPG__gte=min_mpg, MPG__lte=max_mpg)
  if (use_ppg == 1):
    objs = objs.filter(PPG__gte=min_ppg, PPG__lte=max_ppg)
  if (use_rpg == 1):
    objs = objs.filter(RPG__gte=min_rpg, RPG__lte=max_rpg)
  if (use_apg == 1):
    objs = objs.filter(APG__gte=min_apg, APG__lte=max_apg)
  if (use_spg == 1):
    objs = objs.filter(SPG__gte=min_spg, SPG__lte=max_spg)
  if (use_bpg == 1):
    objs = objs.filter(BPG__gte=min_bpg, BPG__lte=max_bpg)
  
  print("PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG")
  for obj in objs:
    print(obj.PLAYER_ID, obj.TEAM_ID.TEAM_ID, obj.UNIFORM_NUM, obj.FIRST_NAME, obj.LAST_NAME, \
        obj.MPG, obj.PPG, obj.RPG, obj.APG, obj.SPG, obj.BPG)

def query2(team_color):
  objs = TEAM.objects.filter(COLOR_ID__NAME=team_color)
  print("NAME")
  for obj in objs:
    print(obj.NAME)

def query3(team_name):
  objs = PLAYER.objects.filter(TEAM_ID__NAME=team_name).order_by('-PPG')
  print("FIRST_NAME LAST_NAME")
  for obj in objs:
    print(obj.FIRST_NAME, obj.LAST_NAME)

def query4(team_state, team_color):
  objs = PLAYER.objects.filter(TEAM_ID__STATE_ID__NAME=team_state).filter(TEAM_ID__COLOR_ID__NAME=team_color)
  print("UNIFORM_NUM FIRST_NAME LAST_NAME")
  for obj in objs:
    print(obj.UNIFORM_NUM, obj.FIRST_NAME, obj.LAST_NAME)

def query5(num_wins):
  objs = PLAYER.objects.filter(TEAM_ID__WINS__gt=num_wins)
  print("FIRST_NAME LAST_NAME NAME WINS")
  for obj in objs:
    print(obj.FIRST_NAME, obj.LAST_NAME, obj.TEAM_ID.NAME, obj.TEAM_ID.WINS)

def add_player(p_id, t_id, u_id, f_name, l_name, mpg, ppg, rpg, apg, spg, bpg):
  if not PLAYER.objects.filter(PLAYER_ID=p_id).exists():
    obj = PLAYER.objects.create(PLAYER_ID=p_id, UNIFORM_NUM=u_id,FIRST_NAME=f_name,LAST_NAME=l_name,MPG=mpg,PPG=ppg,RPG=rpg,APG=apg,SPG=spg,BPG=bpg)
    obj.TEAM_ID = TEAM.objects.get(TEAM_ID=t_id)
    obj.save()
  else:
    print("Can not add player!")

def add_team(t_id, name, s_id, c_id, win, lose):
  if not TEAM.objects.filter(TEAM_ID=t_id).exists():
    obj = TEAM.objects.create(TEAM_ID=t_id, NAME=name, WINS=win, LOSSES=lose)
    obj.STATE_ID = STATE.objects.get(STATE_ID=s_id)
    obj.COLOR_ID = COLOR.objects.get(COLOR_ID=c_id)
    obj.save()
  else:
    print("Can not add team!")

def add_state(s_id, name):
  if not STATE.objects.filter(STATE_ID=s_id).exists():
    obj = STATE.objects.create(STATE_ID=s_id, NAME=name)
    obj.save()
  else:
    print("Can not add state!")

  
def add_color(c_id, name):
  if not COLOR.objects.filter(COLOR_ID=c_id).exists():
    obj = COLOR.objects.create(COLOR_ID=c_id, NAME=name)
    obj.save()
  else:
    print("Can not add color!")
