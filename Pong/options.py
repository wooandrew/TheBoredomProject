# Pong : options.py
# Boredom Project

import random

class Options:

    def __init__(self):

        self.oneplayer = False
        self.twoplayer = True

        self.cpulevel = 0

        # Paddle Options
        self.pSpeed = 3

        self.c_paddle1 = [  0, 255, 255]
        self.c_paddle2 = [255,   0, 255]

        self.paddle1_cc = False
        self.paddle2_cc = True

        # Ball Options
        self.u_ss = 2   # Universal Serve Speed

        self.b_xyspeed_random = True

        self.b_xspeed = 2
        self.b_yspeed = 4

        # Miscellaneous
        self.sfps = False
        self.scoring_mode = [True, False]  # Classic, Defense

    def randomize_b_xyspeed(self):

        self.b_yspeed = random.randint(1, 4)
        self.b_xspeed = 6 - self.b_yspeed
