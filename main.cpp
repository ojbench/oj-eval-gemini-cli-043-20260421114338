#include <iostream>
#include <cstdio>
using namespace std;

namespace LIST
{

struct NODE
{
    int data;
    NODE *prev, *next;
    NODE(int x) : data(x), prev(nullptr), next(nullptr) {}
};

NODE *head = nullptr, *tail = nullptr;
int len = 0;

void Pre()
{
    head = nullptr;
    tail = nullptr;
    len = 0;
}

NODE* move(int i)
{
    if (i < 0 || i >= len) return nullptr;
    NODE* curr;
    if (i < len / 2) {
        curr = head;
        for (int j = 0; j < i; ++j) curr = curr->next;
    } else {
        curr = tail;
        for (int j = len - 1; j > i; --j) curr = curr->prev;
    }
    return curr;
}

void insert(int i, int x)
{
    NODE* newNode = new NODE(x);
    if (len == 0) {
        head = tail = newNode;
    } else if (i == 0) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    } else if (i == len) {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    } else {
        NODE* curr = move(i);
        newNode->prev = curr->prev;
        newNode->next = curr;
        curr->prev->next = newNode;
        curr->prev = newNode;
    }
    len++;
}

void remove(int i)
{
    if (i < 0 || i >= len) return;
    NODE* curr = move(i);
    if (curr == head && curr == tail) {
        head = tail = nullptr;
    } else if (curr == head) {
        head = head->next;
        head->prev = nullptr;
    } else if (curr == tail) {
        tail = tail->prev;
        tail->next = nullptr;
    } else {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }
    delete curr;
    len--;
}

int Get_length()
{
    return len;
}

int Query(int i)
{
    if (i < 0 || i >= len) return -1;
    NODE* curr = move(i);
    return curr->data;
}

void Print()
{
    if (len == 0) {
        cout << -1 << endl;
        return;
    }
    NODE* curr = head;
    while (curr) {
        cout << curr->data << (curr->next ? " " : "");
        curr = curr->next;
    }
    cout << endl;
}

void Clear()
{
    NODE* curr = head;
    while (curr) {
        NODE* next = curr->next;
        delete curr;
        curr = next;
    }
    head = tail = nullptr;
    len = 0;
}

}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    int op, x, p, ans;
    LIST::Pre();
    for (int _=0;_<n;++_)
    {
        if (!(cin >> op)) break;
        switch(op)
        {
            case 0:
                ans = LIST::Get_length();
                cout << ans << "\n";
                break;
            case 1:
                cin >> p >> x;
                LIST::insert(p,x);
                break;
            case 2:
                cin >> p;
                ans = LIST::Query(p);
                cout << ans << "\n";
                break;
            case 3:
                cin >> p;
                LIST::remove(p);
                break;
            case 4:
                LIST::Print();
                break;
        }
    }
    LIST::Clear();
    return 0;
}
