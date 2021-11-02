#include <stdio.h>
#include <math.h>

#include <stdlib.h>
#include <time.h>

#include <unistd.h>

void print_network_position(int neuronNos[10000], double Scales[10000], int position) {

	printf("Network %d:\n", position);

	for (int neuron = 0; neuron < 20; neuron++) {

		if (Scales[position*100+neuron*5] > 0 || Scales[position*100+neuron*5 + 1] > 0 || Scales[position*100+neuron*5 + 2] > 0 || Scales[position*100+neuron*5 + 3] > 0 || Scales[position*100+neuron*5 + 4] > 0) {
	
			printf("Neuron: %d:\n", neuron);

			for (int input = 0; input < 5; input++) {

				int neuronNo = neuronNos[position*100+neuron*5+input];

				double Scale = Scales[position*100+neuron*5+input];
			
				printf("%d, %lf; ", neuronNo, Scale);

			}

			printf("\n");

		}
	}
}

/*
void gen_zero_position(int neuronNo[10000], double Scale[10000], int position) {

	

}
*/

void gen_random_position(int inputNo, int neuronNo[10000], double Scale[10000], int activeNeurons, int position) {

	for (int neuron = 0; neuron < activeNeurons; neuron++) {
	
		for (int input = 0; input < 3; input++) {
			
			neuronNo[position*100+neuron*5+input] = rand() % (inputNo + neuron);

			Scale[position*100+neuron*5+input] = (double) (rand() % 10 - 5) + 0.1;

		}
	}
}

/*

int main(void) {


	int neuronNo[10000];


	double Scale[10000];

	
	gen_random_position(2, neuronNo, Scale, 5, 98);

	print_network_position(neuronNo, Scale, 98);

	return EXIT_SUCCESS;

}

*/
