
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <string>
#include <sstream>
#include <fstream>

#include "./include.h"

using namespace std;

class exec{
	public:
		int place;
		vector<unsigned char> program;

		exec(vector<unsigned char> program){
			this->place = 0;
			this->program = program;
		}

		int next(){
			try{
				return this->program[this->place++];
			}catch (int e){
				return STP;
			}
		}

		void set(int val){
			this->place=val;
		}
};

class scope{
	public:
		unordered_map<int,variable *> vars = {};
		scope * parent_scope;
		scope(scope * parent){

		}

		void new_var(variable * value){
			// this->vars.insert({name,value});
		}

		variable * get_var(int address){
			return vars[address];
		}
};

class Scopes{
	public:
		stack<scope * > scopes;
		scope * bottom;
		
		Scopes(){

		}

		void exit_scope(){
			if(this->scopes.top() == this->bottom){
				this->bottom = NULL;
			}
			this->scopes.pop();
		}

		scope * current(){
			return this->scopes.top();
		}

		void enter_scope(){
			if(this->bottom == NULL){
				this->bottom = this->scopes.top();
			}

			this->scopes.push(	
				new scope(
					this->scopes.top()
				)
			);
		}
};



int concat(vector<int> vals){



	int val = vals[0];
	for (int i = 1; i < vals.size();i++){
		val<<=8;
		val += (vals[i]);
	}
	return val;
}

void execute(vector<unsigned char> program, map<int,variable*> constants){

	exec executor = exec(program);
	Scopes * scopes = new Scopes();
	stack<variable *> frame;
	bool running = true;
	
	while(running){
		int instruction = executor.next();
		cout<< instruction<<endl;
		cout<< frame<<endl;

		switch(instruction){
			
			case LV:{
				vector<int> args;
				for (int i = 0; i < 4; ++i)
				{
					args.push_back(executor.next());
				}
			
				frame.push(scopes->current()->get_var(concat(args)));
				break;
			}

			case LC:{
				vector<int> args;
				for (int i = 0; i < 4; ++i)
				{
					args.push_back(executor.next());
				}
				
				frame.push(constants[concat(args)]);
				break;
			}

			case SV:{
				vector<int> args;
				for (int i = 0; i <= 4; ++i)
				{
					args.push_back(executor.next());
				}
				scopes->current()->new_var(frame.top());
				break;
			}

			case ADD:{
				variable * temp1 = frame.top();
				frame.pop();
				variable * temp2 = frame.top();
				frame.pop();
				frame.push(temp2->_add(temp1));
				break;
			}

			case SUB:{
				variable * temp1 = frame.top();
				frame.pop();
				variable * temp2 = frame.top();
				frame.pop();
				frame.push(temp2->_sub(temp1));
				break;
			}

			case POW:{
				variable * temp1 = frame.top();
				frame.pop();
				variable * temp2 = frame.top();
				frame.pop();
				frame.push(temp2->_pow(temp1));
				break;
			}
			
			case DIV:{
				variable * temp1 = frame.top();
				frame.pop();
				variable * temp2 = frame.top();
				frame.pop();
				frame.push(temp2->_div(temp1));
				break;
			}
			
			case MUL:{
				variable * temp1 = frame.top();
				frame.pop();
				variable * temp2 = frame.top();
				frame.pop();
				frame.push(temp2->_mul(temp1));
				break;
			}

			case UNARY_NEG:{
				variable * temp1 = frame.top();
				frame.pop();
				frame.push(temp1->_unary_neg());
				break;
			}			

			case PT:{
				frame.pop();
				break;
			}

			case STP:{
				running = false;
				break;
			}
			case NOP:{
				break;
			}

			default:{cout<<"ERROR"<<endl;break;}
		}
	}
}


// vector<int> fromFileToArray( const string & fileName )
// {
// 	vector<int> data = {};	
// 	ifstream stream;
// 	stream.open(fileName, std::ios_base::binary);
// 	if (!stream.bad()) {
// 		std::cout << std::hex;
// 		std::cout.width(2);

// 		while (!stream.eof()) {
// 			unsigned char c;
// 			stream >> c;
// 			data.push_back(static_cast<int>(c));
// 		}
// 	}
// 	stream.close();
// 	return data;
// }

// int main(int argc, char *argv[]){
// 	vector<int> program = fromFileToArray(argv[1]);
// 	// for (int i = 0; i < data.size(); i++)
// 	// {
// 	// 	cout<<data[i]<<endl;
// 	// }
// 	// cout<<endl;

// 	vector<variable*> constants = {new int_var(2),new int_var(3)};

// 	exec executor = exec(program);
// 	Scopes * scopes = new Scopes();
// 	stack<variable *> frame;
	

// 	while(true){
// 		int instruction = executor.next();
// 		cout<< instruction<<endl;
// 		cout<< frame<<endl;

// 		switch(instruction){
			
// 			case LV:{
// 				vector<int> args;
// 				for (int i = 0; i <= 4; ++i)
// 				{
// 					args.push_back(executor.next());
// 				}
			
// 				frame.push(scopes->current()->get_var(concat(args)));
// 				break;
// 			}

// 			case LC:{
// 				vector<int> args;
// 				for (int i = 0; i <= 4; ++i)
// 				{
// 					args.push_back(executor.next());
// 				}
			
// 				frame.push(constants[concat(args)]);
// 				break;
// 			}

// 			case SV:{
// 				vector<int> args;
// 				for (int i = 0; i <= 4; ++i)
// 				{
// 					args.push_back(executor.next());
// 				}
// 				scopes->current()->new_var(frame.top());
// 				break;
// 			}

// 			case ADD:{
// 				variable * temp1 = frame.top();
// 				frame.pop();
// 				variable * temp2 = frame.top();
// 				frame.pop();
// 				frame.push(temp2->_add(temp1));
// 				break;
// 			}

// 			case SUB:{
// 				variable * temp1 = frame.top();
// 				frame.pop();
// 				variable * temp2 = frame.top();
// 				frame.pop();
// 				frame.push(temp2->_sub(temp1));
// 				break;
// 			}
			
// 			case DIV:{
// 				variable * temp1 = frame.top();
// 				frame.pop();
// 				variable * temp2 = frame.top();
// 				frame.pop();
// 				frame.push(temp2->_div(temp1));
// 				break;
// 			}
			
// 			case MUL:{
// 				variable * temp1 = frame.top();
// 				frame.pop();
// 				variable * temp2 = frame.top();
// 				frame.pop();
// 				frame.push(temp2->_mul(temp1));
// 				break;
// 			}

// 			case PT:{
// 				frame.pop();
// 				break;
// 			}

// 			case STP:{
// 				goto exit;
// 				break;
// 			}
// 			case NOP:{
// 				break;
// 			}

// 		}
// 	}
// 	exit:
// 	return 0;
// }


