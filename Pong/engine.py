# Pong : engine.py
# Boredom Project

import sys
import pygame

button_clickable = True

genopt_clicked = False
padopt_clicked = False
ballopt_clicked = False
about_clicked = False

inabout = False

def check_events(sett, opt, buttons, b_genopt, b_padopt, b_ballopt, b_about,
                 paddle1, paddle2):

    exit_game = False

    # Event Handler
    for event in pygame.event.get():

        if event.type is pygame.QUIT:
            exit_game = True

        if event.type is pygame.MOUSEBUTTONDOWN:
            mousex, mousey = pygame.mouse.get_pos()
            mousedown(event, sett, opt, buttons, b_genopt, b_padopt, b_ballopt, b_about,
                      mousex, mousey)

        if event.type is pygame.KEYDOWN:
            keydown(event, sett, paddle1, paddle2)
        if event.type is pygame.KEYUP:
            keyup(event, paddle1, paddle2)

    if exit_game:
        return False
    else:
        return True

def mousedown(event, sett, opt, buttons, b_genopt, b_padopt, b_ballopt, b_about,
              mousex, mousey):

    global button_clickable, genopt_clicked, padopt_clicked, ballopt_clicked, \
        about_clicked, inabout

    if sett.game_pause:
        for button in buttons:
            clicked = button.rect.collidepoint(mousex, mousey)

            if clicked and button_clickable:
                button.clicked = True
                button_clickable = False

                if button.msg == sett.options_menu[0]:
                    genopt_clicked = True
                elif button.msg == sett.options_menu[1]:
                    padopt_clicked = True
                elif button.msg == sett.options_menu[2]:
                    ballopt_clicked = True
                elif button.msg == sett.options_menu[3]:
                    about_clicked = True

                break

        for button in b_about:
            clicked = button.rect.collidepoint(mousex, mousey)

            if clicked and not button_clickable and about_clicked:

                if inabout:

                    button.clicked = not button.clicked

                    if button.msg == sett.about_menu[0]:
                        b_about[1].clicked = False
                        b_about[2].clicked = False
                        b_about[3].clicked = False
                    elif button.msg == sett.about_menu[1]:
                        b_about[0].clicked = False
                        b_about[2].clicked = False
                        b_about[3].clicked = False
                    elif button.msg == sett.about_menu[2]:
                        b_about[0].clicked = False
                        b_about[1].clicked = False
                        b_about[3].clicked = False
                    elif button.msg == sett.about_menu[3]:
                        b_about[0].clicked = False
                        b_about[1].clicked = False
                        b_about[2].clicked = False

                    if button.msg == sett.about_menu[4]:
                        b_about[0].clicked = False
                        b_about[1].clicked = False
                        b_about[2].clicked = False
                        b_about[3].clicked = False
                        b_about[4].clicked = False

                        buttons[3].clicked = False
                        about_clicked = False
                        button_clickable = True

                if about_clicked:
                    inabout = True
                else:
                    inabout = False

        for button in b_genopt:
            clicked = button.rect.collidepoint(mousex, mousey)

            if clicked and not button_clickable and genopt_clicked:
                button.change(sett)

                if button.options[0] == '1 Player':  # SINGLE or TWO PLAYER
                    if button.chosen_opt is 0:
                        opt.oneplayer = True
                        opt.twoplayer = False
                    else:
                        opt.oneplayer = False
                        opt.twoplayer = True

                elif button.options[0] == ' No':  # SHOW FPS
                    if button.chosen_opt is 1:
                        opt.sfps = True
                    else:
                        opt.sfps = False

                elif button.options[0] == 'Classic':  # GAME SCORING METHOD
                    if button.chosen_opt is 0:
                        opt.scoring_mode = [True, False]
                    else:
                        opt.scoring_mode = [False, True]

                if button.options[0] == '< Back':  # LEAVE GENERAL OPTIONS MENU
                    buttons[0].clicked = False
                    button_clickable = True
                    genopt_clicked = False

        for button in b_padopt:
            clicked = button.rect.collidepoint(mousex, mousey)

            if clicked and not button_clickable and padopt_clicked:

                if button.options[0] is None:  # PADDLE SPEED
                    button.changenum(sett, event.button)
                    opt.pSpeed = button.numiter

                elif button.options[0] == 'False':
                    button.change(sett)
                    opt.paddle1_cc = not opt.paddle1_cc

                elif button.options[0] == ' True':
                    button.change(sett)
                    opt.paddle2_cc = not opt.paddle2_cc

                if button.options[0] == '< Back':  # LEAVE GENERAL OPTIONS MENU
                    buttons[1].clicked = False
                    button_clickable = True
                    padopt_clicked = False

        for button in b_ballopt:
            clicked = button.rect.collidepoint(mousex, mousey)

            if clicked and not button_clickable and ballopt_clicked:

                if button.options[0] == 'uss':
                    button.changenum(sett, event.button)
                    opt.u_ss = button.numiter

                elif button.options[0] == 'Random':
                    button.change(sett)
                    opt.b_xyspeed_random = not opt.b_xyspeed_random

                elif button.options[0] == 'bxs' and not opt.b_xyspeed_random:
                    button.changenum(sett, event.button)
                    opt.b_xspeed = button.numiter

                elif button.options[0] == 'bys' and not opt.b_xyspeed_random:
                    button.changenum(sett, event.button)
                    opt.b_yspeed = button.numiter

                if button.options[0] == '< Back':
                    buttons[2].clicked = False
                    button_clickable = True
                    ballopt_clicked = False

