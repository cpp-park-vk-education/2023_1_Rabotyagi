from django.shortcuts import render
from django.views import View
from django.http.response import HttpResponse, JsonResponse
from .models import *
from django.contrib.auth.hashers import check_password, make_password


class IUser(View):
    @staticmethod
    def get(request):
        username = request.GET.get('username', None)
        password = request.GET.get('password', None)
        
        if not username:
            return JsonResponse({
                'message': "Отсутствует username"
            }, status=400)
        
        if not password:
            return JsonResponse({
                'message': "Отсутствует password"
            }, status=400)
        
        try:
            user = User.objects.get(username=username)
            if check_password(password, user.password):
                return JsonResponse({
                    'id': user.pk,
                    'name': username,
                    'email': user.email,
                    'password': password,
                    'last_login': user.last_login
                }, status=200)
            else:
                return JsonResponse({
                    'message': "Неправильный пароль"
                }, status=400)
                
        except User.DoesNotExist:
            return JsonResponse({
                'message': f"Отсутствует User с {username}"
            }, status=400)
        
    @staticmethod
    def post(request):
        username = request.POST.get('username', None)
        password = request.POST.get('password', None)
        email = request.POST.get('email', None)
        
        if not username:
            return JsonResponse({
                'message': "Отсутствует username"
            }, status=400)
        
        if not password:
            return JsonResponse({
                'message': "Отсутствует password"
            }, status=400)
            
        if not email:
            return JsonResponse({
                'message': "Отсутствует email"
            }, status=400)
            
        try:
            user = User.objects.get(username=username)
            return JsonResponse({
                'message': f"User with {username} already exists"
            }, status=400)
        except User.DoesNotExist:
            user = User.objects.create(
                username = username,
                email = email,
                password = make_password(password)
            )
            return JsonResponse({
                    'id': user.pk,
                    'name': username,
                    'email': user.email,
                    'password': password,
                    'last_login': user.last_login
                }, status=200)


class IChannel(View):
    @staticmethod
    def get(request):
        channel_id = request.GET.get('channel_id', None)
        
        if not channel_id:
            return JsonResponse({
                'message': "Отсутствует channel_id"
            }, status=400)
        
        try:
            channel = Channel.manager.get(id=channel_id)
        except Channel.DoesNotExist:
            return JsonResponse({
                'message': f"Отсутствует channel с {channel_id}"
            }, status=400)
            
        messages = Channel.manager.get_messages_dict(channel)
        return JsonResponse({
            'id': channel.id,
            'name': channel.name,
            'type': channel.type,
            'created_at': channel.created_at,
            'updated_at': channel.updated_at,
            'messages': messages
            }, status=200)
    
    @staticmethod
    def post(request):
        guild_id = request.POST.get('guild_id', None)
        name = request.POST.get('name', None)
        # type = request.POST.get('type', None)
        
        if not guild_id:
            return JsonResponse({
                'message': "Отсутствует guild_id"
            }, status=400)
            
        if not name:
            return JsonResponse({
                'message': "Отсутствует name"
            }, status=400)
        
        try:
            guild = Guild.manager.get(id=guild_id)
        except Guild.DoesNotExist:
            return JsonResponse({
                'message': f"Отсутствует guild с {guild_id}"
            }, status=400)
        
        channel = Channel.manager.create(
            guild = guild,
            name = name
        )
        
        return JsonResponse({
            'id': channel.id,
            'name': channel.name,
            'type': channel.type,
            'created_at': channel.created_at,
            'updated_at': channel.updated_at,
            # 'messages': channel.messages
            }, status=200)


class IMessage(View):
    @staticmethod
    def get(request):
        pass
    
    @staticmethod
    def post(request):
        content = request.POST.get('content', None)
        channel_id = request.POST.get('channel_id', None)
        owner_id = request.POST.get('owner_id', None)
        
        if not owner_id:
            return JsonResponse({
                'message': "Отсутствует owner id"
            }, status=400)
            
        if not channel_id:
            return JsonResponse({
                'message': "Отсутствует channel id"
            }, status=400)
            
        if not content:
            return JsonResponse({
                'message': "Отсутствует content"
            }, status=400)
        
        try:
            channel = Channel.manager.get(id=channel_id)
        except Channel.DoesNotExist:
            return JsonResponse({
                'message': f"Отсутствует channel с {channel_id}"
            }, status=400)
            
        try:
            owner = User.objects.get(id=owner_id)
        except User.DoesNotExist:
            return JsonResponse({
                'message': f"Отсутствует user с {owner_id}"
            }, status=400)
        
        Message.manager.create(
            owner = owner,
            channel=channel,
            content=content
        )
        
        return JsonResponse({}, status=200)


class IGuild(View):
    @staticmethod
    def get(request):
        guild_id = request.GET.get('guild_id', None)

        if not guild_id:
            return JsonResponse({
                'message': "Отсутствует id для guild"
            }, status=400)
        
        guild = Guild.manager.get(id=guild_id)
        return JsonResponse({
            'id': guild.id,
            'name': guild.name,
            # 'owner': guild.owner,
            'user_count': guild.user_count,
            'created_at': guild.created_at
            }, status=200)
        
    @staticmethod
    def post(request):
        owner_id = request.POST.get('owner_id', None)
        guild_name = request.POST.get('guild_name', None)
        
        if not owner_id:
            return JsonResponse({
                'message': "Отсутствует owner_id"
            }, status=400)
            
        if not guild_name:
            return JsonResponse({
                'message': "Отсутствует name"
            }, status=400)
        
        try:
            owner = User.objects.get(id=owner_id)
        except User.DoesNotExist:
            return JsonResponse({
                'message': f"Отсутствует owner c {owner_id}"
            }, status=400)
        
        guild = Guild.manager.create(
            owner = owner,
            name=guild_name,
            user_count=1
        )
        return JsonResponse({
            'id': guild.id,
            'name': guild.name,
            # 'owner': 
            'user_count': guild.user_count,
            'created_at': guild.created_at
            }, status=200)
