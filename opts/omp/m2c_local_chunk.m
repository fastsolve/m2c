function varargout = m2c_local_chunk(varargin)
coder.inline('always');
[varargout{1:nargout}] = OMP_local_chunk(varargin{:});
