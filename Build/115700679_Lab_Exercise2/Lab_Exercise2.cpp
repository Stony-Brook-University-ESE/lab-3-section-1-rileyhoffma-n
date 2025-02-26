using namespace std;
#include <iostream>

//node with all song info
class SongNode{
    private:
        string title;
        string author;
        int releaseYear;
        SongNode* next;     //Pointer to the next node

        //constructor
        SongNode(string a, string b, int c, SongNode* n = nullptr){
            next = n;           //each node pointer will default to null if no value is specified
            title = a;           //the data is passed into the function
            author = b;
            releaseYear = c;
        }

        friend class SongSingleLinkedList;  //the list class is a friend of the node class, so it can create new nodes if it wants
};

class SongSingleLinkedList {
    private:
        SongNode* head;        //pointer to the first node

    public: 
        //constructor
        SongSingleLinkedList(){
            //the list starts off as empty bc the head is pointing to nothing
            head = nullptr;
        }

        bool checkIfEmpty(){
            //if the head is pointing to nothing, then the list is empty
            return head == nullptr;
        }

        void addAlphabetically(string a, string b, int c){
            SongNode* new_node = new SongNode(a,b,c);       //allocate new node

            //node data is put in by the node constructor

            //if the list is empty, just point head to the new node bc there isn't really a front/back
            if(checkIfEmpty()){
                head = new_node;
            }

            //else, add after the node with higher ascii, but before the node with lower ascii
            else{
                //temporary pointers for iterating through the list
                SongNode* previousNode = nullptr;
                SongNode* currentNode = head;
                
                //case for first node (IF new title is the alphabetical first, put it in front of list to be displayed first)
                //AKA add it before the current node
                if(new_node->title < currentNode->title){
                    new_node->next = currentNode;       //point the new node to the current node
                    head = new_node;                    //The new node is now the head
                    return;                             //end the method
                }

                else{
                    //while you haven't reached the last node
                    while(currentNode->next != nullptr){
                        //advance the temporary pointers
                        previousNode = currentNode;     //previous goes to current
                        currentNode = currentNode->next;    //current goes to next

                        //if the new title is alphabetically after the previous node's title, but not after the current node's title
                        //add it before the current node
                        if(new_node->title > previousNode->title && new_node->title < currentNode->title){
                            new_node->next = currentNode;   //point the new node to current node
                            previousNode->next = new_node;  //point the previous node to the new node
                            return;                         //end the method
                        }
                    } 
                }

                //if you reach the last node and you still haven't added, add it to the end because it is the alphabetically largest (last) title
                currentNode->next = new_node;   //point old end to new node
                new_node->next = nullptr;       //new node is the new end
                return;                         //end the method
            }
        }

        //sorts by bubbling the largest values to the right so that the value at the first index is the smallest
        //This way the earliest year is first
        void sortByReleaseYear() {
            bool swapped = true;
            SongNode* currentNode;
            SongNode* previousNode;
            //before current moves to next, previous moves to current

            //while the last loop resulted in a swap
            while(swapped == true){
                swapped = false;        //reset swapped

                currentNode = head;     //start the current node at head
                previousNode = nullptr; //start previous as nothing, then set it equal to current when advancing through the list

                //while you are not on the END of the list and not on the LAST NODE
                while(currentNode != nullptr && currentNode->next != nullptr){
                    //if the current node is larger than the node after it, then swap them
                    if(currentNode->releaseYear > currentNode->next->releaseYear){
                        swapNodes(previousNode, currentNode);

                        //if the previous node is nullptr, then you made a swap at the beginning of the list
                        if(previousNode == nullptr){
                            previousNode = head;    //this means that head is right before current, so set this as previous
                        }
                        //otherwise previous will be 2 node begind current, so let it catch up
                        else{
                            previousNode = previousNode->next;
                        }
                        
                        swapped = true; //flag that there was a swap
                    }

                    //If no swap, current and previous will advance together
                    else{
                        previousNode = currentNode;
                        currentNode = previousNode->next;
                    }
                }
            }
        }

        //go from pab to pba, swaps current with next
        void swapNodes(SongNode* previous, SongNode* current){
            SongNode* next = current->next;     //The storage for next node points to the node after current

            //if current is the same as head then you are on the firsst node and have to deal with the head
            if(current == head){
                head = next;                     //point the head to the next node
                current->next = next->next;    //point the current node node after the node it was already ponting to 
                next->next = current;       //point the next node to the old current node 
            }
            else{
                previous->next = next;  //point the previous node to the node after current
                current->next = next->next;    //point current to the node after the node after it
                next->next = current;        //point the old next node to current
            }

            //when it returns, there will be a node in between previous and current (the "next" pointer) so the sorting loop should handle this
        }

