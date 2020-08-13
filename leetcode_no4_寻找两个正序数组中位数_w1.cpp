/*--------------------------------------------------------------------------------------|
给定两个大小为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。							|
																						|
请你找出这两个正序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。				|
																						|
你可以假设 nums1 和 nums2 不会同时为空。												|
																						|
示例 1:																					|
																						|
nums1 = [1, 3]																			|
nums2 = [2]																				|
																						|
则中位数是 2.0																			|
示例 2:																					|
																						|
nums1 = [1, 2]																			|
nums2 = [3, 4]																			|
																						|
则中位数是 (2 + 3)/2 = 2.5																|
																						|
来源：力扣（LeetCode）																	|
链接：https://leetcode-cn.com/problems/median-of-two-sorted-arrays						|
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。					|
---------------------------------------------------------------------------------------*/

/*	通过划分区域的方式，得到左边半区的最大值小于右边半区最小值的时候就可以比较容易取得中位数
* 
* 
*	形如：
*	|abcdf				a|bcdf			ab|cdf					abc|df				abcd|f				abcdf|
*	qwertygh|jk			qwertyg|hjk		qwerty|ghjk				qwert|yghjk			qwer|tyghjk			qwe|rtyghjk
*	由于两个数组均为递增元素，因此左半部分对应最大元素值为：
*	h					max(a,g)		max(b,y)				max(c,t)			max(d,r)			max(f,e)
*	右半部分对应最小元素为：
*	min(a,j)			min(b,h)		min(c,g)				min(d,y)			min(f,t)			r
*	通过比较即可得出中位数
*	同时要注意没有选取到的区域的复制，inf和-inf要注意赋值位置和关系
* 
* 
*	执行用时：16 ms, 在所有 C++ 提交中击败了84.39%的用户
*	内存消耗：7 MB, 在所有 C++ 提交中击败了95.91%的用户
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) 
{
	if (nums1.size() > nums2.size())														/*	假定nums1的长度比nums2的长度短	*/
	{
		return findMedianSortedArrays(nums2, nums1);
	}

	if (nums1.empty())
	{
		int length = nums2.size();

		double y = nums2[(length + 1) / 2 - 1];

		if (length % 2)
		{
			return y;
		}
		else
		{
			double x = nums2[(length + 1) / 2];
			return (x + y) / 2;
		}
	}
	else
	{
		int l1 = nums1.size();
		int l2 = nums2.size();
		int length = l1 + l2;

		double left_max, right_min;

		for (int i = 0; i <= l1; i++)
		{
			int j = (length + 1) / 2 - i;

			int left1 = (i == 0) ? INT_MIN : nums1[i - 1];
			int right1 = (i == l1) ? INT_MAX : nums1[i];

			int left2 = (j == 0) ? INT_MIN : nums2[j - 1];
			int right2 = (j == l2) ? INT_MAX : nums2[j];

			left_max = max(left1, left2);
			right_min = min(right1, right2);

			if (left_max <= right_min)
			{
				if (length % 2)
				{
					return left_max;
				}
				else
				{
					return (left_max + right_min) / 2;
				}
			}
		}
	}
	return -1;
}

int main()
{
	vector<int> nums1 = {  };
	vector<int> nums2 = { 1 };
	double result;
	////
	/////

	result = findMedianSortedArrays(nums1, nums2);

	cout << result << endl;
}