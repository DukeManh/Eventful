from django.contrib.auth import authenticate, login, logout
from django.shortcuts import render
from django.http import HttpResponseRedirect, HttpResponse
from django.urls import reverse
# Create your views here.


def profile(request):
    if request.user.is_authenticated:
        return render(request, "registration/profile.html")
    else:
        return HttpResponseRedirect(reverse('login'))

