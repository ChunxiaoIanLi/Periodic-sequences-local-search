#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <time.h>

struct quadratic_eq
{
	std::vector<char> quadratic;
	int pos_one_count=0;
	int neg_one_count=0;
};

void init_quadratics(std::vector<std::vector<char> >& sequences, std::vector<quadratic_eq>& quadratics, int& n, int& seq_count, int& quadratic_count){
	for(int qua=0; qua<quadratic_count; qua++){
		//for each quadratic equation
		int step=qua+1;
		for(int seq=0; seq<seq_count; seq++){
			for(int var=0; var<n; var++){
				//for each variable in each sequence
				char temp=sequences[seq][var]*sequences[seq][(var+step)%n];
				//push to array
				quadratics[qua].quadratic.push_back(temp);
				//increase counter
				if(temp==1){
					++quadratics[qua].pos_one_count;
				}
				else{
					++quadratics[qua].neg_one_count;
				}
			}
		}
	}
}

bool verify_solution(std::vector<quadratic_eq>& quadratics, std::vector<std::vector<std::vector<int> > >& sequences_indices, std::vector<std::vector<char> >& sequences){
	
	
	//testing
	std::cout<<std::endl<<"LINEAR EQUATION"<<std::endl<<std::endl;
    for(auto a: sequences[0]){
		std::cout<<(int)a<<" ";
    }
	std::cout<<std::endl;
    for(auto b: sequences[1]){
		std::cout<<(int)b<<" ";
    }
	std::cout<<std::endl<<std::endl;

    int counter=1;
    for(auto a: sequences_indices){
		std::cout<<"linear: "<<counter<<std::endl;
		std::cout<<"Positive: ";
        for(auto b: a[0]){
			std::cout<<b<<", ";
        }
		std::cout<<std::endl;
		std::cout<<"Negative: ";
        for(auto b: a[1]){
			std::cout<<b<<", ";
        }
		std::cout<<std::endl<<std::endl;
        ++counter;
    }
	std::cout<<std::endl;



	//testing
	std::cout<<"QUADRATIC EQUATION"<<std::endl<<std::endl;
    counter=1;
    for(auto qua: quadratics){
		std::cout<<"quadratic: "<<counter<<std::endl;
        for(auto num: qua.quadratic){
			std::cout<<(int)num<<" ";
        }
		std::cout<<std::endl;
		std::cout<<"positive count: "<<qua.pos_one_count<<std::endl;
		std::cout<<"negative count: "<<qua.neg_one_count<<std::endl<<std::endl;
        ++counter;
    }
	

	for(auto qua: quadratics){
		if(qua.pos_one_count-qua.neg_one_count!=2){
			return false;
		}
	}
	return true;
}

