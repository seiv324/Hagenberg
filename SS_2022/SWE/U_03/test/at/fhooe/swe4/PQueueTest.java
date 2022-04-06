package at.fhooe.swe4;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Nested;

import java.util.NoSuchElementException;

import static org.junit.jupiter.api.Assertions.*;

class PQueueTest {

    @Nested
    class HeapTest {
        private PQueue<String> uut;

        @org.junit.jupiter.api.BeforeEach
        void setUp() {
            uut = new Heap<>();
        }

        @org.junit.jupiter.api.AfterEach
        void tearDown() {
            uut = null;
        }

        @org.junit.jupiter.api.Test
        void peek() {
            for (int i = 0; i < 5; i++) {
                uut.enqueue("test" + i);
            }
            assertEquals("test4", uut.peek());
        }

        @org.junit.jupiter.api.Test
        void isEmpty() {
            uut.enqueue("test");

            assertFalse(uut.isEmpty());
            uut = new Heap<>();
            assertTrue(uut.isEmpty());
        }

        @org.junit.jupiter.api.Test
        void enqueue() {
            assertTrue(uut.isEmpty());
            uut.enqueue("test1");
            uut.enqueue("test2");
            uut.enqueue("test3");
            assertFalse(uut.isEmpty());
            assertEquals("test3", uut.peek());
            uut.dequeue();
            uut.dequeue();
            assertFalse(uut.isEmpty());
            uut.dequeue();
            assertTrue(uut.isEmpty());

            NoSuchElementException thrown = Assertions.assertThrows(NoSuchElementException.class, () -> {
                uut.dequeue();
            }, "NoSuchElementException was expected");

            Assertions.assertEquals("cannot dequeue from empty queue", thrown.getMessage());

        }

        @org.junit.jupiter.api.Test
        void dequeue() {
            assertTrue(uut.isEmpty());
            uut.enqueue("test1");
            assertFalse(uut.isEmpty());
            uut.dequeue();
            assertTrue(uut.isEmpty());
        }

        @org.junit.jupiter.api.Test
        void testToString() {
            assertEquals("heap = []", uut.toString());
            uut.enqueue("Test, ");
            uut.enqueue("FH, ");
            uut.enqueue("Hagenberg");
            assertEquals("heap = [Test, FH, Hagenberg]", uut.toString());
        }
    }

    @Nested
    class DHeapQueueTest {
        private DHeapQueue<String> uut;

        @org.junit.jupiter.api.BeforeEach
        void setUp() {
            uut = new DHeapQueue<>();
        }

        @org.junit.jupiter.api.AfterEach
        void tearDown() {
            uut = null;
        }

        @org.junit.jupiter.api.Test
        void peek() {
            for (int i = 0; i < 5; i++) {
                uut.enqueue("test" + i);
            }
            assertEquals("test4", uut.peek());
        }

        @org.junit.jupiter.api.Test
        void isEmpty() {
            uut.enqueue("test");

            assertFalse(uut.isEmpty());
            uut = new DHeapQueue<>();
            assertTrue(uut.isEmpty());
        }

        @org.junit.jupiter.api.Test
        void enqueue() {
            assertTrue(uut.isEmpty());
            uut.enqueue("test1");
            uut.enqueue("test2");
            uut.enqueue("test3");
            assertFalse(uut.isEmpty());
            assertEquals("test3", uut.peek());
            uut.dequeue();
            uut.dequeue();
            assertFalse(uut.isEmpty());
            uut.dequeue();
            assertTrue(uut.isEmpty());

            NoSuchElementException thrown = Assertions.assertThrows(NoSuchElementException.class, () -> {
                uut.dequeue();
            }, "NoSuchElementException was expected");

            Assertions.assertEquals("cannot dequeue from empty queue", thrown.getMessage());
        }

        @org.junit.jupiter.api.Test
        void dequeue() {
            assertTrue(uut.isEmpty());
            uut.enqueue("test1");
            assertFalse(uut.isEmpty());
            uut.dequeue();
            assertTrue(uut.isEmpty());
        }

        @org.junit.jupiter.api.Test
        void testToString() {
            assertEquals("heap = []", uut.toString());
            uut.enqueue("Test, ");
            uut.enqueue("FH, ");
            uut.enqueue("Hagenberg");
            assertEquals("heap = [Test, FH, Hagenberg]", uut.toString());
        }
    }

}