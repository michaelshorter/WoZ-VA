Smartness WoZ Prototype
The WoZVA (Wizard of Oz Voice Assistant) allows researchers to become the ‘voice’ of a VA. Responding to users commands in a synthetic voice, as well as controlling VA LED behaviours to add some theatre to the user experience. 


LED Controller
The LED ring is controlled via a web portal. To access the LED dashboard go to Adafruit IO: https://io.adafruit.com/mshorter/dashboards/va-led-controller 

Username: xxxxxx
Password: xxxxxx

There are four LED setting:
 
Spinning – activated when a wake word has been detected and user command spoken
Sparkle – activated when processing the users command
Pulse – activated when the VA is responding.
Off. 
 

 
Changing Wifi Credentials for LED Ring
To change the credentials of the you need to change this in the Arduino code. The code can all be found here on GitHub. 

In the config.h file change the following lines to your Wifi credentials. This will not work with a network that uses a captive window to login - In this case it is best to use a WiFi dongle.

#define WIFI_SSID "xxxxxxx"
#define WIFI_PASS "xxxxxxx"

Also make sure the IO Username and Key are correct - they should be:

#define IO_USERNAME "xxxxxx"
#define IO_KEY "xxxxxxxxxx"


Hearing Participant VA Commands
The simplest way to do this is to have a hidden laptop running a Teams meeting between the participant and the controller (with controller side muted) in close proximity to the participant.


Synthetic Speech Responses
Connect to the bluetooth speaker inside the VA, it’s called ‘JBL Go 3’.
Open a suitable translation App. Good options that speak english and German identified are:
Microsoft Translator (Good at recognising and speaking punctuation)
Google Translate (App + Desktop Version)


Powering the WoZ VA
The WozVA is battery powered. There is a LiPo battery powering the LED ring. The battery life is XX hours when the LEDs are constantly on, so should last significantly longer when LEDs are OFF. To re-charge the battery, plug a micro usb cable into the Adafruit Board.

The Blutooth Speaker (JBL Go 3) is also battery powered and has a battery life of 5+ hours, and is closer to 12 hours at 50% volume. The speaker is charged using a USB-C cable and can take around 2 hours to fully charge.
