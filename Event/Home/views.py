from django.http import HttpResponse
from django.shortcuts import render

# Create your views here.


def index(request):
    return HttpResponse("TEsting")


def greet(request, name):
    return render(request, "home/List.html", {
        "fruits": ["kiwi", "jackfruit", "mango"],
        "name": name
    })


def homepage(request):
    return render(request, "home/index.html")


def test(request):
    return render(request, "home/base.html")
