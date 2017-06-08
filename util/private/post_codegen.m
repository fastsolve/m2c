function [parmode, changed, has_emxutil] = post_codegen(func, cpath, m2c_opts)
%% Modify files generated by codegen

c_filename = [cpath func '.' m2c_opts.suf];
cfile_str = readFile(c_filename);

emxC_filename = [cpath func '_emxutil.' m2c_opts.suf];
if exist(emxC_filename, 'file')
    emxC_str = readFile(emxC_filename);
    has_emxutil = contains(emxC_str, 'emxCopyStruct_');
    
    emxH_filename = [cpath func '_emxutil.h'];
    if exist(emxH_filename, 'file')
        emxH_str = readFile(emxH_filename);
    else
        emxH_filename = '';
        emxH_str = '';
    end
else
    has_emxutil = false;
end

h_filename = [cpath func '.h'];
hfile_str = readFile(h_filename);

ctype_filename = [cpath func '_types.h'];
ctypes_str = readFile(ctype_filename);

% Check whether the C file includes m2c.h
usem2c = ~isempty(regexp(cfile_str, '\n#include "m2c.h"', 'once'));

if has_emxutil
    emxC_str_orig = emxC_str;
    emxH_str_orig = emxH_str;
end
cfile_str_orig = cfile_str;
hfile_str_orig = hfile_str;
ctypes_str_orig = ctypes_str;

%% Move type declarations from C file to header file
% Remove definition of emxArray__common
cfile_str = regexprep(cfile_str, ['#ifndef\s+struct_emxArray__common\s+'...
    '#define\s+struct_emxArray__common\s+struct\s+emxArray__common\s+{[^}]+};\s+' ...
    '#endif\s+#ifndef\s+typedef_emxArray__common\s+#define\s+typedef_emxArray__common\s+' ...
    'typedef\s+struct\s+emxArray__common\s+' ...
    'emxArray__common;\s+#endif\n'], '');

[cfile_str, type_def] = move_type_decl(cfile_str);

if ~isempty(type_def)
    if m2c_opts.verbose
        % Move type definitions
        fprintf('M2C: API functions involves structures. Moved type definitions into header file %s_types.h\n', func);
    end

    if contains(ctypes_str, '/* End of code generation')
        ctypes_str = strrep(ctypes_str, ...
            sprintf('\n#endif\n\n/* End of code generation'), ...
            [sprintf('%s\n', '', '', ...
            '/* Type Declarations inserted by m2c */', type_def, ...
            '#endif', '') '/* End of code generation']);
    else
        ctypes_str = regexprep(ctypes_str, '(\n#endif\n*$)', [type_def '$1']);
    end
end

if has_emxutil
    [emxC_str, emxH_str] = remove_stdemx_funcs(emxC_str, emxH_str, ctypes_str);
else
    [cfile_str, hfile_str] = remove_stdemx_funcs(cfile_str, hfile_str, ctypes_str);
end

cfile_str = fix_emxInit(cfile_str, ctypes_str);

%% Try to remove emxArrays
if m2c_opts.remEmx
    [cfile_str, hfile_str, ctypes_str] = reemxArrays...
        (cfile_str, hfile_str, ctypes_str, m2c_opts);
end

%% Process pragmas
[cfile_str, hfile_str, parmode] = replace_pragmas(cfile_str, hfile_str, m2c_opts);

if ~has_emxutil
  % Remove file <func>_emxutil.h
  cfile_str = regexprep(cfile_str, ['(^|\n)(#include\s+"' func '_emxutil.h"\n)'], '$1');
end

% Add '#include "m2c.h"' if needed
if ~usem2c && (length(cfile_str) ~= length(cfile_str_orig) || has_emxutil)
    cfile_str = regexprep(cfile_str, ['(^|\n)(#include\s+"' func '.h"\n)'], ...
        '$1$2#include "m2c.h"\n');
    if has_emxutil
        emxC_str = regexprep(emxC_str, ['(^|\n)(#include\s+"' func '.h"\n)'], ...
            '$1$2#include "m2c.h"\n');
    end
end

