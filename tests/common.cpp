#include "common.hh"
#include <algorithm>
#include <fstream>

using namespace std;

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

void write_as_fasta(const std::vector<std::string>& seqs, std::string fastq_filename){
    std::ofstream out(fastq_filename);
    if(!out.good()) throw std::runtime_error("Error opening file " + fastq_filename);
    for(const std::string& S : seqs){
        out << ">\n" << S << "\n";
    }
}


void write_seqs_to_fasta_file(const std::vector<std::string>& v, const std::string& filename){
    std::ofstream out(filename);
    for(std::string S : v) out << ">\n" << S << "\n";
}

void write_seqs_to_fasta_file(const std::vector<std::string>& seqs, const std::vector<std::string>& headers, const std::string& filename){
    std::ofstream out(filename);
    assert(seqs.size() == headers.size());
    for(int64_t i = 0; i < (int64_t)seqs.size(); i++)
        out << ">" << headers[i] << "\n" << seqs[i] << "\n";
}

int64_t cur_time_millis(){
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
}

std::string string_to_temp_file(const std::string& S, const std::string& suffix){
    std::string filename = get_random_filename() + suffix;
    std::ofstream out(filename);
    out.write(S.data(), S.size());
    return filename;
}

const std::string generate_random_kmer(int64_t k) {
    std::string s;
    for (int64_t i = 0; i < k; i++) {
        const int r = std::rand() % 4;
        switch (r) {
            case (0): s += 'A'; break;
            case (1): s += 'C'; break;
            case (2): s += 'G'; break;
            case (3): s += 'T'; break;
            default: break;
        }
    }
    return s;
}

std::string get_rc(std::string S){
    std::reverse(S.begin(), S.end());
    for(char& c : S){
        if(c == 'A') c = 'T';
        else if(c == 'T') c = 'A';
        else if(c == 'G') c = 'C';
        else if(c == 'C') c = 'G';
    }
    return S;
}