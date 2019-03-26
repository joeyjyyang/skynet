from sense_hat import SenseHat

sense = SenseHat()
sense.set_imu_config(False, True, True)

while True:
    orientation = sense.get_orientation()
    direction = orientation["yaw"]
    print(direction)

