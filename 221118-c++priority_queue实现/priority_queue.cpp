#include <iostream>
#include <vector>
using namespace std;

class priority_queue {
private:
    int capacity;
    int size;
    vector<int> v;
public:
    priority_queue(int capacity) {
        v.resize(capacity + 1);
        size = 0;
    }

    priority_queue(int capacity, int arr[], int arr_size) {
        v.resize(capacity + 1);
        size = arr_size;
        for(int i = 0; i < arr_size; i++) {
            v[i+1] = arr[i];
        }
        for(int i = arr_size / 2; i > 0; i--) {
            shift_down(i);
        }
    }

    bool empty() {
        return size == 0;
    }

    void push(int i) {
        assert(size != capacity);
        v[size] = i;
        shift_up(size);
        size++;
    } 

    int top() {
        assert(size > 0);
        if(size > 0) {
            return v[1];
        }
    }

    int pop() {
        assert(size > 0);
        int res = v[1];
        if(size > 1) {
            v[1] = v[size];
            size--;
            shift_down(1);
        } else {
            size--;
        }
        return res;
    }

private:
    void shift_up(int index) {
        if(index == 1) {
            return;
        }
        if(v[index] > v[father(index)]) {
            swap(v[index], v[father(index)]);
            shift_up(father(index));
        }
    }

    void shift_down(int index) {
        int max_index = index;
        if(left_child(index) <= size && v[left_child(index)] > v[max_index]) {
            max_index = left_child(index);
        }
        if(right_child(index) <= size && v[right_child(index)] > v[max_index]) {
            max_index = right_child(index);
        }
        if(max_index != index) {
            swap(v[max_index], v[index]);
            shift_down(max_index);
        }
    }

    inline int left_child(int i) {
        return i * 2;
    }

    inline int right_child(int i) {
        return i * 2 + 1;
    }

    inline int father(int i) {
        return i / 2;
    }

    void print() {
        for(int i = 1; i <= size; i++) {
            cout << v[i] << " " << endl;
        }
        cout << endl;
    }
};

int main() {
    int a[] = {1,4,2,5,7};
    priority_queue q(123, a, 5);
    // q.push(3);
    // q.push(10);
    while(!q.empty()) {
        cout << "q top:" << q.pop() << endl;
    }
    q.push(3);
    q.push(1);
    q.push(89);
    q.push(36);
    q.push(-1);
    q.push(9);
    while(!q.empty()) {
        cout << "q top:" << q.pop() << endl;
    }
}

// compile: g++ 221118-c++priority_queue实现/priority_queue.cpp
// run: ./a.out