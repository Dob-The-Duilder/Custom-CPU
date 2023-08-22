SWAP = False
OP   = 0

regConvert = ["a", "b", "c", "d", "e", "f", "sr", "pc", "ao"]

variables = {'a': 0, 'b': 1, 'c': 2, 'd': 3, 'e': 4, 'f': 5, 'sr': 6, 'pc': 7, 'ao': 8}

def defineValue(token, ProgramLine):
    if not token[1].isidentifier():
        raise Exception(f"ERROR in line {ProgramLine}: Invalid varible name '{token[1]}'")
    if token[1] in regConvert:
        raise Exception(f"ERROR in line {ProgramLine}: Varible name '{token[1]}' is reserved")
    variables[token[1]] = getValue(token[3])

def getValue(value: str, ProgramLine=0):
    """ 0x0000
        0b0000
          0000
           'a'
       varible
    """
    
    if "'" in value: return convert.index(value[-2])
    
    if value[:2] == "0x": return int(value, base = 16)
    if value[:2] == "0b": return int(value, base =  2)
    
    if value[0].isdigit(): return int(value)
    
    return variables[value]
    
# Command 0
def NOOP():
    return (0x00, 0x00, 0x00, 0x00)

# Command 1
def MEMWAIT():
    return (0x01, 0x00, 0x00, 0x00)

# Command 2
def SW():
    global SWAP
    SWAP = not SWAP
    return (0x02, 0x00, 0x00, 0x00)

# Command 3-6
def LD(token, ProgramLine):
    #   Setting output register for load function
    registerOut = getValue(token[1])
    
    if len(token) == 3:
        if "$" in token[2]:
            #   Instruction 0x03/3: Load from memory address
            memAddress = getValue(token[2][1:])
            return (0x03, registerOut, memAddress >> 8, memAddress & 0xFF)
        else:
            #   Instruction 0x04/4: Load from hard-coded value
            hardValue = getValue(token[2])
            return (0x04, registerOut, hardValue >> 8, hardValue & 0xFF)
    else:
        if "$" in token[2]:
            #   Instruction 0x05/5: Load from memory address pointed to by register
            memAddress = getValue(token[3])
            return (0x05, registerOut, 0x00, memAddress)
        else:
            #   Instruction 0x06/6: Load from register
            sourceRegister = getValue(token[3])
            return (0x06, registerOut, 0x00, sourceRegister)

# Command 7-8
def SR(token, ProgramLine):
    #   Setting locations for store function
    registerIn = getValue(token[1], token)
    
    if len(token) == 3:
        #   Instruction 0x07/7: Store to memory address
        memAddress = getValue(token[2][1:], token)
        return (0x07, registerIn, memAddress >> 8, memAddress & 0xFF)
    else:
        #   Instruction 0x08/8: Store to memory address pointed to by register
        memAddress = getValue(token[3], token)
        return (0x08, registerIn, 0x00, memAddress)

# Command 9
def ST(token, ProgramLine):
    global OP
    if token[1] not in ('AND', 'OR', 'XOR', 'NOT', 'SHL', 'SHR', 'RTL', 'RTR', 'ADD', 'SUB', 'MUL', 'DIV', 'MOD'):
        raise Exception(f"ERROR in line {ProgramLine}: Invalid math operation, expected AND, OR, XOR, NOT, SHL, SHR, RTL, RTR, ADD, SUB, MUL, DIV, or MOD")
    match token[1]:
        case 'AND':
            opCode = 15
        case 'OR':
            opCode = 14
        case 'XOR':
            opCode = 13
        case 'NOT':
            opCode = 12
        case 'SHL':
            opCode = 11
        case 'SHR':
            opCode = 10
        case 'RTL':
            opCode = 9
        case 'RTR':
            opCode = 8
        case 'ADD':
            opCode = 4
        case 'SUB':
            opCode = 3
        case 'MUL':
            opCode = 2
        case 'DIV':
            opCode = 1
        case 'MOD':
            opCode = 0
        case _:
            raise Exception(f"Invalid Math Operation: {token[1]}")
    OP = opCode
    return (0x09, opCode, 0x00, 0x00)

