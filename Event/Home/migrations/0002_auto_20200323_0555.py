# Generated by Django 3.0.4 on 2020-03-23 05:55

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('Home', '0001_initial'),
    ]

    operations = [
        migrations.AlterField(
            model_name='event',
            name='organizer',
            field=models.CharField(max_length=150, null=True),
        ),
    ]