%% Change API definitinons.
api_decl = '';
for i=1:length(m2c_opts.api)
    [cfile_str, api_decl] = move_api_declaration(m2c_opts.api{i}, ...
        cfile_str, api_decl);

    cfile_str = change_api_definition(m2c_opts.api{i}, cfile_str);
    fprintf('M2C: Moved API function %s into header file\n', m2c_opts.api{i});
end

if ~isempty(api_decl)
    hfile_str = strrep(hfile_str, ...
        sprintf('\n#endif\n\n/* End of code generation'), ...
        [sprintf('%s\n', '', ...
        ['/* API Function Declarations inserted inserted by m2c */', api_decl], '', ...
        '#endif', '') '/* End of code generation']);

    pat = '\s+(emxArray_\w*struct\w*_T)\s+\*';
    public_types = regexp(api_decl, '\s+emxArray_\w*struct\w*_T\s+\*', 'match');
    for i=1:length(public_types)
        public_types{i} = regexprep(public_types{i}, pat, '$1');
    end

    if ~isempty(public_types)
        % Move emxInit_ and emxFree_ of public data types into the header file
        [cfile_str, hfile_str] = move_emx_decl(cfile_str, hfile_str, public_types);
    end
end

%% Replace M2C_GET_FIELD, M2C_SET_FIELD, and M2C_INTDIV
cfile_str = regexprep(cfile_str, '([^\w])M2C_GET_FIELD\s*\((([\w\[\]\.\*]|->)+),\s*(\w+)\)', ...
    '$1$2->$3');
cfile_str = regexprep(cfile_str, '([^\w])M2C_SET_FIELD\s*\((([\w\[\]\.\*]|->)+),\s*(\w+),\s*(([\w\[\]\.\*]|->)+)\)', ...
    '$1$2->$3 = $4');

cfile_str = regexprep(cfile_str, '([^\w])M2C_OFFSET_PTR\s*\((([\w\[\]\.\*\/]|->)+),\s*(([\w\[\]\.\*\/]|->)+)\)', ...
    '$1$2 + $3');
cfile_str = regexprep(cfile_str, '([^\w])M2C_OFFSET_PTR\s*\(([^,\)]+),\s*(([\w\[\]\.\*\/]|->)+)\)', ...
    '$1($2) + $3');
cfile_str = regexprep(cfile_str, '([^\w])M2C_OFFSET_PTR\s*\((([\w\[\]\.\*\/]|->)+),\s*([^,\)]+)\)', ...
    '$1$2 + ($3)');
cfile_str = regexprep(cfile_str, '([^\w])M2C_OFFSET_PTR\s*\(([^,\)]+),\s*([^,\)]+)\)', ...
    '$1($2) + ($3)');

cfile_str = regexprep(cfile_str, '([^\w])M2C_INTDIV\s*\((([\w\[\]\.\*\/]|->)+),\s*(([\w\[\]\.]|->)+)\)', ...
    '$1$2 / $3');
cfile_str = regexprep(cfile_str, '([^\w])M2C_INTDIV\s*\(([^,\)]+),\s*(([\w\[\]\.]|->)+)\)', ...
    '$1($2) / $3');
cfile_str = regexprep(cfile_str, '([^\w])M2C_INTDIV\s*\((([\w\[\]\.\*\/]|->)+),\s*([^,\)]+)\)', ...
    '$1$2 / ($3)');
cfile_str = regexprep(cfile_str, '([^\w])M2C_INTDIV\s*\(([^,\)]+),\s*([^,\)]+)\)', ...
    '$1($2) / ($3)');

% Remove two consecutive empty lines and empty functions
while ~isempty(regexp(cfile_str, '\n\n\n', 'once'))
    cfile_str = regexprep(cfile_str, '(\n\n)\n', '$1');
end
cfile_str = regexprep(cfile_str, '(\{\n)\n+(\})', '$1$2');

changed = false;
% Write C file
if ~isequal(cfile_str, cfile_str_orig)
    writeFile(c_filename, cfile_str);
    if m2c_opts.withNvcc
        % Move file to .cu
        [pathstr, base] = fileparts(c_filename);
        movefile(c_filename, [pathstr, '/', base, '.cu']);
    end
    changed = true;
end

