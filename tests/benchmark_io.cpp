#include "SeqIO.hh"
#include "common.hh"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>

using namespace std;

int main(){

    // Generate 10 megabases of reads of length 100
    vector<string> reads;
    int64_t total_len = 0;
    for(int64_t i = 0; i < 100000; i++){
        reads.push_back(get_random_dna_string(100, 4));
        total_len += 100;
    }

    // Create a new fasta file for each so avoid caching effects
    string fastq1 = get_random_string(10, 26);
    string fastq2 = get_random_string(10, 26);
    string fastq3 = get_random_string(10, 26);

    write_as_fastq(reads, fastq1);
    write_as_fastq(reads, fastq2);
    write_as_fastq(reads, fastq3);

    // Unbuffered

    SeqIO::Reader sr(fastq1, SeqIO::FASTQ);
    int64_t sr_t0 = cur_time_millis();

    int64_t counter = 0;
    while(true){
        int64_t len = sr.get_next_read_to_buffer();
        if(len == 0) break;
        counter += len;
    }
    int64_t sr_t1 = cur_time_millis();
    double sr_seconds = (sr_t1 - sr_t0) / 1000.0;
    cout << "Total sequence length read: " << counter << endl;
    cout << total_len / 1e6 / sr_seconds << " Mbp/s" << endl;

}