void quadratics_check(std::vector<std::vector<char> >& sequences, std::vector<quadratic_eq>& quadratics, int& pos_index, int& neg_index,  std::vector<std::vector<int> >& qua_temp, int& seq, int& score_temp, int& n, int& qua_target){
	int step=1;
	for(auto qua: quadratics){
		std::vector<int> pos_neg_count;
		pos_neg_count.reserve(2);
		pos_neg_count.push_back(qua.pos_one_count);
		pos_neg_count.push_back(qua.neg_one_count);
		/*check for
		  conflict pairs:
		  (pos_index, (pos_index+step)%n)
		  ((neg_index-step)%n, neg_index)
		  
		  ((pos_index-step)%n, pos_index)
		  (neg_index, (neg_index+step)%n)*/
		
		//check for first conflict pair
		if(pos_index != (neg_index-step+n)%n){
			//if value was 1, now it's -1 and we minus score_temp by 2
			if(sequences[seq][pos_index]*sequences[seq][(pos_index+step)%n]==1){
				if(pos_neg_count[0]-pos_neg_count[1]>qua_target){
					score_temp=score_temp-2;
				}
				else{
					score_temp=score_temp+2;
				}
				--pos_neg_count[0];
				++pos_neg_count[1];
			}
			else{
				if(pos_neg_count[0]-pos_neg_count[1]<qua_target){
					score_temp=score_temp-2;
				}
				else{
					score_temp=score_temp+2;
				}
				--pos_neg_count[1];
				++pos_neg_count[0];
			}
			if(sequences[seq][(neg_index-step+n)%n]*sequences[seq][neg_index]==1){
				if(pos_neg_count[0]-pos_neg_count[1]>qua_target){
                    score_temp=score_temp-2;
                }
                else{
                    score_temp=score_temp+2;
                }
				--pos_neg_count[0];
				++pos_neg_count[1];
			}
			else{
				if(pos_neg_count[0]-pos_neg_count[1]<qua_target){
                    score_temp=score_temp-2;
                }
                else{
                    score_temp=score_temp+2;
                }
				--pos_neg_count[1];
				++pos_neg_count[0];

			}
		}
		//check for the other conflicts
		if((pos_index-step+n)%n != neg_index){
			//if value was 1, now it's -1 and we minus score_temp by 2
			if(sequences[seq][(pos_index-step+n)%n]*sequences[seq][pos_index]==1){
				if(pos_neg_count[0]-pos_neg_count[1]>qua_target){
                    score_temp=score_temp-2;
                }
                else{
                    score_temp=score_temp+2;
                }
				--pos_neg_count[0];				
				++pos_neg_count[1];
			}
			else{
				if(pos_neg_count[0]-pos_neg_count[1]<qua_target){
                    score_temp=score_temp-2;
                }
                else{
                    score_temp=score_temp+2;
                }
				--pos_neg_count[1];
				++pos_neg_count[0];
			}
			if(sequences[seq][neg_index]*sequences[seq][(neg_index+step)%n]==1){
				if(pos_neg_count[0]-pos_neg_count[1]>qua_target){
                    score_temp=score_temp-2;
                }
                else{
                    score_temp=score_temp+2;
                }
				--pos_neg_count[0];
				++pos_neg_count[1];
			}
			else{
				if(pos_neg_count[0]-pos_neg_count[1]<qua_target){
                    score_temp=score_temp-2;
                }
                else{
                    score_temp=score_temp+2;
                }
				--pos_neg_count[1];
				++pos_neg_count[0];
			}
		}
		qua_temp.push_back(pos_neg_count);
		++step;
		std::cout<<"score_temp is "<<score_temp<<std::endl;
	}
	return;
}	
	
void local_search(std::vector<std::vector<char> >& sequences, std::vector<std::vector<std::vector<int> > >& sequences_indices, std::vector<quadratic_eq>& quadratics, int& n, int& seq_count, int& quadratic_count, int& qua_target){

	int score=0; //want to make score 0
	int score_min;
	int pos_min;
	int neg_min;
	int seq_min;
	std::vector<std::vector<int> > qua_min;
	int score_temp;
	int pos_rand;
	int neg_rand;
	int seq_rand;
	
	//find current score
	for(auto qua: quadratics){
        score+=abs(qua.pos_one_count-qua.neg_one_count-qua_target);
	}
	score_min=score;
	score_temp=score;

	/*main loop*/
	int iteration=0;
	while(!verify_solution(quadratics, sequences_indices, sequences)){
		++iteration;
		std::cout<<"current score is: "<<score<<std::endl;

		//reset
		if(score == 0){
			//std::cout<<"stochastic restart"<<std::endl;
		}
		else{	
			/*find all neighbour states*/
			//for each sequence
			for(int seq=0; seq<seq_count; seq++){
				//check all pairs of 1 and -1's that can be flipped
				for(auto pos_index: sequences_indices[seq][0]){
					for(auto neg_index: sequences_indices[seq][1]){
						//loop through each quadratic equation and check if new score is smaller
						score_temp=score;
						//int step=1;
						std::vector<std::vector<int> > qua_temp;
						quadratics_check(sequences, quadratics, pos_index, neg_index, qua_temp, seq, score_temp, n, qua_target);
						std::cout<<"new score: "<<score_temp<<std::endl;
						std::cout<<"flipped "<< pos_index <<" and "<<neg_index<<" from sequence "<<seq<<std::endl;
						//update current best
						if(abs(score_temp)<=abs(score_min)){
							score_min=score_temp;
							std::cout<<"score_min is: "<<score_min<<std::endl;
							seq_min=seq;
							pos_min=pos_index;
							neg_min=neg_index;
							qua_min=qua_temp;
						}
					}
				}
			}
		}
		/* prob. need to check for local minimum here */
		//if no better configuration found
		if(score==score_min){
			std::vector<std::vector<int> > qua_temp;
			//randomly pick a sequence
			seq_rand=rand()%seq_count;
			//randomly pick a pair of positive one and negtive one to switch
			pos_rand=sequences_indices[seq_rand][0][rand()%(sequences_indices[seq_rand][0].size()-1)];
			neg_rand=sequences_indices[seq_rand][1][rand()%(sequences_indices[seq_rand][1].size()-1)];
			quadratics_check(sequences, quadratics, pos_rand, neg_rand, qua_temp, seq_rand, score_temp, n, qua_target);
			seq_min=seq_rand;
			pos_min=pos_rand;
			neg_min=neg_rand;
			score_min=score_temp;
			qua_min=qua_temp;
		}

		score=score_min;
		std::cout<<"score_min is "<<score_min<<std::endl;
		//update sequences
		std::cout<<"fliping "<<pos_min<<" "<<neg_min<<" from sequence "<<seq_min<<std::endl;
		sequences[seq_min][pos_min]=-1;
		sequences[seq_min][neg_min]=1;
		//update sequences indices list
		sequences_indices[seq_min][0].erase(std::remove(sequences_indices[seq_min][0].begin(), sequences_indices[seq_min][0].end(),pos_min), sequences_indices[seq_min][0].end());
		sequences_indices[seq_min][1].push_back(pos_min);
		sequences_indices[seq_min][1].erase(std::remove(sequences_indices[seq_min][1].begin(), sequences_indices[seq_min][1].end(),neg_min), sequences_indices[seq_min][1].end());
		sequences_indices[seq_min][0].push_back(neg_min);

		//update quadratics (will be taken out) and pos_one_count and neg_one_count
		int step_temp;
		int temp;
		for(int i=0; i<quadratic_count; i++){
			quadratics[i].pos_one_count=qua_min[i][0];
			quadratics[i].neg_one_count=qua_min[i][1];
			step_temp=i+1;
			quadratics[i].quadratic[seq_min*n+pos_min]=quadratics[i].quadratic[seq_min*9+pos_min]*(-1);
			quadratics[i].quadratic[seq_min*n+(neg_min-step_temp+n)%n]=quadratics[i].quadratic[seq_min*9+(neg_min-step_temp+n)%n]*(-1);
			quadratics[i].quadratic[seq_min*n+(pos_min-step_temp+n)%n]=quadratics[i].quadratic[seq_min*9+(pos_min-step_temp+n)%n]*(-1);
			quadratics[i].quadratic[seq_min*n+neg_min]=quadratics[i].quadratic[seq_min*9+neg_min]*(-1);
		}
	}
	//testing 
	std::cout<<"current score is: "<<score<<std::endl;

	std::cout<<std::endl<<"LINEAR EQUATION"<<std::endl<<std::endl;                        
    for(auto a: sequences[0]){                                                            
		std::cout<<(int)a<<" ";                                                           
    }                                                        
	std::cout<<std::endl;                                                                
    for(auto b: sequences[1]){                                                            
		std::cout<<(int)b<<" ";                                                           
    }                                                                                     
	std::cout<<std::endl<<std::endl; 

	std::cout<<"iterations used: "<<iteration<<std::endl;
}

