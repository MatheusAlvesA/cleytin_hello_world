import sys, os, json, re, base64

GAME_ROM_ADDRESS = 0x100000

def align_to_64kb(pointer):
    anchor = 64 * 1024 # 64kb
    if(pointer % anchor == 0):
        return pointer
    return pointer + (anchor - (pointer % anchor))


def get_project_name():
    contents = ""
    with open('CMakeLists.txt') as f:
        contents = f.read()
    r = re.search("project\((.+)\)", contents)
    if(r is None):
        print("Não foi possível encontrar o nome do projeto")
        sys.exit(1)
    return r.group(1)


def generate_cpp_header(compiled_banks, start_pointer):
    r = "#ifndef _STORAGE_H\n"
    r += "#define _STORAGE_H\n\n"

    bank_ptr = start_pointer
    for bank in compiled_banks:
        r += "#define " + bank["key"] + " " + str(bank_ptr) + "\n"
        r += "#define " + bank["key"] + "_size " + str(len(bank["payload"])) + "\n\n"
        for variable in bank["pointers"]:
            r += "#define " + variable["key"] + " " + str(variable["pointer"]) + "\n"
            r += "#define " + variable["key"] + "_size " + str(variable["size"]) + "\n"
        bank_ptr += len(bank["payload"])
        bank_ptr = align_to_64kb(bank_ptr)
        r += "\n"

    r += "\n#endif\n"
    return r


def generate_bin(compiled_banks, bin_size, ptr_start):
    if((ptr_start ) <= bin_size):
        print("Tamanho do binário configurado deve ser maior que o tamanho do binário compilado (" + str(bin_size) + ")")
        sys.exit(1)
    
    r = bytearray()
    r += bytearray([0x42] * (ptr_start - (GAME_ROM_ADDRESS + bin_size)))
    bank_ptr = ptr_start
    for bank in compiled_banks:
        new_bank_ptr = align_to_64kb(bank_ptr)
        if(new_bank_ptr > bank_ptr):
            r += bytearray([0x42] * (new_bank_ptr - bank_ptr))
        r += bytearray(bank["payload"])
        bank_ptr = new_bank_ptr + len(bank["payload"])
    return r


def compile_bank(metadata):
    key = "storage_" + metadata["key"]
    pointer = 0
    payload = []
    pointers = []
    for var in metadata["data"]:
        parsed_data = base64.b64decode(var["data"])
        payload += parsed_data
        pointers.append({
            "key": key + "_" + var["key"],
            "pointer": pointer,
            "size": len(parsed_data),
        })
        pointer += len(parsed_data)

    if(len(payload) > 4 * 1000 * 1024):
        print("Banco " + metadata["key"] + " é muito grande (" + str(len(payload)) + " bytes). Max: 4MB")
        os.exit(1)

    return {
        "key": key,
        "payload": payload,
        "pointers": pointers,
    }


def compile(project_name):
    contents = ""
    with open('storage.json') as f:
        contents = f.read()
    json_data = json.loads(contents)
    ptr_start = align_to_64kb(json_data["maxBinSize"] + GAME_ROM_ADDRESS)
    compiled_banks = [ compile_bank(b) for b in json_data["banks"] ]

    header_text = generate_cpp_header(compiled_banks, ptr_start)
    with open(json_data["headerPath"], 'w') as f:
        f.write(header_text)
    
    bin_file_path = './build/' + project_name + '.bin'
    os.system("idf.py build")
    bin_size = os.path.getsize(bin_file_path)

    bin_data = generate_bin(compiled_banks, bin_size, ptr_start)
    with open('./build/storage.bin', 'wb') as f:
        f.write(bin_data)
    with open(bin_file_path, 'ab') as f:
        f.write(bin_data)


def print_help():
    print("Comandos válidos:")
    print(">  compile")


def main():
    project_name = get_project_name()
    commands = sys.argv[1:]
    if(len(commands) == 0):
        print_help()
        sys.exit(1)
    
    command = commands[0]
    if(command == "compile"):
        compile(project_name)
    else:
        print("Comando inválido: " + command)
        print_help()
        sys.exit(1)


if __name__ == "__main__":
    main()
