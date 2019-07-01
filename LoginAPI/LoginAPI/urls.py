from django.contrib import admin
from django.urls import path

from rest_framework.authtoken.views import obtain_auth_token

from .views import LoginView

urlpatterns = [
    path('admin/', admin.site.urls),

    path('api/login/', LoginView.as_view()),
    path('api/login/request-token/', obtain_auth_token), # Request the token for the user
]