# Command 10
def IO(token, ProgramLine):
    #   Set Artificial register and append run log
    return (0x0A, getValue(token[1]), 0x00, 0x00)

# Command 11-12
def SD(token, ProgramLine):
    if "x" in token[1]:
        value = getValue(token[1])
        return (0x0B, 0x00,  value >> 8, value & 0xFF)
    else:
        return (0x0C, getValue(token[1]), 0x00, 0x00)

# Command 13
def RC(token, ProgramLine):
    return (0x0D, getValue(token[1]), 0x00, 0x00)

# Command 14
def JP(token, ProgramLine, value):
    return (0x0E, 0x00, value >> 8, value & 0xFF)

# Command 15
def JZ(token, ProgramLine, value):
    return (0x0F, 0x00, value >> 8, value & 0xFF)

# Command 16
def JN(token, ProgramLine, value):
    return (0x10, 0x00, value >> 8, value & 0xFF)

# Command 17
def JC(token, ProgramLine, value):
    return (0x11, 0x00, value >> 8, value & 0xFF)

# Command 18
def IC(token, ProgramLine):
    return (0x12, getValue(token[1]), 0x00, 0x00)

# Command 19
def DC(token, ProgramLine):
    return (0x13, getValue(token[1]), 0x00, 0x00)

# Command 255
def HALT():
    return (0xFF, 0x00, 0x00, 0x00)

#End of CPU Instructions

def ifReplace(token, ProgramLine):
    #   b < 0x3f
    operation = token[1][1:-1].split(' ')
    match operation[1]:
        case '>' :
            jumpType = "JumpCarry"
            final = mathReplace(f"MATH ao = {operation[0]} - {operation[2]}".split(), ProgramLine)
            final.append(IC(["Increment", "b"], ProgramLine))
        case '<' :
            jumpType = "JumpCarry"
            final = mathReplace(f"MATH ao = {operation[0]} - {operation[2]}".split(), ProgramLine)
            final.append(IC(["Increment", "b"], ProgramLine))
            
        case '==':
            jumpType = "JumpNotZero"
            final = mathReplace(f"MATH ao = {operation[0]} - {operation[2]}".split(), ProgramLine)
        case '!=':
            jumpType = "JumpZero"
            final = mathReplace(f"MATH ao = {operation[0]} - {operation[2]}".split(), ProgramLine)
        case '<=':
            jumpType = "JumpCarry"
            final = mathReplace(f"MATH ao = {operation[2]} - {operation[0]}".split(), ProgramLine)
        case '>=':
            jumpType = "JumpCarry"
            final = mathReplace(f"MATH ao = {operation[0]} - {operation[2]}".split(), ProgramLine)
    
    return jumpType, final

opDecode = ["&", "|", "^", "!", "<", ">", "<<", ">>", "", "", "", "+", "-", "*", "/", "%"]
def mathReplace(token, ProgramLine):
    global OP
    operation = token[1:]
    final = []
    
    if len(operation) != 5: raise Exception(f"ERROR in line {ProgramLine}: Math instruction contains too many values/operations")
    
    if operation[3] not in opDecode:
        raise Exception(f"ERROR in line {ProgramLine}: Invalid math operation '{operation[3]}'")
    if OP != (15 - opDecode.index(operation[3])):
        final.append((0x09, 15 - opDecode.index(operation[3]), 0x00, 0x00))
        OP = 15 - opDecode.index(operation[3])
    
    if operation[2] != "a":
        if operation[2] in regConvert:
            final.append(LD(["Load", "a", "<<", operation[2]], ProgramLine))
        else:
            final.append(LD(["Load", "a", operation[2]], ProgramLine))
        
    if operation[4] != "b":
        if operation[4] in regConvert:
            final.append(LD(["Load", "b", "<<", operation[4]], ProgramLine))
        else:
            final.append(LD(["Load", "b", operation[4]], ProgramLine))
    
    if operation[0] != "ao":
        if operation[0] in regConvert:
            final.append(LD(["Load", operation[0], "<<", "ao"], ProgramLine))
        else:
            final.append(SR(["Store", "ao", operation[0]], ProgramLine))
    
    return final


