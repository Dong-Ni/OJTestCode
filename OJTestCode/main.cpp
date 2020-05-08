
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <regex>
#include <stack>
#include <unordered_map>
#include <queue>

using namespace std;

//1.两数之和
//给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
//
//你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。
//
//示例 :
//
//给定 nums = [2, 7, 11, 15], target = 9
//
//因为 nums[0] + nums[1] = 2 + 7 = 9
//所以返回[0, 1]
//
vector<int> twoSum(vector<int>& nums, int target) {
	vector<int>  vRet;
	for (size_t i = 0; i < nums.size(); i++)
	{
		for (size_t j = i+1; j < nums.size(); j++)
		{
			if ((nums[i] + nums[j]) == target)
			{
				vRet.emplace_back(i);
				vRet.emplace_back(j);
			}
		}
	}
	return vRet;
}

//2.两数相加
//给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。
//
//如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。
//
//您可以假设除了数字 0 之外，这两个数都不会以 0 开头。
//输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
//输出：7 -> 0 -> 8
//原因：342 + 465 = 807
  struct ListNode {
      int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
  };
  void addTwoNumbersToAnather(ListNode* l1, ListNode* l2, ListNode* lNext, bool Inc) {	  
	  int nSum = l1->val + l2->val;
	  if (Inc)
	  {
		  nSum += 1;
	  }
	  bool bInc = false;
	  if (nSum >= 10)
	  {
		  nSum -= 10;
		  bInc = true;
	  }
	  lNext->val = nSum;

	  if (l1->next == NULL && l2->next == NULL)
	  {
		  if (bInc)  lNext->next = new ListNode(1);
		  return;
	  }

	  lNext->next = new ListNode(0);
	  if (l1->next == NULL)
	  {
		  l1->next = new ListNode(0);
	  }
	  
	  if (l2->next == NULL)
	  {
		  l2->next = new ListNode(0);
	  }

	  addTwoNumbersToAnather(l1->next, l2->next, lNext->next, bInc);
  }
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	ListNode *pRet = new ListNode(0);
	addTwoNumbersToAnather(l1, l2, pRet, false);

	return pRet;
}

//3.最长子串
//给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。
//输入: "abcabcbb"
//输出 : 3
//解释 : 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
int lengthOfLongestSubstring(string s) {
	int nTotal = 0;
	string strSub;
	int nTmpTotal = 0;
	for (size_t i = 0; i < s.size(); ++i)
	{
		strSub.clear();
		strSub.push_back(s[i]);
		nTmpTotal = 1;
		for (size_t j = i + 1; j < s.size(); ++j)
		{
			if (find(strSub.begin(), strSub.end(), s[j]) == strSub.end())
			{
				strSub.push_back(s[j]);
				nTmpTotal += 1;
			}
			else
			{
				break;
			}
		}

		if (nTmpTotal > nTotal)
		{
			nTotal = nTmpTotal;
		}
	}

	return nTotal;
}


//5. 最长回文数
//给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。
//输入: "babad"
//输出 : "bab"
//注意 : "aba" 也是一个有效答案。
int CalaLen(string s, int nLeft, int nRight)
{
	while (nLeft >= 0 && nRight < s.length() && s[nLeft] == s[nRight])
	{
		nLeft--;
		nRight++;
	}

	return nRight - nLeft - 1;
}
string longestPalindrome(string s) {
	string strRet;
	int nSum = 0;
	int nStart = 0;
	int nEnd = 0;
	for (int i = 0; i < s.length(); ++i)
	{
		int nLen1 = CalaLen(s, i, i);
		int nLen2 = CalaLen(s, i, i+1);
		nSum = nLen1 > nLen2 ?nLen1 : nLen2;

		if (nSum > nEnd - nStart) {
			nStart = i - (nSum - 1) / 2;
			nEnd = i + nSum / 2;
		}
	}

	strRet = s.substr(nStart, nEnd - nStart + 1);
	return strRet;
}

//6.Z字形变化
//将一个给定字符串根据给定的行数，以从上往下、从左到右进行 Z 字形排列。
//
//比如输入字符串为 "LEETCODEISHIRING" 行数为 3 时，排列如下：
//
//L   C   I   R
//E T O E S I I G
//E   D   H   N
//之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："LCIRETOESIIGEDHN"。
string convert(string s, int numRows) {

	vector<string> vecStr;
	string strRet;
	if (numRows == 1)
	{
		return s;
	}

	for (int i = 0; i < s.length();)
	{
		for (int j = 0; j < numRows - 1; ++j)
		{
			string strTmp;
			for (int k = 0; k < numRows; ++k)
			{
				strTmp.push_back(' ');
			}

			if (j == 0)
			{
				for (int nIndex = 0; i < s.length() && nIndex < numRows; ++i, ++nIndex)
				{
					strTmp[nIndex] = s[i];
				}
			}
			else
			{
				strTmp[numRows - j - 1] = s[i];
				i++;
			}

			vecStr.emplace_back(strTmp);

			if (i >= s.length())
			{
				break;
			}
		}
	}

	for (int j = 0; j < numRows; ++j)
	{
		vector<string>::iterator it = vecStr.begin();
		for (; it != vecStr.end(); ++it)
		{
			if (it->at(j) != ' ')
			{
				strRet.push_back(it->at(j));
			}
		}
	}

	return strRet;
}

//7 整数反转
//给出一个 32 位的有符号整数，你需要将这个整数中每位上的数字进行反转
//输入: -123
//输出: -321
//输入: 123
//输出: 321
int reverse(int x) {
	int rev = 0;
	while (x != 0)
	{
		int pop = x % 10;
		x /= 10;
		if (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && pop > 7)) return 0;
		if (rev < INT_MIN / 10 || (rev == INT_MIN / 10 && pop > 8)) return 0;
		rev = rev * 10 + pop;
	}

	return rev;
}

//49 字母异位词分组
//给定一个字符串数组，将字母异位词组合在一起。字母异位词指字母相同，但排列不同的字符串
vector<vector<string>> groupAnagrams(vector<string> strs) {
	map<string, vector<string>> mapStrVector;
	vector<vector<string>> vecVecStrRet;
	for (auto it : strs)
	{
		string tmp = it;
		sort(tmp.begin(), tmp.end());
		mapStrVector[tmp].emplace_back(it);
	}

	for (auto it : mapStrVector)
	{
		vecVecStrRet.emplace_back(it.second);
	}

	return vecVecStrRet;

}

//11 最大水位
//给定 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0)。
//找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
int maxArea(vector<int>& height) {
	int nMaxRet = 0;
	for (int i = 0; i < height.size() - 1; ++i)
	{
		for (int j = i+1; j < height.size(); ++j)
		{
			int nTmp = (j - i) * min(height[i], height[j]);
			nMaxRet = nTmp > nMaxRet ? nTmp : nMaxRet;
		}
	}

	return nMaxRet;
}
//上面解法 两个for循环 执行会超时
//双指针法
int maxArea2(vector<int>& height) {
	int nMaxRet = 0;
	int nLeft = 0;
	int nRight = height.size() - 1;
	while (nLeft < nRight)
	{
		int nTmp = (nRight - nLeft) * min(height[nLeft], height[nRight]);
		nMaxRet = nMaxRet > nTmp ? nMaxRet : nTmp;

		if (height[nLeft] <= height[nRight])
		{
			nLeft++;
		}
		else
		{
			nRight--;
		}
	}

	return nMaxRet;
}

