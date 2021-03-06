function ret = MPI_UNSIGNED_LONG
coder.inline('always');

if ~isempty(coder.target)
    ret = coder.opaque('MPI_Datatype', 'MPI_UNSIGNED_LONG');
else
    ret = mpi_get_const('MPI_UNSIGNED_LONG');
end
