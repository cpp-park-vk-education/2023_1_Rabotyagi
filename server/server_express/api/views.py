from django.shortcuts import render
from django.views import View
from django.http.response import HttpResponse, JsonResponse
from .models import *
from django.contrib.auth.hashers import check_password


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
        pass
    
    @staticmethod
    def patch(request):
        pass


class IChannel(View):
    @staticmethod
    def get(request):
        pass
    
    @staticmethod
    def post(request):
        pass
    
    @staticmethod
    def patch(request):
        pass


class IMessage(View):
    @staticmethod
    def get(request):
        pass
    
    @staticmethod
    def post(request):
        pass
    
    @staticmethod
    def patch(request):
        pass


class IGuild(View):
    @staticmethod
    def get(request):
        pass
    
    @staticmethod
    def post(request):
        pass
    
    @staticmethod
    def patch(request):
        pass