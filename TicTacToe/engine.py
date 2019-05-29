# Tic Tac Toe : engine.py
# Boredom Project

import pygame
from scoring import *

score = Score()

def check_events(board, cross, circle, rboard, reset):

    exit_game = False

    # Event Handler
    for event in pygame.event.get():

        if event.type is pygame.QUIT:
            exit_game = True

        if event.type is pygame.MOUSEBUTTONDOWN:
            mousex, mousey = pygame.mouse.get_pos()
            mousedown(event, board, (mousex, mousey), cross, circle, rboard, reset)

    if exit_game:
        return False
    else:
        return True

def mousedown(event, board, mpos, cross, circle, rboard, reset):

    rboard_clicked = rboard.crect.collidepoint(mpos[0], mpos[1])
    reset_clicked = reset.crect.collidepoint(mpos[0], mpos[1])

    if rboard_clicked:
        for x in cross:
            x.draw = False
        for o in circle:
            o.draw = False

        board.reset()
        score.reset()

    if reset_clicked:
        for x in cross:
            x.draw = False
        for o in circle:
            o.draw = False

        board.reset()
        score.reset()

        score.x_score = 0
        score.o_score = 0

    if not score.gameover and event.button is 1:

        a1_clicked = board.carre_a1.collidepoint(mpos[0], mpos[1])
        a2_clicked = board.carre_a2.collidepoint(mpos[0], mpos[1])
        a3_clicked = board.carre_a3.collidepoint(mpos[0], mpos[1])

        b1_clicked = board.carre_b1.collidepoint(mpos[0], mpos[1])
        b2_clicked = board.carre_b2.collidepoint(mpos[0], mpos[1])
        b3_clicked = board.carre_b3.collidepoint(mpos[0], mpos[1])

        c1_clicked = board.carre_c1.collidepoint(mpos[0], mpos[1])
        c2_clicked = board.carre_c2.collidepoint(mpos[0], mpos[1])
        c3_clicked = board.carre_c3.collidepoint(mpos[0], mpos[1])

        if a1_clicked:
            if board.board_used['a1'] is False:
                board.board_used['a1'] = True

                if board.x_turn:
                    cross[0].draw = True
                    board.board_x[0] = 1
                elif board.o_turn:
                    circle[0].draw = True
                    board.board_o[0] = 1

                board.x_turn = not board.x_turn
                board.o_turn = not board.o_turn

                board.turns += 1

        elif a2_clicked:
            if board.board_used['a2'] is False:
                board.board_used['a2'] = True

                if board.x_turn:
                    cross[1].draw = True
                    board.board_x[1] = 1
                elif board.o_turn:
                    circle[1].draw = True
                    board.board_o[1] = 1

                board.x_turn = not board.x_turn
                board.o_turn = not board.o_turn

                board.turns += 1

        elif a3_clicked:
            if board.board_used['a3'] is False:
                board.board_used['a3'] = True

                if board.x_turn:
                    cross[2].draw = True
                    board.board_x[2] = 1
                elif board.o_turn:
                    circle[2].draw = True
                    board.board_o[2] = 1

                board.x_turn = not board.x_turn
                board.o_turn = not board.o_turn

                board.turns += 1

        elif b1_clicked:
            if board.board_used['b1'] is False:
                board.board_used['b1'] = True

                if board.x_turn:
                    cross[3].draw = True
                    board.board_x[3] = 1
                elif board.o_turn:
                    circle[3].draw = True
                    board.board_o[3] = 1

                board.x_turn = not board.x_turn
                board.o_turn = not board.o_turn

                board.turns += 1

        elif b2_clicked:
            if board.board_used['b2'] is False:
                board.board_used['b2'] = True

                if board.x_turn:
                    cross[4].draw = True
                    board.board_x[4] = 1
                elif board.o_turn:
                    circle[4].draw = True
                    board.board_o[4] = 1

                board.x_turn = not board.x_turn
                board.o_turn = not board.o_turn

                board.turns += 1

        elif b3_clicked:
            if board.board_used['b3'] is False:
                board.board_used['b3'] = True

                if board.x_turn:
                    cross[5].draw = True
                    board.board_x[5] = 1
                elif board.o_turn:
                    circle[5].draw = True
                    board.board_o[5] = 1

                board.x_turn = not board.x_turn
                board.o_turn = not board.o_turn

                board.turns += 1

        elif c1_clicked:
            if board.board_used['c1'] is False:
                board.board_used['c1'] = True

                if board.x_turn:
                    cross[6].draw = True
                    board.board_x[6] = 1
                elif board.o_turn:
                    circle[6].draw = True
                    board.board_o[6] = 1

                board.x_turn = not board.x_turn
                board.o_turn = not board.o_turn

                board.turns += 1

        elif c2_clicked:
            if board.board_used['c2'] is False:
                board.board_used['c2'] = True

                if board.x_turn:
                    cross[7].draw = True
                    board.board_x[7] = 1
                elif board.o_turn:
                    circle[7].draw = True
                    board.board_o[7] = 1

                board.x_turn = not board.x_turn
                board.o_turn = not board.o_turn

                board.turns += 1

        elif c3_clicked:
            if board.board_used['c3'] is False:
                board.board_used['c3'] = True

                if board.x_turn:
                    cross[8].draw = True
                    board.board_x[8] = 1
                elif board.o_turn:
                    circle[8].draw = True
                    board.board_o[8] = 1

                board.x_turn = not board.x_turn
                board.o_turn = not board.o_turn

                board.turns += 1

def update(screen, sett, board, cross, circle, rboard, reset):

    if board.turns >= 5:
        score.check(board)

    # Clear Screen
    screen.fill(sett.white)

    # Draw Stuff
    board.draw_object(screen)

    for x in cross:
        if x.draw:
            x.draw_object(screen)

    for o in circle:
        if o.draw:
            o.draw_object(screen)

    xscore = 'X Score: ' + str(score.x_score)

    xs_image = sett.s_font.render(xscore, True, sett.black, None)
    xs_rect = xs_image.get_rect()

    xs_rect.x = 5
    xs_rect.y = 520

    screen.blit(xs_image, xs_rect)

    oscore = 'O Score: ' + str(score.o_score)

    os_image = sett.s_font.render(oscore, True, sett.black, None)
    os_rect = os_image.get_rect()

    os_rect.x = sett.width - (os_rect.width + 5)
    os_rect.y = 520

    screen.blit(os_image, os_rect)

    rboard.draw_button(screen)
    reset.draw_button(screen)

    # Flip
    pygame.display.flip()
