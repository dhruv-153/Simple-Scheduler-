#include <ctype.h>
#include <bits/stdc++.h>
using namespace std;

#include "func_file.h"

	unordered_map<string,int> labels;

	string Assembler::imm_B_Type_1(const string instruction)
	{
	    char imm12=instruction[instruction.size()-13];
	
	    string imm105=instruction.substr(instruction.size()-11,6); 
	
	    return string(1,imm12)+imm105;		
	}

	string Assembler::imm_B_Type_2(const string instruction)
	{
	    char imm11=instruction[instruction.size()-12];
	
	    string imm41=instruction.substr(instruction.size()-5,4); 
	
	    return imm41+string(1,imm11);		
	}

	string Assembler::imm_U_Type(const string instruction)
	{
	    string imm3112=instruction.substr(instruction.size()-32,20); 
	
	    return imm3112;		
	}

	string Assembler::imm_I_Type(const string instruction)
	{
	    string imm110=instruction.substr(instruction.size()-12,12);
	    return imm110;		
	}

	string Assembler::imm_S_Type_1(const string instruction)
	{
	    string imm115=instruction.substr(instruction.size()-12,7);
	    return imm115;		
	}

	string Assembler::imm_S_Type_2(const string instruction)
	{
	    string imm40=instruction.substr(instruction.size()-5,5); 
	    return imm40;		
	}

	string Assembler::imm_J_Type(const string instruction)
	{
	    char imm20=instruction[instruction.size()-21]; 
	    string imm101=instruction.substr(instruction.size()-11,10); 
	    char imm11=instruction[instruction.size()-12]; 
	    string imm1912=instruction.substr(instruction.size()-20,8);
	    
	    return string(1,imm20)+imm101+string(1, imm11)+imm1912; 		
	}
	
	int Assembler::stringToDecimal(const std::string& decimalString) {
	    int decimalNumber = 0;
	    int length = decimalString.length();
	
	
	    int num = 0;
	    if(decimalString[0]=='-') num = 1;
	    for (int i = num; i < length; ++i) {
	        decimalNumber += (decimalString[i] - '0') * pow(10, length - i - 1);
	    }
	
	    if(num==1) return -1*decimalNumber;
	    return decimalNumber;
	
	}

	string Assembler::convertingToBinary(int n) {
	
	    if (n < 0) {
		string binary= "";
		n *= -1;

		bool power_of_two = false;
		int x = n&(n-1);
		if(x==0) power_of_two = true;
		    
		int check = 0;
		while (n > 0) {
			int bit = n % 2;
			if(check==0 && bit==1) 
			{
				check = 1;
				binary = to_string(bit) + binary;
			}
			else if(check==0 && bit==0) binary = to_string(bit) + binary;
			else if(check==1) binary = to_string(bit^1) + binary;
			n = n/2;
		}
		if(power_of_two) return binary;
		return '1' + binary;
	    } else {
		string binary = "";
	        while (n > 0) {
			int bit = n % 2;
	           	binary = to_string(bit) + binary;
	            	n = n / 2;
	        }
		return '0' + binary;
	    }
	}


	string Assembler::sign_extension(int bits, string bin)
	{
		string res;
		int temp=bits-bin.size();
		if(bin[0]=='1')
		{
			while(temp>0)
			{
				res+="1";
				temp--;
			}
			res+=bin;
			return res;
		}
		else
		{
			while(temp>0)
			{
				res+="0";
				temp--;
			}
			res+=bin;
			return res;
		}
	}

	void Assembler::store_labels(string input_file_name)
	{
		ifstream inp;
		inp.open(input_file_name);
		if(!inp)
		{
			cerr<< "Input file not present!" <<endl;
			exit(0);
		}

		string instruction;
		int counter = 1;
		while(getline(inp,instruction))
		{
			if(instruction=="") continue;
			string first_word = "";
			int i=0;
			while(i<(int)instruction.size() && instruction[i]!=' ' && instruction[i]!=':') 
			{
				first_word += instruction[i];
				i++;
			}
			if(i<(int)instruction.size() && instruction[i]==':') 
			{
				if(i+1>=(int)instruction.size() || instruction[i+1]!=' ') 
				{
					label_typo = true;
					error_line_num = counter;
					return;
				}
				labels.insert({first_word, address});
			}else 
			{
				if(i+1>=(int)instruction.size() || instruction[i+1]==':')
				{
					label_typo = true;
					error_line_num = counter;
					return;
				}
			}
			address += 4;
			counter++;
		}

		inp.close();
	}

	void Assembler::read_and_write(string input_file_name, string output_file_name)
	{
		if(label_typo) return;
		ofstream op;
		op.open(output_file_name);
		if(!op.is_open())
		{
			cerr<< "Output file not present!" <<endl;
			exit(0);
		}
		
		ifstream inp;
		inp.open(input_file_name);
		if(!inp)
		{
			cerr<< "Input file not present!" <<endl;
			exit(0);
		}

		string instruction;
		while(getline(inp, instruction))
		{
			line_count++;
			if(instruction=="") continue;
			
			int i=0;
			string inst = "";
			while(i<(int)instruction.size() && instruction[i]==' ') i++;
			while(i<(int)instruction.size() && instruction[i]!=' ' && instruction[i]!=':')
			{
				inst += instruction[i];
				i++;
			}
			if(i<(int)instruction.size() && instruction[i]==':')
			{
				i += 2;
				inst = "";
				while(i<(int)instruction.size() && instruction[i]!=' ')
				{
					inst += instruction[i];
					i++;
				}
			}
			i++;

			if(instruction_encoding[inst]=="")
			{
				flag_instruction_typo = true;
				error_line_num = line_count;
				return;
			}
			
			//U-Type
			for(auto u: U_type)
			{
				if(inst == u)
				{
					string reg, num;
					while(i<(int)instruction.size() && instruction[i]!=',')
					{
						reg += instruction[i];
						i++;
					}

					i++;

					while(i<(int)instruction.size() && i!=(int)instruction.size() && instruction[i]!=' ')
					{
						if(!isdigit(instruction[i]))
						{
							flag_illegal_imm = true;
							error_line_num = line_count;
							return;
						}
						num += instruction[i];
						i++;
					}

					int temp = stringToDecimal(num);

					if((long long)temp >= (1LL<<31LL) || (long long)temp < (-1)*(1LL<<31LL))
					{
						flag_illegal_imm = true;
						error_line_num = line_count;
						return;
					}

					string imm = convertingToBinary(temp);
					imm = sign_extension(32, imm);
					
					if(register_mapping[reg]=="")
					{
						flag_register_typo = true;
						error_line_num = line_count;
						return;
					}

					op<< imm_U_Type(imm);
					op<< register_mapping[reg];
					op<< instruction_encoding[inst] <<endl;
					break;
				}
			}
			
			//J-Type
			for (auto u:J_type)
			{
				if(inst==u){
					string reg, label;
					while(i<(int)instruction.size() && instruction[i]!=',')
					{
						reg += instruction[i];
						i++;
					}

					i++;

					while(i<(int)instruction.size() && instruction[i]!='(' && instruction[i]!=' ')
					{
						label += instruction[i];
						i++;
					}
					int temp;
					if(label[0]=='-' || isdigit(label[0]))
					{
						for(int i=1; i<(int)label.size(); i++)
						{
							if(!isdigit(label[i]))
							{
								flag_illegal_imm = true;
								error_line_num = line_count;
								return;
							}
						}
						temp = stringToDecimal(label);
						if(temp >= (1<<20) || temp < (-1)*(1<<20))
						{
							flag_illegal_imm = true;
							error_line_num = line_count;
							return;
						}
					}else 
					{
						if(labels.find(label)==labels.end())
						{
							flag_label_does_not_exist = true;
							error_line_num = line_count;
							return;
						}
						temp = labels[label]-program_counter;
					}
					string imm = convertingToBinary(temp);
					imm = sign_extension(21, imm);
					
					if(register_mapping[reg]=="")
					{
						flag_register_typo = true;
						error_line_num = line_count;
						return;
					}
					
					op<< imm_J_Type(imm);
					op<< register_mapping[reg];
					op<< instruction_encoding[inst] <<endl;
					break;
				}
			}

			// B-Type
			for (auto u: B_type)
			{
				if(inst==u)
				{
					string reg1,reg2,label;

					while(i<(int)instruction.size() && instruction[i]!=',')
					{
						reg1+=instruction[i];
						i++;
					}
					i++;

					while(i<(int)instruction.size() && instruction[i]!=',')
					{
						reg2+=instruction[i];
						i++;
					}
					i++;

					while(i<(int)instruction.size() && instruction[i]!=' ')
					{
						label+=instruction[i];
						i++;
					}
					int temp;
					if(label[0]=='-' || isdigit(label[0]))
					{
						for(int i=1; i<(int)label.size(); i++)
						{
							if(!isdigit(label[i]))
							{
								flag_illegal_imm = true;
								error_line_num = line_count;
								return;
							}
						}
						temp = stringToDecimal(label);
						if(temp >= (1<<12) || temp < (-1)*(1<<12))
						{
							flag_illegal_imm = true;
							error_line_num = line_count;
							return;
						}
					}else 
					{
						if(labels.find(label)==labels.end())
						{
							flag_label_does_not_exist = true;
							error_line_num = line_count;
							return;
						}
						temp = labels[label]-program_counter;
					}
					string imm = convertingToBinary(temp);
					imm = sign_extension(13, imm);

					
					if(inst=="beq" && reg1=="zero" && reg2=="zero" && label=="0") flag_VH_present = true;

					if(register_mapping[reg1]=="" || register_mapping[reg2]=="")
					{
						flag_register_typo = true;
						error_line_num = line_count;
						return;
					}
					
					op<< imm_B_Type_1(imm);
					op<< register_mapping[reg2];
					op<< register_mapping[reg1];
					op<< funct3_encoding[inst];
					op<< imm_B_Type_2(imm);
					op<< instruction_encoding[inst] <<endl;
 					break;
				}
			}


			//S-Type
			for (auto u : S_type)
			{
				if (inst == u)
				{
					string reg1,reg2,num;
					while(i<(int)instruction.size() && instruction[i]!=',')
					{
						reg1+=instruction[i];
						i++;
					}
					i++;
					
					while(i<(int)instruction.size() && instruction[i]!='(')
					{
						if(!isdigit(instruction[i]))
						{
							flag_illegal_imm = true;
							error_line_num = line_count;
							return;
						}
						num+=instruction[i];
						i++;
					}
					i++; 
					
					while(i<(int)instruction.size() && instruction[i]!=')')
					{
						reg2+=instruction[i];
						i++;
					}

					if(register_mapping[reg1]=="" || register_mapping[reg2]=="")
					{
						flag_register_typo = true;
						error_line_num = line_count;
						return;
					}

					int temp = stringToDecimal(num);

					if(temp >= (1<<11) || temp < (-1)*(1<<11))
					{
						flag_illegal_imm = true;
						error_line_num = line_count;
						return;
					}

					string imm = convertingToBinary(temp);
					imm = sign_extension(12, imm);
					
					op<< imm_S_Type_1(imm);
					op<< register_mapping[reg1];
					op<< register_mapping[reg2];
					op<< funct3_encoding[inst];
					op<< imm_S_Type_2(imm);
					op<< instruction_encoding[inst] <<endl;
					
					break;
				}
			}

			//I-Type
			for (auto u:I_type)
			{
				if(inst==u)
				{
					string reg1, reg2, num;
					
					if(inst=="lw")
					{
						while(i<(int)instruction.size() && instruction[i]!=',')
						{
							reg1+=instruction[i];
							i++;
						}
						i++;

						while(i<(int)instruction.size() && instruction[i]!='(')
						{
							if(!isdigit(instruction[i]))
							{
								flag_illegal_imm = true;
								error_line_num = line_count;
								return;
							}
							num += instruction[i];
							i++;
						}
						i++;

						while(i<(int)instruction.size() && instruction[i]!=')')
						{
							reg2+=instruction[i];
							i++;
						}
					}else
					{
						while(i<(int)instruction.size() && instruction[i]!=',')
						{
							reg1+=instruction[i];
							i++;
						}
						i++;
						
						while(i<(int)instruction.size() && instruction[i]!=',')
						{
							reg2+=instruction[i];
							i++;
						}
						i++;
						
						while(i<(int)instruction.size() && instruction[i]!=' ')
						{
							if(!isdigit(instruction[i]))
							{
								flag_illegal_imm = true;
								error_line_num = line_count;
								return;
							}
							num += instruction[i];
							i++;
						}
					}

					int temp = stringToDecimal(num);

					if(temp >= (1<<11) || temp < (-1)*(1<<11))
					{
						flag_illegal_imm = true;
						error_line_num = line_count;
						return;
					}

					string imm = convertingToBinary(temp);
					imm = sign_extension(12, imm);
					
					if(register_mapping[reg1]=="" || register_mapping[reg2]=="")
					{
						flag_register_typo = true;
						error_line_num = line_count;
						return;
					}

					op<< imm_I_Type(imm);
					op<< register_mapping[reg2];
					op<< funct3_encoding[inst];
					op<< register_mapping[reg1];
					op<< instruction_encoding[inst] <<endl;
					break;
				}
			}

			//R-type
			for (auto u:R_type)
			{
				if(inst==u)
				{
					string reg1, reg2, reg3;
					
					while(i<(int)instruction.size() && instruction[i]!=',')
					{
						reg1+=instruction[i];
						i++;
					}
					i++;
					
					while(i<(int)instruction.size() && instruction[i]!=',')
					{
						reg2+=instruction[i];
						i++;
					}
					i++;
					
					while(i<(int)instruction.size() && instruction[i]!=' ')
					{
						reg3+=instruction[i];
						i++;
					}

					if(register_mapping[reg1]=="" || register_mapping[reg2]=="" || register_mapping[reg3]=="")
					{
						flag_register_typo = true;
						error_line_num = line_count;
						return;
					}
					
					op<< funct7_encoding[inst];
					op<< register_mapping[reg3];
					op<< register_mapping[reg2];
					op<< funct3_encoding[inst];
					op<< register_mapping[reg1];
					op<< instruction_encoding[inst] <<endl;
					
					break;
					
				}
			}
			program_counter += 4;
		}
		inp.close();
		op.close();
	}

	void Assembler::check_errors(string output_file_name)
	{
		bool error = false;
		if(label_typo)
		{
			cerr<< "Typo in label name!" <<endl;
			error = true;
		}else if(flag_register_typo)
		{
			cerr<< "Typo in register name!" <<endl;
			error = true;
		}else if(flag_instruction_typo)
		{
			cerr<< "Typo in instruction name!" <<endl;
			error = true;
		}else if(flag_illegal_imm)
		{
			cerr<< "Illegal immediate!" <<endl;
			error = true;
		}else if(flag_label_does_not_exist)
		{
			cerr<< "Label does not exist!" <<endl;
			error = true;
		}
		else
		{
			if(!flag_VH_present)
			{
				cerr<< "Virtual Halt absent!"<< endl;
				error_line_num = line_count;
				error = true;
			}
		}

		if(error)
		{
			cout<< "Error at line number: " << error_line_num <<endl;
			ofstream op;
			op.open(output_file_name);
			op.close();
			exit(0);
		}
	}

	simulator::simulator()
	{
		registers.resize(32, "00000000000000000000000000000000");
		data_memory.resize(32, "00000000000000000000000000000000");

		registers[2] = "00000000000000000000000100000000";
	}

	long long simulator::twos_comp(string binary_value)
	{
	    long long decimal_value = 0;
	    for (int i=binary_value.size()-1;i>0;i--) {
	        if (binary_value[i] == '1') {
	            decimal_value += (long long)pow(2,binary_value.size()-1-i);
	        }
	    }
		if(binary_value[0]=='1') decimal_value -= (long long)pow(2,binary_value.size()-1);
	
		return decimal_value;
	}
	
	long long simulator::unsigned_str(string binary_value)
	{
	    long long decimal_value = 0;
	    for (int i=binary_value.size()-1;i>=0;i--) {
	        if (binary_value[i] == '1') {
	            decimal_value += (long long)pow(2,binary_value.size()-1-i);
	        }
	    }
	
		return decimal_value;
	}
	
	long long simulator::signed_str(string binary_value)
	{
	    long long decimal_value = 0;
	    for (int i=binary_value.size()-1;i>0;i--) {
	        if (binary_value[i] == '1') {
	            decimal_value += (long long)pow(2,binary_value.size()-1-i);
	        }
	    }
		
		if(binary_value[0]=='1') decimal_value *= -1;
	
		return decimal_value;
	}

	string simulator::convertingToBinary(long long n) {
	
	    if (n < 0) {
		string binary= "";
		n *= -1;

		bool power_of_two = false;
		long long x = n&(n-1);
		if(x==0) power_of_two = true;
		    
		int check = 0;
		while (n > 0) {
			int bit = n % 2;
			if(check==0 && bit==1) 
			{
				check = 1;
				binary = to_string(bit) + binary;
			}
			else if(check==0 && bit==0) binary = to_string(bit) + binary;
			else if(check==1) binary = to_string(bit^1) + binary;
			n = n/2;
		}
		if(power_of_two) return binary;
		return '1' + binary;
	    } else {
		string binary = "";
	        while (n > 0) {
			int bit = n % 2;
	           	binary = to_string(bit) + binary;
	            	n = n / 2;
	        }
		return '0' + binary;
	    }
	}

	string simulator::sign_extension(int bits, string bin)
	{
		string res;
		int temp=bits-bin.size();
		if(bin[0]=='1')
		{
			while(temp>0)
			{
				res+="1";
				temp--;
			}
			res+=bin;
			return res;
		}
		else
		{
			while(temp>0)
			{
				res+="0";
				temp--;
			}
			res+=bin;
			return res;
		}
	}

	string simulator::bin_to_hex(string bin)
	{
		string hex = "";
		int i=0;
		while(i<32)
		{
			int res = 0;
			for(int j=3; j>=0; j--)
			{
				if(bin[i]=='1') res += (int)pow(2, j);
				i++;
			}
			if(res < 10) hex += to_string(res);
			else if(res==10) hex += 'a';
			else if(res==11) hex += 'b';
			else if(res==12) hex += 'c';
			else if(res==13) hex += 'd';
			else if(res==14) hex += 'e';
			else hex += 'f';
		}

		return hex;
	}

	void simulator::read(string input_file_name)
	{	
		ifstream inp;
		inp.open(input_file_name);
		if(!inp)
		{
			cerr<< "Input file not present!" <<endl;
			exit(0);
		}

		string instruction;
		while(getline(inp, instruction)) input.push_back(instruction);
		
		inp.close();
	}

	void simulator::write(string output_file_name)
	{
		ofstream op;
		op.open(output_file_name);
		if(!op.is_open())
		{
			cerr<< "Output file not present!" <<endl;
			exit(0);
		}
		
		long long program_counter = 0;
		while(true)
		{
			string instruction = input[program_counter/4];
			if(instruction=="00000000000000000000000001100011") 
			{
				op<< "0b" << sign_extension(32, convertingToBinary(program_counter)) << " ";
				for(int i=0; i<32; i++) 
				{
					op<< "0b" << registers[i];
					if(i!=31) op<< " ";
				}
				op<<endl;

				break;
			}
			
			string opcode = instruction.substr(25,7);	

			if(opcode=="0110111")
			{
				string imm = instruction.substr(0,20);
				imm += "000000000000";
				string rd = instruction.substr(20,5);
				registers[register_address_mapping[rd]] = sign_extension(32, imm);
			}
			else if(opcode=="0100011")
			{
				string imm = instruction.substr(0,7) + instruction.substr(19,5);
				string rs1 = instruction.substr(12,5);
				string rs2 = instruction.substr(7,5);

				data_memory[(twos_comp(registers[register_address_mapping[rs1]]) + twos_comp(imm) - 65536)/4] = registers[register_address_mapping[rs2]];
			}

			///u type
			else if(opcode=="0010111")
			{
				string imm = instruction.substr(0,20);
				imm += "000000000000";
				string rd = instruction.substr(20,5);
				registers[register_address_mapping[rd]] = sign_extension(32, convertingToBinary(program_counter + twos_comp(imm)));
			}
			//R-type
			else if(opcode=="0110011")
			{
				string funct3 = instruction.substr(17,3);
				string rs1=instruction.substr(12,5);
				string rs2=instruction.substr(7,5);
				string rd=instruction.substr(20,5);
				if(funct3=="000")
				{
					if(instruction[1]=='1')
					{
						//sub
						if(rs1=="00000")
						{
							long long val = -1*twos_comp(registers[register_address_mapping[rs2]]);
							registers[register_address_mapping[rd]] = sign_extension(32, convertingToBinary(val));
						}else
						{
							//long long val = signed_str(registers[register_address_mapping[rs1]]) - signed_str(registers[register_address_mapping[rs2]]);
							//registers[register_address_mapping[rd]] = sign_extension(32, convertingToBinary(val)); 	
							registers[register_address_mapping[rd]] = sign_extension(32, convertingToBinary(twos_comp(registers[register_address_mapping[rs1]]) - twos_comp(registers[register_address_mapping[rs2]])));
						}
					}else
					{
						registers[register_address_mapping[rd]] = sign_extension(32, convertingToBinary(twos_comp(registers[register_address_mapping[rs1]]) + twos_comp(registers[register_address_mapping[rs2]])));
					}
				}else if(funct3=="010")
				{
					long long a = twos_comp(registers[register_address_mapping[rs1]]);
					long long b = twos_comp(registers[register_address_mapping[rs2]]);
					if(a<b) registers[register_address_mapping[rd]] = sign_extension(32, "01");
				}else if(funct3=="011")
				{
					long long a = unsigned_str(registers[register_address_mapping[rs1]]);
					long long b = unsigned_str(registers[register_address_mapping[rs2]]);
					if(a<b) registers[register_address_mapping[rd]] = sign_extension(32, "01");
				}
				else if(funct3=="100")
				{
					for(int i=0; i<32; i++)
					{
						long long a = registers[register_address_mapping[rs1]][i] - '0';
						long long b = registers[register_address_mapping[rs2]][i] - '0';
						if((a^b)==1) registers[register_address_mapping[rd]][i] = '1';
						else registers[register_address_mapping[rd]][i] = '0';
					}
				}
				else if(funct3=="110")
				{
					for(int i=0; i<32; i++)
					{
						long long a = registers[register_address_mapping[rs1]][i] - '0';
						long long b = registers[register_address_mapping[rs2]][i] - '0';
						if((a|b)==1) registers[register_address_mapping[rd]][i] = '1';
						else registers[register_address_mapping[rd]][i] = '0';
					}
				}
				else if(funct3=="111")
				{
					for(int i=0; i<32; i++)
					{
						long long a = registers[register_address_mapping[rs1]][i] - '0';
						long long b = registers[register_address_mapping[rs2]][i] - '0';
						if((a&b)==1) registers[register_address_mapping[rd]][i] = '1';
						else registers[register_address_mapping[rd]][i] = '0';
					}
				}
				else if(funct3=="001")
				{
					long long temp = unsigned_str(registers[register_address_mapping[rs2]].substr(27,5));
					string new_val = "";
					for(long long i=temp; i<32; i++) new_val += registers[register_address_mapping[rs1]][i];
					while((int)new_val.size() != 32) new_val += '0';
					registers[register_address_mapping[rd]] = new_val;
 				}
				else if(funct3=="101")
				{
					long long temp = unsigned_str(registers[register_address_mapping[rs2]].substr(27,5));
					string new_val = "";
					for(long long i=0; i<32-temp; i++) new_val += registers[register_address_mapping[rs1]][i];
					while((int)new_val.size() != 32) new_val = '0' + new_val;
					registers[register_address_mapping[rd]] = new_val;
				}
			}
			else if(opcode=="1100011")
			{
				string funct3 = instruction.substr(17,3);
				string rs1 = instruction.substr(12,5);
				string rs2 = instruction.substr(7,5);
				
				string imm = "";
				imm += instruction[0];
				imm += instruction[24];
				imm += instruction.substr(1,6);
				imm += instruction.substr(20,4);
				imm += '0';
				
				if(funct3=="000")
				{
					if(sign_extension(32,registers[register_address_mapping[rs1]]) == sign_extension(32,registers[register_address_mapping[rs2]])) 
					{
						program_counter += twos_comp(imm);
						program_counter -= 4;
					}
				}else if(funct3=="001")
				{
					if(sign_extension(32,registers[register_address_mapping[rs1]]) != sign_extension(32,registers[register_address_mapping[rs2]])) 
					{
						program_counter += twos_comp(imm);
						program_counter -= 4;
					}
				}else if(funct3=="100")
				{
					if(twos_comp(registers[register_address_mapping[rs1]]) < twos_comp(registers[register_address_mapping[rs2]])) 
					{
						program_counter += twos_comp(imm);
						program_counter -= 4;
					}
				}else if(funct3=="101")
				{
					if(twos_comp(registers[register_address_mapping[rs1]]) > twos_comp(registers[register_address_mapping[rs2]])) 
					{
						program_counter += twos_comp(imm);
						program_counter -= 4;
					}
				}else if(funct3=="110")
				{
					if(unsigned_str(registers[register_address_mapping[rs1]]) < unsigned_str(registers[register_address_mapping[rs2]])) 
					{
						program_counter += twos_comp(imm);
						program_counter -= 4;
					}
				}else if(funct3=="111")
				{
					if(unsigned_str(registers[register_address_mapping[rs1]]) > unsigned_str(registers[register_address_mapping[rs2]])) 
					{
						//program_counter += signed_str(imm);
						program_counter += twos_comp(imm);
						program_counter -= 4;
					}
				}
			}
			else if(opcode=="0000011")
			{
				string rd = instruction.substr(20,5);
				string rs1 = instruction.substr(12,5);
				string imm = instruction.substr(0,12);

				registers[register_address_mapping[rd]] = data_memory[(twos_comp(registers[register_address_mapping[rs1]]) + twos_comp(imm) - 65536)/4];
			}
			else if(opcode=="0010011")
			{
				string funct3 = instruction.substr(17,3);
				string rd = instruction.substr(20,5);
				string rs1 = instruction.substr(12,5);
				string imm = instruction.substr(0,12);

				if(funct3=="000")
				{
					registers[register_address_mapping[rd]] = sign_extension(32, convertingToBinary(twos_comp(registers[register_address_mapping[rs1]]) + twos_comp(imm)));
				}else
				{
					if(unsigned_str(registers[register_address_mapping[rs1]]) < unsigned_str(imm)) registers[register_address_mapping[rd]] = sign_extension(32, "01");
				}
			}
			else if(opcode=="1100111")
			{
				string rd = instruction.substr(20,5);
				string rs1 = instruction.substr(12,5);
				string imm = instruction.substr(0,12);

				registers[register_address_mapping[rd]] = sign_extension(32, convertingToBinary(program_counter + 4));
				program_counter = twos_comp(registers[register_address_mapping[rs1]]) + twos_comp(imm);
				string temp_pc = sign_extension(32, convertingToBinary(program_counter));
				temp_pc[temp_pc.size()-1] = '0';

				program_counter = twos_comp(temp_pc);
				program_counter -= 4;
			}
			else if(opcode=="1101111")
			{
				string imm = "";
				imm += instruction[0];
				imm += instruction.substr(12,8);
				imm += instruction[11];
				imm += instruction.substr(1,10);
				imm += '0';
				string rd = instruction.substr(20,5); 

				registers[register_address_mapping[rd]] = sign_extension(32, convertingToBinary(program_counter + 4));
				program_counter += twos_comp(imm);
				string temp_pc = sign_extension(32, convertingToBinary(program_counter));
				temp_pc[temp_pc.size()-1] = '0';

				program_counter = twos_comp(temp_pc);
				program_counter -= 4;
			}

			registers[0] = "00000000000000000000000000000000";

			program_counter += 4;
			op<< "0b" << sign_extension(32, convertingToBinary(program_counter)) << " ";
			for(int i=0; i<32; i++) 
			{
				op<< "0b" << registers[i];
				if(i!=31) op<<" ";
			}
			op<<endl;
		}

		for(int i=0; i<32; i++) op<< "0x" << bin_to_hex(sign_extension(32, convertingToBinary(i*4 + 65536))) << ':' << "0b" << data_memory[i] <<endl;
		
		op.close();
	}
	

