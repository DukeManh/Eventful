from . import views
from django.urls import path

urlpatterns = [
    path("", views.homepage, name="Home"),
    path("home/", views.homepage, name="greet"),
    path("home/<str:name>", views.greet, name="greet"),
    path("test/", views.test, name="test")
]
