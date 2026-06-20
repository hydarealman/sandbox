#include"isincircle.h"
void isincircle(circle& c, point& p) {
	int distance =//有bug找不到
		(c.getcenter().getm_x() - p.getm_x()) * (c.getcenter().getm_x() - p.getm_x()) + (c.getcenter().getm_y() - p.getm_y()) * (c.getcenter().getm_y() - p.getm_y());
	int rdistance = c.getm_r() * c.getm_r();
	if (distance = rdistance) {
		printf("点在圆上");
	}
	else if (distance > rdistance) {
		printf("点在圆外");
	}
	else
		printf("点在圆内");
}