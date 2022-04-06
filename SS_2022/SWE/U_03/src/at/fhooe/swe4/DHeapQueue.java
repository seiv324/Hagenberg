package at.fhooe.swe4;
import at.fhooe.swe4.PQueue;

import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;

public class DHeapQueue<T extends Comparable<T>> implements PQueue<T> {
    private List<T> values;
    private int numChild;

    public DHeapQueue(){
        values = new ArrayList<>();
        numChild = 2;
    }

    public DHeapQueue(int num){
        values = new ArrayList<>();
        numChild = num;
    }

    private boolean less(T a, T b){
        return a.compareTo(b) < 0;
    }

    private int parent(int i){
        return (i-1)/numChild; // (i+1)/2 -1
    }

    private boolean isHeap(){
        int i = 1;
        while(i < values.size() && !less(values.get(parent(i)),values.get(i) )){
            i++;
        }
        return i >= values.size();
    }

    private int nChildInd(int i, int k){
        return numChild * i + k;
    }

    private int minChildInd(int i){
        int childPos = nChildInd(i, 1);
        int k = 2;
        int pos = nChildInd(i, k);
        while((k <= numChild) && (pos < values.size())){
            if(less(values.get(pos), values.get(childPos))){
                childPos = pos;
            }
            pos = nChildInd(i, k++);
        }
        return childPos;
    }

    private void upHeap(){
        int curPos = values.size() -1;
        T tmp = values.get(curPos);
        while(curPos != 0 && less(values.get(parent(curPos)), tmp)){
            values.set(curPos, values.get(parent(curPos)));
            curPos = parent(curPos);
        }
        values.set(curPos, tmp);
    }

    private void downHeap(){
        T child;
        T tmp = values.get(0);
        int minPos;
        int curPos = 0;
        while(nChildInd(curPos, 1) < values.size()){
            minPos = minChildInd(curPos);
            if(less(values.get(minPos), tmp)){
                values.set(curPos, values.get(minPos));
            }
            else
            {
                break;
            }
            curPos = minPos;
        }
        values.set(curPos, tmp);
    }

    @Override
    public boolean isEmpty() {
        return values.isEmpty();
    }

    @Override
    public T peek() {
        return values.isEmpty() ? null : values.get(0);
    }

    @Override
    public void enqueue(T value) throws NoSuchElementException {
        values.add(value);
        upHeap();
    }

    @Override
    public T dequeue() {
        if(values.isEmpty()){
            throw new NoSuchElementException("cannot dequeue from empty queue");
        }
        T top = values.get(0);
        int last = values.size() -1;
        values.set(0, values.get(last));
        values.remove(last);
        if(!values.isEmpty()){
            downHeap();
        }
        return top;
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
}
