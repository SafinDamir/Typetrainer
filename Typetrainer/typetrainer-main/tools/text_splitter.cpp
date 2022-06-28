#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <cctype>
#include <string>
#include <iomanip>


int main(int argc, char *argv[]){

    if (argc < 3) {
        std::cerr << "Not given a file to split!\nUsage: ./text_splitter <length> <filename> [split filename]";
	exit(1);
    }
    
    std::string output_line;
    std::string current_line; // stack
    std::string line;
    std::string token;
    char c;
    
    std::string filename = argv[2];


    std::string split_filename;
    
    if (argc != 4) { //split filename not specified
	    split_filename = "../texts/splitted_text";
    }
    else { split_filename = argv[3]; }
    
    std::ifstream rfile(filename + ".txt");
    std::ofstream wfile(split_filename + ".txt");
    
    const int max_length = std::stoi(argv[1]);
    const int recommended_length = static_cast<int>(std::stoi(argv[1]));
    const int recommended_gap = static_cast<int>(std::stoi(argv[1])*0.25);
    

    if (!rfile.is_open()){
    	std::cerr << "Unable to open the input file!" << std::endl;
    	exit(2);
    } 

    if (!wfile.is_open()){
    	std::cerr << "Unable to create the output file!" << std::endl;
    	exit(2);
    } 
    
    std::getline(rfile, current_line);
    while (std::getline(rfile, line)) {   
        if (line.size() > 0) {
            current_line = current_line + " " + line;
        }
    }

    output_line = "";
    if (current_line.size() > 0) {
        for (char c : current_line) {
            if ((c == ';') || (c == '.') || (c == '!') || (c == '?') || (c == ',')) {
                output_line = output_line + c;
                if (output_line.size() > (recommended_length - 2 * recommended_gap)) {
                    wfile << output_line << std::endl;
                    output_line = "";
                    current_line.erase(0, 1);
                }
            }
            else if (c == ' ') {
                if (output_line.size() > recommended_length - recommended_gap) {
                    wfile << output_line << std::endl;
                    output_line = "";
                }
                else { output_line = output_line + c; }
            }
            else if (c=='\n') { wfile << std::endl; }
            else { output_line = output_line + c;}
            
            if (output_line.size() > (max_length - 2)) {
                wfile << output_line << std::endl;
                output_line = "";
            }
        }
    }
    wfile << output_line.c_str();

    wfile.close();
    rfile.close();
    return 0;
}