//写出一个程序，接受一个由字母和数字组成的字符串，和一个字符，然后输出输入字符串中含有该字符的个数。不区分大小写。
void nNums(string strInput, map<char, int>& mapCharInt)
{
	for (auto it : strInput)
	{
		if (it != ' ')
		{
			it = tolower(it);
		}
		mapCharInt[it] += 1;
	}
}

//明明想在学校中请一些同学一起做一项问卷调查，为了实验的客观性，他先用计算机生成了N个1到1000之间的随机整数（N≤1000），
//对于其中重复的数字，只保留一个，把其余相同的数去掉，不同的数对应着不同的学生的学号。然后再把这些数从小到大排序，按照排好的顺序去找同学做调查。
//请你协助明明完成“去重”与“排序”的工作(同一个测试用例里可能会有多组数据，希望大家能正确处理)。
void SortAndRemoveSmae(vector<int> &vecInt)
{
	vector<int> vecInputTmp = vecInt;
	vecInt.clear();
	for (auto it : vecInputTmp)
	{
		if (find(vecInt.begin(), vecInt.end(), it) == vecInt.end())
		{
			vecInt.emplace_back(it);
		}
	}

	sort(vecInt.begin(), vecInt.end());
}

//•连续输入字符串，请按长度为8拆分每个字符串后输出到新的字符串数组；
//•长度不是8整数倍的字符串请在后面补数字0，空字符串不处理。
vector<string> SplitString(string strInput)
{
	vector<string> vecStrRet;
	if (strInput.empty())
	{
		return vecStrRet;
	}

	int nSplitTimes = strInput.length() / 8;
	int nSplitRem = strInput.length() % 8;
	
	for (int i = 0; i < nSplitTimes; ++i)
	{
		string strTmps = strInput.substr(i * 8, 8);
		vecStrRet.emplace_back(strTmps);
	}

	if (nSplitRem > 0)
	{
		string strRem = strInput.substr(nSplitTimes*8, nSplitRem);
		for (int i = 8; i > nSplitRem; --i)
		{
			strRem.push_back('0');
		}
		vecStrRet.emplace_back(strRem);
	}

	return vecStrRet;
}

//编写一个函数，计算字符串中含有的不同字符的个数。字符在ACSII码范围内(0~127)，换行表示结束符，不算在字符里。不在范围内的不作统计。
int NumsInACSII(string strInput)
{	
	vector<int>  vecNums;
	for (auto it : strInput)
	{
		if (0 <= it && it <= 127)
		{
			if (find(vecNums.begin(), vecNums.end(), it) == vecNums.end())
			{
				vecNums.emplace_back(it);
			}
		}
	}

	return vecNums.size();
}

//华为机试题（2019.11.21）
string SameAAndB(vector<int> vecInput1, vector<int> vecInput2)
{
	string strRet;
	int nANums = 0;
	int nBNums = 0;

	vector<int> vecSameANum;

	//计算A
	for (int i = 0; i < 4; ++i)
	{
		if (vecInput1[i] == vecInput2[i])
		{
			nANums++;
			vecSameANum.emplace_back(vecInput1[i]);
		}
	}

	//计算B
	for (int j = 0; j < 4; ++j)
	{
		if ((find(vecInput1.begin(), vecInput1.end(), vecInput2[j]) != vecInput1.end())
			&& find(vecSameANum.begin(), vecSameANum.end(), vecInput2[j]) == vecSameANum.end())
		{
			nBNums++;
		}
	}

	strRet.push_back(nANums + '0');
	strRet.push_back('A');
	strRet.push_back(nBNums + '0');
	strRet.push_back('B');

	return strRet;
}

//33. 搜索旋转排序数组
int findTargetIndex(vector<int>& nums, int nTarget, int nBeg, int nEnd)
{
	int nIndex = (nBeg + nEnd) / 2;
	while (true)
	{
		if (nums[nIndex] == nTarget)
		{
			return nIndex;
		}
		else if (nums[nIndex] > nTarget)
		{
			nEnd = nIndex;
			nIndex = (nBeg + nEnd) / 2;
		}
		else
		{
			nBeg = nIndex;
			nIndex = (nBeg + nEnd) / 2;
		}

		if (nBeg == nEnd && nums[nBeg] == nTarget)
		{
			return nBeg;
		}

		if (nBeg > nEnd || nIndex == nBeg || nIndex == nEnd)
		{
			if (nums[nEnd] == nTarget) return nEnd;
			if (nums[nBeg] == nTarget) return nBeg;
			return -1;
		}
	}
}
int search(vector<int>& nums, int nTarget) {
	if (nums.size() == 0) return -1;
	if (nums.size() == 1) return nums[0] == nTarget ? 0 : -1;
	if (nums.size() == 2)
	{
		if (nums[0] == nTarget) return 0;
		if (nums[1] == nTarget) return 1;
		return -1;
	}
	if (nums.size() == 3)
	{
		if (nums[0] == nTarget) return 0;
		if (nums[1] == nTarget) return 1;
		if (nums[2] == nTarget) return 2;
		return -1;
	}
	if (nums.size() == 4)
	{
		if (nums[0] == nTarget) return 0;
		if (nums[1] == nTarget) return 1;
		if (nums[2] == nTarget) return 2;
		if (nums[3] == nTarget) return 3;
		return -1;
	}

	int nBeg = 0;
	int nEnd = nums.size() - 1;
	int i = (nBeg + nEnd) / 2;
	while (i > 0)
	{
		//寻找中间旋转点i
		if (i + 1 < nums.size() && nums[i] > nums[i + 1])
		{
			//判断在前半区间还是后半区间
			if (nums[0] <= nTarget && nums[i] >= nTarget)
			{
				//前半区
				nBeg = 0;
				nEnd = i;
				return findTargetIndex(nums, nTarget, nBeg, nEnd);
			}
			else if (nums[i + 1] <= nTarget && nums[nums.size() - 1] >= nTarget)
			{
				//后半区
				nBeg = i + 1;
				nEnd = nums.size() - 1;
				return findTargetIndex(nums, nTarget, nBeg, nEnd);
			}
			else
			{
				return -1;
			}
		}

		if (nums[i] > nums[0])
		{
			nBeg = i;
			i = (nBeg + nEnd) / 2;
		}
		else
		{
			nEnd = i;
			i = (nBeg + nEnd) / 2;
		}

		//没有倒序
		if (nBeg == nEnd || i == nBeg || i == nEnd)
		{
			return  (nums[0] == nTarget) ? 0 : findTargetIndex(nums, nTarget, 0, nums.size() - 1);
		}
	}
	return  -1;
}

