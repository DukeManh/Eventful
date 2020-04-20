from . import views
from django.urls import path

urlpatterns = [
    path("", views.EventListView.as_view(), name="home"),
    path("events/", views.EventListView.as_view(), name="events"),
    path("events/<int:pk>", views.EventDetailView.as_view(), name="event-detail"),

]
