function lib2mex_exe(funcname, ldflags, opflags, args, buildexe)
% Generate a MEXFunction or main function for a C library created by m2c.
%
% See also m2c, lib2mex, lib2exe.

if nargin<1
    error('too few input arguments');
end

if nargin<2; opflags = ''; end
if nargin<3; args = ''; end

locs = regexp(funcname,'[\/\\]');
if ~isempty(locs)
    mpath = funcname(1:locs(end));
    funcname = funcname(locs(end)+1:end);
else
    mpath = '';
end

altapis = [funcname, strtrim(strrep( regexp(args, '(\w+)\s+-args', 'match'), ' -args', ''))];

% Write out C file.
outdir = [mpath 'codegen/lib/' funcname];

if exist([outdir '/' funcname '.cpp'], 'file')
    suf = 'cpp';
else
    suf = 'c';
end

if buildexe
    % Write out C code
    opts = writeCFile([funcname '_exe.' suf]);
    % Write out a build script
    writeExeScript(['ld_' funcname '.m'], opts);
else
    % Write out C code
    [opts, rtCfiles] = writeCFile([funcname '_mex.' suf]);
    % Write out a build script
    writeMexScript(['mex_' funcname '.m'], rtCfiles, opts);
end

print_README(outdir, funcname);

    function [opts, rtCfiles] = writeCFile(filename)
        outCfile = [outdir '/' filename];

        rtCfiles = dir([outdir '/*.' suf]);
        if ~isempty(rtCfiles)
            rtCfiles = sprintf( ' %s', rtCfiles(:).name);
            rtCfiles = strrep(rtCfiles, filename, '');
            rtCfiles = strrep(rtCfiles, [funcname '.'  suf],'');
        end
        [fid,msg] = fopen( outCfile, 'w');
        if (fid<0); error('lib2mex:OpenFile', msg); end
        
        if buildexe
            fprintf( fid, '%s\n', ...
                '/*', [' * ' funcname '_exe.' suf], ' *', ...
                [' * Auxiliary code for standalone executable of ' funcname], ' *', ...
                ' * C source code generated by m2c.', ...
                '*', ' */', '', ...
                '#include "matrix.h"', '');
        else
            fprintf( fid, '%s\n', ...
                '/*', [' * ' funcname '_mex.' suf], ' *', ...
                [' * Auxiliary code for mexFunction of ' funcname], ' *', ...
                ' * C source code generated by m2c.', ...
                '*', ' */', '', ...
                '#include "mex.h"', ...
                '#define BUILD_MEX', '');
        end
        
        fprintf( fid, '%s\n', ...
            '/* Include the C file generated by codegen in lib mode */', ...
            ['#include "' funcname '.h"' suf(2:end)], '#include "m2c.c"',  ...
            ['#include "' funcname '.' suf '"']);
        
        if buildexe
            errMsgFunc = 'm2cErrMsgIdAndTxt';
            fprintf( fid, '%s\n', ...
                '/* Include declaration of some helper functions. */', ...
                '#include "lib2mex_helper.c"', ...
                '#include "lib2exe_helper.c"', '');
        else
            errMsgFunc = 'mexErrMsgIdAndTxt';

            fprintf( fid, '%s\n', ...
                '/* Include declaration of some helper functions. */', ...
                '#include "lib2mex_helper.c"', '');
        end
        
        % Parse input arguments from C files.
        alt_nlhs = zeros(length(altapis),1);
        alt_nrhs = zeros(length(altapis),1);
        for i=1:length(altapis)
            % Parse input arguments from C files.
            [vars, ret, nlhs, nrhs, SDindex] = parse_cgfiles( funcname, altapis{i}, mpath);
            if ~isempty(SDindex)
                fprintf(2, ['lib2mex Info: Codegen generated a StackData object "%s" of type "%s". ' ...
                    'This probably indicates that you have some large, fixed-size local buffers in some subroutines ' ...
                    'that Codegen grouped into an object. See "%scodegen/lib/%s/%s_types.h" for the definition and content of the object.\n'], ...
                    vars(SDindex).name, vars(SDindex).type, mpath, funcname, funcname);
            end
            fprintf( fid, '%s\n', print_apiFunction(funcname, altapis{i}, nlhs, nrhs, vars, ret, SDindex, errMsgFunc));
            alt_nlhs(i) = nlhs; alt_nrhs(i) = nrhs;
        end        
        
        if buildexe
            fprintf( fid, '%s', print_exeFunction(altapis, alt_nlhs, alt_nrhs));
        else
            fprintf( fid, '%s', print_mexFunction(altapis, alt_nlhs, alt_nrhs));
        end
        
        fclose(fid);
        
        if exist('plugin_pkgs', 'file')
            opts = plugin_pkgs([outdir '/' funcname '.' suf]);
        else
            opts = '';
        end
    end

    function writeMexScript(outMfile, rtCfiles, opts)
        % Nested function for writing out mex script
        if ~isequal( outdir, '.')
            outMfile = [outdir '/' outMfile];
        end
        clear(outMfile);
        
        % Nested function for writing out mex script
        fid = fopen( outMfile, 'w');
        if (fid<0); error('lib2mex:OpenOutputFile', msg); end
        
        if hasmpi( [outdir '/' funcname '.' suf])
            mpiopts = '    [mpicflag, mpildflag] = mpiflags;';
            mpicflag = ' '' '' mpicflag ';
            mpildflag = ' '' '' mpildflag ';
        else
            mpiopts = '';
            mpicflag = ''; mpildflag = '';
        end
        
        enableomp = match_option( args, '-acc');
        if enableomp
            ompopts = '    [ompcflag, ompldflag] = ompflags;';
            ompcflag = ' '' '' ompcflag';
            ompldflag = ' '' '' ompldflag ';
        else
            ompopts = '';
            ompcflag = ''; ompldflag = '';
        end
        
        if haslapack( [outdir '/' funcname '.' suf])
            lapackldopts = ''' -lmwlapack -lmwblas ''';
        else
            lapackldopts = '';
        end
        
        % Place mex file in the same directory as the M file.
        mexdir = '../../../';
        
        % Place mex file in the same directory as the M file.
        fprintf( fid, '%s\n', ...
            ['% Build script for ' funcname], ...
            ['if ~isnewer( [''' mexdir funcname '.'' mexext], ''' funcname '_mex.' suf ''', ''' funcname '.' suf ''')'], ...
            '    dir = which(''opaque_obj.m''); dir=dir(1:end-12);', ...
            mpiopts, ompopts, ...
            '    if exist(''octave_config_info'', ''builtin''); output = ''-o''; else output = ''-largeArrayDims -output''; end', ...
            ['    cmd = [''mex ' ldflags ' COPTIMFLAGS=''''' opflags '''''''' mpicflag ompcflag ' '' -I"'' dir ''include" -I. '' '...
            ' ''' funcname '_mex.' suf rtCfiles ' '' output '' ' mexdir funcname ' '' '  opts mpildflag ompldflag lapackldopts '];'], ...
            '    fprintf(''Entering %s\n'', pwd);', ...
            '    disp(cmd);', ...
            '    eval(cmd);', ...
            'else', ['    fprintf( ''' funcname '.%s is up to date.\n'', mexext);'], 'end');
        
        
        fclose(fid);
    end

    function writeExeScript(outMfile, opts)        
        if ~isequal( outdir, '.')
            outMfile = [outdir '/' outMfile];
        end
        clear(outMfile);
        
        
        % Nested function for writing out mex script
        fid = fopen( outMfile, 'w');
        if (fid<0); error('lib2mex:OpenOutputFile', msg); end
        
        if hasmpi( [outdir '/' funcname '.' suf])
            mpiopts = '    [mpicflag, mpildflag] = mpiflags;';
            mpicflag = ' '' '' mpicflag ';
            mpildflag = ' '' '' mpildflag ';
        else
            mpiopts = '';
            mpicflag = ''; mpildflag = '';
        end
        
        enableomp = match_option( args, '-acc');
        if enableomp
            ompopts = '    [ompcflag, ompldflag] = ompflags;';
            ompcflag = ' '' '' ompcflag';
            ompldflag = ' '' '' ompldflag ';
        else
            ompopts = '';
            ompcflag = ''; ompldflag = '';
        end
        
        if haslapack( [outdir '/' funcname '.' suf])
            lapackldopts = ''' -lmwlapack -lmwblas ''';
        else
            lapackldopts = '';
        end
        
        % Place exe file in the same directory as the M file.
        exedir = './';
                
        % Place exe file in the same directory as the M file.
        fprintf( fid, '%s\n', ...
            ['% Build script for ' funcname], ...
            ['if ~isnewer( [''' exedir funcname '.exe''], ''' funcname '_exe.' suf ''', ''' funcname '.' suf ''')'], ...
            '    m2cdir = which(''opaque_obj.m''); m2cdir=m2cdir(1:end-12);', ...
            mpiopts, ompopts, ...
            '    incdir = [matlabroot ''/extern/include''];', ...
            '    bindir = [matlabroot ''/bin/'' lower(computer)];', ...
            '    libs = [''-L'' bindir '' -Xlinker -rpath -Xlinker '' bindir '' -lmat -lmx''];', ...
            ['    cmd = [''cc ' ldflags '' '' opflags mpicflag ompcflag ' -I"'' incdir ''" -I"'' m2cdir ''include" -I. '' '...
            ' ''' funcname '_exe.' suf ' -o ' exedir funcname '.exe '' '  opts mpildflag ompldflag lapackldopts 'libs];'], ...
            '    fprintf(''Entering %s\n'', pwd);', ...
            '    disp(cmd);', ...
            '    unix(cmd);', ...
            'else', ['    fprintf( ''' funcname '.exe is up to date.\n'');'], 'end');
        
        fclose(fid);
    end
