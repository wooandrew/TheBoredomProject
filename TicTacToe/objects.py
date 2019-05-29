# Tic Tac Toe : objects.py
# Boredom Project

import pygame


class Board(object):

    def __init__(self, imagepath, dimensions):

        self.image = pygame.image.load(imagepath)
        self.rect = self.image.get_rect()

        # Turn
        self.x_turn = True
        self.o_turn = False

        self.turns = 0

        # reposition object
        self.rect.centerx = dimensions[0] / 2
        self.rect.centery = (dimensions[1] / 3) + 40

        # Board Data
        self.board_used = {'a1': False, 'a2': False, 'a3': False,
                           'b1': False, 'b2': False, 'b3': False,
                           'c1': False, 'c2': False, 'c3': False}

        self.board_x = [0, 0, 0,
                        0, 0, 0,
                        0, 0, 0]

        self.board_o = [0, 0, 0,
                        0, 0, 0,
                        0, 0, 0]

        self.carre_a1 = pygame.Rect(35, 58, 104, 104)
        self.carre_a2 = pygame.Rect(148, 58, 104, 104)
        self.carre_a3 = pygame.Rect(261, 58, 104, 104)

        self.carre_b1 = pygame.Rect(35, 171, 104, 104)
        self.carre_b2 = pygame.Rect(148, 171, 104, 104)
        self.carre_b3 = pygame.Rect(261, 171, 104, 104)

        self.carre_c1 = pygame.Rect(35, 284, 104, 104)
        self.carre_c2 = pygame.Rect(148, 284, 104, 104)
        self.carre_c3 = pygame.Rect(261, 284, 104, 104)

    def draw_object(self, screen):

        screen.blit(self.image, self.rect)

    def reset(self):
        self.x_turn = True
        self.o_turn = False

        self.board_used = {'a1': False, 'a2': False, 'a3': False,
                           'b1': False, 'b2': False, 'b3': False,
                           'c1': False, 'c2': False, 'c3': False}

        self.board_x = [0, 0, 0,
                        0, 0, 0,
                        0, 0, 0]

        self.board_o = [0, 0, 0,
                        0, 0, 0,
                        0, 0, 0]


class CrossCircle(object):

    def __init__(self, board, imagepath, carre):

        self.image = pygame.image.load(imagepath)
        self.rect = self.image.get_rect()

        self.draw = False

        if carre == 'a1':
            self.rect.x = board.carre_a1[0]
            self.rect.y = board.carre_a1[1]
        elif carre == 'a2':
            self.rect.x = board.carre_a2[0]
            self.rect.y = board.carre_a2[1]
        elif carre == 'a3':
            self.rect.x = board.carre_a3[0]
            self.rect.y = board.carre_a3[1]

        elif carre == 'b1':
            self.rect.x = board.carre_b1[0]
            self.rect.y = board.carre_b1[1]
        elif carre == 'b2':
            self.rect.x = board.carre_b2[0]
            self.rect.y = board.carre_b2[1]
        elif carre == 'b3':
            self.rect.x = board.carre_b3[0]
            self.rect.y = board.carre_b3[1]

        elif carre == 'c1':
            self.rect.x = board.carre_c1[0]
            self.rect.y = board.carre_c1[1]
        elif carre == 'c2':
            self.rect.x = board.carre_c2[0]
            self.rect.y = board.carre_c2[1]
        elif carre == 'c3':
            self.rect.x = board.carre_c3[0]
            self.rect.y = board.carre_c3[1]

    def draw_object(self, screen):

        screen.blit(self.image, self.rect)


class Button:

    def __init__(self, sett, msg, pos):

        self.msg = msg

        self.image = sett.s_font.render(msg, True, sett.black, None)
        self.rect = self.image.get_rect()

        self.rect.centerx = pos[0]
        self.rect.centery = pos[1]

        self.crect = self.rect
        self.crect.width += 5
        self.crect.centerx = pos[0]

        # Button Properties
        self.color = [155, 155, 155]
        self.h_color = [100, 100, 100]

    def draw_button(self, screen):

        mousex, mousey = pygame.mouse.get_pos()

        if self.rect.collidepoint(mousex, mousey):
            screen.fill(self.h_color, self.crect)
        else:
            screen.fill(self.color, self.crect)

        screen.blit(self.image, self.rect)
