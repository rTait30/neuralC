#include <stdio.h>
#include <math.h>

#include <stdlib.h>
#include <time.h>

#include <io.h>


void print_network_position(int neuronNos[10000], double Scales[10000], int position);

void gen_random_position(int inputNo, int neuronNo[10000], double Scale[10000], int activeNeurons, int position);

int calculateActiveNeurons(int neuronNo[10000], double Scale[10000], int position);

double* run_neural(int inputNo, double inputs[], int neuronNos[100], double Scale[100], int outputs, int activeNeurons, int position);

void mutate_network_position(int inputNo, int neuronNo[10000], double Scale[10000], int position);

double Test0_waypoints(int neuronNos[10000], double Scale[10000], double width, double height, double wall, int runtime, double trials, int position);


int sum(int test[100]) {

	int total = 0;

	for (int i = 0; i < 100; i++) {

		total += test[i];

	}

	return total;
}

void copynetwork(int neuronNos[10000], double Scale[10000], int source, int destination) {

	for (int i = 0; i < 100; i++) {

		neuronNos[destination*100+i] = (neuronNos[source*100+i]);

		Scale[destination*100+i] = (Scale[source*100+i]);

	}
}

//begin 10 networks, generate 75 mutated networks, 5 double mutated networks and 10 random networks, rank all including initial networks, offspring; 1:12, 2:11, 3:10, 4:9, 5:8, 6:7, 7:6, 8:5, 9:4, 10:3, choose best 10
double Evolve1_Test1(int neuronNos[10000], double Scale[10000], double width, double height, double wall, int runtime, double trials, int generations) {
	
	int activeNetworks = 0;

	while (!(Scale[activeNetworks*100] == 0.0)) {

		activeNetworks += 1;

	}

	printf("%d active networks\n", activeNetworks);

	if (activeNetworks < 10) {

		printf("generating %d random networks\n", 10-activeNetworks);

		for (int network = activeNetworks; network<10; network++) {

			gen_random_position(2, neuronNos, Scale, 5, network);

		}

	}

	double top_score = 0.0;

	int successful = 0;

	for (int generation = 0; generation < generations; generation++) {

		if (generation % 100 == 0) {printf("\n----------------------------GENERATION %d-----------------------------\n", generation);}

		/*
		if (successful == 2) {

			printf("Initial network:");

			print_network_position(neuronNos, Scale, 9);

		}
		*/

		successful = 0;

		//score initial networks
		double initial_scores[10];

		for (int network = 0; network<10; network++) {

			initial_scores[network] = Test0_waypoints(neuronNos, Scale, width, height, wall, runtime, trials, network);

			if (generation % 150 == 0) {

				//printf("%lf, ", initial_scores[network]);

			}

		}

		//rank networks

		int ranks[10];

		for (int network = 0; network<10; network++) {

			int rank = 0;

			for (int network2 = 0; network2<10; network2++) {

				if (initial_scores[network] > initial_scores[network2]) {

					rank += 1;

				}
			
			ranks[network] = rank;

			}

		}

		int total_offspring = 0;

		int population = 10;

		for (int network = 0; network < 10; network++) {

			int offspring = ranks[network] + 3;

			//printf("network %d, rank %d, offspring: %d\n", network, ranks[network], offspring);

			total_offspring += offspring;

			for (int child = 0; child < offspring; child ++) {

				//printf("network %d, child %d\n", network, child);

				//copy network
				/*
				for (int i = 0; i < 100; i++) {

					neuronNos[population*100+i] = neuronNos[network*100+i];

					Scale[population*100+i] = Scale[network*100+i];

				}
				*/

				copynetwork(neuronNos, Scale, network, population);

				//printf("copied\n");

				//mutate child network
				mutate_network_position(2, neuronNos, Scale, population);

				//printf("mutated\n");

				population += 1;

			}
		}

		//printf("total offspring: %d\n", total_offspring);

		for (int random = population; random < 100; random++) {

			gen_random_position(2, neuronNos, Scale, 5, random);

		}

		double scores[100];

		//printf("%lf\n", scores[0]);

		for (int network = 0; network < 100; network++) {

			//print_network_position(neuronNos, Scale, i);

			double score = Test0_waypoints(neuronNos, Scale, width, height, wall, runtime, trials, network);

			//print_network_position(neuronNos, Scale, network);

			if (score > 0) {

				successful = 1;

				//printf("generation %d, network %d, score %lf\n", generation, network, score);

				//print_network_position(neuronNos, Scale, network);

				//print_network_position(neuronNos, Scale, network);
				

			}

			scores[network] = score;

		}

		//now have 100 networks with scores

		//rank networks

		//int best[10];


		int safe_networks[100];
	
		for (int network = 0; network < 100; network++) {

			safe_networks[network] = 0;

		}
		

		int iteration = 0;

		//(sum(safe_networks) < 10)

		while (sum(safe_networks) < 10) {

			
			

			//printf("\niteration %d\n", iteration);

			//printf("safe networks: ");

			/*
			for (int network = 0; network < 100; network++) {

				if (safe_networks[network] == 1) { printf("%d, ", network); }

			}
			*/

			//printf("\n");

			int positions_left = 10 - sum(safe_networks);

			//printf("positions left: %d\n", positions_left);

			double highest_score = 0;

			for (int network = 0; network < 100; network++) {

				if (scores[network] > highest_score && safe_networks[network] == 0) {

					highest_score = scores[network];

					//safe_networks[network] = 1;

					if (iteration == 0) {

						if (highest_score > top_score && generation > 100) {

							//printf("highest_score = %lf\n", highest_score);
						
							//successful = 1;

							top_score = highest_score;

							printf("\nNew top score: %lf\nGeneration %d:\n", top_score, generation);
							
							print_network_position(neuronNos, Scale, network);
							successful = 2;

						}

					}
				}
			}

			

			//check amount of equal networks
			int equal_networks[100];

			for (int network = 0; network < 100; network++) {

				equal_networks[network] = 0;

			}

			for (int network = 0; network < 100; network++) {

				if (scores[network] == highest_score) { equal_networks[network] = 1; }

			}

			/*

			printf("equal networks: ");

			for (int network = 0; network < 100; network++) {

				if (equal_networks[network] == 1 && safe_networks[network] == 0) {

					printf("%d, ", network);

				}

			}

			*/

			//printf("\n");

			//printf("total equal networks: %d\n", sum(equal_networks));

			if (sum(equal_networks) > positions_left) {

				//printf("problem\n");

				int network = 0;

				while (sum(safe_networks) < 10) {

					if (equal_networks[network] == 1) {

						safe_networks[network] = 1;
					}

					network += 1;
				}

			} else {

				for (int network = 0; network < 100; network++) {

					if (equal_networks[network] == 1 && safe_networks[network] == 0) {

						safe_networks[network] = 1;

					}

				}
			}

			//printf("\n\n");

			iteration += 1;

		}
		
		/*
		if (successful == 1) {

			printf("final safe networks: ");

			for (int network = 0; network < 100; network++) {

				if (safe_networks[network] == 1) {

					printf("network %d\n", network);
	
					print_network_position(neuronNos, Scale, network);

				}

			}

			printf("\n");

		}
		*/

		int new_generation = 0;

		//if (successful == 1) {printf("non-zero scores: ");}

		for (int network = 0; network < 100; network++) {

			if (safe_networks[network] == 1) {

				//if (successful == 1) {printf("%d, ", network);}

				/*
				for (int i = 0; i < 100; i++) {

					neuronNos[new_generation*100+i] = *(neuronNos[network*100+i]);

					Scale[new_generation*100+i] = Scale[network*100+i];

				}
				*/
				copynetwork(neuronNos, Scale, network, new_generation);

				new_generation += 1;

			}

		}

		//printf("\nnew_generation: %d\n", new_generation);

		//if (successful == 1) {printf("|");}
		if (successful == 2) {printf("+");}


	}


	return 0.0;

}

