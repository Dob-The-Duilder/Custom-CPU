
## Instruction set and basic architecture 

### Registers

### Instructions
(Empty column means unassigned/unnecessary)
| Inst. # | Command Name  | Input 1	| Input 2	| Input 3 
|---|---|---|---|---
| 0 | NOOP
| 1 |
| 2 | SWAP
| 3 | Load REG from Addr.| Register (0-7) |Upper 8 bits of Address | Lower 8 bits of Address
| 4 | Load REG from value| Register (0-7) |Upper 8 bits of Value| Lower 8 bits of Value
| 5 | Load REG from Addr. from REG| Register (0-7) | | Register (0-8) 
| 6 | Load REG from from REG| Register (0-7) | | Register (0-8) 
| 7 | Store REG to Addr. | Register (0-8) |Upper 8 bits of Address | Lower 8 bits of Address
| 8 | Store REG to Addr. from  REG| Register (0-8) |   | Register (0-8) 
| 9 | Set ALU Operation flag | Value (0-15)
| 10 | Set IO output flag | Value (0-255)
| 11 | Send value |   |Upper 8 bits of Value| Lower 8 bits of Value
| 12 | Send from REG| Register (0-8)
| 13 | Receive into REG| Register (0-7)
| 14 |
| 15 | Jump if ALU zero |   |Upper 8 bits of Value| Lower 8 bits of Value
| 16 | Jump if not ALU zero |   |Upper 8 bits of Value| Lower 8 bits of Value
| 17 | Jump if ALU carry |   |Upper 8 bits of Value| Lower 8 bits of Value
| 18 | Jump if ALU zero to REG Addr.||| Register (0-8)
| 19 | Jump if not ALU zero to REG Addr.||| Register (0-8)
| 20 | Jump if ALU carry to REG Addr.||| Register (0-8)
| 21 | Increment REG | Register (0-7)
| 22 | Decrement REG | Register (0-7)
| … |
| 255 | HALT
