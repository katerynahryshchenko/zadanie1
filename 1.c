#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NULA_VNOTURNYCH_DOTYCNIC 0
#define JEDNA_VNOTURNA_DOTYCNICA 1
#define DVE_VNOTURNE_DOTYCNICE 2

typedef struct{
	float x;
	float y;
}POINT;

typedef struct{
	POINT p;
	float r;
}CIRCLE;

typedef struct{
	float a;
	float b;
	float c;
}LINE;


void init (CIRCLE *c1, CIRCLE *c2) {
	float x1, x2, y1, y2, r1, r2;
	
	puts("Zadajte x-ovu a y-ovu suradnice stredu a priemer 1 kruznice");
	scanf("%f %f %f", &x1, &y1, &r1);
	puts("Zadajte x-ovu a y-ovu suradnice stredu a priemer 2 kruznice");
	scanf("%f %f %f", &x2, &y2, &r2);
	
	c1->p.x = x1;
	c1->p.y = y1;
	c1->r = r1;
	c2->p.x = x2;
	c2->p.y = y2;
	c2->r = r2;
}

char circ_circ_inner_tangents(CIRCLE *c1, CIRCLE *c2, LINE *t1, LINE *t2) {
	float d, r, vx, vy, bodx, body, q, bod1x, bod2x, bod3x, bod4x, q2, bod1y, bod2y, bod3y, bod4y, qsin, qcos, q2sin, q2cos;
	
	d = sqrt((c1->p.x - c2->p.x) * (c1->p.x - c2->p.x) + (c1->p.y - c2->p.y) * (c1->p.y - c2->p.y));
	r = c1->r + c2->r;
	
	if (d < r) {
		return NULA_VNOTURNYCH_DOTYCNIC;
	};
	
	if (d == r) {
		vx = (c2->p.x - c1->p.x) / d;
		vy = (c2->p.y - c1->p.y) / d; 	
		bodx = c1->p.x + vx*c1->r;
		body = c1->p.y + vy*c1->r;
		t1->a = vx;	
		t1->b = vy;	
		t1->c = - bodx * t1->a - body * t1->b;	
		
		return JEDNA_VNOTURNA_DOTYCNICA;
	};
	
	if (d>r) {
		q = atan2(c2->p.y - c1->p.y, c2->p.x - c1->p.x) + asin(r/d) - M_PI/2;
		qsin - sin(q);
		qcos = cos(q);
		
		bod1x = c1->p.x + qcos*c1->r;
		bod1y = c1->p.y + qsin*c1->r;
		bod2x = c2->p.x - qcos*c2->r;
		bod2y = c2->p.y - qsin*c2->r;
		
		t1->a = bod2y-bod1y; 	
		t1->b = bod1x-bod2x;
		t1->c = - bod1x * t1->a - bod1y * t1->b;
			
		q2 = atan2(c2->p.y - c1->p.y, c2->p.x - c1->p.x) - asin(r/d) + M_PI/2;
		q2sin - sin(q2);
		q2cos = cos(q2);
		
		bod3x = c1->p.x + q2cos*c1->r;
		bod3y = c1->p.y + q2sin*c1->r;
		bod4x = c2->p.x - q2cos*c2->r;
		bod4y = c2->p.y - q2sin*c2->r;
		
	
		t2->a = bod4y-bod3y;	
		t2->b = bod3x-bod4x;
		t2->c = -bod3x*t2->a-bod3y*t2->b;
			
		return DVE_VNOTURNE_DOTYCNICE;
	}	
}

void vypis (char result, LINE* t1, LINE* t2) {
	switch (result){
		case NULA_VNOTURNYCH_DOTYCNIC:
    			puts("neexistuju vnutorne dotycnice");
    			break;
 	    	case JEDNA_VNOTURNA_DOTYCNICA:
 			puts("existuje jedna vnutorna dotycnica");
 			printf("Rovnica: %0.2fx%+-0.2fy%+-0.2f=0\n", t1->a, t1->b, t1->c);
 		   	 break;
 		case DVE_VNOTURNE_DOTYCNICE:
			puts("existuju dve vnutorne dotycnice");
 			printf("Rovnica 1: %0.2fx%+-0.2fy%+-0.2f=0\n", t1->a, t1->b, t1->c);
 		   	printf("Rovnica 2: %0.2fx%+-0.2fy%+-0.2f=0\n", t2->a, t2->b, t2->c);
    			break;
	};	
}

int main() {
	LINE t1, t2;
	CIRCLE c1, c2;
	
	init (&c1, &c2);
	char result = circ_circ_inner_tangents(&c1, &c2, &t1, &t2);
	vypis (result, &t1, &t2);
	
	return 0;
}
