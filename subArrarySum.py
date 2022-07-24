"""
Subarray with given sum
Given an unsorted array A of size N that contains only non-negative integers, find a continuous sub-array which adds to a given number S.

In case of multiple subarrays, return the subarray which comes first on moving from left to right.

"""


import unittest

class Solution:
    def subArraySum(self, arr, n, s):
        startIndex = 0
        cur_sum = arr[0]
        if cur_sum == s:
            return (startIndex, startIndex)

        for i in range(1, n):
            cur_sum += arr[i]
            print(f"i: {i} {arr[i]}, cur_sum: {cur_sum}, {arr[i]}")
            while cur_sum > s and startIndex < i - 1:
                cur_sum -= arr[startIndex]
                startIndex += 1

            # if cur_sum < s:
            #     cur_sum += arr[i]
            if cur_sum == s:
                return(startIndex, i)

        return {-1}


class TestSubArray(unittest.TestCase):
    def test_1(self):
        A = "135 101 170 125 79 159 163 65 106 146 82 28 162 92 196 143 28 37 192 5 103 154 93 183 22 117 119 96 48 127 172 139 70 113 68 100 36 95 104 12 123 134".split(
            " ")
        A = [int(i) for i in A]
        n = 42
        s = 468
        ob = Solution()
        ans = ob.subArraySum(A, n, s)
        self.assertEqual(ans, (37, 41))

    def test_2(self):
        A = "1 2 3 7 5".split(" ")
        A = [int(i) for i in A]

        ob = Solution()
        ans = ob.subArraySum(A, 5, 12)
        self.assertEqual(ans, (1, 3))

    def test_3(self):
        A = "1 2 3 4 5 6 7 8 9 10".split(" ")
        A = [int(i) for i in A]

        ob = Solution()
        ans = ob.subArraySum(A, 10, 15)
        self.assertEqual(ans, (0, 4))

    def test_4(self):
        A = "1 2 3 4 5 6 7 8 9 10".split(" ")
        A = [int(i) for i in A]

        ob = Solution()
        ans = ob.subArraySum(A, 10, 14)
        self.assertEqual(ans, (1, 4))


if __name__ == "__main__":
    unittest.main()