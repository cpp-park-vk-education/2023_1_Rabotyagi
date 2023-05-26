from django.db import models
from django.db.models.signals import *
from django.contrib.auth.models import User
from datetime import date


channel_types = (
    ('voice', 'Голосовой'),
    ('text', 'Текстовый')
)


class MessageManager(models.Manager):
    def has_new(self, pk: int):
        pass


class ChannelManager(models.Manager):
    pass


class GuildManager(models.Manager):
    pass


class Guild(models.Model):
    owner = models.ForeignKey(User, models.CASCADE, related_name='owned_guild')
    name = models.CharField(max_length=100)
    user_count = models.IntegerField(default=0)
    created_at = models.DateField(default=date.today)
    
    manager = GuildManager()


class Channel(models.Model):
    guild = models.ForeignKey(Guild, models.CASCADE, related_name='channels')
    name = models.CharField(max_length=100)
    type = models.CharField(choices=channel_types, default='text')
    created_at = models.DateField(default=date.today)
    updated_at = models.DateField(blank=True, null=True)
    
    manager = ChannelManager()


class Message(models.Model):
    owner = models.ForeignKey(User, models.CASCADE, related_name='messages')
    channel = models.ForeignKey(Channel, models.CASCADE, related_name='messages')
    content = models.TextField()
    created_at = models.DateField(default=date.today)
    updated_at = models.DateField(blank=True, null=True)
    
    manager = MessageManager()