end

function str = print_apiFunction(funcname, altname, nlhs, nrhs, vars, ret, SDindex, errMsgFunc)
% Print into a string an API function for the function with the given
% numbers of input and output arguments.

if ~isempty(ret)
    retval = [ret.name ' = '];
else
    retval = '';
end

vars_ret = [vars; ret];
if isempty(SDindex)
    SDname = '';
else
    SDname = ['&' vars(SDindex).name];
end

str = sprintf( '%s\n', ...
    ['void ' altname '_api(const mxArray ** prhs, const mxArray **plhs) {'], ...
    var_declr(vars, ret), ...
    marshallin( altname, vars_ret, nlhs, nrhs, SDindex, errMsgFunc), ...
    '', '    /* Invoke the target function */', ...
    ['    ' funcname '_initialize(' SDname ');'], ...
    ['    ' retval altname '(' listargs( vars) ');'], ...
    ['    ' funcname '_terminate();'], '', ...
    marshallout(vars_ret, nlhs), '', var_free(vars_ret), '}');

% Remove two consecutive empty lines
while ~isempty( regexp( str, '\n\n\n', 'once'))
    str = regexprep( str, '(\n\n)\n', '$1');
end

end

function str = print_mexFunction(altapis, alt_nlhs, alt_nrhs)
% Print into a string a mexFunction for the function with the given
% numbers of input and output arguments.

