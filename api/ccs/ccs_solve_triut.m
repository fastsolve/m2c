function b = ccs_solve_triut(U, b)
% ccs_solve_triut Solves U.'\b, where U is upper triangular
%     b = ccs_solve_triut(U, b)
%  The matrix is assumed to be upper triangular. The right-hand side vector
%  will be overwritten by U.'\b at output.

%#codegen -args {ccs_matrix, coder.typeof(0, [inf,1])}

coder.inline('always');

n = int32(length(U.col_ptr) - 1);

for j = 1:n
    last = U.col_ptr(j+1) - 1;
    assert(U.row_ind(last) == j && U.val(last) ~= 0);

    for k = U.col_ptr(j):(last - 1)
        i = U.row_ind(k);
        b(j) = b(j) - U.val(k) * b(i);
    end

    b(j) = b(j) / U.val(last);
end

function test %#ok<DEFNU>
%!test
%! for k=1:100
%!     T = triu(rand(10,10)); b = rand(10,1);
%!     if condest(T) < 1.e5
%!         U = ccs_createFromSparse(sparse(T));
%!         us = ccs_solve_triut(U, b);
%!         assert(norm(T' * us - b) <= 1.e-10);
%!     end
%! end
