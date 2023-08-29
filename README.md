
## Instruction set and basic architecture 

(Empty column means unassigned/unnecessary)
| Inst. # | Command Name  | Input 1	| Input 2	| Input 3 |
|---|---|---|---|---|
| 0 | NOOP |   |   |   |
| 1 |    |   |   |   |
| 2 | SWAP |   |   |   |
| 3 | Load REG from Addr.| Register (0-7) |Upper 8 bits of Address | Lower 8 bits of Address|
| 4 | Load REG from value| Register (0-7) |Upper 8 bits of Value| Lower 8 bits of Value|
| 5 | Load REG from Addr. from REG| Register (0-7) | | Register (0-8) |
| 6 | Load REG from from REG| Register (0-7) | | Register (0-8) |
| 7 | Store REG to Addr. | Register (0-8) |Upper 8 bits of Address | Lower 8 bits of Address|
| 8 | Set ALU Operation flag | Value (0-15) |   |   |
| 9 | Set IO output flag | Value (0-255) |   |   |
| 10 | Send value |   |Upper 8 bits of Value| Lower 8 bits of Value|
| 11 | Send from REG| Register (0-8)    |   |
| 12 | Receive into REG| Register (0-7) |   |   |
| 13 | Jump |   |Upper 8 bits of Value| Lower 8 bits of Value|
| 14 | Jump if ALU zero |   |Upper 8 bits of Value| Lower 8 bits of Value|
| 15 | Jump if not ALU zero |   |Upper 8 bits of Value| Lower 8 bits of Value|
| 16 | Jump if ALU carry |   |Upper 8 bits of Value| Lower 8 bits of Value|
| 17 | Increment REG | Register (0-7) |   |   |
| 18 | Decrement REG | Register (0-7) |   |   |
| 19 |   |   |   |   |
| … |   |   |   |   |
| 255 | HALT |   |   |   |
