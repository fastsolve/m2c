function [errCode, toplevel] = cuVecCopySubToGPU_async(n, vec, ...
    istart, inc, cuVec, incCuVec, strm)
[errCode, toplevel] = cuVecCopySubToGPU(n, vec, ...
    istart, inc, cuVec, incCuVec, strm);
