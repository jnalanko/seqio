#include "SeqIO/SeqIO.hh"
#include "common.hh"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <filesystem>

using namespace std;

void benchmark_buffered_stream(){
    string data = get_random_string(1e6 * 50, 10);
    string outfile = get_random_string(10, 26);
    ofstream out(outfile, ios::binary);
    out.write(data.data(), data.size());
    out.flush();

    ifstream in(outfile, ios::binary);
    seq_io::Buffered_ifstream<ifstream> bin(outfile, ios::binary);
    
    string data2(data.size(), '\0');

    int64_t t0 = cur_time_millis();
    char c = 0;
    for(int64_t i = 0; i < (int64_t)data.size(); i++){
        bin.get(&c);
        data2[i] = c;
    }
    int64_t t1 = cur_time_millis();
    double seconds = (t1 - t0) / 1000.0;
    cout << "Read " << data2.size() << " bytes" << endl;
    cout << "Raw buffered bytes by byte: " << data.size() / 1e6 / seconds << " MB/s" << endl;

    std::filesystem::remove(outfile);
}

void benchmark_seqio(){

    // Generate 10 megabases of reads of length 100
    vector<string> reads;
    int64_t total_len = 0;
    for(int64_t i = 0; i < 100000; i++){
        reads.push_back(get_random_dna_string(100, 4));
        total_len += reads.back().size();
    }

    string fastq = get_random_string(10, 26);
    string fasta = get_random_string(10, 26);

    write_as_fastq(reads, fastq);
    write_as_fasta(reads, fasta);

    //
    // FASTQ
    //
    seq_io::Reader sr(fastq, seq_io::FASTQ);
    int64_t sr_t0 = cur_time_millis();

    int64_t counter = 0;
    while(true){
        int64_t len = sr.get_next_read_to_buffer();
        if(len == 0) break;
        counter += len;
    }
    int64_t sr_t1 = cur_time_millis();
    double sr_seconds = (sr_t1 - sr_t0) / 1000.0;
    cout << "FASTQ: Total sequence length read: " << counter << endl;
    cout << total_len / 1e6 / sr_seconds << " MBase/s" << endl;

    cout << "--" << endl;
    //
    // FASTA
    //
    seq_io::Reader sr2(fasta, seq_io::FASTA);
    sr_t0 = cur_time_millis();

    counter = 0;
    while(true){
        int64_t len = sr2.get_next_read_to_buffer();
        if(len == 0) break;
        counter += len;
    }
    sr_t1 = cur_time_millis();
    sr_seconds = (sr_t1 - sr_t0) / 1000.0;
    cout << "FASTA: Total sequence length read: " << counter << endl;
    cout << total_len / 1e6 / sr_seconds << " MBase/s" << endl;

    std::filesystem::remove(fastq);
    std::filesystem::remove(fasta);

}

int main(){
    benchmark_seqio();
    cout << "---" << endl;
    benchmark_buffered_stream();
}
