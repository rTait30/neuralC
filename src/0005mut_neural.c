#include <stdio.h>
#include <math.h>

#include <stdlib.h>
#include <time.h>

#include <unistd.h>

int calculateActiveNeurons(int neuronNo[10000], double Scale[10000], int position);

void mutate_network_position(int inputNo, int neuronNo[10000], double Scale[10000], int position) {

	int mutationType = rand() % 8;

	//int mutationType = 7;

	//printf("mutate type: %d\n", mutationType);

	int activeNeurons = calculateActiveNeurons(neuronNo, Scale, position);

	if (mutationType == 0) { //add neuron

		if (activeNeurons < 20) {

			int neuronPosition = rand() % activeNeurons;

			//printf("position = %d\n", neuronPosition);

			for (int neuron = activeNeurons+1; neuron > neuronPosition; neuron--) {

				for (int input = 0; input < 5; input++) {

					if ( neuronNo[position*100+(neuron-1)*5+input] < (neuronPosition+inputNo) ) {
						
						neuronNo[position*100+neuron*5+input] = neuronNo[position*100+(neuron-1)*5+input];

					} else {
						
						neuronNo[position*100+neuron*5+input] = neuronNo[position*100+(neuron-1)*5+input] + 1;
						
					}

					Scale[position*100+neuron*5+input] = Scale[position*100+(neuron-1)*5+input];

				}

			}

			for (int input = 0; input < 3; input++) {
				
				neuronNo[position*100+neuronPosition*5+input] = rand() % (neuronPosition + inputNo);

				Scale[position*100+neuronPosition*5+input] = (double) ((rand() % 10) - 5) + 0.000001;

			}

		} else {

			//printf("Cant add any more neurons\n");

		}

	}

	if (mutationType == 1) { //delete neuron

		if (activeNeurons > 1) {

			int neuronPosition = rand() % activeNeurons;

			//printf("position = %d\n", neuronPosition);

			for (int neuron = neuronPosition; neuron < activeNeurons; neuron++) {

				for (int input = 0; input < 5; input++) {

					if ( neuronNo[position*100+(neuron+1)*5+input] < (neuronPosition+inputNo) ) {
						
						neuronNo[position*100+neuron*5+input] = neuronNo[position*100+(neuron+1)*5+input];

					} else {
						
						neuronNo[position*100+neuron*5+input] = neuronNo[position*100+(neuron+1)*5+input] - 1;
						
					}

					Scale[position*100+neuron*5+input] = Scale[position*100+(neuron+1)*5+input];

				}

			}

		} else {

			//printf("Cant delete any more neurons\n");

		}

	}
	
	if (mutationType == 2) { //add input easy

		int changeNeuron = rand() % activeNeurons;

		int activeInputs = 0;

		while (!(Scale[position*100+changeNeuron*5 + activeInputs] == 0.0) && (activeInputs < 5)) {

			activeInputs += 1;

		}

		if (activeInputs < 5) {

			//printf("add input to neuron %d\n", changeNeuron);

			neuronNo[position*100+changeNeuron*5+activeInputs] = rand() % (inputNo + changeNeuron);

			Scale[position*100+changeNeuron*5+activeInputs] = (double) (rand() % 10 - 5) + 0.000001;

		} else {
			
			//printf("already max inputs on neuron %d!\n", changeNeuron);

		}

	}
	
	if (mutationType == 3) { //delete input easy
		
		int changeNeuron = rand() % activeNeurons;

		int activeInputs = 0;

		while (!(Scale[position*100+changeNeuron*5 + activeInputs] == 0.0) && (activeInputs < 5)) {

			activeInputs += 1;

		}

		if (activeInputs > 1) {
			
			neuronNo[position*100+changeNeuron*5+activeInputs-1] = 0;

			Scale[position*100+changeNeuron*5+activeInputs-1] = 0.0;

		} else {
			
			//printf("cant delete any more neurons on neuron %d!\n", changeNeuron);

		}

	}
	
	if (mutationType == 4) { //move neuronNo easy
		
		int changeNeuron = rand() % activeNeurons;

		int activeInputs = 0;

		while (!(Scale[position*100+changeNeuron*5 + activeInputs] == 0.0) && (activeInputs < 5)) {

			activeInputs += 1;

		}

		int changeInput = rand() % activeInputs;

		int change = (rand() % 3) - 1;

		//printf("change neuron %d, input %d by %d\n", changeNeuron, changeInput, change);

		neuronNo[position*100+changeNeuron*5+changeInput] = abs((neuronNo[position*100+changeNeuron*5+changeInput] + change) % (changeNeuron + inputNo));

		

	}
	
	if (mutationType == 5) { //new neuronNo easy
		
		int changeNeuron = rand() % activeNeurons;

		int activeInputs = 0;

		while (!(Scale[position*100+changeNeuron*5 + activeInputs] == 0.0) && (activeInputs < 5)) {

			activeInputs += 1;

		}

		int changeInput = rand() % activeInputs;

		neuronNo[position*100+changeNeuron*5+changeInput] = abs(rand() % (changeNeuron + inputNo));

	}
	
	if (mutationType == 6) { //move Scale easy
		
		int changeNeuron = rand() % activeNeurons;

		int activeInputs = 0;

		while (!(Scale[position*100+changeNeuron*5 + activeInputs] == 0.0) && (activeInputs < 5)) {

			activeInputs += 1;

		}

		int changeInput = rand() % activeInputs;

		double change = ((double) ((rand() % 10000000) - 5000000))/1000000;

		//printf("change neuron %d, input %d by %lf\n", changeNeuron, changeInput, change);

		Scale[position*100+changeNeuron*5+changeInput] = (Scale[position*100+changeNeuron*5+changeInput] + change);

	}
	
	if (mutationType == 7) { //new Scale easy
		
		int changeNeuron = rand() % activeNeurons;

		int activeInputs = 0;

		while (!(Scale[position*100+changeNeuron*5 + activeInputs] == 0.0) && (activeInputs < 5)) {

			activeInputs += 1;

		}

		int changeInput = rand() % activeInputs;

		Scale[position*100+changeNeuron*5+changeInput] = (double) (rand() % 10 - 5) + 0.000001;

	}
	
}
