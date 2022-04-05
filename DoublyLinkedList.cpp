#include "DoublyLinkedList.h"
#include <cstddef>
#include <iostream>

using namespace std;

template <class T>
DoublyLinkedList<T>::DoublyLinkedList() {
    head = NULL;
} // constructor

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    NodeType<T> *temp;
    while (head != NULL) { // iterating through and deleting nodes
        temp = head;
        head = head->next;
        delete temp;
    } // end while
} // destructor

template <class T>
void DoublyLinkedList<T>::insertItem(T &item) {

    NodeType<T> *current = head;
    NodeType<T> *newNode = new NodeType<T>;
    newNode->data = item;

    if (head == NULL) { // empty list
        head = newNode;
        return;
    } else if (head->data >= newNode->data) { // start of list
        newNode->next = head; // putting newNode behind head
        (newNode->next)->back = newNode; // linking node in front of newNode
        head = newNode; // moving head to newNode
        return;
    } else {

        while ((current->next != NULL) && ((current->next)->data < item)) { // iterating
            current = current->next;
        } // end while

        newNode->next = current->next; // linking

        if (current->next != NULL) { // insert at end of list
            (newNode->next)->back = newNode;
        } // end if

        // "general case"
        current->next = newNode;
        newNode->back = current;

    } // end if
} // insertItem

template <class T>
void DoublyLinkedList<T>::deleteItem(T &item) {

    NodeType<T> *current = head;
    NodeType<T> *temp;

    if (head == NULL) { // empty list
        cout << "You cannot delete from an empty list" << endl;
        return;
    } else if (head->next == NULL) { // only element
        head = NULL;
        return;
    } // end if

    if (item == current->data) { // first element
        (head->next)->back = NULL;
        head = (head->next);
    } else {
        while ((current->next != NULL) && item != (current->next)->data) {
            current = current->next;
        } // end while
        if (current->next == NULL) {
            cout << "Item not in list!" << endl;
            return;
        } // end if

        temp = current->next;
        current->next = temp->next;
        if (temp->next != NULL) { // if deleting last element
            (temp->next)->back = current;
        } // end if
        delete temp;

    } // end if

} // deleteItem

template <class T>
int DoublyLinkedList<T>::lengthIs() const {
    NodeType<T> *temp = head;
    int length = 0;
    while(temp != NULL) {
        temp = temp->next;
        length++;
    } // end while
    return length;
} // lengthIs

template <class T>
void DoublyLinkedList<T>::print() {
    NodeType<T> *temp = head;
    while(temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    } // end while
    cout << endl;
} // print

template <class T>
void DoublyLinkedList<T>::printReverse() {
    NodeType<T> *current = head;
    while (current->next != NULL) {
        current = current->next;
    } // end while

    while(current != NULL) {
        cout << current->data << " ";
        current = current->back;
    } // end while
    cout << endl;
} // printReverse

template <class T>
void DoublyLinkedList<T>::deleteSubsection(T start, T end) {
    NodeType<T> *current = head;
    while (current != NULL) {
        T curr = current->data;
        if ((curr <= end) && (curr >= start)) { // if within bounds
            this->deleteItem(current->data);
        } // end if
        current = current->next;
    } // end while

} // deleteSubsection

template <class T>
T DoublyLinkedList<T>::mode() {
    NodeType<T> *current = head;
    NodeType<T> *temp;
    NodeType<T> *target = head;
    int mode = 0;

    while (current != NULL) { // iterating through list
        temp = current;
        int counter = 0;
        while (temp != NULL) {
            if (temp->data == current->data) {
                counter++;
            } // end if
            temp = temp->next;
        } // end while temp
        if (counter > mode) { // higher mode found
            mode = counter;
            target = current;
        } // end if
        current = current->next;
    } // end while current

    return target->data;

} // mode

template <class T>
void DoublyLinkedList<T>::swapAlternate() {

    NodeType<T> *current = head->next;
    NodeType<T> *predLoc;

    while (current != NULL) {
        predLoc = current->back;
        predLoc->next = current->next;
        current->back = predLoc->back;

        (current->next)->back = predLoc;

        if (predLoc != head) {
            (predLoc->back)->next = current; // problematic if predLoc = head
        } else {
            head = current;
        } // end if

        predLoc->back = current;
        current->next = predLoc;

        current = ((current->next)->next)->next;
    } // end while

} // swapAlternate


template class DoublyLinkedList<int>;
template class DoublyLinkedList<float>;
template class DoublyLinkedList<std::string>;