//39.组合总和
//给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
//candidates 中的数字可以无限制重复被选取。
void DFS(int nPos, int target, vector<int>& road, vector<int>& candidates, vector<vector<int>>& vecVecRet)
{
	if (target == 0)
	{
		vecVecRet.push_back(road);
		return;
	}

	for (int i = nPos; i < candidates.size(); ++i)
	{
		if (target < candidates[i]) return;
		target -= candidates[i];
		road.push_back(candidates[i]);
		DFS(i, target, road, candidates, vecVecRet);
		target += candidates[i];
		road.pop_back();
	}
}
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
	vector<vector<int>> vecVecRet;
	sort(candidates.begin(), candidates.end());
	vector<int> road;
	DFS(0, target, road, candidates, vecVecRet);

	return vecVecRet;
}

//54. 螺旋矩阵
//给定一个包含 m x n 个元素的矩阵（m 行, n 列），请按照顺时针螺旋顺序，返回矩阵中的所有元素。
vector<int> spiralOrder(vector<vector<int>>& matrix) {
	vector<int> vecRet;
	if (matrix.empty()) return vecRet;
	if (matrix[0].empty()) return vecRet;

	int i = 0;
	int j = 0;
	int nRows = matrix.size();
	int nCols = matrix[0].size();

	for (int nIndex = 0; ;)
	{
		nIndex = i;
		while (j < nCols - nIndex)
		{
			vecRet.push_back(matrix[i][j]);
			j++;
		}
		j--;
		if (vecRet.size() == nCols * nRows)
		{
			break;
		}

		i++;
		while (i < nRows - nIndex)
		{
			vecRet.push_back(matrix[i][j]);
			i++;
		}
		i--;
		if (vecRet.size() == nCols * nRows)
		{
			break;
		}

		j--;
		while (j >= nIndex)
		{
			vecRet.push_back(matrix[i][j]);
			j--;
		}
		j++;
		if (vecRet.size() == nCols * nRows)
		{
			break;
		}

		i--;
		while (i > j)
		{
			vecRet.push_back(matrix[i][j]);
			i--;
		}
		i++;
		j++;

		if (vecRet.size() == nCols * nRows)
		{
			break;
		}
	}

	return vecRet;
}

//56.最后一个单词的长度
//给定一个仅包含大小写字母和空格 ' ' 的字符串，返回其最后一个单词的长度。
int lengthOfLastWord(string s) {
	int nIndex = s.find_last_of(' ');
	if (nIndex < 0)
	{
		return s.size();
	}
	else if (nIndex == s.size() - 1)
	{
		int nIndexStr = s.find_last_not_of(' ');
		string strSub = s.substr(0, nIndexStr+1);
		return lengthOfLastWord(strSub);
	}
	else
	{
		return s.size() - nIndex - 1;
	}
}

//找出给定字符串中大写字符(即'A'-'Z')的个数 华为机试
int calcBigalhaNums(string s)
{
	int nNums = 0;
	for (auto it : s)
	{
		if ('A' <= it && 'Z' >= it)
		{
			nNums++;
		}
	}

	return nNums;
}

//输入一个整数，将这个整数以字符串的形式逆序输出
//程序不考虑负数的情况，若数字含有0，则逆序形式也含有0，如输入为100，则输出为001
string Int2Str(int nNum)
{
	string strRet;
	while (nNum >= 10)
	{
		int nTmp = nNum % 10;
		nNum = nNum / 10;
		strRet.push_back(nTmp + '0');
	}
	strRet.push_back(nNum + '0');

	//reverse(strRet.begin(), strRet.end());

	return strRet;
}

//华为机试 （2019.12.13）
//给定一组字符串，包括大小写字母，求同一字母组成的最长子串，字母不区分大小写
string str2MaxStr(string strInput)
{
	if (strInput.size() <= 1) return strInput;

	string strRet;
	string strTmp;
	char curChr = strInput[0];
	strTmp.push_back(curChr);
	strRet.push_back(curChr);
	for (int i = 1; i< strInput.size(); ++i)
	{
		if (strInput[i] == curChr || (strInput[i] - curChr == 32) || (curChr - strInput[i] == 32))
		{
			strTmp.push_back(strInput[i]);
		}
		else
		{
			curChr = strInput[i];
			if (strTmp.size() > strRet.size())
			{
				strRet = strTmp;
			}
			strTmp.clear();
			strTmp.push_back(curChr);
		}
	}

	if (strTmp.size() > strRet.size())
	{
		strRet = strTmp;
	}

	return strRet;
}

//64. 最小路径和
//给定一个包含非负整数的 m x n 网格，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
int minPathSum(vector<vector<int>>& grid)
{
	int nRet = 0;
	if (grid.empty()) return nRet;
	if (grid[0].empty()) return nRet;

	int nRow = grid.size();
	int nCol = grid[0].size();
	vector<vector<int>> vecVecSum(nRow, vector<int>(nCol, 0));
	for (int i = 0; i < nRow; ++i)
	{
		for (int j = 0; j < nCol; ++j)
		{
			if (i == 0 && j == 0) vecVecSum[i][j] = grid[i][j];
			else if (i == 0 && j != 0) vecVecSum[i][j] = grid[i][j] + vecVecSum[i][j-1];
			else if (i != 0 && j == 0) vecVecSum[i][j] = grid[i][j] + vecVecSum[i-1][j];
			else
			{
				vecVecSum[i][j] = min(vecVecSum[i - 1][j], vecVecSum[i][j - 1]) + grid[i][j];
			}			
		}
	}

	return vecVecSum[nRow -1][nCol-1];
}

//87.扰乱字符串 
//递归解法
//就是s1和s2是scramble的话，那么必然存在一个在s1上的长度l1，将s1分成s11和s12两段，
//同样有s21和s22.那么要么s11和s21是scramble的并且s12和s22是scramble的；要么s11和s22是scramble的并且s12和s21是scramble的
bool isScramble(string s1, string s2) {
	if (s1.size() != s2.size()) return false;
	if (s1 == s2) return true;
	string str1 = s1;
	string str2 = s2;
	sort(str1.begin(), str1.end());
	sort(str2.begin(), str2.end());
	if (str1 != str2) return false;
	for (int i = 1; i < s1.size(); ++i)
	{
		string str11 = s1.substr(0, i);
		string str12 = s1.substr(i);
		string str21 = s2.substr(0, i);
		string str22 = s2.substr(i);
		if (isScramble(str11, str21) && isScramble(str12, str22)) return true;
		str21 = s2.substr(0, str12.size());
		str22 = s2.substr(str12.size());
		if (isScramble(str11, str22) && isScramble(str12, str21)) return true;
	}

	return false;
}

//92. 反转链表 II
//反转从位置 m 到 n 的链表。请使用一趟扫描完成反转。
//
//说明 :
//1 ≤ m ≤ n ≤ 链表长度。
//
//示例 :
//
//输入: 1->2->3->4->5->NULL, m = 2, n = 4
//输出 : 1->4->3->2->5->NULL
ListNode* reverseBetween(ListNode* head, int m, int n) {
	ListNode* nodeBeg = head;
	ListNode* nodeFirst = NULL;
	for (int i = 1; i <= m; i++)
	{
		if (i == n)
		{
			nodeFirst = head->next;
		}

		head = head->next;
	}

	return head;
}

