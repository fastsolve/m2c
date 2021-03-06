function type = m2c_intvec(maxlen, vardim) %#codegen
% Specifies an integer (int32) column vector.
%    m2c_intvec() specifies a variable-length column vector.
%
%    m2c_intvec(c) or m2c_intvec(c, false) specifies a fixed-length 
%        column vector with up to c numbers, where c must be a constant.
%
%    m2c_intvec(c, true) specifies a variable-length integer column vector 
%         with c numbers, where c must be a constant at compile time.
%
% See also m2c_intmat, m2c_mat, m2c_vec, m2c_string

if nargin==0
    type = coder.typeof(int32(0), [inf, 1]);
elseif nargin==1 || ~vardim
    type = coder.typeof(int32(0), [maxlen, 1]);
else
    type = coder.typeof(int32(0), [maxlen, 1], [1, 0]);
end
