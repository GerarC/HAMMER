from _thread import start_new_thread

from kivy.clock import mainthread
from kivy.uix.screenmanager import Screen
import threading
from kivy.properties import (
    StringProperty,
    BooleanProperty,
    NumericProperty
)
from comm import *


class Hammer(Screen):
    good_light = BooleanProperty(False)
    good_water = BooleanProperty(False)
    temperature_val = NumericProperty(0.0)
    humidity_val = NumericProperty(0.0)

    light_image = StringProperty('assets/bombillo_apagao.png')
    water_image = StringProperty('assets/no_hay_agua.png')
    temperature_string = StringProperty('20.0C')
    humidity_string = StringProperty('20RH')

    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        listener = Listener(self)
        start_new_thread(listener.start, ())

    @mainthread
    def process_water(self, water_level):
        msg = "off"
        if water_level < 100:
            msg = "on"
        else:
            msg = "off"
        Publisher.send_message(LED_WATER_TOPIC_OUT, msg)
        self.water_image = ("assets/no_hay_agua.png" if msg == "on" else "assets/si_hay_agua.png")

    @mainthread
    def process_light(self, light_level):
        msg = "off"
        if light_level < 2000:
            msg = "on"
        else:
            msg = "off"
        Publisher.send_message(LED_LIGHT_TOPIC_OUT, msg)
        self.light_image = ("assets/bombillo_prendio.png" if msg == "on" else "assets/bombillo_apagao.png")

    @mainthread
    def process_temperature(self, temperature_level):
        level = 0
        if temperature_level >= 30:
            level = 5
        elif temperature_level > 25:
            level = 4
        elif temperature_level > 18:
            level = 3
        elif temperature_level > 15:
            level = 2
        elif temperature_level <= 15:
            level = 1
        Publisher.send_message(LED_TEMPERATURE_TOPIC_OUT, f"set:{level}")
        self.temperature_string = f"{temperature_level}C"

    @mainthread
    def process_humidity(self, humidity_level):
        self.humidity_string = f"{humidity_level}RH"

    @mainthread
    def process_message(self, msg):
        msg_split = str(msg).split(":")
        if msg_split[0] == "water":
            self.process_water(int(msg_split[1]))
        if msg_split[0] == "light":
            self.process_light(int(msg_split[1]))
        if msg_split[0] == "temperature":
            self.process_temperature(float(msg_split[1]))
        if msg_split[0] == "humidity":
            self.process_humidity(float(msg_split[1]))
