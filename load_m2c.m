function load_m2c

% Startup script for loading M2C.
% The script must be run in the M2C Root directory.

persistent loaded;

% Load only once
if ~isempty(loaded)
  return
else
  loaded = true;
end

warning('off', 'MATLAB:pfileOlderThanMfile');
warning('off', 'MATLAB:mex:GccVersion')
warning('off', 'MATLAB:mex:GccVersion_link');

% Set m2croot explicitly to bypass a bug in Octave 4.2.1
m2croot = fileparts(which('load_m2c'));
if m2croot == '.'
    m2croot=pwd;
end
if ispc
    m2croot = strrep(m2croot,'\','/');
end

addpath(m2croot); %#ok<*MCAP>
addpath([m2croot '/util']);
addpath([m2croot '/api']);
addpath([m2croot '/api/ctypes']);
addpath([m2croot '/api/mtypes']);

% Add path for matrix operations
addpath([m2croot '/api/crs']);
addpath([m2croot '/api/ccs']);
addpath([m2croot '/api/dense/geom']);
addpath([m2croot '/api/dense/vec']);
addpath([m2croot '/api/dense/solve']);
addpath([m2croot '/api/dense/tiny']);
addpath([m2croot '/api/dense/tensor']);

% Add path for MPI
addpath([m2croot '/api/mpi4m']);
addpath([m2croot '/api/mpi4m/mpi']);
addpath([m2croot '/api/mpi4m/util']);

% Add path for OpenMP
addpath([m2croot '/api/multicore']);
addpath([m2croot '/api/omp4m']);

if ~isempty(m2c_cuda_opts)
    % Add path for CUDA
    addpath([m2croot '/api/cuda']);
    addpath([m2croot '/api/cuda/cuBLAS']);
end

% Add dummy API if Coder does not exist
if ~exist('coder.p', 'file')
    addpath([m2croot '/opts/No_coder']);
end

if isoctave
    % Initialize OpenMP
    if isempty(getenv('OMP_NUM_THREADS'))
        fprintf(1, 'Set OMP_NUM_THREADS to %d.\n', nproc);
        setenv('OMP_NUM_THREADS', int2str(nproc));
    end

    addpath([m2croot '/util/octave']);
    addpath([m2croot '/opts/No_coder/octave']);

    % Initialize MPI
    try
      init_mpi
    catch
      warning('Could not initialize MPI');
    end
else
    addpath([m2croot '/util/getMD5']);
    [~, ~, GetMD5_ext] = fileparts(which('GetMD5'));
    if isequal(GetMD5_ext, '.m')
        InstallMex('GetMD5.c');
    end
end
