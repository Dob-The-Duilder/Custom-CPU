#include <cstdlib>
#include <stdio.h>
#include <iomanip>
#include <queue>
#include <algorithm>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <fstream>
#include <cstring>
using namespace std;

#include "main.h"
//#include "peripherals.cpp"

void print(vector<string> const &input)
{
    for (int i = 0; i < input.size(); i++) {
        cout << input[i] << ' ';
    }
	cout << endl;
}

void print_window(StateH32* state, vector<string> h_buffer, int offset = 0)
{

	system("cls");

	cout << (char)218<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)194<<(char)196<<(char)196<<(char)194<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)194<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)191
	     << "|a:"<< right << setw(5) << setfill('-') << dec <<state->a << " ALU:" << opSwap[state->sr.ao] 				  	   << "|  |c:" << right << setw(5) << setfill('-') << state->c << " d:" << right << setw(5) << setfill('-') << state->d << " e:" << right << setw(5) << setfill('-') << state->e  <<"| "<< setw(4) << setfill('0') << hex <<     offset <<": "<< setw(4) << setfill('0') << hex << state->ram[    offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[1 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[2 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[3 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[4 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[5 + offset] <<" |"
	     << "|b:"<< right << setw(5) << setfill('-') << dec <<state->b << " " << right << setw(5) << setfill('-') << state->ao << "|  |f:" << right << setw(5) << setfill('-') << state->f << " s:" << right << setw(5) << setfill('-') << 0        << " p:" << right << setw(5) << setfill('-') << state->pc <<"| "<< setw(4) << setfill('0') << hex << 6 + offset <<": "<< setw(4) << setfill('0') << hex << state->ram[6 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[7 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[8 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[9 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[10+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[11+ offset] <<" |"
	     << (char)195<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)193<<(char)196<<(char)196<<(char)193<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)180<<" "<< right << setw(4) << setfill('0') << hex<< 12 + offset <<": "<< setw(4) << setfill('0') << hex << state->ram[12 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[13 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[14 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[15 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[16 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[17 + offset] <<" |"
	     << "|"<< left << setw(40) << setfill(' ') << h_buffer[19] <<"| "<< right << setw(4) << setfill('0') << hex<<  18 + offset <<": "<< setw(4) << setfill('0') << hex << state->ram[18 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[19 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[20 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[21 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[22 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[23 + offset] <<" |"
	     << "|"<< left << setw(40) << setfill(' ') << h_buffer[18] <<"| "<< right << setw(4) << setfill('0') << hex<<  24 + offset <<": "<< setw(4) << setfill('0') << hex << state->ram[24 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[25 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[26 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[27 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[28 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[29 + offset] <<" |"
	     << "|"<< left << setw(40) << setfill(' ') << h_buffer[17] <<"| "<< right << setw(4) << setfill('0') << hex<<  30 + offset <<": "<< setw(4) << setfill('0') << hex << state->ram[30 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[31 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[32 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[33 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[34 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[35 + offset] <<" |"
	     << "|"<< left << setw(40) << setfill(' ') << h_buffer[16] <<"| "<< right << setw(4) << setfill('0') << hex<<  36 + offset <<": "<< setw(4) << setfill('0') << hex << state->ram[36 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[37 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[38 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[39 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[40 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[41 + offset] <<" |"
	     << "|"<< left << setw(40) << setfill(' ') << h_buffer[15] <<"| "<< right << setw(4) << setfill('0') << hex<<  42 + offset <<": "<< setw(4) << setfill('0') << hex << state->ram[42 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[43 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[44 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[45 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[46 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[47 + offset] <<" |"
	     << "|"<< left << setw(40) << setfill(' ') << h_buffer[14] <<"| "<< right << setw(4) << setfill('0') << hex<<  48 + offset <<": "<< setw(4) << setfill('0') << hex << state->ram[48 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[49 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[50 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[51 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[52 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[53 + offset] <<" |"
	     << "|"<< left << setw(40) << setfill(' ') << h_buffer[13] <<"| "<< right << setw(4) << setfill('0') << hex<<  54 + offset <<": "<< setw(4) << setfill('0') << hex << state->ram[54 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[55 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[56 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[57 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[58 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[59 + offset] <<" |"
	     << "|"<< left << setw(40) << setfill(' ') << h_buffer[12] <<"| "<< right << setw(4) << setfill('0') << hex<<  60 + offset <<": "<< setw(4) << setfill('0') << hex << state->ram[60 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[61 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[62 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[63 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[64 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[65 + offset] <<" |"
	     << "|"<< left << setw(40) << setfill(' ') << h_buffer[11] <<"| "<< right << setw(4) << setfill('0') << hex<<  66 + offset <<": "<< setw(4) << setfill('0') << hex << state->ram[66 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[67 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[68 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[69 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[70 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[71 + offset] <<" |"
	     << "|"<< left << setw(40) << setfill(' ') << h_buffer[10] <<"| "<< right << setw(4) << setfill('0') << hex<<  72 + offset <<": "<< setw(4) << setfill('0') << hex << state->ram[72 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[73 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[74 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[75 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[76 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[77 + offset] <<" |"
	     << "|"<< left << setw(40) << setfill(' ') << h_buffer[ 9] <<"| "<< right << setw(4) << setfill('0') << hex<<  78 + offset <<": "<< setw(4) << setfill('0') << hex << state->ram[78 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[79 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[80 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[81 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[82 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[83 + offset] <<" |"
	     << "|"<< left << setw(40) << setfill(' ') << h_buffer[ 8] <<"| "<< right << setw(4) << setfill('0') << hex<<  84 + offset <<": "<< setw(4) << setfill('0') << hex << state->ram[84 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[85 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[86 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[87 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[88 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[89 + offset] <<" |"
	     << "|"<< left << setw(40) << setfill(' ') << h_buffer[ 7] <<"| "<< right << setw(4) << setfill('0') << hex<<  90 + offset <<": "<< setw(4) << setfill('0') << hex << state->ram[90 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[91 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[92 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[93 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[94 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[95 + offset] <<" |"
	     << "|"<< left << setw(40) << setfill(' ') << h_buffer[ 6] <<"| "<< right << setw(4) << setfill('0') << hex<<  96 + offset <<": "<< setw(4) << setfill('0') << hex << state->ram[96 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[97 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[98 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[99 + offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[100+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[101+ offset] <<" |"
	     << "|"<< left << setw(40) << setfill(' ') << h_buffer[ 5] <<"| "<< right << setw(4) << setfill('0') << hex<< 102 + offset <<": "<< setw(4) << setfill('0') << hex << state->ram[102+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[103+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[104+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[105+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[106+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[107+ offset] <<" |"
	     << "|"<< left << setw(40) << setfill(' ') << h_buffer[ 4] <<"| "<< right << setw(4) << setfill('0') << hex<< 108 + offset <<": "<< setw(4) << setfill('0') << hex << state->ram[108+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[109+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[110+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[111+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[112+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[113+ offset] <<" |"
	     << "|"<< left << setw(40) << setfill(' ') << h_buffer[ 3] <<"| "<< right << setw(4) << setfill('0') << hex<< 114 + offset <<": "<< setw(4) << setfill('0') << hex << state->ram[114+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[115+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[116+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[117+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[118+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[119+ offset] <<" |"
	     << "|"<< left << setw(40) << setfill(' ') << h_buffer[ 2] <<"| "<< right << setw(4) << setfill('0') << hex<< 120 + offset <<": "<< setw(4) << setfill('0') << hex << state->ram[120+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[121+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[122+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[123+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[124+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[125+ offset] <<" |"
	     << "|"<< left << setw(40) << setfill(' ') << h_buffer[ 1] <<"| "<< right << setw(4) << setfill('0') << hex<< 126 + offset <<": "<< setw(4) << setfill('0') << hex << state->ram[126+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[127+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[128+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[129+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[130+ offset] <<" "<< setw(4) << setfill('0') << hex << state->ram[131+ offset] <<" |"
	     << (char)192<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)193<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)217
	     << " "<< h_buffer[ 0];
}

void print_queue(queue<char> q)
{
  while (!q.empty())
  {
    cout << (int) q.front() << " ";
    q.pop();
  }
  cout << endl;
}

bool write_file_binary (string const & filename, short unsigned int * data, size_t const bytes)
{
	//ofstream b_stream(filename.c_str(), fstream::out | fstream::binary);
	//if (b_stream)
	//{
	//	b_stream.write(data, bytes);
	//	return (b_stream.good());
	//}
	return false;
}


StateH32* InitH32(void)
{
	StateH32* state = (StateH32*) calloc(1,sizeof(StateH32));
	state->pc		= 0;
	state->rom	  = (struct OpCode*)	malloc(sizeof(struct OpCode) * 0xFFFF);
	state->ram	  = (unsigned short*)	malloc(0xFFFF * 2);
	return state;
}

int EmulateH32(StateH32* state, int offset, queue<char> &inputBuffer, vector<string> &h_buffer)
{
	struct OpCode *opcode = &state->rom[state->pc];

	switch(opcode->is)
	{
		case 0x00: break;	//  NOOP
		case 0x01: break;	//  MemWait
		case 0x02:			//  Swap
			state->sr.ms = 0 ^ state->sr.ms; break;
		case 0x03: 			//	Load from mem. address
		{
			unsigned short * ad = &state->a;
			ad += opcode->p1;
			*ad = state->ram[(state->sr.ms << 16) + (opcode->p2 << 8) + opcode->p3];
			break;
		};
		case 0x04: 			//	Load from raw value
		{
			unsigned short * ad = &state->a;
			ad += opcode->p1;
			*ad = (opcode->p2 << 8) + opcode->p3;
			break;
		};
		case 0x05:  		//	Load from register
		{
			unsigned short * ad = &state->a;
			unsigned short * ao = &state->a;
			ad += opcode->p1;
			ao += opcode->p3;
			*ad = state->ram[(state->sr.ms << 16) + *ao];
			break;
		};
		case 0x06:  		//	Load from mem. address from register
		{
			unsigned short * ad = &state->a;
			unsigned short * ao = &state->a;
			ad += opcode->p1;
			ao += opcode->p3;
			*ad = *ao;
			break;
		};
		case 0x07: 			//	Store to mem. address
		{
			unsigned short * ad = &state->a;
			ad += opcode->p1;
			state->ram[(state->sr.ms << 16) + (opcode->p2 << 8) + opcode->p3] = *ad;
			break;
		}
		case 0x08: 			//	Store to mem. address from register
		{
			unsigned short * ad = &state->a;
			unsigned short * ao = &state->a;
			ad += opcode->p1;
			ao += opcode->p3;
			state->ram[(state->sr.ms << 16) + *ao] = *ad;
			break;
		}
		case 0x09:			//	Set Operation
			state->sr.ao = opcode->p1 & 0xF; break;
		case 0x0A:			//	Set Peripheral Control
			state->sr.pe = opcode->p1 & 0xFF; break;
		case 0x0B:			//	Send from Raw Value        IMPLEMENT
		{
			if (opcode->p3 < 128) {
				int output = convert[opcode->p3];
				if (output != '\n')
				{
					h_buffer[0] += output;
				}
				else
				{
					h_buffer.insert(h_buffer.begin(), "");
					h_buffer.pop_back();
					print_window(state, h_buffer, offset);
				}
			}
			break;
		}
		case 0x0C:			//	Send from Register        IMPLEMENT
		{
			unsigned short * ad = &state->a;
			ad += opcode->p1;
			if (*ad < 128) {
				int output = convert[*ad];
				if (output != '\n')
				{
					h_buffer[0] += output;
				}
				else
				{
					h_buffer.insert(h_buffer.begin(), "");
					h_buffer.pop_back();
					print_window(state, h_buffer, offset);
				}
			}
			break;
		}
		case 0x0D:			//	Recive to Register        IMPLEMENT
		{
			unsigned short * ad = &state->a;
			ad += opcode->p1;
			char tempInput[40];
			if (inputBuffer.empty())
			{
				print_window(state, h_buffer, offset);
				cin.get(tempInput, 40);cin.get();
				for(int i = 0; i < strlen(tempInput); i++)
				{
					const char * itr = find(convert, convert + 128, tempInput[i]);
					inputBuffer.push(distance(convert, itr));
				}
				
				string line(tempInput);
				h_buffer[0] += line;
				h_buffer.insert(h_buffer.begin(), "");
				h_buffer.pop_back();
				inputBuffer.push(63);
				print_window(state, h_buffer, offset);
			}
			*ad = inputBuffer.front();
			inputBuffer.pop();
			break;
		}
		case 0x0E:			//	Conditionless Jump
			state->pc = (opcode->p2 << 8) + opcode->p3; 
			break;
		case 0x0F:			//	If Accumulator == 0, Jump
			if(state->sr.az) state->pc = (opcode->p2 << 8) + opcode->p3; break;
		case 0x10:			//	If Accumulator != 0, Jump
			if(state->sr.nz) state->pc = (opcode->p2 << 8) + opcode->p3; break;
		case 0x11:			//	If Accumulator Carry, Jump
			if(state->sr.ac) state->pc = (opcode->p2 << 8) + opcode->p3; break;
		case 0x12: 			//	Increment Register
		{
			unsigned short * ad = &state->a;
			ad += opcode->p1;
			(*ad)++;
			break;
		};
		case 0x13: 			//	Decrement Register
		{
			unsigned short * ad = &state->a;
			ad += opcode->p1;
			(*ad)--;
			break;
		};

		case 0xFF:
		{
			printf("HALT\033[37m");
			printf("\n\nAttepting memory log...\n");
			write_file_binary("memory.bin", state->ram, sizeof(short)*0xFFFF);
			return 1;   //  Halt
		}
	}

	int temporary;
	switch (state->sr.ao)
	{
	case 0:
		if(state->b)
		temporary = state->a % state->b;
		break;
	case 1:
		if (state->b) temporary = state->a / state->b;
		break;
	case 2:
		temporary = state->a * state->b;
		break;
	case 3:
		temporary = state->a - state->b;
		break;
	case 4:
		temporary = state->a + state->b;
		break;
	case 8:
		temporary = (state->a >> state->b) | (state->a << (INT_BITS - state->b));
		break;
	case 9:
		temporary = (state->a << state->b) | (state->a >> (INT_BITS - state->b));
		break;
	case 10:
		temporary = state->a >> state->b;
		break;
	case 11:
		temporary = state->a << state->b;
		break;
	case 12:
		temporary = ~state->a;
		break;
	case 13:
		temporary = state->a ^ state->b;
		break;
	case 14:
		temporary = state->a | state->b;
		break;
	case 15:
		temporary = state->a & state->b;
		break;
	}
	state->ao = temporary & 0xFFFF;

	state->sr.nz = 0;
	state->sr.az = 0;
	state->sr.ac = 0;
	if( state->ao)              state->sr.nz = 1;
	if(!state->ao)              state->sr.az = 1;
	if( state->ao != temporary) state->sr.ac = 1;

	state->pc+=1;
	return 0;
}

void ReadFileIntoRomAt(StateH32* state, char* filename, unsigned long offset)
{
	FILE *f= fopen(filename, "rb");
	if (f==NULL)
	{
		printf("error: Couldn't open %s\n", filename);
		exit(1);
	}
	fseek(f, 0L, SEEK_END);
	int fsize = ftell(f);
	fseek(f, 0L, SEEK_SET);
	
	struct OpCode *buffer = &state->rom[offset];
	fread(buffer, 4, fsize/4, f);
	fclose(f);
}

int main (int argc, char**argv)
{
	printf("\033[32m\n");

	int offset = stoi(argv[2]);

	int done = 0;
	int vblankcycles = 0;
	StateH32* state = InitH32();
	queue<char> inputbuffer;

	vector<string> h_buffer(20, "");
	ReadFileIntoRomAt(state, argv[1], 0);
	//ReadFileIntoMemoryAt(state, "invaders.g", 0x800);
	
	print_window(state, h_buffer);
	while (done == 0)
	{
		done = EmulateH32(state, offset, inputbuffer, h_buffer);
	}
	return 0;
}
