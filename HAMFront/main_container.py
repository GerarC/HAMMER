from kivy.app import App
from kivy.uix.screenmanager import ScreenManager
from hammer import Hammer


class Container(App):
    sm = ScreenManager()

    def build(self):
        self.sm.add_widget(Hammer(name='hammer'))
        return self.sm
