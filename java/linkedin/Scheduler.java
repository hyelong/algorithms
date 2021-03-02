import java.util.PriorityQueue;
import java.util.concurrent.atomic.AtomicInteger;

public class Scheduler {

    private PriorityQueue<Task> tasks;
    private final Thread taskRunnerThread;
    private volatile boolean running;
    private final AtomicInteger taskId;
    private Object lock = new Object();
    
    public Scheduler(){
        tasks = new PriorityQueue<>();
        taskRunnerThread = new Thread( new TaskRunner() );
        running = true;
        taskId = new AtomicInteger(0);
        System.out.println("Scheduler started at: " + System.currentTimeMillis());
        taskRunnerThread.start();
    }   
    
    public void schedule(Task task, long delayMs){
        long timeToRun = System.currentTimeMillis() + delayMs;
        task.setTimeToRun( timeToRun );
        task.setId( taskId.incrementAndGet() );
        synchronized( lock ){
            tasks.offer( task );
            lock.notify();
        }   
    }   
    
    public void stop() throws InterruptedException{
        synchronized( lock ){
            running = false;
            lock.notify();
        }   
        taskRunnerThread.join();
    }   
    
    private class TaskRunner implements Runnable{
        @Override
        public void run(){
            while( running ){
                synchronized( lock ){
                    try{
                        while( running && tasks.isEmpty() ){
                            lock.wait();
                        }   
                        long now = System.currentTimeMillis();
                        Task t = tasks.peek();
                        if (t != null) {
                            if( t.getTimeToRun() <= now ){
                                tasks.poll();
                                t.run();
                            } else {
                                lock.wait( t.getTimeToRun() - now );
                            }
                        } else {
                        }
                    } catch( InterruptedException e){
                        Thread.currentThread().interrupt();
                    }
                }
            }
        }
    }
    
    
    public static void main(String[] args) throws InterruptedException{
        Scheduler scheduler = new Scheduler();
        scheduler.schedule(new Task(), 3000);
        scheduler.schedule(new Task(), 5000);
        Thread.sleep(7000);
        scheduler.stop();
    } 
}      