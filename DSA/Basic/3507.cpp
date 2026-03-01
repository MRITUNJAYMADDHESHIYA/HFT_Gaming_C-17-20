#include<iostream>
using namespace std;

//1.is_sorted
//2.find index of the pair having min sum
//3.Replace the pairs with min sum & erase the other element of the pair

//[5,2,3,1]

int minPairSum(vector<int>& nums){
    int minSum = INT_MAX;
    int index = -1;

    for(int i=0; i<nums.size()-1; i++){
        int sum = nums[i] + nums[i+1];

        if(sum < minSum){
            minSum = sum;
            index = i;
        }
    }
    return index;
}
int minimumPairRemoval(vector<int>& nums){
    int count = 0;

    while(!is_sorted(nums.begin(), nums.end())){ //o(n)
        int index = minPairSum(nums); //o(n)---->use set

        nums[index] = nums[index] + nums[index + 1];

        nums.erase(nums.begin() + index + 1);   //o(n) --->for erase use pointing

        count++;
    }
    return count;
}


//3510 leetcode
//1.find data structure to store pairs-->priority_queue + set
//set erase-->log(n)

//at max you can have n-1 bas pairs-->all elements in decreasing order

///story points:-
//1.set<sum,idx>
//2.prevIdx, nextIdx
//3.RemoveSmallestPair---->fistlest{first, second} secondright   update
//                         badpair update
//                    ---->Index update

#include<vector>
typedef long long ll;
int mininumPairRemovalOptimized(vector<int>& nums){
    int n = nums.size();

    vector<ll> temp(n);
    for(int i=0; i<n; i++){
        temp[i] = nums[i];
    }

    set<pair<ll, int>> minPairSet; //{sum, index}

    vector<int> prevIndex(n);
    vector<int> nextIndex(n);

    for(int i=0; i<n; i++){
        prevIndex[i] = i-1;
        nextIndex[i] = i+1;
    }

    int badPairs = n-1;
    for(int i=0; i<n-1; i++){
        if(temp[i] > temp[i+1]){
            badPairs++;
        }
        minPairSet.insert({temp[i] + temp[i+1], i});
    }

    int count = 0;
    
    while(badPairs > 0){
        int first = minPairSet.begin()->second;
        int second = nextIndex[first];

        int first_left = prevIndex[first];
        int second_right = nextIndex[second];

        minPairSet.erase(minPairSet.begin());
        if(temp[first] > temp[second]){
            badPairs--;
        }

        //{d, (a, b)}
        if(first_left >= 0) {
            if(temp[first_left] > temp[first] &&
            temp[first_left] <= temp[first] + temp[second]) {
                badPairs--;
            } 
            else if(temp[first_left] <= temp[first] &&
            temp[first_left] > temp[first] + temp[second]) {
                badPairs++;
            }
        }

        //{(a, b), d}
        if (second_right < n) {
            if (temp[second_right] >= temp[second] &&
                temp[second_right] < temp[first] + temp[second]) {
                badPairs++;
            }
            else if (temp[second_right] < temp[second] &&
                        temp[second_right] >= temp[first] + temp[second]) {
                badPairs--;
            }
        }

        if(first_left >= 0) {
            minPairSet.erase({temp[first_left] + temp[first], first_left});
            minPairSet.insert({temp[first_left] + temp[first] + temp[second], first_left});
        }

        if(second_right < n) {
            minPairSet.erase({temp[second] + temp[second_right], second});
            minPairSet.insert({temp[first] + temp[second] + temp[second_right], first});
            prevIndex[second_right] = first;
        }

        nextIndex[first] = second_right;
        temp[first] += temp[second];

        operations++;
    }

    return operations;
}