str = 'void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {';

if max(alt_nlhs)>1
    str = sprintf( '\n%s', ...
        str, '    /* Temporary copy for mex outputs. */', ...
        ['    mxArray *outputs[' int2str(max(alt_nlhs)) '];'], ...
        '    int i;', ...
        '    int nOutputs = (nlhs < 1 ? 1 : nlhs);', '');
end

haselse = '';
for i=1:length(altapis)
    funcname = altapis{i}; nlhs = alt_nlhs(i); nrhs = alt_nrhs(i);
    str = sprintf( '\n%s', str, ...
        ['    ' haselse 'if (nrhs == ' int2str(nrhs) ') {'], ...
        ['        if (nlhs > ' int2str(nlhs) ')'], ...
        ['            mexErrMsgIdAndTxt("' funcname ':TooManyOutputArguments",' ...
        '"Too many output arguments for entry-point ' funcname '.");']);
    if max(alt_nlhs)<=1
        str = sprintf( '\n%s', str, ...
            '        /* Call the API function. */', ...
            ['        ' funcname '_api(prhs, (const mxArray**)plhs);'], '    }');
    else
        str = sprintf( '\n%s', str, ...
            '        /* Call the API function. */', ...
            ['        ' funcname '_api(prhs, (const mxArray**)outputs);'], '    }');
    end
    
    haselse = 'else ';
end

str = sprintf( '\n%s', ...
    str, '    else', ...
    ['        mexErrMsgIdAndTxt("' altapis{1} ':WrongNumberOfInputs","' ...
    'Incorrect number of input variables for entry-point ' altapis{1} '.");']);

if max(alt_nlhs)>1
    str = sprintf( '\n%s', ...
        str, '', '    /* Copy over outputs to the caller. */', ...
        '    for (i = 0; i < nOutputs; ++i) {', ...
        '        plhs[i] = outputs[i];', ...
        '    }');
end

str = sprintf( '\n%s', str, '}');

% Remove two consecutive empty lines
while ~isempty( regexp( str, '^\n\n', 'once'))
    str = regexprep( str, '^(\n)\n', '$1');
end
while ~isempty( regexp( str, '\n\n\n', 'once'))
    str = regexprep( str, '(\n\n)\n', '$1');
end

end

function str = print_exeFunction(altapis, alt_nlhs, alt_nrhs)
% Print into a string a mexFunction for the function with the given
% numbers of input and output arguments.

maxin = max(alt_nrhs);  nIn = max(maxin,1);
maxout = max(alt_nlhs); nOut = max(maxout,1);

str = sprintf('%s\n', ...
    'int main(int argc, const char * const argv[]) {', ...
    '    int nlhs, nrhs, nOutputs;', ...
    ['    mxArray *prhs[' int2str(nIn) '] = {' nullptrs(nIn) '};'], ...
    ['    mxArray *plhs[' int2str(nOut) '] = {' nullptrs(nOut) '};'], '', ...
    '    if (argc<5) {', ...
    '        fprintf(stderr, "Too few input arguments. Usage:\n\t %s <nrhs> <infile> <nlhs> <outfile>\n", argv[0]);', ...
    '        return(EXIT_FAILURE);', ...
    '    }', '', ...
    '    nrhs = atoi(argv[1]);', ...
    '    if (nrhs && readInputArgs(argv[2], nrhs, prhs)) {', ...
    '       return(EXIT_FAILURE);', ...
    '    }', '', ...
    '    nlhs = atoi(argv[3]); nOutputs = (nlhs < 1 ? 1 : nlhs);', '' ...
    );


haselse = '';
for i=1:length(altapis)
    funcname = altapis{i}; nlhs = alt_nlhs(i); nrhs = alt_nrhs(i);
    str = sprintf( '\n%s', str, ...
        ['    ' haselse 'if (nrhs == ' int2str(nrhs) ') {'], ...
        ['        if (nlhs > ' int2str(nlhs) ') {'], ...
        ['            fprintf(stderr, "Too many output arguments for entry-point ' funcname '.\n");'], ...
        '            return(EXIT_FAILURE);', ...
        '        }', '', ...
        '        /* Call the API function. */', ...
        ['        ' funcname '_api((const mxArray**)prhs, (const mxArray**)plhs);'], '    }');
    
    haselse = 'else ';
