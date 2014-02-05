import random
import math
import pylab
import numpy as np

def markov_pi(N, delta): 
    x, y = 1.0, 1.0
    n_hits = 0
    n_acceptance = 0
    for i in range(N):
        del_x, del_y = random.uniform(-delta, delta), random.uniform(-delta, delta)
        if abs(x + del_x) < 1.0 and abs(y + del_y) < 1.0:
            x, y = x + del_x, y + del_y
            n_acceptance = n_acceptance + 1
        if x**2 + y**2 < 1.0: n_hits += 1
    return n_hits, n_acceptance

n_runs     = 500
n_trials   = 1000 #4000
delta_list = []
ar_list    = []
pi_list    = []
sigmas     = []
for delta in np.arange(0.1, 5.1, 0.1):
    ar_    = 0
    pi_    = 0.0
    sigma_ = 0.0
    for run in range(n_runs):
        n_hits, n_acceptance = markov_pi(n_trials, delta)
        new_pi_ = 4 * float(n_hits) / float(n_trials)
        ar_     = ar_ + float(n_acceptance) / float(n_trials)
	pi_     = pi_ + new_pi_
        sigma_ += (new_pi_ - math.pi) ** 2
    pi_ = pi_ / float(n_runs)
    ar_  = ar_ / float(n_runs)
    sigma_ = math.sqrt(sigma_/(n_runs))
    pi_list.append(pi_)
    ar_list.append(ar_)
    sigmas.append(sigma_)
    delta_list.append(delta)
    print delta, ar_, pi_, sigma_

pylab.plot(delta_list, ar_list, 'o')
pylab.gca().set_xscale('linear')
pylab.gca().set_yscale('linear')
pylab.xlabel('$\delta$')
pylab.ylabel('Acceptance Ratio')
pylab.title('Acceptance Ratio vs $\delta$')
pylab.savefig('ar_vs_delta.png')
pylab.show()

for i in range(len(ar_list)):
    if (abs(ar_list[i] - 0.5) < 0.025):
        print ar_list[i], delta_list[i]


pylab.plot(delta_list, sigmas, 'o')
pylab.gca().set_xscale('linear')
pylab.gca().set_yscale('linear')
pylab.xlabel('$\delta$')
pylab.ylabel('Rms Error')
pylab.title('Rms Error vs $\delta$')
pylab.savefig('rmserr_vs_delta.png')
pylab.show()



