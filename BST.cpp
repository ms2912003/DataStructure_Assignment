#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class item {
public:
    string itemname;
    string category;
    double price;
    item(string name, string cat, double p) : itemname(name), category(cat), price(p) {}
    bool operator<(const item& other) const {
        return this->itemname < other.itemname;
    }
    void print() const {
        cout << "Item Name: " << itemname << ", Category: " << category << ", Price: $" << price << endl;
    }
};

struct node {
    item data;
    struct node *left, *right;
    node(const item& newItem) : data(newItem), left(nullptr), right(nullptr) {}
};

// Forward declaration
node *minValueNode(node *root);

// Inorder Traversal
void inorder(node *root, vector<item>& itemList) {
    if (root != nullptr) {
        // Traverse left
        inorder(root->left, itemList);

        // Traverse root
        itemList.push_back(root->data);

        // Traverse right
        inorder(root->right, itemList);
    }
}

// Insert a node
bool insert(node *&root, const item& newItem, const string& filename) {
    // Return false if the tree is empty
    if (root == nullptr) {
        root = new struct node(newItem);

        // Open file in append mode and write the new item
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << newItem.itemname << endl;
            file << newItem.category << endl;
            file << newItem.price << endl;
            file.close();
        } else {
            cerr << "Error opening file for appending." << endl;
        }

        return true;
    }

    // Convert item names to lowercase for comparison
    string newItemName = newItem.itemname;
    string currentNodeName = root->data.itemname;
    transform(newItemName.begin(), newItemName.end(), newItemName.begin(), ::tolower);
    transform(currentNodeName.begin(), currentNodeName.end(), currentNodeName.begin(), ::tolower);

    // Convert category names to lowercase for comparison
    string newItemCategory = newItem.category;
    string currentNodeCategory = root->data.category;
    transform(newItemCategory.begin(), newItemCategory.end(), newItemCategory.begin(), ::tolower);
    transform(currentNodeCategory.begin(), currentNodeCategory.end(), currentNodeCategory.begin(), ::tolower);

    // Traverse to the right place and insert the node
    if (newItemName < currentNodeName)
        return insert(root->left, newItem, filename);
    else if (newItemName > currentNodeName)
        return insert(root->right, newItem, filename);
    else {
        // If names match, check category
        if (newItemCategory < currentNodeCategory)
            return insert(root->left, newItem, filename);
        else if (newItemCategory > currentNodeCategory)
            return insert(root->right, newItem, filename);
        else {
            // If both name and category match, check price
            if (newItem.price == root->data.price) {
                // If name, category, and price are the same, it's a duplicate
                cout << "Item already exists." << endl;
                return false;
            } else {
                // Otherwise, insert the node
                if (newItem.price < root->data.price)
                    return insert(root->left, newItem, filename);
                else
                    return insert(root->right, newItem, filename);
            }
        }
    }
}

// Delete a node
node *deleteNode(node *root, const string& itemName, const string& itemCategory, double itemPrice, const string& filename) {
    // Return if the tree is empty
    if (root == nullptr) return root;

    // Convert item name to lowercase for comparison
    string lowerItemName = itemName;
    transform(lowerItemName.begin(), lowerItemName.end(), lowerItemName.begin(), ::tolower);

    // Convert category name to lowercase for comparison
    string lowerItemCategory = itemCategory;
    transform(lowerItemCategory.begin(), lowerItemCategory.end(), lowerItemCategory.begin(), ::tolower);

    // Traverse to find the node to delete
    node *parent = nullptr;
    node *current = root;
    while (current != nullptr) {
        // Convert item name to lowercase for comparison
        string currentNodeName = current->data.itemname;
        transform(currentNodeName.begin(), currentNodeName.end(), currentNodeName.begin(), ::tolower);

        // Convert category name to lowercase for comparison
        string currentNodeCategory = current->data.category;
        transform(currentNodeCategory.begin(), currentNodeCategory.end(), currentNodeCategory.begin(), ::tolower);

        // Compare name, category, and price
        if (lowerItemName == currentNodeName && lowerItemCategory == currentNodeCategory && itemPrice == current->data.price) {
            // Found the node to delete
            break;
        } else if (lowerItemName < currentNodeName || (lowerItemName == currentNodeName && lowerItemCategory < currentNodeCategory) ||
                   (lowerItemName == currentNodeName && lowerItemCategory == currentNodeCategory && itemPrice < current->data.price)) {
            // Traverse left
            parent = current;
            current = current->left;
        } else {
            // Traverse right
            parent = current;
            current = current->right;
        }
    }

    // If node is not found
    if (current == nullptr) {
        cout << "Item not found. No item deleted." << endl;
        return root;
    }

    // Delete the node
    if (current->left == nullptr) {
        // Node has no left child or only right child
        node *temp = current->right;
        delete current;
        if (parent == nullptr) {
            return temp; // If root is deleted
        } else {
            if (parent->left == current) {
                parent->left = temp;
            } else {
                parent->right = temp;
            }
        }
    } else if (current->right == nullptr) {
        // Node has only left child
        node *temp = current->left;
        delete current;
        if (parent == nullptr) {
            return temp; // If root is deleted
        } else {
            if (parent->left == current) {
                parent->left = temp;
            } else {
                parent->right = temp;
            }
        }
    } else {
        // Node has two children
        // Find inorder successor
        node *successorParent = current;
        node *successor = current->right;
        while (successor->left != nullptr) {
            successorParent = successor;
            successor = successor->left;
        }

        // Copy successor's data to current node
        current->data = successor->data;

        // Delete the successor node
        if (successorParent->left == successor) {
            successorParent->left = deleteNode(successorParent->left, successor->data.itemname, successor->data.category, successor->data.price, filename);
        } else {
            successorParent->right = deleteNode(successorParent->right, successor->data.itemname, successor->data.category, successor->data.price, filename);
        }
    }

    // After deletion, update the file
    ofstream file(filename);
    if (file.is_open()) {
        vector<item> itemList;
        inorder(root, itemList);
        file << itemList.size() << endl;
        for (const auto& i : itemList) {
            file << i.itemname << endl;
            file << i.category << endl;
            file << i.price << endl;
        }
        file.close();
    } else {
        cerr << "Error opening file for writing." << endl;
    }

    return root;
}