% Remove two consecutive empty lines and empty functions
if has_emxutil
    while ~isempty(regexp(emxC_str, '\n\n\n', 'once'))
        emxC_str = regexprep(emxC_str, '(\n\n)\n', '$1');
    end
    if ~isequal(emxC_str, emxC_str_orig)
        writeFile(emxC_filename, emxC_str);
        changed = true;
    end
    
    if ~isequal(emxH_str, emxH_str_orig)
        writeFile(emxH_filename, emxH_str);
        changed = true;
    end
end

if ~isequal(ctypes_str, ctypes_str_orig)
    writeFile(ctype_filename, ctypes_str);
    changed = true;
end

if ~isequal(hfile_str, hfile_str_orig)
    writeFile(h_filename, hfile_str);
    changed = true;
end

%% Perform some checkings on performance
if m2c_opts.debugInfo && ~m2c_opts.quiet
    % Check copying of constant input arrays
    check_inputArrays(cfile_str);

    % Check allocation of local arrays
    check_localArrays(cfile_str);

    % Check casting of integers
    check_intCasting(cfile_str);

    % TODO Check integer division
end

end

function [cfile_str, hfile_str] = remove_stdemx_funcs(cfile_str, hfile_str, ctypes_str)
%% Remove functions for standard data types
% Remove declaration of emxEnsureCapacity

hfile_str = regexprep(hfile_str, 'extern\s+void\s+emxEnsureCapacity\s*\([^,\)]+,[^,\)]+,[^,\)]+\);\n', '');
cfile_str = regexprep(cfile_str, '(static\s+)?void\s+emxEnsureCapacity\s*\([^,\)]+,[^,\)]+,[^,\)]+\);\n', '');
cfile_str = regexprep(cfile_str, ['(static\s+)?void\s+' ...
    'emxEnsureCapacity\s*\([^,\)]+,[^,\)]+,[^,\)]+\)\s*' re_funcbody ], '');

% Remove declaration of emxInit_basictype and emxFree_basictype for basic types
tokens = regexp(ctypes_str, ['struct\s+emxArray_(' re_basictype ')'], 'tokens');
for i=1:length(tokens)
    hfile_str = regexprep(hfile_str, ['extern\s+void\s+emxInit_' ...
        tokens{i}{1} '\d*\([^,\)]+,[^,\)]+\);\n'], '');
    cfile_str = regexprep(cfile_str, ['(static\s+)?void\s+emxInit_' ...
        tokens{i}{1} '\d*\([^,\)]+,[^,\)]+\);\n'], '');
    cfile_str = regexprep(cfile_str, ['(static\s+)?void\s+emxInit_' ...
        tokens{i}{1} '\d*\([^,\)]+,[^,\)]+\)\s*' re_funcbody], '');

    hfile_str = regexprep(hfile_str, ['extern\s+void\s+emxFree_' ...
        tokens{i}{1} '\([^,\)]+\);\n'], '');
    cfile_str = regexprep(cfile_str, ['(static\s+)?void\s+emxFree_' ...
        tokens{i}{1} '\([^,\)]+\);\n'], '');
    cfile_str = regexprep(cfile_str, ['(static\s+)?void\s+emxFree_' ...
        tokens{i}{1} '\([^,\)]+\)\s*' re_funcbody], '');
end

% Remove declaration of emxCreate_basictype, emxCreateND_basictype,
% and emxCreateWrapperND_basictype, emxDestroyArray_basictype
cfile_str = regexprep(cfile_str, ['emxArray_\w+\s+\*emxCreate_' re_basictype ...
    '\([^,\)]+,[^,\)]+\)\s*' re_funcbody], '');
cfile_str = regexprep(cfile_str, ['emxArray_\w+\s+\*emxCreateND_' re_basictype ...
    '\([^,\)]+,[^,\)]+\)\s*' re_funcbody], '');
cfile_str = regexprep(cfile_str, ['emxArray_\w+\s+\*emxCreateWrapper_' re_basictype ...
    '\([^,\)]+,[^,\)]+,[^,\)]+\)\s*' re_funcbody], '');
cfile_str = regexprep(cfile_str, ['emxArray_\w+\s+\*emxCreateWrapperND_' re_basictype ...
    '\([^,\)]+,[^,\)]+,[^,\)]+\)\s*' re_funcbody], '');
