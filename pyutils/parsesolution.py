def isint(x):
	try:
		t = int(x)
	except ValueError:
		return False
	return True

def parsesolution(path, problem):
	f = open(path, 'r')
	res = dict()
	res['routes'] = []
	nodes = set()
	sol_was = False
	for line in f.readlines():
		if 'Solution' in line:
			if sol_was:
				break
			sol_was = True
		if line[:5] == 'Route':
			v = line.split(':')[-1].split()
			if False in list(map(isint, v)):
				return None
			if len(v) == 0:
				return None
			res['routes'].append(list(map(int, v)))
	if len(res['routes']) == 0:
		return None
	res['cost'] = 0
	res['cars'] = []
	for route in res['routes']:
		c, d = 0, 0
		prev = 0
		for x in route:
			if x < 1 or x >= problem['n']:
				return None
			nodes.add(x)
			c += problem['d'][x]
			x1 = problem['v'][x][0]
			y1 = problem['v'][x][1]
			x2 = problem['v'][prev][0]
			y2 = problem['v'][prev][1]
			d += ((x1 - x2) ** 2 + (y1 - y2) ** 2) ** 0.5
			prev = x
		x1 = problem['v'][0][0]
		y1 = problem['v'][0][1]
		x2 = problem['v'][prev][0]
		y2 = problem['v'][prev][1]
		d += ((x1 - x2) ** 2 + (y1 - y2) ** 2) ** 0.5
		if c > problem['c']:
			return None
		res['cost'] += d
		res['cars'].append({
			'cargo': c,
			'distance': d
		})
	if len(nodes) != problem['n'] - 1:
		return None
	return res