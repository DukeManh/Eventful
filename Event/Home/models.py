from django.shortcuts import reverse
from django.db import models
from django.contrib.auth.models import User
from django.utils.text import slugify
# Create your models here.


class Venue(models.Model):
    title = models.CharField(max_length=150)
    address = models.CharField(max_length=150)
    city = models.CharField(max_length=20)

    def __str__(self):
        return f'{self.title} - {self.address}, {self.city}'


class Event(models.Model):
    title = models.CharField(max_length=100)
    slug = models.SlugField(unique=True, null=True)
    venue = models.ForeignKey(Venue, on_delete=models.CASCADE)
    organizer = models.ManyToManyField(
        User, help_text='add organizer', related_name='organizer')
    date = models.DateField(
        auto_now=False, auto_now_add=False, verbose_name='Start Date')
    time = models.TimeField(verbose_name='Start time', auto_now=False)
    fee = models.DecimalField(max_digits=5, decimal_places=2)
    imagePath = models.CharField(
        max_length=30, null=True, default="Image/test.png")
    interested = models.ManyToManyField(
        User, help_text='who is interested', related_name='interested', blank=True)

    def __str__(self):
        return f'{self.title} at {self.venue}'

    def get_absolute_url(self):
        return reverse('event-detail', args=[str(self.id)])

    def save(self, *args, **kwargs):
        self.slug = slugify(self.title)
        super(Event, self).save(*args, **kwargs)

    class Meta:
        ordering = ['date', 'time']


class Booking(models.Model):
    event = models.ForeignKey(Event, on_delete=models.CASCADE)
    booker = models.ForeignKey(User, on_delete=models.CASCADE)
    booked_on = models.DateField(
        auto_now=True, auto_now_add=False, verbose_name='Book date')
    ticketNum = models.IntegerField(
        verbose_name="Numbers of Ticket", default=1)

    def __str__(self):
        return f'{self.booker} booked {self.event} on {self.booked_on}'

    def save(self, *args, **kwargs):
        super(Booking, self).save(*args, **kwargs)
        for i in range(self.ticketNum):
            Ticket.objects.create(bookingId=self)


class Ticket(models.Model):
    bookingId = models.ForeignKey(Booking, on_delete=models.CASCADE)

    def __str__(self):
        return f"Booking Id: {self.bookingId}"
