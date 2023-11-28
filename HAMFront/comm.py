import paho.mqtt.client as mqttc
import paho.mqtt.publish as publish

INFO_WATER_TOPIC_IN = 'hammer/water_out'
INFO_TEMPERATURE_TOPIC_IN = 'hammer/temperature_out'
INFO_HUMIDITY_TOPIC_IN = 'hammer/humidity_out'
INFO_LIGHT_TOPIC_IN = 'hammer/light_out'

LED_WATER_TOPIC_OUT = 'hammer/led/water_in'
LED_TEMPERATURE_TOPIC_OUT = 'hammer/led/temperature_in'
LED_LIGHT_TOPIC_OUT = 'hammer/led/light_in'

LED_WATER_TOPIC_IN = 'hammer/led/water_out'
LED_TEMPERATURE_TOPIC_IN = 'hammer/led/temperature_out'
LED_LIGHT_TOPIC_IN = 'hammer/led/light_out'

BROKER_URL = 'localhost'
BROKER_PORT = 1883

OUT_TOPICS = [
    LED_WATER_TOPIC_OUT,
    LED_TEMPERATURE_TOPIC_OUT,
    LED_LIGHT_TOPIC_OUT
]

IN_TOPICS = [
    LED_LIGHT_TOPIC_IN,
    LED_TEMPERATURE_TOPIC_IN,
    LED_WATER_TOPIC_IN,
    INFO_WATER_TOPIC_IN,
    INFO_TEMPERATURE_TOPIC_IN,
    INFO_HUMIDITY_TOPIC_IN,
    INFO_LIGHT_TOPIC_IN,
]


class Publisher:
    @staticmethod
    def send_message(topic, message):
        try:
            print(topic, message, BROKER_URL)
            publish.single(topic, message, hostname=BROKER_URL, port=BROKER_PORT)
        except Exception as ex:
            print(f'Error sending message. Exception: {ex}')


class Listener:
    def __init__(self, observer):
        self.client = mqttc.Client()
        self.client.on_connect = self.on_connect
        self.client.on_message = self.on_message
        self.observador = observer

        try:
            self.client.connect(BROKER_URL, BROKER_PORT, 60)
        except Exception as ex:
            print(f'Error connecting to the broker. Exception: {ex}')

    def on_connect(self, client, userdata, flags, rc):
        for topic in IN_TOPICS:
            print(f'Connected to {topic}')
            client.subscribe(topic)

    def on_message(self, client, userdata, msg):
        self.observador.process_message(msg)
        print('Message received', msg.payload.decode('utf-8'))

    def start(self):
        print('Looping')
        self.client.loop_forever()