#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include <utility>
#include <set>


std::set<std::string> stringset;


void permfunc(std::string& word0, std::vector<std::string>& out){
	
	for(int j = 0; j < word0.size()-1; j++){
			std::vector<char> new0;
			for(int l = 0; l < word0.size(); l++){
				new0.push_back(word0[l]);
				
			}
			new0.push_back('\0');
			new0[j] = word0[j+1];
			new0[j+1] =word0[j];
			
			std::string strs((char*) new0.data());
			
			//std::cout<<strs<<std::endl;
			
			if(stringset.find(strs) != stringset.end()) continue;
			
			stringset.insert(strs);
			
			out.push_back(strs);
			//permfunc(strs);
		
	}
	
}


void genwords(std::string& word){
	std::vector<std::string> in;
	std::vector<std::string>* vptr = &in;
	permfunc(word, in);
	int sz = in.size();
    std::vector<std::string> in1;
    int stp =0;
	while(true){l

        int prvsz = in1.size();
		for(int i = stp; i < sz; i++ ){
			std::string newstr = (*vptr)[i];

			permfunc(newstr, in1);
			
		}
		if(prvsz != 0) stp = prvsz;
        int cursz = in1.size();
        if(cursz == prvsz) break;
		sz = in1.size();
		vptr = &in1;
		
	
	}
}




int main(int argc, char** argv){
	
	char* word;
	
	if(argc > 1) word = argv[1];
	
	int wordlen = strlen(word);
	printf("Arg 1 is: %s and its length is %d \n", word, wordlen );
	
	// loading dictionary files
	
	std::fstream dictfile("./dictionary.txt");
	
	if(dictfile.is_open()) std::cout<<"Yes! File is succesfully opened!"<<std::endl;
	else std::cout<<"failed to open file"<<std::endl;
	
	dictfile.seekg(0, std::ios_base::end);
	unsigned long long size = dictfile.tellp();
	std::cout<<"ghhhhhhhh"<<size<<std::endl;
    std::string str;
    //str.reserve(size);
	
	dictfile.seekp(0);
	
	std::vector<std::string> words;
	while(!dictfile.eof()){
		char buff[255];
		if(dictfile.getline(&buff[0], 255, '\n')){
			std::string str(buff);
			//std::cout<<str.size()<<std::endl;
			words.push_back(str);
		}
		
	}
	std::cout<<"string file pushed and num of word is "<< words.size()<<std::endl;


 	//perm of words hello=> 111, 112, 113,  0 idx ,    211, 311, heyo, ehyo, hyeo, heoy, 
                          //121, 122, 123,  1 idx 111, 121, 131, heyo, eyho, ehoy, eoyh, eyoh, eyeo
                          //131, 132, 133,  2 idx 111, 112, 113  yheo, heyo, hyoe, 
						  //211, 212, 113,  3 idx                ehoy, hoey, heyo  yoeh
																											
//heyo,hyoe heoy eyho ehoy hoey yeho ehyo eyoh eohy ohey hyeo hoey yheo yhoe yohe oyhe yoeh oyeh oeyh oehy eoyh yeoh hoye
																
																
		//helloWorld   hel heo hew her  hed wll elw elw- 
		//
		std::string tmpstr(word, wordlen);
		
		genwords(tmpstr);
		
		
		
		//extrac words starting from len 3 to wordlen-1;
		std::set<std::string> newsets;
		
		for(int p = 3; p < wordlen;  p++){
			for(const auto& s: stringset){
				std::string newword(s.c_str(), p);
				//std::cout<<"created "<<newword<<std::endl;
				if(newsets.find(newword) == newsets.end()) newsets.insert(newword);
			}
		}
		
		for(const auto& s: newsets){
			stringset.insert(s);
		}
		
		
		
		
		
		//std::string tmpstr(word, x);
		
			//permfunc(tmpstr);
		
		//std::cout<<"Printing sets "<<std::endl;
		
		//for(const std::string& ss: stringset){
		//	std::cout<<ss<<std::endl;
		//}
		
		std::set<std::string> found_match;
		for(const auto& vq: stringset){
		for(auto& var: words){
		
			if(vq.size() == var.size() -1){
			if(strncmp(vq.c_str(), var.c_str(), vq.size()) == 0){ found_match.insert(vq); }
			}
		}
		}
		
		
		
		std::cout<<"word found in dict "<<std::endl;
		
		for(const std::string& ss: found_match){
			std::cout<<ss<<std::endl;
		}
		
	
	//}
	
	


	return 0;
}