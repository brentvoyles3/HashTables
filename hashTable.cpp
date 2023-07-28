#include <iostream>
#include <string>
#include <list>
#include <sstream>
using namespace std;

/*
 * In this program implementation, there is no possibility
 * of failing to add an element to the hash table. This is
 * implemented solely for exception handling precaution and practice.
 */
list <int> notAdded;

/*
 * Method to add leading zeros to input elements < 4 digits
 * in length. Returns the input string with additonal leading
 * zeros.
 */
string addZeros(string input) {
    string temp = "";
    int a = 4 - input.length();
    if (a == 1) {
        temp += "0";
        for (int i = 0; i < input.length(); i++) {
            temp += input[i];
        } // for
    } else if (a == 2) {
        temp += "00";
        for (int i = 0; i < input.length(); i++) {
            temp += input[i];
        } // for
    } else if (a == 3) {
        temp += "000";
        for (int i = 0; i < input.length(); i++) {
            temp += input[i];
        } // for
    }
    return temp;
} // addZeros

/*
 * Hash table implementation
 */
class hashTable {
    int size; // always 13 for this assignment
    list <int> * table;
public:
    //Constructor
    hashTable() {
        this->size = 13;
        this->table = new list<int>[size];
    }

    //Function to apply the hash function to a key.
    int hashFn(int temp) {
        int value = ((temp+1) % size);
                return value;
    }

    /* Inserts an item into the hash table at hash function result (index)
     * This insertion function is used solely for when separate chaining is
     * used for when collisions occur in a hash table.
     */
    void addKey(int key) {
        int idx = hashFn(key);
        table[idx].push_back(key);
    }

    //Prints the hash table to std output
    void printTable() {
        int idx = 0;
        for (int i = 0; i < size; i++) {
            cout << i << "\t ";
            //printing dash for empty symbol
            if (table[i].empty())
                cout << "-";
            //for each key in the list at the idx...
            for (int val : table[i]) {
                 stringstream stream;
                 stream << val;
                 string temp;
                 stream >> temp;
                 if (temp.length() < 4)
                 temp = addZeros(temp);
                 //if there was a collision at i
                 if (idx > 0) {
                     cout << " --> ";
                 }
                 cout << temp;
                 //using this index to apply chain "-->"
                 idx++;
            //reset chain idx
            idx = 0;
            cout << endl;
        }
        if (!notAdded.empty()) {
        while (!notAdded.empty()) {
      int elem = notAdded.front();
      notAdded.pop_front();
      cout << elem << " ";
        }
        cout << "was not able to be added to the hash table" << endl;
        }
    } // printTable

    /*
     * Calls the hash function on the key and inserts the key at the hash function
     * value (index) of the table.. Handles collisions with linear probing (open addressing).
     * Separate chaining uses the addKey method instead.
     */
    void insertKey(int key) {
        bool added = false;
        int idx = hashFn(key);
        //if the index is empty insert hash fn value
        if (table[idx].empty()) {
            table[idx].push_back(key);
            added = true;
            //else find next available index.
        } else if (idx > 0 && idx < size-1) {
            for (int j = idx+1; j < size; j++) {
                if (table[j].empty()) {
                    table[j].push_back(key);
                    added = true;
                    break;
                }
            } // for
        } if (!added) { // if couldnt add to indices between current index and end, circle to 0.
            for (int k = 0; k < size; k++) {
                if (table[k].empty()) {
                    table[k].push_back(key);
                    added = true;
                    break;
                } // if
            } // for
        } // if
        //if we couldn't add the element, add element to a list in order to display error msg.
        if (!added) {
            notAdded.push_back(key);
        }
    } // insertKey
}; // hashTable

/*
 * Separate Chaining function that creates a hash table and adds the keys
 * via separate chaining / storing a linked list at each index that encounters
 * a hash function collisions. Calls the addKey method.
 */
void sepChain(int * keys, int size) {
    hashTable ht;
    cout << "Hash Table: " << endl;
    cout<< "Index \t Key" << endl;
    for (int i = 0; i < size; i++) {
        ht.addKey(keys[i]);
    }
    ht.printTable();
} // sepChain

/*
 * Linear probing function that creates a hash table and adds the keys to hash table.
 * Applies linear probing when a collision occurs. Calls insertKey instead of addKeys
 * like the seperate chaining function.
 */
void linearProbing(int * keys, int size) {
    hashTable h;
  cout << "Hash Table: " << endl;
  cout<< "Index \t Key" << endl;
  for (int i = 0; i < size; i++) {
      h.insertKey(keys[i]);
  }
  h.printTable();
} // linearProbing

/*
 * Main function for handling user input by storing user input in
 * an array and passing the array values to call separate chaining and
 * open addressing functions.
 */
int main() {
    //prompt for input
    cout << "Enter elements(numbers) one by one, each on their own line:" << endl;
    int i = 0;
    //fixed size input stated via Code06 on elC.
    const int size = 8;
    int keys[size];
    //Handle / store user input
    while (i < size) {
        cin >> keys[i];
        i++;
    }
    cout << "Method 1: Separate Chaining, using h(x) = (x+1) mod 13" << endl;
    sepChain(keys, size);
    cout << "Method 2: Linear Probing, using h(x) = (x+1) mod 13" << endl;
    linearProbing(keys, size);
} // main