//利用堆栈实现LISP
bool isChar(char c)
{
	if ('a' <= c && c <= 'z')
	{
		return true;
	}
	return false;
}
bool isNum(char c)
{
	if (('0' <= c && c <= '9') || c == '-')
	{
		return true;
	}
	return false;
}
void stackLSIP()
{
	stack<int> stkNum;
	stack<string> stkOpe;
	string str = "(add 1 2)";
	//getline(cin, str);
	int output;
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str.at(i) == '(')
		{
			char buf[2] = { 0 };
			buf[0] = str.at(i);
			stkOpe.push(buf);
		}
		else if (isChar(str.at(i)))
		{
			char buf[4] = { 0 };
			buf[0] = str.at(i);
			buf[1] = str.at(++i);
			buf[2] = str.at(++i);
			stkOpe.push(buf);
		}
		else if (str.at(i) == ')')
		{
			int num1 = stkNum.top();
			stkNum.pop();
			int num2 = stkNum.top();
			stkNum.pop();

			string opr = stkOpe.top();
			stkOpe.pop();
			stkOpe.pop();

			if (opr == "mul")
			{
				output = num1 * num2;
			}
			else if (opr == "add")
			{
				output = num1 + num2;
			}
			else if (opr == "sub")
			{
				output = num1 - num2;
			}
			else if (opr == "div")
			{
				if (num1 == 0)
				{
					cout << "error" << endl;
					return;
				}
				else
				{
					output = num2 / num1;
				}
			}

			if (!stkOpe.empty())
			{
				stkNum.push(output);
			}

		}
		else if (isNum(str.at(i)))
		{
			char buf[64] = { 0 };
			int j = 0;
			while (isNum(str.at(i)))
			{
				buf[j] = str.at(i);
				j++;
				i++;
			}
			--i;
			int num = stoi(buf);
			stkNum.push(num);
		}
	}
	cout << output << endl;
}


//数字转换成二进制后1的个数
void ToCalc1Num()
{
	int num;
	//cin >> num;
	num = 5; // out 2
	int nCount = 1; //最前面一位肯定是1
	while (num / 2 != 0)
	{
		int rem = num % 2;
		num = num / 2;
		if (rem == 1)
		{
			nCount++;
		}
	}
	cout << nCount;
}

//购物单  未实现
typedef struct val
{
	int Index;
	int money;
	int Imp;
	int relVal;

	val()
	{
		Index = 0;
		money = 0;
		Imp = 0;
		relVal = 0;
	}

}val_t;
void CalcAllVal(vector<val_t> val, vector<int> slt, int totalMon)
{
	if (val.empty())
	{
		return;
	}
}
void  buyOrder()
{
	int money;
	int num;
	cin >> money >> num;
	int evyMoney = 0;
	int evyVal = 0;
	int evyImp = 0;
	int index = 1;
	vector<val_t> vecVal;
	vector<int> vecSlt;
	int maxVal = 0;
	while (true)
	{
		cin >> evyMoney >> evyImp >> evyVal;
		val_t val;
		val.Index = index;
		val.money = evyMoney;
		val.Imp = evyImp;
		val.relVal = evyVal;
		vecVal.push_back(val);
		index++;
		if (index > num)
		{
			break;
		}
	}


	for (size_t i = 0; i < vecVal.size(); i++)
	{
		vector<int>::iterator it = find(vecSlt.begin(), vecSlt.end(), vecVal[i].relVal);
		if (vecVal[i].money < money && (vecVal[i].relVal == 0 || it != vecSlt.end()))
		{
			vecSlt.push_back(i);
			money -= vecVal[i].money;
		}

		//计算价值
		for (size_t j = 0; j < vecSlt.size(); j++)
		{

		}
	}

}

