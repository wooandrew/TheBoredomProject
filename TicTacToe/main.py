# Tic Tac Toe : main.py
# Boredom Project

# Import & Init pygame
import pygame

pygame.mixer.pre_init(44100, -16, 2, 512)
pygame.init()

# Imports
from settings import *          # noqa
from objects import *           # noqa
import engine as e              # noqa

# Basic Init
sett = Settings()

ICON = pygame.image.load(r'ttt.ico')

# _ Basic Init - Screen Set
screen = pygame.display.set_mode((sett.width, sett.height))
pygame.display.set_caption(sett.caption)
pygame.display.set_icon(ICON)


# Main
def main():
    rungame = True

    board = Board('board.png', (sett.width, sett.height))

    cross = [CrossCircle(board, 'cross.png', 'a1'),
             CrossCircle(board, 'cross.png', 'a2'),
             CrossCircle(board, 'cross.png', 'a3'),
             CrossCircle(board, 'cross.png', 'b1'),
             CrossCircle(board, 'cross.png', 'b2'),
             CrossCircle(board, 'cross.png', 'b3'),
             CrossCircle(board, 'cross.png', 'c1'),
             CrossCircle(board, 'cross.png', 'c2'),
             CrossCircle(board, 'cross.png', 'c3')]

    circle = [CrossCircle(board, 'circle.png', 'a1'),
              CrossCircle(board, 'circle.png', 'a2'),
              CrossCircle(board, 'circle.png', 'a3'),
              CrossCircle(board, 'circle.png', 'b1'),
              CrossCircle(board, 'circle.png', 'b2'),
              CrossCircle(board, 'circle.png', 'b3'),
              CrossCircle(board, 'circle.png', 'c1'),
              CrossCircle(board, 'circle.png', 'c2'),
              CrossCircle(board, 'circle.png', 'c3')]

    clock = pygame.time.Clock()

    rboard = Button(sett, 'Reset Board', (sett.width / 2, 440))
    reset = Button(sett, 'Reset Game', (sett.width / 2, 470))

    while rungame:
        # Frame Control
        clock.tick(sett.fps)

        # Check Events
        rungame = e.check_events(board, cross, circle, rboard, reset)

        # Update
        e.update(screen, sett, board, cross, circle, rboard, reset)


if __name__ == '__main__':
    main()
