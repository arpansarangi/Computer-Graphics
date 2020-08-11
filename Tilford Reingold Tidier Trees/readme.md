Bresenham's algorithms efficiently draw circles and lines without any floating point calculations. This is done by taking a decision variable. For every point across a row or column, we check whether the curve is above or below midpoint of the candidate points and the point is plotted accordingly. The decision variable changes according to the chosen point and the next iteration continues. 

TR algorithm for tidier drawing of trees tries to satisfy four asthetics of a tree by sacrificing on the width of the tree. The basic principle is that every subtree is made independently and will look the same irrespective of its location in the tree. The left and right subtrees are made and attached to their parent. Then they are separated till the leftmost node of the right subtree and the rightmost node of the left subtree have a minimum separartion along x-axis. Some threads are maintained between appropriate nodes so that the time taken will only depend on the shorter subtree for each node. All of this is done through a postorder traversal and the nodes get their relative coordinates. They are changed to absolute coordinates by a preorder traversal.






# Trial Runs

![alt text](..\pics\1.jpg)
![alt text](..\pics\q.png)
![alt text](..\pics\2.png)
![alt text](..\pics\3.jpg)
![alt text](..\pics\4.jpg)
![alt text](..\pics\14.jpg)
![alt text](..\pics\15.jpg)
![alt text](..\pics\5.jpg)
![alt text](..\pics\6.jpg)
![alt text](..\pics\7.jpg)
![alt text](..\pics\8.jpg)
![alt text](..\pics\9.jpg)
![alt text](..\pics\10.jpg)
![alt text](..\pics\11.jpg)
![alt text](..\pics\12.jpg)
![alt text](..\pics\13.jpg)






# Issues in Coding

1. For trees with larger values of width, all nodes are not visible inside the window. This can be fixed by reducing the minsep. But in that case, the small trees look clumsy. We have tried to find an optimal value for misep which will try to satisfy both cases.
2. Circles drawn rather look like ellipses if the window is too wide.






# Time Analysis

## Bresenham Line and Circle Drawing 
They run in O(n), where n=(x2-x1) or (y2-y1), as we are plotting a point for each row or column. This can be also verified as there is only one loop running for all values of x or y (or just x in case of a circle).

##TR Algorithm
Let n be the number of nodes. The functions drawTree and visualiseTree run in O(n) as we visit each node only once. Function petrify() does a preorder traversal and hence runs in O(n). Function join2nodes() does floating point calculations for every edge and hence is O(n) though the fundamental operations will take more time. Thus the time required is completely determined by the while loop in setup() as the function is executed exactly once per node of the tree. It has been proved by Reingold and Tilford, by induction, that the number of times the body of the loop is executed is equal to the number of internal nodes of the tree. Thus setup() also runs in O(n). Thus TR Algorithm is linear.
