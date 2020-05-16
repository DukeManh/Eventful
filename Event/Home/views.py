from django.views.generic.list import ListView
from django.views.generic import DetailView
from django.http import HttpResponse, Http404, HttpResponseRedirect, JsonResponse
from django.shortcuts import render, get_object_or_404, redirect, reverse
import calendar
from datetime import datetime, date
# built-in django authetication
from django.contrib.auth.decorators import login_required
from rest_framework import generics
from .serializers import EventSerializer
from django.db.models import Avg, Max, Min  # django aggregate functionss
from .models import *
# django API for handling uploaded file, save file to system storage
from django.core.files.storage import FileSystemStorage
# Create your views here.


class EventListView(ListView):
    # class-based view displaying all available events
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

    def get_context_data(self, **kwargs):
        context = super().get_context_data(**kwargs)
        context['month'] = calendar.month_abbr[int(
            context['event'].date.month)]
        if context['event'].ticketOptions.count() > 0:
            context['maxPrice'] = context['event'].ticketOptions.aggregate(
                Max('price'))['price__max']
            context['maxPrice'] = max(
                context['maxPrice'], context['event'].baseFee)
            context['minPrice'] = context['event'].ticketOptions.aggregate(
                Min('price'))['price__min']
            context['minPrice'] = min(
                context['minPrice'], context['event'].baseFee)

        return context

    def event_detail_view(request, slug):
        event = get_object_or_404(Event, slug=slug)
        return render(request, "home/eventDetailView.html")


def homepage(request):
    events = Event.objects.all()
    context = {
        'events': events,
    }
    return HttpResponseRedirect(reverse('events'))


def event(request, id):
    event = get_object_or_404(Event, pk=id)
    context = {
        'event': event,
    }
    return render(request, "home/event.html", context=context)

# handle booking request
@login_required
def booking(request):
    if request.method == 'POST':
        eventName = request.POST['event_name']
        venue = get_object_or_404(Venue, pk=int(request.POST['venue']))
        startdate = request.POST['startdate']
        starttime = request.POST['starttime']
        image = request.FILES['imageFile']
        # assign new unique name for image file to be saved in the local system
        new_name = '{}_{}_{}'.format(
            image.name, request.user.username, startdate)
        # replace file name only, not it's extension
        dot = image.name.rindex('.')
        image.name = image.name.replace(image.name[0:dot], new_name)
        imageFile = FileSystemStorage()
        imageFile.save(image.name, image)
        baseFee = request.POST['baseFee']
        # creating new event
        event = Event(title=eventName, venue=venue, date=startdate,
                      time=starttime, baseFee=baseFee, imagePath=f'Image/{image.name}')
        event.save()
        event.organizer.add(request.user)
        ticket_num = request.POST['additionalTickets']
        # add ticket options
        for i in range(int(ticket_num)):
            title = request.POST[f'title{i+1}']
            price = request.POST[f'price{i+1}']
            ticket = TicketOption(name=title, price=price)
            ticket.save()
            event.ticketOptions.add(ticket)
        return HttpResponseRedirect(reverse('event-detail', kwargs={'slug': event.slug}))

    else:
        venues = Venue.objects.all()
        today = date.today()
        max_date = date(
            int(today.year)+1, int(today.month), int(today.day))
        context = {
            'venues': venues,
            'today': str(today),
            'max_date': max_date,
        }
        return render(request, "home/hosting.html", context=context)


def interested(request):
    # handle ajax request of 'interested button'
    user = request.user
    id = request.GET['id']
    event = Event.objects.get(pk=id)
    # add curr user to interested list
    if not user in event.interested.all():
        event.interested.add(user)
        data = {
            'success': True,
            'interested': event.interested.count(),
        }
        return JsonResponse(data)
    # remove curr user to interested list
    else:
        event.interested.remove(user)
        data = {
            'success': False,
            'interested': event.interested.count(),
        }
        return JsonResponse(data)


def calculateTotal(request):
    num = request.GET['num']
    eventid = int(request.GET['eventid'])
    optionid = int(request.GET['optionid'])
    event = Event.objects.get(pk=eventid)
    price = event.baseFee
    if optionid != 0:
        price = event.ticketOptions.get(pk=optionid).price
    total = price * int(num)
    data = {
        'total': total,
    }
    return JsonResponse(data)


class EventListCreate(generics.ListCreateAPIView):
    queryset = Event.objects.all()
    serializer_class = EventSerializer