end

str = sprintf( '\n%s', str, ...
    '    else {', ...
    ['        fprintf(stderr, "Incorrect number of input variables for entry-point ' altapis{1} '.\n");'], ...
    '        return(EXIT_FAILURE);', ...
    '    }', '');

for i=1:nIn
    str = sprintf( '\n%s', str, ...
        ['    if (prhs[' int2str(i-1) ']) mxDestroyArray(prhs[' int2str(i-1) ']);']);
end

str = sprintf( '\n%s', str, '', ...
    '    if (writeOuputArgs(argv[4], nOutputs, plhs)) {', ...
    '        return(EXIT_FAILURE);', ...
    '    }', '');

for i=1:nOut
    str = sprintf( '\n%s', str, ...
        ['    if (plhs[' int2str(i-1) ']) mxDestroyArray(plhs[' int2str(i-1) ']);']);
end

str = sprintf( '\n%s', str, '}');

% Remove two consecutive empty lines
while ~isempty( regexp( str, '^\n\n', 'once'))
    str = regexprep( str, '^(\n)\n', '$1');
end
while ~isempty( regexp( str, '\n\n\n', 'once'))
    str = regexprep( str, '(\n\n)\n', '$1');
end

end

function print_README(outdir, funcname)
% Print out README file.

outfile = [outdir '/README'];
fid = fopen(outfile, 'w');
if (fid<0); error('lib2mex:OpenOutputFile', msg); end

fprintf(fid, '%s\n', ...
    ['This directory contains the C codes for ' funcname ' generated by m2c.'], '', ...
    'There are three sets of files:', ...
    'Core Library Files (for building a portable library for C):', ...
    ['    ' funcname '_types.h: Declaration of data types'], ...
    ['    ' funcname '.h: Declaration of functions'], ...
    ['    ' funcname '.c: Implementation of functions'], ...
    '    Dependent files m2c.h, m2c.c and rtwtypes.h are in <m2croot>/include.', '', ...
    'MEX Function Files (for building a MATLAB/Octave executable):', ...
    ['    ' funcname '_mex.c: Definition of MexFunction.'], ...
    ['    mex_' funcname '.m: MATLAB script for compiling MEX function'], ...
    '    Additional dependent file lib2mex_helper.c is in <m2croot>/include.', '', ...
    'Main Function (for building a standalone executable for debugging/profiling):', ...
    ['    ' funcname '_exe.c: Definition of main function that read/write MAT files.'], ...
    ['    ld_' funcname '.m: MATLAB script for compiling executible.'], ...
    '    Additional dependent file lib2exe_helper.c is in <m2croot>/include.' ...
    );

fclose(fid);

end

function str = var_declr( vars, ret)
% Produce variable declarations
decl_emx = '';
decl_basic = '';
decl_struct = '';
sub_mx_level = 0;
has_struct_arr = false;

for i=1:length(vars)
    if vars(i).isemx
        % declare a varialbe of type emxArray
        if ~isempty(vars(i).subfields)
            has_struct_arr=true;
            
            a = check_struct_levels(vars(i).subfields);
            sub_mx_level = max(sub_mx_level, a);
        end
        decl_emx = sprintf( '%s\n    %-20s %s;', decl_emx, ...
            vars(i).type, vars(i).name);
    elseif ~isempty(vars(i).subfields)
        if prod(vars(i).size)>1
            has_struct_arr=true;
        end
        
        % declare a variable of a struct type
        if prod(vars(i).size)==1
            decl_struct = sprintf( '%s\n    %-20s %s;', decl_struct, ...
                vars(i).type, vars(i).name);
        else
            decl_struct = sprintf( '%s\n    %-20s %s[%d];', decl_struct, ...
                vars(i).type, vars(i).name, prod(vars(i).size));
        end
        [a,b] = check_struct_levels(vars(i).subfields);
        
        sub_mx_level = max(sub_mx_level, a);
        has_struct_arr = has_struct_arr || b;
    else
        % declare a varialbe of primitive type
        decl_basic = sprintf( '%s\n    %-20s %s%s;', decl_basic, ...
            vars(i).type, vars(i).modifier, vars(i).name);
    end
end

if ~isempty(ret)
    decl_basic = sprintf( '%s\n    %-20s %s%s;', decl_basic, ...
        ret.type, ret.modifier, ret.name);
end

if sub_mx_level
    % declare a variable of a struct type
    if sub_mx_level>1; vstr = sprintf(', *_sub_mx%d', 2:sub_mx_level);
    else vstr = ''; end
    decl_struct = sprintf( '%s\n    %-20s %s%s;', decl_struct, 'mxArray', '*_sub_mx1', vstr);
end

if has_struct_arr
    % declare variables for index
    decl_struct = sprintf( '%s\n    %-20s _sub_k;', decl_struct, 'int32_T');
