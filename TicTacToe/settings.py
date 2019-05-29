# Tic Tac Toe : settings.py
# Boredom Project

import pygame

class Settings:

    def __init__(self):

        self.width = 400
        self.height = 550

        self.caption = 'Boredom Project: Tic Tac Toe'
        self.fps = 200

        # Color Modules
        self.black  = [  0,   0,   0]
        self.white  = [255, 255, 255]
        self.gray   = [211, 211, 211]
        self.green  = [  0, 255,   0]
        self.red    = [255,   0,   0]

        # Miscellaneous
        self.s_font = pygame.font.Font("ralewaylight.ttf", 25)
