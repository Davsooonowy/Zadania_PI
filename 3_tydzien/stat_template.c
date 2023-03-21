#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define TWO_DICE_SUM 11

int rand_from_interval(int a, int b) {
    return a + rand()%(b+1-a);
}


void fill_with_randoms(int array[], int n, int start, int end) {
    for(int i = 0; i < n; i++) {
        array[i] = rand_from_interval(start, end);
    }
}
// Calculates arithmetic mean and    variance of numbers from n-element array v[]
// for n = 0: mean = variance = 0
void mean_variance(const int v[], int n, double *mean, double *variance) {
    double sum_square = 0, sum = 0;
    for(int i = 0; i < n; i++) {
        sum += v[i];
        sum_square += v[i] * v[i];
    }
    *mean = (double) sum / n;
    *variance = (double) sum_square/n - (*mean) * (*mean);
}


// Fill n-element array v[] with Bernoulli sample (binary values)
void bernoulli_gen(int v[], int n, double probability) {
    for(int i = 0; i < n; i++) {
        double res = (double) rand() / RAND_MAX;
        if(res <= probability) {
            v[i] = 1;
        } else {
            v[i] = 0;
        }
    }
}


// Calculate pmf (probability mass function) of discrete random variable.
// Two dice are thrown simultaneously The random variable is the sum of the
// numbers shown (the result is from [2, 12]).
// trials - number of trials
void pmf(double v[], int trials) {
    int pom_tab[TWO_DICE_SUM] = {0};

    for (int i = 0; i < trials; i++) {
        int dice_roll = rand_from_interval(1, 6) + rand_from_interval(1, 6);
        pom_tab[dice_roll - 2]++;
    }

    for (int i = 0; i < 11; i++) {
        v[i] = (double) pom_tab[i] / (trials);
    }
}
// Calculates the cumulative distribution function (v) for 'trials' numbers
// Two dice are thrown simultaneously The random variable is the sum of the
// numbers shown (the result is from [2, 12]).
// trials - number of trials
void cdf(double v[], int trials) {
    int pom_tab[TWO_DICE_SUM] = {0};

    for (int i = 0; i < trials; i++) {
        int dice_roll = rand_from_interval(1, 6) + rand_from_interval(1, 6);
        pom_tab[dice_roll - 2]++;
    }

    double cumulative_sum = 0;
    for (int i = 0; i < TWO_DICE_SUM; i++) {
        cumulative_sum += pom_tab[i];
        v[i] = cumulative_sum / trials;
    }
}

// Histogram - bar chart for the values from v[] array of length n
// x_start - the first value on the abscissa (x increment is 1),
// y_scale - y value corresponding to single char of the histogram
void print_histogram(const double v[], int n, int x_start, double y_scale, char mark) {
    for(int i=0;i<n;i++) {
        printf("%d |", i+x_start);
        int len = (int) round(v[i]/y_scale);
        for(int j = 0; j < len; j++) {
            printf("%c", mark);
        }
        printf(" %.3lf\n", v[i]);
    }
}

// Simulate Monty-Hall problem
// input: n - number of trials
// output: wins - number od wins if door switched
// output: win_probability - probability of win if door switched

// This function calls rand() exactly 2 times:
// the first one returns winning door number,
// the second one returns door number that the player has chosen the first time,
void monty_hall(int n, int *p_switch_wins) {
    int wins = 0;
    for(int i = 0; i < n; i++) {
        int correct = rand() % 3;
        int choice = rand() % 3;
        if(choice == correct) {
            continue;
        } else {
            wins++;
        }
    }
    *p_switch_wins = wins;
}

// print double vector of size n (with 2 figures after the decimal point)
//void print_vector(const double v[], int n) {
//	for (int i = 0; i < n; ++i) {
//		printf("%.2f ", v[i]);
//	}
//	printf("\n");
//}

// print integer vector
void print_int_vector(const int v[], int n) {
	for (int i = 0; i < n; ++i) {
		printf("%d ", v[i]);
	}
	printf("\n");
}

int main(void) {
	char mark;
	int to_do, n, seed, m_h_wins, a, b, i_vector[100];
	double arithmetic_mean, variance, probability, d_vector[100];
	scanf("%d", &to_do);
	scanf("%d",&seed);
	scanf("%d",&n);
	srand((unsigned)seed);

	switch (to_do) {
		case 1: // mean_variance
			scanf("%d %d", &a, &b);
			fill_with_randoms(i_vector, n, a, b);
			mean_variance(i_vector, n, &arithmetic_mean, &variance);
			printf("%.2f %.2f\n", arithmetic_mean, variance);
			break;
		case 2: // bernoulli_gen
			scanf("%lf", &probability);
			bernoulli_gen(i_vector, n, probability);
			print_int_vector(i_vector, n);
			break;
		case 3: // pmf
			scanf(" %c", &mark);
			pmf(d_vector, n);
			print_histogram(d_vector, TWO_DICE_SUM, 2, 0.005, mark);
			break;
		case 4: // cdf
			scanf(" %c", &mark);
			cdf(d_vector, n);
			print_histogram(d_vector, TWO_DICE_SUM, 2, 0.02, mark);
			break;
		case 5: // monty_hall
			monty_hall(n, &m_h_wins);
			printf("%d %d\n", m_h_wins, n - m_h_wins);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}

