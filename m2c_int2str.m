function str = m2c_int2str(val) %#codegen
%Convert a scalar integer into a character string. 
%    str = m2c_int2str(val) returns a string containing the number.
% In MATLAB, the output is the same as num2str.
% In C, the output is a null-terminated character string.
% Limitation: the output of this function cannot be used for 
% concatenation with other strings.

if isempty(coder.target)
    str = [num2str(int32(val)) char(0)];
else
    % We have to use uint8 in stead of char here because of bugs in
    % MATLAB Coder in MATLAB R2016a
    t_str = coder.nullcopy(zeros(20, 1, 'uint8'));

    ptr = coder.opaque('char *');
    ptr = coder.ceval('(char *)', coder.wref(t_str));
    coder.ceval('sprintf', ptr, ...
        coder.opaque('const char *', '"%d"'), int32(val));
    str = char(t_str);
end
