// Addition
vec cli_addition(vec &c1, vec &c2)
{
	return serv_addition(c1, c2);
}

vec serv_addition(vec &c1, vec &c2)
{
	return c1 + c2;
}

// Linear Transform
mat cli_linear_trans(mat &G, mat &S, mat &T)
{
	// G is linear transformation matrix
	// call key_switching_accelerator in the  hardware
	M = keySwitchMatrix(G * S, T);
	return serv_linear_trans(M, c);
}

mat serv_linear_trans(mat &M, vec &c)
{
	// c = Sx and M is the key switch matrix from GS to S')
	c_bit = bit_repr_vector(c); // in hardware
	return M * c_bit;
}

mat keySwitchMatrix(mat S, mat T)
{
	mat S * = bit_repr_matrix(S); // in hardware
}