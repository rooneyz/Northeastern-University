// Author: Zach Rooney
// Date: 2019-07-17

import java.util.Arrays;
import java.util.LinkedList;

public class Hanoi {

    // gameboad
    private Object [] poles = new Object[3];
    // number of disks and moves
    private int ndisks;
    private int moveCount;
    // poles
    private int startPole;
    private int destPole;
    private int middlePole;
    private LinkedList<Integer> p0;
    private LinkedList<Integer> p1;
    private LinkedList<Integer> p2;


    /**
     * Default constructor. Variables initialized to 1 disk and standard src, dest poles
     */
    public Hanoi() {
        this.ndisks = 1;
        this.startPole = 0;
        this.middlePole = 1;
        this.destPole = 2;

        // instantiate list of linked lists and add to array

        p0 = new LinkedList<Integer>();
        poles[startPole] = p0;
        p1 = new LinkedList<Integer>();
        poles[middlePole] = p1;
        p2 = new LinkedList<Integer>();
        poles[destPole] = p2;



        // fill starting pole
        int d = 1;
        while (d <= ndisks){
            p0.push(d);
            d++;
        }
    }

    /**
     * Constructor validates and assigns arguments, fills linked list
     * @param ndisks
     * @param src
     * @param dest
     */
    public Hanoi(int ndisks, int src, int dest) {

        // validate arguments and assign
        if (ndisks > 0) {
            this.ndisks = ndisks;
        } else {
            System.err.println("disk number must be greater than 0, setting to 1 disk");
            this.ndisks = 1;
        }
        if (src >= 0 && src < 3 && src != dest) {
            this.startPole = src;
        } else {
            System.err.println("starting pole must be between 0-2 and cannot equal destination, setting to 0 ");
            this.startPole = 0;
        }
        if (dest >= 0 && dest < 3 && src != dest) {
            this.destPole = dest;
        } else {
            System.err.println("destination pole must be between 0-2 and cannot equal starting, setting to 2 ");
            this.destPole = 2;
        }

        // assign the last pole number
        for (int i = 0; i < 3; i++) {
            if (this.startPole == i) {
                continue;
            } else if (this.destPole == i) {
                continue;
            } else {
                this.middlePole = i;
            }
        }

        // instantiate list of linked lists and add to array

        this.p0 = new LinkedList<Integer>();
        this.poles[startPole] = p0;
        this.p1 = new LinkedList<Integer>();
        this.poles[middlePole] = p1;
        this.p2 = new LinkedList<Integer>();
        this.poles[destPole] = p2;



        // fill starting pole
        int d = 1;
        while (d <= this.ndisks) {
            p0.push(d);
            d++;
        }

    }

    /**
     * This method will simulate all of the moves to solve the tower of hanoi puzzle
     */
    public void play(){
        // Assign new pointers to keep correct order
//        LinkedList<Integer> a = (LinkedList<Integer>)poles[startPole];
//        LinkedList<Integer> b = (LinkedList<Integer>)poles[middlePole];
//        LinkedList<Integer> c = (LinkedList<Integer>)poles[destPole];

        int a = startPole;
        int b = middlePole;
        int c = destPole;


        if (ndisks % 2 == 0){
            // repeat movement pattern until finished
            boolean finished = false;
            while (!finished){
                moveDisk(poles, a, b );
                if (p2.size() == ndisks){
                    finished = true;
                    continue;
                }
                moveDisk(poles, a, c);
                if (p2.size() == ndisks){
                    finished = true;
                    continue;
                }
                moveDisk(poles, b, c);
                if (p2.size() == ndisks){
                    finished = true;
                }
            }

        }

        else {
            // stop variable
            boolean finished = false;
            // do initial move
            moveDisk(poles, a, c);
            // repeat these steps until done
            while (!finished){
                moveDisk(poles, a, b );
                if (p2.size() == ndisks){
                    finished = true;
                    continue;
                }
                moveDisk(poles, b, c);
                if (p2.size() == ndisks){
                    finished = true;
                    continue;
                }
                moveDisk(poles, a, c);
                if (p2.size() == ndisks){
                    finished = true;
                }
            }
        }

        // Print final pole and move count
        System.out.println("Finished. Pole " + destPole + " is:");
        for (Integer e : p2){
            System.out.println(e);
        }
        System.out.println("Number of Moves: " + moveCount);


    }

