function libs = lapacklib

% libs = '-LMyLAPACKPath -llapack -LBlasPath -lblas'; return;

switch computer
    case 'PCWIN'
        fprintf(2,'%s\n', ['Using LAPACK and BLAS distributed with MATLAB. To provide your own '...
            'LAPACK and BLAS libraries, edit the file "' which('lapacklib') ...
            '" to specify their path with the -L option after you have installed them.']);
        libs = '-lmwlapack -lmwblas';
    case 'PCWIN64'
        fprintf(2,'%s\n',['On 64-bit Windows platform, you must provide your own '...
            'LAPACK and BLAS libraries, since MATLAB''s built-in libraries '...
            'mwlapack and mwblas use 64-bit integers for matrix dimensions. '...
            'You might find LAPACK and BLAS at http://icl.cs.utk.edu/lapack-for-windows '...
            'and then edit the file "' which('lapacklib') ...
            '" to specify their path with the -L option.']);
        libs = '-llapack -lblas';
    case 'MACI64'
        fprintf(2,'%s\n',['Note: Using the optimized LAPACK and BLAS libraries of Mac OS X. To provide '...
            'other LAPACK and BLAS libraries, edit the file "' which('lapacklib') ...
            '" to specify their path with the -L option.']);
        libs = '-llapack -lblas';
    case 'GLNX86'
        fprintf(2,'%s\n',['Using LAPACK and BLAS distributed with MATLAB. To provide your own '...
            'LAPACK and BLAS libraries, edit the file "' which('lapacklib') ...
            '" to specify their path with the -L option.']);
        libs = '-lmwlapack -lmwblas';
    case 'GLNXA64'
        fprintf(2,'%s\n',['On 64-bit Linux platform, you must provide your own '...
            'LAPACK and BLAS libraries, since MATLAB''s built-in libraries '...
            'mwlapack and mwblas use 64-bit integers for matrix dimensions. '...
            'Most Linux distributions provide LAPACK and BLAS distributions. '...
            'Edit the file "' which('lapacklib') '" to specify their path with the -L option.']);
        libs = '-llapack -lblas';
    otherwise
        libs = '-llapack -lblas';
        % error('Unsupported platform.');
end