end

str = sprintf('%s\n%s\n%s\n', decl_emx, decl_struct, decl_basic);
end

function [level,has_struct_arr] = check_struct_levels(vars, level)
% Check number of levels of a struct and whether it contains struct arrays
if nargin<2; level = 1; end

has_struct_arr = false;
for i=1:length(vars)
    if ~isempty(vars(i).subfields)
        [level,b] = check_struct_levels(vars(i).subfields, level+1);
        
        has_struct_arr = has_struct_arr || b || prod(vars(i).size)~=1;
    end
end
end

function str = marshallin( funcname, vars, nlhs, nrhs, SDindex, errMsgFunc)
% Marshall function input arguments and preallocate output arguments.

invarsindex = zeros(nrhs, 1);
outvarsindex = zeros(nlhs, 1);

for i=1:length(vars)
    if ~isempty(vars(i).iindex)
        invarsindex( vars(i).iindex) = i;
    end
    if ~isempty(vars(i).oindex)
        outvarsindex( vars(i).oindex) = i;
    end
end

str = '';
first = true;
for j=1:nrhs
    i = invarsindex(j); assert(i>0);
    var = vars(i);
    
    if first
        str = '    /* Marshall in function inputs */';
        first = false;
    end
    
    if ~isempty(var.oindex)
        str = sprintf( '%s\n    plhs[%d] = mxDuplicateArray( prhs[%d]);', ...
            str, var.oindex-1, var.iindex-1);
        mx = ['plhs[' int2str(var.oindex-1) ']'];
    else
        mx = ['prhs[' int2str(var.iindex-1) ']'];
    end
    if ~isempty( var.subfields)
        str = marshallin_struct( str, mx, var, funcname, errMsgFunc);
    else
        str = sprintf( ['%s\n    if ( mxGetNumberOfElements(%s) && mxGetClassID(%s) != %s)\n', ...
            '        ' errMsgFunc '("%s:WrongInputType",\n',...
            '            "Input argument %s has incorrect data type. %s is expected.");'], ...
            str, mx, mx, getMxClassID( var.basetype), ...
            funcname, var.name, getMatlabClass(var.basetype));
        
        if var.isemx
            str = sprintf( '%s\n    alias_mxArray_to_emxArray(%s, (emxArray__common *)&%s, "%s", %d);', ...
                str, mx, var.name, var.name, length(var.size));
        elseif prod(var.size)~=1
            assert( ~isequal(var.type, 'char') && ~isequal(var.type, 'char_T'));
            
            str = sprintf( ['%s\n    if ( mxGetNumberOfElements(%s) != %d)\n', ...
                '        ' errMsgFunc '("%s:WrongSizeOfInputArg",\n',...
                '            "Argument %s must contain %d numbers.");'], ...
                str, mx, prod(var.size), funcname, var.name, prod(var.size));
            str = sprintf( '%s\n    %s = (%s*)mxGetData(%s);', ...
                str, var.name, var.type, mx);
        else
            str = sprintf( ['%s\n    if ( mxGetNumberOfElements(%s) != 1)\n', ...
                '        ' errMsgFunc '("%s:WrongSizeOfInputArg",\n',...
                '            "Argument %s should be a scalar.");'], ...
                str, mx, funcname, var.name);
            if isempty(var.modifier)
                if isequal( var.type, 'char_T') || isequal( var.type, 'char')
                    str = sprintf( '%s\n    %s = *(mxChar*)mxGetData(%s);', ...
                        str, var.name, mx);
                else
                    str = sprintf( '%s\n    %s = *(%s*)mxGetData(%s);', ...
                        str, var.name, var.type, mx);
                end
            else
                str = sprintf( '%s\n    %s = (%s*)mxGetData(%s);', ...
                    str, var.name, var.type, mx);
            end
        end
    end
end

first = true;
% Preallocate output arguemnts that are arrays of fixed size
for j=1:nlhs
    var = vars(outvarsindex(j));
    if ~isempty(var.iindex); continue; end
    if first
        str = sprintf('%s\n\n%s', str, '    /* Preallocate output variables */');
        first = false;
    end
    
    if var.isemx
        str = sprintf( '%s\n    init_emxArray((emxArray__common*)&%s, %d);', ...
            str, var.name, length(var.size));
    elseif ~isempty( var.subfields)
        str = preallocate_struct( str, var.name, var);
    elseif ~isempty(var.modifier) && prod(var.size)>0
        str = sprintf( ['%s\n    {mwSize l_size[] = {', ...
            regexprep( strtrim(sprintf( '%d ', var.size)), ' ', ', '), '};\n', ...
            '    *(void **)&%s = prealloc_mxArray((mxArray**)&plhs[%d], %s, %d, l_size); }'], ...
            str, var.name, var.oindex-1, getMxClassID(var.basetype), length(var.size));
    end
end

% Preallocate StackData object
if ~isempty( SDindex)
    var = vars(SDindex);
    sf = vars(SDindex).subfields;
    str = sprintf('%s\n\n%s\n    %s.%s = (%s *)mxMalloc(sizeof(%s));', str, ...
        '    /* Allocate Stack Data */', var.name,sf.name, sf.type, sf.type);
