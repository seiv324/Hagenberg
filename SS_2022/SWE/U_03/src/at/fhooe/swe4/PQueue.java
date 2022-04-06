package at.fhooe.swe4;

import java.util.NoSuchElementException;

public interface PQueue<T extends Comparable> {
    boolean isEmpty();
    T peek();
    void enqueue(T value) throws NoSuchElementException;
    T dequeue();
}


