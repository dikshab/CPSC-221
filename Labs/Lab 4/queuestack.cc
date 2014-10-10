#include <assert.h>
#include <iostream>

class QueueStack {
  public:
  
  void enqueue(int data) {
    Node *new_back = new Node(data);
    new_back->prev_ = back_;
    if (back_ != nullptr)
      back_->next_ = new_back;
    else
      front_ = new_back; // The first node added is the front AND back
      back_ = new_back;
    }
    
  void print() {
    Node *temp = front_;
    std::cout << "{ ";
    while (temp != NULL) {
      std::cout << temp->data_ << " "; 
      temp = temp->next_;
    }
    std::cout << "}" << std::endl;
  }  
    
  int dequeue() {
    assert(front_ != nullptr);
    int result = front_->data_;
    Node *temp = front_;
    front_ = front_->next_;
    if (front_ != nullptr)
      front_->prev_ = nullptr;
    else
      back_ = nullptr; // Deleted the one node left; so, no back_
    delete temp;
    return result;
  }
  
  int dequeue_back() {
    assert(back_ != nullptr);
    int result = back_->data_;
    Node *temp = back_;
    back_ = back_->prev_;
    if (back_ != nullptr)
      back_->next_ = nullptr;
    else
      front_ = nullptr;
    delete temp;
    return result;
  }

  // TODO
  // parameters: number of data elements to return
  // returns array containing (num) data elements from the front of the QueueStack
  int* dequeue_mult(int num) {
    int *elt = new int[num];
    for (int i = 0; i < num; i++) {
      elt[i] = dequeue();
    }
    return elt;
  }
  
  // TODO
  // parameters: number of data elements to return
  // returns array containing (num) data elements from the back of the QueueStack
  int* dequeue_mult_back(int num) {
    int *elt = new int[num];
    for (int i = 0; i < num; i++) {
      elt[i] = dequeue_back();
    }
    return elt;
  }
  
  private:
  
  struct Node {
    Node(int data) : data_(data) { }
    int data_;
    Node *prev_ = nullptr;
    Node *next_ = nullptr;
  };
  Node *front_ = nullptr;
  Node *back_ = nullptr;
};

void test() {
  QueueStack qs;
  qs.enqueue(1);
    qs.enqueue(2);
      qs.enqueue(3);
        qs.enqueue(4);
          qs.enqueue(5);
            qs.enqueue(6);
              qs.enqueue(7);
                qs.enqueue(8);
  qs.print();
  int * temp = qs.dequeue_mult(2);
  delete temp;
  qs.print();
  temp = qs.dequeue_mult_back(2);
  delete temp;
  qs.print();
  qs.dequeue_mult(200);
}

int main() {
  // put your tests here
  test();
  return 0;
}
