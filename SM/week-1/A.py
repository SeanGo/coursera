import random, math, pylab

def direct_pi(N):
    n_hits = 0
    for i in range(N):
        x, y = random.uniform(-1.0, 1.0), random.uniform(-1.0, 1.0)
        if x ** 2 + y ** 2 < 1.0:
            n_hits += 1
    return n_hits

n_runs = 500
n_trials_list = []
sigmas = []
for poweroftwo in range(4, 13):
    n_trials = 2 ** poweroftwo
    sigma = 0.0
    for run in range(n_runs):
        pi_est = 4.0 * direct_pi(n_trials) / float(n_trials)
        sigma += (pi_est - math.pi) ** 2
    rms_err = math.sqrt(sigma/(n_runs))
    sigmas.append(rms_err)
    n_trials_list.append(n_trials)
    print poweroftwo, rms_err, n_trials

for i in range(1, len(n_trials_list)):
    print sigmas[i] / sigmas[i - 1], n_trials_list[i]/n_trials_list[i - 1], sigmas[i]

#
# the mean of sigmas[i] / sigmas[i - 1] is aboub 0.7
#
# asume the n_trails^(-a) = K * rms_err
# n_1^(-a) = K * rms_err_1, n_2^(-a) = K * rms_err_2
# n_1^(-a) / n_2^(-a) = (K * rms_err_1) / (K * rms_err_2) = 0.7
# (n_1/n_2)^(-a) = 0.7
# 2^(-a) = 0.7
# then a = - log_2(0.7)
# and K = n_trails^(-a) / rms_err
#

a = - math.log(0.7, 2)
print a
# get 0.51457317283 for example

# get the K value
for i in range(1, len(n_trials_list)):
    print math.pow(n_trials_list[i], -a) / sigmas[i]

# get 0.564579695658 for example

pylab.plot(n_trials_list, sigmas, 'o')
pylab.gca().set_xscale('log')
pylab.gca().set_yscale('log')
pylab.xlabel('n_trials')
pylab.ylabel('$\sigma$')
pylab.title('Direct sampling: Standard deviation $\sigma$ as a function of n_trials')
pylab.savefig('direct_sampling_statistical_error.png')
pylab.show()

