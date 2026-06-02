#ifndef HW4_QUEUE_H
#define HW4_QUEUE_H

#include <cassert>
#include <exception>

template <class T>
struct Node {
    T value;
    int index;
    struct Node *next;
    struct Node *previous;

};

template <class T>
class Queue{
private:
    Node<T> *m_head;
    Node<T> *m_tail;
    int m_size;

//    template<typename Condition>
//    friend Queue<T> filter(Queue<T>& ,Condition);
//
//    template<typename Operation>
//    friend void transform(Queue<T>& ,Operation);

public:
    Queue();
    Queue(const Queue&);
    ~Queue();

    void pushBack(T);

    class Iterator;
    Iterator begin();
    Iterator end() ;

    class ConstIterator;
    ConstIterator begin() const;
    ConstIterator end() const;


    T& front();
    const T& front() const;
    void popFront();
    void updateIndexes(int i = 1);
    int size() const;
    Node<T>* operator[](int);
    const Node<T>* operator[](int) const;
    bool operator==(const Queue<T>&);
    bool operator!=(Queue<T>);
    Queue<T>& operator=(const Queue<T>&);
    class EmptyQueue{};

};

template <class T>
class Queue<T> :: Iterator{
private:
    Node<T>* m_node;
    explicit Iterator(Node<T>* node);
    friend class Queue<T>;
public:
    T& operator*();
    Iterator& operator++();
    Iterator operator++(int);
    bool operator==(const Iterator& i);
    bool operator!=(const Queue<T>::Iterator& i);
    Iterator(const Queue<T>::Iterator  &) = default; //****
    ~Iterator() = default; //****

    class InvalidOperation{};
};


template <class T>
class Queue<T> :: ConstIterator{
private:
    Node<T>* m_node;
    explicit ConstIterator(Node<T>* node);
    friend class Queue<T>;
public:
    T& operator*() const;
    ConstIterator& operator++();
    ConstIterator operator++(int);
    bool operator==(const ConstIterator& i) const;
    bool operator!=(const Queue<T>::ConstIterator& i) const;
    ConstIterator(const Queue<T>::ConstIterator&) = default; //****
    ~ConstIterator() = default; //****

    class InvalidOperation{};
};




template <class T> Queue<T>::Queue(){
    try {
        m_head = new Node<T>;
    }catch(const std::bad_alloc& e){
        throw e;
    }
    m_head ->index = -1;
    m_head ->next = NULL;
    m_head ->previous = NULL;
    m_tail = m_head;
    m_size = 0;
}

template <class T> Queue<T>::Queue(const Queue& givenQueue){
    try {
        m_head = new Node<T>;
    }catch(const std::bad_alloc& e){
        throw e;
    }
    m_head ->index = -1;
    m_head ->next = NULL;
    m_head ->previous = NULL;
    m_tail = m_head;
    m_size = 0;

    Node<T>* temp = givenQueue.m_head;
    while(temp -> next != NULL){
        pushBack(temp -> value);
        temp = temp -> next;
    }
}

template <class T>
Queue<T> :: ~Queue(){
    while(this -> m_head != NULL){
        Node<T>* toDelete = this -> m_head;
        this -> m_head = this -> m_head -> next;
        delete toDelete;
    }
}

template <class T>
void Queue<T> :: pushBack(T value){
    Node<T> *temp;
    try {
        temp = new Node<T>;
    } catch(const std::bad_alloc& e){
        throw e;
    }
    temp -> index = m_size;
    temp -> value = value;


    if (m_size == 0){
        m_head = temp;
        m_head ->previous = NULL;
        temp -> next = m_tail;
        m_tail -> previous = temp;
        m_tail = m_head;
        m_size++;
        return;
    }

    Node<T>* temp2 = m_tail ->next;
    m_tail->next = temp;
    temp -> previous = m_tail;
    temp -> next = temp2;
    temp2 -> previous = temp;
    m_tail = temp;
    m_size++;
}

template<class T> T& Queue<T>::front() {
    if(m_head -> index == -1){
        throw EmptyQueue();
    }
    return m_head->value;
}
template<class T> const T& Queue<T>::front() const {
    if(m_head -> index == -1){
        throw EmptyQueue();
    }
    return m_head->value;
}


template<class T> void Queue<T>::popFront() {
    if(m_size == 0){
        throw EmptyQueue();
    }
    Node<T>* temp = m_head;
    m_head = m_head -> next;
    m_head ->previous = NULL;
    delete temp;

    this->updateIndexes(1);
}

template<class T> void Queue<T>::updateIndexes(int i) {

    Node<T>* temp = m_head;
    while(temp -> next != NULL){
        temp -> index -= i;
        temp = temp -> next;
    }

    m_size -= i;
}