cfile_str = regexprep(cfile_str, ['void\s+emxDestroyArray_' re_basictype ...
    '\([^,\)]+\)\s*' re_funcbody], '');

end

function cfile_str = fix_emxInit(cfile_str, ctypes_str)
% Replace calls to emxInit_<type>\d by emxInit_<type>

tokens = regexp(ctypes_str, ['struct\s+emxArray_(' re_basictype ')'], 'tokens');
for i=1:length(tokens)
    cfile_str = regexprep(cfile_str, ['(\s+emxInit_' tokens{i}{1} ')\d+\('], '$1(');
end

end

function check_inputArrays(str)
% Check input constant arrays

funcs = regexp(str, ['(\w+)(\([^\)]+const emxArray_[^\)]+\))\s*(' re_funcbody ')'], 'tokens');

for i=1:length(funcs)
    % Check whether an argument is copied.
    funname = funcs{i}{1};
    args = funcs{i}{2};
    fun = funcs{i}{3};
    if contains(funname, 'emlrt_'); continue; end

    toks = regexp(args, 'const emxArray_(\w+)\s*\*\s*(\w+)', 'tokens');
    for j=1:length(toks)

        % Check to see whether the array has a copy defined.
        if isempty(strfind(toks{j}{2}, '_')) && ~isempty(regexp(fun, ...
                ['\semxArray_' toks{j}{1} '\s*\*\s*\w+_' toks{j}{2} ';'], 'once'))
            warning('m2c:ConstArrayCopyConst', ['Function "%s" makes a copy of an input array "%s". ' ...
                'For better performance, make this array an output as well, '...
                'and when calling the function, use a same variable '...
                'on the left- and right-hand side for this argument.'], funname, toks{j}{2});
        end
    end
end
end

function check_localArrays(str)
funcs = regexp(str, ['(\w+)(\([^\)]+\))\s*(' re_funcbody ')'], 'tokens');

dir = 'lib';

for i=1:length(funcs)
    % Check whether an argument is copied.
    funname = funcs{i}{1};
    % args = funcs{i}{2};
    fun = funcs{i}{3};

    if contains(funname, 'emlrt_'); continue; end
    toks = regexp(fun, '\s+emxEnsureCapacity\(\(emxArray__common \*\)(r[\d]+),\s*\w+,\s*\(int32_T\)', 'tokens');

    for j=1:length(toks)
        % Check to see whether the variables are used as local indices
        target = regexp(fun, ['\s+(\w+)->data\[\w+\] = [\w->]+->data\[' toks{j}{1} '->data\[\w+\] - 1\]'], 'tokens');
        if ~isempty(target)
            fprintf(2, ['m2c Info: Function "%s" created a local integer buffer for the assignment of array "%s". '...
                'This probably indicates that you are assigning to a submatrix or a subvector of some variable size. ' ...
                'Current version of MATLAB Coder does not generate very efficient code for it. ' ...
                'Please review the generated C code codegen/%s/%s/%s.c and the MATLAB code, and consider replacing the assignment ' ...
                'in the MATLAB code with an explict for loop for better efficiency of the C code.\n'], ...
                funname, target{1}{1}, dir, funname, funname);
        else
            skip=false;
            for k=1:j-1
                if isequal(toks{j}{1},toks{k}{1}); skip=true; end
            end
            if skip
                continue;
            end
            target = regexp(fun, [toks{j}{1} '->data\[\w+\] = ([\w->]+)->data\[\w+\]'], 'tokens');
            if ~isempty(target)
                fprintf(2, 'm2c Info: Function "%s" created a local buffer as a local copy of array "%s".\n', ...
                    funname, target{1}{1});
            else
                fprintf(2, 'm2c Info: Function "%s" created a local buffer "%s".\n', ...
                    funname, toks{j}{1});
            end
        end
    end
end

end

function check_intCasting(str)

funcs = regexp(str, ['(\w+)(\([^\)]+\))\s*(' re_funcbody ')'], 'tokens');

