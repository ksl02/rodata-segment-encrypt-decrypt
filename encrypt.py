import sys
from io import FileIO
sys.path.append('elfReader/')
import pathlib
from elfReader import ELFReader
from symbols import SymbolTypes
import ctypes

def syntax():
    print("Syntax:")
    print("python3 encrypt.py <file_to_encrypt> <output_file> <crypto_libname>")

if __name__ == "__main__":
    if len(sys.argv) < 4:
        syntax()
        exit()

    output = open(sys.argv[2],"wb")
    libname = pathlib.Path().absolute() / sys.argv[3]
    c_lib = ctypes.CDLL(str(libname),winmode=0)
    print(sys.argv[1],"rb")
    with open(sys.argv[1],"rb") as f:
        io = FileIO(f.fileno())
        er = ELFReader(io)

        #Can add more sections to encrypt here. Find bounds of section
        #via our defined symbols in dummy.cpp rather than section addresses
        #due to merging of sections by the linker
        bounds = {"rodata":{"start":None,"end":None}}
        for s in er.symbols.get(SymbolTypes.STT_NOTYPE):
            if s.name == "START_RODATA":
                bounds["rodata"]["start"] = s.addr
            elif s.name == "END_RODATA":
                bounds["rodata"]["end"] = s.addr

        er.seek2Offset(0)
        data = er.read()
        er.seek2Offset(0)
        
        for section in bounds:
            start = bounds[section]["start"]
            end = bounds[section]["end"]
            size = end - start
            print("Encrypting "+section+"...")
            print("Start:",start)
            print("End:",end)
            print("--------------------")
            char_array = ctypes.c_char * size
            data_encrypt = char_array.from_buffer_copy(data[start:end])
            c_lib.encrypt(data_encrypt,size)
            data = data[:start] + data_encrypt.raw + data[end:]

    output.write(data)
    output.close()