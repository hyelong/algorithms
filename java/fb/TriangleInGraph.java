/**
 * Given an Undirected simple graph, We need to find how many triangles it can have
 * https://www.geeksforgeeks.org/number-of-triangles-in-a-undirected-graph/
 */
import java.io.*;

public class TriangleInGraph {
    public static void main(String[] args) {
        TriangleInGraph triangle = new TriangleInGraph();

        int graph[][] = {
                            {0, 1, 1, 0},
                            {1, 0, 1, 1},
                            {1, 1, 0, 1},
                            {0, 1, 1, 0}
                        };
        System.out.println("Total number of Triangle in Graph:" + triangle.triangleInGraph(graph));
    }

    void multiply(int A[][], int B[][], int C[][]) {
        int n = A.length;
        for (int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                C[i][j] = 0;
                for (int k = 0; k < n; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    }

    int getTrace(int graph[][]) {
        int trace = 0;
        for (int i = 0; i < graph.length; i++) {
            trace += graph[i][i];
        }
        return trace;
    }

    int triangleInGraph(int graph[][]) {
        int n = graph.length;
        int[][] aux2 = new int[n][n];
        int[][] aux3 = new int[n][n];

        multiply(graph, graph, aux2);
        multiply(graph, aux2, aux3);

        int trace = getTrace(aux3);
        return trace/6;
    }
}
