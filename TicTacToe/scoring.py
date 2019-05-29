# Tic Tac Toe : scoring.py
# Boredom Project

class Score:

    def __init__(self):

        self.x_score = 0
        self.o_score = 0

        self.gameover = False

        self.x_win = False
        self.o_win = False

        self.final_check_x = [[0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0]]

        self.final_check_o = [[0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0]]

    def check(self, board):

        for sindex, scenario in enumerate(scenarios):
            for index, item in enumerate(scenario):

                if item is 1:
                    if board.board_x[index] is 1:
                        self.final_check_x[sindex][index] = 1

            if self.final_check_x[sindex] == scenario:
                self.x_win = True
                self.scored([True, False])
                self.gameover = True
                break

        for sindex, scenario in enumerate(scenarios):
            for index, item in enumerate(scenario):

                if item is 1:
                    if board.board_o[index] is 1:
                        self.final_check_o[sindex][index] = 1

            if self.final_check_o[sindex] == scenario:
                self.o_win = True
                self.scored([False, True])
                self.gameover = True
                break

    def scored(self, scorer):

        if scorer[0] and not self.gameover:
            self.x_score += 1
        elif scorer[1] and not self.gameover:
            self.o_score += 1

    def reset(self):

        self.gameover = False

        self.x_win = False
        self.o_win = False

        self.final_check_x = [[0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0]]

        self.final_check_o = [[0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0],

                              [0, 0, 0,
                               0, 0, 0,
                               0, 0, 0]]


scenarios = [[1, 1, 1,  # Scenario 0
              0, 0, 0,
              0, 0, 0],

             [0, 0, 0,  # Scenario 1
              1, 1, 1,
              0, 0, 0],

             [0, 0, 0,  # Scenario 2
              0, 0, 0,
              1, 1, 1],

             [1, 0, 0,  # Scenario 3
              1, 0, 0,
              1, 0, 0],

             [0, 1, 0,  # Scenario 4
              0, 1, 0,
              0, 1, 0],

             [0, 0, 1,  # Scenario 5
              0, 0, 1,
              0, 0, 1],

             [1, 0, 0,  # Scenario 6
              0, 1, 0,
              0, 0, 1],

             [0, 0, 1,  # Scenario 7
              0, 1, 0,
              1, 0, 0]]
