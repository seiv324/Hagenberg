package at.fhooe.swe4;

import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.Random;

public class Heap<T extends Comparable<T>> implements PQueue<T> {
    private List<T> values;

    public Heap(){
        values = new ArrayList<>();
    }

    private boolean less(T a, T b){
        return a.compareTo(b) < 0;
    }

    public T peek() {
        return values.isEmpty() ? null : values.get(0);
    }

    public boolean isEmpty() {
        return values.isEmpty();
    }

    public void enqueue(T x){
        assert isHeap();
        values.add(x);
        upHeap();
        assert isHeap();
    }

    public T dequeue() throws NoSuchElementException{
        assert isHeap();
        if(values.isEmpty())
            throw new NoSuchElementException("cannot dequeue from empty queue");

        T top = values.get(0);
        int last = values.size()-1;
        values.set(0,values.get(last));
        values.remove(last);
        if(!values.isEmpty())
            downHeap();
        assert isHeap();
        return top;
    }

    private static int parent(int i){
        return (i-1)/2; // (i+1)/2 -1
    }

    private static int left(int i) { return i * 2 +1;} //(i+1)*2-1
    private static int right(int i) {return i*2+2;} // (i+1)*2+1-1

    private void upHeap(){
        int i = values.size()-1;
        T x = values.get(i);
        while(i != 0 && less(values.get(parent(i)), x)){
            values.set(i, values.get(parent(i))); // values[i] = values[parent(i)]
            i = parent(i);
        }
        values.set(i, x);
    }

    private int largerChild(int i){
        int indexOfLargerChild = left(i);
        if(right(i)< values.size() && less(values.get(indexOfLargerChild), values.get(right(i)))){
            indexOfLargerChild = right(i);
        }
        return indexOfLargerChild;
    }

    private void downHeap(){
        assert !values.isEmpty();
        int i = 0;
        T x = values.get(0);
        while(left(i) < values.size()){
            int indexOfLagerChild = largerChild(i);
            if(!less(x, values.get(indexOfLagerChild))){
                break;
            }
            values.set(i, values.get(indexOfLagerChild));
            i = indexOfLagerChild;
        }
        values.set(i, x);
    }

    private boolean isHeap(){
        int i = 1;
        while(i < values.size() && !less(values.get(parent(i)),values.get(i) )){
            i++;
        }
        return i >= values.size();
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("heap = [");
        for(int i = 0; i < values.size(); i++){
            sb.append(values.get(i));
        }
        sb.append(("]"));
        return sb.toString();
    }

    public static void main(String[] args){
        Heap<Integer> h = new Heap<>();
        Random r = new Random();
        for(int i = 0; i<10; i++){
            h.enqueue(r.nextInt(100));
        }
        while(!h.isEmpty()){
            System.out.println(h.dequeue());
        }
    }
}
