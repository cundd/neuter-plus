window.importedFileWithSubRequireNested_file1 = true;
console.log('Imported importedFileWithSubRequireNested/file1.js');

require('importedFileWithSubRequireNested/file2');

require('importedFileWithSubRequireNested/notFound');
window.fileCounter++;