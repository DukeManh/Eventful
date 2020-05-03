from . import views
from django.urls import path

urlpatterns = [
    path("", views.EventListView.as_view(), name="home"),
    path("events/", views.EventListView.as_view(), name="events"),
    path("booking/", views.booking, name="booking"),
    path("events/<slug:slug>/",
         views.EventDetailView.as_view(), name="event-detail"),
    path("ajax/interested/", views.interested, name="interested"),
    path("api/events/", views.EventListCreate.as_view(), name="events-api"),
]
