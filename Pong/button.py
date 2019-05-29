# Pong : button.py
# Boredom Project

import pygame

class Button:

    def __init__(self, screen, sett, msg, b_rect):

        self.screen = screen
        self.msg = msg

        # Button Properties
        self.color = [155, 155, 155]
        self.h_color = [100, 100, 100]

        self.clicked = False

        # Build Button
        self.rect = pygame.Rect(b_rect[4], b_rect[1], b_rect[2], b_rect[3])
        self.m_image = sett.ps_font.render(self.msg, True, sett.black, None)
        self.mi_rect = self.m_image.get_rect()

        self.mi_rect.x = b_rect[0]
        self.mi_rect.y = self.rect.y + 5

    def draw(self):

        mousex, mousey = pygame.mouse.get_pos()

        if self.rect.collidepoint(mousex, mousey):
            self.screen.fill(self.h_color, self.rect)
        else:
            self.screen.fill(self.color, self.rect)

        self.screen.blit(self.m_image, self.mi_rect)


class AbButton:

    def __init__(self, screen, sett, msg, b_rect):

        self.screen = screen
        self.msg = msg

        # Button Properties
        self.color = [155, 155, 155]
        self.h_color = [100, 100, 100]

        self.clicked = False

        # Build Button
        self.rect = pygame.Rect(b_rect[4], b_rect[1], b_rect[2], b_rect[3])
        self.m_image = sett.ps_font.render(self.msg, True, sett.black, None)
        self.mi_rect = self.m_image.get_rect()

        self.mi_rect.x = b_rect[0]
        self.mi_rect.y = self.rect.y + 5

    def draw(self, sett):

        mousex, mousey = pygame.mouse.get_pos()

        if self.rect.collidepoint(mousex, mousey) or self.clicked:
            self.screen.fill(self.h_color, self.rect)
        else:
            self.screen.fill(self.color, self.rect)

        self.screen.blit(self.m_image, self.mi_rect)

        if self.clicked:
            self.screen.fill(self.color, sett.i_rect)


class OptionsB:

    def __init__(self, screen, sett, opts, b_rect):

        self.screen = screen
        self.options = []

        for opt in opts:
            self.options.append(opt)

        self.chosen_opt = 0

        # Button Properties
        self.color = [155, 155, 155]
        self.h_color = [100, 100, 100]

        self.clicked = False

        # Build Button
        self.rect = pygame.Rect(b_rect[4], b_rect[1] - 4, b_rect[2], b_rect[3])
        self.m_image = sett.ps_font.render(self.options[0], True, sett.black, None)
        self.mi_rect = self.m_image.get_rect()

        self.mi_rect.x = b_rect[0]
        self.mi_rect.y = b_rect[1]

        self.b_rect = b_rect

    def change(self, sett):

        self.chosen_opt += 1

        if self.chosen_opt >= len(self.options):
            self.chosen_opt = 0

        self.m_image = sett.ps_font.render(self.options[self.chosen_opt], True, sett.black, None)
        self.mi_rect = self.m_image.get_rect()

        self.mi_rect.x = self.b_rect[0]
        self.mi_rect.y = self.b_rect[1]

    def draw(self):

        mousex, mousey = pygame.mouse.get_pos()

        if self.rect.collidepoint(mousex, mousey):
            self.screen.fill(self.h_color, self.rect)
        else:
            self.screen.fill(self.color, self.rect)

        self.screen.blit(self.m_image, self.mi_rect)


class IterButton:

    def __init__(self, screen, sett, startnum, opt, b_rect):
        self.screen = screen

        self.options = opt

        self.numiter = startnum

        # Button Properties
        self.color = [155, 155, 155]
        self.h_color = [100, 100, 100]

        self.clicked = False

        # Build Button
        self.rect = pygame.Rect(b_rect[4], b_rect[1] - 4, b_rect[2], b_rect[3])
        self.m_image = sett.ps_font.render(str(self.numiter), True, sett.black, None)
        self.mi_rect = self.m_image.get_rect()

        self.mi_rect.x = b_rect[0]
        self.mi_rect.y = b_rect[1]

        self.b_rect = b_rect

    def changenum(self, sett, button):

        if button is 1 and 0 < self.numiter < 9:
            self.numiter += 1
        elif button is 3 and (self.numiter - 1 > 0):
            self.numiter -= 1

        self.m_image = sett.ps_font.render(str(self.numiter), True, sett.black, None)
        self.mi_rect = self.m_image.get_rect()

        self.mi_rect.x = self.b_rect[0]
        self.mi_rect.y = self.b_rect[1]

    def draw(self):

        mousex, mousey = pygame.mouse.get_pos()

        if self.rect.collidepoint(mousex, mousey):
            self.screen.fill(self.h_color, self.rect)
        else:
            self.screen.fill(self.color, self.rect)

        self.screen.blit(self.m_image, self.mi_rect)
