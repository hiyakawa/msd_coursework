package lab01;

import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.Assert.assertEquals;

public class TestFindSmallestDiff {
    private int[] arr1, arr2, arr3, arr4, arr5;

    @BeforeClass
    public static void setUpBeforeClass() throws Exception {
        //happens once per test run.
    }

    @BeforeEach
    public void setUp() throws Exception {
        arr1 = new int[0];
        arr2 = new int[] { 3, 3, 3 };
        arr3 = new int[] { 52, 4, -8, 0, -17 };
        arr4 = new int[] { 10, 8, 6, 4, 2 };
        arr5 = new int[10000];
        for (int i = 0; i < 10000; i++) {
            arr5[i] = i;
        }
    }

    @Test
    public void emptyArray() {
        assertEquals(-1, DiffUtil.findSmallestDiff(arr1));
    }

    @Test
    public void allArrayElementsEqual() {
        assertEquals(0, DiffUtil.findSmallestDiff(arr2));
    }

    @Test
    public void smallRandomArrayElements() {
        assertEquals(4, DiffUtil.findSmallestDiff(arr3));
    }

    @Test
    public void allDiffEqual() {
        assertEquals(2, DiffUtil.findSmallestDiff(arr4));
    }

    @Test
    public void bigArray() {
        assertEquals(1, DiffUtil.findSmallestDiff(arr5));
    }

    @AfterEach
    public void tearDown() throws Exception {
        // happens right after every Test.
        arr1 = null;
        arr2 = null;
        arr3 = null;
    }

    @AfterClass
    public static void tearDownAfterClass() throws Exception {
        // happens once per class, after all test methods have been run.
    }

    private void someHelperMethodUsedInManyTests() {
    }
}