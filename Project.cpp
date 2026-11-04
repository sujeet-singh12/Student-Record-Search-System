#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Student {
    int enrolmentID;
    string name;
    string department;
};

struct Node {
    Student data;
    Node* left;
    Node* right;

    Node(const Student& student) {
        data = student;
        left = right = nullptr;
    }
};

class StudentBST {
private:
    Node* root;

    Node* insertNode(Node* node, const Student& student, bool& inserted) {
        if (node == nullptr) {
            inserted = true;
            return new Node(student);
        }

        if (student.enrolmentID < node->data.enrolmentID)
            node->left = insertNode(node->left, student, inserted);
        else if (student.enrolmentID > node->data.enrolmentID)
            node->right = insertNode(node->right, student, inserted);
        else
            inserted = false; // Duplicate key is not allowed.

        return node;
    }

    Node* searchNode(Node* node, int id, int& comparisons) const {
        while (node != nullptr) {
            comparisons++;
            if (id == node->data.enrolmentID) return node;
            if (id < node->data.enrolmentID) node = node->left;
            else node = node->right;
        }
        return nullptr;
    }

    Node* minimumNode(Node* node) const {
        while (node != nullptr && node->left != nullptr)
            node = node->left;
        return node;
    }

    Node* deleteNode(Node* node, int id, bool& deleted) {
        if (node == nullptr) return nullptr;

        if (id < node->data.enrolmentID) {
            node->left = deleteNode(node->left, id, deleted);
        } else if (id > node->data.enrolmentID) {
            node->right = deleteNode(node->right, id, deleted);
        } else {
            deleted = true;

            // Case 1: Leaf node
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }

            // Case 2: Node has only right child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            // Case 2: Node has only left child
            if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: Node has two children
            Node* successor = minimumNode(node->right);
            node->data = successor->data;
            bool successorDeleted = false;
            node->right = deleteNode(node->right,
                                     successor->data.enrolmentID,
                                     successorDeleted);
        }
        return node;
    }

    void inorder(Node* node) const {
        if (node == nullptr) return;
        inorder(node->left);
        printStudent(node->data);
        inorder(node->right);
    }

    void preorder(Node* node) const {
        if (node == nullptr) return;
        printStudent(node->data);
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) const {
        if (node == nullptr) return;
        postorder(node->left);
        postorder(node->right);
        printStudent(node->data);
    }

    void destroy(Node* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    static void printStudent(const Student& s) {
        cout << "ID: " << s.enrolmentID
             << " | Name: " << s.name
             << " | Department: " << s.department << "\n";
    }

public:
    StudentBST() : root(nullptr) {}
    ~StudentBST() { destroy(root); }

    bool insert(const Student& student) {
        bool inserted = false;
        root = insertNode(root, student, inserted);
        return inserted;
    }

    void search(int id) const {
        int comparisons = 0;
        Node* result = searchNode(root, id, comparisons);
        if (result != nullptr) {
            cout << "Student found:\n";
            printStudent(result->data);
        } else {
            cout << "Student with enrolment ID " << id << " not found.\n";
        }
        cout << "Comparisons: " << comparisons << "\n";
    }

    void remove(int id) {
        bool deleted = false;
        root = deleteNode(root, id, deleted);
        if (deleted) cout << "Student record deleted successfully.\n";
        else cout << "Enrolment ID not found. No record deleted.\n";
    }

    void showInorder() const {
        if (!root) { cout << "Tree is empty.\n"; return; }
        cout << "\nInorder (sorted by enrolment ID):\n";
        inorder(root);
    }

    void showPreorder() const {
        if (!root) { cout << "Tree is empty.\n"; return; }
        cout << "\nPreorder traversal:\n";
        preorder(root);
    }

    void showPostorder() const {
        if (!root) { cout << "Tree is empty.\n"; return; }
        cout << "\nPostorder traversal:\n";
        postorder(root);
    }

    void loadSampleRecords() {
        Student samples[] = {
            {50, "Aarav", "CSE"},
            {30, "Simran", "IT"},
            {70, "Rahul", "ECE"},
            {20, "Neha", "CSE"},
            {40, "Karan", "ME"},
            {60, "Isha", "IT"},
            {80, "Manav", "ECE"},
            {10, "Priya", "CSE"},
            {35, "Arjun", "IT"},
            {65, "Riya", "CSE"}
        };

        for (const Student& s : samples) insert(s);
        cout << "10 sample student records loaded (if tree was empty).\n";
    }

    // Compares search comparisons in two different insertion orders.
    static int countSearchComparisons(const int values[], int n, int target) {
        struct TempNode {
            int key;
            TempNode* left;
            TempNode* right;
            TempNode(int k) : key(k), left(nullptr), right(nullptr) {}
        };

        TempNode* tempRoot = nullptr;
        for (int i = 0; i < n; i++) {
            TempNode** current = &tempRoot;
            while (*current != nullptr) {
                if (values[i] < (*current)->key) current = &((*current)->left);
                else current = &((*current)->right);
            }
            *current = new TempNode(values[i]);
        }

        int comparisons = 0;
        TempNode* current = tempRoot;
        while (current != nullptr) {
            comparisons++;
            if (target == current->key) break;
            if (target < current->key) current = current->left;
            else current = current->right;
        }

        // Free temporary tree
        auto freeTree = [&](auto&& self, TempNode* node) -> void {
            if (!node) return;
            self(self, node->left);
            self(self, node->right);
            delete node;
        };
        freeTree(freeTree, tempRoot);
        return comparisons;
    }

    static void compareInsertionOrders() {
        int balancedOrder[] = {50, 30, 70, 20, 40, 60, 80, 10, 35, 65};
        int sortedOrder[] = {10, 20, 30, 35, 40, 50, 60, 65, 70, 80};
        int n = 10, target = 80;

        int balancedCount = countSearchComparisons(balancedOrder, n, target);
        int sortedCount = countSearchComparisons(sortedOrder, n, target);

        cout << "\nSearch comparison for ID " << target << ":\n";
        cout << "Balanced-looking insertion order: " << balancedCount << "\n";
        cout << "Sorted insertion order: " << sortedCount << "\n";
        cout << "Fewer comparisons usually mean a faster search for this example.\n";
    }
};

