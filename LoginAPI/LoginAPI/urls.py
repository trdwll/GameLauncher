from django.contrib import admin
from django.urls import path

from .views import LoginView

urlpatterns = [
    path('admin/', admin.site.urls),

    path('api/login/', LoginView.as_view())
]
