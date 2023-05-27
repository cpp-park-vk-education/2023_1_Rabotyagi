# Generated by Django 4.2.1 on 2023-05-27 16:03

from django.conf import settings
from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        migrations.swappable_dependency(settings.AUTH_USER_MODEL),
        ('api', '0001_initial'),
    ]

    operations = [
        migrations.AddField(
            model_name='guild',
            name='users',
            field=models.ManyToManyField(related_name='guilds', to=settings.AUTH_USER_MODEL),
        ),
    ]
