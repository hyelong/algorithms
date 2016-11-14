package FB;

import java.util.*;

/*
 * 4种thread：1，2，3，4, 冷却时间: 3，在multithreading的时候同类型的thread要等上一个thread跑完冷却时间之后才能运行，
 * 求最后scheduler用了多少time slot。
 * 举个例子，thread: 1, 2, 1, 1, 3, 4; 冷却时间: 2 time slot，scheduler应该是这样的：1, 2, _, 1, _, _,1, 3, 4，最后返回9. 
 */
public class ThreadCoolDown {
	public static void test(){
		int[] threads = {1,1,2,1};
		int coolDownTime = 3;
		int total = 0;
		Map<Integer, Integer> map = new HashMap<>();
		for(int i=0;i<threads.length;i++){
			if(!map.containsKey(threads[i])){
				map.put(threads[i], total);
				total++;
			}
			else{
				while(total-map.get(threads[i])<coolDownTime) total++;
				map.put(threads[i], total);   //update the position
				total++;
			}
		}
		System.out.println(total);
	}
	
	public static void test1(){
		class task{
			int id;
			int count;
			task(int id, int count){
				this.id = id;
				this.count = count;
			}
		}
		int[] threads = {1,2,3,1,2,3,2};
		int cooldown = 3;
		Queue<task> q = new PriorityQueue<>(new Comparator<task>(){
			public int compare(task t1, task t2){
				return t2.count-t1.count;
			}
		});
		Map<Integer, Integer> map = new HashMap<>();
		for(int i : threads){
			if(!map.containsKey(i)) map.put(i, 0);
			map.put(i, map.get(i)+1);
		}
		for(int key:map.keySet()){
			task t = new task(key, map.get(key));
			q.add(t);
		}
		
		task[] tasks = new task[q.size()];
		int index = 0;
		while(!q.isEmpty()){
			tasks[index++] = q.poll();
		}
		System.out.println(tasks[1].id);
		StringBuilder sb = new StringBuilder();
		int total = 0;
		boolean finished = false;
		while(!finished){
			finished = true;
			int cadidate = -1;
			for(int i=0;i<tasks.length;i++){
				if(tasks[i].count==0) continue;
				finished = false;
				int id = -1;
				for(int j = total-1;j>=total-cooldown;j--){
					if(j<0) continue;
					if(sb.charAt(j)-'0'==tasks[i].id){
						id = tasks[i].id;
						break;
					}
				}
				if(id==-1){
					cadidate = tasks[i].id;
					tasks[i].count--;
					break;
				}
			}
			if(finished) break;
			if(cadidate==-1) sb.append('_');
			else sb.append(cadidate);
			total++;
		}
		
		System.out.println(sb.toString());
	}
}