end

end

function str = preallocate_struct( str, prefix, var, level)
% Pre-allocate output struct

if nargin<4; level=1; end
assert(~var.isemx);

substr = '';
indent = repmat('    ',1,level-1);
if prod(var.size)>1
    indent = repmat('    ',1,level);
end

for k=1:length(var.subfields)
    sf = var.subfields(k);
    if sf.isemx
        substr = sprintf( ['%s\n%s    *(void **)&%s.%s = mxCalloc(1, sizeof(emxArray__common));', ...
            '%s    init_emxArray( (emxArray__common*)%s.%s, %d);'], ...
            substr, indent, prefix, sf.name, indent, prefix, sf.name, length(sf.size));
    elseif ~isempty( sf.subfields)
        substr = preallocate_struct( substr, [prefix '.' sf.name], sf, level+1);
    end
end

if prod(var.size)>1 && ~isempty(substr)
    substr = sprintf('%s\n%s%s\n%s}', '', indent, ...
        'for (_sub_k=0; _sub_k<%d; ++_sub_k) {', substr, indent);
end

str = sprintf('%s%s', str, substr);
end

function str = marshallin_struct( str, mx, var, funcname, level, prefix, errMsgFunc)
if nargin<5; level=1; end
if nargin<6; prefix=''; end

indent = repmat('    ',1,level-1);

str = sprintf('%s\n', str);

% Check struct type and fields
str = sprintf( ['%s\n%s    if ( !mxIsStruct(%s))\n', ...
    '%s        ' errMsgFunc '("%s:WrongInputType",\n',...
    '%s            "Input argument %s has incorrect data type. struct is expected.");'], ...
    str, indent, mx, indent, funcname, indent, [prefix var.name]);
str = sprintf(['%s\n%s    if ( mxGetNumberOfFields( %s)!=%d)\n', ...
    '%s        ' errMsgFunc '("%s:InputStructWrongFields",\n',...
    '%s            "Input argument %s has incorrect number of fields.");'], ...
    str, indent, mx, length(var.subfields), indent, funcname, indent, [prefix var.name]);
if prod(var.size)>=1
    str = sprintf( ['%s\n%s    if ( mxGetNumberOfElements(%s) != %d)\n', ...
        '%s        ' errMsgFunc '("%s:WrongSizeOfInputArg",\n',...
        '%s            "Argument %s must contain %d items.");'], ...
        str, indent, mx, prod(var.size), indent, funcname, indent, var.name, prod(var.size));
end

if var.isemx
    str = sprintf('%s\n%s    init_emxArray_from_mxArray( %s, (emxArray__common*)&%s, "%s", %d, sizeof(%s));', ...
        str, indent, mx, [prefix var.name], [prefix var.name], length(var.size), var.structname);
    indent = repmat('    ',1,level);
    index = '_sub_k'; p = [[prefix var.name] '.data[_sub_k]' ];
elseif prod(var.size)>1
    indent = repmat('    ',1,level);
    index = '_sub_k'; p = [[prefix var.name] '[_sub_k]' ];
else
    index = '0'; p = [prefix var.name];
end

submx = ['_sub_mx' int2str(level)];
substr = '';
for k=1:length(var.subfields)
    sf = var.subfields(k);
    
    % Check fields
    substr = sprintf('%s\n%s    %s = mxGetField( %s, %s, "%s");', ...
        substr, indent, submx, mx, index, sf.name);
    substr = sprintf(['%s\n%s    if ( %s==NULL)\n', ...
        '%s        ' errMsgFunc '("%s:WrongInputStruct",\n',...
        '%s            "Input argument %s does not have the field %s.");'], ...
        substr, indent, submx, indent, funcname, indent, [prefix var.name], sf.name);
    
    substr = sprintf( ['%s\n%s    if ( mxGetNumberOfElements(%s) && mxGetClassID(%s) != %s)\n', ...
        '%s        ' errMsgFunc '("%s:WrongInputType",\n',...
        '%s            "Input argument %s.%s has incorrect data type. %s is expected.");'], ...
        substr, indent, submx, submx, getMxClassID( sf.basetype), indent, funcname, ...
        indent, [prefix var.name], sf.name, getMatlabClass(sf.basetype));
    
    if sf.isemx
        substr = sprintf( '%s\n%s    *(void**)&%s.%s = mxCalloc(1, sizeof(emxArray__common));', ...
            substr, indent, p, var.subfields(k).name);
        substr = sprintf( '%s\n%s    alias_mxArray_to_emxArray(%s, (emxArray__common*)%s.%s, "%s.%s", %d);', ...
            substr, indent, submx, p, sf.name, [prefix var.name], sf.name, length(sf.size));
    elseif ~isempty( var.subfields(k).subfields)
        substr = marshallin_struct( substr, submx, var.subfields(k), ...
            funcname, level+1, [prefix var.name '.'], errMsgFunc);
    elseif prod(sf.size)>1
        assert( ~isequal(sf.type, 'char') && ~isequal(sf.type, 'char_T'));
        substr = sprintf( ['%s\n%s    if ( mxGetNumberOfElements(%s) != %d)\n', ...
            '%s        ' errMsgFunc '("%s:WrongSizeOfInputArg",\n',...
            '%s            "Argument %s.%s must contain %d numbers.");'], ...
            substr, indent, submx, prod(sf.size), indent, ...
            funcname, indent, [prefix var.name], sf.name, prod(sf.size));
        substr = sprintf( '%s\n%s    copy_mxArray_to_array( %s, %s.%s, %d);', ...
            substr, indent, submx, p, sf.name, prod(sf.size));
    else
        substr = sprintf( ['%s\n%s    if ( mxGetNumberOfElements(%s) != 1)\n', ...
            '%s        ' errMsgFunc '("%s:WrongSizeOfInputArg",\n',...
            '%s            "Argument %s.%s should be a scalar.");'], ...
            substr, indent, submx, indent, funcname, indent, [prefix var.name], sf.name);
        substr = sprintf( '%s\n%s    %s.%s = *(%s*)mxGetData(%s);', ...
            substr, indent, p, sf.name, sf.type, submx);
    end
