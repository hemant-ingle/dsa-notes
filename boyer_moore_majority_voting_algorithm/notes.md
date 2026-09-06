# Boyer-Moore Majority Voting Algorithm
The **Boyer-Moore Majority Voting Algorithm** is an O(n) time and O(1) space algorithm used to find the **majority element** in an array.

A **majority element** is an element that appears **more than n / 2 times.**

Example:
```
Input:  [2, 2, 1, 1, 1, 2, 2]

2 appears 4 times
n = 7

4 > 7 / 2

Output: 2
```
The key idea is to treat different elements as **opponents in a duel** and cancel them against each other.

## Classic Problem 
**[Majority Element (Leetcode)](https://leetcode.com/problems/majority-element/description/)**

## Related Problems

- Majority Element
- Majority Element II
- Finding elements occurring more than n / k times
- Streaming majority detection
- Cancellation / voting based problems

## Core Idea

The algorithm works on a simple concept of **cancellation.**

Imagine a **battle between different teams.** Whenever two members from **different teams** meet, they fight a duel and **eliminate each other.**
```
Team A ⚔️ Team B
      ↓
Both eliminated
```
Now suppose one team has a **strict majority** (more than half of all members).

Even if every member of another team is paired against a member of the majority team, the majority team will **always have at least one member remaining at the very end.**

The algorithm applies the same idea to array elements.

By tracking a single `candidate` and a `count` representing the **net strength** of that candidate, opposing elements are cancelled against each other:
```
Same element      → count++
Different element → count--
```
When `count` becomes `0`, the current candidate has been completely cancelled, so the next element can become the new candidate.

### Example
```
[ A, B, A, B, A ]

A ⚔️ B → both eliminated
A ⚔️ B → both eliminated
A      → survives
```
Since A appears more than half the time, it **cannot be completely eliminated.**

Therefore, the final surviving candidate is the **majority element.**

> **Key idea:** Different elements cancel each other like opponents in a duel. A true majority element has enough members to survive all possible cancellations.

## Implementation (Classic Problem)
```cpp
class Solution {
public:
    int majorityElement(vector<int> &nums) {
        int candidate;
        int count = 0;

        for(int x: nums) {
            if(count == 0) {
                candidate = x;
                count = 1; /* count++; */
            } else if(candidate == x) {
                count++;
            } else {
                count--;
            }
        }

        return candidate;
    }
};
```

## Notes (Important Lines)
1. **Maintain a candidate and its vote count**
int candidate;
int count = 0;
- candidate → current possible majority element
- count → net number of votes/strength for the candidate
2. **When `count == 0`, choose a new candidate**
```cpp
if(count == 0) {
    candidate = num;
}
```
The current candidate has been completely cancelled.

Therefore, the current element becomes the new candidate.
```
count = 0

A ⚔️ B
A ⚔️ B
↓
No candidate remains

Next element → new candidate
```
3. **Same element → increase count**
```cpp
if(num == candidate) {
    count++;
}
```
The current element belongs to the candidate's team, so it adds strength.

```
candidate = A

A → count++
A → count++
```
4. **Different element → decrease count**
```cpp
else {
    count--;
}
```

A different element acts as an opponent and cancels one unit of the candidate's strength.
```
candidate = A

A ⚔️ B
↓
count--
```
**Important:** We don't actually remove elements from the array. count simply represents the **net result of the cancellations.**

### Why Does It Work?

Assume `A` is the majority element.
```
If:

count(A) > n / 2

then:

count(A) > count(all non-A elements)

Now imagine pairing every non-A element with an A:

A ⚔️ B → cancelled
A ⚔️ C → cancelled
A ⚔️ B → cancelled
A ⚔️ C → cancelled
A      → remains
```

There are more `A`s than all the opponents combined.

Therefore, **A cannot be completely cancelled.**

This is exactly what the `candidate` and `count` variables simulate.

### Example

Consider:
```
[2, 2, 1, 1, 1, 2, 2]

Process each element:

num   candidate   count
-----------------------
 2       2          1
 2       2          2
 1       2          1
 1       2          0
 1       1          1
 2       1          0
 2       2          1

Final:

candidate = 2

Therefore:

Output: 2
```
The `2`s have survived the cancellation process because they form the majority.

## Key Invariant

At any point:
```
count
```
represents the **net advantage of the current candidate** after conceptually cancelling it against different elements.

The algorithm does not need to store the frequency of every element.

It only needs:
```
candidate + count
```

## Important Limitation

The basic algorithm only guarantees a correct answer when a majority element is **known to exist.**
```
For example:

[1, 2, 3]

has no majority element.
```
The algorithm will still return some `candidate`, but that candidate is not necessarily a majority.

If the problem does **not** guarantee a majority element, verify the candidate using a second pass.
```cpp
int candidate = 0;
int count = 0;

for(int num : nums) {
    if(count == 0) {
        candidate = num;
    }

    if(num == candidate) {
        count++;
    } else {
        count--;
    }
}

count = 0;

for(int num : nums) {
    if(num == candidate) {
        count++;
    }
}

if(count > nums.size() / 2) {
    return candidate;
}

return -1;
```
So:

First pass  → Find candidate
Second pass → Verify candidate

### Quick Memory Trick

Remember the three rules:
```
count == 0 → Choose new candidate

Same      → count++

Different → count--
```
Or think of it as a duel:
```
Same team       → Reinforce ⚔️
Different team  → Duel → Both cancel
```

## The Core Insight

> **A true majority cannot be completely eliminated because it has more members than all opposing teams combined.** 

## Complexity
**Time Complexity**: *O(n)* <br>
**Space Complexity**: *O(1)*