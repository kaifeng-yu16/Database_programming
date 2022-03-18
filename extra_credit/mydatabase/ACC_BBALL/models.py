from django.db import models

# Create your models here.

class STATE(models.Model):
  STATE_ID = models.AutoField(primary_key = True)
  NAME = models.TextField()

class COLOR(models.Model): 
  COLOR_ID = models.AutoField(primary_key = True)
  NAME = models.TextField()

class TEAM(models.Model):
  TEAM_ID = models.AutoField(primary_key = True)
  NAME = models.TextField()
  STATE_ID = models.ForeignKey(STATE, on_delete=models.SET_NULL, null=True)
  COLOR_ID = models.ForeignKey(COLOR, on_delete=models.SET_NULL, null=True)
  WINS = models.IntegerField() 
  LOSSES = models.IntegerField()


class PLAYER(models.Model):
  PLAYER_ID = models.AutoField(primary_key = True)
  TEAM_ID = models.ForeignKey(TEAM, on_delete=models.SET_NULL, null=True)
  UNIFORM_NUM = models.TextField()
  FIRST_NAME = models.TextField()
  LAST_NAME = models.TextField()
  MPG = models.IntegerField()
  PPG = models.IntegerField()
  RPG = models.IntegerField()
  APG = models.IntegerField()
  SPG = models.FloatField()
  BPG = models.FloatField()

