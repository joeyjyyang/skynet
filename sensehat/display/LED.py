from sense_hat import SenseHat
from time import sleep

blue = (0, 0, 255)
yellow = (255, 255, 0)
red = (255, 0, 0)
green = (0, 255, 0)

def init_sense():
    sense = SenseHat()
    sense.clear()
    return sense

def display_text(sense):
    while True:
        accel = sense.get_accelerometer_raw()

        z = accel['z']
        z = round(z, 0)

        if (z == 1):
            sense.show_message("Rita", scroll_speed = 0.1, text_colour = yellow, back_colour = blue)
        elif (z == -1):
            sense.show_message("Joey", scroll_speed = 0.1, text_colour = red, back_colour = green)
        else:
            sense.show_message("Bob", scroll_speed = 0.1)

def display_letter(sense):
    sense.show_letter("Z")

def set_matrix(sense):
    matrix_pixels = [
            blue, blue, blue, blue, blue, blue, blue, blue,
            yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow,
            green, green, green, green, green, green, green, green,
            red, red, red, red, red, red, red, red,
            blue, blue, blue, blue, blue, blue, blue, blue,
            yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow,
            green, green, green, green, green, green, green, green,
            red, red, red, red, red, red, red, red,
    ]

    sense.set_pixels(matrix_pixels)

    while True:
        sleep(1)
        sense.flip_v()
        #sense.set_rotation(90)

def main():
   sense = init_sense()
   #display_text(sense)
   set_matrix(sense)

if __name__ == "__main__":
    main()
