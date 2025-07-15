#ifndef FUNC_FILE_H
#define FUNC_FILE_H

#include <bits/stdc++.h>
using namespace std;

class Assembler
{
	bool flag_VH_present = false;
	bool flag_register_typo = false;
	bool flag_instruction_typo = false;
	bool flag_illegal_imm = false;
	bool label_typo = false;
	bool flag_label_does_not_exist = false;

	int error_line_num = -1;
	int line_count = 0;
	int address = 0;
	int program_counter = 0;

	vector<string> B_type = {"beq", "bne", "blt", "bge", "bltu", "bgeu"};
	vector<string> U_type = {"lui", "auipc"};
	vector<string> J_type = {"jal"};
	vector<string> R_type = {"add", "sub", "sll", "slt", "sltu", "xor", "srl", "or", "and"};
   	vector<string> I_type={"lw","addi","sltiu","jalr"};
   	vector<string> S_type={"sw"};
	
	// Instruction encoding dictionary
	unordered_map<string, string> instruction_encoding = {
	    // R-type instructions
	    {"add", "0110011"}, {"sub", "0110011"}, {"sll", "0110011"},
	    {"slt", "0110011"}, {"sltu", "0110011"}, {"xor", "0110011"},
	    {"srl", "0110011"}, {"or", "0110011"}, {"and", "0110011"},
	    // I-type instructions
	    {"lw", "0000011"}, {"addi", "0010011"}, {"sltiu", "0010011"},
	    {"jalr", "1100111"},
	    // S-type instructions
	    {"sw", "0100011"},
	    // B-type instructions
	    {"beq", "1100011"}, {"bne", "1100011"}, {"blt", "1100011"},
	    {"bge", "1100011"}, {"bltu", "1100011"}, {"bgeu", "1100011"},
	    // U-type instructions
	    {"lui", "0110111"}, {"auipc", "0010111"},
	    // J-type instructions
	    {"jal", "1101111"}
	};

	// Register Mapping
	unordered_map<string, string> register_mapping = {
		{"zero", "00000"},
		{"ra", "00001"},
		{"sp", "00010"},
		{"gp", "00011"},
		{"tp", "00100"},
		{"t0", "00101"},

		{"t1", "00110"},
		{"t2", "00111"},

		{"s0", "01000"},
		{"fp", "01000"},

		{"s1", "01001"},

		{"a0", "01010"},
		{"a1", "01011"},

		{"a2", "01100"},
		{"a3", "01101"},
		{"a4", "01110"},
		{"a5", "01111"},
		{"a6", "10000"},
		{"a7", "10001"},

		{"s2", "10010"},
		{"s3", "10011"},
		{"s4", "10100"},
		{"s5", "10101"},
		{"s6", "10110"},
		{"s7", "10111"},
		{"s8", "11000"},
		{"s9", "11001"},
		{"s10", "11010"},
		{"s11", "11011"},

		{"t3", "11100"},
		{"t4", "11101"},
		{"t5", "11110"},
		{"t6", "11111"},

	};
	unordered_map<string,string> funct7_encoding = {
	    {"add", "0000000"}, {"sub", "0100000"}, {"sll", "0000000"},
	    {"slt", "0000000"}, {"sltu", "0000000"}, {"xor", "0000000"},
	    {"srl", "0000000"}, {"or", "0000000"}, {"and", "0000000"},
	};

	unordered_map<string,string> funct3_encoding = {
	    {"add", "000"}, {"sub", "000"}, {"sll", "001"},
	    {"slt", "010"}, {"sltu", "011"}, {"xor", "100"},
	    {"srl", "101"}, {"or", "110"}, {"and", "111"},
	    {"lw", "010"}, {"addi", "000"}, {"sltiu", "011"},
	    {"jalr", "000"}, {"beq", "000"}, {"bne", "001"},
	    {"blt", "100"}, {"bge", "101"}, {"bltu", "110"},
	    {"bgeu", "111"}, {"sw", "010"}
	};

	public:

	string imm_B_Type_1(const string instruction);

	string imm_B_Type_2(const string instruction);

	string imm_U_Type(const string instruction);

	string imm_I_Type(const string instruction);

	string imm_S_Type_1(const string instruction);

	string imm_S_Type_2(const string instruction);

	string imm_J_Type(const string instruction);

	void read_and_write(string input_file_name, string output_file_name);

	void check_errors(string output_file_name);

	void store_labels(string input_file_name);

	int stringToDecimal(const std::string&);

	string convertingToBinary(int n);

	string sign_extension(int bits, string bin);
};

class simulator
{
	vector<string> registers;
	vector<string> data_memory;
	vector<string> input;

 	//register address
	unordered_map<string,int> register_address_mapping = {
	{"00000",0},
	{"00001",1},
	{"00010",2},
	{"00011",3},
	{"00100",4},
	{"00101",5},
	{"00110",6},
	{"00111",7},
	{"01000",8},
	{"01001",9},
	{"01010",10},
	{"01011",11},
	{"01100",12},
	{"01101",13},
	{"01110",14},
	{"01111",15},
	{"10000",16},
	{"10001",17},
	{"10010",18},
	{"10011",19},
	{"10100",20},
	{"10101",21},
	{"10110",22},
	{"10111",23},
	{"11000",24},
	{"11001",25},
	{"11010",26},
	{"11011",27},
	{"11100",28},
	{"11101",29},
	{"11110",30},
	{"11111",31}
	};

	public:

	simulator();

	long long twos_comp(string binary_value);

	long long unsigned_str(string binary_value);

	long long signed_str(string binary_value);

	string convertingToBinary(long long n);

	string sign_extension(int bits, string bin);

	string bin_to_hex(string bin);
	
	void read(string input_file_name);
	
	void write(string output_file_name);
};

#endif
