#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string> 
#include <functional>
#include <time.h>
using namespace std;

template <class _Operation1, class _Operation2>
class unary_compose
  : public std::unary_function<typename _Operation2::argument_type,
                               typename _Operation1::result_type> 
{
protected:
  _Operation1 __op1;
  _Operation2 __op2;
public:
  unary_compose(const _Operation1& __x, const _Operation2& __y) 
    : __op1(__x), __op2(__y) {}
  typename _Operation1::result_type
  operator()(const typename _Operation2::argument_type& __x) const {
    return __op1(__op2(__x));
  }
};

template <class _Operation1, class _Operation2>
inline unary_compose<_Operation1,_Operation2> 
compose1(const _Operation1& __op1, const _Operation2& __op2)
{
  return unary_compose<_Operation1,_Operation2>(__op1, __op2);
}



class IntRandomGen
{
public:
	int operator()() const
	{
		return rand() % 100;
	}
};
class StringRandomGen
{
public:
	string operator()() const
	{
		int n = (rand() % 11) + 5;
		string s = "";
		for(int i = 0; i < n; i++)
		{
			s += 'a' + rand() % 26;
		}
		return s;
	}
};
class SortBylength
{
public:
	bool operator()(string a, string b) const
	{
		return a.length() < b.length();
	}
};
struct Count : public unary_function<int, void>
{
	int oddCnt;
	int evenCnt;
	Count() : oddCnt(0), evenCnt(0) {};
	void operator()(int a) 
	{
		if(a % 2 == 1)
			oddCnt++; 
		else
			evenCnt++;
	}
};

template <typename BidirectionalIterator>
void my_reverse(BidirectionalIterator first, BidirectionalIterator last) 
{
	last--;
	while(distance(first,last) > 0)
	{
		swap(*first,*last);
		first++;
		last--;
	}
}

void practice1();
void practice2();
void practice3();
void practice4();
void practice5(int size);
int main()
{	
	srand(time(NULL));
	
	practice1();
	practice2();
	practice3();
	practice4();
	practice5(11);
	getchar();
	return 0;
}
void practice1()
{
	vector<int> a(100);
	generate(a.begin(), a.end(), IntRandomGen());
	copy(a.begin(),a.end(),ostream_iterator<int>(cout, ", "));
	cout << endl;
}
void practice2()
{
	vector<string> s(100);
	generate(s.begin(), s.end(), StringRandomGen());
	sort(s.begin(),s.end());
	cout << endl;
	copy(s.begin(),s.end(),ostream_iterator<string>(cout, ", "));	
	sort(s.begin(),s.end(),SortBylength());
	cout << endl;
	copy(s.begin(),s.end(),ostream_iterator<string>(cout, ", "));
	cout << endl;
}
void practice3()
{
	vector<int> a(100);
	generate(a.begin(), a.end(), IntRandomGen());
	Count count = for_each(a.begin(),a.end(),Count());
	cout << "# of odd : " << count.oddCnt << ", # of even : "  << count.evenCnt << endl;
}
void practice4()
{
	vector<int> v;
    v.push_back(1);
    v.push_back(4);
    v.push_back(2);
    v.push_back(8);
    v.push_back(5);
    v.push_back(7);

    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
	
    vector<int>::iterator new_end = 
		remove_if(v.begin(), v.end(), 
			compose1(bind2nd(equal_to<int>(),0),bind2nd(modulus<int>(), 2)));
	
	//v.end() -> new_end
    copy(v.begin(), new_end, ostream_iterator<int>(cout, " "));
    cout << endl;
      
}
void practice5(int size)
{
	vector<int> a(size);
	generate(a.begin(),a.end(),IntRandomGen());
	copy(a.begin(),a.end(),ostream_iterator<int>(cout, ", "));
	cout << endl;
	my_reverse(a.begin(),a.end());
	copy(a.begin(),a.end(),ostream_iterator<int>(cout, ", "));
	cout << endl;
}