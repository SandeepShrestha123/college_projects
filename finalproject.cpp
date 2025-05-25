#include <iostream>
#include <fstream>
#include <unordered_map>
#include <iomanip> // for formatting
#include <cstdlib> // for system("cls")
using namespace std;

class FileManager {
private:
    struct fileNode {
        string fileName;
        fileNode* next;
        fileNode(string name) : fileName(name), next(nullptr) {}
    };

    fileNode* head; // Head of linked list
    unordered_map<string, fileNode*> fileHashTable; // Hash table for file names
    string recentFiles[2]; // Array to store last 2 searched files (changed from 5 to 2)
    int top; // Pointer to track the number of recent files

    const string filename = "filesname.txt"; // File to store file names

public:
    FileManager() : head(nullptr), top(-1) {
        loadFiles(); // Load files when the program starts
    }

    ~FileManager() {
        saveFiles(); // Save files when the program ends
    }

    void addFile() {
        system("cls");
        string fileName;
        cout << "\n\n\t\tEnter the file name to create: ";
        cin >> fileName;

        ofstream file(fileName);
        if (!file) {
            cout << "\n\t\tError creating file!\n";
            return;
        }

        cout << "\t\tEnter content for " << fileName << ": ";
        string content;
        cin.ignore();
        getline(cin, content);
        file << content;
        file.close();

        fileNode* newNode = new fileNode(fileName);
        newNode->next = head;
        head = newNode;

        // Add the file to the hash table
        fileHashTable[fileName] = newNode;

        cout << "\n\t\tFile (" << fileName << ") created and linked successfully!\n";
    }

    void displayFiles() {
        system("cls");
        if (!head) {
            cout << "\n\t\tNo files found!\n";
            return;
        }

        cout << "\n\t\tLinked Files (From Latest to Oldest):\n";
        cout << "\t\t+-----------------------+\n";
        cout << "\t\t|      File Name        |\n";
        cout << "\t\t+-----------------------+\n";

        fileNode* temp = head;
        while (temp) {
            cout << "\t\t| " << setw(20) << left << temp->fileName << " |\n";
            temp = temp->next;
        }
        cout << "\t\t+-----------------------+\n";
    }

    void searchFile() {
        system("cls");
        string fileName;
        cout << "\n\n\t\tEnter file name to search: ";
        cin >> fileName;

        // Check if the file exists using the hash table
        if (fileHashTable.find(fileName) != fileHashTable.end()) {
            ifstream file(fileName);
            if (!file) {
                cout << "\n\t\tError opening file!\n";
                return;
            }

            cout << "\n\t\tContents of " << fileName << ":\n";
            cout << "\t\t-----------------------------\n";
            string line;
            while (getline(file, line)) {
                cout << "\t\t" << line << endl;
            }
            cout << "\t\t-----------------------------\n";
            file.close();

            // Add the searched file to the recent files array
            pushRecentFile(fileName);
        } else {
            cout << "\n\t\tFile not found!\n";
        }
    }

    void loadFiles() {
        ifstream inFile(filename);
        if (!inFile) {
            cout << "\n\t\tNo existing file list found. Starting fresh.\n";
            return;
        }

        string fileName;
        while (getline(inFile, fileName)) {
            fileNode* newNode = new fileNode(fileName);
            newNode->next = head;
            head = newNode;

            // Add the file to the hash table
            fileHashTable[fileName] = newNode;
        }

        inFile.close();
        cout << "\n\t\tFile list loaded successfully!\n";
    }

    void saveFiles() {
        ofstream outFile(filename);
        if (!outFile) {
            cout << "\n\t\tError saving file list!\n";
            return;
        }
        fileNode* temp = head;
        while (temp) {
            outFile << temp->fileName << endl;
            temp = temp->next;
        }
        outFile.close();
        cout << "\n\t\tFile list saved successfully!\n";
    }

    // Function to push a recently accessed file to the array (modified for 2 files)
    void pushRecentFile(string fileName) {
        if (top < 1) {  // Changed from 4 to 1 (0-based index for array size 2)
            top++;
        } else {
            // Shift elements (only need to shift one position now)
            recentFiles[0] = recentFiles[1];
        }
        recentFiles[top] = fileName;
    }

    // Function to display recently accessed files (updated message)
    void displayRecentFiles() {
        system("cls");
        if (top == -1) {
            cout << "\n\t\tNo recently accessed files!\n";
            return;
        }

        cout << "\n\t\tRecently Accessed Files (Last 2):\n";  // Changed from 5 to 2
        cout << "\t\t+-----------------------+\n";
        cout << "\t\t|      File Name        |\n";
        cout << "\t\t+-----------------------+\n";
        for (int i = top; i >= 0; i--) {
            cout << "\t\t| " << setw(20) << left << recentFiles[i] << " |\n";
        }
        cout << "\t\t+-----------------------+\n";
    }
};

int main() {
    FileManager fm;
    int choice;
    do {
        //system("cls");
        cout << "\n\n\t\t===== File Management System =====\n";
        cout << "\t\t1. Add File\n";
        cout << "\t\t2. Display All Files\n";
        cout << "\t\t3. Search and Display File\n";
        cout << "\t\t4. Display Recently Accessed Files\n";
        cout << "\t\t5. Exit\n";
        cout << "\t\t----------------------------------\n";
        cout << "\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: fm.addFile(); break;
            case 2: fm.displayFiles(); break;
            case 3: fm.searchFile(); break;
            case 4: fm.displayRecentFiles(); break;
            case 5: cout << "\n\t\tExiting program...\n"; break;
            default: cout << "\n\t\tInvalid choice! Try again.\n";
        }

        cout << "\n\t\tPress Enter to continue...";
        cin.ignore();
        cin.get();

    } while (choice != 5);

    return 0;
}