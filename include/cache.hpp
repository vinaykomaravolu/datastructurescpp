#pragma once
#include "hashmap.hpp"
#include <iostream>

using namespace std;

template <typename K, typename V>
class CacheNode
{
public:
    CacheNode *next = nullptr;
    CacheNode *prev = nullptr;
    K key;
    V val;
    CacheNode(K key, V val)
    {
        this->key = key;
        this->val = val;
    }
};

template <typename K, typename V>
class Cache
{
    virtual V get(K key) = 0;
    virtual void put(K key, V value) = 0;
};

template <typename K, typename V>
class LRUCache : public Cache<K, V>
{
public:
    LRUCache(int capacity)
    {
        this->capacity = capacity;
    }

    V get(K key)
    {
        CacheNode<K, V> **curr = hashmap.get(key);
        if (this->currcapacity != 1)
        {
            if ((*curr) == head)
            {
                this->head = this->head->next;
                this->head->prev = nullptr;
                (*curr)->prev = tail;
                (*curr)->next = nullptr;
                tail->next = (*curr);
                tail = (*curr);
            }
            else if ((*curr) != head && (*curr) != tail)
            {
                (*curr)->prev->next = (*curr)->next->prev;
                this->tail->next = (*curr);
                (*curr)->prev = this->tail;
                (*curr)->next = nullptr;
                this->tail = (*curr);
            }
        }

        return (*curr)->val;
    }

    void put(K key, V value)
    {

        if (this->head == nullptr || this->tail == nullptr)
        {
            CacheNode<K, V> *node = new CacheNode<K, V>(key, value);
            hashmap.put(key, node);
            this->head = node;
            this->tail = node;
            this->currcapacity++;
        }
        else
        {
            if (hashmap.exists(key))
            {
                CacheNode<K, V> **curr = hashmap.get(key);
                (*curr)->val = value;
                if (this->currcapacity != 1)
                {
                    if ((*curr) == this->head)
                    {
                        this->head = this->head->next;
                        this->head->prev = nullptr;
                        this->tail->next = (*curr);
                        (*curr)->prev = this->tail;
                        (*curr)->next = nullptr;
                        this->tail = (*curr);
                    }
                    else if ((*curr) != head && (*curr) != tail)
                    {
                        (*curr)->prev->next = (*curr)->next->prev;
                        this->tail->next = (*curr);
                        (*curr)->prev = this->tail;
                        (*curr)->next = nullptr;
                        this->tail = (*curr);
                    }
                }
            }
            else
            {
                CacheNode<K, V> *node = new CacheNode<K, V>(key, value);
                if (this->currcapacity < this->capacity)
                {
                    hashmap.put(key, node);
                    this->tail->next = node;
                    node->prev = this->tail;
                    this->tail = node;
                    this->currcapacity++;
                }
                else
                {
                    CacheNode<K, V> *nodedelete = this->head;
                    this->head = this->head->next;
                    this->head->prev = nullptr;
                    hashmap.remove(nodedelete->key);
                    delete nodedelete;
                    hashmap.put(key, node);
                    this->tail->next = node;
                    node->prev = this->tail;
                    this->tail = node;
                }
            }
        }
    }

    V LRUValue()
    {
        if (head)
        {
            return head->val;
        }
        throw invalid_argument("Cache Empty");
    }

    V MRUValue()
    {
        if (tail)
        {
            return tail->val;
        }
        throw invalid_argument("Cache Empty");
    }

    int size()
    {
        return this->capacity;
    }

    int currentsize()
    {
        return this->currcapacity;
    }

private:
    int capacity;
    int currcapacity = 0;
    CacheNode<K, V> *head = nullptr;
    CacheNode<K, V> *tail = nullptr;
    HashMap<K, CacheNode<K, V> *> hashmap;
};

template <typename K, typename V>
class LFUCache : public Cache<K, V>
{
    V get(K key)
    {
    }
    void put(K key, V value)
    {
    }
};