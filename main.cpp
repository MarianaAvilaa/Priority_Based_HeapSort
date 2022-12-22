#include <iostream>
#include <vector>
#include <string>
using namespace std;
template <typename E>
class VectorCompleteTree{
private:
    // private memebers here
    std::vector<E> V;
public:
    typedef typename std::vector<E>::iterator Position; // a position in the tree
protected:
    Position pos(int i){
        return V.begin() +i;
    }
    int idx(const Position &p) const{
        return p-V.begin();
    }
public:
        VectorCompleteTree():V(1){}
    int size() const {
        return V.size()-1;
    }
    Position left(const Position &p){
        return pos(2*idx(p));
    }
    Position right(const Position &p){
        return pos(2*idx(p)+1);
    }
    Position parent(const Position &p){
        return pos(idx(p/2));
    }
    bool hasLeft(const Position &p)const{
        return 2*idx(p)<=size();
    }
    bool hasRight(const Position &p)const{
        return 2*idx(p)+1<=size();
    }
    bool isRoot(const Position &p)const{
        return idx(p) ==1;
    }
    Position root(){
        return pos(1);
    }
    Position last(){
        return pos(size());
    }
    void addLast(const E &e){
        V.push_back(e);
    }
    void removelast(){
        V.pop_back();
    }
    void swap(const Position &p, const Position &q){
        E e=*q;
        *q= *p;
        *p=e;

    }

};
template<typename E, typename C>
class HeapPriorityQueue{
public:
    int size() const{
        return T.size();
    }
    bool empty() const{
        return size() ==0;
    }
    void insert(const E &e){
        T.addLast(e);
        Position  v= T.last();
        while(!T.isRoot(v)){
            Position u= T.parent(v);
            if(!isLess(*v,*u)) {
                break;
            }
            T.swap(v,u);
            v=u;
        }
    }
    const E& min(){
        return  *(T.root());
    }

    void removeMin(){
        if(size()==1){
            T.removelast();
        }else{
            Position u= T.root();
            T.swap(u,T.last());
            T.removelast();
            while(T.hasLeft(u)){
                Position v= T.left(u);
                if(T.hasRight(u)&& isLess(*(T.right(u)),*v)){
                    v= T.right(u);
                }
                if(isLess(*v,*u)){
                    T.swap(u,v);
                    u=v;
                }
                else break;
            }
        }
    }
private:
    VectorCompleteTree<E> T;
    C isLess; // less than comparator
    typedef typename VectorCompleteTree<E>:: Position Position;
};
int main() {
srand(time(0));

VectorCompleteTree<int> tree;
HeapPriorityQueue<int,char> q;

q.insert(1);
q.insert(5);
  cout << q.size();

    return 0;
}
