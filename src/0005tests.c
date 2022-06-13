
double M_PI = 3.14159265359;

int calculateActiveNeurons(int neuronNo[10000], double Scale[10000], int position);

double* run_neural(int inputNo, double inputs[], int neuronNos[100], double Scale[100], int outputs, int activeNeurons, int position);

double Test0_waypoints(int neuronNos[10000], double Scale[10000], double width, double height, double wall, int runtime, double trials, int position) {

	int activeNeurons = calculateActiveNeurons(neuronNos, Scale, position);

	double big_score = 0.0;

	//Car = speed, position x, position y, direction

	double Car[4] = {0.0,0.0,0.0,0.0};

	double Waypoint[2];

	/*
	Waypoint[0] = (double) ( rand() % ( (width/2 + wall) * 2 - (width/2 * wall)));
	Waypoint[1] = (double) ( rand() % ( (height/2 + wall) * 2 - (height/2 * wall)));

	Waypoint[0] = 50.0;
	Waypoint[1] = 40.0;
	*/

	for (int trial = 0; trial < trials; trial++) {

		int alive = 1;

		Waypoint[0] = (double) ( 400 - (rand() % 800));
		Waypoint[1] = (double) ( 400 - (rand() % 800));

		Car[0] = 0.0;
		Car[1] = (double) ( 400 - (rand() % 800));
		Car[2] = (double) ( 400 - (rand() % 800));
		Car[3] = 0.0;

		double trial_score = 0.0;

		//while frame < runtime and alive == 1:

		int frame = 0;

		while ((frame < runtime) && (alive == 1)) {

			if (trial == 0 && trial_score == 0 && frame%10 == 0) {

				//printf("%lf, %lf, %lf, %lf\n", Car[0], Car[1], Car[2], Car[3]);

			}

			frame += 1;
			
			if ((abs(Waypoint[0] - Car[1]) < 10) && (abs(Waypoint[1] - Car[2]) < 10)) {
			
				Waypoint[0] = (double) ( 400 - (rand() % 800));
				Waypoint[1] = (double) ( 400 - (rand() % 800));

				/*
				Waypoint[0] = 50.0;
				Waypoint[1] = 40.0;

				Car[0] = 0.0;
				Car[1] = 0.0;
				Car[2] = 0.0;
				Car[3] = 0.0;
				*/
				

				trial_score += 1;
			
			}

			if (alive == 1) {

				double real_direction;
				
				if (Car[2] < Waypoint[1]) {

					if (Car[1] < Waypoint[0]) {

						real_direction = atan((abs(Waypoint[1]-Car[2]))/(abs(Waypoint[0]-Car[1])+0.000001)); //good

	 				} else {

						real_direction = M_PI - atan((abs(Waypoint[1]-Car[2]))/(abs(Waypoint[0]-Car[1])+0.000001)); //good

					}

				} else {
					
					if (Car[1] < Waypoint[0]) {

						real_direction = (M_PI*2) - atan((abs(Waypoint[1]-Car[2]))/(abs(Waypoint[0]-Car[1])+0.000001));

					} else {
						
						real_direction = M_PI + atan((abs(Waypoint[1]-Car[2]))/(abs(Waypoint[0]-Car[1])+0.000001));

					}
			
				}

				double relative_direction = (((M_PI*2) - Car[3]) + real_direction);

				if (relative_direction > M_PI) {

					relative_direction -= (M_PI*2);

				}

				double distance_waypoint = sqrt(pow((Waypoint[1]-Car[2]),2) + pow((Waypoint[0]-Car[1]), 2)); //good

				double Senses[2];

				Senses[0] = relative_direction;

				Senses[1] = distance_waypoint;

				double* Inputs = run_neural(2, Senses, neuronNos, Scale, 2, activeNeurons, position);

				Car[1] += Car[0] * cos(Car[3]);

				Car[2] += Car[0] * sin(Car[3]);

				Car[0] += Inputs[0];

				Car[3] += Inputs[1];

				if ( (Car[1] < -480) || (Car[1] > 480) || (Car[2] < -480) || (Car[2] > 480) ){

					alive = 0;

				}

			} else {

			}
		}

		//if (trial_score > 0) {printf("Trial score: %lf\n", trial_score);}

		big_score += trial_score;

	}

	double avg_score = (big_score/trials);

	return avg_score;
	
}
