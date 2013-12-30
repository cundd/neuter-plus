/**
 * Created by daniel on 27/12/13.
 */

(function() {/*require('importedFile1.js');// */window.importedFile1 = true;

})()


(function() {/*require('importedFile2');// */window.importedFile2 = true;

})()


(function() {/*require('importedFileWithSubRequire');// */(function() {/*require('subRequiredFile');// */window.subRequiredFile = true;

})()



})()


(function() {/*require('importNested');// */window.nested = {};
(function() {/*require('nested\/file1');// */window.nested.file1 = true;

})()



})()


(function() {/*require('nested2\/*');// */// Nested 2 -> File 1

// Nested 2 -> File 2

})()

