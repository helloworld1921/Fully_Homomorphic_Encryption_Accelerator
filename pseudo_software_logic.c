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
	mat M = syscall.keySwitchMatrix(G * S, T); // compute key switch matrix in hardware
	return serv_linear_trans(M, c);
}

// server side linear transform operation, returns c'==S(Gx) given c=Sx and M
mat serv_linear_trans(mat &M, vec &c)
{
	c_bit = syscall.bit_repr_vector(c); // compute bit representation in hardware
	return M * c_bit;
}

// call server side inner product operation
// returns M, the key switch matrix from vec(S^t S) to S
mat cli_inner_product(mat &T, int w, mat &c1, mat &c2)
{
	mat S = getSecretKey(T);						// get secret key
	mat t = transpose(vectorize(transpose(S) * S)); // vec(S^t S) to S,
	mat M = syscall.keySwitchMatrix(t, T);
	return serv_inner_product(c1, c2, M, w);
}

// given two ciphertexts and the keyswitch matrix, computes an inner product
vec serv_inner_product(vec c1, vec c2, mat M, int w)
{
	vec cc = vectorize(c1 * transpose(c2));
	vec n = syscall.nearestInteger(cc, w);
	return M * syscall.bit_repr_cector(n);
}

// call server side polynomial operation
// returns M, the key switch matrix from vec(S^t S) to S
mat cli_polynomial(mat &T, mat &c, int w)
{
	mat S = getSecretKey(T); // get secret key
	mat Sp = extend(S);		 // extend secret key with constant 1
	mat t = transpose(vectorize(transpose(Sp) * Sp));
	mat M = syscall.keySwitchMatrix(t, T);
	return serv_polynomial(c, M, w);
}

// given ciphertext and the keyswitch matrix, computes an inner product
vec serv_polynomial(vec c, mat &M, int w)
{
	vec cc = vectorize(c * transpose(c));
	vec n = syscall.nearestInteger(cc, w);
	return M * syscall.bit_repr_cector(n);
}
