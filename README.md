# tng

> **Status:** `tng` is currently under active development (WIP).  
> We are actively shaping the core architecture, and contributions of any size are highly welcome and appreciated.  
> If you would like to help improve `tng`, please check out the [Contributing](#contributing) section below.

# Work in progress

`tng` is currently under heavy development.  
The public API, configuration format, and internal architecture may change between versions.

---

## About tng

`tng` stands for `touch 'N generate`.

It is a command-line tool designed to create "ready-to-use" programming files by:

- creating files if they do not exist, and
- filling them with configurable boilerplate text (headers, license, metadata, etc.)  
  based on file name and file extension.

The goal is to make it easy to:

- standardize file headers and licenses,
- keep comments and structure consistent across a project,
- avoid manually copying boilerplate into each new source file.

---

## What does tng do exactly?

`tng` operates on a set of target files and a configuration file.

At a high level, for each target file:

1. If the file does not exist, `tng` creates it (similar to `touch`).
2. `tng` reads a configuration file (e.g. `tng.conf`) that defines:
   - how to comment generated text,
   - where to find the license,
   - what header/footer text to insert,
   - how to behave per file extension.
3. Based on the file extension (e.g. `cpp`, `h`, `c`, `txt`, etc.), `tng` selects a matching configuration section.
4. It then generates a buffer (header, license, metadata, footer) and writes it into the file according to the rules in the configuration.

If no matching section for a specific extension is found, `tng` falls back to a `[GLOBAL]` section (if defined).

---

## Example usage

```sh
tng file1.txt file2.txt -c /PATH/TO/CONFIG_FILE/tng.conf
```

### Execution flow for this example

1. `tng` checks `file1.txt` and `file2.txt`:
   - if a file does not exist, it will be created.
2. `tng` reads the configuration file:
   ```sh
   -c /PATH/TO/CONFIG_FILE/tng.conf
   ```
3. If the configuration defines behavior for `.txt` files, `tng` uses that section to:
   - determine comment style,
   - determine how to insert license text,
   - decide which header/footer text to use.

For instance, if in the config we have:

```ini
[txt]
comment = YES
line_prefix = "//"
license_path = "/home/username/license-file/"
```

and a license file like:

```txt
HERE IS LICENSE FILE
```

then the resulting `file1.txt` / `file2.txt` could look like:

```txt
// HERE IS LICENSE FILE CONTENT
```

(The exact content depends on the `header_text`, `footer_text`, comment style, and other options defined in the configuration.)

---

## Configuration

`tng` uses a configuration file (for example `tng.conf`) to define behavior per extension and a global fallback.

Below is a simplified version of the example you provided, with explanations.

### Configuration syntax rules

- For boolean variables you can use `<YES>` or `<NO>` as aliases for `<true>` or `<false>` (btw: also you can now use `yes` or `no`).
- Paths must be absolute. Relative (non-absolute) paths are not allowed.
- Use triple quotes `"""` for multi-line string values.
- Sections are declared using `[section_name]`.  
  For example:
  - `[cpp, c, cc, hpp, h]` defines a section that applies to multiple extensions.
  - `[GLOBAL]` defines fallback behavior for files whose extension does not match any other section.

---

### Example: per-extension section for C/C++-like files

```ini
[cpp, c, cc, hpp, h]

####################################
############## Policy ##############
####################################

# Use comments for all tng-generated text.
comment = YES

# Comment style: "block" or "line"
comment_style = block

# Line comment prefix (for line or mixed styles)
line_prefix = "//"

# Multi-line / block comment syntax
block_header      = "/*"
block_line_prefix = " * "
block_footer      = " */"

# License path (absolute path only)
license_path = "/home/exampleUserName/license-file/"
# TODO: use PWD here
# -> license_path = "PWD/license/"

# If tng has already written the generated buffer once, do not write it again
# when this is set to YES.
do_not_duplicate_buffer = NO

####################################
############## Layout ##############
####################################

header_text = """
GNU Based project by : Ilia Abolghasemy (aka: gfaerny, Iliya Abolghasemi)
tng is under GNU license
"""

file_introduce   = "File:"
time_introduce   = "Time:"
license_introduce = "License : MIT"

footer_text = """
Copyright by Ilia Abolghasemy
"""
# TODO: Implement a modification analyzer:
#  - detect last config update time
#  - compare with file modification time
#  - decide whether the generated buffer should be rewritten or not.
```

---

### Global fallback section

```ini
[GLOBAL]
# This section is used when no per-extension section matches.
# You can define default comment style, header/footer, and license handling here.
```

**Behavior note:**  
When `tng` processes a file:

1. It tries to find a section matching that file’s extension (for example `[cpp, c, cc, hpp, h]`).
2. If none match, it falls back to `[GLOBAL]` (if defined).
3. If neither a specific extension section nor `[GLOBAL]` exists, behavior is undefined (or will result in an error, depending on implementation).

---

## Error handling and `TODO: throw error`

`tng` uses a structured error system defined in `error.hpp`.  
Throughout the codebase, you may see comments like:

```cpp
// TODO: throw error
```

These mark places where proper error reporting should be implemented using the error API.

### Error system overview

- Error codes and categories are defined as enums (for example `ErrorCode`, `ParserError`, etc.) in `error.hpp`.
- An error object (exception type) is constructed using these enums.
- Errors are thrown instead of using raw strings or ad-hoc mechanisms.

The process to implement these TODOs is:

1. **Locate error definitions**

   Open:

   ```text
   include/tng/error.hpp
   ```

   (Or the corresponding header in your tree.) This file defines:
   - error codes (enums),
   - error categories,
   - error classes / exception types,
   - helper functions or factories, if any.

2. **Add a new error code (if needed)**

   If the scenario is not covered by any existing error code, add a new enumerator to the appropriate enum, following the existing naming conventions.

   Example:

   ```cpp
   enum class error_type
   {
       cannot_open_create_file,
       expected_file_n_find,
       file_does_n_exist,
 
       arg_expected_argument,

       c_array_dn_more,
       c_more_less_symbol_EFNS,
       c_no_config_file_select,
       c_cant_select_multi_conf
   };
   ```

3. **Replace `// TODO: throw error` with a proper throw**

   For example, instead of:

   ```cpp
   // TODO: throw error this config probelm. no file selected for config
   ```

   you might write:

   ```cpp
    throw tng_error{.error_type_o = error_type::c_no_config_file_select,
      .error_massage = {"no file selected for config"}};

   ```
  
---

## Contributing

We welcome contributions to `tng`. The project is under active development and there are many areas where you can help:

- implementing missing error handling (`// TODO: throw error`),
- extending configuration features,
- improving documentation and examples,
- adding tests for configuration parsing and file generation.

### Where to start

The easiest way to get started is to search for:

```text
// TODO:
```

in the codebase. Many of these are intentionally left as entry points for contributors.

Examples of current TODO categories:

- `// TODO: throw error`  
  Implement error handling using the structured error API in `error.hpp`.
- `// TODO: use PWD in here`  
  Improve path handling to optionally support `PWD`-based relative paths.
- `// TODO: Did we have to write modifie analyzer ...`  
  Design and implement logic for deciding when generated buffers should be rewritten.

### Coding guidelines

There is no any serious policy but it's very nice to use tng clang-format for your workspace
---

## License

`tng` is a under BSD license.
Please refer to the `LICENSE` file in the repository for the exact license terms.
