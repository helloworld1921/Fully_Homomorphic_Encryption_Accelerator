// call server side addition operation
vec cli_addition(vec &c1, vec &c2)
{
	return serv_addition(c1, c2);
}

// server side addition operation, return the vector addition of two ciphtertext
vec serv_addition(vec &c1, vec &c2)
{
	return c1 + c2;
}

// call server side linear transform operation, send the key switch matrix M from GS -> S to the server
mat cli_linear_trans(mat &G, mat &S, mat &T)
{
	// G is linear transformation matrix
	// call key_switching_accelerator in hardware
	M = keySwitchMatrix(G * S, T); // in hardware
	return serv_linear_trans(M, c);
}

// server side linear transform operation, returns c'==S(Gx) given c=Sx and M
mat serv_linear_trans(mat &M, vec &c)
{
	c_bit = bit_repr_vector(c); // in hardware
	return M * c_bit;
}
