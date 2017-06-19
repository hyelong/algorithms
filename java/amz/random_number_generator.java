/**
 * Question: Write a function to generate a random number between 1 and 9 with equal probability, 
 * given a method rand6() that generates a random number between 1 and 6.
 */

public class random_number_generator{
    // first generate blocks 0...6...12...18...24...30, pick one of the blocks
    // each block has 6 items, pick one of them
    // (rand6()-1) + 6 * (random6()-1) evenly distributed between 0-35
    int random9(){
        return ((random6()-1) + 6 * (random6()-1))%9 + 1;
    }
    int random6(){
        return (int)((Math.random()*100) % 6) + 1;
    }

    public static void main(String[] args){
        random_number_generator rand = new random_number_generator();
        int[] nums = new int[10];
        for(int i=0;i<100000;i++){
            int num = rand.random9();
            nums[num] += 1;
        }

        for(int i=1;i<10;i++) System.out.println(i + ": " + nums[i]);
    }
}
