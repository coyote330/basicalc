#include <math.h>

typedef struct {
	double top;
	double bottom;
} Number; //represent all numbers as fractions for accuracy

Number add(Number a, Number b){
	Number result;
	result.top = a.top*b.bottom+b.top*a.bottom;
	result.bottom = a.bottom*b.bottom;
	return result;
}

Number subtract(Number a, Number b){
	Number result;
	result.top = a.top*b.bottom-b.top*a.bottom;
	result.bottom = a.bottom*b.bottom;
	return result;
}

Number multiply(Number a, Number b){
	Number result;
	result.top = a.top*b.top;
	result.bottom = a.bottom*b.bottom;
	return result;
}

Number divide(Number a, Number b){
	Number result;
	result.top = a.top*b.bottom;
	result.bottom = a.bottom*b.top;
	return result;
}

Number exponent(Number a, Number b){
	Number result;
	result.top = pow(a.top,b.top/b.bottom);
	result.bottom = pow(a.bottom,b.top/b.bottom);
	return result;
}
