#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <cstring>
#include <iomanip>
#include <queue>
#include <algorithm>
using namespace std;

#include "main.h"
//#include "peripherals.cpp"

void print_queue(std::queue<char> q)
{
  while (!q.empty())
  {
    std::cout << (int) q.front() << " ";
    q.pop();
  }
  std::cout << std::endl;
}

StateH32* InitH32(void)
{
	StateH32* state = (StateH32*) calloc(1,sizeof(StateH32));
	state->pc		= 0;
	state->rom	  = (struct OpCode*)	malloc(sizeof(struct OpCode) * 0xFFFF);
	state->ram	  = (unsigned long*)	malloc(0xFFFF);
	return state;
}

int EmulateH32(StateH32* state, bool verbose, queue<char> &inputBuffer)
{
	struct OpCode *opcode = &state->rom[state->pc];
	if (verbose)
	{
		printf("\033[0;31mProgram Counter: %d\033[0m\n", state->pc);
		printf("OpCode: %d, %d, %d\n", opcode->is, opcode->p1, (opcode->p2 << 8) + opcode->p3);
	}

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
			*ad = state->ram[(opcode->p2 << 8) + opcode->p3];
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
			*ad = state->ram[*ao];
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
			state->ram[(opcode->p2 << 8) + opcode->p3] = *ad;
			break;
		}
		case 0x08: 			//	Store to mem. address from register
		{
			unsigned short * ad = &state->a;
			unsigned short * ao = &state->a;
			ad += opcode->p1;
			ao += opcode->p3;
			state->ram[*ao] = *ad;
			break;
		}
		case 0x09:			//	Set Operation
			state->sr.ao = opcode->p1 & 0xF; break;
		case 0x0A:			//	Set Peripheral Control
			state->sr.pe = opcode->p1 & 0xFF; break;
		case 0x0B:			//	Send from Raw Value        IMPLEMENT
		{
			int output = convert[(opcode->p3) & 0x7F];
			printf("\033[32m%c", output);
			break;
		}
		case 0x0C:			//	Send from Register        IMPLEMENT
		{
			unsigned short * ad = &state->a;
			ad += opcode->p1;
			printf("%c", convert[*ad & 0x7F]);
			break;
		}
		case 0x0D:			//	Recive to Register        IMPLEMENT
		{
			unsigned short * ad = &state->a;
			ad += opcode->p1;
			char tempInput[40];
			if (inputBuffer.empty())
			{
				cin.get(tempInput, 40);cin.get();
				for(int i = 0; i < strlen(tempInput); i++)
				{
					const char * itr = find(convert, convert + 128, tempInput[i]);
					inputBuffer.push(distance(convert, itr));
				}
				inputBuffer.push(63);
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
		case 0x14: break;
		case 0x15: break;
		case 0x16: break;
		case 0x17: break;
		case 0x18: break;
		case 0x19: break;
		case 0x1A: break;
		case 0x1B: break;
		case 0x1C: break;
		case 0x1D: break;
		case 0x1E: break;
		case 0x1F: break;

		case 0xFF: printf("\033[37m"); return 1;   //  Halt
	}

	int temporary;
	switch (state->sr.ao)
	{
	case 0:
		if(state->b)
		temporary = state->a %  state->b;
		break;
	case 1:
		temporary = state->a /  state->b;
		break;
	case 2:
		temporary = state->a *  state->b;
		break;
	case 3:
		temporary = state->a -  state->b;
		break;
	case 4:
		temporary = state->a + state->b;
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
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

	if (verbose)
	{
	printf("Stat Register: %d, %d, %d, %d, %d, %d\n", state->sr.nz, state->sr.az, state->sr.ac, state->sr.ms, state->sr.ao, state->sr.pe);
	printf("Registers: %d, %d, %d, %d, %d, %d, %d\n", state->a, state->b, state->c, state->d, state->e, state->f, state->ao);
	}

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
	printf("\033[32m");
	bool output = 0;

	int done = 0;
	int vblankcycles = 0;
	StateH32* state = InitH32();
	queue<char> inputbuffer;

	ReadFileIntoRomAt(state, "roms/test.bin", 0);
	//ReadFileIntoMemoryAt(state, "invaders.g", 0x800);
	
	while (done == 0)
	{
		done = EmulateH32(state, (bool) argv[1], inputbuffer);
	}
	return 0;
}