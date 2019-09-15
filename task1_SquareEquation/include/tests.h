#ifndef TESTS_H_
#define TESTS_H_

#define TESTS_NUMBER	2

typedef double data;

data input_data[TESTS_NUMBER][3] =
{
		{0, 0, 0},
		{1, 2, 1}
};

int res_data[TESTS_NUMBER] =
{
		3,
		1
};

data roots_data[TESTS_NUMBER][2] =
{
		{0, 0},
		{-1, -1}
};

int unittest_SolveSquare(int cnt)
{
	data x1 = 0, x2 = 0;
	data a = input_data[cnt-1][0], b = input_data[cnt-1][1], c = input_data[cnt-1][2];
	int result = SolveSquare(a, b, c, &x1, &x2);

	if ((result != res_data[cnt-1]) || (x1 != roots_data[cnt-1][0]) || (x2 != roots_data[cnt-1][1]))
	{
		printf("#!! Unit test #%d FAILED\n", cnt);
		printf("#!!\tSolveSquare result: %d, expected: %d\n", result, res_data[cnt-1]);
		printf("#!!\ta = %.2lf\tb = %.2lf\tc = %.2lf\n", a, b, c);
		printf("#!!\tx1 = %.2lf, expected: %.2lf\n", x1, roots_data[cnt-1][0]);
		printf("#!!\tx2 = %.2lf, expected: %.2lf\n", x2, roots_data[cnt-1][1]);
		return -1;
	}

	return 0;
}


#endif /* TESTS_H_ */
