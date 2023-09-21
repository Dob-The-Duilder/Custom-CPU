

# Instruction set and basic architecture 

## Registers | All registers are 16 bit

 -  A, B : Math Registers
	- The registers used when preforming math operations. Result automatically put into AO register.
	-  A is always the primary number in the operation.
		- A - B,   A % B,	!A 
- C, D, E, F : General Purpose Registers
	- Simply store a value.
- SR : Stat Register
	- Bits 13-15 reserved for ALU flags. Read only.
	- Sub-section Breakdown
		- Bits 0-7: IO select, can be set directly by "Set IO" (Instruction 10).
		- Bits 8-11: ALU operation select, can be set directly by "Set ALU" (Instruction 9).
		- Bit 12: SWAP flag, used to swap highest bit of memory addresses to increase total memory.
		- Bit 13: ALU carry flag.
		- Bit 14: ALU zero flag.
		- Bit 15: ALU not zero flag.
- PC: Program Counter
	- Current position of the CPU is executing from.
	- Can be set like any other register.
- AO: ALU Output
	- **Read only**
	- Automatically set based on inputs from registers A, B, and SR.
## ALU Operations
- Numbers corispond to what the ALU operation select flag should be set to for a given operation.
- All operators needed to be a single character, some may have unusual or non-standard operands

|   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|---|---|---|---|---|---|---|---|---|
|Name| Modulus | Division | Multiplication | Subtraction | Addition | (Unused) | Greater Than | Less Than |
| Operand | % | / | * | - | + |   | > | < |
||||||||||
|   | 8 | 9 | A | B | C | D | E | F | 
| Name | Rotate Right | Rotate Left | Shift Right | Shift Left | Bitwise NOT | Bitwise XOR | Bitwise OR | Bitwise AND|
| Operand | } | { | ) | ( | ! | ^ | &#124; | & |

## Instructions
| Inst. # | Command Name  | Input 1	| Input 2	| Input 3 
|---|---|---|---|---
| 0 | NOOP
| 1 |
| 2 | SWAP
| 3 | Load REG from Addr.| Register (0-7) |Upper 8 bits of Address | Lower 8 bits of Address
| 4 | Load REG from value| Register (0-7) |Upper 8 bits of Value| Lower 8 bits of Value
| 5 | Load REG from Addr. from REG| Register (0-7) | | Addr. Register (0-8) 
| 6 | Load REG from from REG| Register (0-7) | | Register (0-8) 
| 7 | Store REG to Addr. | Register (0-8) |Upper 8 bits of Address | Lower 8 bits of Address
| 8 | Store REG to Addr. from  REG| Register (0-8) |   | Addr. Register (0-8) 
| 9 | Set ALU Operation flag | Value (0-15)
| 10 | Set IO output flag | Value (0-255)
| 11 | Send value |   |Upper 8 bits of Value| Lower 8 bits of Value
| 12 | Send from REG| Register (0-8)
| 13 | Receive into REG| Register (0-7)
| 14 | Store value to Addr. from REG | Addr. Register (0-8) |Upper 8 bits of Value| Lower 8 bits of Value
| 15 | Jump if ALU zero |   |Upper 8 bits of Value| Lower 8 bits of Value
| 16 | Jump if not ALU zero |   |Upper 8 bits of Value| Lower 8 bits of Value
| 17 | Jump if ALU carry |   |Upper 8 bits of Value| Lower 8 bits of Value
| 18 | Jump if ALU zero to REG Addr.||| Addr. Register (0-8) |
| 19 | Jump if not ALU zero to REG Addr.||| Addr. Register (0-8) |
| 20 | Jump if ALU carry to REG Addr.||| Addr. Register (0-8) |
| 21 | Increment REG | Register (0-7) |   |   |
| 22 | Decrement REG | Register (0-7) |   |   |
| … |   |   |   |   |
| 255 | HALT |   |   |   |