//坐标移动
bool CheckInput(string str)
{
	regex rge("(A|W|S|D)[0-9]{1,2}");
	return regex_match(str, rge);
}
void MovePoint()
{
	string str;
	//str = "A10;S20;W10;D30;X;A1A;B10A11;;A10;"; // 10,-10
	//str = "W49; W92; A84; W33; A32; A52; D97; S14; S33; D79; A14; W25; D97; D21; D31; A66; S67; S4; A59; S62; W40; S26; S65; A58; S17; A67; D48; W23; D68; S99; S97; W63; W27; D12; D83; W8; S3; W6; A88; D23; W30; S91; D58; W74; D45; W3; D19; S72; D8; S79; S76; S49; W16; A29; W93; W99; W92; D82; A10; A4; D25; A90; D83; W45; W20; S68; D59; S48; A18; S0; W24; S48; W75; A39; W29; S28; W76; W78; D94; A57; A5; D51; S61; A39; W77; S70; A2; D8; S58; D51; S86; W30; A27; S62; D56; A51; D0; S58; W34; S39; A64; A68; A96; D37; S91; S16; A17; D35; A85; W88; S57; S61; A28; D12; A87; S39; A85; W22; D65; D72; A5; A78; A59; D75; D57; S66; A55; D84; D72; W87; S46; W64; D49; S46; W34; D60; S39; A30; W86; D20; W93; D25; W44; W86; A16; D4; A86; S86; S27; W7; W89; W93; S17; S39; W66; W72; D81; W93; A88; D46; S57; W45; S84; S57; D27; A11; D54; S8; W15; A50; A69; A4; D19; D69; A3; A28; D47; W18; A39; D47; W14; D77; W59; S84; A32; D56; S16; D99; A33; A51; A24; D65; W37; D98; A13; W6; D94; D28; A12; S18; W40; S23; W76; D6; S40; D26; W97; W7; W90; W75; S12; A89; S46; S36; D96; A49; A73; S53; D84; A87; D75; D48; W84; S14; W65; W79; W51; S9; S77; D51; S76; W16; W77; A90; S96; D78; S7; W71; D17; W10; W4; D96; S58; A88; S89; D41; W47; W13; S75; S85; W63; W87; S19; S80; W92; W95; W73; D43; D35; W60; S31; D72; A73; W90; S51; A55; S82; W81; S56; W83; W41; A77; S37; D63; A72; D44; W81; S26; S53; W32; A24; S90; S83; W34; D10; S53; D69; A87; W84; S32; D72; S63; D97; W27; D23; D25; D18; W86; D74; D42; A31; S1; D98; D76; S46; D67; W94; S6; S97; S40; W71; W12; D62; W57; A92; W59; W59; D15; A16; D21; S33; S45; S83; D89; W77; A93; S60; S6; W24; S93; D69; D79; S13; S8; W63; D99; S36; D35; W53; S5; S44; S19; D76; S14; A86; A86; W43; W65; D20; S19; W66; A54; A98; A17; D2; W98; W2; D77; A90; S8; S55; S67; W88; W19; S59; D9; S75; S56; W75; W54; A61; W47; S19; D67; S39; D55; S6; A89; A5; W58; W7; W88; W92; D85; S32; S32; A27; S42; D52; A55; S26; D27; W40; D76; A55; D38; W13; A71; D79; W59; A76; A33; A12; D1; D63; W63; W62; D7; W48; A84; D27; A80; D42; D27; D49; D4; D71; W90; W39; D24; W71; D16; S1; W88; W88; D25; D66; S39; S43; A99; A92; W19; W20; A90; A31; A6; A79; D4; D80; A77; D71; D36; S64;W49;W92;A84;W33;A32;A52;D97;S14;S33;D79;A14;W25;D97;D21;D31;A66;S67;S4;A59;S62;W40;S26;S65;A58;S17;A67;D48;W23;D68;S99;S97;W63;W27;D12;D83;W8;S3;W6;A88;D23;W30;S91;D58;W74;D45;W3;D19;S72;D8;S79;S76;S49;W16;A29;W93;W99;W92;D82;A10;A4;D25;A90;D83;W45;W20;S68;D59;S48;A18;S0;W24;S48;W75;A39;W29;S28;W76;W78;D94;A57;A5;D51;S61;A39;W77;S70;A2;D8;S58;D51;S86;W30;A27;S62;D56;A51;D0;S58;W34;S39;A64;A68;A96;D37;S91;S16;A17;D35;A85;W88;S57;S61;A28;D12;A87;S39;A85;W22;D65;D72;A5;A78;A59;D75;D57;S66;A55;D84;D72;W87;S46;W64;D49;S46;W34;D60;S39;A30;W86;D20;W93;D25;W44;W86;A16;D4;A86;S86;S27;W7;W89;W93;S17;S39;W66;W72;D81;W93;A88;D46;S57;W45;S84;S57;D27;A11;D54;S8;W15;A50;A69;A4;D19;D69;A3;A28;D47;W18;A39;D47;W14;D77;W59;S84;A32;D56;S16;D99;A33;A51;A24;D65;W37;D98;A13;W6;D94;D28;A12;S18;W40;S23;W76;D6;S40;D26;W97;W7;W90;W75;S12;A89;S46;S36;D96;A49;A73;S53;D84;A87;D75;D48;W84;S14;W65;W79;W51;S9;S77;D51;S76;W16;W77;A90;S96;D78;S7;W71;D17;W10;W4;D96;S58;A88;S89;D41;W47;W13;S75;S85;W63;W87;S19;S80;W92;W95;W73;D43;D35;W60;S31;D72;A73;W90;S51;A55;S82;W81;S56;W83;W41;A77;S37;D63;A72;D44;W81;S26;S53;W32;A24;S90;S83;W34;D10;S53;D69;A87;W84;S32;D72;S63;D97;W27;D23;D25;D18;W86;D74;D42;A31;S1;D98;D76;S46;D67;W94;S6;S97;S40;W71;W12;D62;W57;A92;W59;W59;D15;A16;D21;S33;S45;S83;D89;W77;A93;S60;S6;W24;S93;D69;D79;S13;S8;W63;D99;S36;D35;W53;S5;S44;S19;D76;S14;A86;A86;W43;W65;D20;S19;W66;A54;A98;A17;D2;W98;W2;D77;A90;S8;S55;S67;W88;W19;S59;D9;S75;S56;W75;W54;A61;W47;S19;D67;S39;D55;S6;A89;A5;W58;W7;W88;W92;D85;S32;S32;A27;S42;D52;A55;S26;D27;W40;D76;A55;D38;W13;A71;D79;W59;A76;A33;A12;D1;D63;W63;W62;D7;W48;A84;D27;A80;D42;D27;D49;D4;D71;W90;W39;D24;W71;D16;S1;W88;W88;D25;D66;S39;S43;A99;A92;W19;W20;A90;A31;A6;A79;D4;D80;A77;D71;D36;S64;";
	//str = "A37;S1;S72;S41;W21;W32;A45;A98;D97;D69;W57;W11;S41;S0;S24;S83;A75;W77;S32;D18;A24;D20;A65;D95;S18;W56;A84;W30;S3;S50;D64;S84;D82;A86;A36;S85;S94;W64;W62;A12;W12;S84;W29;A52;A73;W55;W71;D43;D76;D49;W19;S56;W63;W56;A68;D68;D40;A48;W5;A12;S84;A2;S44;A93;D51;D64;S4;W32;W27;W15;W70;A47;S77;S88;A25;D51;D8;A34;A71;A5;D83;S36;S72;A34;D46;S29;S5;W57;W16;S42;A23;A30;D43;S0;W62;A34;D60;D31;W89;W91;S87;A15;S15;S18;W83;S82;W87;W73;D42;A92;D48;A65;D36;A11;W50;W38;W2;A0;D65;W29;D56;S64;D31;W8;A56;A45;A56;W54;A97;D97;A90;S72;A95;A89;S78;A35;A31;W68;W42;A73;S73;A24;S28;D69;W53;S54;D80;D27;W24;S86;A17;A36;A41;A1;D19;S53;S96;A31;A52;A63;A18;S54;A35;A82;W95;D8;W48;S75;W11;S9;W60;D68;A92;A96;W32;S30;D26;W61;S0;D10;S89;W31;D4;W37;S49;D79;S56;A87;S61;A61;D96;W86;S81;D50;S91;A68;A82;A36;A16;S6;W25;D76;D94;A20;A37;D91;S58;A54;S77;S27;A35;S6;A88;A14;S72;D12;A95;W93;W1;A73;A55;A13;S55;W43;W6;D37;W19;W79;W56;S26;A36;W85;A6;W94;A54;A12;S0;A13;D18;W14;A52;W44;D83;W17;W73;A72;D56;A63;S14;A64;A84;S54;D67;A92;D46;A51;D99;W42;W2;D22;S14;D96;A79;A41;S65;D8;S41;D30;S61;D77;A52;W2;S11;W26;D47;A65;S11;D2;W98;A30;D36;W26;S41;S71;D65;D76;D28;D25;S24;S24;S58;W13;D80;A58;S64;S52;W54;S51;S40;W20;D54;W13;A7;D37;D93;A74;D24;S0;A5;W52;D86;D22;W22;S13;D56;S99;D67;S34;S5;D47;D87;D41;S15;S66;W10;D55;A63;S57;W12;S96;W28;W96;S33;D70;D75;S20;W76;D83;A34;W29;S24;A7;W11;W81;S85;W1;W71;W73;D20;A62;S2;W43;S22;D18;W35;A15;S72;W12;S12;D93;S37;S55;D33;D52;S85;W97;A88;W47;A17;A50;A40;D9;A0;D13;A16;S87;S61;D12;D8;D69;S59;S71;A7;W99;D81;W6;D48;A92;D23;D47;W37;W30;A5;S96;D28;A13;D53;D17;D9;D58;S78;S26;W17;D88;A11;W87;W94;D45;D60;W52;S71;S71;D35;D60;W60;D73;A42;D57;A25;W87;A4;W74;W70;A50;S22;S63;W15;A62;S70;A15;W58;D19;D56;A80;S95;S57;D75;A16;S8;D88;S33;S94;A43;D97;S11;D53;W55;S52;W59;S92;D39;D40;W34;W33;D52;D19;S87;A21;D94;W5;W42;A50;D27;A29;D47;W12;D5;S70;D47;S16;W52;W30;D2;A48;S1;D68;W82;A47;S84;S56;S60;S14;W64;W8;A41;W8;S4;D80;A49;D72; ";
	str = "A1A;";
	int x = 0;
	int y = 0;
	size_t iPos = str.find_first_of(';');
	while (iPos != string::npos)
	{
		string sub = str.substr(0, iPos);
		str = str.substr(iPos + 1, str.size());
		iPos = str.find_first_of(';');
		int tmp = 0;
		if (sub.length() > 3 || !CheckInput(sub))
		{
			continue;
		}
		if (sub.find('A') != string::npos)
		{
			sub = sub.substr(1, sub.size() - 1);
			if (!sub.empty())
			{
				tmp = stoi(sub);
				x = x - tmp;
			}
		}
		else if (sub.find('D') != string::npos)
		{
			sub = sub.substr(1, sub.size() - 1);
			if (!sub.empty())
			{
				tmp = stoi(sub);
				x = x + tmp;
			}
		}
		else if (sub.find('W') != string::npos)
		{
			sub = sub.substr(1, sub.size() - 1);
			if (!sub.empty())
			{
				tmp = stoi(sub);
				y = y + tmp;
			}
		}
		else if (sub.find('S') != string::npos)
		{
			sub = sub.substr(1, sub.size() - 1);
			if (!sub.empty())
			{
				tmp = stoi(sub);
				y = y - tmp;
			}
		}

	}
	cout << x << "," << y;
}

