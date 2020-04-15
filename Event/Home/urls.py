from . import views
from django.urls import path

urlpatterns = [
    path("", views.homepage, name="Home"),
    path("home/", views.greet, name="greet"),
    path("event/<int:id>", views.event, name="event")
]
