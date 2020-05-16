from rest_framework import serializers
from Home.models import Event


class EventSerializer(serializers.ModelSerializer):
    class Meta:
        model = Event
        fields = ('title', 'slug', 'venue', 'organizer', 'date',
                  'time', 'fee', 'interested', 'imagePath')
