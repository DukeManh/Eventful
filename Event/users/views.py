from django.contrib.auth import authenticate, login, logout
from django.shortcuts import render
from django.http import HttpResponseRedirect, HttpResponse
from django.urls import reverse
# Create your views here.


def index(request):
    if not request.user.is_authenticated:
        return HttpResponseRedirect(reverse("login"))
    return HttpResponse("dafs")


def logout_view(request):
    pass


def signup_view(request):
    pass


def login_view(request):
    if request.method == "POST":
        username = request.POST["Username"]
        password = request.POST["Password"]
        user = authenticate(request, username=username, password=password)

        if user is not None:
            login(request, user)
            return HttpResponseRedirect(reverse('index'))
        else:
            return render(request, 'users/login.html',
                          {
                              "message": "Invalid credentials"
                          })
    return render(request, 'users/login.html')