        bool removeTitle(string& titleForRemoval){
            //if the list is empty, then let the user know and then return without doing anything else
            if(checkIfEmpty()){
                cout << "Cannot remove because the list is empty." << endl;
                return false;
            }

            SongNode* currentNode = head;
            SongNode* previousNode = nullptr;

            //if the node to be removed is the head
            if(head->title == titleForRemoval){
                head = head->next;      //move head to next node
                delete currentNode;     //free the memory of the old head
                return true;
            }

            else{
                //while you are not on the last node
                while(currentNode->next != nullptr){
                    //advance the temporary pointers
                    previousNode = currentNode;     //previous goes to current
                    currentNode = currentNode->next;    //current goes to next

                    if(currentNode->title == titleForRemoval){
                        previousNode->next = currentNode->next;     //point previous node to the node after current 
                        delete currentNode;     //free the memory of the deleted node
                        return true;
                    }
                }

                //if you make it out of the loop, see if the last node is the node you want deleted
                if(currentNode->title == titleForRemoval){
                    previousNode->next = nullptr;       //make the previous node the new last node
                    delete currentNode;
                    return true;
                }
                //if not, then this song is not in the list
                else{
                    cout << "Error, this song cannot be removed because it is not in the list" << endl;
                    return false;
                }
            }
        }

        void askToRemoveThree(){
            cout << "You will be asked to remove up to three songs..." << endl << endl;
            int numRemoved = 0;
            string titleToRemove;

            //while three songs haven't been removed
            while(numRemoved < 3){

                //see if there are enough songs to rmove another
                if(checkIfEmpty()){
                    cout << "Cannot remove anymore songs becuase the list is empty. Ending method..." << endl;
                    return;
                }

                //ask for the title to remove
                cout << "Enter the name of a title to be removed: ";
                cin >> titleToRemove;

                if(removeTitle(titleToRemove)){
                    numRemoved++;
                }
            }
        }

        void displayNext(){
            //start on the head, AKA the first node
            SongNode* currentNode = head;

            //while the next value is not null, AKA you are not at the end of the list
            while(currentNode != nullptr){
                //print the values on the current node
                cout << "Title: " << (*currentNode).title << " | Author: " << (*currentNode).author << " | Release Year: " << (*currentNode).releaseYear << endl;

                //move to the next node by making "current node" point to the node that "next" is pointing to
                currentNode = (*currentNode).next;
            }
        }

        void removeFromFront(){
            //if the list is empty, then let the user know and then return without doing anything else
            if(checkIfEmpty()){
                cout << "Cannot remove the front element because the list is empty." << endl;
                return;
            }

            SongNode* old = head;        //point "old" to the same node as the head (the first node)
            head = (*head).next;     //make the head point to the next node after the one it is currently pointing to (2nd node)
            delete old;             //free the memory of the node that "old" is pointing to (avoide memory leak fo unused nodes)
        }

        ~SongSingleLinkedList(){
            //while the list is not empty
            while(!checkIfEmpty()){
                removeFromFront();      //remove the front item, which frees the memory for each node
            }
        }
};



int main() {

    SongSingleLinkedList myList;        //creates and constructs an empty list
    string inputTitle, inputAuthor;
    int inputYear;

    while(1){
        //ask for the next town
        cout << "Leave the title field empty and just input commas to stop taking entries" << endl;
        cout << "Input a new list entry (title, author, release year): ";

        //read the fromatted data, read town, then ignore comma, read county then ignore comma, read population
        getline(cin, inputTitle, ',');
        //if the town field is empty, stop taking entries
        if(inputTitle == ""){
            break;
        }

        //ignore the leading space;
        cin.ignore(1);
        getline(cin, inputAuthor, ',');

        //get population and ignore the newline from entering
        cin >> inputYear;
        cin.ignore(1);

        //add it to the list
        myList.addAlphabetically(inputTitle, inputAuthor, inputYear);
    }
    cin.ignore(1);  //ignore the enter from the last entry

    //display the whole list
    cout << endl;
    cout << "--- Alphabetically Sorted List ---" << endl;
    myList.displayNext();
    cout << endl;

    myList.sortByReleaseYear();
    cout << endl << "---- Sorted By Release Year ----" << endl;
    myList.displayNext();
    

    return(0);
}