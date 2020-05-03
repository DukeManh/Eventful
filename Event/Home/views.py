from django.views.generic.list import ListView
from django.views.generic import DetailView
from django.http import HttpResponse, Http404, HttpResponseRedirect, JsonResponse
from django.shortcuts import render, get_object_or_404, redirect, reverse
from datetime import datetime
from django.contrib.auth.decorators import login_required
from rest_framework import generics
from .serializers import EventSerializer

from Home.models import *
# Create your views here.


def homepage(request):
    events = Event.objects.all()
    context = {
        'events': events,
    }
    return HttpResponseRedirect(reverse('events'))


def event(request, id):
    """
    try:
        event = Event.objects.get(pk=id)
    except Event.DoesNotExist:
        raise Http404('Event does not exist')
    """
    event = get_object_or_404(Event, pk=id)
    context = {
        'event': event,
    }
    return render(request, "home/event.html", context=context)


class EventListView(ListView):
    model = Event
    template_name = 'home/eventListView.html'
    context_object_name = 'event_list'

    def get_queryset(self):
        return Event.objects.all()[:10]

    def get_context_data(self, **kwargs):
        context = super().get_context_data(**kwargs)
        context["currTime"] = datetime.now().time()
        visits = self.request.session.get('visits', 0)
        self.request.session['visits'] = visits + 1
        context["visits"] = visits
        return context


class EventDetailView(DetailView):
    model = Event
    template_name = 'home/eventDetailView.html'
    months = {1: 'January', 2: 'February', 3: 'March', 4: 'April', 5: 'May', 6: 'June', 7: 'July', 8: 'August', 9: 'September',
              10: 'October', 11: 'November', 12: 'December'}

    def get_context_data(self, **kwargs):
        context = super().get_context_data(**kwargs)
        context['month'] = self.months[int(context['event'].date.month)]
        return context

    def event_detail_view(request, slug):
        event = get_object_or_404(Event, slug=slug)
        return render(request, "home/eventDetailView.html")


@login_required
def booking(request):
    return HttpResponse("we're working on it")


def interested(request):
    user = request.user
    id = request.GET['id']
    event = Event.objects.get(pk=id)
    if not user in event.interested.all():
        event.interested.add(user)
        data = {
            'success': True,
            'interested': event.interested.count(),
        }
        return JsonResponse(data)
    else:
        event.interested.remove(user)
        data = {
            'success': False,
            'interested': event.interested.count(),
        }
        return JsonResponse(data)


class EventListCreate(generics.ListCreateAPIView):
    queryset = Event.objects.all()
    serializer_class = EventSerializer
