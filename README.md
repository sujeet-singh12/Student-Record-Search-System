Student Record Search System Using Binary Search Tree (BST)
1. Project Overview
This is a menu-driven C++ application for storing and managing student records using a Binary Search Tree. Each record contains an enrolment ID, student name, and department/programme. The enrolment ID is used as the unique BST key.

2. Objectives
Insert student records into a BST.
Reject duplicate enrolment IDs.
Search for a student by enrolment ID.
Delete a student record (leaf, one-child, or two-child case).
Display inorder, preorder, and postorder traversals.
Display records in sorted enrolment-ID order using inorder traversal.
Compare search comparisons for balanced-looking and sorted insertion orders.
3. Technologies Used
Language: C++
Standard: C++17
Data structures: Binary Search Tree, structures, pointers
Concepts: Recursion, insertion, searching, deletion, tree traversal
4. Student Record Structure
Each student record contains:

enrolmentID: unique integer key used for BST ordering.
name: student's name.
department: programme or department.
5. BST Property
For every node:

All IDs in its left subtree are smaller than the node's ID.
All IDs in its right subtree are greater than the node's ID.
Duplicate IDs are not allowed.
6. Main Operations
Insertion
The new record is placed by comparing its enrolment ID with the current node and moving left or right. Duplicate IDs are rejected.

Searching
The ID is compared with the current node. If it is smaller, search the left subtree; if greater, search the right subtree.

Deletion
Three cases are handled:

Leaf node: delete the node directly.
One child: replace the node with its only child.
Two children: copy the inorder successor (smallest node in the right subtree) and delete the successor node.
Traversals
Inorder: Left, Root, Right. Displays records in ascending enrolment-ID order.
Preorder: Root, Left, Right.
Postorder: Left, Right, Root.
7. How to Compile and Run
Using g++:

g++ -std=c++17 main.cpp -o student_bst
./student_bst
On Windows:

g++ -std=c++17 main.cpp -o student_bst.exe
student_bst.exe
8. Menu Options
Insert student record
Search student by enrolment ID
Delete student record
Display inorder traversal
Display preorder traversal
Display postorder traversal
Load 10 sample records
Compare balanced-looking and sorted insertion orders
Exit
Choose option 7 to load 10 example records quickly. To avoid duplicate IDs, use option 7 on a fresh/empty program run.

9. Sample Test Cases
Start with a fresh program and choose option 7 to load the sample records.

Test	Operation	Expected result
1: Successful search	Search ID 40	Karan, department ME, is displayed
2: Unsuccessful search	Search ID 999	Student not found message
3: Duplicate insertion	Insert ID 50 again	Duplicate enrolment ID message
4: Delete leaf	Delete ID 10	Record deleted; inorder no longer contains 10
5: Delete one-child node	In a fresh sample tree, first delete ID 10, then delete ID 20	ID 20 is removed; the tree remains correctly ordered
6: Delete two-child node	In a fresh sample tree, delete ID 30	Record deleted; inorder remains sorted
7: Traversal	Select inorder	IDs are displayed in ascending order
For test 5, use a fresh program session and insert these four records in this order: 50, 30, 70, 20. Then delete ID 30. Node 30 has one child (20), so this checks the one-child deletion case.

10. Time and Space Complexity
Let n be the number of student records and h be the height of the BST.

Operation	Average case (balanced-looking tree)	Worst case (skewed tree)
Insertion	O(log n)	O(n)
Searching	O(log n)	O(n)
Deletion	O(log n)	O(n)
Traversal	O(n)	O(n)
The BST stores n nodes, so its space complexity is O(n). Recursive operations use O(h) call-stack space.

11. Balanced vs Skewed BST
A balanced-looking BST has a smaller height, so search, insertion, and deletion usually need fewer comparisons. If IDs are inserted in sorted order, the BST can become skewed like a linked list. In that case, operations can take O(n).

A self-balancing tree such as an AVL tree performs rotations to keep the height balanced, allowing search, insertion, and deletion in O(log n) time.

13. Conclusion
This project demonstrates how a Binary Search Tree can store student records and support insertion, searching, deletion, and sorted display. It also shows how tree height affects operation efficiency.
