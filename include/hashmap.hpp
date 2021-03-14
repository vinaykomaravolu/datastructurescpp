#include <iostream>
#include <functional>
#include <vector>

using namespace std;

template <typename K, typename V>
class HashNode
{
public:
    K key;
    V value;
    HashNode<K, V> *next = nullptr;

    HashNode(K key, V value)
    {
        this->key = key;
        this->value = value;
    }
};

template <typename K, typename V>
class HashMap
{
public:
    HashMap(size_t hashsize)
    {
        this->hashsize = hashsize;
        this->allocatedsize = 0;
        storage.resize(this->hashsize, nullptr);
    }

    HashMap()
    {
        this->hashsize = 64;
        this->allocatedsize = 0;
        storage.resize(this->hashsize, nullptr);
    }

    ~HashMap(){
        for(int i = 0; i < this->storage.size(); i++){
            if(this->storage[i] == nullptr){
                continue;
            }
            HashNode<K,V> * curr = this->storage[i];
            HashNode<K,V> * temp = nullptr;
            while(curr){
                temp = curr;
                curr = curr->next;
                delete temp;
                temp = nullptr;
            }
        }
    }

    void put(K key, V value)
    {
        int index = this->hashIndex(key);
        if(storage[index] == nullptr){
            HashNode<K,V> * newNode = new HashNode<K,V>(key, value);
            storage[index] = newNode;
            this->allocatedsize++;                
        }else{
            HashNode<K,V> * node = storage[index];
            while(node != nullptr){
                if(node->key == key){
                    node->value = value;
                    return;
                }
                if(node->next == nullptr){
                    HashNode<K,V> * newNode = new HashNode<K,V>(key, value);
                    node->next = newNode;
                    this->allocatedsize++;                
                    return;
                }
                node = node->next;
            }
        }
    }

    V * get(K key){
        int index = this->hashIndex(key);
        HashNode<K,V> * node = storage[index];
        while(node != nullptr){
            if(node->key == key){
                return &node->value;
            }
            node = node->next;
        }
        return nullptr;
    }

    bool remove(K key){
        int index = this->hashIndex(key);
        HashNode<K,V> * node = storage[index];
        HashNode<K,V> * prev = nullptr;
        while(node != nullptr){
            if(node->key == key){
                if(prev == nullptr){
                    storage[index] = node->next;
                }else{
                    prev->next = node->next;
                }
                this->allocatedsize--;                
                delete node;
                return true;
            }
            prev = node;
            node = node->next;
        }
        return false;
    }

    size_t size(){
        return this->allocatedsize;
    }

private:
    vector<HashNode<K, V> *> storage;
    hash<K> hashf;
    size_t hashsize;
    size_t allocatedsize;

    int hashIndex(K key){
        return int(this->hashf(key) % this->hashsize);
    }
};
