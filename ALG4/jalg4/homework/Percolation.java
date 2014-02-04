/**
 * Created by sean on 2/4/14.
 */
public class Percolation {
    private WeightedQuickUnionUF uf;
    /**
     *create N-by-N grid, with all sites blocked
     */
    public Percolation(int N)
    {
        uf = new WeightedQuickUnionUF(N * N);
    }

    /**
     * open site (i, j) if it is not already
     * @param i row number
     * @param j column number
     */
    public void open(int i, int j)
    {

    }

    /**
     * is site (i, j) open?
     * @param i row number
     * @param j column number
     * @return
     */
    public boolean isOpen(int i, int j)
    {
        return false;
    }

    /**
     * is site (i, j) full?
     * @param i row number
     * @param j column number
     * @return true if the side was full
     */
    public boolean isFull(int i, int j)
    {
        return false;
    }

    /**
     * does the system percolate?
     * @return true if the system was perocolated
     */
    public boolean percolates()
    {
        return false;
    }
}

