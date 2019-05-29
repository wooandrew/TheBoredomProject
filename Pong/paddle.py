# Pong : paddle.py
# Boredom Project

import pygame

class Paddle1(object):

    def __init__(self, dimensions):

        self.dimensions = dimensions

        # Paddle Rect Data
        self.rect = pygame.Rect(0, 0, 20, 100)

        self.rect.x = 30
        self.rect.centery = self.dimensions[1] / 2

        # Moving
        self.movingup = False
        self.movingdown = False

    def update(self, opt, ball):

        if not opt.paddle1_cc:

            if self.movingup and self.rect.y > 0:
                self.rect.centery -= opt.pSpeed
            elif self.movingdown and self.rect.y < self.dimensions[1] - 100:
                self.rect.centery += opt.pSpeed

        else:
            if self.rect.centery < ball.rect.centery:
                self.rect.centery += opt.pSpeed
            elif self.rect.centery > ball.rect.centery:
                self.rect.centery -= opt.pSpeed


class Paddle2(object):

    def __init__(self, dimensions):

        self.dimensions = dimensions

        # Paddle Rect Data
        self.rect = pygame.Rect(0, 0, 20, 100)

        self.rect.x = dimensions[0] - 50
        self.rect.centery = dimensions[1] / 2

        # Moving
        self.movingup = False
        self.movingdown = False

    def update(self, opt, ball):

        if not opt.paddle2_cc:

            if self.movingup and self.rect.y > 0:
                self.rect.centery -= opt.pSpeed
            elif self.movingdown and self.rect.y < self.dimensions[1] - 100:
                self.rect.centery += opt.pSpeed

        else:
            if self.rect.centery < ball.rect.centery:
                self.rect.centery += opt.pSpeed
            elif self.rect.centery > ball.rect.centery:
                self.rect.centery -= opt.pSpeed
