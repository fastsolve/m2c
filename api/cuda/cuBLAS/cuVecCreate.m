function [vec, errCode, toplevel] = cuVecCreate(n, type)
%Creates a vector on a CUDA device.
%
%  [vec, errCode] = cuVecCreate(n, [type]) creates a vector of length n
%  on CUDA, where type is MCU_INT*, MCU_UINT*, MCU_DOUBLE, MCU_SINGLE,
%  MCU_COMPLEX, or MCU_DOUBLE_COMPLEX, MCU_INT*, or MCU_UINT*. If not
%  specified, then type is MCU_DOUBLE.
%
%  SEE ALSO: cuVecDestroy, cuVecCopyToGPU, cuVecCopyFromGPU

%#codegen -args {int32(0), int32(0)}
%#codegen cuVecCreate_1arg -args {int32(0)}

toplevel = nargout>2;

if nargin<2; type = MCU_DOUBLE; end

sizepe = mcuGetSizePerElement(type);

t_vec = coder.opaque('void *');
errCode = int32(0);  %#ok<NASGU>
errCode = coder.ceval('cudaMalloc', coder.wref(t_vec), n*sizepe);

vec = CuVec(t_vec, type, n, 'wrap');

if errCode && (toplevel || m2c_debug)
    m2c_error('CUDA:RuntimeError', 'cudaMalloc returned error code %s\n', cuGetErrorString(errCode));
end
end