int main(void) {

	srand(time(NULL));

	int intData[10000];

	double doubleData[10000];

	//double inputs[2] = {1.0, 2.0};

	/*

	for (int i = 1; i<100; i++) {

		gen_random_position(2, intData, doubleData, 5, i);

	}

	*/

	//double score = Test0_waypoints(intData, doubleData, 500.0, 500.0, 20.0, 1000, 10.0, 0);

	//printf("Score: %lf\n", score);

	
	//intData[2] = 1;
	//intData[10] = 1;

	//doubleData[0] = 2.0;
	//doubleData[1] = 1.0;
	//doubleData[2] = 3.0;
	//doubleData[5] = 1.0;
	//doubleData[10] = 1.0;

	/*

	doubleData[0] = 7.691292;
	doubleData[1] = 2;
	doubleData[2] = 10.447243;

	doubleData[5] = -5;
	doubleData[6] = 0.000001;

	doubleData[10] = -5.0;
	doubleData[11] = 2.0;
	doubleData[12] = -5.0;

	doubleData[15] = 1.43327;

	doubleData[20] = 3.271112;
	doubleData[21] = 0.000001;
	doubleData[22] = 2;

	intData[0] = 1;
	intData[1] = 1;
	intData[2] = 1;

	intData[5] = 2;
	intData[6] = 1;

	intData[10] = 3;
	intData[11] = 2;
	intData[12] = 2;


	intData[21] = 2;

	*/

	

	double* testOutputs;

	double inputs[2] = {1,2};

	testOutputs = run_neural(2, inputs, intData, doubleData, 2, 5, 0);

	printf("%lf, %lf\n", testOutputs[0], testOutputs[1]);

	
	

	//printf("%lf\n", Test0_waypoints(intData, doubleData, 500.0, 500.0, 20.0, 2000, 100.0, 0));

	Evolve1_Test1(intData, doubleData, 500.0, 500.0, 20.0, 2000, 100.0, 1000000);

	/*
	double* outputs = run_neural(2, inputs, intData, doubleData, 2, activeNeurons, 0);
	
	printf("%lf, ", outputs[0]);
	printf("%lf\n", outputs[1]);
	*/

	/*

	for (int i = 0; i<100; i++) {

		printf("Network %d:\n", i);

		int activeNeurons = calculateActiveNeurons(intData, doubleData, i);

		double* outputs;

		outputs = run_neural(2, inputs, intData, doubleData, 2, activeNeurons, i);

		printf("%lf, ", outputs[0]);
		printf("%lf\n", outputs[1]);

	}

	*/

	/*

	for (int i = 0; i<15; i++) {

		if (i == 0) { print_network_position(intData, doubleData, 0); }


		mutate_network_position(2, intData, doubleData, 0);

		print_network_position(intData, doubleData, 0);

		int activeNeurons = calculateActiveNeurons(intData, doubleData, 0);

		double* outputs = run_neural(2, inputs, intData, doubleData, 2, activeNeurons, 0);

		
		printf("%lf, ", outputs[0]);
		printf("%lf\n\n", outputs[1]);

	}
	
	*/

	return EXIT_SUCCESS;
	
}
