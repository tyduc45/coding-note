#include <windows.h>
#include <clocale>
#include <algorithm>
#include <climits>
#include <random>
#include <stdio.h>
#include <stack>
#include <string>
#include <vector>
using namespace std;

// ==================== 被测代码（原样，未做任何修改） ====================
int deep(stack<int> stack)
{
	if(stack.empty())
	{
		return 0;
	}
	else
	{
		int a = stack.top(); stack.pop();
		int d = deep(stack);
		stack.push(a);
		d += 1;
		return d;
	}
}
int find_max(stack<int> &stack, int deep)
{
	if(deep == 0)
	{
		return INT_MIN;
	}
	else
	{
		int a = stack.top(); stack.pop();
		int max_num = find_max(stack , deep - 1);
		int max_ = max(a , max_num);
		stack.push(a);
		return max_;
	}
}
int times(stack<int> stack , int deep , int max)
{
	if(deep == 0)
	{
		return 0;
	}
	else
	{
		int a = stack.top(); stack.pop();
		int rest_times = times(stack , deep - 1, max);
		int times = rest_times + (a == max)? 1 : 0;
		stack.push(a);
		return times;
	}
}
void down(stack<int> &stack , int deep ,int max, int k)
{
	if(deep == 0)
	{
		for(int i = 0 ; i < k;i++)
		{
			stack.push(max);
		}
	}
	else
	{
		int a = stack.top(); stack.pop();
		down(stack, deep - 1 , max, k);
		if(a != max)
		{
			stack.push(a);
		}
	}
}
void sortStack(stack<int> &stack)
{
	int d = deep(stack);
	while(d > 0)
	{
		int max = find_max(stack,d);
		int k = times(stack , d ,max);
		down(stack , d , max , k);
		d -= k;
	}
}
// ==================== 测试框架 ====================
static int g_pass = 0, g_fail = 0;
static string g_section;

static void section(const string& s){ g_section = s; printf("\n=== %s ===\n", s.c_str()); }
static void check(bool ok, const string& name, const string& detail = "")
{
	if(ok){ ++g_pass; printf("  [PASS] %s\n", name.c_str()); }
	else  { ++g_fail; printf("  [FAIL] %s%s%s\n", name.c_str(),
	        detail.empty()?"":"  ->  ", detail.c_str()); }
}

// vector 的下标 0 = 栈底，末尾 = 栈顶
static stack<int> mk(const vector<int>& v){ stack<int> s; for(int x : v) s.push(x); return s; }
static vector<int> vec(stack<int> s){
	vector<int> r; while(!s.empty()){ r.push_back(s.top()); s.pop(); }
	reverse(r.begin(), r.end()); return r;
}
static string str(const vector<int>& v){
	string r = "[";
	for(size_t i = 0; i < v.size(); ++i){ if(i) r += ","; r += to_string(v[i]); }
	return r + "]";
}
static string cmpstr(const vector<int>& got, const vector<int>& want){
	return "got=" + str(got) + " want=" + str(want);
}

// ==================== 参考实现（用来算期望值） ====================
static int ref_max(const vector<int>& v, int d){
	if(d == 0) return INT_MIN;
	return *max_element(v.end() - d, v.end());
}
static int ref_times(const vector<int>& v, int d, int m){
	return (int)count(v.end() - d, v.end(), m);
}
// down 的期望：底部 v[0..n-d-1] 不动；窗口重排为 [max × k] + [窗口内非 max 元素，保持原序]
static vector<int> ref_down(const vector<int>& v, int d, int m, int k){
	vector<int> r(v.begin(), v.end() - d);
	for(int i = 0; i < k; ++i) r.push_back(m);
	for(auto it = v.end() - d; it != v.end(); ++it) if(*it != m) r.push_back(*it);
	return r;
}

// ==================== 各函数的单元测试 ====================
static void test_deep(){
	section("deep()  — 返回栈的元素个数");
	vector<vector<int>> cases = { {}, {7}, {1,2,3}, {5,5,5,5}, {-1,0,INT_MIN,INT_MAX} };
	for(auto& v : cases){
		stack<int> s = mk(v);
		int d = deep(s);
		check(d == (int)v.size(), "size " + str(v),
		      "got=" + to_string(d) + " want=" + to_string(v.size()));
		// deep 是值传参，调用方的栈必须一个字节都没变
		check(vec(s) == v, "调用方栈未被改动 " + str(v), cmpstr(vec(s), v));
	}
}

static void test_find_max(){
	section("find_max()  — 栈顶往下 deep 层内的最大值 + 后置条件(栈还原)");
	vector<vector<int>> cases = {
		{1,2,3}, {3,2,1}, {2,3,1}, {5,5,5}, {-7,-3,-9},
		{INT_MIN, INT_MIN}, {INT_MAX, 0, INT_MIN}, {4,1,4,1,4}
	};
	for(auto& v : cases){
		for(int d = 0; d <= (int)v.size(); ++d){
			stack<int> s = mk(v);
			int got = find_max(s, d);
			int want = ref_max(v, d);
			check(got == want, "max " + str(v) + " deep=" + to_string(d),
			      "got=" + to_string(got) + " want=" + to_string(want));
			check(vec(s) == v, "栈已还原 " + str(v) + " deep=" + to_string(d),
			      cmpstr(vec(s), v));
		}
	}
	// 单独盯一下 INT_MIN：base case 用 INT_MIN 当哨兵，真实最大值就是 INT_MIN 时会不会出问题
	{
		stack<int> s = mk({INT_MIN, INT_MIN, INT_MIN});
		check(find_max(s, 3) == INT_MIN, "哨兵值与真实最大值撞车时仍正确");
	}
}