template<class T> int Queue<T>::size() const{
    return m_size;
}



template<class T, class Condition>
Queue<T> filter(Queue<T>& queue, Condition condition) {
    Queue<T> newQueue;

    for(int i = 0 ; i < queue.size(); i++){
        if(condition(queue[i]->value)){
            newQueue.pushBack(queue[i]->value);
        }
    }
    return newQueue;
}

template<class T> Node<T>* Queue<T> :: operator[](int index)
{
    Node<T>* temp = m_head;
    for(int i = 0; i < index ; i++){
        temp = temp -> next;
    }
    return temp;
}
template<class T> const Node<T>* Queue<T> :: operator[](int index) const
{
    Node<T>* temp = m_head;
    for(int i = 0; i < index ; i++){
        temp = temp -> next;
    }
    return temp;
}

template <typename T>
bool Queue<T> :: operator==(const Queue<T>& queue){
    if(this == &queue){
        return true;
    }
    if(m_size != queue.m_size){
        return false;
    }
    Node<T>* temp1 = m_head;
    Node<T>* temp2 = queue.m_head;
    while(temp1 != NULL && temp2 != NULL){
        if(temp1 -> value != temp2 -> value || temp1 -> index != temp2 -> index){
            return false;
        }
        temp1 = temp1 -> next;
        temp2 = temp2 -> next;
    }
    if(temp1 != NULL || temp2 != NULL){
        return false;
    }

    return true;
}

template <typename T>
bool Queue<T> :: operator!=(const Queue<T> queue){
    if(this == queue){
        return false;
    }
    return true;
}

template <typename T>
Queue<T>& Queue<T> :: operator=(const Queue<T>& queue){
    if(this == &queue){
        return *this;
    }
    while(m_head-> next != NULL){
        this->popFront();
    }

    Node<T>* temp = queue.m_head;
    while(temp ->next != NULL){
        pushBack(temp -> value);
        temp = temp -> next;
    }

    return *this;
}



template<class T, typename Operation>
void transform(Queue<T>& queue, Operation operation) {

    for(int i = 0 ; i < queue.size(); i++){
        operation(queue[i] -> value);
    }
}


template<class T> Queue<T>::Iterator::Iterator(Node<T>* node) : m_node(node) {}
template<class T> Queue<T>::ConstIterator::ConstIterator(Node<T>* node) : m_node(node) {}

template<class T> T &Queue<T>::Iterator::operator*() {
    if(m_node==NULL || m_node -> index == -1){
        throw InvalidOperation();
    }
    return m_node->value;
}
template<class T> T &Queue<T>::ConstIterator::operator*() const {
    if(m_node==NULL || m_node -> index == -1){
        throw InvalidOperation();
    }
    return m_node->value;
}

template<typename T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++(){
    if(m_node -> next == NULL){
        throw InvalidOperation();
    }
    m_node = m_node -> next;
    return *this;
}

template<typename T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++(){
    if(m_node -> next == NULL){
        throw InvalidOperation();
    }
    m_node = m_node -> next;
    return *this;
}



template<typename T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(int) {
    Queue<T>::Iterator result = *this;
    ++(*this);
    return result;
}


template<typename T>
typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator++(int) {
    Queue<T>::ConstIterator result = *this;
    ++(*this);
    return result;
}



template<class T> bool Queue<T>::Iterator::operator==(const Iterator& i) {

    return (this -> m_node == i -> m_node);
}

template<typename T> bool Queue<T>::ConstIterator::operator==(const ConstIterator& i) const {

    return (this -> m_node == i -> m_node );
}

template<typename T> bool Queue<T>::Iterator::operator!=(const Queue<T>::Iterator &i)  {
    return (this -> m_node  != i .m_node);
}

template<typename T> bool Queue<T>::ConstIterator::operator!=(const Queue<T>::ConstIterator &i) const {
    return (this -> m_node != i .m_node);
}


template<typename T> typename Queue<T>::Iterator Queue<T>::begin()  {
    return Queue<T>::Iterator(m_head);
}

template<typename T> typename Queue<T>::ConstIterator Queue<T>::begin() const {
    return Queue<T>::ConstIterator(m_head);
}



template<typename T> typename Queue<T>::Iterator Queue<T>::end()  {
    if(m_tail -> index == -1){
        return Queue<T>::Iterator(m_tail);
    }
    return Queue<T>::Iterator(m_tail->next);
}

template<typename T> typename Queue<T>::ConstIterator Queue<T>::end() const {
    if(m_tail -> index == -1){
        return Queue<T>::ConstIterator(m_tail);
    }
    return Queue<T>::ConstIterator(m_tail->next);
}
#endif //HW4_QUEUE_H