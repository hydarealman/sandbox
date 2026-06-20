#include<stdio.h>
float calculate(float up, float down, float high) {
	float area = (up + down) * high / 2;
	return area;
}