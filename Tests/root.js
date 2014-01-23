/**
 * Created by daniel on 27/12/13.
 */

window = typeof window !== 'undefined' ? window : global;

require('importedFile1.js');
require('importedFile2');
require('importedFileWithSubRequire');
require('importNested');
require('nested2/*');
require('importNotExisting');

require('again/importedFile');
require('again/*');

console.log('ende')