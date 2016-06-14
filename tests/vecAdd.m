function z = vecAdd(x, y, z, m)
% Example function for adding two vectors.

%#codegen -args {m2c_vec, m2c_vec, m2c_vec, int32(0)}

[istart, iend] = m2c_local_chunk(m);

for i=istart:iend
    z(i) = x(i) + y(i);
end

%!test
%! m2c -force -O3 -exe tests/vecAdd
%! z = run_vecAdd_exe(ones(100,1), ones(100,1), rand(100,1), int32(100));
%! assert(all(z==2));

%!test
%! m2c -replace-emx -force -O3 -exe tests/vecAdd
%! z = run_vecAdd_exe(ones(100,1), ones(100,1), rand(100,1), int32(100));
%! assert(all(z==2));

%!test
%! m2c -replace-emx -omp -force -O3 -exe tests/vecAdd
%! z = run_vecAdd_exe(ones(10000,1), ones(10000,1), rand(10000,1), int32(10000));
%! assert(all(z==2));

%!test
%! m2c -nvcc -force -O3 -exe tests/vecAdd
%! z = run_vecAdd_exe(ones(10000,1), ones(10000,1), rand(10000,1), int32(10000));
%! assert(all(z==2));

%!test
%! m2c -replace-emx -nvcc -force -O3 -exe tests/vecAdd
%! z = run_vecAdd_exe(ones(10000,1), ones(10000,1), rand(10000,1), int32(10000));
%! assert(all(z==2));