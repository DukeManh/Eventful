from django.http import HttpResponse
from django.shortcuts import render
from Home.models import *

# Create your views here.


def index(request):
    return HttpResponse("Under development sorry")


def greet(request):
    return render(request, "home/List.html", {
        "fruits": ["kiwi", "jackfruit", "mango"],
    })


def homepage(request):
    events = Event.objects.all()
    context = {
        'admin': 'Chris',
        'events': events,
    }
    return render(request, "home/index.html", context=context)


def event(request, id):
    try:
        event = Event.objects.get(pk=id)
    except Event.DoesNotExist:
        event = None
    context = {
        'event': event,
    }
    return render(request, "home/event.html", context=context)