    /**
     * This is a supporting function that determines the move direction by comparing the top disks on the stacks.
     * NOTE: the Object array in the arguments is just a formality as the assignment asked for it. The instance of
     * the Hanoi object already has access to the pole array as it is a class variable.
     * @param poles
     * @param src
     * @param dest
     */
    public void moveDisk(Object[] poles, int src, int dest){
        LinkedList<Integer> temp = (LinkedList<Integer>)poles[src];
        LinkedList<Integer> temp2 = (LinkedList<Integer>)poles[dest];

        // empty check
        if (temp.isEmpty() && temp2.isEmpty()){
            return;
        }
        // if one is empty move to that one
        if(temp.peek() == null){
            int diskNum = temp2.peek();
            temp.push(temp2.pop());
            System.out.println("Moved disk " + diskNum + " from pole " + dest + " to pole " + src);
        }
        else if (temp2.peek() == null){
            int diskNum = temp.peek();
            temp2.push(temp.pop());
            System.out.println("Moved disk " + diskNum + " from pole " + src + " to pole " + dest);
        }
        // else compare values and move higher value
        else if (temp.peek() < temp2.peek()){
            int diskNum = temp2.peek();
            temp.push(temp2.pop());
            System.out.println("Moved disk " + diskNum + " from pole " + dest + " to pole " + src);
        }
        else if (temp2.peek() < temp.peek()){
            int diskNum = temp2.peek();
            temp2.push(temp.pop());
            System.out.println("Moved disk " + diskNum + " from pole " + src + " to pole " + dest);
        }
        moveCount++;

    }

    /** This method returns the Object[] poles
     *
     * @return
     */
    public Object[] getPoles() {
        return poles;
    }

    /**
     * Sets the Object[] poles
     * @param poles
     */
    public void setPoles(Object[] poles) {
        this.poles = poles;
    }

    /**
     * Returns ndisks
     * @return
     */
    public int getNdisks() {
        return ndisks;
    }

    /**
     * Sets ndisks
     * @param ndisks
     */
    public void setNdisks(int ndisks) {
        this.ndisks = ndisks;
    }

    /**
     * Returns the moveCount
     * @return
     */
    public int getMoveCount() {
        return moveCount;
    }

    /**
     * Sets the moveCount
     * @param moveCount
     */
    public void setMoveCount(int moveCount) {
        this.moveCount = moveCount;
    }

    /**
     * Returns the startPole
     * @return
     */
    public int getStartPole() {
        return startPole;
    }

    /**
     * Sets the start pole
     * @param startPole
     */
    public void setStartPole(int startPole) {
        this.startPole = startPole;
    }

    /**
     * Returns the destPole
     * @return
     */
    public int getDestPole() {
        return destPole;
    }

    /**
     * Sets the destPole
     * @param destPole
     */
    public void setDestPole(int destPole) {
        this.destPole = destPole;
    }

    /**
     * Returns the middle pole
     * @return
     */
    public int getMiddlePole() {
        return middlePole;
    }

    /**
     * Sets the middle pole
     * @param middlePole
     */
    public void setMiddlePole(int middlePole) {
        this.middlePole = middlePole;
    }

    /**
     * Returns a string representation of the Hanoi object
     * @return
     */
    @Override
    public String toString() {
        return "Hanoi{" +
                "poles=" + Arrays.toString(poles) +
                ", ndisks=" + ndisks +
                ", moveCount=" + moveCount +
                ", startPole=" + startPole +
                ", destPole=" + destPole +
                ", middlePole=" + middlePole +
                ", p0=" + p0 +
                ", p1=" + p1 +
                ", p2=" + p2 +
                '}';
    }

    public static void main(String[] args) {

        // standard 3 disk game
        Hanoi test = new Hanoi(3, 0, 2);
        test.play();
        System.out.println("***** End of Test ******");

        // standard 6 disk game
        Hanoi test1 = new Hanoi(6, 0, 2);
        test1.play();
        System.out.println("***** Test 1 ******");
//
//        // standard 12 disk game (test by itself, lots of print out)
//        //Hanoi test2 = new Hanoi(12, 0, 2);
//        //test2.play();
//        //System.out.println("***** End of Test 2 ******");
//
        // different pole 6 disk game
        Hanoi test3 = new Hanoi(6, 2, 0);
        test3.play();
        System.out.println("***** End of Test 3 ******");

        // different starting and destination poles
        Hanoi test4 = new Hanoi(6, 2, 1);
        test4.play();
        System.out.println("***** End of Test 4 ******");

        // test default constructor
        Hanoi test5 = new Hanoi();
        test5.play();
        System.out.println("*****  End of Test 5 ******");

        // NOTE: since printing to standard error sometimes all error messages get printed at once instead of where they
        // should be in standard out
        // test same src and destination pole
        Hanoi test6 = new Hanoi(4, 1, 1);
        test6.play();
        System.out.println("*****  End of Test 6 ******");

        // test negative check
        Hanoi test7 = new Hanoi(-1, -1, -2);
        test7.play();
        System.out.println("*****  End of Test 7 ******");


    }
}
