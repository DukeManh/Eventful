# Generated by Django 3.0.4 on 2020-03-23 23:35

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('Home', '0002_auto_20200323_0555'),
    ]

    operations = [
        migrations.AlterField(
            model_name='event',
            name='organizer',
            field=models.CharField(max_length=150, null=True, verbose_name='Organizer Name'),
        ),
    ]