int main() {
    StudentBST bst;
    int choice, id;
    Student student;

    do {
        cout << "\n===== STUDENT RECORD SEARCH SYSTEM =====\n";
        cout << "1. Insert student record\n";
        cout << "2. Search student by enrolment ID\n";
        cout << "3. Delete student record\n";
        cout << "4. Display inorder traversal\n";
        cout << "5. Display preorder traversal\n";
        cout << "6. Display postorder traversal\n";
        cout << "7. Load 10 sample records\n";
        cout << "8. Compare balanced-looking and sorted insertion orders\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter enrolment ID: ";
                cin >> student.enrolmentID;
                cin.ignore();
                cout << "Enter student name: ";
                getline(cin, student.name);
                cout << "Enter department/programme: ";
                getline(cin, student.department);

                if (bst.insert(student))
                    cout << "Student record inserted successfully.\n";
                else
                    cout << "Duplicate enrolment ID! Record not inserted.\n";
                break;

            case 2:
                cout << "Enter enrolment ID to search: ";
                cin >> id;
                bst.search(id);
                break;

            case 3:
                cout << "Enter enrolment ID to delete: ";
                cin >> id;
                bst.remove(id);
                break;

            case 4:
                bst.showInorder();
                break;

            case 5:
                bst.showPreorder();
                break;

            case 6:
                bst.showPostorder();
                break;

            case 7:
                bst.loadSampleRecords();
                break;

            case 8:
                StudentBST::compareInsertionOrders();
                break;

            case 0:
                cout << "Thank you for using Student Record Search System!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
