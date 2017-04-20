#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include "complex.h"

#include <stdio.h>

Z z_multiply_two(Z one, Z two){
	// (a + ib)( c + id ) = (ac − bd ) + i (ad + bc).
	Z prod = {one.a*two.a - one.b*two.b, one.a*two.b + one.b*two.a};
	return prod;
}

Z z_multiply(unsigned int items, ...){
	va_list arglist;
	va_start(arglist, items);
	
	Z product = {1, 0};
	Z current ;
	
	while(items--) {
		current = va_arg(arglist, Z);
		product = z_multiply_two(product, current);
		
	}
	va_end(arglist);
	return product;
}

Z z_add_two(Z one, Z two){
	Z sum = {one.a+two.a, one.b+two.b};
	return sum;
}

// z = zn-1 ^2 + c
int Mb_GetN(Z c, int max_iter){ // returns -1 if not in set 
	Z zn = {0, 0};
	Z znMinusOne = {0, 0};
	int n = 0;
	for(; n < max_iter; n++){
		zn = z_multiply_two(znMinusOne, znMinusOne) ;
		zn = z_add_two(zn, c);
		
		if(ZMAG(zn) > 2.0 ) {
			// c is not on the mandelbrot set
			return n;
		}
		
		znMinusOne = zn;
	}
	return -1;
}