end

%
if ~isempty(substr)
    if var.isemx
        indent = repmat('    ',1,level);
        str = sprintf('%s\n%sfor (_sub_k=mxGetNumberOfElements(%s)-1; _sub_k>=0; --_sub_k) {%s\n%s}', ...
            str, indent, mx, substr, indent);
    elseif prod(var.size)>1
        indent = repmat('    ',1,level);
        str = sprintf('%s\n%sfor (_sub_k=0; _sub_k<%d; ++_sub_k) {%s\n%s}', ...
            str, indent, prod(var.size), substr, indent);
    else
        str = sprintf( '%s\n%s', str, substr);
    end
end
end

function str = listargs( vars)
% List the arguments for calling the function

str = '';
for i=1:length(vars)
    if vars(i).isemx
        str = sprintf( '%s, &%s', str, vars(i).name);
    elseif ~isempty(vars(i).subfields)
        if ~isempty(vars(i).modifier) && prod(vars(i).size)==1
            modifier='&';
        else
            modifier='';
        end
        str = sprintf( '%s, %s%s', str, modifier, vars(i).name);
    else
        str = sprintf( '%s, %s', str, vars(i).name);
    end
end

str = str(3:end);
end

function str = marshallout(vars, nlhs)
% Marshall function output arguments

if nlhs==0;
    str='';
    return;
else
    str = '    /* Marshall out function outputs */';
end

outvarsindex = zeros(nlhs, 1);
for i=1:length(vars)
    if ~isempty(vars(i).oindex)
        outvarsindex( vars(i).oindex) = i;
    end
end

for j=1:nlhs
    var = vars(outvarsindex(j));
    
    if ~isempty(var.subfields)
        str = marshallout_struct(str, sprintf('plhs[%d]', j-1), var);
    elseif ~isempty(var.iindex) && var.isemx
        str = sprintf( '%s\n    if (%s.canFreeData) plhs[%d] = move_emxArray_to_mxArray((emxArray__common*)&%s, %s);', ...
            str, var.name, j-1, var.name, getMxClassID( var.basetype));
    elseif var.isemx
        str = sprintf( '%s\n    plhs[%d] = move_emxArray_to_mxArray((emxArray__common*)&%s, %s);', ...
            str, j-1, var.name, getMxClassID( var.basetype));
    elseif isempty(var.modifier)
        str = sprintf( '%s\n    plhs[%d] = copy_scalar_to_mxArray(&%s, %s);', ...
            str, j-1, var.name, getMxClassID( var.basetype));
    else
        str = sprintf( '%s\n    /* Nothing to do for plhs[%d] */', str, j-1);
    end
end
end

function str = marshallout_struct(str, mx, var, level, prefix)

if nargin<4; level=1; end
if nargin<5; prefix=''; end

indent = repmat('    ',1,level-1);

str = sprintf( '%s\n%s    {const char *_fields[] = { %s ""};', ...
    str, indent, sprintf( '"%s", ', var.subfields.name));

if var.isemx
    str = sprintf( '%s\n%s    %s = create_struct_mxArray( %s.numDimensions, %s.size, %d, _fields);}', ...
        str, indent, mx, [prefix var.name], [prefix var.name], length(var.subfields));
    indent = repmat('    ',1,level); index='_sub_k'; sub='.data[_sub_k]';
elseif prod(var.size)>1
    sz_str = sprintf(', %d', var.size); sz_str = sz_str(3:end);
    
    str = sprintf( ['%s\n%s    int32_T _size[] = {%s};' ...
        '\n%s    %s = create_struct_mxArray( %d, _size, %d, _fields);}'], ...
        str, indent, sz_str, indent, mx, length(var.size), length(var.subfields));
    indent = repmat('    ',1,level); index='_sub_k'; sub='[_sub_k]';
else
    str = sprintf( '%s\n%s    int32_T _one=1;\n%s    %s = create_struct_mxArray( 1, &_one, %d, _fields);}', ...
        str, indent, indent, mx, length(var.subfields));
    index='0';  sub='';
