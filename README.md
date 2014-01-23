neuter+
=======

Concatenate files in the order you require.

Usage:

	neuter-plus --input "input-with-require-statement.js" --output "output-name.js" --basePath "base-for-the-required-files-paths"
	
A bit like [grunt-neuter](https://github.com/trek/grunt-neuter) but in fast.

Options
-------
### --input
Input file with the `require` statements.


### --output
Output file name

### --basePath
Base path from which relative file paths are resolved

### --wrapBefore
String to be placed before each `require` statement

Default:  `(function() {`

### --wrapAfter
String to be placed after each `require` statement

Default: `})();`

### --separator
String to be placed between `require` statements

Default: `\n\n`

### --stdout
Print result to STDOUT instead of writing to file
