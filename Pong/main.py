# Pong : main.py
# Boredom Project

# Import & Init pygame
import pygame

pygame.mixer.pre_init(44100, -16, 2, 512)
pygame.init()

# Imports
from settings import *
from options import *

from paddle import *
from ball import *

from button import Button, AbButton, OptionsB, IterButton

import engine as e

# Basic Init
sett = Settings()
opt = Options()

ICON = pygame.image.load(r'pong.ico')

# _ Basic Init - Screen Set
screen = pygame.display.set_mode((sett.width, sett.height))
pygame.display.set_caption(sett.caption)
pygame.display.set_icon(ICON)

# Main
def main():

    rungame = True

    clock = pygame.time.Clock()

    paddle1 = Paddle1((sett.width, sett.height))
    paddle2 = Paddle2((sett.width, sett.height))

    ball = Ball((sett.width, sett.height))

    buttons = [Button(screen, sett, sett.options_menu[0], sett.b_rect[0]),
               Button(screen, sett, sett.options_menu[1], sett.b_rect[1]),
               Button(screen, sett, sett.options_menu[2], sett.b_rect[2]),
               Button(screen, sett, sett.options_menu[3], sett.b_rect[3]),
               Button(screen, sett, sett.options_menu[4], sett.b_rect[4]),
               Button(screen, sett, sett.options_menu[5], sett.b_rect[5])]

    b_about = [AbButton(screen, sett, sett.about_menu[0], sett.about_brect[0]),
               AbButton(screen, sett, sett.about_menu[1], sett.about_brect[1]),
               AbButton(screen, sett, sett.about_menu[2], sett.about_brect[2]),
               AbButton(screen, sett, sett.about_menu[3], sett.about_brect[3]),
               AbButton(screen, sett, sett.about_menu[4], sett.about_brect[4])]

    b_genopt = [OptionsB(screen, sett, sett.genopt_options[0], sett.genopt_brect[0]),
                OptionsB(screen, sett, sett.genopt_options[1], sett.genopt_brect[1]),
                OptionsB(screen, sett, sett.genopt_options[2], sett.genopt_brect[2]),
                OptionsB(screen, sett, sett.genopt_options[3], sett.genopt_brect[3])]

    b_padopt = [IterButton(screen, sett, opt.pSpeed, sett.padopt_options[0], sett.padopt_brect[0]),
                OptionsB(screen, sett, sett.padopt_options[1], sett.padopt_brect[1]),
                OptionsB(screen, sett, sett.padopt_options[2], sett.padopt_brect[2]),
                OptionsB(screen, sett, sett.padopt_options[3], sett.padopt_brect[3]),
                OptionsB(screen, sett, sett.padopt_options[4], sett.padopt_brect[4]),
                OptionsB(screen, sett, sett.padopt_options[5], sett.padopt_brect[5])]

    b_ballopt = [IterButton(screen, sett, opt.u_ss, sett.ballopt_options[0], sett.ballopt_brect[0]),
                 OptionsB(screen, sett, sett.ballopt_options[1], sett.ballopt_brect[1]),
                 IterButton(screen, sett, opt.b_xspeed, sett.ballopt_options[2], sett.ballopt_brect[2]),
                 IterButton(screen, sett, opt.b_yspeed, sett.ballopt_options[3], sett.ballopt_brect[3]),
                 OptionsB(screen, sett, sett.ballopt_options[4], sett.ballopt_brect[4])]

    pygame.mouse.set_visible(False)

    # Main Loop
    while rungame:

        # Frame Control
        clock.tick(sett.fps)
        fps = int(clock.get_fps())

        # Check Events
        rungame = e.check_events(sett, opt, buttons, b_genopt, b_padopt, b_ballopt, b_about,
                                 paddle1, paddle2)

        # If game not paused, update objects
        if not sett.game_pause:
            paddle1.update(opt, ball)
            paddle2.update(opt, ball)
            ball.update(opt, paddle1, paddle2)

        # Update Screen
        e.update(screen, sett, opt, fps, paddle1, paddle2, ball,
                 buttons, b_genopt, b_padopt, b_ballopt, b_about)


if __name__ == '__main__':
    main()
