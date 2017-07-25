function b = ccs_solve_utriu(U, b, varargin)
% ccs_solve_utriu Solves U\b, where U is unit upper triangular
%     b = ccs_solve_utriu(U, b) solves U\b, where U stores the strict 
%     upper triangular part of U. The right-hand side vector will be 
%     overwritten by U\b at output.
%
%     b = ccs_solve_utriu(U, b, offset) uses b(offset+1:offset+n) 
%     instead of b for the rhs and solution vector, where n=size(U,1).
%
% See also ccs_solve_tril, ccs_solve_trilt

%#codegen -args {ccs_matrix, coder.typeof(0, [inf,1])}
%#codegen ccs_solve_utriu_3args -args {ccs_matrix, m2c_vec, int32(0)}

coder.inline('always');

if nargin < 3
    offset = int32(0);
else
    offset = int32(varargin{1});
end
n = int32(length(U.col_ptr) - 1);

for j = n:-1:1
    for k = U.col_ptr(j):(U.col_ptr(j+1) - 1)
        i = U.row_ind(k);
        % This can be done concurrently
        b(i+offset) = b(i+offset) - U.val(k) * b(j+offset);
    end
end

function test %#ok<DEFNU>
%!test
%! for k=1:100
%!     T = triu(rand(10,10), 1); b = rand(10, 1);
%!     U = ccs_createFromSparse(sparse(T));
%!     us = ccs_solve_utriu(U, b);
%!     assert(norm((T + speye(10)) * us - b) <= 1.e-10);
%! end
