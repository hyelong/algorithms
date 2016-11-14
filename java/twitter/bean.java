import java.util.*;

public class bean{
    public static void main(String[] args){
        bean b = new bean();
        System.out.println(b.lastWhiteP(2,1));
    }

    double lastWhiteP(int w, int r){
        double[][] mem = new double[w+1][r+1];
        return lastWhiteP(w, r, mem);
    }

    double lastWhiteP(int w, int r, double[][] mem){
        if(mem[w][r]>0) return mem[w][r];
        if(w==0) return 0.0;
        if(r==0) return 1.0;
        mem[w][r] = w*1.0/(w+r)*lastWhiteP(w-1, r)+
        r*1.0/(w+r)*(r*1.0/(w+r)*lastWhiteP(w, r-1)+w*1.0/(w+r)*lastWhiteP(w-1, r));
        return mem[w][r];
    }
}