//识别有效的IP地址和掩码地址并进行分类统计
/**
*    ip地址合法校验
*  1		25[0-5]                     	250-255
*  2		2[0-4]\\d                    	200-249
*  3		[1]{1}\\d{1}\\d{1}   		100-199
*  4		[1-9]{1}\\d{1}			10-99
*  5		\\d{1}				0-9
*  6		($|(?!\\.$)\\.)               	结束 或者 不以.结束的加上.
*  7		(?!^0{1,3}(\\.0{1,3}){3}$)     	排除 0.0.0.0 		(?!^0{1,3}(\\.0{1,3}){3}$)^((25[0-5]|2[0-4]\\d|[1]{1}\\d{1}\\d{1}|[1-9]{1}\\d{1}|\\d{1})($|(?!\\.$)\\.)){4}$
*  8		(?!^255(\\.255){3}$)      	排除 255.255.255.255	(?!^255(\\.255){3}$)^((25[0-5]|2[0-4]\\d|[1]{1}\\d{1}\\d{1}|[1-9]{1}\\d{1}|\\d{1})($|(?!\\.$)\\.)){4}$
*/
char checkIp(string& strIp, string& strMask)
{
	//错误Ip
	string::size_type iIpPos = strIp.find_first_of(".");
	string tmpIp = strIp;
	vector<int> vecIpStr;
	int indexIp = 0;
	while (iIpPos != string::npos)
	{
		string sbb = tmpIp.substr(0, iIpPos);
		tmpIp = tmpIp.substr(iIpPos + 1, tmpIp.length());
		iIpPos = tmpIp.find_first_of(".");
		indexIp++;
		if (indexIp > 3 || sbb.empty() || stoi(sbb) > 255 || stoi(sbb) < 0)
		{
			return 'I';
		}
		vecIpStr.push_back(stoi(sbb));
	}
	if (stoi(tmpIp) > 255 || stoi(tmpIp) < 0)
	{
		return 'I';
	}
	vecIpStr.push_back(stoi(tmpIp));
	if (vecIpStr.size() != 4)
	{
		return 'I';
	}

	//错误Mask 不能去0.0.0.0 or 255.255.255.255
	size_t iPos = strMask.find_first_of(".");
	string tmp = strMask;
	vector<int> vecStr;
	int index = 0;
	while (iPos != string::npos)
	{
		string sbb = tmp.substr(0, iPos);
		tmp = tmp.substr(iPos + 1, tmp.length());
		iPos = tmp.find_first_of(".");
		index++;
		if (index > 3 || sbb.empty() || stoi(sbb) > 255 || stoi(sbb) < 0)
		{
			return 'Y';
		}
		vecStr.push_back(stoi(sbb));
	}
	if (stoi(tmp) > 255 || stoi(tmp) < 0)
	{
		return 'Y';
	}
	vecStr.push_back(stoi(tmp));
	if (vecStr.size() != 4)
	{
		return 'Y';
	}
	if (vecStr[0] == 255)
	{
		if (vecStr[1] == 255)
		{
			if (vecStr[2] == 255)
			{
				if (vecStr[3] != 254 && vecStr[3] != 252 && vecStr[3] != 248
					&& vecStr[3] != 240 && vecStr[3] != 224 && vecStr[3] != 192 && vecStr[3] != 128 && vecStr[3] != 0)
				{
					return 'Y';
				}
			}
			else if (vecStr[2] != 255 && vecStr[2] != 254 && vecStr[2] != 252 && vecStr[2] != 248
				&& vecStr[2] != 240 && vecStr[2] != 224 && vecStr[2] != 192 && vecStr[2] != 128 && vecStr[2] != 0)
			{
				return 'Y';
			}
			else if (vecStr[3] != 0)
			{
				return 'Y';
			}
		}
		else if (vecStr[1] != 255 && vecStr[1] != 254 && vecStr[1] != 252 && vecStr[1] != 248
			&& vecStr[1] != 240 && vecStr[1] != 224 && vecStr[1] != 192 && vecStr[1] != 128 && vecStr[1] != 0)
		{
			return 'Y';
		}
		else if (vecStr[2] != 0 || vecStr[3] != 0)
		{
			return 'Y';
		}
	}
	else if (vecStr[0] != 255 && vecStr[0] != 254 && vecStr[0] != 252 && vecStr[0] != 248
		|| vecStr[0] != 240 && vecStr[0] != 224 && vecStr[0] != 192 && vecStr[0] != 128)
	{
		return 'Y';
	}
	else if (vecStr[1] != 0 || vecStr[2] != 0 || vecStr[3] != 0)
	{
		return 'Y';
	}

	//判断私有
	if (vecIpStr[0] == 10)
	{
		return 'K';
	}
	else if (vecIpStr[0] == 172 && 16 <= vecIpStr[1] && vecIpStr[1] <= 31)
	{
		return 'G';
	}
	else if (vecIpStr[0] == 192 && vecIpStr[1] == 168)
	{
		return 'H';
	}


	//判断A
	if (1 <= vecIpStr[0] && vecIpStr[0] <= 126)
	{
		return 'A';
	}

	//判断B
	if (128 <= vecIpStr[0] && vecIpStr[0] <= 191)
	{
		return 'B';
	}

	//判断C
	if (192 <= vecIpStr[0] && vecIpStr[0] <= 223)
	{
		return 'C';
	}

	//判断D
	if (224 <= vecIpStr[0] && vecIpStr[0] <= 239)
	{
		return 'D';
	}

	//判断E
	if (240 <= vecIpStr[0] && vecIpStr[0] <= 255)
	{
		return 'E';
	}

	return ' ';
}
void CalcValidIpInfo()
{
	string str;
	int aNum = 0;
	int bNum = 0;
	int cNum = 0;
	int dNum = 0;
	int eNum = 0;
	int errIp = 0; //I错误掩码 Ip错误
	int errYan = 0; //私有IP
	str = "206.76.161.30~255.0.0.0 159.70.213.68~255.0.0.0 181.131.118.0~255.255.255.0 80.164.71.44~255.255.255.255 12.208.232.42~255.255.0.0 150.24.121.174~255.0.102.0 131.221.165.68~255.0.0.0 160.126.59.101~255.0.75.0 236.239.205.137~255.255.0.0 89.124.33.74~255.0.0.159 233.174.151.221~255.255.0.0 218.140.130.246~255.255.255.255 13.13.219.143~255.0.0.0 232.95.224.67~255.255.255.255 2.108.39.131~255.0.0.0 161.217.200.192~255.0.0.0 123.170.177.162~255.0.0.0 239.64.91.24~255.0.0.0 241.199.108.210~255.255.255.0 117.0.169.232~255.255.255.255 122.49.165.60~255.255.242.255 71.148.13.251~255.0.0.32 199.22.216.173~255.254.27.0 58.24.55.101~255.132.255.0 68.128.113.136~255.0.0.0 197.234.247.46~255.255.255.0 79.22.71.93~255.255.0.0 250.217.239.76~255.0.8.0 153.96.7.235~255.255.0.0 237.173.48.19~255.0.0.0 140.48.84.23~255.255.255.0 107.222.50.243~255.0.0.0 189.224.126.176~255.255.255.0 111.9.155.102~255.0.0.0 117.4.142.205~255.255.255.255 59.0.177.100~255.255.0.0 60.70.81.248~255.255.255.255 72.85.2.100~255.255.125.0 74.15.130.23~255.0.0.0 37.51.172.97~255.255.255.149 51.58.149.175~255.0.0.0 76.106.99.1~255.255.0.0 198.102.96.87~255.255.0.0 97.170.76.38~255.0.214.0 42.115.213.173~255.255.0.0 95.115.180.128~255.255.0.0 192.240.88.125~255.0.0.47 148.36.118.39~255.0.0.0 237.211.17.109~255.255.255.255 161.230.133.200~255.0.0.0 163.139.243.139~255.0.0.0 249.174.134.36~255.255.255.0 148.64.179.63~255.0.0.0 59.156.109.132~255.0.0.0 42.50.113.7~255.0.0.0 225.95.158.160~255.0.0.0 133.17.112.129~255.0.152.0 212.183.133.49~255.255.0.0 183.12.213.169~255.255.255.255 7.144.20.194~255.255.0.0 106.46.24.252~255.255.255.255 51.181.112.115~255.0.0.0 47.243.149.186~255.255.255.0 174.11.159.234~255.0.0.0 8.83.231.207~255.0.0.0 212.211.51.229~255.0.0.0 6.13.59.212~255.255.119.0 131.151.60.159~255.0.0.0 47.21.57.12~255.0.0.0 136.242.238.159~255.0.0.0 249.200.157.157~255.255.255.0 150.2.21.239~255.0.0.0 26.100.58.90~255.226.0.0 7.167.169.193~255.255.255.0 48.49.16.45~255.132.0.0 67.244.5.142~255.0.189.0 239.170.232.59~255.0.0.0 223.138.166.166~255.0.0.103 199.65.124.179~255.255.0.0 231.121.177.81~255.255.186.193 30.247.220.230~255.255.255.0 227.72.33.192~255.255.255.255 126.189.96.104~255.255.167.255 ";
	while (cin >> str)
	{
		size_t iPos = str.find_first_of("~");
		string subBeg = str.substr(0, iPos);
		string subEnd = str.substr(iPos + 1, str.length());

		char ret = checkIp(subBeg, subEnd);
		switch (ret)
		{
		case 'A':
			aNum++;
			break;
		case 'B':
			bNum++;
			break;
		case 'C':
			cNum++;
			break;
		case 'D':
			dNum++;
			break;
		case 'E':
			eNum++;
			break;
		case 'I':
			errIp++;
			break;
		case 'Y':
			errIp++;
			break;
		case 'K':
			aNum++;
			errYan++;
			break;
		case 'G':
			bNum++;
			errYan++;
			break;
		case 'H':
			cNum++;
			errYan++;
			break;
		default:
			break;
		}
	}

	cout << aNum << " " \
		<< bNum << " "\
		<< cNum << " "\
		<< dNum << " "\
		<< eNum << " "\
		<< errIp << " "\
		<< errYan;
}

