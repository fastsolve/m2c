function n = ompGetNumProcs %#codegen
%Returns the number of processors that are available to the program.

%#codegen -args {}

n = int32(1);
if ~strcmp(coder.target,'rtw'); return; end

momp_require_header
coder.inline('always');
coder.allowpcode('plain')

n = coder.ceval('omp_get_num_procs');
