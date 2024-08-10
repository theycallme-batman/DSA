#Given an array of integers nums and an integer target,return indices of the two numbers such that they add up to target.
#You may assume that each input would have exactly one solution, and you may not use the same element twice.
#You can return the answer in any order.

# Example 1:

# Input: nums = [2,7,11,15], target = 9
# Output: [0,1]
# Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

nums = [2,7,11,15]
target = 9
n = len(nums)
#Approach 1 - O(n^2) - time and O(n) - space
# Do two for loops which will iterate through all the possible cases for 2 sum and store in the result array 

# result = []
# for i in range(n):
#     for j in range(i+1,n):
#         if(nums[i] + nums[j] == target):
#             result.append((i,j))


#Approach 2 - O(n) - time O(n) space

hash= {}
result = []
for iter in range(n):
    if(hash.__contains__(target - nums[iter])):
        result.append((iter,hash[target-nums[iter]]))
    hash[nums[iter]] = iter





for iter in result:
    print(iter)





