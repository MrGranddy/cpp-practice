template<typename T>
Node<T>::Node(T value){
    this->value = value;
    this->next = nullptr;
}

template<typename T>
LinkedList<T>::LinkedList(){
    this->root = nullptr;
}

template<typename T>
void LinkedList<T>::insert(T value){
    Node<T> *newNode = new Node<T>(value);
    if(root){
        Node<T> *trav = root;
        while(trav->next)
            trav = trav->next;
        trav->next = newNode;
    }
    else{
        root = newNode;
    }
}

template<typename T>
void LinkedList<T>::remove(T value){
    Node<T> *trav = root;
    Node<T> *tail = nullptr;

    while(trav && trav->value != value){
        tail = trav;
        trav = trav->next;
    }

    if(trav){

        if(trav == root){ // Delete root
            Node<T> *newRoot = root->next;
            delete root;
            root = newRoot;
        }
        else if(!trav->next){ // Delete end node
            delete trav;
            tail->next = nullptr;
        }
        else{
            tail->next = trav->next;
            delete trav;
        }

    }

}

template<typename T>
void LinkedList<T>::display(){
    Node<T> *trav = root;
    while(trav && trav->next){
        std::cout << trav->value << " ";
        trav = trav->next;
    }
    if(trav){
        std::cout << trav->value;
    }
    std::cout << std::endl;
}

template<typename T>
LinkedList<T>::~LinkedList(){
    Node<T> *trav = root;
    Node<T> *temp;

    while(trav){
        temp = trav;
        trav = trav->next;
        delete temp;
    }
}