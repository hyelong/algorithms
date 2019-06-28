public class QueueWithArray {
    public static void main(String[] args) {
        QueueWithFixedArray queue = new QueueWithFixedArray();
        for(int i = 1; i <= 11; i++) {
            queue.add(i);
        }
        //System.out.println(queue.size());
        System.out.println(queue.peek());
        System.out.println(queue.peek());
        queue.pop();
        System.out.println(queue.peek());
        queue.pop();
        queue.pop();
        queue.pop();
        queue.pop();
        queue.pop();
        System.out.println(queue.peek());
        queue.pop();
        queue.pop();
        queue.pop();
        queue.pop();
        System.out.println(queue.peek());
    }
}

class QueueWithFixedArray {
    private static final int BUFFER_SIZE = 5;
    int count = 0;
    Node head, tail;
    int head_i = 0, tail_i = 0;
    public QueueWithFixedArray() {
        head = new Node();
        tail = head;
    }

    public void add(int num) {
        if (tail_i < BUFFER_SIZE) {
            tail.buffer[tail_i] = num;
            // System.out.println(tail_i + ":" + num);
            tail_i++;
            count++;
        } else {
            tail_i = 0;
            tail.next = new Node();
            tail = tail.next;
            add(num);
        }
    }

    public void pop() {
        System.out.println("method pop, count:" + count);
        if (count > 0) {
            if (head_i < BUFFER_SIZE) {
                head_i++;
                if (head_i == BUFFER_SIZE) {
                    head_i = 0;
                    head = head.next;
                }
                count--;
                return;
            }
        }
        throw new IllegalStateException("Queue is empty!!");
    }

    public int peek() {
        if (count > 0) {
            return head.buffer[head_i];
        }
        throw new IllegalStateException("Queue is empty!");
    }

    public int size() {
        return count;
    }
}

class Node {
    int[] buffer = new int[5];
    Node next;
}