# Pong : ball.py
# Boredom Project

import math as m
import pygame

deflect = pygame.mixer.Sound('deflected.wav')
scored = pygame.mixer.Sound('scored.wav')

class Ball(object):

    def __init__(self, dimensions):

        self.dimensions = dimensions

        # Ball Hitbox Data
        self.rect = pygame.Rect(0, 0, 40, 40)

        self.rect.centerx = self.dimensions[0] / 2
        self.rect.centery = self.dimensions[1] / 2

        # Ball Data
        self.radius = 20
        self.pos = [m.floor(self.dimensions[0]/2), m.floor(self.dimensions[1]/2)]

        self.xmove = 1
        self.ymove = 0

        # Player Win
        self.leftwin = False
        self.rightwin = False

        self.leftscore = 0
        self.rightscore = 0

    def collision(self, opt, paddle1, paddle2):

        if self.rect.colliderect(paddle1.rect):

            deflect.play()

            if opt.scoring_mode == [True, False]:    # Classic Scoring
                pass
            elif opt.scoring_mode == [False, True]:  # Defense Scoring
                self.leftscore += 1

            # Movement
            self.xmove = opt.b_xspeed
            if self.rect.centery > paddle1.rect.centery:
                self.ymove = opt.b_yspeed
            else:
                self.ymove = -opt.b_yspeed

        elif self.rect.colliderect(paddle2.rect):

            deflect.play()

            if opt.scoring_mode == [True, False]:  # Classic Scoring
                pass
            elif opt.scoring_mode == [False, True]:  # Defense Scoring
                self.rightscore += 1

            # Movement
            self.xmove = -opt.b_xspeed
            if self.rect.centery > paddle2.rect.centery:
                self.ymove = opt.b_yspeed
            else:
                self.ymove = -opt.b_yspeed

        # If ball goes past goal line
        elif self.rect.x + 40 > self.dimensions[0]:
            self.leftwin = True
        elif self.rect.x < 0:
            self.rightwin = True

        # Ball hits top or bottom
        elif self.rect.y < 0:
            self.ymove = opt.b_yspeed
        elif self.rect.y + 40 > self.dimensions[1]:
            self.ymove = -opt.b_yspeed

    def update(self, opt, paddle1, paddle2):

        self.collision(opt, paddle1, paddle2)

        # IF LEFT WINS
        if self.leftwin:
            self.leftwin = False

            scored.play()

            self.xmove = opt.u_ss
            self.ymove = 0

            if opt.scoring_mode == [True, False]:  # Classic Scoring
                self.leftscore += 1
            elif opt.scoring_mode == [False, True]:  # Defense Scoring
                self.rightscore -= 5

            self.rect.centerx = self.dimensions[0] / 2
            self.rect.centery = self.dimensions[1] / 2
            self.pos = [m.floor(self.dimensions[0] / 2), m.floor(self.dimensions[1] / 2)]

        # IF RIGHT WINS
        elif self.rightwin:

            self.rightwin = False

            scored.play()

            self.xmove = -opt.u_ss
            self.ymove = 0

            if opt.scoring_mode == [True, False]:  # Classic Scoring
                self.rightscore += 1
            elif opt.scoring_mode == [False, True]:  # Defense Scoring
                self.leftscore -= 5

            self.rect.centerx = self.dimensions[0] / 2
            self.rect.centery = self.dimensions[1] / 2
            self.pos = [m.floor(self.dimensions[0] / 2), m.floor(self.dimensions[1] / 2)]

        # Move hitbox & ball
        self.rect.centerx += self.xmove
        self.rect.centery += self.ymove

        self.pos[0] += self.xmove
        self.pos[1] += self.ymove

        if opt.b_xyspeed_random:
            opt.randomize_b_xyspeed()