def keydown(event, sett, paddle1, paddle2):

    if event.key is pygame.K_ESCAPE:
        sett.game_pause = not sett.game_pause
        pygame.mouse.set_visible(sett.game_pause)

    if event.key is pygame.K_w:
        paddle1.movingup = True
    elif event.key is pygame.K_s:
        paddle1.movingdown = True

    if event.key is pygame.K_i:
        paddle2.movingup = True
    elif event.key is pygame.K_k:
        paddle2.movingdown = True

def keyup(event, paddle1, paddle2):

    if event.key is pygame.K_w:
        paddle1.movingup = False
    elif event.key is pygame.K_s:
        paddle1.movingdown = False

    if event.key is pygame.K_i:
        paddle2.movingup = False
    elif event.key is pygame.K_k:
        paddle2.movingdown = False

def update(screen, sett, opt, fps, paddle1, paddle2, ball,
           buttons, b_genopt, b_padopt, b_ballopt, b_about):

    draw(screen, sett, opt, fps, paddle1, paddle2, ball,
         buttons, b_genopt, b_padopt, b_ballopt, b_about)

    # Flip
    pygame.display.flip()

def draw(screen, sett, opt, fps, paddle1, paddle2, ball,
         buttons, b_genopt, b_padopt, b_ballopt, b_about):

    # Clear Screen
    screen.fill(sett.black)

    # -------------------------------------------------
    draw_dashed_line(screen, (sett.width, sett.height))

    # Draw Paddles
    pygame.draw.rect(screen, opt.c_paddle1, paddle1.rect)
    pygame.draw.rect(screen, opt.c_paddle2, paddle2.rect)

    # Draw Ball
    pygame.draw.rect(screen, [255, 0, 0], ball.rect, 1)
    pygame.draw.circle(screen, [255, 255, 255], ball.pos, ball.radius)

    # Data
    if opt.sfps:
        showfps(screen, sett, fps)

    score(screen, sett, ball)

    if sett.game_pause:
        game_pause(screen, sett, buttons, b_genopt, b_padopt, b_ballopt, b_about)


# OTHER STUFF
def showfps(screen, sett, fps):

    text = str(fps)
    textimage = sett.ffps.render(text, True, sett.green, None)

    textrect = textimage.get_rect()
    textrect.left = screen.get_rect().left + 6
    textrect.top = 6

    screen.blit(textimage, textrect)

