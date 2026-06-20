#include<iostream>
using namespace std;
class cube {
public:
	/*int setnum(int l, int w, int h) {
		m_l = l;
		m_w = w;
		m_h = h;
		return ;
	}*/
	int setm_l() {
	
		return m_l;
	}
	int setm_w() {
		
		return m_w;
	}
	int setm_h() {
		
		return m_h;
	}
	int gets() {
		return 2 * m_l * m_w + 2 * m_l * m_h + 2 * m_w * m_h;
	}
	int getv() {
		return m_l * m_w * m_h;
	}
private:
	int m_l;
	int m_w;
	int m_h;
};
//利用全局函数判断两个立方体是否相等
bool issame(cube &c1, cube &c2) {
	if (c1.setm_h() == c2.setm_h() && c1.setm_l() == c2.setm_l() && c1.setm_w() == c2.setm_w()) {
		return true;
	}
}
int main() {
	cube c1;
	cube c2;
	/*c1.setnum(10, 20, 30);
	c2.setnum(11, 21, 31);*/
	c1.setm_h(10);
	c1.setm_l(10);
	c1.setm_w(10);
	c2.setm_h(10);
	c2.setm_l(10);
	c2.setm_w(10);
	cout << c1.gets() << endl;
	cout << c1.getv() << endl;
	cout << issame(c1,c2) << endl;
}