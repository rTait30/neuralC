#include <stdio.h>
#include <math.h>

#include <stdlib.h>
#include <time.h>

#include <io.h>

#define MAX_OUTPUTS 5

// Highly Time Critical!

int calculateActiveNeurons(int neuronNo[10000], double Scale[10000], int position) {

	//calculate active neurons

	int activeNeurons = 0;

	while (!(Scale[position*100+activeNeurons*5] == 0.0)) {

		activeNeurons += 1;

	}

	//printf("Active neurons: %d", activeNeurons);

	return activeNeurons;

}

double* run_neural(int inputNo, double inputs[], int neuronNos[10000], double Scale[10000], int outputs, int activeNeurons, int position) {

	//test parameters

	/*

	printf("inputs: ");

	for (int i = 0; i < inputNo; i++) {

		printf("%f, ", inputs[i]);

	}

	printf("\n");
	
	for (int i = 0; i < 20; i++) {

		printf("neuron %d: ", i);

		for (int i2 = 0; i2 < 5; i2++) {

			printf("%d, ", neuronNos[position*100+i*5+i2]);

			printf("%lf, ", Scale[position*100+i*5+i2]);
		}

		printf("\n");

	}

	*/

	//---------------------------------------------------------------------------------------------

	//actual code

	// process
	
	double neuronValues[25];

	for (int i = 0; i < inputNo; i++) {
		
		neuronValues[i] = inputs[i];

	}

	for (int neuron = 0; neuron < activeNeurons; neuron++) {

		//printf("\nneuron %d\n", neuron);

		double neuronValue = 0;

		//calculate active inputs

		int activeInputs = 0;

		while (!(Scale[position*100+neuron*5 + activeInputs] == 0.0) && (activeInputs < 5)) {

			activeInputs += 1;

		}

		//printf("active inputs: %d\n", activeInputs);

		for (int input = 0; input < activeInputs; input++) {

			//printf("\ninput %d\n", input);

			int const neuronNo = neuronNos[position*100+neuron*5+input];

			double scale = Scale[position*100+neuron*5+input];

			//printf("neuronNo: %d, scale: %lf\n", neuronNo, scale);

			double scaledInput;
			
			scaledInput = neuronValues[neuronNo] * scale;

			//printf("%lf\n", scaledInput);				

			neuronValue += scaledInput;

		}

		//printf("total neuron value: %lf\n", neuronValue);

		neuronValues[neuron+inputNo] = neuronValue;

	}

	/*

	for (int neuron = 0; neuron < activeNeurons+inputNo; neuron++) {

		printf("neruon value: %lf\n", neuronValues[neuron]);

	}

	*/

	static double output[MAX_OUTPUTS];

	for (int neuron = 0; neuron < outputs; neuron++) {

		int subscript = activeNeurons + inputNo - neuron - 1;

		double value = neuronValues[subscript];

		output[neuron] = value;

	}

	return output;
}

/*

int main(void) {

	int intData[10000];

	double doubleData[10000];

	double inputs[2] = {1.0, 2.0};

	//int activeNeurons = 0;

	doubleData[500] = 3.0;
	doubleData[505] = 3.0;
	doubleData[510] = 3.0;
	doubleData[515] = 3.0;
	doubleData[520] = 3.0;



	int activeNeurons = calculateActiveNeurons(intData, doubleData, 5);

	printf ("Active neurons: %d\n", activeNeurons);

	//timing for optimising

	
	
	for (int i = 0; i < 1000000; i++) {

		run_neural(2, inputs, intData, doubleData, 2, activeNeurons, 5);

	}

	

    double* outputs;

	outputs = run_neural(2, inputs, intData, doubleData, 2, activeNeurons, 5);

	printf("%lf\n", outputs[0]);
	printf("%lf\n", outputs[1]);

	return EXIT_SUCCESS;
	
}

*/
