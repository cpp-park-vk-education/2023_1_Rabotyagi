from django.contrib import admin
from django.urls import path, include
from .views import *

urlpatterns = [
    path('IUser', IUser.as_view()),
    path('IUser/guild', getUserGuilds),
    path('IMessage', IMessage.as_view()),
    path('IGuild', IGuild.as_view()),
    path('IGuild/join', join),
    path('IChannel', IChannel.as_view()),
]