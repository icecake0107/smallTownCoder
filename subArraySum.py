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
            return (startIndex + 1, startIndex + 1)

        for i in range(1, n):
            cur_sum += arr[i]
            while cur_sum > s and startIndex < i:
                cur_sum -= arr[startIndex]
                startIndex += 1
                if cur_sum == s:
                    return(startIndex + 1, i + 1)

            if cur_sum == s:
                return(startIndex + 1, i + 1)

        return {-1}

# A = "10 20 1000 90 80"
# A = [int(i) for i in A]
# A = [10, 20, 1000, 90, 80]
# n = 5
# s = 1000
# ob = Solution()
# ans = ob.subArraySum(A, n, s)
# print(ans)


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

    def test_5(self):
        A = [10, 20, 1000, 90, 80]

        ob = Solution()
        ans = ob.subArraySum(A, 5, 1000)
        self.assertEqual(ans, (2, 2))

    def test_6(self):
        A = [1, 2, 3, 4]

        ob = Solution()
        ans = ob.subArraySum(A, 4, 0)
        self.assertEqual(ans, {-1})


if __name__ == "__main__":
    unittest.main()