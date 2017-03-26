# PhyXTGears 2017 Robot Bling
Our setup uses a arduino mega to run an LED panel.
Our LED panel (40 pixles wide by 16 pixels high) is composed of two 32x8 panels and two 8x8 panels, chained together and connected to one pin on the Arduino.
The LEDs in the use 24-bit color, and are wired like one long string (the data for the last pixel must travel through all of the other pixels).
Using the NeoPixel library we can control the panel like a string of pixels.
The NeoMatrix library lets us control the panel like a matrix using (x, y) coordinates.
Using the Adafruit GFX library we can draw points, lines, and shapes.