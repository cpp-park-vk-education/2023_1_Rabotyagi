from django.contrib import admin
from .models import *

# Register your models here.
@admin.register(Channel)
class ChannelAdmin(admin.ModelAdmin):
    list_display = ('id', 'name', 'guild')
    search_fields = ('guild', 'name' ,)
    
@admin.register(Message)
class MessageAdmin(admin.ModelAdmin):
    list_display = ('owner', 'channel')
    # search_fields = ('paper__title', 'paper__id' ,)

@admin.register(Guild)
class GuildAdmin(admin.ModelAdmin):
    list_display = ('id', 'name', 'owner',)