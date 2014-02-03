import java.lang.*;

/**
 * Created by sean on 2/4/14.
 */
public class PercolationStats {
    private int N;  ///N-by-N grid
    private int T;  ///T independent computational experiments
    private double[] radio; ///the radio array
    private double mu;      ///mean of radio
    private double std;     ///stddev of radio
    private double hiconf;  ///upper bound of the 95% confidence interval
    private double lowconf; ///lower bound of the 95% confidence interval

    /**
     * perform T independent computational experiments on an N-by-N grid
     * @param N N-by-N grid
     * @param T T independent computational experiments, must be >= 2
     * @throws java.lang.IllegalArgumentException when N ≤ 0 or T < 2.
     */
    public PercolationStats(int N, int T)
        throws java.lang.IllegalArgumentException
    {
        if (N <= 0 || T < 2)
            throw new java.lang.IllegalArgumentException();

        this.N = N;
        this.T = T;

        radio = new double[T];
        mu = std = hiconf = lowconf = -1;
    }

    /**
     * reset the mu, std, hiconf and low conf to -1 for new comutational experiment
     */
    private void reset()
    {
        mu = std = hiconf = lowconf = -1;
    }

    /**
     * sample mean of percolation threshold
     * @return the mean value
     */
    public double mean()
    {
        if (mu < 0) {
            double sum = 0;
            for (int i = 0; i < T; ++i)
                sum += radio[i];
            mu = sum / (double)T;
        }
        return mu;
    }

    /**
     * sample standard deviation of percolation threshold
     * @return the standard dev value
     */
    public double stddev()
    {
        if (std < 0) {
            double themu = mean();
            for (int i = 0; i < T; ++i)
                std += (radio[i] - themu) *(radio[i] - themu);
            std = Math.sqrt(std/(T - 1));
        }
        return std;
    }

    /**
     * returns lower bound of the 95% confidence interval
     * @return
     */
    public double confidenceLo()
    {
        if (lowconf < 0) {
            double themu = mean();
            double thestd = stddev();

            lowconf = themu - 1.96 * thestd / Math.sqrt(T);
        }
        return (lowconf);
    }

    /**
     * returns upper bound of the 95% confidence interval
     * @return
     */
    public double confidenceHi()
    {
        if (hiconf < 0) {
            double themu = mean();
            double thestd = stddev();

            hiconf = themu + 1.96 * thestd / Math.sqrt(T);
        }
        return (hiconf);
    }

    /**
     * calculate statistics, mu, std, hi-low confidence
     */
    public void statistics()
    {
        mean();
        stddev();
        confidenceLo();
        confidenceHi();
    }

    /**
     * test client, described below
     * @param args
     */
    public static void main(String[] args)
    {

    }
}
