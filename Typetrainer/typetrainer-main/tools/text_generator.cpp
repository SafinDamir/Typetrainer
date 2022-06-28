#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <unistd.h>
#include<random>
#include <string>
#include <cctype>
#include <time.h> //to use time for seed generating

std::string possessive(const char gender){
    std::string poss;
    switch (gender) {
        case 'm': {
            poss = "his";
            break;
        }
        case 'f': {
            poss = "her";
            break;
        }
        case 'n': {
            poss = "their";
            break;
        }
        default: {
            std::cerr << "Gender is unknown! \n";
	        exit(1);
        }
    }
    return poss;
}


void structure1(const int difficulty, std::ofstream& wfile, const std::vector<std::vector<std::string>>& words, std::string& sentence){

    std::string verb;
    std::string subj;
    std::string poss;
    std::string obj;
    std::string adj;
    std::string punct = ".";
    if (difficulty == 1){
        punct = "";
    }
    
    char gender;

    int elem = rand() % words[0].size();
    subj = words[0][elem];
    subj.pop_back();
    subj.pop_back();
    gender = words[0][elem][words[0][elem].size() - 1];
    poss = possessive(gender);

    verb = words[1][rand() % words[1].size()]; //verb
    obj = words[2][rand() % words[2].size()]; //object
    adj = words[3][rand() % words[3].size()]; //adjective
    sentence = subj + ' ' + verb + ' ' + poss + ' ' + adj + ' ' + obj + punct;
    //std::cout << sentence << std::endl;
}

void structure2(const int difficulty, std::ofstream& wfile, const std::vector<std::vector<std::string>>& words, std::string& sentence){
    std::string str1;
    std::string str2; 
    std::string connector;
    std::string comma = ",";
    if (difficulty == 1){
        comma = "";
    }
    structure1(difficulty, wfile, words, str1);
    structure1(difficulty, wfile, words, str2);
    if (difficulty != 1){
        str1.erase(str1.size() - 1); //get rid of the punctuation mark
    }
    connector = words[4][rand() % words[4].size()];
    sentence = str1 + comma + ' ' + connector + ' ' + str2;
}

void compose(const int num, const int difficulty, std::ofstream& wfile, const std::vector<std::vector<std::string>>& words){
    std::string sentence;
    for (auto i = 0; i < num; i++){
        if (i % 2 == 0){ structure1(difficulty, wfile, words, sentence); }
        else{ structure2(difficulty, wfile, words, sentence); }  
        wfile << sentence << std::endl;
    }
}

int main(int argc, char *argv[]){
    srand (time(NULL)); //seeding random numbers with the time

    if (argc < 3) {
        std::cerr << "Not given a number of sentences or a diffuculty level!\nUsage: ./text_generator <num> <difficulty> [output filename]";
	exit(1);
    }

    int num = std::stoi(argv[1]);
    int difficulty = std::stoi(argv[2]);

    if ((difficulty > 3) || (difficulty < 1)){
        std::cerr << "The difficulty level should be between 1 and 3! \n";
	    exit(1);
    }

    std::string output_filename;
    std::string source_filename;

    source_filename = "../tools/source_texts/level" + std::to_string(difficulty);

    if (argc != 4){
        output_filename = "../texts/generated_text"; //output filename is not specified
    } 
    else {
        output_filename = argv[3];
    }

    std::string line;
    std::string word = "";
    std::vector<std::string> wordline;
    std::vector<std::vector<std::string>> words;

    std::ifstream rfile(source_filename + ".txt");
    std::ofstream wfile(output_filename + ".txt");

    if (!rfile.is_open() || !wfile.is_open()){
    	std::cerr << "Unable to open/create a text file!";
    	exit(1);
    }

    while (std::getline(rfile, line)) {  
        if (line.size() > 0) {
            for (char c : line) {
                if (c == ' ') {
                    wordline.push_back(word);               
                    word = "";
                } 
                else if (c == '\r'){
                } 
                else {
                    word = word + c;
                }
            }
            wordline.push_back(word);
            word = "";
            words.push_back(wordline);
            wordline = {};
        }
    }

    compose(num, difficulty, wfile, words);

    wfile.close();
    rfile.close();

    return 0;
}
