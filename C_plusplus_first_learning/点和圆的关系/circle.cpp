
#include"circle.h"
using namespace std;

void circle::setm_r(int r) {
	m_r = r;
}
int circle::getm_r() {
	return m_r;
}
void circle::setcenter(point center) {
	m_center = center;
}
point circle::getcenter() {
	return m_center;
}

int m_r;
point m_center;