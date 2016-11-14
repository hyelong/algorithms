import java.util.*;

public class rate_limiter{
    public static void main(String[] args){
        for(int i=0;i<100;i++){
            if(new Random().nextInt(10)%10==0){
                try{
                    System.out.print("sleeping...  ");
                    Thread.sleep(500);
                }
                catch(Exception e){}
            }
            System.out.println(acquire());
        }
    }
    
    static int pos = 0;
    static long[] requestList = new long[10];
    static boolean acquire(){
        long cur = new Date().getTime();
        System.out.print("time:" + cur+"     ");
        if(cur - requestList[pos]>1000){
            requestList[pos] = cur;
            pos =  (pos+1)%10;
            return true;
        }
        else return false;
    }
}