//密码判断
void CheckSecret()
{
	string str;
	//str = "021Abc9Abc1";
	//str = "$85 * 550 & -#$30";
	//str = "))20Uq%0";
	//str = "5n + w!b7$1!v + eG27pl$6e200ClB18*--286 ^ *2!8O0";
	while (getline(cin, str))
	{
		//长度
		if (str.length() <= 8)
		{
			cout << "NG" << endl;
			continue;
		}

		//包含类型
		bool Big = false;
		bool Small = false;
		bool Num = false;
		bool Other = false;
		int bIndexNUm = 0;
		for (size_t i = 0; i < str.length(); i++)
		{
			if (isalnum(str[i]) && !Num)
			{
				Num = true;
				bIndexNUm++;
			}
			else if (islower(str[i]) && !Small)
			{
				Small = true;
				bIndexNUm++;
			}
			else if (isupper(str[i]) && !Big)
			{
				Big = true;
				bIndexNUm++;
			}
			else if (!isalnum(str[i]) && !islower(str[i]) && !isupper(str[i]) && !Other)
			{
				Other = true;
				bIndexNUm++;
			}
		}
		if (bIndexNUm < 3)
		{
			cout << "NG" << endl;
			continue;
		}

		//重复串 至少3个
		bool flag = false;
		for (size_t i = 0; i < str.length() - 2; i++)
		{
			string leftStr = str.substr(i + 3, str.length());
			string dstStr = str.substr(i, 3);
			size_t iPos = leftStr.find(dstStr);
			if (iPos != string::npos)
			{
				flag = true;
			}
		}
		if (flag)
		{
			cout << "NG" << endl;
			continue;
		}
		cout << "OK" << endl;
	}
}

//945. 使数组唯一的最小增量
//给定整数数组 A，每次 move 操作将会选择任意 A[i]，并将其递增 1。
//返回使 A 中的每个值都是唯一的最少操作次数。
//输入：[1, 2, 2]
//输出：1
//解释：经过一次 move 操作，数组将变为[1, 2, 3]。
//输入：[3, 2, 1, 2, 1, 7]
//输出：6
//解释：经过 6 次 move 操作，数组将变为[3, 4, 1, 2, 5, 7]。
int minIncrementForUnique(vector<int>& A) {
	int mapUnique[80000] = { 0 };
	for (auto it : A) mapUnique[it]++;
	int nRet = 0;
	int nToken = 0;
	for (int it = 0; it < 80000; ++it)
	{
		if (mapUnique[it]>= 2)
		{
			nToken += mapUnique[it] - 1;
			nRet -= it * (mapUnique[it] - 1);
		}
		else if (nToken > 0 && mapUnique[it] == 0)
		{
			nToken--;
			nRet += it;
		}
	}
	return nRet;
}
//解法2 eg 5 5 5 6
int minIncrementForUnique2(vector<int>& A) {
	sort(A.begin(), A.end());
	int nRet = 0;
	for (int it = 1; it < A.size(); ++it)
	{
		if (A[it] <= A[it - 1])
		{
			nRet += A[it - 1] - A[it] + 1;
			A[it] = A[it - 1] + 1;
		}
	}

	return nRet;
}
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}	
};

