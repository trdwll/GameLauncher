from django.views.generic import View, ListView
from django.shortcuts import render, get_object_or_404, get_list_or_404
from django.http import JsonResponse
from django.contrib.auth.models import User
from django.utils.decorators import method_decorator
from django.views.decorators.csrf import csrf_exempt

from django.contrib.auth import authenticate


@method_decorator(csrf_exempt, name='dispatch')
class LoginView(View):

    def get(self, request):
        return JsonResponse({'status': 'Error', 'msg': 'GET requests not allowed here.'})

    def post(self, request):

        username = request.POST.get('username')
        password = request.POST.get('password')


        # The current method of validation shouldn't be used in production since we're passing the password to the server via plaintext and not hashed
        json = {}
        user = authenticate(username=username, password=password)
        if user is not None and user.is_active:
            json = {'status': 'Ok', 'msg': 'User authenticated', 'loggedin': True}
        else:
            json = {'status': 'Error', 'msg': 'User not authenticated', 'loggedin': False}


        return JsonResponse(json)