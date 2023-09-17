#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <cassert>
#include <exception>

std::string get_random_dna_string(int64_t length, int64_t alphabet_size){ // For testing
    std::string s;
    assert(alphabet_size >= 1 && alphabet_size <= 4);
    char alphabet[4] = {'A','T','G','C'};
    for(int64_t i = 0; i < length; i++){
        s.push_back(alphabet[rand() % alphabet_size]);
    }
    return s;
}

std::string get_random_string(int64_t length, int64_t alphabet_size){ // For testing
    std::string s;
    for(int64_t i = 0; i < length; i++){
        int64_t r = rand() % alphabet_size;
        s += 'a' + r;
    }
    return s;
}

std::string get_random_filename(){
    return get_random_string(10, 26);
}

void write_as_fastq(const std::vector<std::string>& seqs, std::string fastq_filename){
    std::ofstream out(fastq_filename);
    if(!out.good()) throw std::runtime_error("Error opening file " + fastq_filename);
    for(const std::string& S : seqs){
        out << "@\n" << S << "\n+\n" << std::string(S.size(), 'I') << "\n";
    }
}

int64_t cur_time_millis(){
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
}