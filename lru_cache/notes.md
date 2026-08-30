# LRU Cache
An LRU (Least Recently Used) Cache stores a limited number of key-value pairs and removes the least recently used item when the cache reaches its capacity.

The cache must support:

- `get(key)` → return the value if the key exists and mark it as recently used.
- `put(key, value)` → insert/update a key and mark it as recently used.
- When the capacity is exceeded, **evict the least recently used key.**

### **Why is it called LRU?**
**LRU stands for Least Recently Used, which describes the cache's eviction policy.**

When the cache is full and a new item needs to be inserted, we must decide which existing item to remove.

LRU chooses:

> **The item that has not been used for the longest time.**

For example:
```
Capacity = 3

Most Recently Used       Least Recently Used
        ↓                       ↓
       [C]  ←----→  [A] ←----→ [B]

put(D)

Evict B

       [D] ←----→ [C] ←----→ [A]
```

So, LRU is named after the policy used to decide which item gets evicted, not because of how the cache is internally implemented.

Other cache policies can use different eviction rules, such as:

- **LRU** → evict least recently used
- **FIFO** → evict oldest inserted
- **LFU** → evict least frequently used
- **MRU** → evict most recently used

## Classic Problem 
**[LRU Cache (LeetCode)](https://leetcode.com/problems/lru-cache/description/)**

## Related Problems
| #   | Problem | Platform | Solution | Redo |
|----:|:-------:|:--------:|:--------:|:----:|

## Core Idea
Use **two data structures together:**
- `unordered_map` → provides O(1) lookup of a key.
- `list` → maintains the usage order and allows O(1) insertion, removal, and movement of nodes.

Maintain the list in this order:
```
Most Recently Used                    Least Recently Used
        ↓                                      ↓
      [ C ] ←----→ [ A ] ←----→ [ B ] ←----→ [ D ]
      front                                  back
```

The map stores an **iterator to each key's node in the list:**
```
key → list iterator
```
This combination gives us the required O(1) operations:
```
unordered_map
     │
     │ key → iterator
     ▼
   list
   ┌─────────────────────────────────────┐
   │ MRU ←-→ ... ←-→ ... ←-→ ... ←-→ LRU │
   └─────────────────────────────────────┘
```
- On `get`, use the map to find the node and move it to the front.
- On `put`, insert/update the node and move it to the front.
- When capacity is exceeded, remove the node at the back and erase its key from the map.

The important implementation trick is `list::splice()`, which moves an existing list node to the front in **O(1)** without copying it.

## Implementation (Classic Problem)
```cpp
class LRUCache {
private:
    unordered_map<int, list<pair<int, int>>::iterator> keyToNode;
    list<pair<int, int>> cacheList;
    int capacity;
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }

    int get(int key) {
        auto mapIterator = keyToNode.find(key);
        if(mapIterator == keyToNode.end()) {
            return -1;
        }
        auto listIterator = mapIterator->second;
        int value = listIterator->second;
        cacheList.splice(cacheList.begin(), cacheList, listIterator);
        return value;
    }

    void put(int key, int value) {
        auto mapIterator = keyToNode.find(key);
        if(mapIterator != keyToNode.end()) {
            auto listIterator = mapIterator->second;
            listIterator->second = value;
            cacheList.splice(cacheList.begin(), cacheList, listIterator);
            return;
        }
        cacheList.push_front({key, value});
        keyToNode[key] = cacheList.begin();

        if(cacheList.size() > capacity) {
            int leastRecentlyUsedKey = cacheList.back().first;
            keyToNode.erase(leastRecentlyUsedKey);
            cacheList.pop_back();
        }
    }
};
```


## Notes (Important Lines)
1. `unordered_map<int, list<pair<int, int>>::iterator>` **stores an iterator to each key's node in the list.** This gives direct O(1) access to the corresponding list node.
2. `cacheList.splice(cacheList.begin(), cacheList, listIterator);` Moves the accessed node to the front of the list in O(1), without creating or copying the node.
3. **Front = Most Recently Used, Back = Least Recently Used.**
4. **When an existing key is updated, it also becomes the Most Recently Used item.**
5. **When capacity is exceeded, remove** `cacheList.back()` **because it is the Least Recently Used item.**
6. **The map and list must always stay synchronized.** When a node is removed from the list, its key must also be removed from the map.
7. `cacheList.begin()` **is stored after insertion because the newly inserted node is at the front.**

## Complexity
**Time Complexity:** *O(1)* for both `get()` and `put()`. <br>
**Space Complexity:** *O(n)* where n is the capacity. <br>