def score(screen, sett, ball):

    left_score = str(ball.leftscore)
    ls_image = sett.score.render(left_score, True, sett.white, None)

    ls_rect = ls_image.get_rect()
    ls_rect.centerx = screen.get_rect().width/4
    ls_rect.top = 10

    screen.blit(ls_image, ls_rect)

    right_score = str(ball.rightscore)
    rs_image = sett.score.render(right_score, True, sett.white, None)

    rs_rect = rs_image.get_rect()
    rs_rect.centerx = screen.get_rect().width - screen.get_rect().width/4
    rs_rect.top = 10

    screen.blit(rs_image, rs_rect)

def draw_dashed_line(screen, dimensions):

    xpos = dimensions[0]/2 - 1
    ypos = 3

    while ypos < dimensions[1]:

        pygame.draw.line(screen, [255, 255, 255], (xpos, ypos), (xpos, ypos + 3), 1)
        ypos += 10

def game_pause(screen, sett, buttons, b_genopt, b_padopt, b_ballopt, b_about):

    global button_clickable, genopt_clicked, padopt_clicked, ballopt_clicked

    screen.fill(sett.c_pause, sett.ps_rect)

    button_clicked = False

    for button in buttons:
        if button.clicked:
            button_clicked = True

            if button.msg == sett.options_menu[0] and genopt_clicked:
                button_clicked = genopt(screen, sett, b_genopt)

            elif button.msg == sett.options_menu[1] and padopt_clicked:
                button_clicked = padopt(screen, sett, b_padopt)

            elif button.msg == sett.options_menu[2] and ballopt_clicked:
                button_clicked = ballopt(screen, sett, b_ballopt)

            elif button.msg == sett.options_menu[3]:
                button_clicked = about(screen, sett, b_about)

            elif button.msg == sett.options_menu[4]:
                sett.game_pause = False
                button.clicked = False
                button_clickable = True

            elif button.msg == sett.options_menu[5]:
                sys.exit()

    if not button_clicked:
        for button in buttons:
            button.draw()

# BUTTON HANDLING
def genopt(screen, sett, b_genopt):

    iypos = 30

    for item in sett.genopt_menu:
        image = sett.ps_font.render(item, True, sett.black, None)
        imagerect = image.get_rect()

        imagerect.x = 40
        imagerect.top = iypos

        screen.blit(image, imagerect)

        iypos += 40

    for button in b_genopt:
        button.draw()

    return True

def padopt(screen, sett, b_padopt):

    iypos = 30

    for item in sett.padopt_menu:
        image = sett.ps_font.render(item, True, sett.black, None)
        imagerect = image.get_rect()

        imagerect.x = 35
        imagerect.top = iypos

        screen.blit(image, imagerect)

        iypos += 40

    for button in b_padopt:
        button.draw()

    return True

def ballopt(screen, sett, b_ballopt):

    iypos = 30

    for item in sett.ballopt_menu:
        image = sett.ps_font.render(item, True, sett.black, None)
        imagerect = image.get_rect()

        imagerect.x = 35
        imagerect.top = iypos

        screen.blit(image, imagerect)

        iypos += 40

    for button in b_ballopt:
        button.draw()

    return True

