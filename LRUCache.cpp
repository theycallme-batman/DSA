#include<iostream>
#include<map>

class Link{

    public:
        //Attributes:
        std::string data;
        Link *next;
        Link *prev;

        //Constructors:

        Link(){
            this->next = nullptr;
            this->prev = nullptr;
            this->data = "";
        }

        Link(const std::string &data){
            this->next = nullptr;
            this->prev = nullptr;
            this->data = data;
        }
};


class Cache{

    public:
        //Attributes:
        Link *head;
        Link *tail;
        int cache_size;
        int curr_len;
        std::map<std::string,Link*> hashmap;

        //Constructor:
        Cache(int len){
            this->head = nullptr;
            this->tail = nullptr;
            this->cache_size = len;
            this->curr_len = 0;
        }

        //Methods:

        //Method 1 - Insertion

        void insert(const std::string &data){
            // There are 2 cases possible - a) cache_hit b) cache_miss

            bool cache_hit_or_miss = false;
            if(hashmap.count(data)) cache_hit_or_miss = true;

            //Case a) - Cache hit
            if(cache_hit_or_miss) cache_hit(data);
            //Case b) - Cache miss
            else cache_miss(data);
        }

        //Method 2 - Cache hit

        void cache_hit(const std::string &data){
            // 2 phases -
            //Phase 1 - removing the element from the list
            //Phase 2 - adding it to the front of the list

            Link *address = hashmap[data];
            Link *front = address->prev;
            Link *back = address->next;

            //Phase 1 
            if(front) front->next = address->next;

            //Need to handle when the cache is hit on the tail element, need to set a new tail as well
            if(back) back->prev = address->prev;
            else{
                //if the back is null; that means it is the last element in the list
                if(front) tail = front;
            }

            //Phase 2
            // if there is only one element in the list with cache hit=>no need to do anything
            // if there are more elements => bring the cache-hit element to the front

            if(data != head->data){
                address->next = head;
                head->prev = address;
                head = address;
            }


        }

        //Method 3 - Cache miss

        void cache_miss(const std::string &data){
            //Phase 1 - Check if the cache is already full => In this case, we need to remove the tail element and set a new tail
            //Phase 2 - if cache is not full, add element at the front
            //Phase 3 - increment curr_len variable

            //Phase 1
            if(curr_len + 1 > cache_size){
                //removing the tail and setting a new tail
                Link *temp_tail = tail;

                //if cache size is only 1, that means head = tail, we cannot set a new tail
                if(head != tail){
                    tail = tail->prev;
                    tail->next = nullptr;
                }
                else{
                    head = nullptr;
                    tail = nullptr;
                }
                hashmap.erase(temp_tail->data);
                delete temp_tail;
            }

            //Phase 2
            if(head == nullptr){
                head = new Link(data);
                tail = head;
            }
            else{
                Link *temp = new Link(data);
                temp->next = head;
                head->prev = temp;
                head = temp;
            }
            hashmap[data] = head;

            //Phase 3
            curr_len += 1;
        }

        //Method 4 - Displaying the list
        void print(){
            Link *temp_head = head;
            while(temp_head){
                std::cout<<temp_head->data<<" ";
                temp_head = temp_head->next;
            }
            std::cout<<std::endl;
        }
};


int main(){

    Cache obj(4);
    obj.insert("Apple");
    obj.print(); //Apple
    obj.insert("Peach");
    obj.print(); // Peach Apple
    obj.insert("Grapes");
    obj.print(); // Grapes Peach Apple
    obj.insert("Mango");
    obj.print(); // Mango Grapes Peach Apple
    obj.insert("Peach");
    obj.print(); // Peach Mango Grapes Apple   
    obj.insert("Kiwi");
    obj.print(); // Kiwi Peach Mango Grapes

    return 0;
}