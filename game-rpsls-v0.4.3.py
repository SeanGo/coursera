import random
import matplotlib.pyplot as plt


'''The Payoff Matrix
   Abbreviate Rock-Paper-Scissors-Lizard-Spock to ('r', 'p', 'c', 'l', 's').
   The element of matrix is a odered payoff-pair (x, y) what the first number
   is payoff of human, sencond number is payoff of computer. Usually,  x, y 
   are blons (-1, 0, 1) to indecate (win, dogfall, loss) situation, but actully
   we can change these payoff to any value.
'''
pm =[#     r         p         c         l         s
    [( 0,  0), (-1,  1), ( 1, -1), ( 1, -1), (-1,  1)], #r
    [( 1, -1), ( 0,  0), (-1,  1), (-1,  1), ( 1, -1)], #p
    [(-1,  1), ( 1, -1), ( 0,  0), ( 1, -1), (-1,  1)], #c
    [(-1,  1), ( 1, -1), (-1,  1), ( 0,  0), ( 1, -1)], #l
    [( 1, -1), (-1,  1), ( 1, -1), (-1,  1), ( 0,  0)]  #s
    ]#     r         p         c         l         s

weapons = ['rock', 'paper', 'scissors', 'lizard', 'Spock']
short_weapons = ['r', 'p', 'c', 'l', 's']
Dict = {'r' : 0, 'p' : 1, 'c' : 2, 'l' : 3, 's' : 4}
str_result = ['Computer wins!', 'Player and computer tie!', 'Player wins!']

window_length = 15

global human_score      #to store human's score
global computer_score   #to store computer's score
global game_counter     #a counter to store the times of game
global history          #to store result of each game
global prb_human        #the probability of human
global prb_computer     #the probability-interval of computer
global human_history    #to store human's history, this is string

human_score   = computer_score = game_counter = 0
history       = []
human_history = '' #set to a empty string
prb_human     = [.0, .0, .0, .0, 0.0]
prb_computer  = [.2, .4, .6, .8, 1.0]

#computer generate a random number [0, 4] according to prb_computer
#and return the weapon in weapons list
def computer_play():
    #return short_weapons[int(rands() * 5) - 1]
    p = random.random()
    index = 0 #Rock
    if   (prb_computer[0] <= p < prb_computer[1]):
        index = 1 #Peper
    elif (prb_computer[1] <= p < prb_computer[2]):
        index = 2 #Scissors
    elif (prb_computer[2] <= p < prb_computer[3]):
        index = 3 #Lizard
    elif (prb_computer[3] <= p < prb_computer[4]):
        index = 4 #Spock
    return short_weapons[index]

def play_game(human):
    global human_score, computer_score, history, game_counter, human_history
    global prb_human    #the probability-interval of human
    global prb_computer #the probability-interval of computer

    #compluter play
    computer = computer_play()
    #get payoff from matrix
    r = pm[Dict[human]][Dict[computer]]
    human_history += human
    #Accumulate total score
    game_counter   += 1
    human_score    += r[0]
    computer_score += r[1]
    
    #store the result into history
    history.append((human, computer))
    print '[GAME ' + str(game_counter) + ']: You play ' + weapons[Dict[human]] + ' Computer play ' + weapons[Dict[computer]] + ', ' + str_result[r[0] + 1]
    show_score()

#find max H factor of payoff
#if the probability is equivalent, then return -1
#else return the index of max H factor
def max_payoff_factor(prob):
    #set the H[0] is equivalent probability 0.20
    #H1 - H5 corresponding to weapon rock - Spock
    H  =  [0.2, .0, .0, .0, .0, .0]
    H[1] =    0     - prob[1] + prob[2] + prob[3] - prob[4]
    H[2] =  prob[0] +   0     - prob[2] - prob[3] + prob[4]
    H[3] = -prob[0] + prob[1] +   0     + prob[3] - prob[4]
    H[4] = -prob[0] + prob[1] - prob[2] +    0    + prob[4]
    H[5] =  prob[0] - prob[1] + prob[2] - prob[3] +    0
    max_h = 0;
    for i in range(1, 6):
        if H[i] > H[max_h]:
            max_h = i
    #return the index of max, -1 corresponding to equivalent probability of human
    return max_h - 1

#get last 20 human-games in human_history string
def get_effective_history_string():
    global human_history
    last = 20
    if (len(human_history) < last):
        last = len(human_history)
    last_games = human_history[-last:]
    return last_games

#calculate and adjust the next weapon probability
def calculate_next_weapon_probability(history, repeted_times):
    next_weapon = [.0, .0, .0, .0, .0]
    next_prob   = [.0, .0, .0, .0, .0]
    #find previous repeted game
    str_his = history
    for i in range(0, repeted_times - 1):
        next_char_positoin = str_his.find(history[-2:]) + 2
        next_weapon[Dict[str_his[next_char_positoin]]] += 1
        str_his = str_his[next_char_positoin:]

    if (max(next_weapon) > 0):
        for i in range(0, len(weapons)):
            next_prob[i]  = next_weapon[i] / sum(next_weapon)
        return next_prob
    return None


