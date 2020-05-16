from django.contrib import admin
# Register your models here.
from .models import *

admin.site.register(Event)
admin.site.register(Booking)
admin.site.register(Venue)
admin.site.register(Ticket)
admin.site.register(TicketOption)
