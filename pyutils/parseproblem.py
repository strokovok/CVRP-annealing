def isint(x):
	try:
		t = int(x)
	except ValueError:
		return False
	return True

def parseproblem(path):
	f = open(path, 'r')
	res = {}
	while True:
		line = f.readline()
		if not line:
			break
		tokens = line.split()
		if len(tokens) == 3 and tokens[0] == 'DIMENSION' and isint(tokens[-1]):
			res['n'] = int(tokens[-1])
		if len(tokens) == 3 and tokens[0] == 'CAPACITY' and isint(tokens[-1]):
			res['c'] = int(tokens[-1])
		if len(tokens) == 1 and tokens[0] == 'NODE_COORD_SECTION':
			res['v'] = []
			if 'n' not in res:
				return None
			for i in range(res['n']):
				line = f.readline()
				if not line:
					return None
				tokens = line.split()
				if len(tokens) != 3:
					return None
				for token in tokens:
					if not isint(token):
						return None
				res['v'].append((int(tokens[1]), int(tokens[2])))
		if len(tokens) == 1 and tokens[0] == 'DEMAND_SECTION':
			res['d'] = []
			if 'n' not in res:
				return None
			for i in range(res['n']):
				line = f.readline()
				if not line:
					return None
				tokens = line.split()
				if len(tokens) != 2:
					return None
				for token in tokens:
					if not isint(token):
						return None
				res['d'].append(int(tokens[1]))
	for p in ['n', 'c', 'v', 'd']:
		if p not in res:
			return None
	return res