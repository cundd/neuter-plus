/**
 * Created by daniel on 27/12/13.
 */

(function() {/*require('importedFile1.js');// */window.importedFile1 = true;})()
(function() {/*require('importedFile1.js');// */window.importedFile1 = true;})()(function() {/*require('importedFile2');// */window.importedFile2 = true;})()
(function() {/*require('importedFile1.js');// */window.importedFile1 = true;})()(function() {/*require('importedFile2');// */window.importedFile2 = true;})()(function() {/*require('importedFileWithSubRequire');// */require('')})()