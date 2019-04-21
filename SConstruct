env = Environment(CPPPATH = 'include', CPPFLAGS = ['-g', '-std=c++11', '-Wall'])

def src(name, isInCatalog):
	if isInCatalog == 1:
		return 'src/' + name + '.cpp'
	else:
		return name + '.cpp'
	
def make_prog(name, sources):
	all_sources = [src(name,0), src('idexception',1)] + list(map(lambda x: src(x, 1), sources))
	env.Program(name, all_sources)

make_prog('lab1', ['vectors'])
make_prog('lab2', ['matrix'])
make_prog('lab3', ['math_abstract', 'math_matrix', 'math_vector'])
make_prog('lab4a', ['rational'])
make_prog('lab4b', ['polynomial'])
make_prog('lab5c', ['temp_polynomial', 'rational'])
