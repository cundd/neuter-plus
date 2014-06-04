/**
 * Created by daniel on 27/12/13.
 */

window = typeof window !== 'undefined' ? window : global;
window.fileCounter = 0;
var fileCounterExpected = 16;

require('importedFile1.js');
require('importedFile2');
require('importedFileWithSubRequire');
require('importNested');
require('nested2/*');


require('importNestedNotExisting');
require('importNotExisting.js');
require('importNotExisting');

require('importedFileWithSubRequireNested/file1');

require('nested-more-levels/sublevel/file1');
require('nested-more-levels/sublevel-file');

require('again/importedFile');
require('again/*');


if (window.fileCounter != fileCounterExpected) {
	console.warn('Error: File counter not as expected: ' + window.fileCounter + "/" + fileCounterExpected);
}

console.log('Finished')