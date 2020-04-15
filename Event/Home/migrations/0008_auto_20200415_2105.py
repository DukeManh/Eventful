# Generated by Django 3.0.4 on 2020-04-15 21:05

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('Home', '0007_auto_20200415_0535'),
    ]

    operations = [
        migrations.AddField(
            model_name='booking',
            name='ticketNum',
            field=models.IntegerField(default=1, verbose_name='Numbers of Ticket'),
        ),
        migrations.AlterField(
            model_name='event',
            name='date',
            field=models.DateField(verbose_name='Start Date'),
        ),
        migrations.AlterField(
            model_name='event',
            name='time',
            field=models.TimeField(verbose_name='Start time'),
        ),
        migrations.DeleteModel(
            name='Ticket',
        ),
    ]