end

substr = '';
for k=1:length(var.subfields)
    sf = var.subfields(k).name;
    if ~isempty( var.subfields(k).subfields)
        substr = marshallout_struct(substr, ['_sub_mx' int2str(level)], var.subfields(k), level+1, [prefix var.name sub '.']);
        substr = sprintf( '%s\n%s    mxSetFieldByNumber( (mxArray*)(%s), %s, %d, _sub_mx%d);', ...
            substr, indent, mx, index, k-1, level);
    elseif var.subfields(k).isemx
        substr = sprintf( ['%s\n%s    mxSetFieldByNumber( (mxArray*)(%s), %s, %d, ' ...
            'move_emxArray_to_mxArray((emxArray__common*)%s%s.%s, %s));'], ...
            substr, indent, mx, index, k-1, [prefix var.name], sub, ...
            sf, getMxClassID(var.subfields(k).basetype));
    elseif prod( var.subfields(k).size)==1
        substr = sprintf( ['%s\n%s    mxSetFieldByNumber( (mxArray*)(%s), %s, %d, ' ...
            'copy_scalar_to_mxArray(&%s%s.%s, %s));'], ...
            substr, indent, mx, index, k-1, [prefix var.name], sub, sf, getMxClassID( var.subfields(k).basetype));
    else
        sz = var.subfields(k).size;
        sz_str = sprintf(', %d', var.size); sz_str = sz_str(3:end);
        
        substr = sprintf( ['%s\n%s    {int32_T _size[] = {%s};\n' ...
            '%s    mxSetFieldByNumber( (mxArray*)(%s), %s, %d, ' ...
            'copy_array_to_mxArray(%s%s.%s, %s, %d, _size)); }'], ...
            substr, indent, sz_str, indent, mx, index, k-1, [prefix var.name], sub, sf, ...
            getMxClassID( var.subfields(k).basetype), length(sz));
    end
end

if ~isempty( substr)
    if var.isemx
        str = sprintf('%s\n%sfor (_sub_k=mxGetNumberOfElements(%s)-1; _sub_k>=0; --_sub_k) {%s\n%s}', ...
            str, indent, mx, substr, indent);
    elseif prod(var.size)>1
        str = sprintf('%s\n%sfor (_sub_k=0; _sub_k<%d; ++_sub_k) {%s\n%s}', ...
            str, indent, prod(var.size), substr, indent);
    else
        str = sprintf('%s%s', str, substr);
    end
end
end

function str = var_free(vars)
% Print out free_emxArray for given variable

has_emxArray = false;

fvstr = '';
for i=1:length(vars)
    if ~isempty(vars(i).subfields)
        [fvstr,hasa] = deallocate_struct(fvstr, '', vars(i));
        has_emxArray = has_emxArray || hasa;
    elseif strncmp( vars(i).type, 'emxArray_', 9)
        fvstr = sprintf( '%s\n    free_emxArray( (emxArray__common*)&%s);', ...
            fvstr, vars(i).name);
        has_emxArray = true;
    end
end

if has_emxArray;
    str = sprintf('    /* Free temporary variables */%s', fvstr);
else
    str = '';
end
end

function [str, has_emxArray] = deallocate_struct( str, prefix, var, level)
% Deallocate output struct

if nargin<4; level=1; end
indent = repmat('    ', 1, level-1);

substr = '';

if strncmp( var.type, 'emxArray_', 9)
    has_emxArray = true;
    varname = [prefix var.name '.data[_sub_k].'];
    indent = repmat('    ', 1, level);
else
    has_emxArray = false;
    if prod(var.size)>1
        varname = [prefix var.name '[_sub_k].'];
        indent = repmat('    ', 1, level);
    else
        varname = [prefix var.name '.'];
    end
end

for k=1:length(var.subfields)
    sf = var.subfields(k);
    if sf.isemx
        substr = sprintf( '%s    free_emxArray( (emxArray__common*)%s%s); mxFree( %s%s);\n%s', ...
            indent, varname, sf.name, varname, sf.name, substr);
        has_emxArray = true;
    elseif ~isempty( sf.subfields)
        [substr, has_subemx] = deallocate_struct( substr, varname, sf, level+1);
        has_emxArray = has_emxArray || has_subemx;
    end
end

if isempty(substr); return; end

if strncmp( var.type, 'emxArray_', 9)
    str = sprintf('%s\n%sfor (_sub_k=nelems_emxArray((emxArray__common*)&%s)-1; _sub_k>=0; --_sub_k) {\n%s\n%s}', ...
        str, indent, [prefix var.name], substr, indent);
elseif prod(var.size)>1
    str = sprintf('%s\n%sfor (_sub_k=0; _sub_k<%d; ++_sub_k) {\n%s\n%s}', ...
        str, indent, prod(var.size), substr, indent);
else
    str = sprintf('%s\n%s', str, substr);
end
end

function s = nullptrs(n) 
  s = sprintf('%d, ', zeros(n,1));
  s = s(1:end-2);
end