//110. 平衡二叉树
//给定一个二叉树，判断它是否是高度平衡的二叉树。
//本题中，一棵高度平衡二叉树定义为：
//一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过1。
int DFSNums(TreeNode* root)
{
	if (NULL == root) return 0;

	int nDepthLeft = DFSNums(root->left);
	int nDepthRight = DFSNums(root->right);


	return max(nDepthLeft, nDepthRight) + 1;
}

bool isBalanced(TreeNode* root) {
	
	int nLeft = DFSNums(root->left);
	int nRight = DFSNums(root->right);

	return abs(nLeft-nRight) <= 1 && isBalanced(root->left) && isBalanced(root->right);
}

//111. 二叉树的最小深度 easy
//给定一个二叉树，找出其最小深度。
//最小深度是从根节点到最近叶子节点的最短路径上的节点数量。
//说明 : 叶子节点是指没有子节点的节点。
int minDepth(TreeNode* root) {
	if (NULL == root) return 0;

	queue<TreeNode*> queTree;
	queTree.push(root);
	int nDepth = 1;
	int nTimes = 1;
	while (!queTree.empty())
	{
		while (nTimes > 0)
		{
			TreeNode* tmp = queTree.front();
			queTree.pop();

			if(NULL != tmp->left) queTree.push(tmp->left);
			if(NULL != tmp->right) queTree.push(tmp->right);
			if (NULL == tmp->left && NULL == tmp->right) return nDepth;
			nTimes--;
		}

		nTimes = queTree.size();
		nDepth++;
	}

	return nDepth;
}
//利用递归实现最小深度
int minDepthDFS(TreeNode* root)
{
	if (NULL == root) return 0;
	if (NULL == root->left || NULL == root->right) return 1;

	int nMin = INT_MAX;
	if(NULL != root->left) nMin = min(nMin,minDepthDFS(root->left));
	if (NULL != root->right) nMin = min(nMin, minDepthDFS(root->right));

	return nMin + 1;
}

//46. 全排列 mid
//给定一个 没有重复 数字的序列，返回其所有可能的全排列。
void vecPermuteDFS(vector<int>& rem, vector<int>& cur, vector<vector<int>>& vecVecRet)
{
	if (rem.empty())
	{
		vecVecRet.push_back(cur);
		return;
	}

	for (int it = 0 ; it < rem.size(); ++it)
	{
		cur.push_back(rem[it]);
		vector<int> vecTmp = rem;
		vecTmp.erase(vecTmp.begin() + it);
		vecPermuteDFS(vecTmp, cur, vecVecRet);
		cur.pop_back();
	}
}
vector<vector<int>> permute(vector<int>& nums) {
	vector<vector<int>> vecVecRet;
	vector<int> vecTmp;
	vecPermuteDFS(nums, vecTmp, vecVecRet);
	return vecVecRet;
}

//120. 三角形最小路径和 mid
//给定一个三角形，找出自顶向下的最小路径和。每一步只能移动到下一行中相邻的结点上。
int minimumTotal(vector<vector<int>>& triangle) {
	if (triangle.empty() || triangle[0].empty()) return 0;

	queue<int> quePathTotal;
	queue<int> queLastIndex;
	queLastIndex.push(0);
	quePathTotal.push(triangle[0][0]);
	int nMin = triangle[0][0];
	for (int i = 1; i < triangle.size(); i++)  //行
	{
		int nTimes = quePathTotal.size();
		nMin = INT_MAX;
		while(nTimes > 0)
		{
			int nTmp = quePathTotal.front();
			quePathTotal.pop();
			int nIndex = queLastIndex.front();
			queLastIndex.pop();
			//每个值有两种可能
			int nCur = nTmp + triangle[i][nIndex];
			quePathTotal.push(nCur);
			queLastIndex.push(nIndex);
			nMin = min(nMin, nCur);
			nCur = nTmp + triangle[i][nIndex + 1];
			quePathTotal.push(nCur);
			queLastIndex.push(nIndex + 1);
			nMin = min(nMin, nCur);
			nTimes--;
		}
	}

	return nMin;
}

//重载 + - 运算
//string operator+ (const string& str)
//{
//	string strRet(str);
//	strRet.append("hello.");
//	return str;
//}
//
//string operator-(const string& str)
//{
//	string strRet(str);
//	strRet.append("hello.");
//	return str;
//}

//98. 验证二叉搜索树
//给定一个二叉树，判断其是否是一个有效的二叉搜索树。
//假设一个二叉搜索树具有如下特征：
//节点的左子树只包含小于当前节点的数。
//节点的右子树只包含大于当前节点的数。
//所有左子树和右子树自身必须也是二叉搜索树。
bool isValidBST(TreeNode* root) {

	stack<TreeNode*> stackNode;
	long long nCurNum = (long long)INT_MIN - 1;
	while (!stackNode.empty() || root != NULL)
	{
		while (root != NULL)
		{
			stackNode.push(root);
			root = root->left;
		}

		root = stackNode.top();
		stackNode.pop();
		if (root->val <= nCurNum) return false;

		nCurNum = root->val;
		root = root->right;
	}
	return true;
}

//221. 最大正方形
//在一个由 0 和 1 组成的二维矩阵内，找到只包含 1 的最大正方形，并返回其面积。
//动态规划
int maximalSquare(vector<vector<char>>& matrix) {
	int nMaxSide = 0;
	if (matrix.empty() || matrix[0].empty()) return nMaxSide;

	int nRow = matrix.size();
	int nCol = matrix[0].size();

	vector<vector<int>> vecVecDpInt(nRow, vector<int>(nCol, 0));
	for (int i = 0; i < nRow; ++i)
	{
		for (int j = 0; j < nCol; ++j)
		{
			if (matrix[i][j] == '1')
			{
				if (i == 0 || j == 0) vecVecDpInt[i][j] = 1;
				else vecVecDpInt[i][j] = min(min(vecVecDpInt[i - 1][j], vecVecDpInt[i - 1][j - 1]), vecVecDpInt[i][j - 1]) + 1;

				nMaxSide = max(nMaxSide, vecVecDpInt[i][j]);
			}
		}
	}
	return nMaxSide;
}
int main()
{
	vector<vector<int>>  vecVecInput1 = {{2}, {3,4}, {6,5,7}, {4,1,8,3}};
	int nRet1 = minimumTotal(vecVecInput1);

	system("pause");
	return 0;
}