// Find the inorder successor
node *minValueNode(node *root) {
    if (root == nullptr)
        return nullptr;

    node *current = root;

    // Find the leftmost leaf
    while (current && current->left != nullptr)
        current = current->left;

    return current;
}

// Custom comparison function for case-insensitive sorting
bool compareByName(const item& a, const item& b) {
    // Convert both names to lowercase for comparison
    string nameA = a.itemname;
    string nameB = b.itemname;
    transform(nameA.begin(), nameA.end(), nameA.begin(), ::tolower);
    transform(nameB.begin(), nameB.end(), nameB.begin(), ::tolower);
    return nameA < nameB;
}

void displayItemsByNameAsc(node *root) {
    vector<item> itemList;
    inorder(root, itemList);

    // Sort items by name in ascending order (case-insensitive)
    sort(itemList.begin(), itemList.end(), compareByName);

    // Display sorted items
    cout << "\nDisplaying items sorted by name in ascending order:" << endl;
    for (const auto& i : itemList) {
        i.print();
    }
}


// Custom comparison function for case-insensitive sorting in descending order
bool compareByNameDesc(const item& a, const item& b) {
    // Convert both names to lowercase for comparison
    string nameA = a.itemname;
    string nameB = b.itemname;
    transform(nameA.begin(), nameA.end(), nameA.begin(), ::tolower);
    transform(nameB.begin(), nameB.end(), nameB.begin(), ::tolower);
    return nameA > nameB; // Sort in descending order
}

// Function to display items sorted by name in descending order
void displayItemsByNameDesc(node *root) {
    vector<item> itemList;
    inorder(root, itemList);

    // Sort items by name in descending order (case-insensitive)
    sort(itemList.begin(), itemList.end(), compareByNameDesc);

    // Display sorted items
    cout << "\nDisplaying items sorted by name in descending order:" << endl;
    for (const auto& i : itemList) {
        i.print();
    }
}


// Function to display items sorted by price in ascending order
void displayItemsByPriceAsc(node *root) {
    vector<item> itemList;
    inorder(root, itemList);

    // Sort items by price in ascending order
    sort(itemList.begin(), itemList.end(), [](const item& a, const item& b) {
        return a.price < b.price;
    });

    // Display sorted items
    cout << "\nDisplaying items sorted by price in ascending order:" << endl;
    for (const auto& i : itemList) {
        i.print();
    }
}

// Function to display items sorted by price in descending order
void displayItemsByPriceDesc(node *root) {
    vector<item> itemList;
    inorder(root, itemList);

    // Sort items by price in descending order
    sort(itemList.begin(), itemList.end(), [](const item& a, const item& b) {
        return a.price > b.price;
    });

    // Display sorted items
    cout << "\nDisplaying items sorted by price in descending order:" << endl;
    for (const auto& i : itemList) {
        i.print();
    }
}

int main() {
    node *root = nullptr;
    string filename = "items.txt";

    ifstream file(filename);
    if (file.is_open()) {
        int numItems;
        file >> numItems;
        file.ignore();

        for (int i = 0; i < numItems; ++i) {
            string name, category;
            double price;
            getline(file, name);
            getline(file, category);
            file >> price;
            file.ignore();
            insert(root, item(name, category, price), filename);
        }

        file.close();
    } else {
        cerr << "Error opening file: " << filename << endl;
    }

    while (true) {
        cout << "\nBinary Search Tree Menu:" << endl;
        cout << "1. Add item data" << endl;
        cout << "2. Remove item data" << endl;
        cout << "3. Display item data normally" << endl;
        cout << "4. Display all items sorted by their name (ascending)" << endl;
        cout << "5. Display all items sorted by their name (descending)" << endl;
        cout << "6. Display all items sorted by their price (ascending)" << endl;
        cout << "7. Display all items sorted by their price (descending)" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, category;
                double price;
                cout << "Enter item name: ";
                cin >> name;
                cout << "Enter item category: ";
                cin >> category;
                cout << "Enter item price: ";
                cin >> price;
                if (insert(root, item(name, category, price), filename)) {
                    cout << "Item inserted successfully." << endl;
                }
                break;
            }
            case 2: {
                string itemName, itemCategory;
                double itemPrice;
                cout << "Enter item name to remove: ";
                cin >> itemName;
                cout << "Enter item category to remove: ";
                cin >> itemCategory;
                cout << "Enter item price to remove: ";
                cin >> itemPrice;
                root = deleteNode(root, itemName, itemCategory, itemPrice, filename);
                break;
            }
            case 3: {
                vector<item> itemList;
                inorder(root, itemList);
                cout << "\nDisplaying items normally:" << endl;
                for (const auto& i : itemList) {
                    i.print();
                }
                break;
            }
            case 4:
                displayItemsByNameAsc(root);
                break;
            case 5:
                displayItemsByNameDesc(root);
                break;
            case 6:
                displayItemsByPriceAsc(root);
                break;
            case 7:
                displayItemsByPriceDesc(root);
                break;
            case 8:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
