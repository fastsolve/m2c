function z = spVecAdd_Fixed(x, y, z)
% Example function for adding two vectors.

%#codegen -args {coder.typeof(struct('is', m2c_intvec(10000), 'vals', m2c_vec(10000), 'len', int32(0))),
%#codegen coder.typeof(struct('is', m2c_intvec(10000), 'vals', m2c_vec(10000), 'len', int32(0))),
%#codegen coder.typeof(struct('is', m2c_intvec(10000), 'vals', m2c_vec(10000), 'len', int32(0)))}

[istart, iend] = m2c_local_chunk(x.len);

for i=istart:iend
    z.vals(z.is(i)) = x.vals(x.is(i)) + y.vals(y.is(i));
end

%!shared x, y, z
%!test
%! x= struct('is', int32(1:10000)', 'vals', ones(10000,1), 'len', int32(10000));
%! y= struct('is', int32(1:10000)', 'vals', ones(10000,1), 'len', int32(10000));
%! z= struct('is', int32(1:10000)', 'vals', rand(10000,1), 'len', int32(10000));
%! 
%! m2c -force -O3 -mex tests/spVecAdd_Fixed
%! z = spVecAdd_Fixed(x, y, z);
%! assert(all(z.vals==2));

% %!test
% %! m2c -remove-emx -force -O3 -mex tests/spVecAdd_Fixed
% %! z = spVecAdd_Fixed(x, y, z);
% %! assert(all(z.vals==2));

%!test
%! m2c -omp -force -O3 -mex tests/spVecAdd_Fixed
%! z = spVecAdd_Fixed(x, y, z);
%! assert(all(z.vals==2));

% %!test
% %! m2c -nvcc -force -O3 -mex tests/spVecAdd_Fixed
% %! z = spVecAdd_Fixed(x, y, z);
% %! assert(all(z.vals==2));

% %!test
% %! m2c -remove-emx -nvcc -force -O3 -mex tests/spVecAdd_Fixed
% %! z = spVecAdd_Fixed(x, y, z);
% %! assert(all(z.vals==2));
