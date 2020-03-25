from django.db import models

# Create your models here.


class Event(models.Model):
    name = models.CharField(max_length=150)
    organizer = models.CharField(
        max_length=150, null=True, verbose_name="Organizer Name")

    def __str__(self):
        return f"{self.name} was organized by {self.organizer}"
