# Pong : settings.py
# Boredom Project

import pygame

class Settings:

    def __init__(self):

        self.width = 1000
        self.height = 600

        self.caption = 'Boredom Project: Pong'
        self.fps = 200

        self.game_pause = False

        # Color Modules
        self.black  = [  0,   0,   0]
        self.white  = [255, 255, 255]
        self.gray   = [211, 211, 211]
        self.green  = [  0, 255,   0]

        self.c_pause = [155, 155, 155]

        # Miscellaneous
        self.ffps = pygame.font.SysFont("Courier New", 12)
        self.score = pygame.font.SysFont("Arial", 40)

        # Pause Screen
        self.ps_rect = pygame.Rect(0, 0, self.width/3, self.height)
        self.ps_font = pygame.font.Font("gasalt.ttf", 25)

        # Button Objects
        self.options_menu = [
            'General Options',
            'Paddle Options',
            'Ball Options',
            'About',
            'Exit Options Menu',
            'Quit Game'
        ]
        self.b_rect = [(40, 30, self.width/3, 34, 0),
                       (40, 65, self.width/3, 34, 0),
                       (40, 100, self.width/3, 34, 0),
                       (40, 135, self.width/3, 34, 0),
                       (40, 170, self.width/3, 34, 0),
                       (40, 205, self.width/3, 34, 0)]

        self.arrows = ['<', '>']

        # General Options Buttons
        self.genopt_brect = [(110, 30, 82, 34, 105),
                             (145, 70, 47, 34, 140),
                             (190, 110, 85, 34, 185),
                             (40, 150, 67, 34, 35)]

        self.genopt_menu = [
            'Player: ',
            'Show FPS: ',
            'Scoring Method: '
        ]

        self.genopt_options = [
            ('1 Player', '2 Player'),
            (' No', 'Yes'),
            ('Classic', 'Defense'),
            ('< Back', '< Back')
        ]

        # Paddle Options Buttons
        self.padopt_brect = [(173, 30, 20, 34, 168),
                             (180, 70, 157, 34, 175),
                             (180, 110, 157, 34, 175),
                             (160, 150, 63, 34, 155),
                             (160, 190, 63, 34, 155),
                             (35, 230, 67, 34, 30)]

        self.padopt_menu = [
            'Paddle Speed: ',
            'Paddle 1 Color: ',
            'Paddle 2 Color: ',
            'Paddle 1 CC: ',
            'Paddle 2 CC: '
        ]

        self.padopt_options = [
            (None, None),
            ('COMING SOON', 'COMING SOON'),
            ('COMING SOON', 'COMING SOON'),
            ('False', ' True'),
            (' True', 'False'),
            ('< Back', '< Back')
        ]

        # Ball Options Buttons
        self.ballopt_brect = [(255, 30, 20, 34, 250),
                              (212, 70, 85, 34, 207),
                              (165, 110, 20, 34, 160),
                              (165, 150, 20, 34, 160),
                              (35, 190, 67, 34, 30)]

        self.ballopt_menu = [
            'Universal Serve Speed: ',
            'Ball Bounce Mode: ',
            'Ball X Speed: ',
            'Ball Y Speed: ',
        ]

        self.ballopt_options = [
            ('uss', None),
            ('Random', '  Static'),
            ('bxs', None),
            ('bys', None),
            ('< Back', '< Back')
        ]

        # About Buttons
        self.about_brect = [(40, 30, self.width/3, 34, 0),
                            (40, 65, self.width/3, 34, 0),
                            (40, 100, self.width/3, 34, 0),
                            (40, 135, self.width/3, 34, 0),
                            (40, 170, self.width/3, 34, 0)]

        self.about_menu = [
            'About Pong',
            'Instructions',
            'Technical Details',
            'Credits',
            'Back'
        ]

        self.i_rect = pygame.Rect(370, 0, self.width / 2 + 95, self.height)

        self.abf_about = pygame.font.Font("gasalt.ttf", 22)
        self.abf_instructions = pygame.font.Font("gasalt.ttf", 20)
        self.abf_technical = pygame.font.Font("gasalt.ttf", 20)
        self.abf_credits = pygame.font.Font("gasalt.ttf", 22)
