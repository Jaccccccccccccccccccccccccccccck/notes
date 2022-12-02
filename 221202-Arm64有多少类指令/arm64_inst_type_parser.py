def parse(file_path):
    type_set = set()
    with open(file_path) as f:
        lines = f.readlines()
        for line in lines:
            if line.isspace():
                continue
            types = line.split(':')[0]
            if types.endswith(')'):
                types = types.split('(')[0].strip()
            for type in types.split(','):
                type_set.add(type)
                # print(str(type_set.__len__()) + ":" + type)
    print(file_path + " types: " + str(type_set.__len__()))

if __name__ == '__main__':
    parse('./arm64_base_insts.txt')
    parse('./arm64_SIMD_FP_insts.txt')
    parse('./arm64_sve_insts.txt')