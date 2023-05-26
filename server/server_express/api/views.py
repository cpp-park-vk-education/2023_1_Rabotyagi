from django.shortcuts import render
from django.views import View


class IUser(View):
    @staticmethod
    def get(request):
        pass
    
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