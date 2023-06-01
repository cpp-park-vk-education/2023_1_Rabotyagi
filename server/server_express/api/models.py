from django.db import models
from django.db.models.signals import *
from django.contrib.auth.models import User
from datetime import date
from django.db.models.signals import post_save, pre_delete, post_delete
from django.dispatch import receiver

channel_types = (
    ('voice', 'Голосовой'),
    ('text', 'Текстовый')
)


class MessageManager(models.Manager):
    def has_new(self, pk: int):
        pass


class ChannelManager(models.Manager):
    def get_messages_dict(self, instance: models.Model):
        messages = instance.messages.all()
        result = [
            {
                'id': msg.id,
                'owner': msg.owner.username,
                'channel': instance.id,
                'content': msg.content,
            } for msg in messages
        ]
        return result


class GuildManager(models.Manager):
    def get_channels(self, instance: models.Model):
        channels = instance.channels.all()
        result = [
            {
                "id": channel.id,
                "name": channel.name
            } for channel in channels
        ]
        return result
    
    # def get_user_guilds(self, instance: models.Model):
    #     Guild.manager


class Guild(models.Model):
    owner = models.ForeignKey(User, models.CASCADE, related_name='owned_guild')
    name = models.CharField(max_length=100, unique=True)
    users = models.ManyToManyField(User, related_name='guilds')
    user_count = models.IntegerField(default=1)
    created_at = models.DateField(default=date.today)
    
    manager = GuildManager()
    
    def __str__(self) -> str:
        return self.name


@receiver(post_save, sender=Guild)
def create_section_group(sender, instance, **kwargs):
    instance.users.add(instance.owner)


class Channel(models.Model):
    guild = models.ForeignKey(Guild, models.CASCADE, related_name='channels')
    name = models.CharField(max_length=100)
    type = models.CharField(choices=channel_types, default='text')
    created_at = models.DateField(default=date.today)
    updated_at = models.DateField(default=date.today)
    
    manager = ChannelManager()
    
    def __str__(self) -> str:
        return self.name


class Message(models.Model):
    owner = models.ForeignKey(User, models.CASCADE, related_name='messages')
    channel = models.ForeignKey(Channel, models.CASCADE, related_name='messages')
    content = models.TextField()
    created_at = models.DateField(default=date.today)
    updated_at = models.DateField(default=date.today)
    
    manager = MessageManager()

    def __str__(self) -> str:
        return f'{self.channel}, id:{self.id}'