from django.views.generic.list import ListView
from django.views.generic import DetailView
from django.http import HttpResponse, Http404, HttpResponseRedirect
from django.shortcuts import render, get_object_or_404, redirect, reverse
from datetime import datetime
from django.contrib.auth.decorators import login_required

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

    def event_detail_view(request, pk):
        event = get_object_or_404(Event, pk=pk)
        return render(request, "home/eventDetailView.html", context={'event': event})
