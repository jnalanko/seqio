#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <cassert>
#include <exception>
#include <iostream>
#include "stdlib_printing.hh"

class TestLogger{
    public:
    bool verbose = false;

    // This is to make std::endl compile and work with the logger
    TestLogger& operator<<(std::ostream& (*f)(std::ostream&)){
        if(verbose) f(std::cerr);
        return *this;
    }
};

template <typename T>
TestLogger& operator<<(TestLogger& L, const T& t){
    if(L.verbose) std::cerr << t;
    return L;
}

std::string get_random_dna_string(int64_t length, int64_t alphabet_size);
std::string get_random_string(int64_t length, int64_t alphabet_size);
std::string get_random_filename();

void write_as_fastq(const std::vector<std::string>& seqs, std::string fastq_filename);
void write_as_fasta(const std::vector<std::string>& seqs, std::string fastq_filename);
void write_seqs_to_fasta_file(const std::vector<std::string>& v, const std::string& filename);
void write_seqs_to_fasta_file(const std::vector<std::string>& seqs, const std::vector<std::string>& headers, const std::string& filename);
int64_t cur_time_millis();
std::string string_to_temp_file(const std::string& S, const std::string& suffix = "");
const std::string generate_random_kmer(int64_t k);
std::string get_rc(std::string S);