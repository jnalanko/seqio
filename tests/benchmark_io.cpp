#include "SeqIO.hh"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>

using namespace std;

string get_random_dna_string(int64_t length, int64_t alphabet_size){ // For testing
    string s;
    assert(alphabet_size >= 1 && alphabet_size <= 4);
    char alphabet[4] = {'A','T','G','C'};
    for(int64_t i = 0; i < length; i++){
        s.push_back(alphabet[rand() % alphabet_size]);
    }
    return s;
}

string get_random_string(int64_t length, int64_t alphabet_size){ // For testing
    string s;
    for(int64_t i = 0; i < length; i++){
        int64_t r = rand() % alphabet_size;
        s += 'a' + r;
    }
    return s;
}

void write_as_fastq(const vector<string>& seqs, string fastq_filename){
    std::ofstream out(fastq_filename);
    if(!out.good()) throw std::runtime_error("Error opening file " + fastq_filename);
    for(const string& S : seqs){
        out << "@\n" << S << "\n+\n" << string(S.size(), 'I') << "\n";
    }
}

int64_t cur_time_millis(){
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
}

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