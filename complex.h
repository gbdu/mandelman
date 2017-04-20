#define EPSILON 0.0001
#define ZMAG(z) (sqrtf(z.a*z.a + z.b*z.b))
#define EQUAL(a,b) (fabs(a-b) < EPSILON)
#define ZEQUAL(one,two) (EQUAL(one.a, two.a) && EQUAL(one.b, two.b))

typedef struct {
	float a;
	float b;
} Z; //

int Mb_GetN(Z c, int max_iter); // returns -1 if not in set

Z z_multiply_two(Z one, Z two);
Z z_multiply(unsigned int items, ...);