# Artificial Commands
UpperROM = (" ", "!", "@", "#", "$", "%", "^", "&", "*", "(", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", ")", "{", "}", "<", ">", "_", "+", "~", "|", "?", '"', ":", "◤", "◢", "◣", "◥", "✘", "┘", "└", "┌", "┐", "┼", "┬", "┤", None, "\\t", None, "\\n")
LowerROM = (" ", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "0", "[", "]", ",", ".", "-", "=", "`","\\", "/", "'", ";", "█", "▀", "■", "▄", "✔", "→", "←", "↑", "↓", "─", "┴", "├",  None, "\\t", None, "\\n")

# Character Send
def SS(token, ProgramLine):
    if token[1][0] != '"': raise Exception(f"ERROR in line {ProgramLine}: Expected ' \" ' to begin string")
    if token[1][-1] != '"': raise Exception(f"ERROR in line {ProgramLine}: Expected ' \" ' to end string")
    
    chars = []
    for char in token[1][1:-1]:
        #if char == '\n':
        #    if OP != "ADD": chars.append(ST(['', 'ADD'], ProgramLine))
        #    if token[2] != '2' and token[2] != '1': 
        #        chars.append(LD(['Load', '2', '<<', token[2]], ProgramLine))
        #        chars.append(LD(['Load', '1', '0x80'], ProgramLine))
        #        chars.append(LD(['Load', '2', '<<', token[2]], ProgramLine))
        
        if   char in LowerROM:
            pos = (1 << 15) + (0b10 << 6) + LowerROM.index(char)
        elif char in UpperROM:
            pos = (1 << 15) + (0b11 << 6) + UpperROM.index(char)
        else:
            raise Exception(f"ERROR in line {ProgramLine}: Invalid character in string '{char}'")
            
        chars.append(SD(["Send", hex(pos)], ProgramLine))
        chars.append(IC(["Increment", token[2]], ProgramLine))
        chars.append(SD(["Send", token[2]], ProgramLine))
    return chars

convert = [" ", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e",
           "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t",
           "u", "v", "w", "x", "y", "z", "0", "[", "]", ",", ".", "-", "=", "`","\\",
           "/", "'", ";", "█", "▀", "■", "▄", "✔", "→", "←", "↑", "↓", "─", "┴", "├",
           " ","\t", " ","\n",
           " ", "!", "@", "#", "$", "%", "^", "&", "*", "(", "A", "B", "C", "D", "E",
           "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
           "U", "V", "W", "X", "Y", "Z", ")", "{", "}", "<", ">", "_", "+", "~", "|",
           "?", '"', ":", "◤", "◢", "◣", "◥", "✘", "┘", "└", "┌", "┐", "┼", "┬", "┤",
           " ","\t", " ","\n"]

def printf(token, ProgramLine):
    if token[1][0] != '"': raise Exception(f"ERROR in line {ProgramLine}: Expected ' \" ' to begin string")
    if token[1][-1] != '"': raise Exception(f"ERROR in line {ProgramLine}: Expected ' \" ' to end string")
    
    chars = []
    prefix = 0
    for char in token[1][1:-1]:
        if char == '\\': 
            prefix = 1
            continue
        
        if not prefix:
            if char in convert:
                pos = (1 << 15) + convert.index(char)
            else:
                raise Exception(f"ERROR in line {ProgramLine}: Invalid character in string '{char}'")
        else:
            match(char):
                case 't': pos = (1 << 15) + 61
                case 'b': pos = (1 << 15) + 62
                case 'n': pos = (1 << 15) + 63
            prefix = 0
        
        chars.append(SD(["Send", hex(pos)], ProgramLine))
    return chars
