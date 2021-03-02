public class Task implements Comparable<Task>{
    private long timeToRun;
    private int id; 
    
    public void setId(int id){
        this.id = id; 
    }   
    
    public void setTimeToRun(long timeToRun){
        this.timeToRun = timeToRun;
    }   
    
    public void run(){
        System.out.println("Running task: " + id + " at: " + System.currentTimeMillis());
    }   
    
    public int compareTo(Task other){
        return (int) ( timeToRun -  other.getTimeToRun() );
    }   
    
    public long getTimeToRun(){
        return timeToRun;
    }   
}