Open todos:
Blogpost with python examples and theory
https://alaurans.com/blog/reinforcement-learning-from-scratch-to-deep-q-network
https://www.learndatasci.com/tutorials/reinforcement-q-learning-scratch-python-openai-gym/


//TODO: observation and step taking on a method? if not difficult
//TODO: Neural Network class QLearning is supposed to be passed to a neural network for it to learn to apply the learned behaviour dynamically
                              check out Arduino NN Library: https://github.com/GiorgosXou/NeuralNetworks
                              
//TODO: Vehicle function to take and action and recieve the reward
//TODO: Save sessions to text file? is it doable?
//TODO: refactor Q array to be multidimensional, at least Q[State][Actions]


Q learning:
The Agent has two motors which can be turn on both directions at different speeds:
Actions:
left motor, time, speed, //TODO: direction
right motor, time, speed, //TODO: directions
//TODO: Servo with Ultrasonic sensor, rotationAngle //TODO: Mount ultrasonic sensor on a turrent

States , Environment observations:
Measurements from ultrasonic sensors. Current 3 Sensors, //TODO: 2 to be removed

//TODO: add Compass module which will add more observations 


--------------------------

int learningRate = 0.003;

//2 steps per second to move for 1 minutes
int steps = 100;

//goal = distances from wall
int goal = 10 ;
int initialRuns = 10000;

Vehicle vehicle;

float gamma = 0.75;
float alpha = 0.1;
float epsilon;

void initialPopulation() {

  //2D Array with the actions
  int trainingData[goalSteps][4];

  //save all scores
  int scores[initialRuns];
  int acceptedScores[100];

  for (int i = 0; i < initialRuns; i++) {

    int score = 0;
    int memory[50];

    //left, mid, right sensor measurements
    double previousObservation[3] = {0.0, 0.0, 0.0};

    for (int i = 0; i < goalSteps; i++) {

      //choose random from the action space
      int action[4] = {random(0, 2), random(0, 2), random(0, 2), random(0, 2) };
      vehicle.perform(action);

      /*
        Based on last action, do one step, return environment observation, acquire reward for that action.
        observation, reward, isDone, info = environment.step(action)
      */

      /*
        int observation[4] = vehicle.getObservation(action);
        int reward = getReward();
      */
      if ((sizeof(previousObservation) / sizeof(previousObservation[0])) > 0) {
        //append action to previous observation to memory
        memory[i] = previousObservation;
      }
      //previousObservation = observation
      score += reward;
      if (done) {
        break;
      }
    }
  }

  if (measurement >= goal) { //save it somewhere
  
    for (int i = 0; i < memory.length; i++) {
      //int[] output= {0,0};
      //get the actions from the memory to implement them in the controller
     
       if (memory[1] == 1) {   //actions in memory come in pairs
        output = [0, 1];  //e.x:  move right
        } else if (memory[1] == 0) {
        output = [1, 0]; //e.x: move left
        } else {
        output = [0, 0]; //dont move
        }

      //trainingData.append([memory[0], output]);
    }
    //reset environment
    score.append(score);
  }

  //return training data

}
 
   Naive Q-Learning
   _______________

   Q-learning (Watkins & Dayan, 1992) learns the action value (“Q-value”) and update it according
   to the Bellman equation. The key point is while estimating what is the next action, it does not follow
   the current policy but rather adopt the best Q value (the part in red) independently.

   Q = defaultdict(float)
  gamma = 0.99  # Discounting factor
  alpha = 0.5  # soft update param

  actions = range(env.action_space)

  def update_Q(s, r, a, s_next, done):
    max_q_next = max([Q[s_next, a] for a in actions])
    # Do not include the next state's value if currently at the terminal state.
    Q[s, a] += alpha * (r + gamma * max_q_next * (1.0 - done) - Q[s, a])

   D Q Learning

   Deep Q-network is a seminal piece of work to make the training of Q-learning more stable and
   more data-efficient, when the Q value is approximated with a nonlinear function. Two key ingredients
   are experience replay and a separately updated target network.

   The main loss function looks like the following
  Y(s,a,r,s′)=r + γ maxa′Qθ−(s′,a′)
  L(θ)= E (s,a,r,s′)∼U(D)[(Y(s,a,r,s′)−Qθ(s,a))^2]


   q = dense(states, [32, 32, 2], name='Q_primary')
  q_target = dense(states_next, [32, 32, 2], name='Q_target')


DQN Step by step: 
initialize replay memory
initialize policy network with random weights
clone network and call it target network
for each episode:
    initialize the starting state
    for each time step:
        select an action
            via exploration or exploitation
        execute selected action in an emulator
        observe reward and next state
        store experience in replay memory
        sample random batch from replay memory
        preprocess states from batch
        pass batch of preprocessed states to policy network
        calculate loss between ouput Q values and target Q values
            requires a pass to the target network for the next state
        gradient descent updates weights in the policy network to minimize loss
            after x time steps, weights in the target network are updated to the wieghts in the policy network
            