int main(int argc, char *argv[]){
	int n=atoi(argv[1]);
	int qua_target=2; //target number that all the qoadratic equation will equal to
    int seq_count=2;
	int quadratic_count=(n-1)/2; //number of quadratic equations
   	std::vector<int> lin_targets;
	/*
	  initialization
	*/

	srand(time(NULL));
		
	//testing
	lin_targets.push_back(atoi(argv[2]));
	lin_targets.push_back(atoi(argv[3]));

	//initialize sequences with linear constraints
	std::vector<std::vector<char> > sequences;
	std::vector<std::vector<std::vector<int> > > sequences_indices(seq_count, std::vector<std::vector<int> >(2));
	sequences.reserve(seq_count);
	for(int i=0; i<seq_count; i++){
		//for each sequence
		sequences[i].reserve(n);
		int pos_one_count_temp=(n+lin_targets[i])/2;
		int neg_one_count_temp=n-pos_one_count_temp;
		
		//push 1's
		for(int j=0; j<pos_one_count_temp; j++){
			sequences[i].push_back(1);
			sequences_indices[i][0].push_back(j);
		}
		//push -1's
		for(int k=0; k<neg_one_count_temp; k++){
            sequences[i].push_back(-1);
			sequences_indices[i][1].push_back(k+pos_one_count_temp);
        }
	}

	//initialize quadratics with quadratic constrains
	std::vector<quadratic_eq> quadratics;
    quadratics.reserve(quadratic_count);
	for(int i=0; i<quadratic_count; i++){
		quadratics.emplace_back(quadratic_eq());
		quadratics[i].quadratic.reserve(seq_count*n);
	}
	init_quadratics(sequences, quadratics, n, seq_count, quadratic_count);

	/*local search*/
	local_search(sequences, sequences_indices, quadratics, n, seq_count, quadratic_count, qua_target);	

	return 0;
}