for i=1:length(funcs)
    % Check whether an argument is copied.
    funname = funcs{i}{1};
    fun = funcs{i}{3};

    toks = regexp(fun, '(\w+)\s*=\s*\(int32_T\)floor\(', 'tokens');
    for j=1:length(toks)
        fprintf(2, 'm2c Info: Function "%s" involves casting from a real value to integer variable "%s".\n', ...
            funname, toks{j}{1});
    end
end
end

function [cfile, hfile] = move_api_declaration(func, cfile, hfile)
% Move a particlar API function declaration from C to h

% Find function declaration
pat = ['\n\s*static\s+\w+\s+' func '\s*\(([^)]*)\);'];
decl = regexp(cfile, pat, 'match', 'once');

if isempty(decl)
    fprintf(['Could not find the API function %s in the generated C code.\n Please make sure the ' ...
        'function is not inlined by adding coder.inline(''never'') in the M code.'], func);
else
    % Remove it from C file
    cfile = strrep(cfile, decl, '');

    % replace static by extern
    new_decl = [decl(1), 'extern', decl(8:end)];

    % Add the declaration to the header file
    hfile = [hfile, new_decl];
end

end

function cfile = change_api_definition(func, cfile)
% Change the definition of the function in the C code

% Find function declaration
pat = ['(\n\s*)static\s+(\w+\s+' func '\s*\(([^)]*)\)\s*{)'];
defs = regexp(cfile, pat, 'match', 'once');

if isempty(defs)
    fprintf(['Did not find API function %s in the generated C code.\n Please check ' ...
        'whether the function is used and is marked as coder.inline(''never'').'], func);
else
    new_def = regexprep(defs, pat, '$1$2');

    spaces = repmat(' ', 1, length(defs)-length(new_def));
    % Remove spaces
    new_def = strrep(new_def, [defs(1) spaces], defs(1));

    % Add the declaration to the header file
    cfile = strrep(cfile, defs, new_def);
end
end

function [cfile, type_def] = move_type_decl(cfile)
% Find function declaration
pat = '\n\/\* Type Definitions \*\/\n.+\n\/\* Function Declarations \*\/\n';
comment = regexp(cfile, pat, 'match', 'once');

if ~isempty(comment)
    % Remove it from C file
    cfile = strrep(cfile, comment, ...
        sprintf('\n%s', '/* Function Declarations */', ''));

    type_def = comment(25:end-30);
else
    % Move type declarations from C code to the _types.h header file.
    pat = ['#ifndef\s+\w+\n+\#define\s+\w+\n+(typedef\s+struct\s+{([^}][^\n]+\n)+\}\s+\w+|' ...
        'struct\s+\w+\s+\{([^}][^\n]+\n)+\};\n+#endif\n+' ...
        '#ifndef\s+typedef_\w+\n+#define\s+\w+\n+typedef\s+struct\s+\w+\s+\w+);\n+#endif'];

    types = regexp(cfile, pat, 'match');
    type_def = '';
    for i=1:length(types)
        cfile = strrep(cfile, types{i}, '');
        type_def = sprintf('%s\n', type_def, types{i});
    end
end
end

function [cfile_str, hfile_str] = move_emx_decl(cfile_str, hfile_str, public_types)
% Move emxFree_ and emxInit_ declarations from C code to the _types.h header file.
types = sprintf('%s|', public_types{:});

% Find declaration of emxInit_struct_T and and emxFree_struct_T
pat = ['\n\s*static\s+void\s+(emx(Init|Free)_struct_\w+)\s*\((' types(1:end-1) ')([^)]*)\);'];
emx_API = regexp(cfile_str, pat, 'match');

emx_decl = '';
for i=1:length(emx_API)
    func = regexprep(emx_API{i}, pat, '$1');
    [cfile_str, emx_decl] = move_api_declaration(func, cfile_str, emx_decl);

    cfile_str = change_api_definition(func, cfile_str);
    fprintf('M2C: Moved helper function %s into header file\n', func);
end

hfile_str = strrep(hfile_str, ...
    sprintf('\n#endif\n\n/* End of code generation'), ...
    [sprintf('%s\n', '', ...
    ['/* emx Function Declarations inserted inserted by m2c */', emx_decl], '', ...
    '#endif', '') '/* End of code generation']);
end