def about(screen, sett, b_about):

    global a_credits

    for button in b_about:
        button.draw(sett)

        if button.clicked:

            if button.msg == sett.about_menu[0]:

                iterator = 40

                for string in a_about:
                    textimage = sett.abf_instructions.render(string, True, sett.black, None)
                    imagerect = textimage.get_rect()

                    imagerect.centerx = 668
                    imagerect.y = iterator

                    screen.blit(textimage, imagerect)
                    iterator += 20

            if button.msg == sett.about_menu[1]:

                iterator = 20

                for string in a_instructions:
                    textimage = sett.abf_instructions.render(string, True, sett.black, None)
                    imagerect = textimage.get_rect()

                    imagerect.centerx = 668
                    imagerect.y = iterator

                    screen.blit(textimage, imagerect)
                    iterator += 20

            if button.msg == sett.about_menu[2]:

                iterator = 20

                for string in a_technical:
                    textimage = sett.abf_technical.render(string, True, sett.black, None)
                    imagerect = textimage.get_rect()

                    imagerect.centerx = 668
                    imagerect.y = iterator

                    screen.blit(textimage, imagerect)
                    iterator += 20

            if button.msg == sett.about_menu[3]:

                iterator = 90

                for string in a_credits:
                    textimage = sett.abf_credits.render(string, True, sett.black, None)
                    imagerect = textimage.get_rect()

                    imagerect.centerx = 668
                    imagerect.y = iterator

                    screen.blit(textimage, imagerect)
                    iterator += 20

    return True


a_about = ['The Boredom Project: Pong',
           'About Pong',
           '------',
           '',
           'Pong is one of the earliest arcade video games. It is a table tennis',
           'sports game featuring simple two-dimensional graphics. The game was',
           'originally manufactured by Atari, which released it in 1972.',
           '- Wikipedia',
           '',
           'https://en.wikipedia.org/wiki/Pong']

a_instructions = ['The Boredom Project: Pong',
                  'Instructions',
                  '------',
                  '',
                  'HOW TO MOVE',
                  '-',
                  'Paddle1 (Cyan) can be moved up and down using W and S, respectively.',
                  'Paddle2 (Magenta) can be moved up and down using I and K, respectively.',
                  '',
                  'SCORING',
                  '-',
                  'Mode: Classic. Gain 1 point every time you score.',
                  'Mode: Defense. Gain 1 point every time the ball is succesfully deflected',
                  'and lose 5 points every time the opponent scores.',
                  '',
                  'PADDLE',
                  '-',
                  'Paddle Speed changes the speed of the paddle.',
                  'CC stands for Computer Controlled. Enabling CC makes the computer control',
                  'the Paddle which CC is enabled for.',
                  '',
                  'BALL',
                  '-',
                  'Universal Serve Speed changes the serving speed of the ball.',
                  'Ball Bounce Mode: Random randomizes the X, Y speed of the ball everytime',
                  'the ball updates.',
                  'Ball Bounce Mode: Static allows users to set the X, Y speed of the ball.']

a_technical = ['The Boredom Project: Pong',
               'Technical Details',
               '------',
               '',
               'MOVEMENT DETAILS',
               '1 unit = 1 PXU, or 1 Pixel Unit.',
               'Every moving object moves by a multiple of 1 PXU per frame.',
               'On average, the game updates at 175 Frames Per Second.',
               'By default, the paddle moves at 3 PXU, so it moves',
               '3 PXU * 175 FPS = 525 PXU/S',
               '--',
               "The ball's X, Y movement is random. Pseudocode being:",
               'ball y speed = random integer between 1 & 4 PXU per frame, including 1 & 4',
               'ball x speed = 6 - ball y speed',
               'This ensures that the net PXU moved per frame equals 6.',
               '--',
               "That is literally it. Like, there are only 2 really 'technical'",
               'details. The ball, and the paddle.']

a_credits = ['The Boredom Project',
             'Pong',
             '',
             'A FlamingThanatos Production Recreation',
             'by Andrew Woo',
             'Version 0.1.0',
             '',
             'Andrew Woo: Programmer, Art, Sound',
             'Rémi Lagast: Font Gasalt Regular v2 (not affiliated)',
             '',
             'My Email: seungminleader@gmail.com',
             'Website: flamingthanatos.github.io',
             '',
             "Don't contact me. I'll move your email to spam.",
             'Have fun I guess? I mean, it is literally one of',
             'the first game ever made... so... Look out for my',
             'other The Boredom Project programs.',
             '-----------']