static void test_times(){
	section("times()  — 最大值在 deep 层内出现的次数");
	vector<pair<vector<int>, int>> cases = {
		{{1,2,3}, 3}, {{3,3,1}, 3}, {{5,5,5}, 3}, {{1,3,3,2}, 4},
		{{9}, 1}, {{2,2}, 2}, {{7,1,7,1,7}, 5}, {{4,4,2,2}, 2}
	};
	for(auto& [v, d] : cases){
		int m = ref_max(v, d);
		stack<int> s = mk(v);
		int got = times(s, d, m);
		int want = ref_times(v, d, m);
		check(got == want,
		      "count " + str(v) + " deep=" + to_string(d) + " max=" + to_string(m),
		      "got=" + to_string(got) + " want=" + to_string(want));
		check(vec(s) == v, "调用方栈未被改动 " + str(v), cmpstr(vec(s), v));
	}
}

static void test_down(){
	section("down()  — 把 deep 层内的 k 个 max 沉到窗口底部");
	vector<pair<vector<int>, int>> cases = {
		{{1,2,3}, 3}, {{3,1,2}, 3}, {{1,3,2,3}, 4}, {{5,5,5}, 3},
		{{9,1,2,3}, 3}, {{2,2,1,1}, 4}, {{1}, 1}
	};
	for(auto& [v, d] : cases){
		int m = ref_max(v, d);
		int k = ref_times(v, d, m);          // 用参考值喂进去，隔离 times 的影响
		stack<int> s = mk(v);
		down(s, d, m, k);
		vector<int> got = vec(s), want = ref_down(v, d, m, k);
		check(got == want,
		      "down " + str(v) + " deep=" + to_string(d) +
		      " max=" + to_string(m) + " k=" + to_string(k), cmpstr(got, want));
		check(got.size() == v.size(), "元素总数守恒 " + str(v),
		      "got=" + to_string(got.size()) + " want=" + to_string(v.size()));
	}
}

// ==================== 端到端测试 ====================
// 约定：最大值沉底，所以 bottom->top 应为降序（栈顶最小）
static bool run_sort(const vector<int>& v, vector<int>& got, vector<int>& want){
	stack<int> s = mk(v);
	sortStack(s);
	got = vec(s);
	want = v; sort(want.begin(), want.end(), greater<int>());
	return got == want;
}

static void test_sort_fixed(){
	section("sortStack()  — 固定用例");
	struct C { vector<int> v; const char* name; };
	vector<C> cases = {
		{{},                     "空栈"},
		{{42},                   "单元素"},
		{{1,2,3,4,5},            "已有序(栈顶最大)"},
		{{5,4,3,2,1},            "逆序(栈顶最小)"},
		{{3,1,4,1,5,9,2,6},      "一般乱序"},
		{{7,7,7,7},              "全部相同"},           // <-- 重复元素
		{{2,1,2,1,2},            "最大值出现多次"},      // <-- 重复元素
		{{1,1,2,2,3,3},          "每个值都成对"},        // <-- 重复元素
		{{-5,-1,-9,-3},          "全负数"},
		{{0,-1,1,0},             "含 0 与正负混合"},
		{{INT_MIN, 0, INT_MAX},  "极值"},
		{{INT_MIN, INT_MIN},     "全部 INT_MIN"},
	};
	for(auto& c : cases){
		vector<int> got, want;
		bool ok = run_sort(c.v, got, want);
		check(ok, string(c.name) + " " + str(c.v), cmpstr(got, want));
	}
}

static void test_sort_random(){
	section("sortStack()  — 随机对拍");
	mt19937 rng(20260814);
	int fails = 0;
	// 分两档：值域大 => 基本无重复；值域小 => 大量重复
	for(int range : {1000, 3}){
		for(int iter = 0; iter < 300; ++iter){
			int n = (int)(rng() % 12);
			vector<int> v(n);
			for(int& x : v) x = (int)(rng() % (2 * range)) - range;
			vector<int> got, want;
			if(!run_sort(v, got, want)){
				if(fails < 5)   // 只打印前几个反例，避免刷屏
					printf("  [FAIL] range=%d  in=%s  %s\n",
					       range, str(v).c_str(), cmpstr(got, want).c_str());
				++fails; ++g_fail;
			} else ++g_pass;
		}
		printf("  -- 值域 ±%d 完成，累计失败 %d 例\n", range, fails);
	}
}

int main(){
	SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, ".UTF-8");
	
	test_deep();
	test_find_max();
	test_times();
	test_down();
	test_sort_fixed();
	test_sort_random();
	printf("\n========================================\n");
	printf("PASS: %d    FAIL: %d\n", g_pass, g_fail);
	printf("========================================\n");
	return g_fail ? 1 : 0;
}