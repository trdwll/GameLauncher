from django.views.generic import View, ListView
from django.shortcuts import render, get_object_or_404, get_list_or_404
from django.http import JsonResponse
from django.contrib.auth.models import User
from django.utils.decorators import method_decorator
from django.views.decorators.csrf import csrf_exempt

from django.contrib.auth import authenticate

from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework.permissions import IsAuthenticated 


class LoginView(APIView):
    permission_classes = (IsAuthenticated, )

    def get(self, request):
        json = {'status': 'Ok', 'msg': 'User authenticated', 'loggedin': True}
        return Response(json)
