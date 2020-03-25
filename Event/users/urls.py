from django.urls import path
from . import views


urlpatterns = [
    path("index", views.index, name="index"),
    path("", views.index, name="index"),
    path("login", views.login_view, name="login"),
    path("signup", views.signup_view, name="signup"),
    path("logout", views.logout_view, name="logout")
]
