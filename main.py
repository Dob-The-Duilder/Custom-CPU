import cpu as cpu
import os
import subprocess



def ASMtoBYTE(source, boot=False, offset=0):
    b = []
    b.append(cpu.NOOP())
    
    lines = []
    for _ in range(0, offset):
        lines.insert(0,'NOOP')
    
    #   Load in program instructions
    file = open(source, encoding="utf8")
    lines.extend(file.read().replace("::", "\n").split("\n"))
    file.close()
    lines = list(filter(None, lines))
    final = []
    
    #print(lines)
    
    #      Assignable Register Decleration (Each item is one register)
    #         1 MathReg1 : Number from which MathReg2 will be added or subtracted from
    #         2 MathReg2 : Number which is added or subtracted from MathReg1
    #         3 GenReg1  : Simple General Register
    #         4 GenReg2  : Simple General Register
    #
    #         5 StatReg (Lower 8) : Set what peripheral main bus is connected to
    #         5 StatReg (Upper 8) : Settings
    #              Bits 0-3 : Math Operation Selection
    #              Bits 4   : 0 = Upper Memory Select, 1 = Lower Memory Select
    #              Bits 5   : Carry bit
    #              Bits 6   : Zero bit (High if accumilator zero)
    #              Bits 7   : Not Zero
    #          
    #         6 Accumilator : Output of math opperations                (Read-Only)
    #         7 ProgramCnt  : Position that should be read from memory  (Read-Only)
    #         8 StackPoint  : Overal count of cpu cycle                 (Read-Only)

    registerList = [bin(0), bin(0), bin(0), bin(0), bin(0), 0, -1, -1]
    PrgmCnt = 0
    jumpPoints = [0]
    ifPoints   = [0]
    
    markers    = {"_" : 0}
    recheck    = []
    # Main Program Thread
    while PrgmCnt < len(lines)-1:
        #   Initilize key registers and Inciment
        registerList[6] += 1
        registerList[7] += 1
        PrgmCnt, StkPnt = registerList[6:]
        
        #   If line is empty or commented skip
        line = lines[PrgmCnt]
        if line.isspace(): continue
        while line[0] == ' ':
            line = line[1:]
        if line[0] == '#' or line == '\n':
            continue
        final.append([line,len(b)])
            
        line = line.replace('\n', '')
        tok = line.split(' ', 1)
        
        match tok[0]:
            case 'CharSend':
                if tok[1].isdigit(): 
                    break
                pFrom =  tok[1].index('"')
                pTo   = tok[1].rindex('"')

                result = tok[1][pFrom:pTo+1]
                tok = tok[1].split()
                tok = ['CharSend', result, tok[-1]]
            case 'printf':
                if tok[1].isdigit():
                    break
                pFrom = tok[1].index('"')
                pTo   = tok[1].rindex('"')

                result = tok[1][pFrom:pTo+1]
                tok = tok[1].split()
                tok = ['printf', result]
            case 'IF':
                if '(' in tok[1]:
                    pFrom = tok[1].index('(')
                    pTo   = tok[1].rindex(')')

                    result = tok[1][pFrom:pTo+1]
                    tok = ['IF', result]
                else:
                    tok[1:] = tok[1].split(' ')
            case 'SWAP':
                pass
            case 'HALT':
                pass
            case 'JUMPIN':
                pass
            case 'NOOP':
                pass
            case 'MEMWAIT':
                pass
            case 'Jump':
                pass
            case 'JumpZero':
                pass
            case 'JumpNotZero':
                pass
            case 'JumpCarry':
                pass
            case 'JUMPIF':
                pass
            case 'JUMPPOINT':
                markers[tok[1]] = len(b)-1
                continue
            case 'END':
                tok = ifPoints[-1].split(' ')
                match tok[0]:
                    case 'JumpZero':
                        b[int(tok[1])-1] = cpu.JZ(tok, PrgmCnt, len(b)-2)
                    case 'JumpNotZero':
                        b[int(tok[1])-1] = cpu.JN(tok, PrgmCnt, len(b)-2)
                    case 'JumpCarry':
                        b[int(tok[1])-1] = cpu.JC(tok, PrgmCnt, len(b)-2)
                if len(ifPoints) > 1: ifPoints.pop()
                continue
            case _:
                tok[1:] = tok[1].split(' ')
        
        match tok[0]:
            case 'JUMPIN':
                jumpPoints.append(len(b)-1)
            case 'IF':                
                if "(" in tok[1]:
                    tok[1], chars = cpu.ifReplace(tok, PrgmCnt)
                    for char in chars: b.append(char)
                b.append(cpu.NOOP())
                ifPoints.append(' '.join([tok[1], str(len(b))]))
            case 'CharSend':
                chars = cpu.SS(tok, PrgmCnt)
                for char in chars: b.append(char)
            case 'printf':
                chars = cpu.printf(tok, PrgmCnt)
                for char in chars: b.append(char)
            case 'MATH':
                maths = cpu.mathReplace(tok, PrgmCnt)
                for math in maths: b.append(math)
            case 'VAR':
                cpu.defineValue(tok, PrgmCnt)
                                
            case 'MEMWAIT':
                b.append(cpu.MEMWAIT())
            case 'Load':
                b.append(cpu.LD(tok, PrgmCnt))
            case 'Store':
                b.append(cpu.SR(tok, PrgmCnt))
            case 'SetIO':
                b.append(cpu.IO(tok, PrgmCnt))
            case 'Send':
                b.append(cpu.SD(tok, PrgmCnt))
            case 'Receive':
                b.append(cpu.RC(tok, PrgmCnt))
            case 'Jump':
                if len(tok) == 1:
                    b.append(cpu.JP(tok, PrgmCnt, jumpPoints[-1] - 1))
                    if len(jumpPoints) > 1: jumpPoints.pop()
                else:
                    try:
                        b.append(cpu.JP(tok, PrgmCnt, int(markers[tok[1]])-1))
                    except KeyError:
                        recheck.append(["Jump", len(b)-1, tok[1]])
                        b.append(cpu.NOOP())
            case 'JumpZero':
                if len(tok) == 1:
                    b.append(cpu.JZ(tok, PrgmCnt, jumpPoints[-1] - 1))
                    if len(jumpPoints) > 1: jumpPoints.pop()
                else:
                    try:
                        b.append(cpu.JZ(tok, PrgmCnt, int(markers[tok[1]])))
                    except KeyError:
                        recheck.append(["JumpZero", len(b)-1, tok[1]])
                        b.append(cpu.NOOP())
            case 'JumpNotZero':
                if len(tok) == 1:
                    b.append(cpu.JN(tok, PrgmCnt, jumpPoints[-1] - 1))
                    if len(jumpPoints) > 1: jumpPoints.pop()
                else:
                    try:
                        b.append(cpu.JN(tok, PrgmCnt, int(markers[tok[1]])))
                    except KeyError:
                        recheck.append(["JumpNotZero", len(b)-1, tok[1]])
                        b.append(cpu.NOOP())
            case 'JumpCarry':
                if len(tok) == 1:
                    b.append(cpu.JC(tok, PrgmCnt, jumpPoints[-1] - 1))
                    if len(jumpPoints) > 1: jumpPoints.pop()
                else:
                    try:
                        b.append(cpu.JC(tok, PrgmCnt, int(markers[tok[1]])))
                    except KeyError:
                        recheck.append(["JumpCarry", len(b)-1, tok[1]])
                        b.append(cpu.NOOP())
            case 'JUMPIF':
                if "(" in tok[1]:
                    tok[0], chars = cpu.ifReplace(tok, PrgmCnt)
                    for char in chars: b.append(char)
                match tok[0]:
                    case "JumpCarry":
                        b.append(cpu.JC(tok, PrgmCnt, jumpPoints[-1] - 1))
                    case "JumpNotZero":
                        b.append(cpu.JN(tok, PrgmCnt, jumpPoints[-1] - 1))
                    case "JumpZero":
                        b.append(cpu.JZ(tok, PrgmCnt, jumpPoints[-1] - 1))
                if len(jumpPoints) > 1: jumpPoints.pop()
            case 'SWAP':
                b.append(cpu.SW())
            case 'Increment':
                b.append(cpu.IC(tok, PrgmCnt))
            case 'Decrement':
                b.append(cpu.DC(tok, PrgmCnt))
            case 'SetOP':
                b.append(cpu.ST(tok, PrgmCnt))
            case 'HALT':
                b.append(cpu.HALT())
            case _:
                b.append(cpu.NOOP())
    
    for type, pos, keyValue in recheck:
        match type:
            case 'Jump':
                b[pos + 1] = cpu.JP('', PrgmCnt, int(markers[keyValue.strip()])-1)
            case 'JumpZero':
                b[pos + 1] = cpu.JZ('', PrgmCnt, int(markers[keyValue])-1)
            case 'JumpNotZero':
                b[pos + 1] = cpu.JN('', PrgmCnt, int(markers[keyValue])-1)
            case 'JumpCarry':
                b[pos + 1] = cpu.JC('', PrgmCnt, int(markers[keyValue])-1)
    
    while len(b) < 512 and boot:
        b.append(cpu.NOOP())
    
    b = b[offset:]
    
    with open(os.path.dirname(source) + "/Program Log.log", "w", encoding="utf-8") as out:
        for idx, function in enumerate(b):
            while final and final[0][1] == idx:
                out.write(f"{final[0][0]}\n")
                final.pop(0)
            if idx:
                out.write(f"{idx+offset}: {function}\n")
                
    with open(os.path.dirname(source) + f"/{source[4:-4]}.bin", "wb") as file:
        buffer = []
        for code in b:
            buffer.extend(code)
        some = bytearray(buffer[4:])
        immutable = bytes(some)
        file.write(immutable)
    
    return b

ASMtoBYTE("roms/test.lep")

if 1 == 0:
    subprocess.call([r'C:\Users\kilom\OneDrive\Desktop\TBD_Computer\Hardware\Emulator\build\build.bat'])

"""
g++ "../src/main.cpp" -o "main.exe"

char convert[128] = {' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e',
                    'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                    'u', 'v', 'w', 'x', 'y', 'z', '0', '[', ']', ',', '.', '-', '=', '`','\\',
                    '/','\'', ';', 219, 223, 254, 220, '✔', '→', '←', '↑', '↓', 196, 193, 195,
                    ' ','\t', ' ','\n',
                    255, '!', '@', '#', '$', '%', '^', '&', '*', '(', 'A', 'B', 'C', 'D', 'E',
                    'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                    'U', 'V', 'W', 'X', 'Y', 'Z', ')', '{', '}', '<', '>', '_', '+', '~', 179,
                    '?', '"', ':', '◤', '◢', '◣', '◥', '✘', 217, 192, 218, 119, 197, 194, 180,
                    ' ','\t', ' ','\n'};

"""