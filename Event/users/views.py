from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.models import User
from django.shortcuts import render, redirect
from django.http import HttpResponseRedirect, HttpResponse
from django.urls import reverse
# Create your views here.


def profile(request):
    if request.user.is_authenticated:
        return render(request, "registration/profile.html")
    else:
        return HttpResponseRedirect(reverse('login'))


def signup(request):
    if request.method == 'POST':
        username = request.POST['username']
        email = request.POST['mail']
        password = request.POST['pass1']
        nameerror = None
        emailerror = None
        if (username in User.objects.values_list('username')):
            nameerror = "Username already exists"
        if (email in User.objects.values_list('email')):
            emailerror = "Email has already been used"
        if not nameerror and not emailerror:
            user = User.objects.create_user(username, email, password)
            login(request, user)
            return HttpResponseRedirect(reverse('home'))

        else:
            return render(request, "registration/signup.html", context={
                'nameerror': nameerror,
                'emailerror': emailerror,
            })
    else:
        return render(request, "registration/signup.html")