def adjust_computer_probability_by_pattern():
    global prb_computer
    history = get_effective_history_string()
    #first pattern is last 2 games
    #find pattern, if exists one 
    repeated_times = history.count(history[-2:])
    #repeted 4+ times, because five weapons can repete 4 times in 20 games
    if (repeated_times > 3):
        #find max likehood for next weapon
        next_prob = calculate_next_weapon_probability(history, repeated_times)
        if (next_prob is not None):
            #adjust by pattern
            weapon_pattern = max_payoff_factor(next_prob)
            #weigth of fraqunce is 0.5, weight of pattern is 0.5
            if (weapon_pattern > -1):
                for i in range(0, len(weapons)):
                    prb_computer[i] *= .5
                prb_computer[weapon_pattern] += .5


def adjust_computer_probability_by_frequency():
    global prb_computer
    weapon_fraquency = max_payoff_factor(prb_human)
    if (weapon_fraquency < 0):
        prb_computer = [.2, .4, .6, .8, 1.0]
    else:
        prb_computer = [.0, .0, .0, .0,  .0]
        prb_computer[weapon_fraquency] = 1.0


def calculate_computer_probability():
    global prb_human
    #calculate human's probability
    prb_human  =  [.0, .0, .0, .0, .0]
    prb_human_history = [.0, .0, .0, .0, .0]
    for i in range(game_counter - 1, game_counter - window_length - 1, -1):
        prb_human_history[Dict[history[i][0]]] += 1
    for i in range(0, 5):
        prb_human[i] = prb_human_history[i] / window_length

    #adjust by frequnce
    adjust_computer_probability_by_frequency()

    #find the pattern
    adjust_computer_probability_by_pattern()


#Show Probability
def show_stat():
    global prb_human, prb_computer
    if (game_counter < window_length):
        print 'nothing to show'
        return
    print '>>> Human probability: '
    for i in range(0, 5):
        print '>>> ' + weapons[i] + ' -> ' + str(prb_human[i])
    print

    print '<<< Computer probability'
    print '<<< ' + weapons[0] + ' -> ' + str(prb_computer[0])
    for i in range(1, 5):
        if (prb_computer[i] > prb_computer[i -  1]):
            print '<<< ' + weapons[i] + ' -> ' + str(prb_computer[i] - prb_computer[i - 1])
        else:
            print '<<< ' + weapons[i] + ' -> 0'
    print


#Draw the game process
def draw_walk():
    global history

    if (game_counter < 2):
        print "nothing to show"
        return
    x  = range(0, game_counter + 1)
    hs = [0]
    cs = [0]
    hg = [0]
    cg = [0]
    #first game reulst
    r = pm[Dict[history[0][0]]][Dict[history[0][1]]]
    hs.append(r[0])
    cs.append(r[1])
    hg.append(Dict[history[0][0]])
    cg.append(Dict[history[0][1]])
    #Accumulate score
    for i in range(1, game_counter):
        hg.append(Dict[history[i][0]])
        cg.append(Dict[history[i][1]])
        r = pm[Dict[history[i][0]]][Dict[history[i][1]]]
        hs.append(hs[i] + r[0])
        cs.append(cs[i] + r[1])
    plt.figure(0)
    plt.plot(x, hg, 'x', x, cg, 'o')
    plt.draw()
    plt.legend(['Human', 'Computer'])
    plt.figure(1)
    plt.plot(x, hs, x, cs)
    plt.draw()
    plt.legend(['Human', 'Computer'])
    plt.show()


def show_score():
    global game_counter, human_score, computer_score
    print '[GAME ' + str(game_counter) + ']: Your total score is ' + str(human_score) + ', computer got ' + str(computer_score)


#Show help
def how_to_play():
    print '\
\n------------------------------ HOW TO PLAY -------------------------------\n\
input (r, p, c, l, s) to play game,\n\
r for Rock, p for Paper, c for Scissors, l for Lizard, s for Spock\n\
or input command:\n\
"show" to show the game result, after close all graphs game will continue,\n\
"stat" to show the probability of human and computer,\n\
"score" to show total score,\n\
"human" to show human\'s history,\n\
"h" for displa this help,\n\
"q" for quit game\n\
------------------------------ HOW TO PLAY -------------------------------\n'


def Game():
    global history, game_counter, human_history
    human = '0'
    command = ['h', 'q', 'show', 'stat', 'score']
    game = ['r', 'p', 'c', 'l', 's'];
    while human is not 'q':
        human = raw_input('Input your weapon(h for help): ')
        if human in game:
                play_game(human)
                if game_counter >= window_length:
                    calculate_computer_probability()
        elif human in command:
            if human == 'h':
                how_to_play()
            elif human == 'q':
                break;
            elif human == 'stat':
                show_stat()
            elif human == 'show':
                draw_walk()
            elif human == 'human':
                print human_history
            elif human == 'score':
                show_score()
        else:
            how_to_play()
    print "Goodbye!"

if __name__ == '__main__':
    Game()
