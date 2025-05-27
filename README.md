# Luminaphone

The Luminaphone was an odd electronic musical instrument created 100 years ago. Only one prototype was ever built, and no recordings of its music have survived. I have reconstructed this unusual instrument to see what it sounded like.

![](https://raw.githubusercontent.com/nickbild/luminaphone/refs/heads/main/media/logo.jpg)

**Check out the video on YouTube:**
<a href="https://www.youtube.com/watch?v=kRWPpAO6C3s">![](https://raw.githubusercontent.com/nickbild/luminaphone/refs/heads/main/media/playing.png)</a>

## Background

The Luminaphone has a really interesting history. It was invented by a man named Harry Grindell Matthews. 

![](https://raw.githubusercontent.com/nickbild/luminaphone/refs/heads/main/media/Harry_Grindell_Matthews_1924.jpg)

He invented a lot of other things as well, like a wireless remote control system for submarines and a self-righting flying machine, but he is best known for a dubious claim he made about creating what he called a Death Ray. It was supposed to instantly and silently kill, and bring motors to a halt. He claimed it would end wars forever. 

![](https://raw.githubusercontent.com/nickbild/luminaphone/refs/heads/main/media/death_ray.jpg)

All of this created quite the international stir, but he was never able to back up those claims with a demonstration, and so he lost the people’s trust. A NYT article from the time about the Luminaphone derisively called him Death Ray Man.

![](https://raw.githubusercontent.com/nickbild/luminaphone/refs/heads/main/media/luminaphone_matthews.png)

The Luminaphone, on the other hand, was definitely real. People who heard it described it as sounding something like a little pipe organ.

## How It Works

![](https://raw.githubusercontent.com/nickbild/luminaphone/refs/heads/main/media/original_circuit.png)

This is what Matthews’ Luminaphone circuit looked like. Each key turned on an incandescent bulb that was directed at a particular ring in a metal disc, which was spinning at 400 RPMs. Each ring had a pattern of holes made in it. Light that made it through the holes in the disc fell on a selenium cell (an early photoresistor), which altered the amount of current that flowed through it, and the transformer it was in series with. This transformer removed any DC components from the signal, leaving just the light modulated signal on the other side of the transformer. This was fed into some amplifiers before it reached a speaker.

The reason the spinning disc was necessary was due to the technological limitations of the day. Incandescent bulbs do not turn on and off rapidly as a modern LED or laser does, for example, so the holes in the metal provided the fast transitions. This setup also provided the control — it specified when the light should turn off. But in today’s world, there are much better ways to achieve these goals.

![](https://raw.githubusercontent.com/nickbild/luminaphone/refs/heads/main/media/my_luminaphone.png)

For this reason, I did things differently, but achieved the same result. I did away with the spinning disk and instead replaced it with a laser that can turn on and off very rapidly. I paired that with this Arduino microcontroller development board (Nano 33 IoT) that gives me precise control over exactly when the laser is turned on or off.

GPIO pins are rapidly switched on and off in a pattern I define when buttons are pressed. That switches a transistor that controls the current flowing through the laser. The laser shines on a photoresistor, which turns the light into an electrical signal that is played through a speaker.

Now for those patterns. Each musical note has a particular frequency. For example, middle C has a frequency of about 261 hertz, and D4 is 293 hertz. I tailored the on-off patterns to match these frequencies.

![](https://raw.githubusercontent.com/nickbild/luminaphone/refs/heads/main/media/schematic.jpg)

## Bill of Materials

- 1 x Arduino Nano 33 IoT
- 1 x 2N3904 NPN transistor
- 1 x Laser Diode — 5mW 650nm Red
- 1 x TRRS breakout board
- 1 x Speaker
- 1 x Photoresistor
- 1 x 100K resistor
- 1 x 5K resistor
- 1 x 220 resistor
- 8 x Pushbuttons

## About the Author

[Nick A. Bild, MS](https://nickbild79.firebaseapp.com/#!/)
